/*
 * ELF loader with support for the "remoteproc" kernel module functionality.
 *
 * Copyright (c) 2015 Venkateswara Rao Mandela, Texas Instruments Inc
 * <venkat.mandela@ti.com>
 *
 * Modified from cmd_elf.c which carries the below copyright notice.
 */

 /* Copyright (c) 2001 William L. Pitts
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms are freely
  * permitted provided that the above copyright notice and this
  * paragraph and the following disclaimer are duplicated in all
  * such forms.
  *
  * This software is provided "AS IS" and without any express or
  * implied warranties, including, without limitation, the implied
  * warranties of merchantability and fitness for a particular
  * purpose.
  */

#include <errno.h>
#include <linux/compat.h>
#include <malloc.h>
#include <elf.h>
#include "remoteproc.h"

static struct resource_table *rsc_table;
static struct list_head mappings;

typedef int (*handle_resource_t) (void *, int offset, int avail);

void *alloc_mem(unsigned long len, unsigned long align);
unsigned int config_pagetable(unsigned int virt, unsigned int phys,
			      unsigned int len);

int va_to_pa(int va)
{
	struct rproc_mem_entry *maps = NULL;

	list_for_each_entry(maps, &mappings, node) {
		if (va >= maps->da && va < (maps->da + maps->len))
			return maps->dma + (va - maps->da);
	}

	return 0;
}

/* Virtio ring descriptors: 16 bytes.  These can chain together via "next". */
struct vring_desc {
	/* Address (guest-physical). */
	__u64 addr;
	/* Length. */
	__u32 len;
	/* The flags as indicated above. */
	__u16 flags;
	/* We chain unused descriptors via this, too */
	__u16 next;
};

/* u32 is used here for ids for padding reasons. */
struct vring_used_elem {
	/* Index of start of used descriptor chain. */
	__u32 id;
	/* Total length of the descriptor chain which was used (written to) */
	__u32 len;
};

static unsigned vring_size(unsigned int num, unsigned long align)
{
	return ((sizeof(struct vring_desc) * num + sizeof(__u16) * (3 + num)
		 + align - 1) & ~(align - 1))
	    + sizeof(__u16) * 3 + sizeof(struct vring_used_elem) * num;
}

static int handle_trace(struct fw_rsc_trace *rsc, int offset, int avail)
{
	if (sizeof(*rsc) > avail) {
		printf("trace rsc is truncated\n");
		return -EINVAL;
	}

	/* make sure reserved bytes are zeroes */
	if (rsc->reserved) {
		printf("trace rsc has non zero reserved bytes\n");
		return -EINVAL;
	}

	debug("trace rsc: da 0x%x, len 0x%x\n", rsc->da, rsc->len);

	return 0;
}

static int handle_devmem(struct fw_rsc_devmem *rsc, int offset, int avail)
{
	struct rproc_mem_entry *mapping;

	if (sizeof(*rsc) > avail) {
		printf("devmem rsc is truncated\n");
		return -EINVAL;
	}

	/* make sure reserved bytes are zeroes */
	if (rsc->reserved) {
		printf("devmem rsc has non zero reserved bytes\n");
		return -EINVAL;
	}

	debug("devmem rsc: pa 0x%x, da 0x%x, len 0x%x\n",
	      rsc->pa, rsc->da, rsc->len);

	config_pagetable(rsc->da, rsc->pa, rsc->len);

	mapping = kzalloc(sizeof(*mapping), GFP_KERNEL);
	if (!mapping) {
		printf("kzalloc mapping failed\n");
		return -ENOMEM;
	}

	/*
	 * We'll need this info later when we'll want to unmap everything
	 * (e.g. on shutdown).
	 *
	 * We can't trust the remote processor not to change the resource
	 * table, so we must maintain this info independently.
	 */
	mapping->dma = rsc->pa;
	mapping->da = rsc->da;
	mapping->len = rsc->len;
	list_add_tail(&mapping->node, &mappings);

	debug("mapped devmem pa 0x%x, da 0x%x, len 0x%x\n",
	      rsc->pa, rsc->da, rsc->len);

	return 0;
}

static int handle_carveout(struct fw_rsc_carveout *rsc, int offset, int avail)
{
	struct rproc_mem_entry *mapping;

	if (sizeof(*rsc) > avail) {
		printf("carveout rsc is truncated\n");
		return -EINVAL;
	}

	/* make sure reserved bytes are zeroes */
	if (rsc->reserved) {
		printf("carveout rsc has non zero reserved bytes\n");
		return -EINVAL;
	}

	debug("carveout rsc: da %x, pa %x, len %x, flags %x\n",
	      rsc->da, rsc->pa, rsc->len, rsc->flags);

	rsc->pa = (int)alloc_mem(rsc->len, 8);
	config_pagetable(rsc->da, rsc->pa, rsc->len);

	/*
	 * Ok, this is non-standard.
	 *
	 * Sometimes we can't rely on the generic iommu-based DMA API
	 * to dynamically allocate the device address and then set the IOMMU
	 * tables accordingly, because some remote processors might
	 * _require_ us to use hard coded device addresses that their
	 * firmware was compiled with.
	 *
	 * In this case, we must use the IOMMU API directly and map
	 * the memory to the device address as expected by the remote
	 * processor.
	 *
	 * Obviously such remote processor devices should not be configured
	 * to use the iommu-based DMA API: we expect 'dma' to contain the
	 * physical address in this case.
	 */
	mapping = kzalloc(sizeof(*mapping), GFP_KERNEL);
	if (!mapping) {
		printf("kzalloc mapping failed\n");
		return -ENOMEM;
	}

	/*
	 * We'll need this info later when we'll want to unmap
	 * everything (e.g. on shutdown).
	 *
	 * We can't trust the remote processor not to change the
	 * resource table, so we must maintain this info independently.
	 */
	mapping->dma = rsc->pa;
	mapping->da = rsc->da;
	mapping->len = rsc->len;
	list_add_tail(&mapping->node, &mappings);

	debug("carveout mapped 0x%x to 0x%x\n", rsc->da, rsc->pa);

	return 0;
}

#define RPROC_PAGE_SHIFT 12
#define RPROC_PAGE_SIZE  (1 << RPROC_PAGE_SHIFT)
#define RPROC_PAGE_ALIGN(x) (((x) + (RPROC_PAGE_SIZE - 1)) & ~(RPROC_PAGE_SIZE - 1))

static int alloc_vring(struct fw_rsc_vdev *rsc, int i)
{
	struct fw_rsc_vdev_vring *vring = &rsc->vring[i];
	int size;
	int order;
	void *pa;

	debug("vdev rsc: vring%d: da %x, qsz %d, align %d\n",
	      i, vring->da, vring->num, vring->align);

	/* make sure reserved bytes are zeroes */
	if (vring->reserved) {
		printf("vring rsc has non zero reserved bytes\n");
		return -EINVAL;
	}

	/* verify queue size and vring alignment are sane */
	if (!vring->num || !vring->align) {
		printf("invalid qsz (%d) or alignment (%d)\n",
		       vring->num, vring->align);
		return -EINVAL;
	}

	/* actual size of vring (in bytes) */
	size = RPROC_PAGE_ALIGN(vring_size(vring->num, vring->align));
	order = vring->align >> RPROC_PAGE_SHIFT;

	pa = alloc_mem(size, order);
	debug("alloc_mem(%#x, %d): %p\n", size, order, pa);
	vring->da = (u32) pa;

	return pa == NULL;
}

#define RPMSG_NUM_BUFS         (512)
#define RPMSG_BUF_SIZE         (512)
#define RPMSG_TOTAL_BUF_SPACE  (RPMSG_NUM_BUFS * RPMSG_BUF_SIZE)

static int handle_vdev(struct fw_rsc_vdev *rsc, int offset, int avail)
{
	int i, ret;
	void *pa;

	/* make sure resource isn't truncated */
	if (sizeof(*rsc) + rsc->num_of_vrings * sizeof(struct fw_rsc_vdev_vring)
	    + rsc->config_len > avail) {
		printf("vdev rsc is truncated\n");
		return -EINVAL;
	}

	/* make sure reserved bytes are zeroes */
	if (rsc->reserved[0] || rsc->reserved[1]) {
		printf("vdev rsc has non zero reserved bytes\n");
		return -EINVAL;
	}

	debug("vdev rsc: id %d, dfeatures %x, cfg len %d, %d vrings\n",
	      rsc->id, rsc->dfeatures, rsc->config_len, rsc->num_of_vrings);

	/* we currently support only two vrings per rvdev */
	if (rsc->num_of_vrings > 2) {
		printf("too many vrings: %d\n", rsc->num_of_vrings);
		return -EINVAL;
	}

	/* allocate the vrings */
	for (i = 0; i < rsc->num_of_vrings; i++) {
		ret = alloc_vring(rsc, i);
		if (ret)
			goto alloc_error;
	}

	pa = alloc_mem(RPMSG_TOTAL_BUF_SPACE, 6);
	debug("vring buffer alloc_mem(%#x, 6): %p\n",
	      RPMSG_TOTAL_BUF_SPACE, pa);

	return 0;

alloc_error:
	return ret;
}

/*
 * A lookup table for resource handlers. The indices are defined in
 * enum fw_resource_type.
 */
static handle_resource_t loading_handlers[RSC_LAST] = {
	[RSC_CARVEOUT] = (handle_resource_t) handle_carveout,
	[RSC_DEVMEM] = (handle_resource_t) handle_devmem,
	[RSC_TRACE] = (handle_resource_t) handle_trace,
	[RSC_VDEV] = (handle_resource_t) handle_vdev,
};

/* handle firmware resource entries before booting the remote processor */
static int handle_resources(int len, handle_resource_t handlers[RSC_LAST])
{
	handle_resource_t handler;
	int ret = 0, i;

	for (i = 0; i < rsc_table->num; i++) {
		int offset = rsc_table->offset[i];
		struct fw_rsc_hdr *hdr = (void *)rsc_table + offset;
		int avail = len - offset - sizeof(*hdr);
		void *rsc = (void *)hdr + sizeof(*hdr);

		/* make sure table isn't truncated */
		if (avail < 0) {
			printf("rsc table is truncated\n");
			return -EINVAL;
		}

		debug("rsc: type %d\n", hdr->type);

		if (hdr->type >= RSC_LAST) {
			printf("unsupported resource %d\n", hdr->type);
			continue;
		}

		handler = handlers[hdr->type];
		if (!handler)
			continue;

		ret = handler(rsc, offset + sizeof(*hdr), avail);
		if (ret)
			break;
	}

	return ret;
}

static Elf32_Shdr *find_table(unsigned int addr)
{
	Elf32_Ehdr *ehdr;	/* Elf header structure pointer     */
	Elf32_Shdr *shdr;	/* Section header structure pointer */
	Elf32_Shdr sectionheader;
	int i;
	u8 *elf_data;
	char *name_table;
	struct resource_table *ptable;

	ehdr = (Elf32_Ehdr *) addr;
	elf_data = (u8 *) ehdr;
	shdr = (Elf32_Shdr *) (elf_data + ehdr->e_shoff);
	memcpy(&sectionheader, &shdr[ehdr->e_shstrndx], sizeof(sectionheader));
	name_table = (char *)(elf_data + sectionheader.sh_offset);

	for (i = 0; i < ehdr->e_shnum; i++, shdr++) {
		memcpy(&sectionheader, shdr, sizeof(sectionheader));
		u32 size = sectionheader.sh_size;
		u32 offset = sectionheader.sh_offset;

		if (strcmp(name_table + sectionheader.sh_name,
			   ".resource_table"))
			continue;

		ptable = (struct resource_table *)(elf_data + offset);

		/* make sure table has at least the header */
		if (sizeof(struct resource_table) > size) {
			printf("header-less resource table\n");
			return NULL;
		}

		/* we don't support any version beyond the first */
		if (ptable->ver != 1) {
			printf("unsupported fw ver: %d\n", ptable->ver);
			return NULL;
		}

		/* make sure reserved bytes are zeroes */
		if (ptable->reserved[0] || ptable->reserved[1]) {
			printf("non zero reserved bytes\n");
			return NULL;
		}

		/* make sure the offsets array isn't truncated */
		if (ptable->num * sizeof(ptable->offset[0]) +
		    sizeof(struct resource_table) > size) {
			printf("resource table incomplete\n");
			return NULL;
		}

		return shdr;
	}

	return NULL;
}

static struct resource_table *find_resource_table(unsigned int addr,
						  int *tablesz)
{
	Elf32_Shdr *shdr;
	Elf32_Shdr sectionheader;
	struct resource_table *ptable;
	u8 *elf_data = (u8 *) addr;

	shdr = find_table(addr);
	if (!shdr) {
		printf
		    ("find_resource_table: failed to get resource section header\n");
		return NULL;
	}

	memcpy(&sectionheader, shdr, sizeof(sectionheader));
	ptable = (struct resource_table *)(elf_data + sectionheader.sh_offset);
	if (tablesz)
		*tablesz = sectionheader.sh_size;

	return ptable;
}

/* ======================================================================
 * A very simple elf loader, assumes the image is valid, returns the
 * entry point address.
 * ====================================================================== */
unsigned long load_elf_image_phdr_rproc(unsigned long addr,
					unsigned long *entry_point)
{
	Elf32_Ehdr *ehdr;	/* Elf header structure pointer     */
	Elf32_Phdr *phdr;	/* Program header structure pointer */
	Elf32_Phdr proghdr;
	struct resource_table *ptable = NULL;
	int tablesz;
	int va;
	int pa;
	int ret;
	int i;

	if (entry_point == 0)
		return 0;

	ehdr = (Elf32_Ehdr *) addr;
	phdr = (Elf32_Phdr *) (addr + ehdr->e_phoff);

	ptable = find_resource_table(addr, &tablesz);
	if (!ptable) {
		printf("%s : failed to find resource table\n", __func__);
		return 0;
	} else {
		debug("%s : found resource table\n", __func__);

		rsc_table = kzalloc(tablesz, GFP_KERNEL);
		if (!rsc_table) {
			printf("resource table alloc failed!\n");
			return 0;
		}

		/* Copy the resource table into a local buffer
		 * before handling the resource table.
		 */
		memcpy(rsc_table, ptable, tablesz);

		INIT_LIST_HEAD(&mappings);

		ret = handle_resources(tablesz, loading_handlers);
		if (ret) {
			printf("handle_resources failed: %d\n", ret);
			return 0;
		}

		/* Instead of trying to mimic the kernel flow of copying the
		 * processed resource table into its post ELF load location in
		 * DDR , I am copying it into its original location.
		 */
		memcpy(ptable, rsc_table, tablesz);

		free(rsc_table);
		rsc_table = NULL;
	}

	/* Load each program header */
	for (i = 0; i < ehdr->e_phnum; ++i) {

		memcpy(&proghdr, phdr, sizeof(Elf32_Phdr));

		if (proghdr.p_type != PT_LOAD) {
			++phdr;
			continue;
		}

		va = proghdr.p_paddr;
		pa = va_to_pa(va);
		if (pa)
			proghdr.p_paddr = pa;

		void *dst = (void *)(uintptr_t) proghdr.p_paddr;
		void *src = (void *)addr + proghdr.p_offset;

		debug("Loading phdr %i to 0x%p (%i bytes)\n",
		      i, dst, proghdr.p_filesz);
		if (proghdr.p_filesz)
			memcpy(dst, src, proghdr.p_filesz);
		if (!ptable) {
			if ((proghdr.p_filesz != proghdr.p_memsz)
			    && (proghdr.p_paddr - 0x58820000) > 0x4000
			    && proghdr.p_memsz > 9)
				memset(dst + proghdr.p_filesz, 0x00,
				       proghdr.p_memsz - proghdr.p_filesz);
		} else {
			if (proghdr.p_filesz != proghdr.p_memsz)
				memset(dst + proghdr.p_filesz, 0x00,
				       proghdr.p_memsz - proghdr.p_filesz);
		}
		/*Don't have to flush cache if greater than 15MB */
		if (proghdr.p_memsz < 15 * 1024 * 1024)
			flush_cache((unsigned long)dst, proghdr.p_filesz);
		++phdr;
	}

	*entry_point = ehdr->e_entry;

	return 1;
}
