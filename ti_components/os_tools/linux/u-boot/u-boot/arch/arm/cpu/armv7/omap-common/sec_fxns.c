/*
 *
 * Common security functions that rely on OMAP ROM secure world code
 *
 * (C) Copyright 2015
 * Texas Instruments, <www.ti.com>
 *
 * Daniel Allred    <d-allred@ti.com>
 *
 * SPDX-License-Identifier: GPL-2.0+
 */


/*------------------------------ Include Files -------------------------------*/

#include <common.h>
#include <stdarg.h>

#include <asm/arch/sys_proto.h>
#include <asm/omap_common.h>


/*----------------------------- Extern Declarations --------------------------*/

extern int SEC_ENTRY_Pub2SecBridgeEntry(uint32_t appl_id, uint32_t proc_ID, uint32_t flag, uint32_t *params);


/*------------------------------- Local Macros -------------------------------*/

#define SIGNATURE_LENGTH				(0x118)

#if defined(CONFIG_OMAP54XX)
/* API Index for OMAP5, DRA7xx */
#define API_HAL_KM_VERIFYCERTIFICATESIGNATURE_INDEX     (0x0000000E)
#else
/* API Index for OMAP4, J5, J5Eco, Aegis, Subarctic */
#define API_HAL_KM_VERIFYCERTIFICATESIGNATURE_INDEX     (0x0000000C)
#endif


/*-------------------------- Local Type Definitions --------------------------*/


/*----------------------- Local Variable Declarations ------------------------*/

static uint32_t LOCAL_smcParams[5] __aligned(ARCH_DMA_MINALIGN);


/*---------------------- Global Variable Declarations ------------------------*/


/*------------------------ Local Function Definitions ------------------------*/

static void LOCAL_prepParams(uint32_t numParams, ...)
{
	int i;
	va_list ap;
	va_start(ap, numParams);

	LOCAL_smcParams[0] = numParams;
	for (i=0; i<numParams; i++)	{
		LOCAL_smcParams[i+1] = va_arg(ap, uint32_t);
	}

	va_end(ap);

#if !defined(CONFIG_SPL_BOOT)
#if !defined(CONFIG_SYS_DCACHE_OFF)
	flush_dcache_range(
		(unsigned int) &LOCAL_smcParams[0],
		((unsigned int)&LOCAL_smcParams[0]) + roundup(sizeof(LOCAL_smcParams), ARCH_DMA_MINALIGN));
#endif
#endif
}

/*----------------------- Global Function Definitions ------------------------*/

int secure_boot_verify_image(const void *image, size_t size)
{
	int result = 1;
	uint32_t load_addr, sig_addr;

#if !defined(CONFIG_SPL_BOOT)
#if !defined(CONFIG_SYS_DCACHE_OFF)
	/* Perform cache writeback on input buffer */
	flush_dcache_range(
		(unsigned int) image,
		((unsigned int)image) + roundup(size, ARCH_DMA_MINALIGN));
#endif
#endif

	load_addr = (uint32_t)image;
	size -= SIGNATURE_LENGTH;   /* Subtract out the signature size */
	sig_addr = load_addr + size;

	/* Check if image load address is 32-bit aligned */
	if (0 != (0x3 & load_addr)) {
		puts("Image is not 4-byte aligned.\n");
		result = 1;
		goto auth_exit;
	}

	/* Image size also should be multiple of 4 */
	if (0 != (0x3 & size)) {
		puts("Image size is not 4-byte aligned.\n");
		result = 1;
		goto auth_exit;
	}

	/*
	 * Call ROM HAL API to verify certificate signature.
	 * This is kind of an abuse of the API as the image
	 * is not a certificate, but rather just a signed data blob.
	 */
	debug("%s: load_addr = %x, size = %x, sig_addr = %x\n", __func__,
		load_addr, size, sig_addr);

	LOCAL_prepParams(4, load_addr, size,
        sig_addr, 0xFFFFFFFF);
	result = SEC_ENTRY_Pub2SecBridgeEntry(
		API_HAL_KM_VERIFYCERTIFICATESIGNATURE_INDEX,
		0, 0, LOCAL_smcParams);
auth_exit:
		if (result != 0) {
			puts("Authentication failed!\n");
			printf("Return Value = %08X\n", result);
			hang();
		}

	return result;
}

/*------------------------------- End Of File --------------------------------*/
