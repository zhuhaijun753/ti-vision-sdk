/*
 * Copyright (C) 2013 Texas Instruments
 *
 * Author : Pankaj Bharadiya <pankaj.bharadiya@ti.com>
 *
 * Tom Rix <Tom.Rix@windriver.com> and Sitara 2011 u-boot by
 * Mohammed Afzal M A <afzal@ti.com>
 *
 * Copyright (C) 2008 The Android Open Source Project
 * All rights reserved.
 *
 * Copyright 2014 Linaro, Ltd.
 * Dileep Katta <dileep.katta@linaro.org>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <command.h>
#include <usb/fastboot.h>
#include <linux/usb/ch9.h>
#include <linux/usb/gadget.h>
#include <environment.h>
#include <mmc.h>
#include <dfu.h>
#include <asm/arch/mmc_host_def.h>
#include <malloc.h>

#define EFI_VERSION 0x00010000
#define EFI_ENTRIES 128
#define EFI_NAMELEN 36

struct partition_emmc {
	const char *name;
	unsigned size_kb;
};

/* eMMC partition layout (All sizes are in kB)
 * Modify the below partition table to change the GPT configuration.
 * The entry for each partition can be modified as per the requirement.
 */
static struct partition_emmc partitions[] = {
	{ "-", 128 },	/* Master Boot Record and GUID Partition Table */
	{ "xloader", 128 },	/* First stage bootloader */
	{ "bootloader", 384 },	/* Second stage bootloader */
	{ "environment", 128 },
	{ "misc", 128 },		/* Rserved for internal purpose */
	{ "-", 384 },			/* Reserved */
	{ "efs", 16384 },
	{ "crypto", 16 },
	{ "recovery", 10*1024 },	/* Recovery partition  */
	{ "boot", 10*1024 },	/* Partition contains kernel + ramdisk images */
	{ "system", 768*1024 },		/* Android file system */
	{ "cache", 256*1024 },		/* Store Application Cache */
	{ "ipu1", 1024 },
	{ "ipu2", 1024 },
	{ "userdata", 0 },	/* User data */
	{ NULL, 0 },
};


static const u8 partition_type[16] = {
	0xa2, 0xa0, 0xd0, 0xeb, 0xe5, 0xb9, 0x33, 0x44,
	0x87, 0xc0, 0x68, 0xb6, 0xb7, 0x26, 0x99, 0xc7,
};

static const u8 random_uuid[16] = {
	0xff, 0x1f, 0xf2, 0xf9, 0xd4, 0xa8, 0x0e, 0x5f,
	0x97, 0x46, 0x59, 0x48, 0x69, 0xae, 0xc3, 0x4e,
};

struct efi_entry {
	u8 type_uuid[16];
	u8 uniq_uuid[16];
	u64 first_lba;
	u64 last_lba;
	u64 attr;
	u16 name[EFI_NAMELEN];
};

struct efi_header {
	u8 magic[8];

	u32 version;
	u32 header_sz;

	u32 crc32;
	u32 reserved;

	u64 header_lba;
	u64 backup_lba;
	u64 first_lba;
	u64 last_lba;

	u8 volume_uuid[16];

	u64 entries_lba;

	u32 entries_count;
	u32 entries_size;
	u32 entries_crc32;
} __packed;

struct ptable {
	u8 mbr[512];
	union {
		struct efi_header header;
		u8 block[512];
	};
	struct efi_entry entry[EFI_ENTRIES];
};

static void init_mbr(u8 *mbr, u32 blocks)
{
	mbr[0x1be] = 0x00; /* nonbootable */
	mbr[0x1bf] = 0xFF; /* bogus CHS */
	mbr[0x1c0] = 0xFF;
	mbr[0x1c1] = 0xFF;

	mbr[0x1c2] = 0xEE; /* GPT partition */
	mbr[0x1c3] = 0xFF; /* bogus CHS */
	mbr[0x1c4] = 0xFF;
	mbr[0x1c5] = 0xFF;

	mbr[0x1c6] = 0x01; /* start */
	mbr[0x1c7] = 0x00;
	mbr[0x1c8] = 0x00;
	mbr[0x1c9] = 0x00;

	memcpy(mbr + 0x1ca, &blocks, sizeof(u32));

	mbr[0x1fe] = 0x55;
	mbr[0x1ff] = 0xaa;
}


static void start_ptbl(struct ptable *ptbl, unsigned blocks)
{
	struct efi_header *hdr = &ptbl->header;

	memset(ptbl, 0, sizeof(*ptbl));

	init_mbr(ptbl->mbr, blocks - 1);

	memcpy(hdr->magic, "EFI PART", 8);
	hdr->version = EFI_VERSION;
	hdr->header_sz = sizeof(struct efi_header);
	hdr->header_lba = 1;
	hdr->backup_lba = blocks - 1;
	hdr->first_lba = 34;
	hdr->last_lba = blocks - 1;
	memcpy(hdr->volume_uuid, random_uuid, 16);
	hdr->entries_lba = 2;
	hdr->entries_count = EFI_ENTRIES;
	hdr->entries_size = sizeof(struct efi_entry);
}

static void end_ptbl(struct ptable *ptbl)
{
	struct efi_header *hdr = &ptbl->header;
	u32 n;

	n = crc32(0, 0, 0);
	n = crc32(n, (void *)ptbl->entry, sizeof(ptbl->entry));
	hdr->entries_crc32 = n;

	n = crc32(0, 0, 0);
	n = crc32(0, (void *)&ptbl->header, sizeof(ptbl->header));
	hdr->crc32 = n;
}

int add_ptn(struct ptable *ptbl, u64 first, u64 last, const char *name)
{
	struct efi_header *hdr = &ptbl->header;
	struct efi_entry *entry = ptbl->entry;
	unsigned n;

	if (first < 34) {
		printf("partition '%s' overlaps partition table\n", name);
		return -1;
	}

	if (last > hdr->last_lba) {
		printf("partition '%s' does not fit\n", name);
		return -1;
	}
	for (n = 0; n < EFI_ENTRIES; n++, entry++) {
		if (entry->last_lba)
			continue;
		memcpy(entry->type_uuid, partition_type, 16);
		memcpy(entry->uniq_uuid, random_uuid, 16);
		entry->uniq_uuid[0] = n;
		entry->first_lba = first;
		entry->last_lba = last;
		for (n = 0; (n < EFI_NAMELEN) && *name; n++)
			entry->name[n] = *name++;
		return 0;
	}
	printf("out of partition table entries\n");
	return -1;
}

void import_efi_partition(struct efi_entry *entry)
{
	struct fastboot_ptentry e;
	int n;
	if (memcmp(entry->type_uuid, partition_type, sizeof(partition_type)))
		return;
	for (n = 0; n < (sizeof(e.name)-1); n++)
		e.name[n] = entry->name[n];
	e.name[n] = 0;
	e.start = entry->first_lba;
	e.length = (entry->last_lba - entry->first_lba + 1) * 512;
	e.flags = 0;

	if (!strcmp(e.name, "environment"))
		e.flags |= FASTBOOT_PTENTRY_FLAGS_WRITE_ENV;
	fastboot_flash_add_ptn(&e);

	if (e.length > 0x100000)
		printf("%8d %8lluM %s\n", e.start, (e.length/(u64)0x100000), e.name);
	else
		printf("%8d %8lluK %s\n", e.start, (e.length/(u64)0x400), e.name);
}

int load_ptbl(void)
{
	u64 ptbl_sectors = 0;
	int i = 0, r = 0;

	struct mmc* mmc = NULL;

	struct ptable *gpt = memalign(ARCH_DMA_MINALIGN, sizeof(struct ptable));
	if (gpt == NULL) {
		printf("Failed to allocate GPT\n");
		return -1;
	}

	mmc = find_mmc_device(CONFIG_FASTBOOT_FLASH_MMC_DEV);
	if (mmc == NULL) {
		printf("No MMC in slot 1\n");
		r = -1;
		goto fail;
	}

	int gpt_size = sizeof(struct ptable);

	ptbl_sectors = (u64)(gpt_size / MMCSD_SECTOR_SIZE);

	r = mmc->block_dev.block_read(1, 0, ptbl_sectors,( void*)gpt);
	if (r == -1) {
		printf("error reading GPT\n");
		goto fail;
	}

	if (memcmp(gpt->header.magic, "EFI PART", 8)) {
		printf("efi partition table not found\n");
		r = -1;
		goto fail;
	}

	for (i = 0; i < EFI_ENTRIES; i++)
		import_efi_partition(&gpt->entry[i]);

fail:
	free(gpt);
	return r;
}

int board_mmc_fbtptn_init(void)
{
	struct mmc *mmc = NULL;
	int ret = 0;

        mmc = find_mmc_device(CONFIG_FASTBOOT_FLASH_MMC_DEV);
        if (!mmc) {
                printf("no mmc device at slot %x\n", CONFIG_FASTBOOT_FLASH_MMC_DEV);
                return -1;
        }
        mmc->has_init = 0;
        if (mmc_init(mmc))
                return -1;

        ret = mmc_select_hwpart(CONFIG_FASTBOOT_FLASH_MMC_DEV, 0);
        printf("switch to partitions #%d, %s\n",
               0, (!ret) ? "OK" : "ERROR");
        if (ret)
                return -1;

	return load_ptbl();
}


static struct ptable the_ptable;

int do_format(void)
{
	struct ptable *ptbl = &the_ptable;
	unsigned blocks;
	unsigned next;
	int n;
	int ret;

	/* get mmc info */
	struct mmc *mmc = find_mmc_device(CONFIG_FASTBOOT_FLASH_MMC_DEV);
	if (mmc == 0) {
		printf("no mmc device at slot %d", CONFIG_FASTBOOT_FLASH_MMC_DEV);
		return -1;
	}

	mmc->has_init = 0;
	if (mmc_init(mmc)) {
		printf("\n mmc init FAILED");
		return -1;
	} else{
		printf("\nmmc capacity is: %llu", mmc->capacity);
		printf("\nmmc: number of blocks:0x%lx", mmc->block_dev.lba);
		printf("\nmmc: block size:0x%lx", mmc->block_dev.blksz);
	}

	blocks = mmc->block_dev.lba;

	start_ptbl(ptbl, blocks);
	n = 0;
	next = 0;
	for (n = 0, next = 0; partitions[n].name; n++) {
		/* 10/11 : below line change size from KB to no of blocks */
		unsigned sz = partitions[n].size_kb*2;
		if (!strcmp(partitions[n].name, "-")) {
			next += sz;
			continue;
		}
		if (sz == 0)
			sz = blocks - next;
		if (add_ptn(ptbl, next, next + sz - 1, partitions[n].name))
			return -1;
		next += sz;
	}
	end_ptbl(ptbl);

	fastboot_flash_reset_ptn();

	ret = mmc_select_hwpart(CONFIG_FASTBOOT_FLASH_MMC_DEV, 0);
	printf("switch to partitions #%d, %s\n",
	       0, (!ret) ? "OK" : "ERROR");
	if (ret)
		return -1;

	n = mmc->block_dev.block_write(CONFIG_FASTBOOT_FLASH_MMC_DEV, 0x00,
				       (sizeof(struct ptable)/512)+1,
				       (void *)ptbl);

	if (n != ((sizeof(struct ptable)/512)+1)) {
		printf("Writing mbr is FAILED!\n");
		return -1;
	} else {
		printf("Writing mbr is DONE!\n");
	}

	printf("\nnew partition table:\n");
	load_ptbl();

	return 0;
}
