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

/* \brief Base addresses of DSP MMU memory mapped registers */
#define SOC_DSP_MMU0CFG_BASE                 (0x08010000U)

/*  \brief Control module base address */
#define PADCTRL_BASE                         (0x08140000U)

/*  \brief PRCM Base Address */
#define PRCM_BASE                            (0x08180000U)

/*  \brief Base address of I2C memory mapped registers */
#define SOC_I2C1_BASE                        (0x08028000U)
#define SOC_I2C2_BASE                        (0x0802A000U)
#define SOC_I2C3_BASE                        (0x0819C000U)
#define SOC_I2C4_BASE                        (0x0819E000U)
#define SOC_I2C5_BASE                        (0x0819E000U)

/*  \brief Base address of UART memory mapped registers */
#define SOC_UART1_BASE                       (0x08020000U)
#define SOC_UART2_BASE                       (0x08022000U)
#define SOC_UART3_BASE                       (0x08024000U)
#define SOC_UART4_BASE                       (0x081A6000U)
#define SOC_UART5_BASE                       (0x081A8000U)
#define SOC_UART6_BASE                       (0x081AA000U)

/*  \brief Base addresses of EDMA memory mapped registers  */
#define SOC_EDMA_TPCC_BASE                   (0x09000000U)

/*  \brief DSP INTC base address  */
#define SOC_DSP_ICFG_BASE                   (0x1000000U)

/*  \brief EDMA TPTC registers */
#define SOC_EDMA_TC0_BASE                   (0x09800000U)
#define SOC_EDMA_TC1_BASE                   (0x09900000U)
#define SOC_EDMA_TC2_BASE                   (0x09A00000U)
#define SOC_EDMA_TC3_BASE                   (0x09B00000U)

/*
 * \brief Base address of Transfer controller memory mapped registers
 * Defined again to keep the interface same
 */
#define SOC_EDMA30TC_0_REGS                 (0x09800000U)
#define SOC_EDMA30TC_1_REGS                 (0x09900000U)
#define SOC_EDMA30TC_2_REGS                 (0x09A00000U)
#define SOC_EDMA30TC_3_REGS                 (0x09B00000U)

/*  \brief Base address of MCSPI memory mapped registers */
#define SOC_MCSPI1_BASE                      (0x08030000U)
#define SOC_MCSPI2_BASE                      (0x081A0000U)
#define SOC_MCSPI3_BASE                      (0x081A2000U)
#define SOC_MCSPI4_BASE                      (0x081A4000U)

/*
 * \brief Base address of MCSPI memory mapped registers
 * Defined again to keep the interface same
 */
#define SOC_MCSPI0_REGS                    (0x08030000U)
#define SOC_MCSPI1_REGS                    (0x081A0000U)
#define SOC_MCSPI2_REGS                    (0x081A2000U)
#define SOC_MCSPI3_REGS                    (0x081A4000U)

/*  \brief Base address of MCASP memory mapped registers */
#define SOC_MCASP0_CFG_BASE                  (0x08038000U)
#define SOC_MCASP0_BASE                      (0x46000000U)
#define SOC_MCASP1_CFG_BASE                  (0x0803C000U)
#define SOC_MCASP1_BASE                      (0x46400000U)
#define SOC_MCASP2_CFG_BASE                  (0x08050000U)
#define SOC_MCASP2_BASE                      (0x46800000U)
#define SOC_MCASP3_CFG_BASE                  (0x0A1A2000U)
#define SOC_MCASP3_BASE                      (0x4A1A5000U)
#define SOC_MCASP4_CFG_BASE                  (0x0A1A8000U)
#define SOC_MCASP4_BASE                      (0x4A1AB000U)
#define SOC_MCASP5_CFG_BASE                  (0x0A1AE000U)
#define SOC_MCASP5_BASE                      (0x4A1B1000U)

/*
 *  \brief Base address of McASP memory mapped registers
 *  Defined again to keep the interface same
 */
#define SOC_MCASP0_CTRL_REGS               (0x08038000U)
#define SOC_MCASP0_FIFO_REGS               (0x08039000U)
#define SOC_MCASP0_DATA_REGS               (0x46000000U)

#define SOC_MCASP1_CTRL_REGS               (0x0803C000U)
#define SOC_MCASP1_FIFO_REGS               (0x0803D000U)
#define SOC_MCASP1_DATA_REGS               (0x46400000U)

#define SOC_MCASP2_CTRL_REGS               (0x08050000U)
#define SOC_MCASP2_FIFO_REGS               (0x08051000U)
#define SOC_MCASP2_DATA_REGS               (0x46800000U)

#define SOC_MCASP3_CTRL_REGS               (0x0A1A2000U)
#define SOC_MCASP3_FIFO_REGS               (0x0A1A3000U)
#define SOC_MCASP3_DATA_REGS               (0x4A1A5000U)

#define SOC_MCASP4_CTRL_REGS               (0x0A1A8000U)
#define SOC_MCASP4_FIFO_REGS               (0x0A1A9000U)
#define SOC_MCASP4_DATA_REGS               (0x4A1AB000U)

#define SOC_MCASP5_CTRL_REGS               (0x0A1AE000U)
#define SOC_MCASP5_FIFO_REGS               (0x0A1AF000U)
#define SOC_MCASP5_DATA_REGS               (0x4A1B1000U)

/*  \brief Base address of PCIe memory mapped registers  */
#define SOC_PCIE_APP_BASE                   (0x51000000U)
#define SOC_PCIE_LOCAL_CONF_BASE            (0x51001000U)
#define SOC_PCIE_REMOTE_CONF_BASE           (0x51002000U)
#define SOC_PCIE_REMOTE_IO_BASE             (0x51003000U)

/*  \brief PCIe memory space base address */
#define SOC_PCIE_BASE                       (0x20000000U)

/* \brief Base address of Timer memory mapped registers */
#define SOC_TIMER1_BASE                     (0x0802E000U)
#define SOC_TIMER2_BASE                     (0x08040000U)
#define SOC_TIMER3_BASE                     (0x08042000U)
#define SOC_TIMER4_BASE                     (0x08044000U)
#define SOC_TIMER5_BASE                     (0x08046000U)
#define SOC_TIMER6_BASE                     (0x08048000U)
#define SOC_TIMER7_BASE                     (0x0804A000U)
#define SOC_TIMER8_BASE                     (0x081C1000U)

/* \brief McBSP region */
#define SOC_MCBSP_BASE                      (0x47000000U)

/* \brief HDMI region */
#define SOC_HDMI_BASE                       (0x46C00000U)

/* \brief USB Base address */
#define SOC_USB_BASE                        (0x47400000U)

/*  \brief Base address of MMCSD memory mapped registers */
#define SOC_MMC3_BASE                       (0x47810000U)

/* \brief Media controller base address */
#define SOC_MEDIA_CONTROL_BASE              (0x55000000U)

/* \brief SGX530 base address*/
#define SOC_SGX530_SOC                      (0x56000000U)

/* \brief HDVICP2 Configuration base address*/
#define SOC_HDVICP2_CONF_BASE               (0x58000000U)

/* \brief ISS base address*/
#define SOC_ISS_BASE                        (0x5C000000U)

/* \brief HDVICP2 SL2 base address*/
#define SOC_HDVICP2_SL2_BASE                (0x00400000U)

/* \brief DSP L2 RAM base*/
#define SOC_DSP_L2_RAM_BASE                 (0x00800000U)

/* \brief DSP L1P RAM base*/
#define SOC_DSP_L1P_CACHE_RAM_BASE          (0x00E00000U)

/* \brief DSP L1D RAM base*/
#define SOC_DSP_L1D_CACHE_RAM_BASE          (0x00F00000U)

/* \brief DSP Internal cfg registers*/
#define SOC_DSP_INT_CFG_BASE                (0x01800000U)

/* \brief DSP Internal Global address */
#define SOC_DSP_INT_GLOBAL_BASE             (0x10000000U)

/* \brief DSP Internal Global address */
#define SOC_DSP_INT_GLOBAL_BASE             (0x10000000U)

/* \brief OCMC RAM Base address */
#define SOC_OCMC_RAM_BASE                   (0x40300000U)

/* \brief EMAC memory mapped register base */
#define SOC_EMAC_SW_BASE                    (0x0A100000U)

/* \brief DEMMU memory mapped register base */
#define SOC_DEMMU_BASE                      (0x08010000U)

/*  \brief Base addresses of GPIO memory mapped registers */
#define SOC_GPIO1_BASE                       (0x08032000U)
#define SOC_GPIO2_BASE                       (0x0804C000U)
#define SOC_GPIO3_BASE                       (0x081AC000U)
#define SOC_GPIO4_BASE                       (0x081AE000U)

/*  \brief Base address of Mailbox memory mapped registers */
#define SOC_SYSTEM_MAILBOX                   (0x080C8000U)

/* \brief SPINLOCK memory mapped register base*/
#define SOC_SPINLOCK_BASE                    (0x080CA000U)

/* \brief HDVPSS memory mapped register base*/
#define SOC_HDVPSS_BASE                     (0x48100000U)

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

