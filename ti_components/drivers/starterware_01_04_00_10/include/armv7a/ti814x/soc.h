/******************************************************************************
 *
 * SOC.h - SOC memory map header file
 *
 * Copyright (c) 2008-2013 Texas Instruments Incorporated.  All rights reserved.
 * Software License Agreement
 *
 * Texas Instruments (TI) is supplying this software for use solely and
 * exclusively on TI devices. The software is owned by TI and/or its
 * suppliers, and is protected under applicable patent and copyright laws.
 *
 * You may not combine this software with any open-source software if such
 * combination would cause this software to become subject to any of the
 * license terms applicable to such open source software.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
 * NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
 * NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
 * CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
 * DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************
 */
#ifndef SOC_H_
#define SOC_H_

#ifdef __cplusplus
extern "C"
{
#endif

/*  \brief Base address of AINTC memory mapped registers */
#define SOC_AINTC_REGS                       (0x48200000U)
#define SOC_MPUSS_CONF_BASE                  (0x48240000U)

/*  \brief Control module base address */
#define PADCTRL_BASE                         (0x48140000U)

/*  \brief PRCM Base Address */
#define PRCM_BASE                            (0x48180000U)

/*  \brief Base address of I2C memory mapped registers */
#define SOC_I2C1_BASE                        (0x48028000U)
#define SOC_I2C2_BASE                        (0x4802A000U)
#define SOC_I2C3_BASE                        (0x4819C000U)
#define SOC_I2C4_BASE                        (0x4819E000U)

/*  \brief Base address of UART memory mapped registers */
#define SOC_UART1_BASE                       (0x48020000U)
#define SOC_UART2_BASE                       (0x48022000U)
#define SOC_UART3_BASE                       (0x48024000U)
#define SOC_UART4_BASE                       (0x481A6000U)
#define SOC_UART5_BASE                       (0x481A8000U)
#define SOC_UART6_BASE                       (0x481AA000U)

/*  \brief Base address of MCSPI memory mapped registers */
#define SOC_MCSPI1_BASE                      (0x48030000U)
#define SOC_MCSPI2_BASE                      (0x481A0000U)
#define SOC_MCSPI3_BASE                      (0x481A2000U)
#define SOC_MCSPI4_BASE                      (0x481A4000U)

/*
 *   \brief Base address of MCSPI memory mapped registers
 *   Defined again to keep the interface same
 */
#define SOC_MCSPI0_REGS                      (0x48030000U)
#define SOC_MCSPI1_REGS                      (0x481A0000U)
#define SOC_MCSPI2_REGS                      (0x481A2000U)
#define SOC_MCSPI3_REGS                      (0x481A4000U)

/*  \brief Base address of Mailbox memory mapped registers */
#define SOC_SYSTEM_MAILBOX                   (0x480C8000U)

/*  \brief Base addresses of GPIO memory mapped registers */
#define SOC_GPIO1_BASE                       (0x48032000U)
#define SOC_GPIO2_BASE                       (0x4804C000U)
#define SOC_GPIO3_BASE                       (0x481AC000U)
#define SOC_GPIO4_BASE                       (0x481AE000U)

/*  \brief Base addresses of EDMA memory mapped registers  */
#define SOC_EDMA_TPCC_BASE                   (0x49000000U)

/*  \brief Base addresses of DSP MMU memory mapped registers */
#define SOC_DSP1_MMU0CFG_BASE                (0x48010000U)

/* \brief DSP L2 RAM base*/
#define SOC_DSP_L2_RAM_BASE                  (0x40800000U)

/* \brief DSP L1P RAM base*/
#define SOC_DSP_L1P_CACHE_RAM_BASE           (0x40E00000U)

/* \brief DSP L1D RAM base*/
#define SOC_DSP_L1D_CACHE_RAM_BASE           (0x40F00000U)

/*  \brief Base address of Channel controller  memory mapped registers */
#define SOC_EDMA30CC_0_REGS                  (0x49000000U)

/*  \brief Base address of MCASP memory mapped registers */
#define SOC_MCASP0_CFG_BASE                  (0x48038000U)
#define SOC_MCASP0_BASE                      (0x46000000U)
#define SOC_MCASP1_CFG_BASE                  (0x4803C000U)
#define SOC_MCASP1_BASE                      (0x46400000U)
#define SOC_MCASP2_CFG_BASE                  (0x48050000U)
#define SOC_MCASP2_BASE                      (0x46800000U)
#define SOC_MCASP3_CFG_BASE                  (0x4A1A2000U)
#define SOC_MCASP3_BASE                      (0x4A1A5000U)
#define SOC_MCASP4_CFG_BASE                  (0x4A1A8000U)
#define SOC_MCASP4_BASE                      (0x4A1AB000U)
#define SOC_MCASP5_CFG_BASE                  (0x4A1AE000U)
#define SOC_MCASP5_BASE                      (0x4A1B1000U)

/*  \brief Base address of Timer memory mapped registers */
#define SOC_TIMER1_BASE                     (0x4802E000U)
#define SOC_TIMER2_BASE                     (0x48040000U)
#define SOC_TIMER3_BASE                     (0x48042000U)
#define SOC_TIMER4_BASE                     (0x48044000U)
#define SOC_TIMER5_BASE                     (0x48046000U)
#define SOC_TIMER6_BASE                     (0x48048000U)
#define SOC_TIMER7_BASE                     (0x4804A000U)
#define SOC_TIMER8_BASE                     (0x481C1000U)

/*  \brief Base address of MMCSD memory mapped registers */
#define SOC_MMC1_BASE                       (0x48060000U)
#define SOC_MMC2_BASE                       (0x481D8000U)
#define SOC_MMC3_BASE                       (0x47810000U)

/*
 *  \brief Base address of MMCSD memory mapped registers.
 *  Defined again to keep the interface same
 */
#define SOC_MMCHS_0_REGS                    (0x48060000U)
#define SOC_MMCHS_1_REGS                    (0x481D8000U)
#define SOC_MMCHS_2_REGS                    (0x47810000U)

/*  \brief Base address of PCIe memory mapped registers  */
#define SOC_PCIE_APP_BASE                   (0x51000000U)
#define SOC_PCIE_LOCAL_CONF_BASE            (0x51001000U)
#define SOC_PCIE_REMOTE_CONF_BASE           (0x51002000U)
#define SOC_PCIE_REMOTE_IO_BASE             (0x51003000U)

/*  \brief PCIe memory space base address */
#define SOC_PCIE_BASE                       (0x20000000U)

/*  \brief EDMA TPTC registers */
#define SOC_EDMA_TC0_BASE                   (0x49800000U)
#define SOC_EDMA_TC1_BASE                   (0x49900000U)
#define SOC_EDMA_TC2_BASE                   (0x49A00000U)
#define SOC_EDMA_TC3_BASE                   (0x49B00000U)

/* \brief GPMC region */
#define SOC_GPMC_BASE                       (0x0U)

/* \brief GPMC memory mapped registers */
#define SOC_GPMC_CONF_BASE                  (0x50000000U)
#define SOC_GPMC_CONF_REGS_BASE             (0x50000000U)

/* \brief OCMC RAM Base address */
#define SOC_OCMC_RAM_BASE                   (0x40300000U)

/* \brief McBSP region */
#define SOC_MCBSP_BASE                      (0x47000000U)

/* \brief HDMI region */
#define SOC_HDMI_BASE                       (0x46C00000U)

/* \brief USB Base address */
#define SOC_USB_BASE                        (0x47400000U)

/* \brief Media controller base address */
#define SOC_MEDIA_CONTROL_BASE              (0x55000000U)

/* \brief SGX530 base address*/
#define SOC_SGX530_SOC                      (0x56000000U)

/* \brief HDVICP2 Configuration base address*/
#define SOC_HDVICP2_CONF_BASE               (0x58000000U)

/* \brief HDVICP2 SL2 base address*/
#define SOC_HDVICP2_SL2_BASE                (0x59000000U)

/* \brief ISS base address*/
#define SOC_ISS_BASE                        (0x5C000000U)

/* \brief EMAC memory mapped register base */
#define SOC_EMAC_SW_BASE                    (0x4A100000U)

/* \brief SATA memory mapped register base */
#define SOC_DWC_AHSATA_BASE                 (0x4A140000U)

/* \brief DEMMU memory mapped register base */
#define SOC_DEMMU_BASE                      (0x48010000U)

/* \brief ELM memory mapped register base */
#define SOC_ELM_BASE                        (0x48080000U)

/* \brief RTC memory mapped register base*/
#define SOC_RTC_SS_BASE                     (0x480C0000U)

/* \brief SPINLOCK memory mapped register base*/
#define SOC_SPINLOCK_BASE                   (0x480CA000U)

/* \brief HDVPSS memory mapped register base*/
#define SOC_HDVPSS_BASE                     (0x48100000U)

/* \brief HDMI memory mapped register base*/
#define SOC_HDMI_CONF_BASE                  (0x48122000U)

/* \brief Smart reflex memory mapped register base*/
#define SOC_SMARTREFLEX1_BASE               (0x48188000U)
#define SOC_SMARTREFLEX2_BASE               (0x4818A000U)
#define SOC_SMARTREFLEX3_BASE               (0x48190000U)
#define SOC_SMARTREFLEX4_BASE               (0x48192000U)

/* \brief OCP Watchpoint memory mapped register base */
#define SOC_OCP_WATCHPOINT_BASE             (0x4818C000U)

/* \brief Sync timer memory mapped register base */
#define SOC_SYNCTIMER32K_BASE               (0x481C3000U)

/* \brief PLLSS memory mapped register base */
#define SOC_PLLSS_BASE                      (0x481C5000U)

/* \brief Watch dog timer memory mapped register base */
#define SOC_WATCHDOGTIMER_BASE              (0x481C7000U)

/* \brief DCAN memory mapped register base */
#define SOC_DCAN1_BASE                      (0x481CC000U)
#define SOC_DCAN2_BASE                      (0x481D0000U)

/* \brief VPS module memory mapped register base */
/* \brief VPS module memory mapped register base */
#define SOC_VPS_CHR_US_PRI_0_REGS_BASE      (0x48100300U)
#define SOC_VPS_CHR_US_PRI_1_REGS_BASE      (0x48100400U)
#define SOC_VPS_CHR_US_PRI_2_REGS_BASE      (0x48100500U)
#define SOC_VPS_DEI_0_REGS_BASE             (0x48100600U)
#define SOC_VPS_SC_1_REGS_BASE              (0x48100700U)
#define SOC_VPS_CHR_US_AUX_0_REGS_BASE      (0x48100A00U)
#define SOC_VPS_SC_2_REGS_BASE              (0x48100B00U)
#define SOC_VPS_CSC_HD1_0_REGS_BASE         (0x48100C00U)
#define SOC_VPS_CSC_SD_0_REGS_BASE          (0x48100D00U)
#define SOC_VPS_VCOMP_0_REGS_BASE           (0x48100E00U)
#define SOC_VPS_CSC_HD0_0_REGS_BASE         (0x48100F00U)
#define SOC_VPS_SC_5_REGS_BASE              (0x48105000U)
#define SOC_VPS_CIG_0_REGS_BASE             (0x48105100U)
#define SOC_VPS_COMP_0_REGS_BASE            (0x48105200U)
#define SOC_VPS_CSC_WB2_0_REGS_BASE         (0x48105300U)
#define SOC_VPS_CHR_US_SEC0_0_REGS_BASE     (0x48105400U)
#define SOC_VPS_CHR_US_SEC1_0_REGS_BASE     (0x48105480U)
#define SOC_VPS_VIP0_PARSER_0_REGS_BASE     (0x48105500U)
#define SOC_VPS_CSC_VIP0_0_REGS_BASE        (0x48105700U)
#define SOC_VPS_SC_3_REGS_BASE              (0x48105800U)
#define SOC_VPS_VIP1_PARSER_0_REGS_BASE     (0x48105A00U)
#define SOC_VPS_CSC_VIP1_0_REGS_BASE        (0x48105C00U)
#define SOC_VPS_SC_4_REGS_BASE              (0x48105D00U)
#define SOC_VPS_SD_VENC_0_REGS_BASE         (0x48105E00U)
#define SOC_VPS_HDMI_VENC_0_REGS_BASE       (0x48106000U)
#define SOC_VPS_DVO2_VENC_0_REGS_BASE       (0x4810A000U)
#define SOC_VPS_NF_0_REGS_BASE              (0x4810C200U)
#define SOC_VPS_VPDMA_0_REGS_BASE           (0x4810D000U)

#ifdef __cplusplus
}
#endif
#endif /* SOC_H_ */

