/*
 * Copyright 2008 - 2009 Windriver, <www.windriver.com>
 * Author: Tom Rix <Tom.Rix@windriver.com>
 *
 * (C) Copyright 2014 Linaro, Ltd.
 * Rob Herring <robh@kernel.org>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#include <common.h>
#include <command.h>
#include <g_dnl.h>
#include <usb.h>
#include <usb/fastboot.h>

int do_fastboot(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
	int ret;

	board_usb_init(0, USB_INIT_DEVICE);

#ifdef CONFIG_FASTBOOT_FLASH_MMC_DEV
	board_partition_init();
#endif
	ret = g_dnl_register("usb_dnl_fastboot");
	if (ret)
		return ret;

	while (1) {
		if (ctrlc())
			break;
		usb_gadget_handle_interrupts(0);
	}

	g_dnl_unregister();
	board_usb_cleanup(0, USB_INIT_DEVICE);
	return CMD_RET_SUCCESS;
}

U_BOOT_CMD(
	fastboot,	1,	0,	do_fastboot,
	"use USB Fastboot protocol",
	"\n"
	"    - run as a fastboot usb device"
);
