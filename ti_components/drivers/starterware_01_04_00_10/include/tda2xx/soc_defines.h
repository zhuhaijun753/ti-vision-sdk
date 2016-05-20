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

#ifndef SOC_DEFINES_TDA2XX_H_
#define SOC_DEFINES_TDA2XX_H_

#ifdef __cplusplus
extern "C" {
#endif

/**************************************************************************\
 * TDA2XX soc file
 \**************************************************************************/

/******************************************************************************\
 * Peripheral Instance count
 \******************************************************************************/

/** @brief Number of VPS VIP instances                                        */
#ifndef TDA2EX_BUILD
#define CSL_VPS_VIP_PER_CNT             (3U)
#else
#define CSL_VPS_VIP_PER_CNT             (1U)
#endif
/** @brief Number of VPS VPE instances                                        */
#define CSL_VPS_VPE_PER_CNT             (1U)

/** @brief Number of VPS DSS instances                                        */
#define CSL_VPS_DSS_PER_CNT             (1U)

/** @brief Number of VPS VIP instances                                        */
#define CSL_VPS_VIP_TOP_PER_CNT         (CSL_VPS_VIP_PER_CNT)

/** @brief Number of VPS VIP-PORT instances                                   */
#define CSL_VPS_VIP_PORT_PER_CNT        (CSL_VPS_VIP_PER_CNT * 4U)

/** @brief Number of VPS VPDMA instances                                      */
#define CSL_VPS_VPDMA_PER_CNT           (CSL_VPS_VIP_PER_CNT + \
                                         CSL_VPS_VPE_PER_CNT)

/** @brief Number of VPS CHRUS instances                                      */
#define CSL_VPS_CHRUS_PER_CNT           (CSL_VPS_VPE_PER_CNT * 3U)

/** @brief Number of VPS CSC instances                                        */
#define CSL_VPS_CSC_PER_CNT             ((CSL_VPS_VIP_PER_CNT * 2U) + \
                                         CSL_VPS_VPE_PER_CNT)

/** @brief Number of VPS VPE instances                                        */
#define CSL_VPS_VPE_TOP_PER_CNT         (CSL_VPS_VPE_PER_CNT)

/** @brief Number of VPS DEI instances                                        */
#define CSL_VPS_DEI_PER_CNT             (CSL_VPS_VPE_PER_CNT * 1U)

/** @brief Number of VPS SC instances                                         */
#define CSL_VPS_SC_PER_CNT              ((CSL_VPS_VIP_PER_CNT * 2U) \
                                         + CSL_VPS_VPE_PER_CNT)

/** @brief Number of VPS DSS-Video + Graphics instances */
#define CSL_VPS_DSS_VID_PIPE_PER_CNT    (4U)

/** @brief Number of VPS WB instances */
#define CSL_VPS_DSS_WB_PIPE_PER_CNT     (1U)

/** @brief Number of VPS CAPT ISS Pipelines  */
#define CSL_VPS_ISS_CAPT_PIPE_PER_CNT       (0U)

/** @brief Number of VPS DSS-Overlay manager instances                        */
#define CSL_VPS_DSS_OVLY_MGR_PER_CNT    (4U)

/******************************************************************************\
 * Interrupt Event IDs
 \******************************************************************************/

/* VPS interrupt                                                              */
#define CSL_INTC_EVENTID_VIP1INT0  (27U)
#ifndef TDA2EX_BUILD
#define CSL_INTC_EVENTID_VIP2INT0  (28U)
#define CSL_INTC_EVENTID_VIP3INT0  (29U)
#endif
#define CSL_INTC_EVENTID_VPEINT0   (30U)
#define CSL_INTC_EVENTID_DSS_DISPC (23U)
#define CSL_VPS_INTC_NUM           (0U)

/** @brief Number of McASP instances                                          */
#define CSL_MCASP_PER_CNT                   ((uint32_t) 8U)

/** @brief Number of UART instances                                           */
#define CSL_UART_PER_CNT                    ((uint32_t) 10U)

/** @brief Number of MCSPI instances                                          */
#define CSL_MCSPI_PER_CNT                   ((uint32_t) 4U)

/******************************************************************************\
 * Peripheral Instance definitions.
 \******************************************************************************/
/** @brief Peripheral Instances of McASP instances                            */
#define CSL_MCASP_0                         (0)

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
    UART6_INST,
    UART7_INST,
    UART8_INST,
    UART9_INST,
    UART10_INST
}UART_INST_t;

/** @brief Peripheral Instances of MCSPI instances                            */
#define CSL_MCSPI_0                         (0)
#define CSL_MCSPI_1                         (1)
#define CSL_MCSPI_2                         (2)
#define CSL_MCSPI_3                         (3)

/** @brief Peripheral Instances of MMC/SD instances
 *                           */
typedef enum {
    MMC1_INST = 0,
    MMC2_INST,
    MMC3_INST,
    MMC4_INST
}MMC_INST_t;

/******************************************************************************\
 * Interrupt Event IDs
 \*****************************************************************************/

/* I2C interrupt                                                              */
#define CSL_INTC_EVENTID_I2CINT1     (41U)
#define CSL_INTC_EVENTID_I2CINT3     (43U)
/*I2C4 Interrupt number is used by UART through cross bar and hence be cautious
 *while using this */
#define CSL_INTC_EVENTID_I2CINT4     (44U)

#if defined (TDA2EX_BUILD)
/*I2C2 Interrupt is mapped through cross bar and not used */
#define CSL_INTC_EVENTID_I2CINT2     (0U)
#define CSL_INTC_EVENTID_I2CINT5     (42U)
#else
#define CSL_INTC_EVENTID_I2CINT2     (42U)
/*I2C5 Interrupt is mapped through cross bar and not used */
#define CSL_INTC_EVENTID_I2CINT5     (48U)
#endif

/* To get the ducati int mux number, the 'CSL_INTMUX_OFFSET' has to be
 * subttracted from the interrupt number (directly mapped)
 */
#define    CSL_INTMUX_OFFSET                (23U)

/* MCSPI interrupt                                                            */
#define    CSL_INTC_EVENTID_MCSPIINT0       (57)
#define    CSL_INTC_EVENTID_MCSPIINT1       (58)
/*Dummy and crossbar Mapped - please cross check before use */
#define    CSL_INTC_EVENTID_MCSPIINT2       (44)
#define    CSL_INTC_EVENTID_MCSPIINT3       (45)

/* UART interrupt                                                             */
/* All are crossbar mapped please cross check before use */
/*UART1 is being used in DMA Mode */
/*Instance Number Macro definitions are started from 0, it needs to be changed
 *to 1 later*/
#if (defined BUILD_A15)
/* For a15, UART1 address is 72. 32 is added to offset reserved interrupts */
#define    CSL_INTC_EVENTID_UARTINT0        (72U + 32U)
/* Below interrupts needs to be changed */
#define    CSL_INTC_EVENTID_UARTINT1        (60U + 32U)
#define    CSL_INTC_EVENTID_UARTINT2        (45U + 32U)
#define    CSL_INTC_EVENTID_UARTINT3        (61U + 32U)
#define    CSL_INTC_EVENTID_UARTINT4        (62U + 32U)
#define    CSL_INTC_EVENTID_UARTINT5        (63U + 32U)
#define    CSL_INTC_EVENTID_UARTINT6        (64U + 32U)
#define    CSL_INTC_EVENTID_UARTINT7        (65U + 32U)
#define    CSL_INTC_EVENTID_UARTINT8        (69U + 32U)
#define    CSL_INTC_EVENTID_UARTINT9        (70U + 32U)
#else
#define    CSL_INTC_EVENTID_UARTINT0        (44U)
#define    CSL_INTC_EVENTID_UARTINT1        (60U)
#define    CSL_INTC_EVENTID_UARTINT2        (45U)
#define    CSL_INTC_EVENTID_UARTINT3        (61U)
#define    CSL_INTC_EVENTID_UARTINT4        (62U)
#define    CSL_INTC_EVENTID_UARTINT5        (63U)
#define    CSL_INTC_EVENTID_UARTINT6        (64U)
#define    CSL_INTC_EVENTID_UARTINT7        (65U)
#define    CSL_INTC_EVENTID_UARTINT8        (69U)
#define    CSL_INTC_EVENTID_UARTINT9        (70U)
#endif

/* McASP Interrupts
 *   All are crossbar mapped please cross check before use */
#if defined (BUILD_M4)
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
/* McASP7 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP6_RXINT        (69U)
/* McASP7 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP6_TXINT        (70U)
/* McASP8 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP7_RXINT        (71U)
/* McASP8 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP7_TXINT        (72U)
#else
/* McASP1 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP0_RXINT        (58U)
/* McASP1 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP0_TXINT        (59U)
/* McASP2 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP1_RXINT        (60U)
/* McASP2 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP1_TXINT        (61U)
/* McASP3 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP2_RXINT        (91U)
/* McASP3 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP2_TXINT        (92U)
/* McASP4 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP3_RXINT        (74U)
/* McASP4 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP3_TXINT        (51U)
/* McASP5 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP4_RXINT        (79U)
/* McASP5 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP4_TXINT        (81U)
/* McASP6 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP5_RXINT        (86U)
/* McASP6 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP5_TXINT        (87U)
/* McASP7 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP6_RXINT        (88U)
/* McASP7 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP6_TXINT        (43U)
/* McASP8 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP7_RXINT        (48U)
/* McASP8 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP7_TXINT        (49U)
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
#define CSL_EDMA3_CHA_MCASP0_RX             0
/* McASP0 Transmit Event                                                      */
#define CSL_EDMA3_CHA_MCASP0_TX             1
/* McASP1 Receive Event                                                       */
#define CSL_EDMA3_CHA_MCASP1_RX             2
/* McASP1 Transmit Event                                                      */
#define CSL_EDMA3_CHA_MCASP1_TX             3
/* McASP2 Receive Event                                                       */
#define CSL_EDMA3_CHA_MCASP2_RX             4
/* McASP2 Transmit Event                                                      */
#define CSL_EDMA3_CHA_MCASP2_TX             5
/* McASP3 Receive Event                                                       */
#define CSL_EDMA3_CHA_MCASP3_RX             6
/* McASP3 Transmit Event                                                      */
#define CSL_EDMA3_CHA_MCASP3_TX             7
/* McASP4 Receive Event                                                       */
#define CSL_EDMA3_CHA_MCASP4_RX             8
/* McASP4 Transmit Event                                                      */
#define CSL_EDMA3_CHA_MCASP4_TX             9
/* McASP5 Receive Event                                                       */
#define CSL_EDMA3_CHA_MCASP5_RX             10
/* McASP5 Transmit Event                                                      */
#define CSL_EDMA3_CHA_MCASP5_TX             11
/* McASP6 Receive Event                                                       */
#define CSL_EDMA3_CHA_MCASP6_RX             12
/* McASP6 Transmit Event                                                      */
#define CSL_EDMA3_CHA_MCASP6_TX             13
/* McASP7 Receive Event                                                       */
#define CSL_EDMA3_CHA_MCASP7_RX             14
/* McASP7 Transmit Event                                                      */
#define CSL_EDMA3_CHA_MCASP7_TX             15
/*
 * *Instance Numbers starts from 1 in Vayu but keeping it to 0 to not change the
 * driver
 * Need to modify driver later for Instance Numbers
 */
/* UART0 Receive Event                                                        */
#define CSL_EDMA3_CHA_UART0_RX              49
/* UART0 Transmit Event                                                       */
#define CSL_EDMA3_CHA_UART0_TX              48
/* UART1 Receive Event                                                        */
#define CSL_EDMA3_CHA_UART1_RX              51
/* UART1 Transmit Event                                                       */
#define CSL_EDMA3_CHA_UART1_TX              50
/* UART2 Receive Event                                                        */
#define CSL_EDMA3_CHA_UART2_RX              53
/* UART2 Transmit Event                                                       */
#define CSL_EDMA3_CHA_UART2_TX              52
/* UART3 Receive Event                                                        */
#define CSL_EDMA3_CHA_UART3_RX              55
/* UART3 Transmit Event                                                       */
#define CSL_EDMA3_CHA_UART3_TX              54
/* UART4 Receive Event                                                        */
#define CSL_EDMA3_CHA_UART4_RX              63
/* UART4 Transmit Event                                                       */
#define CSL_EDMA3_CHA_UART4_TX              62

/*
 * Below are Cross Bar Mapped Please redefine for any
 * simultaneous usecase in DMA Mode
 */

/* UART5 Receive Event                                                        */
#define CSL_EDMA3_CHA_UART5_RX              51
/* UART5 Transmit Event                                                       */
#define CSL_EDMA3_CHA_UART5_TX              50
/* UART6 Receive Event                                                        */
#define CSL_EDMA3_CHA_UART6_RX              51
/* UART6 Transmit Event                                                       */
#define CSL_EDMA3_CHA_UART6_TX              50
/* UART7 Receive Event                                                        */
#define CSL_EDMA3_CHA_UART7_RX              51
/* UART7 Transmit Event                                                       */
#define CSL_EDMA3_CHA_UART7_TX              50
/* UART8 Receive Event                                                        */
#define CSL_EDMA3_CHA_UART8_RX              51
/* UART8 Transmit Event                                                       */
#define CSL_EDMA3_CHA_UART8_TX              50
/* UART9 Receive Event                                                        */
#define CSL_EDMA3_CHA_UART9_RX              51
/* UART9 Transmit Event                                                       */
#define CSL_EDMA3_CHA_UART9_TX              50

/* MCSPIx Channelx  */

/* MCSPI0 CHA0 Receive Event                                                  */
#define CSL_EDMA3_CHA0_MCSPI0_RX            35
/* MCSPI0 CHA0 Transmit Event                                                 */
#define CSL_EDMA3_CHA0_MCSPI0_TX            34
/* MCSPI0 CHA1 Receive Event                                                  */
#define CSL_EDMA3_CHA1_MCSPI0_RX            37
/* MCSPI0 CHA1 Transmit Event                                                 */
#define CSL_EDMA3_CHA1_MCSPI0_TX            36
/* MCSPI0 CHA2 Receive Event                                                  */
#define CSL_EDMA3_CHA2_MCSPI0_RX            39
/* MCSPI0 CHA2 Transmit Event                                                 */
#define CSL_EDMA3_CHA2_MCSPI0_TX            38
/* MCSPI0 CHA3 Receive Event                                                  */
#define CSL_EDMA3_CHA3_MCSPI0_RX            41
/* MCSPI0 CHA3 Transmit Event                                                 */
#define CSL_EDMA3_CHA3_MCSPI0_TX            40
/* MCSPI1 CHA0 Receive Event                                                  */
#define CSL_EDMA3_CHA0_MCSPI1_RX            43
/* MCSPI1 CHA0 Transmit Event                                                 */
#define CSL_EDMA3_CHA0_MCSPI1_TX            42
/* MCSPI1 CHA1 Receive Event                                                  */
#define CSL_EDMA3_CHA1_MCSPI1_RX            45
/* MCSPI1 CHA1 Transmit Event                                                 */
#define CSL_EDMA3_CHA1_MCSPI1_TX            44
/* MCSPI2 CHA0 Receive Event                                                  */
#define CSL_EDMA3_CHA0_MCSPI2_RX            15
/* MCSPI2 CHA0 Transmit Event                                                 */
#define CSL_EDMA3_CHA0_MCSPI2_TX            14
/* MCSPI2 CHA1 Receive Event                                                  */
#define CSL_EDMA3_CHA1_MCSPI2_RX            23
/* MCSPI2 CHA1 Transmit Event                                                 */
#define CSL_EDMA3_CHA1_MCSPI2_TX            22
/*
 * Cross Bar Mapped Please check before use
 */
/* MCSPI3 CHA0 Receive Event                                                  */
#define CSL_EDMA3_CHA0_MCSPI3_RX            23
/* MCSPI3 CHA0 Transmit Event                                                 */
#define CSL_EDMA3_CHA0_MCSPI3_TX            22

/** Peripheral related Info
 *
 *
 */

/*  MCSPI   */
#define CSL_MCSPI_0_NumOfPhyChannels       (4U)
#define CSL_MCSPI_1_NumOfPhyChannels       (2U)
#define CSL_MCSPI_2_NumOfPhyChannels       (2U)
#define CSL_MCSPI_3_NumOfPhyChannels       (1U)

#define CSL_MCASP_0_NumSerializers         (16)
#define CSL_MCASP_1_NumSerializers         (16)
#define CSL_MCASP_2_NumSerializers         (4)
#define CSL_MCASP_3_NumSerializers         (4)
#define CSL_MCASP_4_NumSerializers         (4)
#define CSL_MCASP_5_NumSerializers         (4)
#define CSL_MCASP_6_NumSerializers         (4)
#define CSL_MCASP_7_NumSerializers         (4)

/** @brief Enumeration for peripheral frequencies
 *
 *
 */

/** I2C      */
#define CSL_I2C_0_MODULE_FREQ               (96000000)
#define CSL_I2C_1_MODULE_FREQ               (96000000)
#define CSL_I2C_2_MODULE_FREQ               (96000000)
#define CSL_I2C_3_MODULE_FREQ               (96000000)
#define CSL_I2C_4_MODULE_FREQ               (96000000)
#if defined (TDA2EX_BUILD)
#define CSL_I2C_5_MODULE_FREQ               (96000000)
#endif

/** MCSPI      */
#define CSL_MCSPI_0_MODULE_FREQ             (48000000)
#define CSL_MCSPI_1_MODULE_FREQ             (48000000)
#define CSL_MCSPI_2_MODULE_FREQ             (48000000)
#define CSL_MCSPI_3_MODULE_FREQ             (48000000)

/** UART     */
#define CSL_UART_0_MODULE_FREQ              (48000000)
#define CSL_UART_1_MODULE_FREQ              (48000000)
#define CSL_UART_2_MODULE_FREQ              (48000000)
#define CSL_UART_3_MODULE_FREQ              (48000000)
#define CSL_UART_4_MODULE_FREQ              (48000000)
#define CSL_UART_5_MODULE_FREQ              (48000000)
#define CSL_UART_6_MODULE_FREQ              (48000000)
#define CSL_UART_7_MODULE_FREQ              (48000000)
#define CSL_UART_8_MODULE_FREQ              (48000000)
#define CSL_UART_9_MODULE_FREQ              (48000000)

/******************************************************************************
 * IRQ XBAR instance mapping for each core interrupts.
 * This is the IRQ XBAR instance to which a particular interrupt of the core is
 * mapped. This macro could be used to pass the IRQ XBAR instance to the IRQ
 * XBAR connect API of starterware.
 ******************************************************************************/
/* IRQ XBAR Mapping for MPU */
#define XBAR_INST_MPU_IRQ_4             (1U)
#define XBAR_INST_MPU_IRQ_7             (2U)
#define XBAR_INST_MPU_IRQ_8             (3U)
#define XBAR_INST_MPU_IRQ_9             (4U)
#define XBAR_INST_MPU_IRQ_10            (5U)
#define XBAR_INST_MPU_IRQ_11            (6U)
#define XBAR_INST_MPU_IRQ_12            (7U)
#define XBAR_INST_MPU_IRQ_13            (8U)
#define XBAR_INST_MPU_IRQ_14            (9U)
#define XBAR_INST_MPU_IRQ_15            (10U)
#define XBAR_INST_MPU_IRQ_16            (11U)
#define XBAR_INST_MPU_IRQ_17            (12U)
#define XBAR_INST_MPU_IRQ_18            (13U)
#define XBAR_INST_MPU_IRQ_19            (14U)
#define XBAR_INST_MPU_IRQ_20            (15U)
#define XBAR_INST_MPU_IRQ_21            (16U)
#define XBAR_INST_MPU_IRQ_22            (17U)
#define XBAR_INST_MPU_IRQ_23            (18U)
#define XBAR_INST_MPU_IRQ_24            (19U)
#define XBAR_INST_MPU_IRQ_25            (20U)
#define XBAR_INST_MPU_IRQ_26            (21U)
#define XBAR_INST_MPU_IRQ_27            (22U)
#define XBAR_INST_MPU_IRQ_28            (23U)
#define XBAR_INST_MPU_IRQ_29            (24U)
#define XBAR_INST_MPU_IRQ_30            (25U)
#define XBAR_INST_MPU_IRQ_31            (26U)
#define XBAR_INST_MPU_IRQ_32            (27U)
#define XBAR_INST_MPU_IRQ_33            (28U)
#define XBAR_INST_MPU_IRQ_34            (29U)
#define XBAR_INST_MPU_IRQ_35            (30U)
#define XBAR_INST_MPU_IRQ_36            (31U)
#define XBAR_INST_MPU_IRQ_37            (32U)
#define XBAR_INST_MPU_IRQ_38            (33U)
#define XBAR_INST_MPU_IRQ_39            (34U)
#define XBAR_INST_MPU_IRQ_40            (35U)
#define XBAR_INST_MPU_IRQ_41            (36U)
#define XBAR_INST_MPU_IRQ_42            (37U)
#define XBAR_INST_MPU_IRQ_43            (38U)
#define XBAR_INST_MPU_IRQ_44            (39U)
#define XBAR_INST_MPU_IRQ_45            (40U)
#define XBAR_INST_MPU_IRQ_46            (41U)
#define XBAR_INST_MPU_IRQ_47            (42U)
#define XBAR_INST_MPU_IRQ_48            (43U)
#define XBAR_INST_MPU_IRQ_49            (44U)
#define XBAR_INST_MPU_IRQ_50            (45U)
#define XBAR_INST_MPU_IRQ_51            (46U)
#define XBAR_INST_MPU_IRQ_52            (47U)
#define XBAR_INST_MPU_IRQ_53            (48U)
#define XBAR_INST_MPU_IRQ_54            (49U)
#define XBAR_INST_MPU_IRQ_55            (50U)
#define XBAR_INST_MPU_IRQ_56            (51U)
#define XBAR_INST_MPU_IRQ_57            (52U)
#define XBAR_INST_MPU_IRQ_58            (53U)
#define XBAR_INST_MPU_IRQ_59            (54U)
#define XBAR_INST_MPU_IRQ_60            (55U)
#define XBAR_INST_MPU_IRQ_61            (56U)
#define XBAR_INST_MPU_IRQ_62            (57U)
#define XBAR_INST_MPU_IRQ_63            (58U)
#define XBAR_INST_MPU_IRQ_64            (59U)
#define XBAR_INST_MPU_IRQ_65            (60U)
#define XBAR_INST_MPU_IRQ_66            (61U)
#define XBAR_INST_MPU_IRQ_67            (62U)
#define XBAR_INST_MPU_IRQ_68            (63U)
#define XBAR_INST_MPU_IRQ_69            (64U)
#define XBAR_INST_MPU_IRQ_70            (65U)
#define XBAR_INST_MPU_IRQ_71            (66U)
#define XBAR_INST_MPU_IRQ_72            (67U)
#define XBAR_INST_MPU_IRQ_73            (68U)
#define XBAR_INST_MPU_IRQ_74            (69U)
#define XBAR_INST_MPU_IRQ_75            (70U)
#define XBAR_INST_MPU_IRQ_76            (71U)
#define XBAR_INST_MPU_IRQ_77            (72U)
#define XBAR_INST_MPU_IRQ_78            (73U)
#define XBAR_INST_MPU_IRQ_79            (74U)
#define XBAR_INST_MPU_IRQ_80            (75U)
#define XBAR_INST_MPU_IRQ_81            (76U)
#define XBAR_INST_MPU_IRQ_82            (77U)
#define XBAR_INST_MPU_IRQ_83            (78U)
#define XBAR_INST_MPU_IRQ_84            (79U)
#define XBAR_INST_MPU_IRQ_85            (80U)
#define XBAR_INST_MPU_IRQ_86            (81U)
#define XBAR_INST_MPU_IRQ_87            (82U)
#define XBAR_INST_MPU_IRQ_88            (83U)
#define XBAR_INST_MPU_IRQ_89            (84U)
#define XBAR_INST_MPU_IRQ_90            (85U)
#define XBAR_INST_MPU_IRQ_91            (86U)
#define XBAR_INST_MPU_IRQ_92            (87U)
#define XBAR_INST_MPU_IRQ_93            (88U)
#define XBAR_INST_MPU_IRQ_94            (89U)
#define XBAR_INST_MPU_IRQ_95            (90U)
#define XBAR_INST_MPU_IRQ_96            (91U)
#define XBAR_INST_MPU_IRQ_97            (92U)
#define XBAR_INST_MPU_IRQ_98            (93U)
#define XBAR_INST_MPU_IRQ_99            (94U)
#define XBAR_INST_MPU_IRQ_100           (95U)
#define XBAR_INST_MPU_IRQ_101           (96U)
#define XBAR_INST_MPU_IRQ_102           (97U)
#define XBAR_INST_MPU_IRQ_103           (98U)
#define XBAR_INST_MPU_IRQ_104           (99U)
#define XBAR_INST_MPU_IRQ_105           (100U)
#define XBAR_INST_MPU_IRQ_106           (101U)
#define XBAR_INST_MPU_IRQ_107           (102U)
#define XBAR_INST_MPU_IRQ_108           (103U)
#define XBAR_INST_MPU_IRQ_109           (104U)
#define XBAR_INST_MPU_IRQ_110           (105U)
#define XBAR_INST_MPU_IRQ_111           (106U)
#define XBAR_INST_MPU_IRQ_112           (107U)
#define XBAR_INST_MPU_IRQ_113           (108U)
#define XBAR_INST_MPU_IRQ_114           (109U)
#define XBAR_INST_MPU_IRQ_115           (110U)
#define XBAR_INST_MPU_IRQ_116           (111U)
#define XBAR_INST_MPU_IRQ_117           (112U)
#define XBAR_INST_MPU_IRQ_118           (113U)
#define XBAR_INST_MPU_IRQ_119           (114U)
#define XBAR_INST_MPU_IRQ_120           (115U)
#define XBAR_INST_MPU_IRQ_121           (116U)
#define XBAR_INST_MPU_IRQ_122           (117U)
#define XBAR_INST_MPU_IRQ_123           (118U)
#define XBAR_INST_MPU_IRQ_124           (119U)
#define XBAR_INST_MPU_IRQ_125           (120U)
#define XBAR_INST_MPU_IRQ_126           (121U)
#define XBAR_INST_MPU_IRQ_127           (122U)
#define XBAR_INST_MPU_IRQ_128           (123U)
#define XBAR_INST_MPU_IRQ_129           (124U)
#define XBAR_INST_MPU_IRQ_130           (125U)
#define XBAR_INST_MPU_IRQ_133           (126U)
#define XBAR_INST_MPU_IRQ_134           (127U)
#define XBAR_INST_MPU_IRQ_135           (128U)
#define XBAR_INST_MPU_IRQ_136           (129U)
#define XBAR_INST_MPU_IRQ_137           (130U)
#define XBAR_INST_MPU_IRQ_138           (131U)
#define XBAR_INST_MPU_IRQ_141           (134U)
#define XBAR_INST_MPU_IRQ_142           (135U)
#define XBAR_INST_MPU_IRQ_143           (136U)
#define XBAR_INST_MPU_IRQ_144           (137U)
#define XBAR_INST_MPU_IRQ_145           (138U)
#define XBAR_INST_MPU_IRQ_146           (139U)
#define XBAR_INST_MPU_IRQ_147           (140U)
#define XBAR_INST_MPU_IRQ_148           (141U)
#define XBAR_INST_MPU_IRQ_149           (142U)
#define XBAR_INST_MPU_IRQ_150           (143U)
#define XBAR_INST_MPU_IRQ_151           (144U)
#define XBAR_INST_MPU_IRQ_152           (145U)
#define XBAR_INST_MPU_IRQ_153           (146U)
#define XBAR_INST_MPU_IRQ_154           (147U)
#define XBAR_INST_MPU_IRQ_155           (148U)
#define XBAR_INST_MPU_IRQ_156           (149U)
#define XBAR_INST_MPU_IRQ_157           (150U)
#define XBAR_INST_MPU_IRQ_158           (151U)
#define XBAR_INST_MPU_IRQ_159           (152U)

/* IRQ XBAR Mapping for DSP1 */
#define XBAR_INST_DSP1_IRQ_32           (1U)
#define XBAR_INST_DSP1_IRQ_33           (2U)
#define XBAR_INST_DSP1_IRQ_34           (3U)
#define XBAR_INST_DSP1_IRQ_35           (4U)
#define XBAR_INST_DSP1_IRQ_36           (5U)
#define XBAR_INST_DSP1_IRQ_37           (6U)
#define XBAR_INST_DSP1_IRQ_38           (7U)
#define XBAR_INST_DSP1_IRQ_39           (8U)
#define XBAR_INST_DSP1_IRQ_40           (9U)
#define XBAR_INST_DSP1_IRQ_41           (10U)
#define XBAR_INST_DSP1_IRQ_42           (11U)
#define XBAR_INST_DSP1_IRQ_43           (12U)
#define XBAR_INST_DSP1_IRQ_44           (13U)
#define XBAR_INST_DSP1_IRQ_45           (14U)
#define XBAR_INST_DSP1_IRQ_46           (15U)
#define XBAR_INST_DSP1_IRQ_47           (16U)
#define XBAR_INST_DSP1_IRQ_48           (17U)
#define XBAR_INST_DSP1_IRQ_49           (18U)
#define XBAR_INST_DSP1_IRQ_50           (19U)
#define XBAR_INST_DSP1_IRQ_51           (20U)
#define XBAR_INST_DSP1_IRQ_52           (21U)
#define XBAR_INST_DSP1_IRQ_53           (22U)
#define XBAR_INST_DSP1_IRQ_54           (23U)
#define XBAR_INST_DSP1_IRQ_55           (24U)
#define XBAR_INST_DSP1_IRQ_56           (25U)
#define XBAR_INST_DSP1_IRQ_57           (26U)
#define XBAR_INST_DSP1_IRQ_58           (27U)
#define XBAR_INST_DSP1_IRQ_59           (28U)
#define XBAR_INST_DSP1_IRQ_60           (29U)
#define XBAR_INST_DSP1_IRQ_61           (30U)
#define XBAR_INST_DSP1_IRQ_62           (31U)
#define XBAR_INST_DSP1_IRQ_63           (32U)
#define XBAR_INST_DSP1_IRQ_64           (33U)
#define XBAR_INST_DSP1_IRQ_65           (34U)
#define XBAR_INST_DSP1_IRQ_66           (35U)
#define XBAR_INST_DSP1_IRQ_67           (36U)
#define XBAR_INST_DSP1_IRQ_68           (37U)
#define XBAR_INST_DSP1_IRQ_69           (38U)
#define XBAR_INST_DSP1_IRQ_70           (39U)
#define XBAR_INST_DSP1_IRQ_71           (40U)
#define XBAR_INST_DSP1_IRQ_72           (41U)
#define XBAR_INST_DSP1_IRQ_73           (42U)
#define XBAR_INST_DSP1_IRQ_74           (43U)
#define XBAR_INST_DSP1_IRQ_75           (44U)
#define XBAR_INST_DSP1_IRQ_76           (45U)
#define XBAR_INST_DSP1_IRQ_77           (46U)
#define XBAR_INST_DSP1_IRQ_78           (47U)
#define XBAR_INST_DSP1_IRQ_79           (48U)
#define XBAR_INST_DSP1_IRQ_80           (49U)
#define XBAR_INST_DSP1_IRQ_81           (50U)
#define XBAR_INST_DSP1_IRQ_82           (51U)
#define XBAR_INST_DSP1_IRQ_83           (52U)
#define XBAR_INST_DSP1_IRQ_84           (53U)
#define XBAR_INST_DSP1_IRQ_85           (54U)
#define XBAR_INST_DSP1_IRQ_86           (55U)
#define XBAR_INST_DSP1_IRQ_87           (56U)
#define XBAR_INST_DSP1_IRQ_88           (57U)
#define XBAR_INST_DSP1_IRQ_89           (58U)
#define XBAR_INST_DSP1_IRQ_90           (59U)
#define XBAR_INST_DSP1_IRQ_91           (60U)
#define XBAR_INST_DSP1_IRQ_92           (61U)
#define XBAR_INST_DSP1_IRQ_93           (62U)
#define XBAR_INST_DSP1_IRQ_94           (63U)
#define XBAR_INST_DSP1_IRQ_95           (64U)

#ifndef TDA2EX_BUILD
/* IRQ XBAR Mapping for DSP2 */
#define XBAR_INST_DSP2_IRQ_32           (1U)
#define XBAR_INST_DSP2_IRQ_33           (2U)
#define XBAR_INST_DSP2_IRQ_34           (3U)
#define XBAR_INST_DSP2_IRQ_35           (4U)
#define XBAR_INST_DSP2_IRQ_36           (5U)
#define XBAR_INST_DSP2_IRQ_37           (6U)
#define XBAR_INST_DSP2_IRQ_38           (7U)
#define XBAR_INST_DSP2_IRQ_39           (8U)
#define XBAR_INST_DSP2_IRQ_40           (9U)
#define XBAR_INST_DSP2_IRQ_41           (10U)
#define XBAR_INST_DSP2_IRQ_42           (11U)
#define XBAR_INST_DSP2_IRQ_43           (12U)
#define XBAR_INST_DSP2_IRQ_44           (13U)
#define XBAR_INST_DSP2_IRQ_45           (14U)
#define XBAR_INST_DSP2_IRQ_46           (15U)
#define XBAR_INST_DSP2_IRQ_47           (16U)
#define XBAR_INST_DSP2_IRQ_48           (17U)
#define XBAR_INST_DSP2_IRQ_49           (18U)
#define XBAR_INST_DSP2_IRQ_50           (19U)
#define XBAR_INST_DSP2_IRQ_51           (20U)
#define XBAR_INST_DSP2_IRQ_52           (21U)
#define XBAR_INST_DSP2_IRQ_53           (22U)
#define XBAR_INST_DSP2_IRQ_54           (23U)
#define XBAR_INST_DSP2_IRQ_55           (24U)
#define XBAR_INST_DSP2_IRQ_56           (25U)
#define XBAR_INST_DSP2_IRQ_57           (26U)
#define XBAR_INST_DSP2_IRQ_58           (27U)
#define XBAR_INST_DSP2_IRQ_59           (28U)
#define XBAR_INST_DSP2_IRQ_60           (29U)
#define XBAR_INST_DSP2_IRQ_61           (30U)
#define XBAR_INST_DSP2_IRQ_62           (31U)
#define XBAR_INST_DSP2_IRQ_63           (32U)
#define XBAR_INST_DSP2_IRQ_64           (33U)
#define XBAR_INST_DSP2_IRQ_65           (34U)
#define XBAR_INST_DSP2_IRQ_66           (35U)
#define XBAR_INST_DSP2_IRQ_67           (36U)
#define XBAR_INST_DSP2_IRQ_68           (37U)
#define XBAR_INST_DSP2_IRQ_69           (38U)
#define XBAR_INST_DSP2_IRQ_70           (39U)
#define XBAR_INST_DSP2_IRQ_71           (40U)
#define XBAR_INST_DSP2_IRQ_72           (41U)
#define XBAR_INST_DSP2_IRQ_73           (42U)
#define XBAR_INST_DSP2_IRQ_74           (43U)
#define XBAR_INST_DSP2_IRQ_75           (44U)
#define XBAR_INST_DSP2_IRQ_76           (45U)
#define XBAR_INST_DSP2_IRQ_77           (46U)
#define XBAR_INST_DSP2_IRQ_78           (47U)
#define XBAR_INST_DSP2_IRQ_79           (48U)
#define XBAR_INST_DSP2_IRQ_80           (49U)
#define XBAR_INST_DSP2_IRQ_81           (50U)
#define XBAR_INST_DSP2_IRQ_82           (51U)
#define XBAR_INST_DSP2_IRQ_83           (52U)
#define XBAR_INST_DSP2_IRQ_84           (53U)
#define XBAR_INST_DSP2_IRQ_85           (54U)
#define XBAR_INST_DSP2_IRQ_86           (55U)
#define XBAR_INST_DSP2_IRQ_87           (56U)
#define XBAR_INST_DSP2_IRQ_88           (57U)
#define XBAR_INST_DSP2_IRQ_89           (58U)
#define XBAR_INST_DSP2_IRQ_90           (59U)
#define XBAR_INST_DSP2_IRQ_91           (60U)
#define XBAR_INST_DSP2_IRQ_92           (61U)
#define XBAR_INST_DSP2_IRQ_93           (62U)
#define XBAR_INST_DSP2_IRQ_94           (63U)
#define XBAR_INST_DSP2_IRQ_95           (64U)
#endif

/* IRQ XBAR Mapping for IPU1 */
#define XBAR_INST_IPU1_IRQ_23           (1U)
#define XBAR_INST_IPU1_IRQ_24           (2U)
#define XBAR_INST_IPU1_IRQ_25           (3U)
#define XBAR_INST_IPU1_IRQ_26           (4U)
#define XBAR_INST_IPU1_IRQ_27           (5U)
#define XBAR_INST_IPU1_IRQ_28           (6U)
#define XBAR_INST_IPU1_IRQ_29           (7U)
#define XBAR_INST_IPU1_IRQ_30           (8U)
#define XBAR_INST_IPU1_IRQ_31           (9U)
#define XBAR_INST_IPU1_IRQ_32           (10U)
#define XBAR_INST_IPU1_IRQ_33           (11U)
#define XBAR_INST_IPU1_IRQ_34           (12U)
#define XBAR_INST_IPU1_IRQ_35           (13U)
#define XBAR_INST_IPU1_IRQ_36           (14U)
#define XBAR_INST_IPU1_IRQ_37           (15U)
#define XBAR_INST_IPU1_IRQ_38           (16U)
#define XBAR_INST_IPU1_IRQ_39           (17U)
#define XBAR_INST_IPU1_IRQ_40           (18U)
#define XBAR_INST_IPU1_IRQ_41           (19U)
#define XBAR_INST_IPU1_IRQ_42           (20U)
#define XBAR_INST_IPU1_IRQ_43           (21U)
#define XBAR_INST_IPU1_IRQ_44           (22U)
#define XBAR_INST_IPU1_IRQ_45           (23U)
#define XBAR_INST_IPU1_IRQ_46           (24U)
#define XBAR_INST_IPU1_IRQ_47           (25U)
#define XBAR_INST_IPU1_IRQ_48           (26U)
#define XBAR_INST_IPU1_IRQ_49           (27U)
#define XBAR_INST_IPU1_IRQ_50           (28U)
#define XBAR_INST_IPU1_IRQ_51           (29U)
#define XBAR_INST_IPU1_IRQ_52           (30U)
#define XBAR_INST_IPU1_IRQ_53           (31U)
#define XBAR_INST_IPU1_IRQ_54           (32U)
#define XBAR_INST_IPU1_IRQ_55           (33U)
#define XBAR_INST_IPU1_IRQ_56           (34U)
#define XBAR_INST_IPU1_IRQ_57           (35U)
#define XBAR_INST_IPU1_IRQ_58           (36U)
#define XBAR_INST_IPU1_IRQ_59           (37U)
#define XBAR_INST_IPU1_IRQ_60           (38U)
#define XBAR_INST_IPU1_IRQ_61           (39U)
#define XBAR_INST_IPU1_IRQ_62           (40U)
#define XBAR_INST_IPU1_IRQ_63           (41U)
#define XBAR_INST_IPU1_IRQ_64           (42U)
#define XBAR_INST_IPU1_IRQ_65           (43U)
#define XBAR_INST_IPU1_IRQ_66           (44U)
#define XBAR_INST_IPU1_IRQ_67           (45U)
#define XBAR_INST_IPU1_IRQ_68           (46U)
#define XBAR_INST_IPU1_IRQ_69           (47U)
#define XBAR_INST_IPU1_IRQ_70           (48U)
#define XBAR_INST_IPU1_IRQ_71           (49U)
#define XBAR_INST_IPU1_IRQ_72           (50U)
#define XBAR_INST_IPU1_IRQ_73           (51U)
#define XBAR_INST_IPU1_IRQ_74           (52U)
#define XBAR_INST_IPU1_IRQ_75           (53U)
#define XBAR_INST_IPU1_IRQ_76           (54U)
#define XBAR_INST_IPU1_IRQ_77           (55U)
#define XBAR_INST_IPU1_IRQ_78           (56U)
#define XBAR_INST_IPU1_IRQ_79           (57U)

/* IRQ XBAR Mapping for IPU2 */
#define XBAR_INST_IPU2_IRQ_23           (1U)
#define XBAR_INST_IPU2_IRQ_24           (2U)
#define XBAR_INST_IPU2_IRQ_25           (3U)
#define XBAR_INST_IPU2_IRQ_26           (4U)
#define XBAR_INST_IPU2_IRQ_27           (5U)
#define XBAR_INST_IPU2_IRQ_28           (6U)
#define XBAR_INST_IPU2_IRQ_29           (7U)
#define XBAR_INST_IPU2_IRQ_30           (8U)
#define XBAR_INST_IPU2_IRQ_31           (9U)
#define XBAR_INST_IPU2_IRQ_32           (10U)
#define XBAR_INST_IPU2_IRQ_33           (11U)
#define XBAR_INST_IPU2_IRQ_34           (12U)
#define XBAR_INST_IPU2_IRQ_35           (13U)
#define XBAR_INST_IPU2_IRQ_36           (14U)
#define XBAR_INST_IPU2_IRQ_37           (15U)
#define XBAR_INST_IPU2_IRQ_38           (16U)
#define XBAR_INST_IPU2_IRQ_39           (17U)
#define XBAR_INST_IPU2_IRQ_40           (18U)
#define XBAR_INST_IPU2_IRQ_41           (19U)
#define XBAR_INST_IPU2_IRQ_42           (20U)
#define XBAR_INST_IPU2_IRQ_43           (21U)
#define XBAR_INST_IPU2_IRQ_44           (22U)
#define XBAR_INST_IPU2_IRQ_45           (23U)
#define XBAR_INST_IPU2_IRQ_46           (24U)
#define XBAR_INST_IPU2_IRQ_47           (25U)
#define XBAR_INST_IPU2_IRQ_48           (26U)
#define XBAR_INST_IPU2_IRQ_49           (27U)
#define XBAR_INST_IPU2_IRQ_50           (28U)
#define XBAR_INST_IPU2_IRQ_51           (29U)
#define XBAR_INST_IPU2_IRQ_52           (30U)
#define XBAR_INST_IPU2_IRQ_53           (31U)
#define XBAR_INST_IPU2_IRQ_54           (32U)
#define XBAR_INST_IPU2_IRQ_55           (33U)
#define XBAR_INST_IPU2_IRQ_56           (34U)
#define XBAR_INST_IPU2_IRQ_57           (35U)
#define XBAR_INST_IPU2_IRQ_58           (36U)
#define XBAR_INST_IPU2_IRQ_59           (37U)
#define XBAR_INST_IPU2_IRQ_60           (38U)
#define XBAR_INST_IPU2_IRQ_61           (39U)
#define XBAR_INST_IPU2_IRQ_62           (40U)
#define XBAR_INST_IPU2_IRQ_63           (41U)
#define XBAR_INST_IPU2_IRQ_64           (42U)
#define XBAR_INST_IPU2_IRQ_65           (43U)
#define XBAR_INST_IPU2_IRQ_66           (44U)
#define XBAR_INST_IPU2_IRQ_67           (45U)
#define XBAR_INST_IPU2_IRQ_68           (46U)
#define XBAR_INST_IPU2_IRQ_69           (47U)
#define XBAR_INST_IPU2_IRQ_70           (48U)
#define XBAR_INST_IPU2_IRQ_71           (49U)
#define XBAR_INST_IPU2_IRQ_72           (50U)
#define XBAR_INST_IPU2_IRQ_73           (51U)
#define XBAR_INST_IPU2_IRQ_74           (52U)
#define XBAR_INST_IPU2_IRQ_75           (53U)
#define XBAR_INST_IPU2_IRQ_76           (54U)
#define XBAR_INST_IPU2_IRQ_77           (55U)
#define XBAR_INST_IPU2_IRQ_78           (56U)
#define XBAR_INST_IPU2_IRQ_79           (57U)

/******************************************************************************
 * DMA XBAR instance mapping for each DMA instances.
 * This is the DMA XBAR instance to which a particular DMA event is
 * mapped. This macro could be used to pass the DMA XBAR instance to the DMA
 * XBAR connect API of starterware.
 ******************************************************************************/
/* DMA XBAR Mapping for System DMA */
#define XBAR_INST_DMA_SYSTEM_DREQ_0     (1U)
#define XBAR_INST_DMA_SYSTEM_DREQ_1     (2U)
#define XBAR_INST_DMA_SYSTEM_DREQ_2     (3U)
#define XBAR_INST_DMA_SYSTEM_DREQ_3     (4U)
#define XBAR_INST_DMA_SYSTEM_DREQ_4     (5U)
#define XBAR_INST_DMA_SYSTEM_DREQ_5     (6U)
#define XBAR_INST_DMA_SYSTEM_DREQ_6     (7U)
#define XBAR_INST_DMA_SYSTEM_DREQ_7     (8U)
#define XBAR_INST_DMA_SYSTEM_DREQ_8     (9U)
#define XBAR_INST_DMA_SYSTEM_DREQ_9     (10U)
#define XBAR_INST_DMA_SYSTEM_DREQ_10    (11U)
#define XBAR_INST_DMA_SYSTEM_DREQ_11    (12U)
#define XBAR_INST_DMA_SYSTEM_DREQ_12    (13U)
#define XBAR_INST_DMA_SYSTEM_DREQ_13    (14U)
#define XBAR_INST_DMA_SYSTEM_DREQ_14    (15U)
#define XBAR_INST_DMA_SYSTEM_DREQ_15    (16U)
#define XBAR_INST_DMA_SYSTEM_DREQ_16    (17U)
#define XBAR_INST_DMA_SYSTEM_DREQ_17    (18U)
#define XBAR_INST_DMA_SYSTEM_DREQ_18    (19U)
#define XBAR_INST_DMA_SYSTEM_DREQ_19    (20U)
#define XBAR_INST_DMA_SYSTEM_DREQ_20    (21U)
#define XBAR_INST_DMA_SYSTEM_DREQ_21    (22U)
#define XBAR_INST_DMA_SYSTEM_DREQ_22    (23U)
#define XBAR_INST_DMA_SYSTEM_DREQ_23    (24U)
#define XBAR_INST_DMA_SYSTEM_DREQ_24    (25U)
#define XBAR_INST_DMA_SYSTEM_DREQ_25    (26U)
#define XBAR_INST_DMA_SYSTEM_DREQ_26    (27U)
#define XBAR_INST_DMA_SYSTEM_DREQ_27    (28U)
#define XBAR_INST_DMA_SYSTEM_DREQ_28    (29U)
#define XBAR_INST_DMA_SYSTEM_DREQ_29    (30U)
#define XBAR_INST_DMA_SYSTEM_DREQ_30    (31U)
#define XBAR_INST_DMA_SYSTEM_DREQ_31    (32U)
#define XBAR_INST_DMA_SYSTEM_DREQ_32    (33U)
#define XBAR_INST_DMA_SYSTEM_DREQ_33    (34U)
#define XBAR_INST_DMA_SYSTEM_DREQ_34    (35U)
#define XBAR_INST_DMA_SYSTEM_DREQ_35    (36U)
#define XBAR_INST_DMA_SYSTEM_DREQ_36    (37U)
#define XBAR_INST_DMA_SYSTEM_DREQ_37    (38U)
#define XBAR_INST_DMA_SYSTEM_DREQ_38    (39U)
#define XBAR_INST_DMA_SYSTEM_DREQ_39    (40U)
#define XBAR_INST_DMA_SYSTEM_DREQ_40    (41U)
#define XBAR_INST_DMA_SYSTEM_DREQ_41    (42U)
#define XBAR_INST_DMA_SYSTEM_DREQ_42    (43U)
#define XBAR_INST_DMA_SYSTEM_DREQ_43    (44U)
#define XBAR_INST_DMA_SYSTEM_DREQ_44    (45U)
#define XBAR_INST_DMA_SYSTEM_DREQ_45    (46U)
#define XBAR_INST_DMA_SYSTEM_DREQ_46    (47U)
#define XBAR_INST_DMA_SYSTEM_DREQ_47    (48U)
#define XBAR_INST_DMA_SYSTEM_DREQ_48    (49U)
#define XBAR_INST_DMA_SYSTEM_DREQ_49    (50U)
#define XBAR_INST_DMA_SYSTEM_DREQ_50    (51U)
#define XBAR_INST_DMA_SYSTEM_DREQ_51    (52U)
#define XBAR_INST_DMA_SYSTEM_DREQ_52    (53U)
#define XBAR_INST_DMA_SYSTEM_DREQ_53    (54U)
#define XBAR_INST_DMA_SYSTEM_DREQ_54    (55U)
#define XBAR_INST_DMA_SYSTEM_DREQ_55    (56U)
#define XBAR_INST_DMA_SYSTEM_DREQ_56    (57U)
#define XBAR_INST_DMA_SYSTEM_DREQ_57    (58U)
#define XBAR_INST_DMA_SYSTEM_DREQ_58    (59U)
#define XBAR_INST_DMA_SYSTEM_DREQ_59    (60U)
#define XBAR_INST_DMA_SYSTEM_DREQ_60    (61U)
#define XBAR_INST_DMA_SYSTEM_DREQ_61    (62U)
#define XBAR_INST_DMA_SYSTEM_DREQ_62    (63U)
#define XBAR_INST_DMA_SYSTEM_DREQ_63    (64U)
#define XBAR_INST_DMA_SYSTEM_DREQ_64    (65U)
#define XBAR_INST_DMA_SYSTEM_DREQ_65    (66U)
#define XBAR_INST_DMA_SYSTEM_DREQ_66    (67U)
#define XBAR_INST_DMA_SYSTEM_DREQ_67    (68U)
#define XBAR_INST_DMA_SYSTEM_DREQ_68    (69U)
#define XBAR_INST_DMA_SYSTEM_DREQ_69    (70U)
#define XBAR_INST_DMA_SYSTEM_DREQ_70    (71U)
#define XBAR_INST_DMA_SYSTEM_DREQ_71    (72U)
#define XBAR_INST_DMA_SYSTEM_DREQ_72    (73U)
#define XBAR_INST_DMA_SYSTEM_DREQ_73    (74U)
#define XBAR_INST_DMA_SYSTEM_DREQ_74    (75U)
#define XBAR_INST_DMA_SYSTEM_DREQ_75    (76U)
#define XBAR_INST_DMA_SYSTEM_DREQ_76    (77U)
#define XBAR_INST_DMA_SYSTEM_DREQ_77    (78U)
#define XBAR_INST_DMA_SYSTEM_DREQ_78    (79U)
#define XBAR_INST_DMA_SYSTEM_DREQ_79    (80U)
#define XBAR_INST_DMA_SYSTEM_DREQ_80    (81U)
#define XBAR_INST_DMA_SYSTEM_DREQ_81    (82U)
#define XBAR_INST_DMA_SYSTEM_DREQ_82    (83U)
#define XBAR_INST_DMA_SYSTEM_DREQ_83    (84U)
#define XBAR_INST_DMA_SYSTEM_DREQ_84    (85U)
#define XBAR_INST_DMA_SYSTEM_DREQ_85    (86U)
#define XBAR_INST_DMA_SYSTEM_DREQ_86    (87U)
#define XBAR_INST_DMA_SYSTEM_DREQ_87    (88U)
#define XBAR_INST_DMA_SYSTEM_DREQ_88    (89U)
#define XBAR_INST_DMA_SYSTEM_DREQ_89    (90U)
#define XBAR_INST_DMA_SYSTEM_DREQ_90    (91U)
#define XBAR_INST_DMA_SYSTEM_DREQ_91    (92U)
#define XBAR_INST_DMA_SYSTEM_DREQ_92    (93U)
#define XBAR_INST_DMA_SYSTEM_DREQ_93    (94U)
#define XBAR_INST_DMA_SYSTEM_DREQ_94    (95U)
#define XBAR_INST_DMA_SYSTEM_DREQ_95    (96U)
#define XBAR_INST_DMA_SYSTEM_DREQ_96    (97U)
#define XBAR_INST_DMA_SYSTEM_DREQ_97    (98U)
#define XBAR_INST_DMA_SYSTEM_DREQ_98    (99U)
#define XBAR_INST_DMA_SYSTEM_DREQ_99    (100U)
#define XBAR_INST_DMA_SYSTEM_DREQ_100   (101U)
#define XBAR_INST_DMA_SYSTEM_DREQ_101   (102U)
#define XBAR_INST_DMA_SYSTEM_DREQ_102   (103U)
#define XBAR_INST_DMA_SYSTEM_DREQ_103   (104U)
#define XBAR_INST_DMA_SYSTEM_DREQ_104   (105U)
#define XBAR_INST_DMA_SYSTEM_DREQ_105   (106U)
#define XBAR_INST_DMA_SYSTEM_DREQ_106   (107U)
#define XBAR_INST_DMA_SYSTEM_DREQ_107   (108U)
#define XBAR_INST_DMA_SYSTEM_DREQ_108   (109U)
#define XBAR_INST_DMA_SYSTEM_DREQ_109   (110U)
#define XBAR_INST_DMA_SYSTEM_DREQ_110   (111U)
#define XBAR_INST_DMA_SYSTEM_DREQ_111   (112U)
#define XBAR_INST_DMA_SYSTEM_DREQ_112   (113U)
#define XBAR_INST_DMA_SYSTEM_DREQ_113   (114U)
#define XBAR_INST_DMA_SYSTEM_DREQ_114   (115U)
#define XBAR_INST_DMA_SYSTEM_DREQ_115   (116U)
#define XBAR_INST_DMA_SYSTEM_DREQ_116   (117U)
#define XBAR_INST_DMA_SYSTEM_DREQ_117   (118U)
#define XBAR_INST_DMA_SYSTEM_DREQ_118   (119U)
#define XBAR_INST_DMA_SYSTEM_DREQ_119   (120U)
#define XBAR_INST_DMA_SYSTEM_DREQ_120   (121U)
#define XBAR_INST_DMA_SYSTEM_DREQ_121   (122U)
#define XBAR_INST_DMA_SYSTEM_DREQ_122   (123U)
#define XBAR_INST_DMA_SYSTEM_DREQ_123   (124U)
#define XBAR_INST_DMA_SYSTEM_DREQ_124   (125U)
#define XBAR_INST_DMA_SYSTEM_DREQ_125   (126U)
#define XBAR_INST_DMA_SYSTEM_DREQ_126   (127U)

/* DMA XBAR Mapping for EDMA3 DMA */
#define XBAR_INST_DMA_EDMA_DREQ_0       (1U)
#define XBAR_INST_DMA_EDMA_DREQ_1       (2U)
#define XBAR_INST_DMA_EDMA_DREQ_2       (3U)
#define XBAR_INST_DMA_EDMA_DREQ_3       (4U)
#define XBAR_INST_DMA_EDMA_DREQ_4       (5U)
#define XBAR_INST_DMA_EDMA_DREQ_5       (6U)
#define XBAR_INST_DMA_EDMA_DREQ_6       (7U)
#define XBAR_INST_DMA_EDMA_DREQ_7       (8U)
#define XBAR_INST_DMA_EDMA_DREQ_8       (9U)
#define XBAR_INST_DMA_EDMA_DREQ_9       (10U)
#define XBAR_INST_DMA_EDMA_DREQ_10      (11U)
#define XBAR_INST_DMA_EDMA_DREQ_11      (12U)
#define XBAR_INST_DMA_EDMA_DREQ_12      (13U)
#define XBAR_INST_DMA_EDMA_DREQ_13      (14U)
#define XBAR_INST_DMA_EDMA_DREQ_14      (15U)
#define XBAR_INST_DMA_EDMA_DREQ_15      (16U)
#define XBAR_INST_DMA_EDMA_DREQ_16      (17U)
#define XBAR_INST_DMA_EDMA_DREQ_17      (18U)
#define XBAR_INST_DMA_EDMA_DREQ_18      (19U)
#define XBAR_INST_DMA_EDMA_DREQ_19      (20U)
#define XBAR_INST_DMA_EDMA_DREQ_20      (21U)
#define XBAR_INST_DMA_EDMA_DREQ_21      (22U)
#define XBAR_INST_DMA_EDMA_DREQ_22      (23U)
#define XBAR_INST_DMA_EDMA_DREQ_23      (24U)
#define XBAR_INST_DMA_EDMA_DREQ_24      (25U)
#define XBAR_INST_DMA_EDMA_DREQ_25      (26U)
#define XBAR_INST_DMA_EDMA_DREQ_26      (27U)
#define XBAR_INST_DMA_EDMA_DREQ_27      (28U)
#define XBAR_INST_DMA_EDMA_DREQ_28      (29U)
#define XBAR_INST_DMA_EDMA_DREQ_29      (30U)
#define XBAR_INST_DMA_EDMA_DREQ_30      (31U)
#define XBAR_INST_DMA_EDMA_DREQ_31      (32U)
#define XBAR_INST_DMA_EDMA_DREQ_32      (33U)
#define XBAR_INST_DMA_EDMA_DREQ_33      (34U)
#define XBAR_INST_DMA_EDMA_DREQ_34      (35U)
#define XBAR_INST_DMA_EDMA_DREQ_35      (36U)
#define XBAR_INST_DMA_EDMA_DREQ_36      (37U)
#define XBAR_INST_DMA_EDMA_DREQ_37      (38U)
#define XBAR_INST_DMA_EDMA_DREQ_38      (39U)
#define XBAR_INST_DMA_EDMA_DREQ_39      (40U)
#define XBAR_INST_DMA_EDMA_DREQ_40      (41U)
#define XBAR_INST_DMA_EDMA_DREQ_41      (42U)
#define XBAR_INST_DMA_EDMA_DREQ_42      (43U)
#define XBAR_INST_DMA_EDMA_DREQ_43      (44U)
#define XBAR_INST_DMA_EDMA_DREQ_44      (45U)
#define XBAR_INST_DMA_EDMA_DREQ_45      (46U)
#define XBAR_INST_DMA_EDMA_DREQ_46      (47U)
#define XBAR_INST_DMA_EDMA_DREQ_47      (48U)
#define XBAR_INST_DMA_EDMA_DREQ_48      (49U)
#define XBAR_INST_DMA_EDMA_DREQ_49      (50U)
#define XBAR_INST_DMA_EDMA_DREQ_50      (51U)
#define XBAR_INST_DMA_EDMA_DREQ_51      (52U)
#define XBAR_INST_DMA_EDMA_DREQ_52      (53U)
#define XBAR_INST_DMA_EDMA_DREQ_53      (54U)
#define XBAR_INST_DMA_EDMA_DREQ_54      (55U)
#define XBAR_INST_DMA_EDMA_DREQ_55      (56U)
#define XBAR_INST_DMA_EDMA_DREQ_56      (57U)
#define XBAR_INST_DMA_EDMA_DREQ_57      (58U)
#define XBAR_INST_DMA_EDMA_DREQ_58      (59U)
#define XBAR_INST_DMA_EDMA_DREQ_59      (60U)
#define XBAR_INST_DMA_EDMA_DREQ_60      (61U)
#define XBAR_INST_DMA_EDMA_DREQ_61      (62U)
#define XBAR_INST_DMA_EDMA_DREQ_62      (63U)
#define XBAR_INST_DMA_EDMA_DREQ_63      (64U)

/* DMA XBAR Mapping for DSP1 DMA */
#define XBAR_INST_DMA_DSP1_DREQ_0       (1U)
#define XBAR_INST_DMA_DSP1_DREQ_1       (2U)
#define XBAR_INST_DMA_DSP1_DREQ_2       (3U)
#define XBAR_INST_DMA_DSP1_DREQ_3       (4U)
#define XBAR_INST_DMA_DSP1_DREQ_4       (5U)
#define XBAR_INST_DMA_DSP1_DREQ_5       (6U)
#define XBAR_INST_DMA_DSP1_DREQ_6       (7U)
#define XBAR_INST_DMA_DSP1_DREQ_7       (8U)
#define XBAR_INST_DMA_DSP1_DREQ_8       (9U)
#define XBAR_INST_DMA_DSP1_DREQ_9       (10U)
#define XBAR_INST_DMA_DSP1_DREQ_10      (11U)
#define XBAR_INST_DMA_DSP1_DREQ_11      (12U)
#define XBAR_INST_DMA_DSP1_DREQ_12      (13U)
#define XBAR_INST_DMA_DSP1_DREQ_13      (14U)
#define XBAR_INST_DMA_DSP1_DREQ_14      (15U)
#define XBAR_INST_DMA_DSP1_DREQ_15      (16U)
#define XBAR_INST_DMA_DSP1_DREQ_16      (17U)
#define XBAR_INST_DMA_DSP1_DREQ_17      (18U)
#define XBAR_INST_DMA_DSP1_DREQ_18      (19U)
#define XBAR_INST_DMA_DSP1_DREQ_19      (20U)

#ifndef TDA2EX_BUILD
/* DMA XBAR Mapping for DSP2 DMA */
#define XBAR_INST_DMA_DSP2_DREQ_0       (1U)
#define XBAR_INST_DMA_DSP2_DREQ_1       (2U)
#define XBAR_INST_DMA_DSP2_DREQ_2       (3U)
#define XBAR_INST_DMA_DSP2_DREQ_3       (4U)
#define XBAR_INST_DMA_DSP2_DREQ_4       (5U)
#define XBAR_INST_DMA_DSP2_DREQ_5       (6U)
#define XBAR_INST_DMA_DSP2_DREQ_6       (7U)
#define XBAR_INST_DMA_DSP2_DREQ_7       (8U)
#define XBAR_INST_DMA_DSP2_DREQ_8       (9U)
#define XBAR_INST_DMA_DSP2_DREQ_9       (10U)
#define XBAR_INST_DMA_DSP2_DREQ_10      (11U)
#define XBAR_INST_DMA_DSP2_DREQ_11      (12U)
#define XBAR_INST_DMA_DSP2_DREQ_12      (13U)
#define XBAR_INST_DMA_DSP2_DREQ_13      (14U)
#define XBAR_INST_DMA_DSP2_DREQ_14      (15U)
#define XBAR_INST_DMA_DSP2_DREQ_15      (16U)
#define XBAR_INST_DMA_DSP2_DREQ_16      (17U)
#define XBAR_INST_DMA_DSP2_DREQ_17      (18U)
#define XBAR_INST_DMA_DSP2_DREQ_18      (19U)
#define XBAR_INST_DMA_DSP2_DREQ_19      (20U)
#endif

/* L3 FIREWALL */
#ifndef TDA2XX_BUILD
/* L3 Firewall Instance Summary */
#define L3FW_INST_NUM                                       (24U)

#define L3FW_DEBUGSS_CT_TBR_INST        (SOC_SECURITYCORE_DEBUGSS_CT_TBR_BASE)
#define L3FW_DSP1_SDMA_INST             (SOC_SECURITYCORE_DSP1_SDMA_BASE)
#define L3FW_DSS_INST                   (SOC_SECURITYCORE_DSS_BASE)
#define L3FW_GPMC_INST                  (SOC_SECURITYCORE_GPMC_BASE)
#define L3FW_GPU_INST                   (SOC_SECURITYCORE_GPU_BASE)
#define L3FW_IPU1_INST                  (SOC_SECURITYCORE_IPU1_BASE)
#define L3FW_IVA_CFG_INST               (SOC_SECURITYCORE_IVA1_CONFIG_BASE)
#define L3FW_IVA_SL2IF_INST             (SOC_SECURITYCORE_IVA1_SL2IF_BASE)
#define L3FW_L3_INSTR_INST              (SOC_SECURITYCORE_L3_INSTR_BASE)
#define L3FW_OCMC_RAM_INST              (SOC_SECURITYCORE_OCMC_RAM1_BASE)
#define L3FW_EMIF_INST                  (SOC_SECURITYCORE_OCP_FW_EMIF_5430_BASE)
#define L3FW_PCIESS1_INST               (SOC_SECURITYCORE_PCIE1_BASE)
#define L3FW_PRUSS1_INST                (SOC_SECURITYCORE_PRUSS1_BASE)
#define L3FW_QSPI_INST                  (SOC_SECURITYCORE_QSPI_BASE)
#define L3FW_TPCC_INST                  (SOC_SECURITYCORE_TPCC_BASE)
#define L3FW_TPTC_INST                  (SOC_SECURITYCORE_TPTC_BASE)
#define L3FW_IPU2_INST                  (SOC_SECURITYCORE_IPU2_BASE)
#define L3FW_PRUSS2_INST                (SOC_SECURITYCORE_PRUSS2_BASE)
#define L3FW_PCIESS2_INST               (SOC_SECURITYCORE_PCIE2_BASE)
#define L3FW_BB2D_INST                  (0x4A21A000U)
#define L3FW_MCASP1_INST                (SOC_SECURITYCORE_MCASP1_BASE)
#define L3FW_MCASP2_INST                (SOC_SECURITYCORE_MCASP2_BASE)
#define L3FW_MCASP3_INST                (SOC_SECURITYCORE_MCASP3_BASE)
#define L3FW_VCP_INST                   (SOC_SECURITYCORE_VCP1_BASE)

/**
 * \brief  Macro containing instance summary of L3 Firewalls.
 *         Details:
 *         Element No.  Details
 *         1            Firewall Instance
 *         2            Number of region in Firewall
 *         3            Number of ports in Firewall
 *         This macro is used to initialize struct #l3fwInstSummary_t in
 *         fwlibl3.h
 */
#define L3FW_INST_SUMMARY                  \
    {                                      \
        {L3FW_DSP1_SDMA_INST, 1U, 1U},     \
        {L3FW_DSS_INST, 8U, 1U},           \
        {L3FW_GPMC_INST, 8U, 1U},          \
        {L3FW_GPU_INST, 1U, 1U},           \
        {L3FW_IPU1_INST, 4U, 2U},          \
        {L3FW_IPU2_INST, 4U, 2U},          \
        {L3FW_PRUSS1_INST, 1U, 1U},        \
        {L3FW_PRUSS2_INST, 1U, 1U},        \
        {L3FW_IVA_CFG_INST, 1U, 1U},       \
        {L3FW_IVA_SL2IF_INST, 4U, 1U},     \
        {L3FW_OCMC_RAM_INST, 16U, 3U},     \
        {L3FW_EMIF_INST, 8U, 1U},          \
        {L3FW_PCIESS1_INST, 8U, 1U},       \
        {L3FW_PCIESS2_INST, 8U, 1U},       \
        {L3FW_BB2D_INST, 1U, 1U},          \
        {L3FW_QSPI_INST, 1U, 1U},          \
        {L3FW_TPCC_INST, 1U, 1U},          \
        {L3FW_TPTC_INST, 2U, 2U},          \
        {L3FW_VCP_INST, 1U, 1U},           \
        {L3FW_MCASP1_INST, 1U, 1U},        \
        {L3FW_MCASP2_INST, 1U, 1U},        \
        {L3FW_MCASP3_INST, 1U, 1U},        \
        {L3FW_L3_INSTR_INST, 2U, 1U},      \
        {L3FW_DEBUGSS_CT_TBR_INST, 1U, 1U} \
    }

typedef enum SocConnId
{
    SOC_CONNID_MPU           = 0x1U,
    SOC_CONNID_CS_DAP        = 0x4U,
    SOC_CONNID_DSP1_MDMA     = 0x8U,
    SOC_CONNID_DSP1_CFG      = 0x9U,
    SOC_CONNID_DSP1_DMA      = 0xAU,
    SOC_CONNID_IVA           = 0xEU,
    SOC_CONNID_PRUSS1_PRU1   = 0x14U,
    SOC_CONNID_PRUSS1_PRU2   = 0x15U,
    SOC_CONNID_PRUSS2_PRU1   = 0x16U,
    SOC_CONNID_PRUSS2_PRU2   = 0x17U,
    SOC_CONNID_IPU1          = 0x18U,
    SOC_CONNID_IPU2          = 0x19U,
    SOC_CONNID_DMA_SYSTEM_RD = 0x1AU,
    SOC_CONNID_DMA_SYSTEM_WR = 0x1AU,
    SOC_CONNID_TC1_EDMA_WR   = 0x1CU,
    SOC_CONNID_TC1_EDMA_RD   = 0x1CU,
    SOC_CONNID_TC2_EDMA_WR   = 0x1DU,
    SOC_CONNID_TC2_EDMA_RD   = 0x1DU,
    SOC_CONNID_DSS           = 0x20U,
    SOC_CONNID_MLB           = 0x21U,
    SOC_CONNID_MMU1          = 0x21U,
    SOC_CONNID_PCIE1         = 0x22U,
    SOC_CONNID_PCIE2         = 0x23U,
    SOC_CONNID_MMU2          = 0x23U,
    SOC_CONNID_VIP1_P1       = 0x24U,
    SOC_CONNID_VIP1_P2       = 0x24U,
    SOC_CONNID_CAL           = 0x25U,
    SOC_CONNID_VPE_P1        = 0x27U,
    SOC_CONNID_VPE_P2        = 0x27U,
    SOC_CONNID_MMC1          = 0x28U,
    SOC_CONNID_GPU_P1        = 0x28U,
    SOC_CONNID_MMC2          = 0x29U,
    SOC_CONNID_GPU_P2        = 0x29U,
    SOC_CONNID_BB2D_P1       = 0x2AU,
    SOC_CONNID_BB2D_P2       = 0x2AU,
    SOC_CONNID_GMAC_SW       = 0x2BU,
    SOC_CONNID_USB1          = 0x2CU,
    SOC_CONNID_USB2          = 0x2DU,
    SOC_CONNID_USB3          = 0x2EU,
    SOC_CONNID_SATA          = 0x33U
}SocConnId_t;

#else
/* L3 Firewall Instance Summary */
#define L3FW_INST_NUM                                       (36U)

#define L3FW_EVE1_INST                  (SOC_SECURITYCORE_EVE1_BASE)
#define L3FW_EVE2_INST                  (SOC_SECURITYCORE_EVE2_BASE)
#define L3FW_EVE3_INST                  (SOC_SECURITYCORE_EVE3_BASE)
#define L3FW_EVE4_INST                  (SOC_SECURITYCORE_EVE4_BASE)
#define L3FW_PCIESS2_INST               (SOC_SECURITYCORE_PCIE2_BASE)
#define L3FW_IPU1_INST                  (SOC_SECURITYCORE_IPU1_BASE)
#define L3FW_VCP1_INST                  (SOC_SECURITYCORE_VCP1_BASE)
#define L3FW_VCP2_INST                  (SOC_SECURITYCORE_VCP2_BASE)
#define L3FW_EDMA_TPCC_INST             (SOC_SECURITYCORE_TPCC_BASE)
#define L3FW_EDMA_TC0_INST              (SOC_SECURITYCORE_TPTC_BASE)
#define L3FW_PCIESS1_INST               (SOC_SECURITYCORE_PCIE1_BASE)
#define L3FW_MCASP1_INST                (SOC_SECURITYCORE_MCASP1_BASE)
#define L3FW_MCASP2_INST                (SOC_SECURITYCORE_MCASP2_BASE)
#define L3FW_MCASP3_INST                (SOC_SECURITYCORE_MCASP3_BASE)
#define L3FW_DSP1_SDMA_INST             (SOC_SECURITYCORE_DSP1_SDMA_BASE)
#define L3FW_DSP2_SDMA_INST             (SOC_SECURITYCORE_DSP2_SDMA_BASE)
#define L3FW_QSPI_INST                  (SOC_SECURITYCORE_QSPI_BASE)
#define L3FW_OCMC_ROM_INST              (SOC_SECURITYCORE_OCMC_ROM_BASE)
#define L3FW_MA_MPU_NTTP_INST           (SOC_MA_MPU_NTTP_FW_CFG_BASE)
#define L3FW_EMIF_OCP_INST              (SOC_SECURITYCORE_OCP_FW_EMIF_5430_BASE)
#define L3FW_OCMC_RAM2_INST             (SOC_SECURITYCORE_OCMC_RAM2_BASE)
#define L3FW_GPMC_INST                  (SOC_SECURITYCORE_GPMC_BASE)
#define L3FW_OCMC_RAM1_INST             (SOC_SECURITYCORE_OCMC_RAM1_BASE)
#define L3FW_GPU_INST                   (SOC_SECURITYCORE_GPU_BASE)
#define L3FW_IPU2_INST                  (SOC_SECURITYCORE_IPU2_BASE)
#define L3FW_BB2D_INST                  (0x4A21A000U)
#define L3FW_DSS_INST                   (SOC_SECURITYCORE_DSS_BASE)
#define L3FW_IVAHD_SL2IF_INST           (SOC_SECURITYCORE_IVA1_SL2IF_BASE)
#define L3FW_IVA_CONFIG_INST            (SOC_SECURITYCORE_IVA1_CONFIG_BASE)
#define L3FW_DEBUGSS_CT_TBR_INST        (SOC_SECURITYCORE_DEBUGSS_CT_TBR_BASE)
#define L3FW_L3_INSTR_INST              (SOC_SECURITYCORE_L3_INSTR_BASE)
#define L3FW_OCMC_RAM3_INST             (SOC_SECURITYCORE_OCMC_RAM3_BASE)
#define L3FW_AES1_INST                  (SOC_SECURITYCORE_AES1_BASE)
#define L3FW_AES2_INST                  (SOC_SECURITYCORE_AES2_BASE)
#define L3FW_SHA2MD5_1_INST             (SOC_SECURITYCORE_SHA2MD5_P1_BASE)
#define L3FW_SHA2MD5_2_INST             (SOC_SECURITYCORE_SHA2MD5_P2_BASE)

/**
 * \brief  Macro containing instance summary of L3 Firewalls.
 *         Details:
 *         Element No.  Details
 *         1            Firewall Instance
 *         2            Number of region in Firewall
 *         3            Number of ports in Firewall
 *         This macro is used to initialize struct #l3fwInstSummary_t in
 *         fwlibl3.h
 */
#define L3FW_INST_SUMMARY                   \
    {                                       \
        {L3FW_OCMC_RAM1_INST, 16U, 1U},     \
        {L3FW_OCMC_RAM2_INST, 16U, 1U},     \
        {L3FW_OCMC_RAM3_INST, 16U, 1U},     \
        {L3FW_OCMC_ROM_INST, 4U, 1U},       \
        {L3FW_GPMC_INST, 8U, 1U},           \
        {L3FW_IVAHD_SL2IF_INST, 4U, 1U},    \
        {L3FW_GPU_INST, 1U, 1U},            \
        {L3FW_PCIESS1_INST, 8U, 1U},        \
        {L3FW_PCIESS2_INST, 8U, 1U},        \
        {L3FW_L3_INSTR_INST, 1U, 1U},       \
        {L3FW_AES1_INST, 2U, 1U},           \
        {L3FW_AES2_INST, 2U, 1U},           \
        {L3FW_SHA2MD5_1_INST, 2U, 1U},      \
        {L3FW_SHA2MD5_2_INST, 2U, 1U},      \
        {L3FW_EDMA_TC0_INST, 2U, 2U},       \
        {L3FW_EDMA_TPCC_INST, 1U, 1U},      \
        {L3FW_IPU1_INST, 4U, 1U},           \
        {L3FW_IPU2_INST, 4U, 1U},           \
        {L3FW_DSP1_SDMA_INST, 1U, 1U},      \
        {L3FW_DSP2_SDMA_INST, 1U, 1U},      \
        {L3FW_DSS_INST, 8U, 1U},            \
        {L3FW_IVA_CONFIG_INST, 1U, 1U},     \
        {L3FW_DEBUGSS_CT_TBR_INST, 2U, 1U}, \
        {L3FW_EMIF_OCP_INST, 8U, 2U},       \
        {L3FW_MA_MPU_NTTP_INST, 8U, 2U},    \
        {L3FW_BB2D_INST, 1U, 1U},           \
        {L3FW_EVE1_INST, 1U, 1U},           \
        {L3FW_EVE2_INST, 1U, 1U},           \
        {L3FW_EVE3_INST, 1U, 1U},           \
        {L3FW_EVE4_INST, 1U, 1U},           \
        {L3FW_MCASP1_INST, 1U, 1U},         \
        {L3FW_MCASP2_INST, 1U, 1U},         \
        {L3FW_MCASP3_INST, 1U, 1U},         \
        {L3FW_QSPI_INST, 1U, 1U},           \
        {L3FW_VCP1_INST, 1U, 1U},           \
        {L3FW_VCP2_INST, 1U, 1U}            \
    }
typedef enum SocConnId
{
    SOC_CONNID_MPU           = 0x01U,
    SOC_CONNID_CS_DAP        = 0x04U,
    SOC_CONNID_DSP1_MDMA     = 0x08U,
    SOC_CONNID_DSP1_CFG      = 0x09U,
    SOC_CONNID_DSP1_DMA      = 0x0AU,
    SOC_CONNID_DSP2_DMA      = 0x0BU,
    SOC_CONNID_DSP2_CFG      = 0x0CU,
    SOC_CONNID_DSP2_MDMA     = 0x0DU,
    SOC_CONNID_IVA           = 0x0EU,
    SOC_CONNID_EVE1_P1       = 0x10U,
    SOC_CONNID_EVE2_P1       = 0x11U,
    SOC_CONNID_EVE3_P1       = 0x12U,
    SOC_CONNID_EVE4_P1       = 0x13U,
    SOC_CONNID_IPU1          = 0x18U,
    SOC_CONNID_IPU2          = 0x19U,
    SOC_CONNID_DMA_SYSTEM_RD = 0x1AU,
    SOC_CONNID_DMA_SYSTEM_WR = 0x1AU,
    SOC_CONNID_EDMA_TC1_WR   = 0x1CU,
    SOC_CONNID_EDMA_TC1_RD   = 0x1CU,
    SOC_CONNID_EDMA_TC2_WR   = 0x1DU,
    SOC_CONNID_EDMA_TC2_RD   = 0x1DU,
    SOC_CONNID_DSS           = 0x20U,
    SOC_CONNID_MLB           = 0x21U,
    SOC_CONNID_MMU1          = 0x21U,
    SOC_CONNID_PCIE1         = 0x22U,
    SOC_CONNID_PCIE2         = 0x23U,
    SOC_CONNID_MMU2          = 0x23U,
    SOC_CONNID_VIP1_P1       = 0x24U,
    SOC_CONNID_VIP1_P2       = 0x24U,
    SOC_CONNID_VIP2_P1       = 0x25U,
    SOC_CONNID_VIP2_P2       = 0x25U,
    SOC_CONNID_VIP3_P1       = 0x26U,
    SOC_CONNID_VIP3_P2       = 0x26U,
    SOC_CONNID_VPE_P1        = 0x27U,
    SOC_CONNID_VPE_P2        = 0x27U,
    SOC_CONNID_MMC1          = 0x28U,
    SOC_CONNID_GPU_P1        = 0x28U,
    SOC_CONNID_MMC2          = 0x29U,
    SOC_CONNID_GPU_P2        = 0x29U,
    SOC_CONNID_BB2D_P1       = 0x2AU,
    SOC_CONNID_BB2D_P2       = 0x2AU,
    SOC_CONNID_USB1          = 0x2CU,
    SOC_CONNID_USB2          = 0x2DU,
    SOC_CONNID_USB3          = 0x2EU,
    SOC_CONNID_USB4          = 0x2FU,
    SOC_CONNID_SATA          = 0x33U,
    SOC_CONNID_EVE1_P2       = 0x34U,
    SOC_CONNID_EVE2_P2       = 0x35U,
    SOC_CONNID_EVE3_P2       = 0x36U,
    SOC_CONNID_EVE4_P2       = 0x37U
}SocConnId_t;

#endif

#ifdef __cplusplus
}
#endif

#endif  /* SOC_DEFINES_TDA2XX_H_ */
