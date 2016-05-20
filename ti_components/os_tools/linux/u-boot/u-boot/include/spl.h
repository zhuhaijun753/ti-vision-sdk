/*
 * (C) Copyright 2012
 * Texas Instruments, <www.ti.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#ifndef	_SPL_H_
#define	_SPL_H_

/* Platform-specific defines */
#include <linux/compiler.h>
#include <asm/spl.h>
#include <mmc.h>


/* Boot type */
#define MMCSD_MODE_UNDEFINED	0
#define MMCSD_MODE_RAW		1
#define MMCSD_MODE_FAT		2
#define MMCSD_MODE_EMMCBOOT	3
#ifdef CONFIG_SPL_SPI_PROD_OS_BOOT
#define SPI_MODE_PROD		4
#endif

struct spl_image_info {
	const char *name;
	u8 os;
	u32 load_addr;
	u32 entry_point;
	u32 size;
	u32 flags;
};

#define SPL_COPY_PAYLOAD_ONLY	1

extern struct spl_image_info spl_image;

/* SPL common functions */
void preloader_console_init(void);
u32 spl_boot_device(void);
u32 spl_boot_mode(void);
void spl_parse_image_header(const struct image_header *header);
void spl_board_prepare_for_linux(void);
void __noreturn jump_to_image_linux(void *arg);
int spl_start_uboot(void);
void spl_display_print(void);

/* NAND SPL functions */
void spl_nand_load_image(void);

/* OneNAND SPL functions */
void spl_onenand_load_image(void);

/* NOR SPL functions */
void spl_nor_load_image(void);

/* MMC SPL functions */
void spl_mmc_load_image(void);

#ifdef CONFIG_SPL_OS_BOOT
/* MMC SPL functions */
int spl_mmc_load_image_raw_os(void);
#endif

/* YMODEM SPL functions */
void spl_ymodem_load_image(void);

/* SPI SPL functions */
void spl_spi_load_image(void);

/* Ethernet SPL functions */
void spl_net_load_image(const char *device);

/* USB SPL functions */
void spl_usb_load_image(void);

/* SATA SPL functions */
void spl_sata_load_image(void);

/* SPL FAT image functions */
int spl_load_image_fat(block_dev_desc_t *block_dev, int partition, const char *filename);
int spl_load_image_fat_os(block_dev_desc_t *block_dev, int partition);

void spl_mmc_init(struct mmc **mmc);

/*
 * Defined a function to allow the mmc preinit to be triggered before the
 * full mmc_init() function call. Doing a mmc preinit can be useful when doing
 * boot time optimizations.The wait time in mmc initialization can now
 * be utilized for other tasks.
 *
 * mmc preinit is triggered from the mmc_initialize() function call if the
 * preinit flag is set in the device creation. Calling mmc_initialize()
 * a second time, reinitializes the mmc_devices list and nullifies the benefit
 * of doing a mmc_preinit.
 *
 * This function allows calling mmc_initialize() only once even if we
 * do spl_mmc_init() multiple times.
 *
 * If the SPL is not being customized for reduced MMC boot time, the normal
 * calling sequence of spl_mmc_init() can be used.
 *
 * If boot time reduction is desired, the calling sequence is
 *
 * spl_mmc_preinit();
 * .. do non mmc operations.
 * spl_mmc_init();
 *
 */
void spl_mmc_preinit(void);

#ifdef CONFIG_SPL_BOARD_INIT
void spl_board_init(void);
#endif

u32 spl_mmc_load_core(u32 core_id);
u32 spl_boot_core(u32 core_id);

#endif
