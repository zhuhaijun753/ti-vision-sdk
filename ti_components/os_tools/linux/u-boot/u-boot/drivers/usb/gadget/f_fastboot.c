/*
 * (C) Copyright 2008 - 2009
 * Windriver, <www.windriver.com>
 * Tom Rix <Tom.Rix@windriver.com>
 *
 * Copyright 2011 Sebastian Andrzej Siewior <bigeasy@linutronix.de>
 *
 * Copyright 2014 Linaro, Ltd.
 * Rob Herring <robh@kernel.org>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#include <config.h>
#include <common.h>
#include <errno.h>
#include <malloc.h>
#include <linux/usb/ch9.h>
#include <linux/usb/gadget.h>
#include <linux/usb/composite.h>
#include <linux/compiler.h>
#include <version.h>
#include <g_dnl.h>
#ifdef CONFIG_FASTBOOT_FLASH_MMC_DEV
#include <fb_mmc.h>
#endif
#include <usb/fastboot.h>
#include <command.h>
#include <asm/io.h>
#include <asm/omap_common.h>
#include <android_image.h>

#define FASTBOOT_VERSION		"0.4"

#define FASTBOOT_INTERFACE_CLASS	0xff
#define FASTBOOT_INTERFACE_SUB_CLASS	0x42
#define FASTBOOT_INTERFACE_PROTOCOL	0x03

#define RX_ENDPOINT_MAXIMUM_PACKET_SIZE_2_0  (0x0200)
#define RX_ENDPOINT_MAXIMUM_PACKET_SIZE_1_1  (0x0040)
#define TX_ENDPOINT_MAXIMUM_PACKET_SIZE      (0x0040)

/* The 64 defined bytes plus \0 */
#define RESPONSE_LEN	(64 + 1)

#define EP_BUFFER_SIZE			4096

#define CONTROL_STATUS  0x4A002134
#define DEVICETYPE_MASK  (0x7 << 6)

/* To support the Android-style naming of flash */
#define MAX_PTN 16
static fastboot_ptentry ptable[MAX_PTN];
static unsigned int pcount;
/* static int static_pcount = -1; */

/* omap-type */
typedef enum {
        OMAP_TYPE_TEST,
        OMAP_TYPE_EMU,
        OMAP_TYPE_SEC,
        OMAP_TYPE_GP,
        OMAP_TYPE_BAD,
} omap_type;

struct f_fastboot {
	struct usb_function usb_function;

	/* IN/OUT EP's and corresponding requests */
	struct usb_ep *in_ep, *out_ep;
	struct usb_request *in_req, *out_req;
};

static inline struct f_fastboot *func_to_fastboot(struct usb_function *f)
{
	return container_of(f, struct f_fastboot, usb_function);
}

static struct f_fastboot *fastboot_func;
static unsigned int download_size;
static unsigned int download_bytes;

static struct usb_endpoint_descriptor fs_ep_in = {
	.bLength            = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType    = USB_DT_ENDPOINT,
	.bEndpointAddress   = USB_DIR_IN,
	.bmAttributes       = USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize     = TX_ENDPOINT_MAXIMUM_PACKET_SIZE,
	.bInterval          = 0x00,
};

static struct usb_endpoint_descriptor fs_ep_out = {
	.bLength		= USB_DT_ENDPOINT_SIZE,
	.bDescriptorType	= USB_DT_ENDPOINT,
	.bEndpointAddress	= USB_DIR_OUT,
	.bmAttributes		= USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize		= RX_ENDPOINT_MAXIMUM_PACKET_SIZE_1_1,
	.bInterval		= 0x00,
};

static struct usb_endpoint_descriptor hs_ep_out = {
	.bLength		= USB_DT_ENDPOINT_SIZE,
	.bDescriptorType	= USB_DT_ENDPOINT,
	.bEndpointAddress	= USB_DIR_OUT,
	.bmAttributes		= USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize		= RX_ENDPOINT_MAXIMUM_PACKET_SIZE_2_0,
	.bInterval		= 0x00,
};

static struct usb_interface_descriptor interface_desc = {
	.bLength		= USB_DT_INTERFACE_SIZE,
	.bDescriptorType	= USB_DT_INTERFACE,
	.bInterfaceNumber	= 0x00,
	.bAlternateSetting	= 0x00,
	.bNumEndpoints		= 0x02,
	.bInterfaceClass	= FASTBOOT_INTERFACE_CLASS,
	.bInterfaceSubClass	= FASTBOOT_INTERFACE_SUB_CLASS,
	.bInterfaceProtocol	= FASTBOOT_INTERFACE_PROTOCOL,
};

static struct usb_descriptor_header *fb_runtime_descs[] = {
	(struct usb_descriptor_header *)&interface_desc,
	(struct usb_descriptor_header *)&fs_ep_in,
	(struct usb_descriptor_header *)&hs_ep_out,
	NULL,
};

/*
 * static strings, in UTF-8
 */
static const char fastboot_name[] = "Android Fastboot";

static struct usb_string fastboot_string_defs[] = {
	[0].s = fastboot_name,
	{  }			/* end of list */
};

static struct usb_gadget_strings stringtab_fastboot = {
	.language	= 0x0409,	/* en-us */
	.strings	= fastboot_string_defs,
};

static struct usb_gadget_strings *fastboot_strings[] = {
	&stringtab_fastboot,
	NULL,
};

static void rx_handler_command(struct usb_ep *ep, struct usb_request *req);
#ifdef CONFIG_FASTBOOT_FLASH_MMC_DEV
static int fastboot_update_zimage(void);
#endif

/*
 * Android style flash utilties */
void fastboot_flash_reset_ptn(void)
{
#ifdef DEBUG
	printf("fastboot flash reset partition..!!");
#endif
	pcount = 0;
}

void fastboot_flash_add_ptn(fastboot_ptentry *ptn)
{
	if (pcount < MAX_PTN) {
		memcpy((ptable + pcount), ptn, sizeof(*ptn));
		pcount++;
	}
}

void fastboot_flash_dump_ptn(void)
{
	unsigned int n;
	for (n = 0; n < pcount; n++) {
		fastboot_ptentry *ptn = ptable + n;
		printf("ptn %d name='%s'", n, ptn->name);
		printf(" start=%d len=%llu\n", ptn->start, ptn->length);
	}
}

static void fastboot_complete(struct usb_ep *ep, struct usb_request *req)
{
	int status = req->status;
	if (!status)
		return;
	printf("status: %d ep '%s' trans: %d\n", status, ep->name, req->actual);
}

static int fastboot_bind(struct usb_configuration *c, struct usb_function *f)
{
	int id;
	struct usb_gadget *gadget = c->cdev->gadget;
	struct f_fastboot *f_fb = func_to_fastboot(f);
	const char *s;

	/* DYNAMIC interface numbers assignments */
	id = usb_interface_id(c, f);
	if (id < 0)
		return id;
	interface_desc.bInterfaceNumber = id;

	id = usb_string_id(c->cdev);
	if (id < 0)
		return id;
	fastboot_string_defs[0].id = id;
	interface_desc.iInterface = id;

	f_fb->in_ep = usb_ep_autoconfig(gadget, &fs_ep_in);
	if (!f_fb->in_ep)
		return -ENODEV;
	f_fb->in_ep->driver_data = c->cdev;

	f_fb->out_ep = usb_ep_autoconfig(gadget, &fs_ep_out);
	if (!f_fb->out_ep)
		return -ENODEV;
	f_fb->out_ep->driver_data = c->cdev;

	hs_ep_out.bEndpointAddress = fs_ep_out.bEndpointAddress;

	s = getenv("serial#");
	if (s)
		g_dnl_set_serialnumber((char *)s);

	return 0;
}

static void fastboot_unbind(struct usb_configuration *c, struct usb_function *f)
{
	memset(fastboot_func, 0, sizeof(*fastboot_func));
}

static void fastboot_disable(struct usb_function *f)
{
	struct f_fastboot *f_fb = func_to_fastboot(f);

	usb_ep_disable(f_fb->out_ep);
	usb_ep_disable(f_fb->in_ep);

	if (f_fb->out_req) {
		free(f_fb->out_req->buf);
		usb_ep_free_request(f_fb->out_ep, f_fb->out_req);
		f_fb->out_req = NULL;
	}
	if (f_fb->in_req) {
		free(f_fb->in_req->buf);
		usb_ep_free_request(f_fb->in_ep, f_fb->in_req);
		f_fb->in_req = NULL;
	}
}

static struct usb_request *fastboot_start_ep(struct usb_ep *ep)
{
	struct usb_request *req;

	req = usb_ep_alloc_request(ep, 0);
	if (!req)
		return NULL;

	req->length = EP_BUFFER_SIZE;
	req->buf = memalign(CONFIG_SYS_CACHELINE_SIZE, EP_BUFFER_SIZE);
	if (!req->buf) {
		usb_ep_free_request(ep, req);
		return NULL;
	}

	memset(req->buf, 0, req->length);
	return req;
}

static int fastboot_set_alt(struct usb_function *f,
			    unsigned interface, unsigned alt)
{
	int ret;
	struct usb_composite_dev *cdev = f->config->cdev;
	struct usb_gadget *gadget = cdev->gadget;
	struct f_fastboot *f_fb = func_to_fastboot(f);

	debug("%s: func: %s intf: %d alt: %d\n",
	      __func__, f->name, interface, alt);

	/* make sure we don't enable the ep twice */
	if (gadget->speed == USB_SPEED_HIGH)
		ret = usb_ep_enable(f_fb->out_ep, &hs_ep_out);
	else
		ret = usb_ep_enable(f_fb->out_ep, &fs_ep_out);
	if (ret) {
		puts("failed to enable out ep\n");
		return ret;
	}

	f_fb->out_req = fastboot_start_ep(f_fb->out_ep);
	if (!f_fb->out_req) {
		puts("failed to alloc out req\n");
		ret = -EINVAL;
		goto err;
	}
	f_fb->out_req->complete = rx_handler_command;

	ret = usb_ep_enable(f_fb->in_ep, &fs_ep_in);
	if (ret) {
		puts("failed to enable in ep\n");
		goto err;
	}

	f_fb->in_req = fastboot_start_ep(f_fb->in_ep);
	if (!f_fb->in_req) {
		puts("failed alloc req in\n");
		ret = -EINVAL;
		goto err;
	}
	f_fb->in_req->complete = fastboot_complete;

	ret = usb_ep_queue(f_fb->out_ep, f_fb->out_req, 0);
	if (ret)
		goto err;

	return 0;
err:
	fastboot_disable(f);
	return ret;
}

static int fastboot_add(struct usb_configuration *c)
{
	struct f_fastboot *f_fb = fastboot_func;
	int status;

	debug("%s: cdev: 0x%p\n", __func__, c->cdev);

	if (!f_fb) {
		f_fb = memalign(CONFIG_SYS_CACHELINE_SIZE, sizeof(*f_fb));
		if (!f_fb)
			return -ENOMEM;

		fastboot_func = f_fb;
		memset(f_fb, 0, sizeof(*f_fb));
	}

	f_fb->usb_function.name = "f_fastboot";
	f_fb->usb_function.hs_descriptors = fb_runtime_descs;
	f_fb->usb_function.bind = fastboot_bind;
	f_fb->usb_function.unbind = fastboot_unbind;
	f_fb->usb_function.set_alt = fastboot_set_alt;
	f_fb->usb_function.disable = fastboot_disable;
	f_fb->usb_function.strings = fastboot_strings;

	status = usb_add_function(c, &f_fb->usb_function);
	if (status) {
		free(f_fb);
		fastboot_func = f_fb;
	}

	return status;
}
DECLARE_GADGET_BIND_CALLBACK(usb_dnl_fastboot, fastboot_add);

static int fastboot_tx_write(const char *buffer, unsigned int buffer_size)
{
	struct usb_request *in_req = fastboot_func->in_req;
	int ret;

	memcpy(in_req->buf, buffer, buffer_size);
	in_req->length = buffer_size;
	ret = usb_ep_queue(fastboot_func->in_ep, in_req, 0);
	if (ret)
		printf("Error %d on queue\n", ret);
	return 0;
}

static int fastboot_tx_write_str(const char *buffer)
{
	return fastboot_tx_write(buffer, strlen(buffer));
}

fastboot_ptentry *fastboot_flash_find_ptn(const char *name)
{
	unsigned int n;

	for (n = 0; n < pcount; n++) {
		/* Make sure a substring is not accepted */
		if (strlen(name) == strlen(ptable[n].name)) {
			if (0 == strcmp(ptable[n].name, name))
				return ptable + n;
		}
	}
	return 0;
}


static void compl_do_reset(struct usb_ep *ep, struct usb_request *req)
{
	do_reset(NULL, 0, 0, NULL);
}

static void cb_reboot(struct usb_ep *ep, struct usb_request *req)
{
	fastboot_func->in_req->complete = compl_do_reset;
	fastboot_tx_write_str("OKAY");
}

static int strcmp_l1(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return -1;
	return strncmp(s1, s2, strlen(s1));
}

static char *get_cpu_type(void)
{
	static char proc_type[8];
	unsigned int value;

	value = readl(CONTROL_STATUS);
	value &= DEVICETYPE_MASK;

	switch (value >> 6) {
	case OMAP_TYPE_EMU:
		strcpy(proc_type, "EMU");
		break;
	case OMAP_TYPE_SEC:
		strcpy(proc_type, "HS");
		break;
	case OMAP_TYPE_GP:
		strcpy(proc_type, "GP");
		break;
	default:
		strcpy(proc_type, "unknown");
		break;
	}

	return proc_type;
}

static void cb_getvar(struct usb_ep *ep, struct usb_request *req)
{
	char *cmd = req->buf;
	char response[RESPONSE_LEN];
	const char *s;
	size_t chars_left;

	strcpy(response, "OKAY");
	chars_left = sizeof(response) - strlen(response) - 1;

	strsep(&cmd, ":");
	if (!cmd) {
		error("missing variable\n");
		fastboot_tx_write_str("FAILmissing var");
		return;
	}

	if (!strcmp_l1("version", cmd)) {
		strncat(response, FASTBOOT_VERSION, chars_left);
	} else if (!strcmp_l1("bootloader-version", cmd)) {
		strncat(response, U_BOOT_VERSION, chars_left);
	} else if (!strcmp_l1("downloadsize", cmd) ||
		!strcmp_l1("max-download-size", cmd)) {
		char str_num[12];

		sprintf(str_num, "0x%08x", CONFIG_USB_FASTBOOT_BUF_SIZE);
		strncat(response, str_num, chars_left);
	} else if (!strcmp_l1("serialno", cmd)) {
		s = getenv("serial#");
		if (s)
			strncat(response, s, chars_left);
		else
			strcpy(response, "FAILValue not set");
	} else if (!strcmp_l1("cpu", cmd)) {
		switch (omap_revision()) {
		case DRA752_ES1_0:
		case DRA752_ES1_1:
		case DRA752_ES2_0:
			strncat(response, "J6", sizeof(response));
			break;
		case DRA722_ES1_0:
			strncat(response, "J6ECO", sizeof(response));
			break;
		default:
			strcpy(response, "FAILValue not set");
		}
	} else if (!strcmp_l1("secure", cmd)) {

		s = get_cpu_type();
		if (s)
			strncat(response, s, sizeof(response));
		else
			strcpy(response, "FAILValue not set");
#ifdef CONFIG_FASTBOOT_FLASH_MMC_DEV
	} else if (!strcmp_l1("userdata_size", cmd)) {
		fb_mmc_get_ptn_size("userdata", response);
#endif
	} else {
		error("unknown variable: %s\n", cmd);
		strcpy(response, "FAILVariable not implemented");
	}
	fastboot_tx_write_str(response);
}

static unsigned int rx_bytes_expected(unsigned maxpacket)
{
	int rx_remain = download_size - download_bytes;
	int rem = 0;
	if (rx_remain < 0)
		return 0;
	if (rx_remain > EP_BUFFER_SIZE)
		return EP_BUFFER_SIZE;
	if (rx_remain < maxpacket) {
		rx_remain = maxpacket;
	} else if (rx_remain % maxpacket != 0) {
		rem = rx_remain % maxpacket;
		rx_remain = rx_remain + (maxpacket - rem);
	}
	return rx_remain;
}

#define BYTES_PER_DOT	0x20000
static void rx_handler_dl_image(struct usb_ep *ep, struct usb_request *req)
{
	char response[RESPONSE_LEN];
	unsigned int transfer_size = download_size - download_bytes;
	const unsigned char *buffer = req->buf;
	unsigned int buffer_size = req->actual;
	unsigned int pre_dot_num, now_dot_num;

	if (req->status != 0) {
		printf("Bad status: %d\n", req->status);
		return;
	}

	if (buffer_size < transfer_size)
		transfer_size = buffer_size;

	memcpy((void *)CONFIG_USB_FASTBOOT_BUF_ADDR + download_bytes,
	       buffer, transfer_size);

	pre_dot_num = download_bytes / BYTES_PER_DOT;
	download_bytes += transfer_size;
	now_dot_num = download_bytes / BYTES_PER_DOT;

	if (pre_dot_num != now_dot_num) {
		putc('.');
		if (!(now_dot_num % 74))
			putc('\n');
	}

	/* Check if transfer is done */
	if (download_bytes >= download_size) {
		/*
		 * Reset global transfer variable, keep download_bytes because
		 * it will be used in the next possible flashing command
		 */
		download_size = 0;
		req->complete = rx_handler_command;
		req->length = EP_BUFFER_SIZE;

		sprintf(response, "OKAY");
		fastboot_tx_write_str(response);

		printf("\ndownloading of %d bytes finished\n", download_bytes);
	} else {
		req->length = rx_bytes_expected(ep->desc->wMaxPacketSize);
		if (req->length < ep->maxpacket)
			req->length = ep->maxpacket;
	}

	req->actual = 0;
	usb_ep_queue(ep, req, 0);
}

static void cb_download(struct usb_ep *ep, struct usb_request *req)
{
	char *cmd = req->buf;
	char response[RESPONSE_LEN];

	strsep(&cmd, ":");
	download_size = simple_strtoul(cmd, NULL, 16);
	download_bytes = 0;

	printf("Starting download of %d bytes\n", download_size);

	if (0 == download_size) {
		sprintf(response, "FAILdata invalid size");
	} else if (download_size > CONFIG_USB_FASTBOOT_BUF_SIZE) {
		download_size = 0;
		sprintf(response, "FAILdata too large");
	} else {
		sprintf(response, "DATA%08x", download_size);
		req->complete = rx_handler_dl_image;
		req->length = rx_bytes_expected(ep->desc->wMaxPacketSize);
		if (req->length < ep->maxpacket)
			req->length = ep->maxpacket;
	}
	fastboot_tx_write_str(response);
}

int do_booti(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);

static void do_bootm_on_complete(struct usb_ep *ep, struct usb_request *req)
{
	char boot_addr_start[12];
	req->complete = NULL;

	sprintf(boot_addr_start, "0x%x", CONFIG_USB_FASTBOOT_BUF_ADDR);
#ifndef CONFIG_SPL_BUILD
	char *booti_args[3] = {"booti", "ram", boot_addr_start};
	do_booti(NULL, 0, 3, booti_args);
#endif

	/* This only happens if image is somehow faulty so we start over */
	do_reset(NULL, 0, 0, NULL);
}

static void cb_boot(struct usb_ep *ep, struct usb_request *req)
{
	fastboot_func->in_req->complete = do_bootm_on_complete;
	fastboot_tx_write_str("OKAY");
}

#ifdef CONFIG_FASTBOOT_FLASH

#ifdef CONFIG_FASTBOOT_FLASH_MMC_DEV
static u32 fastboot_get_boot_ptn(struct andr_img_hdr *hdr, char *response,
	                                   block_dev_desc_t *dev_desc)
{
	u32 hdr_sectors = 0;
	u32 sector_size;
	int status = 0;
	strcpy(response, "OKAY");
	disk_partition_t info;

	status = get_partition_info_efi_by_name(dev_desc, "boot", &info);
	if (status) {
		strcpy(response, "FAILCannot find boot partition");
		goto out;
	}

	/* Read the boot image header */
	sector_size = info.blksz;
	hdr_sectors = (sizeof(struct andr_img_hdr)/sector_size) + 1;
	status = dev_desc->block_read(dev_desc->dev, info.start,
				      hdr_sectors, (void *)hdr);

	if (status < 0) {
		strcpy(response, "FAILCannot read hdr from boot partition");
		goto out;
	}
	if (android_image_check_header(hdr) != 0) {
		printf("bad boot image magic\n");
		strcpy(response, "FAILBoot partition not initialized");
		goto out;
	}

	return hdr_sectors;

out:
	strcpy(response, "INFO");
	fastboot_tx_write_str(response);

	return -1;
}

#define CEIL(a, b) (((a) / (b)) + ((a % b) > 0 ? 1 : 0))

static int fastboot_update_zimage()
{
	struct andr_img_hdr *hdr = NULL;
	u8 *ramdisk_buffer;
	u32 ramdisk_sector_start, ramdisk_sectors;
	u32 kernel_sector_start, kernel_sectors;
	u32 hdr_sectors = 0;
	u32 sectors_per_page = 0;
	int ret = 0;
	block_dev_desc_t *dev_desc;
	disk_partition_t info;
	char response[RESPONSE_LEN];
	u32 addr = CONFIG_USB_FASTBOOT_BUF_ADDR;

	strcpy(response, "OKAY");
	printf("Flashing zImage...%d bytes\n", download_bytes);

	dev_desc = get_dev("mmc", CONFIG_FASTBOOT_FLASH_MMC_DEV);
	if (!dev_desc || dev_desc->type == DEV_TYPE_UNKNOWN) {
		sprintf(response + strlen(response),
			"FAILINVALID mmc device");
		ret = -1;
		goto out;
	}

	addr += CEIL(download_bytes, 0x1000) * 0x1000;
	hdr = (struct andr_img_hdr *) addr;

	hdr_sectors = fastboot_get_boot_ptn(hdr, response, dev_desc);
	if (hdr_sectors <= 0) {
		sprintf(response + strlen(response),
			"FAILINVALID number of boot sectors %d", hdr_sectors);
		ret = -1;
		goto out;
	}
	ret = get_partition_info_efi_by_name(dev_desc, "boot", &info);
	if (ret) {
		strcpy(response, "FAILCannot find boot partition");
		ret = -1;
		goto out;
	}

	/* Extract ramdisk location and read it into local buffer */
	sectors_per_page = hdr->page_size / info.blksz;
	ramdisk_sector_start = info.start + sectors_per_page;
	ramdisk_sector_start += CEIL(hdr->kernel_size, hdr->page_size)*
				     sectors_per_page;
	ramdisk_sectors = CEIL(hdr->ramdisk_size, hdr->page_size)*
			       sectors_per_page;

	ramdisk_buffer = (u8 *)hdr;
	ramdisk_buffer += (hdr_sectors * info.blksz);
	ret = dev_desc->block_read(dev_desc->dev, ramdisk_sector_start,
				   ramdisk_sectors, ramdisk_buffer);
	if (ret < 0) {
		sprintf(response, "FAILCannot read ramdisk from boot "
			"partition");
		ret = -1;
		goto out;
	}

	/* Change the boot img hdr */
	hdr->kernel_size = download_bytes;
	ret = dev_desc->block_write(dev_desc->dev, info.start,
				    hdr_sectors, (void *)hdr);
	if (ret < 0) {
		sprintf(response, "FAILCannot writeback boot img hdr");
		ret = -1;
		goto out;
	}

	/* Write the new downloaded kernel*/
	kernel_sector_start = info.start + sectors_per_page;
	kernel_sectors = CEIL(hdr->kernel_size, hdr->page_size)*
			      sectors_per_page;
	ret = dev_desc->block_write(dev_desc->dev, kernel_sector_start,
				    kernel_sectors,
				    (const void *)CONFIG_USB_FASTBOOT_BUF_ADDR);
	if (ret < 0) {
		sprintf(response, "FAILCannot write new kernel");
		ret = -1;
		goto out;
	}

	/* Write the saved Ramdisk back */
	ramdisk_sector_start = info.start + sectors_per_page;
	ramdisk_sector_start += CEIL(hdr->kernel_size, hdr->page_size)*
				     sectors_per_page;
	ret = dev_desc->block_write(dev_desc->dev, ramdisk_sector_start,
				    ramdisk_sectors, ramdisk_buffer);
	if (ret < 0) {
		sprintf(response, "FAILCannot write back original ramdisk");
		ret = -1;
		goto out;
	}
	fastboot_tx_write_str(response);
	return 0;

out:
	fastboot_tx_write_str(response);
	return ret;
}
#endif

#ifdef CONFIG_SPL_SPI_SUPPORT
int boot_from_spi = 0;
extern int do_spi_flash(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
#endif

static void cb_flash(struct usb_ep *ep, struct usb_request *req)
{
	char *cmd = req->buf;
	char response[RESPONSE_LEN];
#ifdef CONFIG_SPL_SPI_SUPPORT
	char source[32];
	int status = 0;
	char *sf_probe[3] = {"sf", "probe", "0"};
	char *sf_write_xloader[5] = {"sf", "write", NULL, "0", "20000"};
	char *sf_update_xloader[5] = {"sf", "update", NULL, "0", "20000"};
	char *sf_write_bootloader[5] = {"sf", "write", NULL, "80000", "80000"};
	char *sf_update_bootloader[5] = {"sf", "update", NULL, "80000", "80000"};
#endif

	strsep(&cmd, ":");
	if (!cmd) {
		error("missing partition name\n");
		fastboot_tx_write_str("FAILmissing partition name");
		return;
	}

	strcpy(response, "FAILno flash device defined");
#ifdef CONFIG_SPL_SPI_SUPPORT
	/*Check if this is for xloader or bootloader. Also, check if we have to flash to SPI*/
	if (strcmp(cmd, "xloader") == 0 && boot_from_spi) {
		printf("Flashing %s to SPI\n", cmd);
		status = do_spi_flash(NULL, 0, 3, sf_probe);
		if (status) {
			fastboot_tx_write_str("FAIL:Could not probe SPI");
			return;
		}
		sf_write_xloader[2] = source;
		sf_update_xloader[2] = source;
		sprintf(source, "0x%x", (unsigned int)CONFIG_USB_FASTBOOT_BUF_ADDR);

		printf("Updating X-LOADER to SPI\n");
		status = do_spi_flash(NULL, 0, 5, sf_update_xloader);
		if(status) {
			fastboot_tx_write_str("FAIL:Could not update xloader to SPI");
			return;
		}

		printf("Writing X-LOADER to SPI\n");
		status = do_spi_flash(NULL, 0, 5, sf_write_xloader);
		if (status) {
			fastboot_tx_write_str("FAIL:Could not write xloader to SPI");
			return;
		}
		printf("Writing xloader DONE\n");
		fastboot_tx_write_str("OKAY");
		return;
	}
	if (strcmp(cmd, "bootloader") == 0 && boot_from_spi) {
		printf("Flashing %s to SPI\n", cmd);
		status = do_spi_flash(NULL, 0, 3, sf_probe);
		if (status) {
			fastboot_tx_write_str("FAIL:Could not probe SPI");
			return;
		}
		sf_write_bootloader[2] = source;
		sf_update_bootloader[2] = source;
		sprintf(source, "0x%x", (unsigned int)CONFIG_USB_FASTBOOT_BUF_ADDR);
		printf("Updating bootloader to SPI\n");
		status = do_spi_flash(NULL, 0, 5, sf_update_bootloader);
		if (status) {
			fastboot_tx_write_str("FAIL:Could not update bootloader to SPI");
			return;
		}
		printf("Writing bootloader to SPI\n");
		status = do_spi_flash(NULL, 0, 5, sf_write_bootloader);
		if (status) {
			fastboot_tx_write_str("FAIL:Could not write bootloader to SPI");
			return;
		}
		printf("Writing bootloader DONE\n");
		fastboot_tx_write_str("OKAY");
		return;
	}
#endif
#ifdef CONFIG_FASTBOOT_FLASH_MMC_DEV
	if (!strcmp(cmd, "zImage") || !strcmp(cmd, "zimage")) {
		fastboot_update_zimage();
		return;
	}

	fb_mmc_flash_write(cmd, (void *)CONFIG_USB_FASTBOOT_BUF_ADDR,
			   download_bytes, response);
#endif
	fastboot_tx_write_str(response);
}

static void cb_erase(struct usb_ep *ep, struct usb_request *req)
{
	char *cmd = req->buf;
	char response[RESPONSE_LEN];

	strsep(&cmd, ":");
	if (!cmd) {
		error("missing partition name\n");
		fastboot_tx_write_str("FAILmissing partition name");
		return;
        }

	strcpy(response, "FAILno flash device defined");

#ifdef CONFIG_FASTBOOT_FLASH_MMC_DEV
	fb_mmc_erase(cmd, response);
#endif
	fastboot_tx_write_str(response);
}
#endif

int fastboot_oem(const char *cmd)
{
#ifdef CONFIG_FASTBOOT_FLASH_MMC_DEV
	if (!strcmp(cmd, "format"))
		return do_format();
#endif
	return -1;
}

static void cb_oem(struct usb_ep *ep, struct usb_request *req)
{
	char *cmd = req->buf;
#ifdef CONFIG_SPL_SPI_SUPPORT
	char *sf_erase[4] = {"sf", "erase", "0", "20000"};
	int status;
	char *sf_probe[3] = {"sf", "probe", "0"};
	if (strncmp(req->buf + 4, "spi", 3) == 0) {
		boot_from_spi = 1;
		status = do_spi_flash(NULL, 0, 3, sf_probe);
		if (status) {
			fastboot_tx_write_str("FAIL:Could not probe SPI");
			return;
		}
		status = do_spi_flash(NULL, 0, 4, sf_erase);
		if (status) {
			fastboot_tx_write_str("FAIL:Could not erase SPI");
			return;
		}
		fastboot_tx_write_str("OKAY");
		return;
	}else if (strncmp(req->buf + 4, "mmc", 3) == 0) {
		boot_from_spi = 0;
		fastboot_tx_write_str("OKAY");
		return;
	}
#endif

	if (fastboot_oem(cmd + 4) < 0) {
		fastboot_tx_write_str("FAIL:Unable to create partitions");
	} else {
		fastboot_tx_write_str("OKAY");
	}
}

static void cb_reboot_bootloader(struct usb_ep *ep, struct usb_request *req)
{
	fastboot_tx_write_str("OKAY");
	fastboot_reboot_bootloader();
}

struct cmd_dispatch_info {
	char *cmd;
	void (*cb)(struct usb_ep *ep, struct usb_request *req);
};

static const struct cmd_dispatch_info cmd_dispatch_info[] = {
	{
		.cmd = "reboot-bootloader",
		.cb = cb_reboot_bootloader,
	}, {
		.cmd = "reboot",
		.cb = cb_reboot,
	}, {
		.cmd = "getvar:",
		.cb = cb_getvar,
	}, {
		.cmd = "download:",
		.cb = cb_download,
	}, {
		.cmd = "boot",
		.cb = cb_boot,
	},
#ifdef CONFIG_FASTBOOT_FLASH
	{
		.cmd = "flash",
		.cb = cb_flash,
	}, {
		.cmd = "erase",
		.cb = cb_erase,
	},
#endif
	{
		.cmd = "oem",
		.cb = cb_oem,
	},
};

static void rx_handler_command(struct usb_ep *ep, struct usb_request *req)
{
	char *cmdbuf = req->buf;
	void (*func_cb)(struct usb_ep *ep, struct usb_request *req) = NULL;
	int i;

	for (i = 0; i < ARRAY_SIZE(cmd_dispatch_info); i++) {
		if (!strcmp_l1(cmd_dispatch_info[i].cmd, cmdbuf)) {
			func_cb = cmd_dispatch_info[i].cb;
			break;
		}
	}

	if (!func_cb) {
		error("unknown command: %s\n", cmdbuf);
		fastboot_tx_write_str("FAILunknown command");
	} else {
		if (req->actual < req->length) {
			u8 *buf = (u8 *)req->buf;
			buf[req->actual] = 0;
			func_cb(ep, req);
		} else {
			error("buffer overflow\n");
			fastboot_tx_write_str("FAILbuffer overflow");
		}
	}

	if (req->status == 0) {
		*cmdbuf = '\0';
		req->actual = 0;
		usb_ep_queue(ep, req, 0);
	}
}

#ifdef CONFIG_FASTBOOT_FLASH_MMC_DEV
int board_partition_init(void)
{
	board_mmc_fbtptn_init();
	return 1;
}
#endif
