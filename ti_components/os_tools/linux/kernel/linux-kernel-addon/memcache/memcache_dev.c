/*
 *******************************************************************************
 *
 * Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

#include <dev_memcache_priv.h>

DMA_Dev gDMA_dev;


int DMA_devOpen(struct inode *inode, struct file *filp)
{
  int status=0;
  int minor, major;

  minor = iminor(inode);
  major = imajor(inode);

#ifdef DMA_DEBUG
  printk(KERN_INFO "DMA: DMA_devOpen()   , %4d, %2d \n", major, minor);
#endif

  return status;                /* success */
}

int DMA_devRelease(struct inode *inode, struct file *filp)
{
#ifdef DMA_DEBUG
  printk(KERN_INFO "DMA: DMA_devRelease()\n");
#endif
  return 0;
}


int DMA_devMmap (struct file * filp, struct vm_area_struct * vma)
{
    if (remap_pfn_range (vma,
                         vma->vm_start,
                         vma->vm_pgoff,
                         vma->vm_end - vma->vm_start,
                         vma->vm_page_prot)) {
        return -EAGAIN;
    }

    return 0;
}

long DMA_devIoctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
  int status=0;
  DMA_MmapPrm      mmapPrm;

#ifdef DMA_DEBUG
  printk(KERN_INFO "DMA: DMA_devIoctl()\n");
#endif

  if(!DMA_IOCTL_CMD_IS_VALID(cmd))
    return -1;

  cmd = DMA_IOCTL_CMD_GET(cmd);

  switch(cmd)
  {
    case DMA_CMD_MMAP:

      status = down_interruptible(&gDMA_dev.semLock);

      status = copy_from_user(&mmapPrm, (void*)arg, sizeof(mmapPrm));
      if(status==0) {

        #ifdef DMA_DEBUG
        printk(KERN_INFO "DMA: IOCTL: DMA_CMD_MMAP (0x%08x, %d) ### \n", mmapPrm.physAddr, mmapPrm.size);
        #endif

        if(mmapPrm.mapType==OSA_DMA_MMAP_TYPE_NOCACHE)
        {
                #ifdef DMA_DEBUG
                printk(KERN_INFO "DMA: ### ioremap_nocache() ### \n");
                #endif

                mmapPrm.virtAddr
                    = (unsigned int)ioremap_nocache(
                        mmapPrm.physAddr,
                        mmapPrm.size
                        );
        }
        if(mmapPrm.mapType==OSA_DMA_MMAP_TYPE_CACHE)
        {
                #ifdef DMA_DEBUG
                printk(KERN_INFO "DMA: ### ioremap_cache() ### \n");
                #endif

                mmapPrm.virtAddr
                    = (unsigned int)ioremap_cache(
                        mmapPrm.physAddr,
                        mmapPrm.size
                        );
        }
        if(mmapPrm.mapType==OSA_DMA_MMAP_TYPE_WRITE_COMBINED)
        {
                #ifdef DMA_DEBUG
                printk(KERN_INFO "DMA: ### ioremap_wc() ### \n");
                #endif


                mmapPrm.virtAddr
                    = (unsigned int)ioremap_wc(
                        mmapPrm.physAddr,
                        mmapPrm.size
                        );
        }

        if(status==0) {
          status = copy_to_user((void*)arg, &mmapPrm, sizeof(mmapPrm));
        }
      }

      up(&gDMA_dev.semLock);

      break;

      case DMA_CMD_CACHEINV:
         dmac_map_area(((DMA_CacheInvPrm *)arg)->virtAddr,
                       ((DMA_CacheInvPrm *)arg)->size, DMA_FROM_DEVICE);
         break;

      case DMA_CMD_CACHEWB:
         dmac_flush_range(((DMA_CacheWbPrm *)arg)->virtAddrStart,
                       ((DMA_CacheWbPrm *)arg)->virtAddrEnd);
         break;

      default:
         status = -1;
         break;
  }

  return status;
}


struct file_operations gDMA_devFileOps = {
  owner: THIS_MODULE,
  open: DMA_devOpen,
  release: DMA_devRelease,
  unlocked_ioctl: DMA_devIoctl,
  mmap: DMA_devMmap
};

int DMA_devInit(void)
{
  int     result, i;
  dev_t   dev = 0;

#ifdef DMA_DEBUG
  printk(KERN_INFO "DMA: DMA_devInit() \n");
#endif

  result = alloc_chrdev_region(&dev, 0, 1, DMA_DRV_NAME);

  if (result < 0) {
    FUNCERR( "DMA: can't get device major num \n");
    return result;
  }

  gDMA_dev.major = MAJOR(dev);

  sema_init(&gDMA_dev.semLock, 1);

  cdev_init(&gDMA_dev.cdev, &gDMA_devFileOps);

  gDMA_dev.cdev.owner = THIS_MODULE;
  gDMA_dev.cdev.ops = &gDMA_devFileOps;

  result = cdev_add(&gDMA_dev.cdev, dev, 1);

  if (result)
    FUNCERR( "DMA: Error [%d] while adding device [%s] \n", result, DMA_DRV_NAME);

  printk(KERN_INFO "DMA: Module install successful, device major num = %d \n", gDMA_dev.major);

  return result;
}

void DMA_devExit(void)
{
  dev_t   devno = MKDEV(gDMA_dev.major, 0);

#ifdef DMA_DEBUG
  printk(KERN_INFO "DMA: DMA_devExit() \n");
#endif

  cdev_del(&gDMA_dev.cdev);

  unregister_chrdev_region(devno, 1);
}

