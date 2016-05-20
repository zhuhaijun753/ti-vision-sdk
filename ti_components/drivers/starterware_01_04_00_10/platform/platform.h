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

#include "soc.h"
#include "stdint.h"

/****************************************************************************
**                       MACRO DEFINITIONS
****************************************************************************/

#ifndef TDA3XX_FAMILY_BUILD
#define MMCSD_BASE                       (SOC_MMC1_BASE)
#else
#define MMCSD_BASE                       (SOC_MMC4_BASE)
#endif
#define MMCSD_DMA_BASE                   (SOC_EDMA_TC0_BASE)

/* Todo : please cross check before use */
#define MMCSD_IN_FREQ                    (96000000) /* 96MHz */
#define MMCSD_INIT_FREQ                  (400000)   /* 400kHz */

#define MMCSD_BLK_SIZE                   (512)
#define MMCSD_OCR                        (SD_OCR_VDD_3P0_3P1 | \
                                          SD_OCR_VDD_3P1_3P2)

/*HSMMCSD DMA EVENT SOURCE NUMBER*/
#ifndef TDA3XX_FAMILY_BUILD
#define EDMA_DREQ_MMC1_TX (60U)
#define EDMA_DREQ_MMC1_RX (61U)
#define EDMA_DREQ_MMC2_TX (46U)
#define EDMA_DREQ_MMC2_RX (47U)
#define EDMA_DREQ_MMC3_TX (76U)
#define EDMA_DREQ_MMC3_RX (77U)
#define EDMA_DREQ_MMC4_TX (56U)
#define EDMA_DREQ_MMC4_RX (57U)
#else
#define EDMA_DREQ_MMC4_TX (60U)
#define EDMA_DREQ_MMC4_RX (61U)

#endif

/*Selected EDMA CH for HSMMCSD RX Event*/
#define EDMA_MMCSD_CH   (61U)

/*SBL MAGIC STRING PATTERN*/
#define SBL_REGRESSION_MAGIC_STRING_P1 (0xAAAA5555U)
#define SBL_REGRESSION_MAGIC_STRING_P2 (0x55335533U)
#define SBL_REGRESSION_MAGIC_STRING_P3 (0xBBFFBBFFU)
#define SBL_REGRESSION_MAGIC_STRING_P4 (0x11001100U)

/*DV - DIE ID Registers*/
#define DV_DIE_ID0  (0x4ae0c200)
#define DV_DIE_ID1  (0x4ae0c208)
#define DV_DIE_ID2  (0x4ae0c20C)
#define DV_DIE_ID3  (0x4ae0c210)

/* Todo : please cross check before use */
/*Pad config constant values */
#define PULLUDENABLE_ENABLE         (0U)
#define PULLUDENABLE_DISABLE        (1U)
#define PULLTYPESELECT_PULL_UP      (1U)
#define PULLTYPESELECT_PULL_DOWN    (0U)
#define INPUTENABLE_ENABLE          (1U)
#define INPUTENABLE_DISABLE         (0U)
#define SLEWCONTROL_FAST_SLEW       (0U)
#define SLEWCONTROL_SLOW_SLEW       (1U)
#define WAKEUPENABLE_ENABLE         (1U)
#define WAKEUPENABLE_DISABLE        (0U)

/*On Cortex M4  0x43300000 is not addressable range -
 * Map the EDMA TPCC base address to a virtual address*/
/*Application required to configure AMMU to map Virtual address to L3 physical
 *address*/
#ifdef BUILD_M4
#define SOC_EDMA_TPCC_BASE      (0x63300000U)
#endif

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/*Data type to define the pad configuration*/
typedef struct {
    uint32_t pin_num;
    uint8_t  muxmode;
    uint8_t  pullud_enable;
    uint8_t  pull_typeselect;
    uint8_t  input_enable;
    uint8_t  slewcontrol;
    uint8_t  wakeup_enable;
}pad_config_t;

/* ============================================================================
 * LOCAL TYPES AND DEFINITIONS
 * =============================================================================
 */

/*Regression Test static table*/

/*-------------------------------
 * Test Result
 * -------------------------------
 * SBL Regression Test Magic string
 * -------------------------------
 * Test number track register
 * -------------------------------*/
typedef struct
{
    uint32_t sbl_regression_tc_result_reg;
    uint32_t sbl_regression_tc_pass_reg;
    uint32_t sbl_regression_magic_string_r1;
    uint32_t sbl_regression_magic_string_r2;
    uint32_t sbl_regression_magic_string_r3;
    uint32_t sbl_regression_magic_string_r4;
    uint32_t sbl_regression_tc_track_reg;
    uint32_t sbl_regression_tc_fail_reg;
}sbl_regression_log_bfr_t;

typedef enum
{
    REGRESSIONTEST_PASS         = 0x50415353,
    REGRESSIONTEST_FAIL         = 0x4641494C,
    REGRESSIONTEST_TIMEOUT      = 0x50415858,
    REGRESSIONTEST_LASTTESTCASE = 0x4C415354
}regressiontest_result_t;

/**
 * \brief  Enum to select the Silicon Package Type of SoC.
 */
typedef enum platformSiliconPackageType
{
    PLATFORM_SILICON_PACKAGE_TYPE_UNKNOWN = 0,
    /**< Silicon Package type is Invalid */
    PLATFORM_SILICON_PACKAGE_TYPE_12X12 = 1,
    /**< Silicon Package type is 12x12 */
    PLATFORM_SILICON_PACKAGE_TYPE_15X15 = 2,
    /**< Silicon Package type is 15x15 */
    PLATFORM_SILICON_PACKAGE_TYPE_17X17 = 3,
    /**< Silicon Package type is 17x17 */
    PLATFORM_SILICON_PACKAGE_TYPE_23X23 = 4
                                          /**< Silicon Package type is 23x23 */
} platformSiliconPackageType_t;

/***********************************************************************
**                     EXTERNAL FUNCTION PROTOTYPES
***********************************************************************/
extern sbl_regression_log_bfr_t sbl_regression_log_bfr;

/*****************************************************************************
**                     API FUNCTION PROTOTYPES
*****************************************************************************/

void PlatformI2C1SetPinMux(void);
void PlatformI2C4SetPinMux(void);

void PlatformGPIOClockEnable(void);
void PlatformGPMCClockEnable(void);
void PlatformGPMCPinCtrl(void);
void PlatformGPMCSetPinMux(void);

void PlatformMCSPI1PrcmEnable(void);
void PlatformMCSPI1SetPinMux(void);
void PlatformMCSPI2PrcmEnable(void);
void PlatformMCSPI2SetPinMux(void);
void PlatformMCASP3SetPinMux(void);
void PlatformMCASP3PrcmEnable(void);
void PlatformEDMAWkupDepEnable(void);

#ifdef REGRESSION_MODE
void regressiontest_log_result(regressiontest_result_t arg);
#endif

#ifndef TDA3XX_FAMILY_BUILD
void PlatformPCIESS1ClockEnable(void);

void PlatformPCIESS1PllConfig(void);

void PlatformPCIESS1Reset(void);

void PlatformPCIESS1CtrlConfig(void);

void PlatformPCIESS1PhyConfig(void);
#endif

uint32_t PlatformGetSiliconRev(void);

uint32_t PlatformGetFtRev(void);

int32_t PlatformUARTSetPinMux(UART_INST_t num);
void PlatformQSPISetPinMux(void);
void PlatformUnlockMMR(void);
void PlatformLockMMR(void);
void PlatformMMC1SetPinMux(void);
void PlatformGPMCSetPinMuxAddrLines(void);
void PlatformI2C2SetPinMux(void);
void PlatformVIN1SetPinMux(void);
void PlatformVIN2SetPinMux(void);
void PlatformLCDSetPinMux(void);
void PlatformRGMIISetPinMux(void);
void PlatformRGMII0SetPinMux(void);
void PlatformRGMII1SetPinMux(void);
void PlatformUART1SetPinMux(void);
void PlatformUART3SetPinMux(void);
void PlatformUART4SetPinMux(void);
void PlatformMMCSD1SetPinMux(void);
void PlatformMMCSD3SetPinMux(void);
void PlatformMMCSD4SetPinMux(void);
int32_t PlatformMMCSDSetPinMux(MMC_INST_t num);
void PlatformUART2SetPinMux(void);
void PlatformUartConsoleSetPinMux(void);
void PlatformGPIOInputOutputSetPinMux(void);
void PlatformGPIO1SetPinMux(void);
void PlatformGPIO4SetPinMux(void);
uint32_t PlatformGetQspiMode(void);
void PlatformDCAN1PrcmEnable(void);
void PlatformDCAN2PrcmEnable(void);
void PlatformDcanMessageRamInit(uint32_t instance);
void PlatformDCAN2SetPinMux(void);
void PlatformDCAN1SetPinMux(void);
void PlatformUnlockControlIODSS(void);
void PlatformI2C3SetPinMux(void);
void PlatformI2C5SetPinMux(void);
void PlatformTDA2xxMCSetPinMux(void);
void PlatformMMCSD2SetPinMux(void);
void PlatformDCAN1RXSetPinMux(void);
void PlatformDCAN2RXSetPinMux(void);
int32_t PlatformDcanClkConfig(uint32_t instance);

/**
 * \brief   This function gets the silicon package type of the SoC.
 *
 * \param   None
 *
 * \return  packageType   Refer enum #platformSiliconPackageType_t for details.
 */
uint32_t PlatformGetSiliconPackageType(void);

/* ========================================================================== */
/*                         Deprecated Functions                               */
/* ========================================================================== */
void UART_PAD_CONFIG(void);
void cntrl_core_qspi_pad_config(void);
void HAL_CTRL_UnlockMMR(void);
void I2C1_Pin_Mux(void);
void I2C2_Pin_Mux(void);
void I2C4_Pin_Mux(void);
uint32_t CTRLGetFtRev(void);
uint32_t CTRLGetSiliconRev(void);
void EDMAModuleClkConfig(void);
void GPMC_clock_enable(void);
void GPIO_clock_enable(void);
void MCSPI1_pad_mux_config(void);
void GPMC_pin_Ctrl(void);
void cntrl_core_gpmc_pad_config(void);
void cntrl_core_mmc1_pad_config(void);
void cntrl_core_gpmc_pad_config_addr_lines(void);
void cntrl_core_i2c2_pad_config(void);
void cntrl_core_vin1_pad_config(void);
void cntrl_core_vin2_pad_config(void);
void cntrl_core_lcd_pad_config(void);
void cntrl_core_rgmii_pad_config(void);
void cntrl_core_uart1_pad_config(void);
int32_t Uart_Pin_Mux(UART_INST_t num);
void Uart1_Pin_Mux(void);
void Uart3_Pin_Mux(void);
void Uart4_Pin_Mux(void);
void MMCSD1_Pin_Mux(void);
void MMCSD3_Pin_Mux(void);
void MMCSD4_Pin_Mux(void);
int32_t MMCSD_Pin_Mux(MMC_INST_t num);
void MCASP3_pad_mux_config(void);
void MCSPI2_pad_mux_config(void);
void MCSPI1_prcm_enable(void);
void MCSPI2_prcm_enable(void);
void PlatformGPMCConfig(void);
void GPMC_config(void);
void PCIESS1ClockEnable(void);
void PCIESS1PllConfig(void);
void PCIESS1Reset(void);
void PCIESS1CtrlConfig(void);
void MCASP3_prcm_enable(void);
void PlatformMCASP1SetPinMux(void);
void PlatformMCASP1PrcmEnable(void);
void HAL_CTRL_Control_IO_DSS(void);
void HAL_CTRL_ConfigurePadsQspi(void);
void PCIESS1PhyConfig(void);

#ifdef __cplusplus
}
#endif
#endif
