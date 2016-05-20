/*
 * (C) Copyright 2010
 * Texas Instruments, <www.ti.com>
 *
 * Aneesh V <aneesh@ti.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#include <common.h>
#include <spl.h>
#include <asm/u-boot.h>
#include <mmc.h>
#include <version.h>
#include <image.h>
#include <fat.h>
#include <remoteproc.h>
#ifdef CONFIG_SPL_ANDROID_BOOT_SUPPORT
#include <fdt_support.h>
#endif

DECLARE_GLOBAL_DATA_PTR;

static int mmc_load_image_raw(struct mmc *mmc, unsigned long sector)
{
	unsigned long err;
	u32 image_size_sectors;
	struct image_header *header;
	u32 boot_device;
	u8 device;
#ifdef CONFIG_SPL_ANDROID_BOOT_SUPPORT
	const char *s;
#endif
	boot_device = spl_boot_device();
	if(boot_device == BOOT_DEVICE_MMC1) {
		device = 0;
	} else {
		device = 1;
	}

	header = (struct image_header *)(CONFIG_SYS_TEXT_BASE -
						sizeof(struct image_header));

	/* read image header to find the image size & load address */
	err = mmc->block_dev.block_read(device, sector, 1, header);
	if (err == 0)
		goto end;

#ifdef CONFIG_SPL_ANDROID_BOOT_SUPPORT
	if (genimg_get_format(header) == IMAGE_FORMAT_ANDROID) {
		printf("Loading Android image\n");
	} else
#endif
	if (image_get_magic(header) != IH_MAGIC)
		return -1;

	spl_parse_image_header(header);

	/* convert size to sectors - round up */
	image_size_sectors = (spl_image.size + mmc->read_bl_len - 1) /
				mmc->read_bl_len;

	/* Read the header too to avoid extra memcpy */
	err = mmc->block_dev.block_read(device, sector, image_size_sectors,
					(void *)spl_image.load_addr);

#ifdef CONFIG_SPL_ANDROID_BOOT_SUPPORT
	if (err == 0)
		goto end;

	/* load the ramdisk if this is an Android image */
	if (genimg_get_format(header) == IMAGE_FORMAT_ANDROID) {
		ulong ramdisk_start, ramdisk_len, ramdisk_load;
		u32 sector_ramdisk;
		printf("Loading Android ramdisk\n");

		android_image_get_ramdisk((const struct andr_img_hdr *)header,
					  &ramdisk_start, &ramdisk_len);
		ramdisk_load = android_image_get_rload(
					(const struct andr_img_hdr *)header);
		sector_ramdisk = sector +
					((ramdisk_start - (ulong)header) /
						mmc->block_dev.blksz);
		image_size_sectors = (ramdisk_len + mmc->read_bl_len - 1) /
					mmc->read_bl_len;

		err = mmc->block_dev.block_read(device, sector_ramdisk,
						image_size_sectors, (void *)ramdisk_load);
		if (err == 0)
			goto end;

		err = fdt_resize((void *)CONFIG_SYS_SPL_ARGS_ADDR);
		if (err == 0) {
#ifdef CONFIG_SPL_LIBCOMMON_SUPPORT
			printf("spl: fdt_resize err - %lu\n", err);
#endif
			goto end_noprint;
		}
		err = fdt_chosen((void *)CONFIG_SYS_SPL_ARGS_ADDR);
		if (err < 0) {
#ifdef CONFIG_SPL_LIBCOMMON_SUPPORT
			printf("spl: fdt_chosen err - %lu\n", err);
#endif
			err = 0;
			goto end_noprint;
		}
		err = fdt_initrd((void *)CONFIG_SYS_SPL_ARGS_ADDR, ramdisk_load,
				 ramdisk_load + ramdisk_len);
		if (err < 0) {
#ifdef CONFIG_SPL_LIBCOMMON_SUPPORT
			printf("spl: fdt_initrd err - %lu\n", err);
#endif
			err = 0;
			goto end_noprint;
		}

		s = getenv("serial#");
		if (s) {
			static char data[512];
			int  nodeoffset, len;

			printf("serial# is %s\n", s);
			nodeoffset = fdt_path_offset((void *)CONFIG_SYS_SPL_ARGS_ADDR, "/chosen");
			if (nodeoffset < 0) {
#ifdef CONFIG_SPL_LIBCOMMON_SUPPORT
				printf ("spl: fdt_path_offset err - %lu\n", err);
#endif
				err = 0;
				goto end_noprint;
			}

			sprintf(data, "androidboot.serialno=%s ", s);
			len = strlen(data) + 1;

			err = fdt_setprop((void *)CONFIG_SYS_SPL_ARGS_ADDR,
					  nodeoffset, "bootargs", data, len);
			if (err < 0) {
#ifdef CONFIG_SPL_LIBCOMMON_SUPPORT
				printf ("spl: fdt_setprop err - %lu\n", err);
#endif
				err = 0;
				goto end_noprint;
			}
		}

		err = 1;
		goto end;
	}
#endif

end:
#ifdef CONFIG_SPL_LIBCOMMON_SUPPORT
	if (err == 0)
		printf("spl: mmc blk read err - %lu\n", err);
#endif

#ifdef CONFIG_SPL_ANDROID_BOOT_SUPPORT
end_noprint:
#endif

	return (err == 0);
}

#ifdef CONFIG_SPL_OS_BOOT
static int mmc_load_image_raw_os(struct mmc *mmc)
{
	u32 device;
#if defined(CONFIG_SPL_MMC_DTB_NAME) || defined(CONFIG_SPL_MMC_KERNEL_NAME)
	int ret;
	disk_partition_t info;
#endif
	lbaint_t sector, num_sectors;

	if (spl_boot_device() == BOOT_DEVICE_MMC1)
		device = 0;
	else
		device = 1;

#ifdef CONFIG_SPL_MMC_DTB_NAME
	ret = get_partition_info_efi_by_name(&mmc->block_dev,
					     CONFIG_SPL_MMC_DTB_NAME,
					     &info);
	if (ret) {
#ifdef CONFIG_SPL_LIBCOMMON_SUPPORT
		printf("cannot find partition: '%s'\n",
		       CONFIG_SPL_MMC_DTB_NAME);
#endif
		return -1;
	}

	sector = info.start;
	num_sectors = info.size;
#else
	sector = CONFIG_SYS_MMCSD_RAW_MODE_ARGS_SECTOR;
	num_sectors = CONFIG_SYS_MMCSD_RAW_MODE_ARGS_SECTOR;
#endif

	if (!mmc->block_dev.block_read(device,
				       sector,
				       num_sectors,
				       (void *)CONFIG_SYS_SPL_ARGS_ADDR)) {
#ifdef CONFIG_SPL_LIBCOMMON_SUPPORT
		printf("mmc args blk read error\n");
#endif
		return -1;
	}

#ifdef CONFIG_SPL_MMC_KERNEL_NAME
	ret = get_partition_info_efi_by_name(&mmc->block_dev,
					     CONFIG_SPL_MMC_KERNEL_NAME,
					     &info);
	if (ret) {
#ifdef CONFIG_SPL_LIBCOMMON_SUPPORT
		printf("cannot find partition: '%s'\n",
		       CONFIG_SPL_MMC_KERNEL_NAME);
#endif
		return -1;
	}

	sector = info.start;
#else
	sector = CONFIG_SYS_MMCSD_RAW_MODE_KERNEL_SECTOR;
#endif
	return mmc_load_image_raw(mmc, sector);
}
#endif

u32 spl_mmc_load_core(u32 core_id)
{
	struct rproc *cfg = NULL;
	s32 err;
	struct mmc *mmc;

	if ((core_id == 0) || (core_id >= RPROC_END_ENUMS)) {
		printf("Invalid core id speicified: %d\n", core_id);
		return 1;
	}

	cfg = rproc_cfg_arr[core_id];

	debug("spl: loading remote core image %s\n", cfg->firmware_name);

	spl_mmc_init(&mmc);

	/* load the remote core image from patrition */
	if (cfg->ptn) {
		disk_partition_t info;


		err = get_partition_info_efi_by_name(&mmc->block_dev,
						     cfg->ptn, &info);
		if (err) {
#ifdef CONFIG_SPL_LIBCOMMON_SUPPORT
			printf("cannot find partition: '%s'\n",
			       cfg->ptn);
#endif
		} else if (!mmc->block_dev.block_read(mmc->block_dev.dev,
						      info.start,
						      info.size,
						      (void *)cfg->load_addr)) {
			printf("error reading from mmc\n");
			err = -1;
		} else {
			err = 1;
		}
	} else {
		/* load the remotecore image */
		err = file_fat_read(cfg->firmware_name, (u8 *) cfg->load_addr, 0);
	}

	if (err <= 0) {
		printf("spl: error reading image %s, err - %d\n",
		       cfg->firmware_name, err);
		return 1;
	}

	return 0;
}

void spl_mmc_preinit(void)
{
	static u32 init_needed = 1;

	if (init_needed == 1) {
		mmc_initialize(gd->bd);
		init_needed = 0;
	}
	return;
}

void spl_mmc_init(struct mmc **mmc)
{
	int err;
	u32 boot_device;
	u8 device;
	boot_device = spl_boot_device();
	if(boot_device == BOOT_DEVICE_MMC1) {
		device = 0;
	} else {
		device = 1;
	}

	/*
	 * Call the preinit function to handle the case
	 * where preinit was not triggered beforehand.
	 * This function is a NOP in case preinit was done.
	 */
	spl_mmc_preinit();

	/* We register only one device. So, the dev id is always 0 */
	*mmc = find_mmc_device(device);
	if (!*mmc) {
#ifdef CONFIG_SPL_LIBCOMMON_SUPPORT
		puts("spl: mmc device not found!!\n");
#endif
		hang();
	}

	err = mmc_init(*mmc);
	if (err) {
#ifdef CONFIG_SPL_LIBCOMMON_SUPPORT
		printf("spl: mmc init failed: err - %d\n", err);
#endif
		hang();
	}
}

#ifdef CONFIG_SPL_OS_BOOT
int spl_mmc_load_image_raw_os(void)
{
	struct mmc *mmc;

	spl_mmc_init(&mmc);

	return mmc_load_image_raw_os(mmc);
}
#endif

void spl_mmc_load_image(void)
{
	struct mmc *mmc;
	int err = 0;
	u32 boot_mode;
	printf("%s\n", __func__);

	spl_mmc_init(&mmc);

	boot_mode = spl_boot_mode();
	if (boot_mode == MMCSD_MODE_RAW) {
		debug("boot mode - RAW\n");
#ifdef CONFIG_SPL_OS_BOOT
		if (spl_start_uboot() || mmc_load_image_raw_os(mmc))
#endif
		err = mmc_load_image_raw(mmc,
			CONFIG_SYS_MMCSD_RAW_MODE_U_BOOT_SECTOR);
#ifdef CONFIG_SPL_FAT_SUPPORT
	} else if (boot_mode == MMCSD_MODE_FAT) {
		debug("boot mode - FAT\n");
#ifdef CONFIG_SPL_OS_BOOT
		if (spl_start_uboot() || spl_load_image_fat_os(&mmc->block_dev,
								CONFIG_SYS_MMC_SD_FAT_BOOT_PARTITION))
#endif
		err = spl_load_image_fat(&mmc->block_dev,
					CONFIG_SYS_MMC_SD_FAT_BOOT_PARTITION,
					CONFIG_SPL_FAT_LOAD_PAYLOAD_NAME);
#endif
#ifdef CONFIG_SUPPORT_EMMC_BOOT
	} else if (boot_mode == MMCSD_MODE_EMMCBOOT) {
		/*
		 * We need to check what the partition is configured to.
		 * 1 and 2 match up to boot0 / boot1 and 7 is user data
		 * which is the first physical partition (0).
		 */
		int part = (mmc->part_config >> 3) & PART_ACCESS_MASK;

		if (part == 7)
			part = 0;

		if (mmc_switch_part(0, part)) {
#ifdef CONFIG_SPL_LIBCOMMON_SUPPORT
			puts("MMC partition switch failed\n");
#endif
			hang();
		}
#ifdef CONFIG_SPL_OS_BOOT
		if (spl_start_uboot() || mmc_load_image_raw_os(mmc))
#endif
		err = mmc_load_image_raw(mmc,
			CONFIG_SYS_MMCSD_RAW_MODE_U_BOOT_SECTOR);
#endif
	} else {
#ifdef CONFIG_SPL_LIBCOMMON_SUPPORT
		puts("spl: wrong MMC boot mode\n");
#endif
		hang();
	}

	if (err)
		hang();
}
