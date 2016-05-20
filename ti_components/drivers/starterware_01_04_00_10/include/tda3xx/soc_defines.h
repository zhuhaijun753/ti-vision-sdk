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

#ifndef SOC_DEFINES_TDA3XX_H_
#define SOC_DEFINES_TDA3XX_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "soc.h"

/**************************************************************************\
 * TDA3XX soc file
 \**************************************************************************/

/******************************************************************************\
 * Static inline definition
 \******************************************************************************/
/** @brief Number of VPS VIP instances                                        */
#define CSL_VPS_VIP_PER_CNT             (1U)

/** @brief Number of VPS DSS instances                                        */
#define CSL_VPS_DSS_PER_CNT             (1U)

/** @brief Number of VPS VIP instances                                        */
#define CSL_VPS_VIP_TOP_PER_CNT         (CSL_VPS_VIP_PER_CNT)

/** @brief Number of VPS VIP-PORT instances                                   */
#define CSL_VPS_VIP_PORT_PER_CNT          (CSL_VPS_VIP_PER_CNT * 4U)

/** @brief Number of VPS VPDMA instances                                      */
#define CSL_VPS_VPDMA_PER_CNT      (CSL_VPS_VIP_PER_CNT)

/** @brief Number of VPS CSC instances                                        */
#define CSL_VPS_CSC_PER_CNT        (CSL_VPS_VIP_PER_CNT * 2U)

/** @brief Number of VPS SC instances                                         */
#define CSL_VPS_SC_PER_CNT         (CSL_VPS_VIP_PER_CNT * 2U)

/** @brief Number of VPS DSS-Video + Graphics Pipeline  */
#define CSL_VPS_DSS_VID_PIPE_PER_CNT  (3U)

/** @brief Number of VPS DSS-WB Pipelines  */
#define CSL_VPS_DSS_WB_PIPE_PER_CNT         (1U)

/** @brief Number of VPS DSS-WB Pipelines  */
#define CSL_VPS_ISS_CAPT_PIPE_PER_CNT       (3U)

/** @brief Number of VPS DSS-Overlay manager instances                        */
#define CSL_VPS_DSS_OVLY_MGR_PER_CNT  (2U)

/* VPS interrupt                                                              */
#define CSL_INTC_EVENTID_DSS_DISPC (23U)
/*Todo : Dummy and crossbar Mapped - please cross check before use */
#define CSL_INTC_EVENTID_VIP1INT0  (27U)
#define CSL_VPS_INTC_NUM           (0U)

/** @brief ISS Base Registers */
#define ISS_TOP_BASE_REGISTER                   (SOC_ISS_REGS_BASE + 0x0U)
#define ISS_LVDSRX_BASE_REGISTER                (SOC_ISS_REGS_BASE + 0x4000U)
#define ISS_CTSET_BASE_REGISTER                 (SOC_ISS_REGS_BASE + 0x10000U)
#define ISS_CALA_BASE_REGISTER                  (SOC_ISS_REGS_BASE + 0x12000U)
#define ISS_CALA_CAMERARX_CORE_0_BASE_REGISTER  (SOC_ISS_REGS_BASE + 0x12800U)
#define ISS_CALB_BASE_REGISTER                  (SOC_ISS_REGS_BASE + 0x13000U)
#define ISS_SIMCOP_BASE_REGISTER                (SOC_ISS_REGS_BASE + 0x20000U)
#define ISS_ISP_BASE_REGISTER                   (SOC_ISS_REGS_BASE + 0x40000U)

/* Base Addresses fro ISP Modules */
#define ISS_ISP_SYS1_BASE_REGISTER      (ISS_ISP_BASE_REGISTER + 0x0U)
#define ISS_ISP_SYS2_BASE_REGISTER      (ISS_ISP_BASE_REGISTER + 0xA0U)
#define ISS_ISP_RSZ_BASE_REGISTER       (ISS_ISP_BASE_REGISTER + 0x400U)
#define ISS_ISP_IPIPE_BASE_REGISTER     (ISS_ISP_BASE_REGISTER + 0x800U)
#define ISS_ISP_ISIF_BASE_REGISTER      (ISS_ISP_BASE_REGISTER + 0x1000U)
#define ISS_ISP_IPIPEIF_BASE_REGISTER   (ISS_ISP_BASE_REGISTER + 0x1200U)
#define ISS_ISP_H3A_BASE_REGISTER       (ISS_ISP_BASE_REGISTER + 0x1400U)
#define ISS_ISP_SYS3_BASE_REGISTER      (ISS_ISP_BASE_REGISTER + 0x10000U)
#define ISS_ISP_NSF3_INST0_BASE_REGISTER (ISS_ISP_BASE_REGISTER + 0x10800u)
#define ISS_ISP_NSF3_INST1_BASE_REGISTER (ISS_ISP_BASE_REGISTER + 0x10C00u)
#define ISS_ISP_CNF1_BASE_REGISTER      (ISS_ISP_BASE_REGISTER + 0x10C00U)
#define ISS_ISP_GLBCE_BASE_REGISTER     (ISS_ISP_BASE_REGISTER + 0x11000U)

/* Simcop Modules Base Registers */
#define ISS_SIMCOP_LDC_REGISTERS        (ISS_SIMCOP_BASE_REGISTER + 0x100U)
#define ISS_SIMCOP_DMA_REGISTERS        (ISS_SIMCOP_BASE_REGISTER + 0x200U)
#define ISS_SIMCOP_VTNF_REGISTERS       (ISS_SIMCOP_BASE_REGISTER + 0xA00U)
#define ISS_SIMCOP_LDC_LUT_REGISTERS    (ISS_SIMCOP_BASE_REGISTER + 0x7400U)
#define ISS_SIMCOP_IM_C_REGISTERS       (ISS_SIMCOP_BASE_REGISTER + 0xC000U)
#define ISS_SIMCOP_IM_D_REGISTERS       (ISS_SIMCOP_BASE_REGISTER + 0xD000U)
#define ISS_SIMCOP_IM_E_REGISTERS       (ISS_SIMCOP_BASE_REGISTER + 0xE000U)
#define ISS_SIMCOP_IM_F_REGISTERS       (ISS_SIMCOP_BASE_REGISTER + 0xF000U)

/* Memory Addresses for the different tables */
#define ISS_ISP_IPIPE_HIST_MEM0_ADDR    (ISS_ISP_BASE_REGISTER + 0x2000u)
#define ISS_ISP_IPIPE_HIST_MEM1_ADDR    (ISS_ISP_BASE_REGISTER + 0x2800u)
#define ISS_ISP_IPIPE_HIST_MEM2_ADDR    (ISS_ISP_BASE_REGISTER + 0x3000u)
#define ISS_ISP_IPIPE_HIST_MEM3_ADDR    (ISS_ISP_BASE_REGISTER + 0x3800u)
#define ISS_ISP_IPIPE_HIST_SIZE         (2048u)

#define ISS_ISP_IPIPE_BSC_MEM0_ADDR     (ISS_ISP_BASE_REGISTER + 0x4000u)
#define ISS_ISP_IPIPE_BSC_MEM1_ADDR     (ISS_ISP_BASE_REGISTER + 0x6000u)
#define ISS_ISP_IPIPE_BSC_SIZE          (8192u)

#define ISS_ISP_IPIPE_DPC_MEM0_ADDR     (ISS_ISP_BASE_REGISTER + 0x8000u)
#define ISS_ISP_IPIPE_DPC_MEM1_ADDR     (ISS_ISP_BASE_REGISTER + 0x8400u)
#define ISS_ISP_IPIPE_DPC_SIZE          (1024u)

#define ISS_ISP_IPIPE_YEE_TABLE_ADDR    (ISS_ISP_BASE_REGISTER + 0x00008800u)
#define ISS_ISP_IPIPE_YEE_TABLE_SIZE    (512u)

#define ISS_ISP_IPIPE_GBCE_TABLE_ADDR   (ISS_ISP_BASE_REGISTER + 0x00009000u)
#define ISS_ISP_IPIPE_GBCE_TABLE_SIZE   (2048u)

#define ISS_ISP_IPIPE_3DLUT_MEM0_ADDR   (ISS_ISP_BASE_REGISTER + 0x00009800u)
#define ISS_ISP_IPIPE_3DLUT_MEM1_ADDR   (ISS_ISP_BASE_REGISTER + 0x00009C00u)
#define ISS_ISP_IPIPE_3DLUT_MEM2_ADDR   (ISS_ISP_BASE_REGISTER + 0x0000A000u)
#define ISS_ISP_IPIPE_3DLUT_MEM3_ADDR   (ISS_ISP_BASE_REGISTER + 0x0000A400u)
#define ISS_ISP_IPIPE_3DLUT_SIZE        (1024u)

#define ISS_ISP_IPIPE_GAMMA_R_ADDR      (ISS_ISP_BASE_REGISTER + 0x0000A800u)
#define ISS_ISP_IPIPE_GAMMA_G_ADDR      (ISS_ISP_BASE_REGISTER + 0x0000B000u)
#define ISS_ISP_IPIPE_GAMMA_B_ADDR      (ISS_ISP_BASE_REGISTER + 0x0000B800u)
#define ISS_ISP_IPIPE_GAMMA_SIZE        (2048u)

#define ISS_ISP_ISIF_LIN0_ADDR          (ISS_ISP_BASE_REGISTER + 0xC000u)
#define ISS_ISP_ISIF_LIN1_ADDR          (ISS_ISP_BASE_REGISTER + 0xC200u)
#define ISS_ISP_ISIF_LIN_SIZE           (1024u)

#define ISS_ISP_ISIF_DCCLAMP_MEM_ADDR   (ISS_ISP_BASE_REGISTER + 0xC800u)
#define ISS_ISP_ISIF_DCCLAMP_SIZE       (2048u)

#define ISS_ISP_ISIF_LSC_MEM0_ADDR      (ISS_ISP_BASE_REGISTER + 0xD000u)
#define ISS_ISP_ISIF_LSC_MEM1_ADDR      (ISS_ISP_BASE_REGISTER + 0xE800u)
#define ISS_ISP_ISIF_LSC_MEM_SIZE       (6144u)

#define ISS_ISP_IPIPEIF_LUT0_ADDR       (ISS_ISP_BASE_REGISTER + 0x00016000u)
#define ISS_ISP_IPIPEIF_LUT1_ADDR       (ISS_ISP_BASE_REGISTER + 0x00016C00u)
#define ISS_ISP_IPIPEIF_LUT2_ADDR       (ISS_ISP_BASE_REGISTER + 0x00017800u)

#define ISS_ISP_GLBCE_TABLE_ADDR        (ISS_ISP_BASE_REGISTER + 0x00012000u)

#define ISS_ISP_IPIPEIF_LUT0_SIZE       (513u * 4u)
#define ISS_ISP_IPIPEIF_LUT1_SIZE       (513u * 4u)
#define ISS_ISP_IPIPEIF_LUT2_SIZE       (513u * 4u)

#define CSL_ISS_IPIPE_PER_CNT    (1U)

#define CSL_ISS_ISIF_PER_CNT     (1U)

#define CSL_ISS_RSZ_PER_CNT      (1U)

#define CSL_ISS_NSF3_PER_CNT     (2U)

#define CSL_ISS_H3A_PER_CNT      (1U)

#define CSL_ISS_GLBCE_PER_CNT    (1U)

#define CSL_ISS_CAL_PER_CNT      (2U)
#define CSL_ISS_LVDSRX_PER_CNT   (1U)

#define CSL_ISS_IPIPEIF_PER_CNT  (1U)

#define CSL_ISS_IRQ0_NUM         (33U)
#define CSL_ISS_IRQ1_NUM         (12U + 16U)
#define CSL_ISS_IRQ2_NUM         (13U + 16U)
#define CSL_ISS_IRQ3_NUM         (14U + 16U)
#define CSL_ISS_IRQ4_NUM         (15U + 16U)
#define CSL_ISS_IRQ5_NUM         (16U + 16U)

#define CSL_ISS_SIMCOP_PER_CNT           (1U)
#define CSL_ISS_SIMCOP_NUM_ACT_CTX       (1U)
#define CSL_ISS_SIMCOP_NUM_DMA_CH        (1U)
#define CSL_ISS_SIMCOP_NUM_IRQ           (1U)
#define CSL_ISS_SIMCOP_MAX_HWSEQ_STEPS   (4U)

/******************************************************************************\
 * Peripheral Instance count
 \******************************************************************************/

/** @brief Number of McASP instances                                          */
#define CSL_MCASP_PER_CNT                   ((uint32_t) 1U)

/** @brief Number of UART instances                                           */
#define CSL_UART_PER_CNT                    ((uint32_t) 3U)

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

typedef enum {
    UART1_INST = 0,
    UART2_INST,
    UART3_INST
}UART_INST_t;

/** @brief Peripheral Instances of MCSPI instances                            */
#define CSL_MCSPI_0                         (0)
#define CSL_MCSPI_1                         (1)
#define CSL_MCSPI_2                         (2)
#define CSL_MCSPI_3                         (3)

/** @brief Peripheral Instances of MMC/SD instances
 *                           */
typedef enum {
    MMC4_INST = 0
}MMC_INST_t;

/******************************************************************************\
 * Interrupt Event IDs
 \*****************************************************************************/

/* I2C interrupt                                                              */
#define CSL_INTC_EVENTID_I2CINT1     (41U)
#define CSL_INTC_EVENTID_I2CINT2     (42U)

/*Todo : Dummy and crossbar Mapped - please cross check before use */
/* To get the ducati int mux number, the 'CSL_INTMUX_OFFSET' has to be
 * subttracted from the interrupt number (directly mapped)
 */
#define    CSL_INTMUX_OFFSET                (23U)

/* MCSPI interrupt                                                            */
#define    CSL_INTC_EVENTID_MCSPIINT0       (64)
#define    CSL_INTC_EVENTID_MCSPIINT1       (65)
/*Todo : Dummy and crossbar Mapped - please cross check before use */
#define    CSL_INTC_EVENTID_MCSPIINT2       (48)
#define    CSL_INTC_EVENTID_MCSPIINT3       (49)

/* McASP Interrupts
 * All are crossbar mapped please cross check before use */
#if defined (BUILD_M4)
/** @brief Defining McASP interrupt numbers for the M4 core                   */
/* McASP1 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP0_RXINT        (27U)
/* McASP1 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP0_TXINT        (28U)
#else
/* McASP1 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP0_RXINT        (71U)
/* McASP1 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP0_TXINT        (72U)
#endif

/* UART interrupt                                                             */
/* Todo : All are crossbar mapped please cross check before use */
/*UART1 is being used in DMA Mode */
/*Instance Number Macro definitions are started from 0, it needs to be changed
 *to 1 later*/

#define    CSL_INTC_EVENTID_UARTINT0        (44U)
#define    CSL_INTC_EVENTID_UARTINT1        (43U)
#define    CSL_INTC_EVENTID_UARTINT2        (45U)
/*************************** EDMA RELATED DEFINES  ****************************/

/******************************************************************************\
 *  Parameterizable Configuration:- These are fed directly from the RTL
 *  parameters for the given SOC
 \******************************************************************************/

#define CSL_EDMA3_NUM_DMACH                 64
#define CSL_EDMA3_NUM_QDMACH                8
#define CSL_EDMA3_NUM_PARAMSETS             512
/* Todo : please cross check before use */
#define CSL_EDMA3_NUM_EVQUE                 2
#define CSL_EDMA3_CHMAPEXIST                1
#define CSL_EDMA3_NUM_REGIONS               8
#define CSL_EDMA3_MEMPROTECT                1

/******************************************************************************\
 * Channel Instance count
 \******************************************************************************/
#define CSL_EDMA3_CHA_CNT                   (CSL_EDMA3_NUM_DMACH + \
                                             CSL_EDMA3_NUM_QDMACH)

/* EDMA channel synchronization events                                        */
/* Todo : please cross check before use */
/* McASP0 Receive Event                                                       */
#define CSL_EDMA3_CHA_MCASP0_RX             0
/* McASP0 Transmit Event                                                      */
#define CSL_EDMA3_CHA_MCASP0_TX             1

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
/* Todo : please cross check before use */
/*  MCSPI   */
#define CSL_MCSPI_0_NumOfPhyChannels       (4U)
#define CSL_MCSPI_1_NumOfPhyChannels       (2U)
#define CSL_MCSPI_2_NumOfPhyChannels       (2U)
#define CSL_MCSPI_3_NumOfPhyChannels       (1U)

/* Todo : please cross check before use */
#define CSL_MCASP_0_NumSerializers         (16)

/** @brief Enumeration for peripheral frequencies
 *
 *
 */
/* Todo : please cross check before use */
/** I2C      */
#define CSL_I2C_0_MODULE_FREQ               (96000000)
#define CSL_I2C_1_MODULE_FREQ               (96000000)
/* Todo : please cross check before use */
/** MCSPI      */
#define CSL_MCSPI_0_MODULE_FREQ             (48000000)
#define CSL_MCSPI_1_MODULE_FREQ             (48000000)
#define CSL_MCSPI_2_MODULE_FREQ             (48000000)
#define CSL_MCSPI_3_MODULE_FREQ             (48000000)
/* Todo : please cross check before use */
/** UART     */
#define CSL_UART_0_MODULE_FREQ              (48000000)
#define CSL_UART_1_MODULE_FREQ              (48000000)
#define CSL_UART_2_MODULE_FREQ              (48000000)

/******************************************************************************
 * IRQ XBAR instance mapping for each core interrupts.
 * This is the IRQ XBAR instance to which a particular interrupt of the core is
 * mapped. This macro could be used to pass the IRQ XBAR instance to the IRQ
 * XBAR connect API of starterware.
 ******************************************************************************/
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

/* IRQ XBAR Mapping for IPU1 */
#define XBAR_INST_IPU1_IRQ_23           (uint32_t) (1U)
#define XBAR_INST_IPU1_IRQ_24           (2U)
#define XBAR_INST_IPU1_IRQ_25           (3U)
#define XBAR_INST_IPU1_IRQ_26           (4U)
#define XBAR_INST_IPU1_IRQ_27           (uint32_t) (5U)
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

/******************************************************************************
 * DMA XBAR instance mapping for each DMA instances.
 * This is the DMA XBAR instance to which a particular DMA event is
 * mapped. This macro could be used to pass the DMA XBAR instance to the DMA
 * XBAR connect API of starterware.
 ******************************************************************************/
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

/******************************************************************************\
 * TESOC related info for this SoC.
 \******************************************************************************/
/**
 * \brief   No. of TESOC domains in SoC.
 */
#define TESOC_NUM_DOMAINS                                   (5U)

/**
 * \brief   No. of modules in SoC for which TESOC test can be run.
 *          Each TESOC domain can have multiple modules ex. ISSDSSVIP has
 *          ISS, DSS and VIP.
 */
#define TESOC_NUM_MODULES                                   (8U)

/**
 * \brief   No. of TESOC Tests currently supported by SoC.
 *          Each TESOC domain can have multiple tests ex. ISSDSSVIP has
 *          ISS, DSS and VIP and IPU has IPU LBIST & IPU MBIST.
 */
#define TESOC_NUM_TESTS                                   (9U)

/**
 * \brief   No. of slice blocks for each TESOC domain in SoC.
 */
#define TESOC_NUM_SLICE_BLOCKS                              (8U)

/**
 * \brief   No. of slices for each domain of TESOC in SoC.
 */
#define TESOC_NUM_SLICES                                    (256U)

/**
 * \brief  Macro to store no. of cycles of error log TESOC dumps after failure.
 */
#define  TESOC_DIAG_LOG_CYCLES                              (16U)

/**
 * \brief  Macro to store no. of 32 bit words of error diag data TESOC dumps.
 *         for each failure cycle.
 */
#define  TESOC_DIAG_LOG_DATA_SIZE                           (128U / 32U)

/**
 * \brief  TESOC RAM size in SoC.
 */
#define TESOC_RAM_SIZE                                      (0x10000U)

/**
 * \brief  TESOC ROM size in SoC.
 */
#define TESOC_ROM_SIZE                                      (0x280000U)

/**
 * \brief  TESOC IPU ROM size in SoC.
 *         This is part of TESOC ROM which contains IPU slices.
 *         Only IPU slices are in contiguous in TESOC ROM, for rest of domains
 *         slices are scattered throughout ROM.
 */
#define TESOC_ROM_IPU_SIZE                             ((uint32_t) 0x4B000U)

/**
 * \brief  TESOC IPU ROM CRC golden value.
 *         As CRC signature is 64 bit, it is split into
 *         two parts REGL and REGH.
 */
#define TESOC_ROM_IPU_CRC_SIGNATURE_REGL               ((uint32_t) 0x6057bfe0U)
#define TESOC_ROM_IPU_CRC_SIGNATURE_REGH               ((uint32_t) 0x9bc870b3U)

/**
 * \brief   TESOC domain labels in the SoC.
 */
typedef enum tesocDomainLabel
{
    TESOC_DOMAIN_LABEL_IPU = 0x0,
    /**< IPU domain */
    TESOC_DOMAIN_LABEL_EVE = 0x1,
    /**< EVE domain */
    TESOC_DOMAIN_LABEL_DSP1 = 0x2,
    /**< TURING1 domain */
    TESOC_DOMAIN_LABEL_DSP2 = 0x3,
    /**< TURING2 domain */
    TESOC_DOMAIN_LABEL_ISSDSSVIP = 0x4,
    /**< ISS/DSS/VIP domain domain */
    TESOC_DOMAIN_LABEL_ISS = 0x4,
    /**< ISS domain is part of ISSDSSVIP and all 3 should be
     *   powered off for running this domain
     */
    TESOC_DOMAIN_LABEL_DSS = 0x4,
    /**< DSS domain is part of ISSDSSVIP and all 3 should be
     *   powered off for running this domain
     */
    TESOC_DOMAIN_LABEL_VIP = 0x4
                             /**< VIP domain is part of ISSDSSVIP and all 3
                              * should be powered off for running this domain.
                              */
} tesocDomainLabel_t;

/**
 * \brief   This macro defines the default slice configuration for each
 *          domain.
 *
 *          Though TesOC allows each domain to have maximum of TESOC_NUM_SLICES
 *          slices not all are used by domains in SoC. Only few are used for
 *          storing TDLs(patterns), remaining slices are dummy slices. This
 *          structure stores enabled slices for each domains in SoC.
 *          If value at slice location is 0, slice is not used for storing
 *          valid pattern.
 */
#define TESOC_DEFAULT_SLICE_CFG                                       \
    {                                                                 \
        {                                                             \
            TESOC_TEST_ID_IPU_LBIST,                                  \
            TESOC_DOMAIN_LABEL_IPU,                                   \
            TRUE,                                                     \
            {0x003FFFF8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}           \
        },                                                            \
        {                                                             \
            TESOC_TEST_ID_IPU_MBIST,                                  \
            TESOC_DOMAIN_LABEL_IPU,                                   \
            TRUE,                                                     \
            {0x00000003, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}           \
        },                                                            \
        {                                                             \
            TESOC_TEST_ID_EVE,                                        \
            TESOC_DOMAIN_LABEL_EVE,                                   \
            FALSE,                                                    \
            {0x000FFBFF, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}           \
        },                                                            \
        {                                                             \
            TESOC_TEST_ID_DSP1,                                       \
            TESOC_DOMAIN_LABEL_DSP1,                                  \
            FALSE,                                                    \
            {0xFFFFFFFFU, 0xFDFFFFFFU, 0x3F, 0x0, 0x0, 0x0, 0x0, 0x0} \
        },                                                            \
        {                                                             \
            TESOC_TEST_ID_DSP2,                                       \
            TESOC_DOMAIN_LABEL_DSP2,                                  \
            FALSE,                                                    \
            {0xFFFFFFFFU, 0xFDFFFFFFU, 0x3F, 0x0, 0x0, 0x0, 0x0, 0x0} \
        },                                                            \
        {                                                             \
            TESOC_TEST_ID_ISSDSSVIP,                                  \
            TESOC_DOMAIN_LABEL_ISSDSSVIP,                             \
            FALSE,                                                    \
            {0xFFFFFFFFU, 0x001DBFFF, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}   \
        },                                                            \
        {                                                             \
            TESOC_TEST_ID_ISS,                                        \
            TESOC_DOMAIN_LABEL_ISS,                                   \
            FALSE,                                                    \
            {0xFFFFFFFFU, 0x3FFF, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}       \
        },                                                            \
        {                                                             \
            TESOC_TEST_ID_DSS,                                        \
            TESOC_DOMAIN_LABEL_DSS,                                   \
            FALSE,                                                    \
            {0x0, 0x018000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}             \
        },                                                            \
        {                                                             \
            TESOC_TEST_ID_VIP,                                        \
            TESOC_DOMAIN_LABEL_VIP,                                   \
            FALSE,                                                    \
            {0x0, 0x1C0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}             \
        }                                                             \
    }

/**
 *  \brief  This macro defines the diagnostic slice info for each domain.
 *          Refer #tesocAdvanceResult_t for details.
 *
 *          The diagnostic slice will check if TesOC is able to detect errors
 *          during LBIST. A false compare is made and if f TesOC detects the
 *          miscompare, then the slice fails. The failure in slice result for
 *          the diagnostic slice test means actual pass for diag test.
 */
#define TESOC_DIAGNOSTIC_SLICE_CFG                                \
    {                                                             \
        {TESOC_TEST_ID_IPU_LBIST,                                 \
         TESOC_DOMAIN_LABEL_IPU,                                  \
         {0x00700000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, (22U)}, \
        {TESOC_TEST_ID_IPU_MBIST,                                 \
         TESOC_DOMAIN_LABEL_IPU,                                  \
         {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, (-1)},         \
        {TESOC_TEST_ID_EVE,                                       \
         TESOC_DOMAIN_LABEL_EVE,                                  \
         {0x00100000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, (20U)}, \
        {TESOC_TEST_ID_DSP1,                                      \
         TESOC_DOMAIN_LABEL_DSP1,                                 \
         {0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0}, (70U)},       \
        {TESOC_TEST_ID_DSP2,                                      \
         TESOC_DOMAIN_LABEL_DSP2,                                 \
         {0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0}, (70U)},       \
        {TESOC_TEST_ID_ISSDSSVIP,                                 \
         TESOC_DOMAIN_LABEL_ISSDSSVIP,                            \
         {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, (-1)},         \
        {TESOC_TEST_ID_ISS,                                       \
         TESOC_DOMAIN_LABEL_ISS,                                  \
         {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, (-1)},         \
        {TESOC_TEST_ID_DSS,                                       \
         TESOC_DOMAIN_LABEL_DSS,                                  \
         {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, (-1)},         \
        {TESOC_TEST_ID_VIP,                                       \
         TESOC_DOMAIN_LABEL_VIP,                                  \
         {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, (-1)}          \
    }

/**
 * \brief   TESOC test ids for identifying tests.
 */
typedef enum tesocTestId
{
    TESOC_TEST_ID_IPU_LBIST,
    /**< Test ID for IPU LBIST*/
    TESOC_TEST_ID_IPU_MBIST,
    /**< Test ID for IPU MBIST*/
    TESOC_TEST_ID_EVE,
    /**< Test ID for EVE test*/
    TESOC_TEST_ID_DSP1,
    /**< Test ID for DSP1 test */
    TESOC_TEST_ID_DSP2,
    /**< Test ID for DSP1 test */
    TESOC_TEST_ID_ISSDSSVIP,
    /**< Test ID for ISS/DSS/VIP test */
    TESOC_TEST_ID_ISS,
    /**< Test ID for ISS test */
    TESOC_TEST_ID_DSS,
    /**< Test ID for DSS test */
    TESOC_TEST_ID_VIP
    /**< Test ID for VIP test */
} tesocTestId_t;

/**
 * \brief  Enum to select the COUNT1 clock source for DCC modules.
 */
typedef enum dccClkSrc1
{
    DCC_CLK_SRC1_DCC1_DPLLCORE_M2 = 0U,
    /**< DPLLCORE_M2 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC1_DPLLCORE_M3 = 1U,
    /**< DPLLCORE_M3 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC1_DPLLCORE_H11 = 2U,
    /**< DPLLCORE_H11 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC1_DPLLCORE_H12 = 3U,
    /**< DPLLCORE_H12 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC1_DPLLCORE_H13 = 4U,
    /**< DPLLCORE_H13 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC1_DPLLCORE_H14 = 5U,
    /**< DPLLCORE_H14 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC1_DPLLCORE_H21 = 6U,
    /**< DPLLCORE_H21 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC1_DPLLCORE_H22 = 7U,
    /**< DPLLCORE_H22 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC2_DPLLDDR_M2 = 16U,
    /**< DPLLDDR_M2 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC2_DPLLDDR_M3 = 17U,
    /**< DPLLDDR_M3 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC2_DPLLDDR_H11 = 18U,
    /**< DPLLDDR_H11 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC2_DPLLDDR_H12 = 19U,
    /**< DPLLDDR_H12 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC3_DPLLPER_M2 = 32U,
    /**< DPLLPER_M2 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC3_DPLLPER_M2x2 = 33U,
    /**< DPLLPER_M2x2 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC3_DPLLPER_H11 = 34U,
    /**< DPLLPER_H11 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC3_DPLLPER_H12 = 35U,
    /**< DPLLPER_H12 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC3_DPLLPER_H13 = 36U,
    /**< DPLLPER_H13 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC3_DPLLPER_H14 = 37U,
    /**< DPLLPER_H14 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC4_DPLLDSP_GMAC_M2 = 48U,
    /**< DPLLDSP_GMAC_M2 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC4_DPLLDSP_GMAC_M3 = 49U,
    /**< DPLLDSP_GMAC_M3 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC4_DPLLDSP_GMAC_H11 = 50U,
    /**< DPLLDSP_GMAC_H11 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC4_DPLLDSP_GMAC_H12 = 51U,
    /**< DPLLDSP_GMAC_H12 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC4_DPLLDSP_GMAC_H13 = 52U,
    /**< DPLLDSP_GMAC_H13 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC4_VIN1A = 53U,
    /**< VIN1A is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC4_VIN2A = 54U,
    /**< VIN2A is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC4_RXBTEHS_CLK = 55U,
    /**< RXBTEHS_CLK is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC5_DPLLEVE_VID_M2 = 64U,
    /**< DPLLEVE_VID_M2 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC5_DPLLEVE_VID_M2x2 = 65U,
    /**< DPLLEVE_VID_M2x2 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC5_SDPLLEVE_VID_M3 = 66U,
    /**< DPLLEVE_VID_M3 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC6_SYS_CLK2 = 80U,
    /**< SYS_CLK2 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC6_XREF_CLK = 81U,
    /**< XREF_CLK is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC6_VIN1B = 82U,
    /**< VIN1B is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC6_VIN2B = 83U,
    /**< VIN2B is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC6_RXBTEHS_CLK = 84U,
    /**< RXBTEHS_CLK is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC6_MCASP_ACLKX = 85U,
    /**< MCASP_ACLKX is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC6_MCASP_ACLKR = 86U,
    /**< MCASP_ACLKR is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC7_DPLLCORE_H23 = 96U,
    /**< DPLLCORE_H23 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC7_MCASP_ACLKX = 97U,
    /**< MCASP_ACLKX is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC7_MCASP_ACLKR = 98U,
    /**< MCASP_ACLKR is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC7_MDIO_MCLK = 99U,
    /**< MDIO_MCLK is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC7_RGMII_RXCLK = 100U
                                    /**< RGMII_RXCLK is selected as source for
                                     *   COUNT1 */
}dccClkSrc1_t;

/* ESM number of groups */
#define ESM_NUM_GROUP_MAX                    (1U)
#define ESM_NUM_INTR_PER_GROUP               (128U)
/**
 * \brief  Enum to select the interrupt source for ESM group 1.
 */
typedef enum esmGroup1IntrSrc
{
    ESM_GROUP1_INTR_SRC_DCC1_IRQ_ERROR = 0,
    /**< DCC1_IRQ_ERROR interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_DCC2_IRQ_ERROR = 1,
    /**< DCC2_IRQ_ERROR interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_DCC3_IRQ_ERROR = 2,
    /**< DCC3_IRQ_ERROR interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_GPMC_DREQ = 3,
    /**< GPMC_DREQ interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_CTRL_MODULE_CORE_IRQ_SEC_EVTS = 4,
    /**< CTRL_MODULE_CORE_IRQ_SEC_EVTS interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_L3_MAIN_IRQ_DBG_ERR = 5,
    /**< L3_MAIN_IRQ_DBG_ERR interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_L3_MAIN_IRQ_APP_ERR = 6,
    /**< L3_MAIN_IRQ_APP_ERR interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_L3_MAIN_IRQ_STAT_ALARM = 7,
    /**< L3_MAIN_IRQ_STAT_ALARM interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_CTRL_MODULE_CORE_IRQ_THERMAL_ALERT = 8,
    /**< CTRL_MODULE_CORE_IRQ_THERMAL_ALERT interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_DSP1_IRQ_TPCC_ERR = 10,
    /**< DSP1_IRQ_TPCC_ERR interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_DSP2_IRQ_TPCC_ERR = 11,
    /**< DSP2_IRQ_TPCC_ERR interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_EDMA_TPCC_IRQ_ERR = 14,
    /**< EDMA_TPCC_IRQ_ERR interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_EDMA_TC0_IRQ_ERR = 15,
    /**< EDMA_TC0_IRQ_ERR interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_EDMA_TC1_IRQ_ERR = 16,
    /**< EDMA_TC1_IRQ_ERR interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_DCC4_IRQ_ERROR = 19,
    /**< DCC4_IRQ_ERROR interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_DCC5_IRQ_ERROR = 20,
    /**< DCC5_IRQ_ERROR interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_DCC6_IRQ_ERROR = 21,
    /**< DCC6_IRQ_ERROR interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_DCC7_IRQ_ERROR = 22,
    /**< DCC7_IRQ_ERROR interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_CAM_RST = 23,
    /**< CAM_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_CM_CORE_PWRON_RET_RST = 24,
    /**< CM_CORE_PWRON_RET_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_CM_CORE_RET_RST = 25,
    /**< CM_CORE_RET_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_CUSTEFUSE_RST = 26,
    /**< CUSTEFUSE_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_DSP1_PWRON_RST = 27,
    /**< DSP1_PWRON_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_DSP1_RET_RST = 28,
    /**< DSP1_RET_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_DSP1_RST = 29,
    /**< DSP1_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_DSP1_SYS_RST = 30,
    /**< DSP1_SYS_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_DSP2_PWRON_RST = 31,
    /**< DSP2_PWRON_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_DSP2_RET_RST = 32,
    /**< DSP2_RET_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_DSP2_RST = 33,
    /**< DSP2_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_DSP2_SYS_RST = 34,
    /**< DSP2_SYS_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_DSS_RET_RST = 35,
    /**< DSS_RET_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_DSS_RST = 36,
    /**< DSS_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_EMU_EARLY_PWRON_RST = 37,
    /**< EMU_EARLY_PWRON_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_EMU_PWRON_RST = 38,
    /**< EMU_PWRON_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_EMU_RST = 39,
    /**< EMU_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_EVE_CPU_RST = 40,
    /**< EVE_CPU_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_EVE_PWRON_RST = 41,
    /**< EVE_PWRON_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_EVE_RST = 42,
    /**< EVE_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_IPU_CPU0_RST = 43,
    /**< IPU_CPU0_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_IPU_CPU1_RST = 44,
    /**< IPU_CPU1_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_IPU_PWRON_RST = 45,
    /**< IPU_PWRON_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_IPU_RET_RST = 46,
    /**< IPU_RET_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_IPU_RST = 47,
    /**< IPU_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_L3INIT_PWRON_RST = 48,
    /**< L3INIT_PWRON_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_L3INIT_RST = 49,
    /**< L3INIT_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_L4PER_PWRON_RET_RST = 50,
    /**< L4PER_PWRON_RET_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_L4PER_RET_RST = 51,
    /**< L4PER_RET_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_L4PER_RST = 52,
    /**< L4PER_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_DEBUGSS_STANDBY = 53,
    /**< DEBUGSS_STANDBY interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_LPRM_PWRON_RST = 56,
    /**< LPRM_PWRON_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_LPRM_RST = 57,
    /**< LPRM_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_LPRM_SECURE_RST = 58,
    /**< LPRM_SECURE_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_WKUPAON_PWRON_RST = 59,
    /**< WKUPAON_PWRON_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_WKUPAON_RST = 60,
    /**< WKUPAON_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_WKUPAON_SYS_PWRON_RST = 61,
    /**< WKUPAON_SYS_PWRON_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_CM_CORE_AON_PWRON_RST = 62,
    /**< CM_CORE_AON_PWRON_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_CM_CORE_AON_RST = 63,
    /**< CM_CORE_AON_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_COREAON_PWRON_RST = 64,
    /**< COREAON_PWRON_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_COREAON_RST = 65
                                      /**< COREAON_RST interrupt source for ESM
                                       *   group 1 */
}esmGroup1IntrSrc_t;

/* L3 FIREWALL */
/* L3 Firewall Instance Summary */
#define L3FW_INST_NUM                                       (17U)

#define L3FW_DEBUGSS_CT_TBR_INST        (SOC_SECURITYCORE_DEBUGSS_CT_TBR_BASE)
#define L3FW_DSP1_SDMA_INST             (SOC_SECURITYCORE_DSP1_SDMA_BASE)
#define L3FW_DSP2_SDMA_INST             (SOC_SECURITYCORE_DSP2_SDMA_BASE)
#define L3FW_DSS_INST                   (SOC_SECURITYCORE_DSS_BASE)
#define L3FW_EVE_INST                   (SOC_SECURITYCORE_EVE1_BASE)
#define L3FW_GPMC_INST                  (SOC_SECURITYCORE_GPMC_BASE)
#define L3FW_IPU_INST                   (SOC_SECURITYCORE_IPU1_BASE)
#define L3FW_L3_INSTR_INST              (SOC_SECURITYCORE_L3_INSTR_BASE)
#define L3FW_OCMC_RAM_INST              (SOC_SECURITYCORE_OCMC_RAM1_BASE)
#define L3FW_EMIF_INST                  (SOC_SECURITYCORE_OCP_FW_EMIF_5430_BASE)
#define L3FW_QSPI_INST                  (SOC_SECURITYCORE_QSPI_BASE)
#define L3FW_EDMA_TPCC_INST             (SOC_SECURITYCORE_TPCC_BASE)
#define L3FW_TPTC_INST                  (SOC_SECURITYCORE_TPTC_BASE)
#define L3FW_CRC_INST                   (SOC_SECURITYCORE_CRC_BASE)
#define L3FW_TESOC_INST                 (SOC_SECURITYCORE_TESOC_BASE)
#define L3FW_ISS_INST                   (SOC_SECURITYCORE_ISS_BASE)
#define L3FW_MCASP_INST                 (SOC_SECURITYCORE_MCASP1_BASE)

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
        {L3FW_DEBUGSS_CT_TBR_INST, 2U, 1U}, \
        {L3FW_DSP1_SDMA_INST, 1U, 1U},      \
        {L3FW_DSP2_SDMA_INST, 1U, 1U},      \
        {L3FW_DSS_INST, 8U, 1U},            \
        {L3FW_EVE_INST, 1U, 1U},            \
        {L3FW_GPMC_INST, 8U, 1U},           \
        {L3FW_IPU_INST, 4U, 1U},            \
        {L3FW_L3_INSTR_INST, 1U, 1U},       \
        {L3FW_OCMC_RAM_INST, 24U, 1U},      \
        {L3FW_EMIF_INST, 24U, 1U},          \
        {L3FW_QSPI_INST, 4U, 1U},           \
        {L3FW_EDMA_TPCC_INST, 1U, 1U},      \
        {L3FW_TPTC_INST, 2U, 1U},           \
        {L3FW_CRC_INST, 4U, 1U},            \
        {L3FW_TESOC_INST, 4U, 1U},          \
        {L3FW_ISS_INST, 2U, 1U},            \
        {L3FW_MCASP_INST, 1U, 1U},          \
    }

typedef enum SocConnId
{
    SOC_CONNID_DEBUGSS_CS_DAP_INIT = 0x4U,
    SOC_CONNID_IEEE1500_2_OCP_INIT = 0x5U,
    SOC_CONNID_DSP1_MDMA_INIT      = 0x8U,
    SOC_CONNID_DSP1_CFG_INIT       = 0x9U,
    SOC_CONNID_DSP1_EDMA_INIT      = 0xAU,
    SOC_CONNID_DSP2_EDMA_INIT      = 0xBU,
    SOC_CONNID_DSP2_CFG_INIT       = 0xCU,
    SOC_CONNID_DSP2_MDMA_INIT      = 0xDU,
    SOC_CONNID_EVE_TC0_INIT        = 0x10U,
    SOC_CONNID_IPU_INIT            = 0x18U,
    SOC_CONNID_TPTC1_WR_INIT       = 0x1CU,
    SOC_CONNID_TPTC1_RD_INIT       = 0x1CU,
    SOC_CONNID_TPTC2_WR_INIT       = 0x1DU,
    SOC_CONNID_TPTC2_RD_INIT       = 0x1DU,
    SOC_CONNID_DSS1_INIT           = 0x20U,
    SOC_CONNID_MMU_INIT            = 0x21U,
    SOC_CONNID_VIP_P1_INIT         = 0x24U,
    SOC_CONNID_VIP_P2_INIT         = 0x24U,
    SOC_CONNID_GMAC_SW_INIT        = 0x2BU,
    SOC_CONNID_ISS_RT_INIT         = 0x30U,
    SOC_CONNID_ISS_NRT1_INIT       = 0x31U,
    SOC_CONNID_ISS_NRT2_INIT       = 0x32U,
    SOC_CONNID_EVE_TC1_INIT        = 0x34U,
    SOC_CONNID_STATCOLL1           = 0x38U,
    SOC_CONNID_STATCOLL2           = 0x38U,
    SOC_CONNID_STATCOLL3           = 0x38U,
    SOC_CONNID_STATCOLL4           = 0x38U
}SocConnId_t;

#ifdef __cplusplus
}
#endif

#endif  /* SOC_DEFINES_TDA3XX_H_ */
