/* ======================================================================
 *   Copyright (C) 2013 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */
/*
 *  \file   platform.h
 *
 *  \brief  platform API declarations.
 *
 *   This file contains the API prototypes for platform specific functions
 */

#ifndef PLATFORM_H
#define PLATFORM_H

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
**                       MACRO DEFINITIONS
****************************************************************************/

#define MMCSD_BASE               (SOC_MMCHS_1_REGS)
#define MMCSD_DMA_BASE           (SOC_EDMA30TC_0_REGS)

#define MMCSD_IN_FREQ            96000000 /* 96MHz */
#define MMCSD_INIT_FREQ          400000   /* 400kHz */

#define MMCSD_BLK_SIZE           512
#define MMCSD_OCR                (SD_OCR_VDD_3P0_3P1 | SD_OCR_VDD_3P1_3P2)

/*HSMMCSD0 DMA EVENT SOURCE NUMBER*/
#define EDMA_DREQ_MMC1_TX (24U)
#define EDMA_DREQ_MMC1_RX (25U)

/*Selected EDMA CH for HSMMCSD RX Event*/
#define EDMA_MMCSD_CH (25U)

/*****************************************************************************
**                     API FUNCTION PROTOTYPES
*****************************************************************************/
void PlatformMCASP2SetPinMux(void);
void PlatformMCASP5SetPinMux(void);
void PlatformMCASP2PrcmEnable(void);
void PlatformMCSPI0SetPinMux(void);
void PlatformMCSPI1SetPinMux(void);
void PlatformEDMAPrcmEnable(void);
void PlatformUARTClockEnable(void);
void PlatformUARTSetPinMux(void);
void PlatformI2CClockEnable(void);
void PlatformI2CSetPinMux(void);
void PlatformXBARIntMux(uint32_t xbarIntNum, uint32_t XBARNum);
void PlatformGPMCPinCtrl(void);
void PlatformGPIOClockEnable(void);
void PlatformGPMCClockEnable(void);
void PlatformMCSPI0PrcmEnable(void);
void PlatformMCSPI1PrcmEnable(void);
void PlatformUartConsoleSetPinMux(void);

/* ========================================================================== */
/*                         Deprecated Functions                               */
/* ========================================================================== */
void GPMCClockEnable(void);
void GPIO_clock_enable(void);
void MCASP2_pad_mux_config(void);
void MCASP5_pad_mux_config(void);
void MCSPI0_pad_mux_config(void);
void MCSPI1_pad_mux_config(void);
void MCASP2_prcm_enable(void);
void MCASP_3_4_5_prcm_enable(void);
void MCSPI0_1_2_3_prcm_enable(void);
void EDMA_prcm_enable(void);
void UART_clock_enable(void);
void UART_pad_mux_config(void);
void I2C_pad_mux_config(void);
void I2C_clock_enable(void);
void XBAR_Int_Mux(uint32_t xbarIntNum, uint32_t XBARNum);
void GPMC_pin_Ctrl(void);
void GPMC_clock_enable(void);

#ifdef __cplusplus
}
#endif
#endif

