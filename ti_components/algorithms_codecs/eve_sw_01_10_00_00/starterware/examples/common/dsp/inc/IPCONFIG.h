/* =============================================================================
 *
 *            TEXAS INSTRUMENTS INCORPORATED PROPRIETARY INFORMATION
 *
 *  Property of Texas Instruments
 *  For Unrestricted Internal Use Only 
 *  Unauthorized reproduction and/or distribution is strictly
 *  prohibited.
 *  This product is protected under copyright law and trade secret law  
 *  as an unpublished work.
 *  Created 2006, (C) Copyright 2006 Texas Instruments.  All rights 
 *  reserved.
 */
/**
 *  @Component   ATTILA
 *  @Filename    IPCONFIG.h
 *  @Description This header defines versions of the HW IP in order to handle
 *               the sharig of the same driver library code by multiple versions
 *               of the same IP.
 *               More details here: 
 * http://www.tif.ti.com/omap_validation/projects/sw_common/TechnicalMemo/TechnicalMemo_ProjectIfdefsInSharedLibs.html  
 *
 *//*======================================================================== */

#ifndef __IPCONFIG_H
#define __IPCONFIG_H

/* =============================================================================
 * INCLUDE FILES (only if necessary)
 * =============================================================================
 */

#ifdef __cplusplus
extern 
{
#endif

/* =============================================================================
 * EXPORTED DEFINITIONS
 * =============================================================================
 */

/* Define the versions here, keep following rules
 *  - use IPCONFIG prefix
 *  - use IP abbreviation for easy identification (match to the driver library)
 *  - use hexadecimal representation (not mandatory - gives only higher range)
 *  - keep 8digits
 * Example:
 * #define IPCONFIG_GPMC 0x0000123  -- GPMC version 1.2.3 
 * #define IPCONFIG_GPMC 0x000012A  -- GPMC version 1.2.10 
 */
#ifdef CORTEXA8
 #define ICONT1_MMR__IRQ IVAHD0__ICONT1_MMR__IRQ  /* have defined this variable inside IPCONFIG.h */
#endif 

#define IPCONFIG_DMA4 0x00000500 /* DMA4 version 5.00 */
#define IPCONFIG_GPMC 0x00000500 /* GPMC version 5.00 */
#define IPCONFIG_SDRC 0x00000400 /* SDRC version 4.00 */
#define IPCONFIG_LCD  0x00000500 /* LCD  arch v5 */
#define IPCONFIG_PDMA	0x20070614 /* Generation time: Jun 14 2007 21:01:36 */

/* 
 * define other common constants 
 */

/* Number of IRQ lines in interrupt controller - ARM9 & C55 */
#define IPCONFIG_INTCTL_IRQ_LINES   96

/* Using INTCPS for interrupt controller for ARM9 & C55 */
#define IPCONFIG_INTCPS

/* Number of Mailboxes */
#define IPCONFIG_MBOX_NUMBER        8


/* New PRCM API */
#define IPCONFIG_PRCM_API           2 /* 2nd version of the PRCM API */

/* Define various Power Management Companion chips
 * Triton (EC, ULC, 2)
 * TEJAS
 */
#define IPCONFIG_TRITON_EC    0x00000110
#define IPCONFIG_TRITON_ULC   0x00000120
#define IPCONFIG_TRITON_2     0x00000200
#define IPCONFIG_TEJAS        0x00000300
/* Define Usage of PRCM HAL library for cores */
#ifdef CORTEXA8
    #define IPCONFIG_USE_PRCM_HAL   2
#endif

/* Define PMC chip used with this project */
#define IPCONFIG_PMC          IPCONFIG_TEJAS

/* Define SPI Revision ID */
#define IPCONFIG_SPI	0x21
/* Define GPIO */
#define IPCONFIG_GPIO  

/* Define VLYNQ */
#define IPCONFIG_VLYNQ  0x10

/* Define MCASP */
#define IPCONFIG_MCASP  0x11

/* Define WDT */
#define IPCONFIG_WDT  0x12

#define IPCONFIG_MSI2C  0x000003d0

/* Define DMTIMER ID */
#define IPCONFIG_DMTIMER 0x7
/* Define SYNCTIMER32K */
#define IPCONFIG_SYNCTIMER32K
/* Specman synchronization GPIO port and lines */
#define IPCONFIG_ESYNC_USE_GPIO
#define IPCONFIG_ESYNC_SYNC_PORT         GPIO0
#define IPCONFIG_ESYNC_SYNC_PORT_PRCM    prcm_gpio0
#define IPCONFIG_ESYNC_READY_PORT        GPIO0
#define IPCONFIG_ESYNC_READY_PORT_PRCM   prcm_gpio0

#define IPCONFIG_ESYNC_SYNC_LINE        6 
#define IPCONFIG_ESYNC_READY_LINE       7

#define IPCONFIG_RESEXT_SWVER           0   
#ifdef __cplusplus
}
#endif
#endif	/* __IPCONFIG_H */
/* EOF */

