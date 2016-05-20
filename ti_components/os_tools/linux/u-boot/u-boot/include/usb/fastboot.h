/*
 * (C) Copyright 2008 - 2009
 * Windriver, <www.windriver.com>
 * Tom Rix <Tom.Rix at windriver.com>
 *
 * Copyright (c) 2011 Sebastian Andrzej Siewior <bigeasy at linutronix.de>
 *
 *
 * Copyright (C) 2008 The Android Open Source Project
 * All rights reserved.
 *
 * Copyright 2014 Linaro, Ltd.
 * Dileep Katta <dileep.katta@linaro.org>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef FASTBOOT_H
#define FASTBOOT_H

#include <common.h>
#include <command.h>
#include <environment.h>
#include <linux/usb/ch9.h>
#include <linux/usb/gadget.h>

#ifdef CONFIG_CMD_FASTBOOT

/* Android-style flash naming */
typedef struct fastboot_ptentry fastboot_ptentry;

/* flash partitions are defined in terms of blocks
 ** (flash erase units)
 */
struct fastboot_ptentry {
	/* The logical name for this partition, null terminated */
	char name[16];
	/* The start wrt the nand part, must be multiple of nand block size */
	unsigned int start;
	/* The length of the partition, must be multiple of nand block size */
	u64 length;
	/* Controls the details of how operations are done on the partition
	   See the FASTBOOT_PTENTRY_FLAGS_*'s defined below */
	unsigned int flags;
};

/* Lower byte shows if the read/write/erase operation in
   repeated.  The base address is incremented.
   Either 0 or 1 is ok for a default */

#define FASTBOOT_PTENTRY_FLAGS_REPEAT_MASK(n)   (n & 0x0f)
#define FASTBOOT_PTENTRY_FLAGS_REPEAT_4         0x00000004

/* Writes happen a block at a time.
   If the write fails, go to next block
   NEXT_GOOD_BLOCK and CONTIGOUS_BLOCK can not both be set */
#define FASTBOOT_PTENTRY_FLAGS_WRITE_NEXT_GOOD_BLOCK  0x00000010

/* Find a contiguous block big enough for a the whole file
   NEXT_GOOD_BLOCK and CONTIGOUS_BLOCK can not both be set */
#define FASTBOOT_PTENTRY_FLAGS_WRITE_CONTIGUOUS_BLOCK 0x00000020

/* Sets the ECC to software before writing
   HW and SW ECC should not both be set. */
#define FASTBOOT_PTENTRY_FLAGS_WRITE_SW_ECC           0x00000040

/* Sets the ECC to hardware before writing
   HW and SW ECC should not both be set. */
#define FASTBOOT_PTENTRY_FLAGS_WRITE_HW_ECC           0x00000080

/* Sets the ECC to hardware before writing
   HW and SW ECC should not both be set. */
#define FASTBOOT_PTENTRY_FLAGS_WRITE_HW_BCH4_ECC      0x00000100

/* Sets the ECC to hardware before writing
   HW and SW ECC should not both be set. */
#define FASTBOOT_PTENTRY_FLAGS_WRITE_HW_BCH8_ECC      0x00000200

/* Sets the ECC to hardware before writing
   HW and SW ECC should not both be set. */
#define FASTBOOT_PTENTRY_FLAGS_WRITE_HW_BCH16_ECC     0x00000400

/* Write the file with write.i */
#define FASTBOOT_PTENTRY_FLAGS_WRITE_I                0x00000800

/* Write the file with write.jffs2 */
#define FASTBOOT_PTENTRY_FLAGS_WRITE_JFFS2            0x00001000

/* Write the file as a series of variable/value pairs
   using the setenv and saveenv commands */
#define FASTBOOT_PTENTRY_FLAGS_WRITE_ENV              0x00002000


/* The Android-style flash handling */

/* tools to populate and query the partition table */
void fastboot_flash_add_ptn(fastboot_ptentry *ptn);
fastboot_ptentry *fastboot_flash_find_ptn(const char *name);
fastboot_ptentry *fastboot_flash_get_ptn(unsigned n);
unsigned int fastboot_flash_get_ptn_count(void);
void fastboot_flash_dump_ptn(void);
int fastboot_oem(const char *cmd);
int do_format(void);
int board_mmc_fbtptn_init(void);
void fastboot_flash_reset_ptn(void);
int board_partition_init(void);

extern int do_mmcops(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);

__weak int check_fastboot(void);

__weak int check_recovery(void);

__weak void fastboot_reboot_bootloader(void);

#endif
#endif
