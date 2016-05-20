/*
 * (C) Copyright 2012
 * Texas Instruments, <www.ti.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#ifndef	_ASM_ARCH_SPL_H_
#define	_ASM_ARCH_SPL_H_

#define BOOT_DEVICE_NONE        0
#define BOOT_DEVICE_XIP         1
#define BOOT_DEVICE_XIPWAIT     2
#define BOOT_DEVICE_NAND        3
#define BOOT_DEVICE_ONENAND    4
#define BOOT_DEVICE_MMC1        5
#define BOOT_DEVICE_MMC2        6
#define BOOT_DEVICE_MMC2_2	7
#define BOOT_DEVICE_SATA	9
#define BOOT_DEVICE_SPI		10
#define BOOT_DEVICE_UART	0x43
#define BOOT_DEVICE_USB		0x45

#ifdef CONFIG_DRA7XX

#define SYSBOOT_TYPE_MASK   (0x30)
/* Automotive Production Booting */
#define SYSBOOT_TYPE_PROD   (0x30)
/* Memory Preferred Booting */
#define SYSBOOT_TYPE_MEM    (0x20)
/* Development Booting */
#define SYSBOOT_TYPE_DEV    (0x10)
/* Peripheral Preferred Booting */
#define SYSBOOT_TYPE_PER    (0x00)

#endif

#define MMC_BOOT_DEVICES_START	BOOT_DEVICE_MMC1
#define MMC_BOOT_DEVICES_END	BOOT_DEVICE_MMC2_2

#define SYS_BOOT_DEVICE         0x3F
#define SYS_BOOT_QSPI_1_PROD    0x36
#define SYS_BOOT_QSPI_4_PROD    0x37
#endif
