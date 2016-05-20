/******************************************************************************
 *                                                                            *
 * Copyright (c) 2012 Texas Instruments Incorporated - http://www.ti.com/     *
 *                                                                            *
 * All rights reserved. Property of Texas Instruments Incorporated.           *
 * Restricted rights to use, duplicate or disclose this code are              *
 * granted through contract.                                                  *
 *                                                                            *
 * The program may not be used without the written permission                 *
 * of Texas Instruments Incorporated or against the terms and conditions      *
 * stipulated in the agreement under which this program has been              *
 * supplied.                                                                  *
 *                                                                            *
 *****************************************************************************/

#ifndef SOC_DEFINES_TI814X_H_
#define SOC_DEFINES_TI814X_H_

#ifdef __cplusplus
extern "C" {
#endif

/**************************************************************************\
 * TI814x soc file
 \**************************************************************************/

#ifdef BIOS_PWRM_ENABLE
#include <pwrm.h>
#endif

/******************************************************************************\
 * Peripheral Instance count
 \******************************************************************************/

/** @brief Number of VPS CHRUS instances                                      */
#ifdef TI814X_FAMILY_BUILD
#define CSL_VPS_CHRUS_PER_CNT        (6U)
#else
#define CSL_VPS_CHRUS_PER_CNT        (3U)
#endif

/** @brief Number of VPS CIG instances                                        */
#define CSL_VPS_CIG_PER_CNT          (1U)

/** @brief Number of VPS COMP instances                                       */
#define CSL_VPS_COMP_PER_CNT         (1U)

/** @brief Number of VPS COMPR instances                                      */
#define CSL_VPS_COMPR_PER_CNT        (0U)

/** @brief Number of VPS DCOMPR instances                                     */
#define CSL_VPS_DCOMPR_PER_CNT       (0U)

/** @brief Number of VPS CSC instances                                        */
#ifdef TI814X_FAMILY_BUILD
#define CSL_VPS_CSC_PER_CNT          (6U)
#else
#define CSL_VPS_CSC_PER_CNT          (3U)
#endif

/** @brief Number of VPS DEI instances                                        */
#define CSL_VPS_DEI_PER_CNT          (1U)

/** @brief Number of VPS DRN instances                                        */
#define CSL_VPS_DRN_PER_CNT          (0U)

/** @brief Number of VPS GRPX instances */
#define CSL_VPS_GRPX_PER_CNT         (3U)

/** @brief Number of VPS instances                                            */
#define CSL_VPS_PER_CNT              (1U)

/** @brief Number of VPS EDE instances                                        */
#define CSL_VPS_EDE_PER_CNT          (0U)

/** @brief Number of VPS HDVENC instances                                     */
#define CSL_VPS_HD_VENC_PER_CNT      (2U)

/** @brief Number of VPS NF instances                                         */
#define CSL_VPS_NF_PER_CNT           (1U)

/** @brief Number of VPS SC instances                                         */
#ifdef TI814X_FAMILY_BUILD
#define CSL_VPS_SC_PER_CNT           (5U)
#else
#define CSL_VPS_SC_PER_CNT           (3U)
#endif
/** @brief Number of VPS SDVENC instances                                     */
#define CSL_VPS_SD_VENC_PER_CNT      (1U)

/** @brief Number of VPS VCOMP instances                                      */
#define CSL_VPS_VCOMP_PER_CNT        (1U)

/** @brief Number of VPS CPROC instances                                      */
#define CSL_VPS_CPROC_PER_CNT        (0U)

/** @brief Number of VPS VIP instances                                        */
#define CSL_VPS_VIP_PER_CNT                 (2U)

/** @brief Number of VPS instances                                            */
#define CSL_VPS_PER_CNT              (1U)

/** @brief Number of VPS VIP-PORT instances                                   */
#define CSL_VPS_VIP_PORT_PER_CNT            (4U)

/** @brief Number of VPS VPDMA instances                                      */
#define CSL_VPS_VPDMA_PER_CNT        (1U)

/**< @brief Number of VPS RF Modulator instances                              */
#define CSL_VPS_RF_PER_CNT           (0U)

/** @brief Number of VPS DSS-WB Pipelines  */
#define CSL_VPS_DSS_WB_PIPE_PER_CNT         (0U)

/** @brief Number of VPS CAPT ISS Pipelines  */
#define CSL_VPS_ISS_CAPT_PIPE_PER_CNT       (0U)

/** @brief Number of UPP  instances                                           */
#define CSL_UPP_PER_CNT                     1

/** @brief Number of UHPI instances                                           */
#define CSL_HPI_PER_CNT                     1

/** @brief Number of McASP instances                                          */
#define CSL_MCASP_PER_CNT                   ((uint32_t) 6U)

/** @brief Number of TIMER instances                                          */
#define CSL_TMR_PER_CNT                     8

/** @brief Number of PSC instances                                            */
#define CSL_PRCM_PER_CNT                    1

/** @brief Number of UART instances                                           */
#define CSL_UART_PER_CNT                    6

/** @brief Number of MCSPI instances                                          */
#define CSL_MCSPI_PER_CNT                   (4U)

/** @brief Number of I2C instances                                            */
#define CSL_I2C_PER_CNT                     4

/** @brief Number of PLL instances                                            */
#define CSL_PLLC_PER_CNT                    2

/** @brief Number of MMCSD instances                                          */
#define CSL_MMCSD_PER_CNT                   3

/** @brief Number of LCDC instances                                           */
#define CSL_LCDC_PER_CNT                    1

/** @brief Number of Mcbsp instances                                          */
#define CSL_MCBSP_PER_CNT                   1

/** @brief Number of EDMA3 CC instances                                       */
#define CSL_EDMA3CC_CNT                     1

/** @brief Number of EDMA3 TC instances                                       */
#define CSL_EDMA3TC_CNT                     4

/** @brief Number of EMIFA instances                                          */
#define CSL_EMIFA_PER_CNT                   1

/** @brief Number of EMIFB instances                                          */
#define CSL_EMIFB_PER_CNT                   1

/** @brief Number of EMAC instances                                           */
#define CSL_EMAC_PER_CNT                    2

/** @brief Number of MDIO instances                                           */
#define CSL_MDIO_PER_CNT                    1

/** @brief Number of EHRPWM instances                                         */
#define CSL_EHRPWM_PER_CNT                  2

/** @brief Number of ECAP instances                                           */
#define CSL_ECAP_PER_CNT                    3

/** @brief Number of CPGMAC instances                                         */
#define CSL_CPGMACSSR_PER_CNT               1

/** @brief Number of CPPI instances                                           */
#define CSL_CPPI_PER_CNT                    1

/** @brief Number of USB instances                                            */
#define CSL_USB_PER_CNT                     2

/** @brief Number of VPIF instances                                           */
#define CSL_VPIF_PER_CNT                    1

/** @brief Number of INTC instances                                           */
#define CSL_INTC_PER_CNT                    1

/** @brief Number of SATA instances                                           */
#define CSL_SATA_PER_CNT                    1

/** @brief Number of RTC instances                                            */
#define CSL_RTC_PER_CNT                     1

/** @brief Number of GPIO instances                                           */
#define CSL_GPIO_PER_CNT                    1

/** @brief Number of SYSCFG instances                                         */
#define CSL_SYSCFG_PER_CNT                  2

/** @brief Number of I2C instances                                            */
#define CSL_PCIE_PER_CNT                    1

/******************************************************************************\
 * Peripheral Instance definitions.
 \******************************************************************************/
/** @brief Peripheral Instances of McASP instances                            */
#define CSL_MCASP_0                         (0)

/** @brief Peripheral Instance of EDMA CC instances                           */
#define CSL_EDMA3CC_0                       (0)

/** @brief Peripheral Instance of EDMA TC instances                           */
#define CSL_EDMA3TC_0                       (0)
#define CSL_EDMA3TC_1                       (1)
#define CSL_EDMA3TC_2                       (2)
#define CSL_EDMA3TC_3                       (3)

/** @brief Peripheral Instance of Timer 64 instances                          */
#define CSL_TMR_0                           (0)
#define CSL_TMR_1                           (1)
#define CSL_TMR_2                           (2)
#define CSL_TMR_3                           (3)

/** @brief Peripheral Instances of PRCM instances                             */
#define CSL_PRCM_0                          (0)

/** @brief Peripheral Instances of UART instances                             */
#define CSL_UART_0                          (0)
#define CSL_UART_1                          (1)
#define CSL_UART_2                          (2)
#define CSL_UART_3                          (3)
#define CSL_UART_4                          (4)
#define CSL_UART_5                          (5)

typedef enum {
    UART1_INST = 0,
    UART2_INST,
    UART3_INST,
    UART4_INST,
    UART5_INST,
    UART6_INST
}UART_INST_t;

/** @brief Peripheral Instances of MCSPI instances                            */
#define CSL_MCSPI_0                         (0)
#define CSL_MCSPI_1                         (1)
#define CSL_MCSPI_2                         (2)
#define CSL_MCSPI_3                         (3)

/** @brief Peripheral Instances of I2C instances                              */
#define CSL_I2C_0                           (0)
#define CSL_I2C_1                           (1)
#define CSL_I2C_2                           (2)
#define CSL_I2C_3                           (3)

/** @brief Peripheral Instances of MMCSD instances                            */
#define CSL_MMCSD_0                         (0)
#define CSL_MMCSD_1                         (1)
#define CSL_MMCSD_2                         (2)

typedef enum {
    MMC1_INST = 0,
    MMC2_INST,
    MMC3_INST
}MMC_INST_t;

/** @brief Peripheral Instance of GPIO instances                              */
#define CSL_GPIO                            (0)
/** @brief GPIO pin and bank information                                      */
#define CSL_GPIO_NUM_PINS                   (128)
#define CSL_GPIO_NUM_BANKS                  ((CSL_GPIO_NUM_PINS + 15) / 16)

/** @brief Peripheral Instance of SYSCFG instances                            */
#define CSL_SYSCFG                          (2)

/** @brief Peripheral Instance of PCIe instances                            */
#define CSL_PCIE                            (0)

/*******************************************************************************
 * Peripheral Base Address
 *******************************************************************************/

/* This is MMPU mapped address.  Currently its one to one mapped */

#define CSL_BASE                     (0x48000000U)

/** \brief Control module base address */
#define CSL_CTRL_MODULE_BASE         (CSL_BASE + 0x00140000U)
/** \brief PRCM Base Address */
#define CSL_PRCM_BASE                (CSL_BASE + 0x00180000U)
/** \brief GPIO Base Address */
#define CSL_GPIO0_BASE               (CSL_BASE + 0x00032000U)
/** \brief I2C Base Address */
#define CSL_I2C0_BASE                (CSL_BASE + 0x00028000U)
#define CSL_I2C1_BASE                (CSL_BASE + 0x0002A000U)
#define CSL_I2C2_BASE                (CSL_BASE + 0x0019C000U)
#define CSL_I2C3_BASE                (CSL_BASE + 0x0019E000U)
/** \brief PLL Module base address */
#define CSL_PLL_BASE                 (CSL_BASE + 0x001C5000U)

/** @brief Base address of MCSPI memory mapped registers                      */
#define CSL_MCSPI_0_REGS                    (0x48030000U)
#define CSL_MCSPI_1_REGS                    (0x481A0000U)
#define CSL_MCSPI_2_REGS                    (0x481A2000U)
#define CSL_MCSPI_3_REGS                    (0x481A4000U)

/** @brief Base address of UART memory mapped registers                       */
#define CSL_UART_0_REGS                     (0x48020000U)
#define CSL_UART_1_REGS                     (0x48022000U)
#define CSL_UART_2_REGS                     (0x48024000U)
#define CSL_UART_3_REGS                     (0x481A6000U)
#define CSL_UART_4_REGS                     (0x481A8000U)
#define CSL_UART_5_REGS                     (0x481AA000U)

/** @brief Base address of McASP memory mapped registers                      */
#define CSL_MCASP_0_CTRL_REGS               (0x48038000U)
#define CSL_MCASP_0_FIFO_REGS               (0x48039000U)
#define CSL_MCASP_0_DATA_REGS               (0x46000000U)

#define CSL_MCASP_1_CTRL_REGS               (0x4803C000U)
#define CSL_MCASP_1_FIFO_REGS               (0x4803D000U)
#define CSL_MCASP_1_DATA_REGS               (0x46400000U)

#define CSL_MCASP_2_CTRL_REGS               (0x48050000U)
#define CSL_MCASP_2_FIFO_REGS               (0x48051000U)
#define CSL_MCASP_2_DATA_REGS               (0x46800000U)

#define CSL_MCASP_3_CTRL_REGS               (0x4A1A2000U)
#define CSL_MCASP_3_FIFO_REGS               (0x4A1A3000U)
#define CSL_MCASP_3_DATA_REGS               (0x4A1A5000U)

#define CSL_MCASP_4_CTRL_REGS               (0x4A1A8000U)
#define CSL_MCASP_4_FIFO_REGS               (0x4A1A9000U)
#define CSL_MCASP_4_DATA_REGS               (0x4A1AB000U)

#define CSL_MCASP_5_CTRL_REGS               (0x4A1AE000U)
#define CSL_MCASP_5_FIFO_REGS               (0x4A1AF000U)
#define CSL_MCASP_5_DATA_REGS               (0x4A1B1000U)

/******************************************************************************\
 * Interrupt Event IDs
 \*****************************************************************************/

/* VPS interrupt                                                              */
#define CSL_INTC_EVENTID_VPSINT2     (60U)
#define CSL_INTC_EVENTID_VPSINT3     (61U)
#define CSL_VPS_INTC_NUM             (3U)

/* I2C interrupt                                                              */
#define CSL_INTC_EVENTID_I2CINT0     (41U)
#define CSL_INTC_EVENTID_I2CINT1     (42U)
/* I2C2 interrupt is routed through I2C1 interrupt through the crossbar */
#define CSL_INTC_EVENTID_I2CINT2     (42U)
/* I2C3 interrupt is routed through the crossbar and not used */
#define CSL_INTC_EVENTID_I2CINT3     (0U)

/* To get the ducati int mux number, the 'CSL_INTMUX_OFFSET' has to be
 * subttracted from the interrupt number (directly mapped)
 */
#define    CSL_INTMUX_OFFSET                (23U)

/* MCSPI interrupt                                                            */
#define    CSL_INTC_EVENTID_MCSPIINT0       (75)
/* crossbar Mapped - please cross check before use */
#define    CSL_INTC_EVENTID_MCSPIINT1       (43)
#define    CSL_INTC_EVENTID_MCSPIINT2       (44)
#define    CSL_INTC_EVENTID_MCSPIINT3       (45)

/* UART interrupt                                                             */
#define    CSL_INTC_EVENTID_UARTINT0        (43)
#define    CSL_INTC_EVENTID_UARTINT1        (44)
#define    CSL_INTC_EVENTID_UARTINT2        (45)
/* crossbar please cross check before use */
#define    CSL_INTC_EVENTID_UARTINT3        (9)
#define    CSL_INTC_EVENTID_UARTINT4        (10)
#define    CSL_INTC_EVENTID_UARTINT5        (11)

#if (defined (TI814X_FAMILY_BUILD) && defined (BUILD_DSP))

/*
 * @brief   Interrupt Event IDs
 */
/* Output of event combiner 0, for events 1 to 31                             */
#define    CSL_INTC_EVENTID_EVT0                (0)
/* Output of event combiner 0, for events 32 to 63                            */
#define    CSL_INTC_EVENTID_EVT1                (1)
/* Output of event combiner 0, for events 64 to 95                            */
#define    CSL_INTC_EVENTID_EVT2                (2)
/* Output of event combiner 0, for events 96 to 127                           */
#define    CSL_INTC_EVENTID_EVT3                (3)

/* Timer 64P0 lower counter interrupt                                         */
#define    CSL_INTC_EVENTID_T64P0_TINT12        (4)

/* SYSCFG CHIPSIG Register Interrupt                                          */
#define    CSL_INTC_EVENTID_BOOTCFGINT0         (5)

#define    CSL_INTC_EVENTID_EHRPWM0             (7)

/* CC Completion Interrupt                                                    */
#define    CSL_INTC_EVENTID_EDMA3_0_CC0_INT1    (20)

#if defined (BUILD_M3)
/** @brief Defining McASP interrupt numbers for the M4 core                   */
/* McASP1 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP0_RXINT        (27U)
/* McASP1 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP0_TXINT        (28U)
/* McASP2 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP1_RXINT        (29U)
/* McASP2 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP1_TXINT        (30U)
/* McASP3 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP2_RXINT        (31U)
/* McASP3 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP2_TXINT        (32U)
/* McASP4 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP3_RXINT        (33U)
/* McASP4 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP3_TXINT        (59U)
/* McASP5 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP4_RXINT        (60U)
/* McASP5 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP4_TXINT        (61U)
/* McASP6 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP5_RXINT        (62U)
/* McASP6 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP5_TXINT        (63U)
#else
/* McASP0 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP0_RXINT        (71)
/* McASP0 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP0_TXINT        (70)
/* McASP1 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP1_RXINT        (73)
/* McASP1 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP1_TXINT        (72)
/* McASP2 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP2_RXINT        (75)
/* McASP2 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP2_TXINT        (74)
/* McASP3 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP3_RXINT        (81)
/* McASP3 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP3_TXINT        (80)
/* McASP4 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP4_RXINT        (83)
/* McASP4 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP4_TXINT        (82)
/* McASP5 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP5_RXINT        (85)
/* McASP5 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP5_TXINT        (84)
#endif

/* EDMA3 CC Error Interrupt                                                   */
#define    CSL_INTC_EVENTID_EDMA3_0_CC0_ERRINT  (21)
/* EDMA3 TC Error Interrupt                                                   */
#define    CSL_INTC_EVENTID_EDMA3_0_TC0_ERRINT  (22)
#define    CSL_INTC_EVENTID_EDMA3_0_TC1_ERRINT  (27)
#define    CSL_INTC_EVENTID_EDMA3_0_TC2_ERRINT  (28)
#define    CSL_INTC_EVENTID_EDMA3_0_TC3_ERRINT  (29)

/* PCIe interrupt*/
#define    CSL_INTC_EVENTID_PCIINT0             (36)
#define    CSL_INTC_EVENTID_PCIINT1             (37)
#define    CSL_INTC_EVENTID_PCIINT2             (38)
#define    CSL_INTC_EVENTID_PCIINT3             (39)

/* PRCM interrupt                                                             */
#define    CSL_INTC_EVENTID_PRCM0_ALLINT        (70)

/*************************** PRCM Numbers of peripherals **********************/
/* Even though this are defined in cslr_psc<soc>.h, we are redefining here we *
 * need to have same macros in the driver, for use across multiple Socs       */

#ifndef BIOS_PWRM_ENABLE

/*When PWRM is not enabled, we would be using the prcm apis provided by the   *
 * driver. These APIs use rCSL based PRCM number and hence are mapped to rCSL *
 * macros/ENUMS.                                                              */

/* Peripherals in PRCM0                                                       */
#define    CSL_PRCM_NUMBER_EDMA3_0_CC_0         0
#define    CSL_PRCM_NUMBER_EDMA3_0_TC_0         0
#define    CSL_PRCM_NUMBER_EDMA3_0_TC_1         0
#define    CSL_PRCM_NUMBER_EMIFA_0              0

#define    CSL_PRCM_NUMBER_MMCSD_0              0
#define    CSL_PRCM_NUMBER_MMCSD_1              0

#define    CSL_PRCM_NUMBER_MCSPI_0              (CM_ALWON_SPI_CLKCTRL)
#define    CSL_PRCM_NUMBER_MCSPI_1              (CM_ALWON_SPI_CLKCTRL)
#define    CSL_PRCM_NUMBER_MCSPI_2              (CM_ALWON_SPI_CLKCTRL)
#define    CSL_PRCM_NUMBER_MCSPI_3              (CM_ALWON_SPI_CLKCTRL)

#define    CSL_PRCM_NUMBER_I2C_0                (CM_ALWON_I2C_0_CLKCTRL)
#define    CSL_PRCM_NUMBER_I2C_1                (CM_ALWON_I2C_1_CLKCTRL)
#define    CSL_PRCM_NUMBER_I2C_2                (-1)
#define    CSL_PRCM_NUMBER_I2C_3                (-1)

#define    CSL_PRCM_NUMBER_UART_0               (CM_ALWON_UART_0_CLKCTRL)
#define    CSL_PRCM_NUMBER_UART_1               (CM_ALWON_UART_1_CLKCTRL)
#define    CSL_PRCM_NUMBER_UART_2               (CM_ALWON_UART_2_CLKCTRL)
#define    CSL_PRCM_NUMBER_UART_3               (CM_ALWON_UART_3_CLKCTRL)
#define    CSL_PRCM_NUMBER_UART_4               (CM_ALWON_UART_4_CLKCTRL)
#define    CSL_PRCM_NUMBER_UART_5               (CM_ALWON_UART_5_CLKCTRL)

#define    CSL_PRCM_NUMBER_MCASP_0              (CM_ALWON_MCASP0_CLKCTRL)
#define    CSL_PRCM_NUMBER_MCASP_1              (CM_ALWON_MCASP1_CLKCTRL)
#define    CSL_PRCM_NUMBER_MCASP_2              (CM_ALWON_MCASP2_CLKCTRL)
#define    CSL_PRCM_NUMBER_MCASP_3              (CM_ALWON_MCASP_3_4_5_CLKCTRL)
#define    CSL_PRCM_NUMBER_MCASP_4              (CM_ALWON_MCASP_3_4_5_CLKCTRL)
#define    CSL_PRCM_NUMBER_MCASP_5              (CM_ALWON_MCASP_3_4_5_CLKCTRL)

#else

/*********** Presently, PWRM support is not provided & used *******************/

/* When power management is defined, the straight PRCM numbers are            *
 * not useful for the driver and hence these macros are mapped to             *
 * PWRM specific ID, to be used in PWRM APIs                                  */

/* Peripherals in PRCM0                                                       */
#define    CSL_PRCM_NUMBER_EDMA3_0_CC_0         (PWRM_RSRC_EDMA3_CC_0)
#define    CSL_PRCM_NUMBER_EDMA3_0_TC_0         (PWRM_RSRC_EDMA3_TC_0)
#define    CSL_PRCM_NUMBER_EDMA3_0_TC_1         (PWRM_RSRC_EDMA3_TC_1)
#define    CSL_PRCM_NUMBER_EMIFA_0              (PWRM_RSRC_EMIFA)
#define    CSL_PRCM_NUMBER_SPI_0                (PWRM_RSRC_SPI_0)
#define    CSL_PRCM_NUMBER_MMCSD_0              0
#define    CSL_PRCM_NUMBER_UART_0               (PWRM_RSRC_UART_0)
#define    CSL_PRCM_NUMBER_EDMA3_1_CC_0         (PWRM_RSRC_EDMA3_CC_1)
#define    CSL_PRCM_NUMBER_MCASP_0              (PWRM_RSRC_MCASP_0)
#define    CSL_PRCM_NUMBER_SPI_1                (PWRM_RSRC_SPI_1)
#define    CSL_PRCM_NUMBER_I2C_1                (PWRM_RSRC_I2C_1)
#define    CSL_PRCM_NUMBER_UART_1               (PWRM_RSRC_UART_1)
#define    CSL_PRCM_NUMBER_UART_2               (PWRM_RSRC_UART_2)
#define    CSL_PRCM_NUMBER_MMCSD_1              (PWRM_RSRC_MMCSD_1)
#define    CSL_PRCM_NUMBER_EDMA3_1_TC_1         (PWRM_RSRC_EDMA3_TC_2)

#endif

#define    CSL_PRCM_INSTANCE_MAX            1U
#define    CSL_PRCM_NUMBER_MAX              59U

/************************  PRCM instances of peripherals *********************/
/* In some SOCs, the peripherals are spread across more that one PRCM. Hence *
 * the knowledge of the PRCM instance on which they reside is important for  *
 * driver                                                                    */

#define    CSL_PRCM_INST_EDMA3_0_CC_0           0
#define    CSL_PRCM_INST_EDMA3_0_TC_0           0
#define    CSL_PRCM_INST_EDMA3_0_TC_1           0
#define    CSL_PRCM_INST_MCSPI_0                0
#define    CSL_PRCM_INST_MCSPI_1                0
#define    CSL_PRCM_INST_MCSPI_2                0
#define    CSL_PRCM_INST_MCSPI_3                0
#define    CSL_PRCM_INST_MMCSD_0                0
#define    CSL_PRCM_INST_MMCSD_1                0
#define    CSL_PRCM_INST_MMCSD_2                0
#define    CSL_PRCM_INST_UART_0                 0
#define    CSL_PRCM_INST_UART_1                 0
#define    CSL_PRCM_INST_UART_2                 0
#define    CSL_PRCM_INST_UART_3                 0
#define    CSL_PRCM_INST_UART_4                 0
#define    CSL_PRCM_INST_UART_5                 0
#define    CSL_PRCM_INST_I2C_0                  0
#define    CSL_PRCM_INST_I2C_1                  0
#define    CSL_PRCM_INST_I2C_2                  0
#define    CSL_PRCM_INST_I2C_3                  0
#define    CSL_PRCM_INST_MCASP_0                0
#define    CSL_PRCM_INST_MCASP_1                0
#define    CSL_PRCM_INST_MCASP_2                0
#define    CSL_PRCM_INST_MCASP_3                0
#define    CSL_PRCM_INST_MCASP_4                0
#define    CSL_PRCM_INST_MCASP_5                0
#define    CSL_PRCM_INST_MCBSP_0                0

#endif
/*************************** EDMA RELATED DEFINES  ****************************/

/******************************************************************************\
 *  Parameterizable Configuration:- These are fed directly from the RTL
 *  parameters for the given SOC
 \******************************************************************************/

#define CSL_EDMA3_NUM_DMACH                 64
#define CSL_EDMA3_NUM_QDMACH                8
#define CSL_EDMA3_NUM_PARAMSETS             512
#define CSL_EDMA3_NUM_EVQUE                 4
#define CSL_EDMA3_CHMAPEXIST                0
#define CSL_EDMA3_NUM_REGIONS               4
#define CSL_EDMA3_MEMPROTECT                0

/******************************************************************************\
 * Channel Instance count
 \******************************************************************************/
#define CSL_EDMA3_CHA_CNT                   (CSL_EDMA3_NUM_DMACH + \
                                             CSL_EDMA3_NUM_QDMACH)

/* EDMA channel synchronization events                                        */

/* McASP0 Receive Event                                                       */
#define CSL_EDMA3_CHA_MCASP0_RX             9
/* McASP0 Transmit Event                                                      */
#define CSL_EDMA3_CHA_MCASP0_TX             8
/* McASP1 Receive Event                                                       */
#define CSL_EDMA3_CHA_MCASP1_RX             11
/* McASP1 Transmit Event                                                      */
#define CSL_EDMA3_CHA_MCASP1_TX             10
/* McASP2 Receive Event                                                       */
#define CSL_EDMA3_CHA_MCASP2_RX             13
/* McASP2 Transmit Event                                                      */
#define CSL_EDMA3_CHA_MCASP2_TX             12
/* McASP3 Receive Event                                                       */
#define CSL_EDMA3_CHA_MCASP3_RX             57
/* McASP3 Transmit Event                                                      */
#define CSL_EDMA3_CHA_MCASP3_TX             56
/* McASP4 Receive Event                                                       */
#define CSL_EDMA3_CHA_MCASP4_RX             63
/* McASP4 Transmit Event                                                      */
#define CSL_EDMA3_CHA_MCASP4_TX             62
/* McASP5 Receive Event                                                       */
#define CSL_EDMA3_CHA_MCASP5_RX             90
/* McASP5 Transmit Event                                                      */
#define CSL_EDMA3_CHA_MCASP5_TX             89

/* UART0 Receive Event                                                        */
#define CSL_EDMA3_CHA_UART0_RX              27
/* UART0 Transmit Event                                                       */
#define CSL_EDMA3_CHA_UART0_TX              26
/* UART1 Receive Event                                                        */
#define CSL_EDMA3_CHA_UART1_RX              29
/* UART1 Transmit Event                                                       */
#define CSL_EDMA3_CHA_UART1_TX              28
/* UART2 Receive Event                                                        */
#define CSL_EDMA3_CHA_UART2_RX              31
/* UART2 Transmit Event                                                       */
#define CSL_EDMA3_CHA_UART2_TX              30
/* UART3 Receive Event                                                        */
#define CSL_EDMA3_CHA_UART3_RX              71
/* UART3 Transmit Event                                                       */
#define CSL_EDMA3_CHA_UART3_TX              70
/* UART4 Receive Event                                                        */
#define CSL_EDMA3_CHA_UART4_RX              73
/* UART4 Transmit Event                                                       */
#define CSL_EDMA3_CHA_UART4_TX              72
/* UART5 Receive Event                                                        */
#define CSL_EDMA3_CHA_UART5_RX              75
/* UART5 Transmit Event                                                       */
#define CSL_EDMA3_CHA_UART5_TX              74

/* MCSPIx Channelx  */

/* MCSPI0 CHA0 Receive Event                                                  */
#define CSL_EDMA3_CHA0_MCSPI0_RX            17
/* MCSPI0 CHA0 Transmit Event                                                 */
#define CSL_EDMA3_CHA0_MCSPI0_TX            16
/* MCSPI0 CHA1 Receive Event                                                  */
#define CSL_EDMA3_CHA1_MCSPI0_RX            19
/* MCSPI0 CHA1 Transmit Event                                                 */
#define CSL_EDMA3_CHA1_MCSPI0_TX            18
/* MCSPI0 CHA2 Receive Event                                                  */
#define CSL_EDMA3_CHA2_MCSPI0_RX            21
/* MCSPI0 CHA2 Transmit Event                                                 */
#define CSL_EDMA3_CHA2_MCSPI0_TX            20
/* MCSPI0 CHA3 Receive Event                                                  */
#define CSL_EDMA3_CHA3_MCSPI0_RX            23
/* MCSPI0 CHA3 Transmit Event                                                 */
#define CSL_EDMA3_CHA3_MCSPI0_TX            22
/* MCSPI1 CHA0 Receive Event                                                  */
#define CSL_EDMA3_CHA0_MCSPI1_RX            43
/* MCSPI1 CHA0 Transmit Event                                                 */
#define CSL_EDMA3_CHA0_MCSPI1_TX            42
/* MCSPI1 CHA1 Receive Event                                                  */
#define CSL_EDMA3_CHA1_MCSPI1_RX            45
/* MCSPI1 CHA1 Transmit Event                                                 */
#define CSL_EDMA3_CHA1_MCSPI1_TX            44
/* MCSPI2 CHA0 Receive Event                                                  */
#define CSL_EDMA3_CHA0_MCSPI2_RX            80
/* MCSPI2 CHA0 Transmit Event                                                 */
#define CSL_EDMA3_CHA0_MCSPI2_TX            79
/* MCSPI2 CHA1 Receive Event                                                  */
#define CSL_EDMA3_CHA1_MCSPI2_RX            82
/* MCSPI2 CHA1 Transmit Event                                                 */
#define CSL_EDMA3_CHA1_MCSPI2_TX            81
/* MCSPI3 CHA0 Receive Event                                                  */
#define CSL_EDMA3_CHA0_MCSPI3_RX            84
/* MCSPI3 CHA0 Transmit Event                                                 */
#define CSL_EDMA3_CHA0_MCSPI3_TX            83

/* I2C Channelx  */

/* I2C0 Receive Event                                                         */
#define CSL_EDMA3_CHA_I2C0_RX               59
/* I2C0 Transmit Event                                                        */
#define CSL_EDMA3_CHA_I2C0_TX               58
/* I2C1 Receive Event                                                         */
#define CSL_EDMA3_CHA_I2C1_RX               61
/* I2C1 Transmit Event                                                        */
#define CSL_EDMA3_CHA_I2C1_TX               60
/* I2C2 Receive Event                                                         */
#define CSL_EDMA3_CHA_I2C2_RX               67
/* I2C2 Transmit Event                                                        */
#define CSL_EDMA3_CHA_I2C2_TX               66
/* I2C3 Receive Event                                                         */
#define CSL_EDMA3_CHA_I2C3_RX               69
/* I2C3 Transmit Event                                                        */
#define CSL_EDMA3_CHA_I2C3_TX               68

/** Peripheral related Info
 *
 *
 */

/* QDMA channels                                                              */
/* QDMA Channel Base */
#define    CSL_EDMA3_QCHA_BASE              (CSL_EDMA3_NUM_DMACH)

/* QDMA Channel 0 */
#define    CSL_EDMA3_QCHA_0                 (CSL_EDMA3_QCHA_BASE + 0)

/* QDMA Channel 1 */
#define    CSL_EDMA3_QCHA_1                 (CSL_EDMA3_QCHA_BASE + 1)

/* QDMA Channel 2 */
#define    CSL_EDMA3_QCHA_2                 (CSL_EDMA3_QCHA_BASE + 2)

/* QDMA Channel 3 */
#define    CSL_EDMA3_QCHA_3                 (CSL_EDMA3_QCHA_BASE + 3)

/* QDMA Channel 4 */
#define    CSL_EDMA3_QCHA_4                 (CSL_EDMA3_QCHA_BASE + 4)

/* QDMA Channel 5 */
#define    CSL_EDMA3_QCHA_5                 (CSL_EDMA3_QCHA_BASE + 5)

/* QDMA Channel 6 */
#define    CSL_EDMA3_QCHA_6                 (CSL_EDMA3_QCHA_BASE + 6)

/* QDMA Channel 7 */
#define    CSL_EDMA3_QCHA_7                 (CSL_EDMA3_QCHA_BASE + 7)

/* Enumerations for EDMA Controlleres */
typedef enum {
    CSL_EDMACC_ANY = -1,                      /* Any instance of EDMACC module*/
    CSL_EDMACC_0   = 0                        /* EDMACC Instance 0            */
} CSL_EdmaccNum;

/* Enumerations for EDMA Event Queues */
typedef enum {
    CSL_EDMA3_QUE_0 = 0,                       /* Queue 0                     */
    CSL_EDMA3_QUE_1 = 1,                       /* Queue 1                     */
    CSL_EDMA3_QUE_2 = 2,                       /* Queue 2                     */
    CSL_EDMA3_QUE_3 = 3                        /* Queue 3                     */
} CSL_Edma3Que;

/* Enumerations for EDMA Transfer Controllers
 *
 * There are 4 Transfer Controllers. Typically a one to one mapping exists
 * between Event Queues and Transfer Controllers.
 *
 */
typedef enum {
    CSL_EDMATC_ANY = -1,             /* Any instance of EDMATC                */
    CSL_EDMATC_0   = 0,              /* EDMATC Instance 0                     */
    CSL_EDMATC_1   = 1,              /* EDMATC Instance 1                     */
    CSL_EDMATC_2   = 2,              /* EDMATC Instance 2                     */
    CSL_EDMATC_3   = 3               /* EDMATC Instance 3                     */
} CSL_EdmatcNum;

#define CSL_EDMA3_REGION_GLOBAL            (-1)
#define CSL_EDMA3_REGION_0                  0
#define CSL_EDMA3_REGION_1                  1

/******************************* DAT RELATED DEFINES **************************/

/******************************************************************************\
 *  Parameterizable Configuration:- These are fed directly from the RTL
 *  parameters for the given SOC
 \******************************************************************************/
/******************************************************************************\
 * Channel Instance count
 \******************************************************************************/
/** @brief Number of Generic Channel instances                                */

/** @brief Enumerations for EDMA channels
 *
 *  There are 8 QDMA channels -
 *
 */
#define    CSL_DAT_QCHA_0                   0 /**<   QDMA Channel 0           */
#define    CSL_DAT_QCHA_1                   1 /**<   QDMA Channel 1           */
#define    CSL_DAT_QCHA_2                   2 /**<   QDMA Channel 2           */
#define    CSL_DAT_QCHA_3                   3 /**<   QDMA Channel 3           */
#define    CSL_DAT_QCHA_4                   4 /**<   QDMA Channel 4           */
#define    CSL_DAT_QCHA_5                   5 /**<   QDMA Channel 5           */
#define    CSL_DAT_QCHA_6                   6 /**<   QDMA Channel 6           */
#define    CSL_DAT_QCHA_7                   7 /**<   QDMA Channel 7           */

/** @brief Enumerations for EDMA Event Queues
 *
 *  There are two Event Queues. Q0 is the highest priority and Q1 is the least
 *  priority
 *
 */
typedef enum {
    CSL_DAT_PRI_DEFAULT = 0,                   /* Queue 0 is default          */
    CSL_DAT_PRI_0       = 0,                   /* Queue 0                     */
    CSL_DAT_PRI_1       = 1                    /* Queue 1                     */
} CSL_DatPriority;

/** @brief Enumeration for EDMA Regions
 *
 *
 */

#define CSL_DAT_REGION_GLOBAL              (-1)      /* Global Region        */
#define CSL_DAT_REGION_0                    0        /* EDMA Region 0        */
#define CSL_DAT_REGION_1                    1        /* EDMA Region 1        */
#define CSL_DAT_REGION_2                    2        /* EDMA Region 2        */
#define CSL_DAT_REGION_3                    3        /* EDMA Region 3        */

/** Peripheral related Info
 *
 *
 */

/*  PRCM    */
#define CSL_PRCM_0_ModuleNumMax            (59U)

/*  MCSPI   */
#define CSL_MCSPI_0_NumOfPhyChannels       (4U)
#define CSL_MCSPI_1_NumOfPhyChannels       (2U)
#define CSL_MCSPI_2_NumOfPhyChannels       (2U)
#define CSL_MCSPI_3_NumOfPhyChannels       (1U)

/*  MCASP   */
#define CSL_MCASP_0_NumSerializers         (6)
#define CSL_MCASP_1_NumSerializers         (6)
#define CSL_MCASP_2_NumSerializers         (6)
#define CSL_MCASP_3_NumSerializers         (6)
#define CSL_MCASP_4_NumSerializers         (6)
#define CSL_MCASP_5_NumSerializers         (6)

/** @brief Enumeration for peripheral frequencies
 *
 *
 */
/** I2C      */
#define CSL_I2C_0_MODULE_FREQ               (48000000)
#define CSL_I2C_1_MODULE_FREQ               (48000000)
#define CSL_I2C_2_MODULE_FREQ               (48000000)
#define CSL_I2C_3_MODULE_FREQ               (48000000)
#define CSL_I2C_4_MODULE_FREQ               (48000000)

/** MCSPI      */
#define CSL_MCSPI_0_MODULE_FREQ             (48000000)
#define CSL_MCSPI_1_MODULE_FREQ             (48000000)
#define CSL_MCSPI_2_MODULE_FREQ             (48000000)
#define CSL_MCSPI_3_MODULE_FREQ             (48000000)

/** UART     */
#define CSL_UART_0_MODULE_FREQ              (48000000)
#define CSL_UART_1_MODULE_FREQ              (48000000)
#define CSL_UART_2_MODULE_FREQ              (48000000)
#define CSL_UART_3_MODULE_FREQ              (192000000)
#define CSL_UART_4_MODULE_FREQ              (192000000)
#define CSL_UART_5_MODULE_FREQ              (192000000)

/** @brief McASP prcm registers */
#define CM_ALWON_MCASP_0_CLKCTRL             (PRCM_BASE + (uint32_t) 0x1540)
#define CM_ALWON_MCASP_1_CLKCTRL             (PRCM_BASE + (uint32_t) 0x1544)
#define CM_ALWON_MCASP_2_CLKCTRL             (PRCM_BASE + (uint32_t) 0x1548)
#define CM_ALWON_MCASP_3_4_5_CLKCTRL         (PRCM_BASE + (uint32_t) 0x1584)

/** @brief UARTs Clock registers */
#define CM_ALWON_UART_0_CLKCTRL              (PRCM_BASE + (uint32_t) 0x1550)
#define CM_ALWON_UART_1_CLKCTRL              (PRCM_BASE + (uint32_t) 0x1554)
#define CM_ALWON_UART_2_CLKCTRL              (PRCM_BASE + (uint32_t) 0x1558)
#define CM_ALWON_L3_SLOW_CLKSTCTRL           (PRCM_BASE + (uint32_t) 0x1400)

/** @brief McSPI prcm registers */
#define CM_ALWON_SPI_CLKCTRL                 (PRCM_BASE + (uint32_t) 0x1590)

/** @brief EDMA prcm registers */
#define CM_ALWON_TPCC_CLKCTRL                (PRCM_BASE + (uint32_t) 0x15F4)
#define CM_ALWON_TPTC0_CLKCTRL               (PRCM_BASE + (uint32_t) 0x15F8)
#define CM_ALWON_TPTC1_CLKCTRL               (PRCM_BASE + (uint32_t) 0x15FC)
#define CM_ALWON_TPTC2_CLKCTRL               (PRCM_BASE + (uint32_t) 0x1600)
#define CM_ALWON_TPTC3_CLKCTRL               (PRCM_BASE + (uint32_t) 0x1604)

/** @brief I2Cs Clock registers */
#define CM_ALWON_I2C_0_CLKCTRL               (PRCM_BASE + (uint32_t) 0x1564)
#define CM_ALWON_I2C_2_CLKCTRL               (PRCM_BASE + (uint32_t) 0x1568)

/** @brief McASP 2 PAD Control registers*/
#define PAD39_CNTRL                          (PADCTRL_BASE + \
                                              (uint32_t) (uint32_t) 0x0898)
#define PAD40_CNTRL                          (PADCTRL_BASE + (uint32_t) 0x089C)
#define PAD41_CNTRL                          (PADCTRL_BASE + (uint32_t) 0x08A0)
#define PAD42_CNTRL                          (PADCTRL_BASE + (uint32_t) 0x08A4)
#define PAD16_CNTRL                          (PADCTRL_BASE + (uint32_t) 0x083C)

/** @brief McASP 5 PAD Control registers*/
#define PAD55_CNTRL                          (PADCTRL_BASE + (uint32_t) 0x08D8)
#define PAD56_CNTRL                          (PADCTRL_BASE + (uint32_t) 0x08DC)
#define PAD57_CNTRL                          (PADCTRL_BASE + (uint32_t) 0x08E0)
#define PAD58_CNTRL                          (PADCTRL_BASE + (uint32_t) 0x08E4)
#define PAD16_CNTRL                          (PADCTRL_BASE + (uint32_t) 0x083C)

/** @brief McSPI 0 PAD Control registers*/
#define PAD80_CNTRL                          (PADCTRL_BASE + (uint32_t) 0x093C)
#define PAD81_CNTRL                          (PADCTRL_BASE + (uint32_t) 0x0940)
#define PAD82_CNTRL                          (PADCTRL_BASE + (uint32_t) 0x0944)
#define PAD83_CNTRL                          (PADCTRL_BASE + (uint32_t) 0x0948)
#define PAD84_CNTRL                          (PADCTRL_BASE + (uint32_t) 0x094C)

/** @brief McSPI 1 PAD Control registers*/
#define PAD85_CNTRL                          (PADCTRL_BASE + (uint32_t) 0x0950)
#define PAD86_CNTRL                          (PADCTRL_BASE + (uint32_t) 0x0954)
#define PAD87_CNTRL                          (PADCTRL_BASE + (uint32_t) 0x0958)
#define PAD88_CNTRL                          (PADCTRL_BASE + (uint32_t) 0x095C)
#define PAD89_CNTRL                          (PADCTRL_BASE + (uint32_t) 0x0960)

/** @brief UART 0 PAD Control registers*/

#define PAD69_CNTRL                          (PADCTRL_BASE + (uint32_t) 0x0910)
/* PINCTRL_UART0_RXD */
#define PAD70_CNTRL                          (PADCTRL_BASE + (uint32_t) 0x0914)
/* PINCTRL_UART0_TXD */
#define PAD71_CNTRL                          (PADCTRL_BASE + (uint32_t) 0x0918)
/* PINCTRL_UART0_CTSn */
#define PAD72_CNTRL                          (PADCTRL_BASE + (uint32_t) 0x091C)
/* PINCTRL_UART0_RTSn */
#define PAD73_CNTRL                          (PADCTRL_BASE + (uint32_t) 0x0920)

#define PAD90_CNTRL (PADCTRL_BASE + (uint32_t) 0x0964)
#define PAD91_CNTRL (PADCTRL_BASE + (uint32_t) 0x0968)
#define PAD92_CNTRL (PADCTRL_BASE + (uint32_t) 0x096C)
#define PAD93_CNTRL (PADCTRL_BASE + (uint32_t) 0x0970)
#define PAD94_CNTRL (PADCTRL_BASE + (uint32_t) 0x0974)
#define PAD95_CNTRL (PADCTRL_BASE + (uint32_t) 0x0978)
#define PAD96_CNTRL (PADCTRL_BASE + (uint32_t) 0x097C)
#define PAD97_CNTRL (PADCTRL_BASE + (uint32_t) 0x0980)
#define PAD98_CNTRL (PADCTRL_BASE + (uint32_t) 0x0984)
#define PAD99_CNTRL (PADCTRL_BASE + (uint32_t) 0x0988)
#define PAD100_CNTRL    (PADCTRL_BASE + (uint32_t) 0x098C)
#define PAD101_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0990)
#define PAD102_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0994)
#define PAD103_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0998)
#define PAD104_CNTRL    (PADCTRL_BASE + (uint32_t) 0x099C)

#define PAD105_CNTRL    (PADCTRL_BASE + (uint32_t) 0x09A0)
#define PAD106_CNTRL    (PADCTRL_BASE + (uint32_t) 0x09A4)
#define PAD107_CNTRL    (PADCTRL_BASE + (uint32_t) 0x09A8)
#define PAD108_CNTRL    (PADCTRL_BASE + (uint32_t) 0x09AC)
#define PAD109_CNTRL    (PADCTRL_BASE + (uint32_t) 0x09B0)
#define PAD110_CNTRL    (PADCTRL_BASE + (uint32_t) 0x09B4)
#define PAD111_CNTRL    (PADCTRL_BASE + (uint32_t) 0x09B8)
#define PAD112_CNTRL    (PADCTRL_BASE + (uint32_t) 0x09BC)
#define PAD113_CNTRL    (PADCTRL_BASE + (uint32_t) 0x09C0)
#define PAD115_CNTRL    (PADCTRL_BASE + (uint32_t) 0x09C8)
#define PAD116_CNTRL    (PADCTRL_BASE + (uint32_t) 0x09CC)

#define PAD117_CNTRL    (PADCTRL_BASE + (uint32_t) 0x09D0)
#define PAD118_CNTRL    (PADCTRL_BASE + (uint32_t) 0x09D4)
#define PAD119_CNTRL    (PADCTRL_BASE + (uint32_t) 0x09D8)
#define PAD120_CNTRL    (PADCTRL_BASE + (uint32_t) 0x09DC)
#define PAD122_CNTRL    (PADCTRL_BASE + (uint32_t) 0x09E4)
#define PAD123_CNTRL    (PADCTRL_BASE + (uint32_t) 0x09E8)
#define PAD124_CNTRL    (PADCTRL_BASE + (uint32_t) 0x09EC)
#define PAD125_CNTRL    (PADCTRL_BASE + (uint32_t) 0x09F0)
#define PAD126_CNTRL    (PADCTRL_BASE + (uint32_t) 0x09F4)
#define PAD127_CNTRL    (PADCTRL_BASE + (uint32_t) 0x09F8)
#define PAD128_CNTRL    (PADCTRL_BASE + (uint32_t) 0x09FC)
#define PAD129_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0A00)
#define PAD130_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0A04)
#define PAD131_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0A08)
#define PAD132_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0A0C)
#define PAD133_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0A10)

#define PAD168_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0A9C)
#define PAD169_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0AA0)
#define PAD170_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0AA4)
#define PAD171_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0AA8)
#define PAD172_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0AAC)
#define PAD173_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0AB0)
#define PAD174_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0AB4)
#define PAD175_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0AB8)

#define PAD204_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0B2C)
#define PAD205_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0B30)
#define PAD206_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0B34)
#define PAD207_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0B38)
#define PAD208_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0B3C)
#define PAD209_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0B40)
#define PAD210_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0B44)
#define PAD211_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0B48)
#define PAD212_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0B4C)
#define PAD213_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0B50)
#define PAD214_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0B54)
#define PAD215_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0B58)
#define PAD216_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0B5C)
#define PAD217_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0B60)
#define PAD218_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0B64)
#define PAD219_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0B68)
#define PAD220_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0B6C)
#define PAD221_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0B70)
#define PAD222_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0B74)
#define PAD223_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0B78)
#define PAD224_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0B7C)
#define PAD225_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0B80)
#define PAD226_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0B84)
#define PAD227_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0B88)

#define PAD228_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0B8C)
#define PAD229_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0B90)
#define PAD230_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0B94)

#define PAD232_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0B9c)
#define PAD233_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0Ba0)
#define PAD234_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0Ba4)

#define PAD235_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0BA8)
#define PAD236_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0BAC)
#define PAD237_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0BB0)
#define PAD238_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0BB4)
#define PAD239_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0BB8)
#define PAD240_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0BBC)
#define PAD241_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0BC0)
#define PAD242_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0BC4)
#define PAD243_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0BC8)
#define PAD244_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0BCC)
#define PAD245_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0BD0)
#define PAD246_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0BD4)
#define PAD247_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0BD8)
#define PAD248_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0BDC)
#define PAD249_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0BE0)
#define PAD250_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0BE4)
#define PAD251_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0BE8)
#define PAD252_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0BEC)
#define PAD253_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0BF0)
#define PAD254_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0BF4)
#define PAD255_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0BF8)
#define PAD256_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0BFC)
#define PAD257_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0C00)
#define PAD258_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0C04)
#define PAD259_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0C08)
#define PAD260_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0C0C)
#define PAD261_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0C10)
#define PAD262_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0C14)
#define PAD263_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0C18)
#define PAD264_CNTRL    (PADCTRL_BASE + (uint32_t) 0x0C1C)

/*GPIO CLK registers*/
#define CM_ALWON_GPIO_0_CLKCTRL     (PRCM_BASE + (uint32_t) 0x155C)
#define CM_ALWON_GPIO_1_CLKCTRL     (PRCM_BASE + (uint32_t) 0x1560)

/*GPMC CLK registers*/
#define CM_ALWON_GPMC_CLKCTRL       (PRCM_BASE + (uint32_t) 0x15D0)

/* DUCATI XBAR base address */
#define DUCATI_INTMUX_0_3_CNTL               (PADCTRL_BASE + (uint32_t) 0x0F54)

/******************************************************************************\
 *  Parameterizable Configuration:- These are fed directly from the RTL
 *  parameters for the given SOC
 \******************************************************************************/

#define TPCC_MUX(n)                         (0xF90 + ((n) * 4))

#define SOC_LCDC_0_REGS                     0x4830E000

#define SOC_ADC_TSC_0_REGS                  0x44E0D000

/** @brief Base addresses of PWMSS memory mapped registers.                   */

#define SOC_PWMSS0_REGS                     (0x48300000)
#define SOC_PWMSS1_REGS                     (0x48302000)
#define SOC_PWMSS2_REGS                     (0x48304000)

#define SOC_ECAP_REGS                       (0x00000100)
#define SOC_EQEP_REGS                       (0x00000180)
#define SOC_EPWM_REGS                       (0x00000200)

#define SOC_ECAP_0_REGS                     (SOC_PWMSS0_REGS + SOC_ECAP_REGS)
#define SOC_ECAP_1_REGS                     (SOC_PWMSS1_REGS + SOC_ECAP_REGS)
#define SOC_ECAP_2_REGS                     (SOC_PWMSS2_REGS + SOC_ECAP_REGS)

#define SOC_EQEP_0_REGS                     (SOC_PWMSS0_REGS + SOC_EQEP_REGS)
#define SOC_EQEP_1_REGS                     (SOC_PWMSS1_REGS + SOC_EQEP_REGS)
#define SOC_EQEP_2_REGS                     (SOC_PWMSS2_REGS + SOC_EQEP_REGS)

#define SOC_EPWM_0_REGS                     (SOC_PWMSS0_REGS + SOC_EPWM_REGS)
#define SOC_EPWM_1_REGS                     (SOC_PWMSS1_REGS + SOC_EPWM_REGS)
#define SOC_EPWM_2_REGS                     (SOC_PWMSS2_REGS + SOC_EPWM_REGS)

#define SOC_PWM0_SUB_SYS_CLOCK_CONFIG_REGS   0x48300008
#define SOC_PWM0_SUB_SYS_CLOCK_STATUS_REGS   0x4830000C
#define SOC_PWM0_SUB_SYS_SYS_CONFIG_REGS     0x48300004

#define SOC_PWM1_SUB_SYS_CLOCK_CONFIG_REGS   0x48302008
#define SOC_PWM1_SUB_SYS_CLOCK_STATUS_REGS   0x4830200C
#define SOC_PWM1_SUB_SYS_SYS_CONFIG_REGS     0x48302004

#define SOC_PWM2_SUB_SYS_CLOCK_CONFIG_REGS   0x48304008
#define SOC_PWM2_SUB_SYS_CLOCK_STATUS_REGS   0x4830400C
#define SOC_PWM2_SUB_SYS_SYS_CONFIG_REGS     0x48304004

#define SOC_EPWM_MODULE_FREQ                 100

#ifdef __cplusplus
}
#endif

#endif  /* SOC_DEFINES_TI814X_H_ */
