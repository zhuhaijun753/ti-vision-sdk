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

/**
 *  \file bsp_platformTda2xx.c
 *
 *  \brief Implements the Tda2xx platform specific functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <xdc/std.h>
#include <common/bsp_types.h>
#include <common/bsp_config.h>
#include <common/trace.h>
#include <platforms/bsp_platform.h>
#include <bsp_platformTda2xx.h>
#include <hw/hw_types.h>
#include <hw/hw_dss_family.h>
#include <hw/hw_ctrl_wkup.h>
#include <hw/hw_ctrl_core_pad_io.h>
#include <hw/hw_ipu_cm_core_aon.h>
#include <dma_xbar.h>
#include "dma_xbar_event_ids.h"
#include <irq_xbar_interrupt_ids.h>
#include <irq_xbar.h>
#include <soc_defines.h>
#include <fvid2/fvid2_dataTypes.h>
#include <bsp_platformTda2xx_Priv.h>
#include <hw/hw_wkupaon_cm.h>
#include <soc.h>
#include <hw/hw_ctrl_core.h>
#include "pmlib_videopll.h"
#ifdef VPS_VIP_BUILD
#include <vps/vps_capture.h>
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define PRCM_ENABLE                     ((UInt32) 2U)

/** \brief Enables the MMR region lock  */
/**<  Note : Only if required Enable the macro to lock the MMR region
 *    In the code if unlock MMR and lock MMR is not taken care properly ,
 *    by enabling this macro will result in hang while configuring pinmux ,
 *    PRCM etc.,
 */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static Int32 Bsp_platformTda2xxSetPinMux(
    const Bsp_PlatformInitParams *initParams);

static Int32 Bsp_platformTda2xxEnableMcASP3(void);
static Int32 Bsp_platformTda2xxEnableMcASP6(void);

static Int32 Bsp_platformTda2xxEnableMcSPI1(void);
static Int32 Bsp_platformTda2xxEnableMcSPI2(void);
static Int32 Bsp_platformTda2xxEnableMcSPI3(void);
static Int32 Bsp_platformTda2xxEnableMcSPI4(void);

#if defined (TDA2EX_BUILD) || defined (TDA2XX_MC_BUILD)
static Int32 Bsp_platformTda2xxEnableI2C5(void);
#endif

static Int32 Bsp_platformTda2xxMcSPI4DMAXbar(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 Bsp_platformTda2xxInit(const Bsp_PlatformInitParams *initParams)
{
    Int32          status = BSP_SOK;
    Bsp_PlatformId bspPlatformId;

    bspPlatformId = Bsp_platformGetId();

    if ((TRUE == initParams->isPinMuxSettingReq)
        && ((BSP_PLATFORM_ID_EVM == bspPlatformId)
            || (BSP_PLATFORM_ID_ZEBU == bspPlatformId)))
    {
        status = Bsp_platformTda2xxSetPinMux(initParams);
    }

    /* Cross bar setup */
    if (TRUE == initParams->isIrqXBarSettingReq)
    {
        /* Unlock MMR_LOCK_2  */
        Bsp_platformUnLockRegion(BSP_PLATFORM_MMR_REG_2);
        /* XBAR VIP1_IRQ1 to IPU1_27
         * XBAR VIP2_IRQ1 to IPU1_28 */
        *((volatile UInt32 *) 0x4A0027E8U) =
            ((UInt32) 352 << 16) | (UInt32) 351;
        /* XBAR VIP3_IRQ1 to IPU1_29
         * XBAR VPE1_IRQ1 to IPU1_30 */
        *((volatile UInt32 *) 0x4A0027ECU) =
            ((UInt32) 354 << 16) | (UInt32) 353;
        /* XBAR DISPC_IRQ at IPU1_23 */
        *((volatile UInt32 *) 0x4A0027E0U) = (UInt32) 20;
        /* XBAR HDMI_IRQ at IPU1_26 */
        *((volatile UInt32 *) 0x4A0027E4U) = ((UInt32) 96 << 16);
#ifdef TDA2EX_BUILD
        /* XBAR I2C1_IRQ to IPU1_41
         * XBAR I2C5_IRQ to IPU1_42 */
        *((volatile UInt32 *) 0x4A002804U) =
            ((UInt32) 55 << 16) | (UInt32) 51;

        IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_DSP1,
                       (UInt32) XBAR_INST_DSP1_IRQ_82,
                       I2C1_IRQ);
        IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_DSP1,
                       (UInt32) XBAR_INST_DSP1_IRQ_83,
                       I2C5_IRQ);
#else
        /* XBAR I2C1_IRQ to IPU1_41
         * XBAR I2C2_IRQ to IPU1_42 */
        *((volatile UInt32 *) 0x4A002804U) =
            ((UInt32) 52 << 16) | (UInt32) 51;

        IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_DSP1,
                       (UInt32) XBAR_INST_DSP1_IRQ_82,
                       I2C1_IRQ);
        IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_DSP1,
                       (UInt32) XBAR_INST_DSP1_IRQ_83,
                       I2C2_IRQ);
#endif
        /* XBAR UART1_IRQ to IPU1_44
         * XBAR I2C3_IRQ to IPU1_43 */
        *((volatile UInt32 *) 0x4A002808U) =
            ((UInt32) 67 << 16) | (UInt32) 56;
#ifdef TDA2XX_MC_BUILD
        /* XBAR I2C5_IRQ to IPU1_48 */
        *((volatile UInt32 *) 0x4A002810U) =
            ((UInt32) 55 << 16) | (*((volatile UInt32 *) 0x4A002810U) & 0x1FF);
#endif
    }

    if (TRUE == initParams->isDmaXBarSettingReq)
    {
        /* Unlock MMR_LOCK_1  */
        Bsp_platformUnLockRegion(BSP_PLATFORM_MMR_REG_1);
    }

    if (TRUE == initParams->isAllMcASPInitReq)
    {
        /* For audio on the CPU board */
        status += Bsp_platformTda2xxEnableMcASP3();
        /* For audio on JAMR3 */
        status += Bsp_platformTda2xxEnableMcASP6();
    }

    status += Bsp_platformTda2xxEnableMcSPI1();
    if (TRUE == initParams->isAllMcSPIInitReq)
    {
        status += Bsp_platformTda2xxEnableMcSPI2();
        status += Bsp_platformTda2xxEnableMcSPI3();
        status += Bsp_platformTda2xxEnableMcSPI4();
        if (TRUE == initParams->isDmaXBarSettingReq)
        {
            status += Bsp_platformTda2xxMcSPI4DMAXbar();
        }
    }

#if defined (TDA2EX_BUILD) || defined (TDA2XX_MC_BUILD)
    /* Enable I2C5 module */
    status += Bsp_platformTda2xxEnableI2C5();
#endif

    return (status);
}

Int32 Bsp_platformTda2xxDeInit(void)
{
    Int32 status = BSP_SOK;

    return (status);
}

Bsp_PlatformCpuRev Bsp_platformTda2xxGetCpuRev(void)
{
    UInt32 prodId, cpuRev;
    Bsp_PlatformCpuRev cpuRevEnum = BSP_PLATFORM_CPU_REV_1_0;

    prodId = HW_RD_REG32(SOC_CTRL_MODULE_WKUP_CORE_REGISTERS_BASE +
                         CTRL_WKUP_ID_CODE);
    cpuRev = (prodId & 0xF0000000U) >> 28U;
    switch (cpuRev)
    {
        case 0x0U:
            cpuRevEnum = BSP_PLATFORM_CPU_REV_1_0;
            break;
        case 0x1U:
            cpuRevEnum = BSP_PLATFORM_CPU_REV_1_1;
            break;
        case 0x2U:
            cpuRevEnum = BSP_PLATFORM_CPU_REV_2_0;
            break;
        default:
            /* Default to last known version */
            GT_0trace(
                BspPlatTrace, GT_INFO,
                "PLATFORM: UNKNOWN CPU detected, defaulting to CPU REV 2.0\n");
            cpuRevEnum = BSP_PLATFORM_CPU_REV_2_0;
            break;
    }

    return (cpuRevEnum);
}

Bsp_PlatformPackageType Bsp_platformTda2xxGetPackageType(void)
{
    return (BSP_PLATFORM_PACKAGE_TYPE_UNKNOWN);
}

Int32 Bsp_platformTda2xxSetDispcFuncClkSrc(UInt32 fClkSrc)
{
    Int32 retVal = BSP_SOK;

    if (fClkSrc >= BSP_PLATFORM_CLKSRC_MAX)
    {
        GT_0trace(BspPlatTrace, GT_ERR, "clock source not valid \n");
        retVal = BSP_EBADARGS;
    }

    if (BSP_SOK == retVal)
    {
        retVal = PMLIBVideopllSetDispcFuncClkSrc(
                    (pmlibVideoPllClkSrc_t)fClkSrc);
        if ((Int32)PM_BADARGS == retVal)
        {
            GT_0trace(BspPlatTrace, GT_ERR,
                              "clock source not valid \n");
        }
    }

    return (retVal);
}

/* TODO - Complete these functions once TRM and HW files are updated */
Int32 Bsp_platformTda2xxSetVencClkSrc(const Bsp_PlatformVencSrc *vencPrms)
{
    Int32 retVal = BSP_SOK;

    retVal = PMLIBVideopllSetVencClkSrc(
                (pmlibVideoPllVenc_t) vencPrms->outputVenc,
                (pmlibVideoPllClkSrc_t) vencPrms->vencClkSrc);
    if ((Int32)PM_BADARGS == retVal)
    {
        GT_0trace(BspPlatTrace, GT_ERR,
                          "clock source not valid \n");
    }
    return retVal;
}

/**
 *  \brief  program_dss_video_pll function program the DSS video1,video2 & hdmi
 *          PLL
 *
 *          DSS PLL Programming steps
 *
 *          1) Enable PLL programming in CTRL_CORE_DSS_PLL_CONTROL
 *          2) Enable DSS SCP Interface - DSI_CLK_CTRL.CIO_CLK_ICG
 *          3) DSI Power enable - DSI_CLK_CTRL.PLL_PWR_CMD
 *          4) Check for PLL reset status -PLL_STATUS.PLLCTRL_RESET_DONE
 *          5) set the M,N & H-DIV
 *
 * \param   None.
 *
 * \return  error status.If error has occured it returns a non zero value.
 *          If no error has occured then return status will be zero.
 *
 **/
Int32 Bsp_platformTda2xxSetPllFreq(const Bsp_PlatformSetPllFreq *pllFreq)
{
    Int32  retVal    = BSP_EFAIL;
    UInt32 timeDelay = 0xFFFFFFFFU;
    pmhalPrcmNodeId_t videopllId;

    if (pllFreq->videoPll == BSP_PLATFORM_PLL_VIDEO1)
    {
        videopllId = PMHAL_PRCM_VIDEOPLL_VIDEO1;
    }
#ifndef TDA2EX_BUILD
    else if (pllFreq->videoPll == BSP_PLATFORM_PLL_VIDEO2)
    {
        videopllId = PMHAL_PRCM_VIDEOPLL_VIDEO2;
    }
#endif
    else if (pllFreq->videoPll == BSP_PLATFORM_PLL_HDMI)
    {
        videopllId = PMHAL_PRCM_VIDEOPLL_HDMI;
    }
    else
    {
        videopllId = PMHAL_PRCM_VIDEOPLL_UNDEF;
    }

    retVal = PMLIBVideopllSetFreq(videopllId,
                                  (uint32_t) pllFreq->pixelClk,
                                  timeDelay);

    if (PM_SUCCESS == retVal)
    {
        GT_0trace(BspPlatTrace, GT_DEBUG, "\n DSS PLL Programming - completed");
    }
    else
    {
        GT_0trace(BspPlatTrace, GT_DEBUG, "\n DSS PLL Programming - Failed ");
    }

    return (retVal);
}

Int32 Bsp_platformTda2xxSimVideoInputSelect(UInt32 vipInstId,
                                            UInt32 fileId,
                                            UInt32 pixelClk)
{
    Int32            retVal = BSP_SOK;
#ifndef TDA2EX_BUILD
    volatile UInt32 *pRegs[6];
    UInt32           instId, portId;

    if (vipInstId >= 12U)
    {
        retVal = BSP_EFAIL;
    }
    else
    {
        pRegs[0U] = (volatile UInt32 *) (SOC_VIP1_VIP_REGS_BASE + 0xE100U);
        pRegs[1U] = (volatile UInt32 *) (SOC_VIP1_VIP_REGS_BASE + 0xE200U);
        pRegs[2U] = (volatile UInt32 *) (SOC_VIP2_VIP_REGS_BASE + 0xE100U);
        pRegs[3U] = (volatile UInt32 *) (SOC_VIP2_VIP_REGS_BASE + 0xE200U);
        pRegs[4U] = (volatile UInt32 *) (SOC_VIP3_VIP_REGS_BASE + 0xE100U);
        pRegs[5U] = (volatile UInt32 *) (SOC_VIP3_VIP_REGS_BASE + 0xE200U);

        instId = vipInstId / 2U;
        portId = vipInstId % 2U;
        /* MISRA.PTR.ARITH Does not exceed portId */
        pRegs[instId][0U + portId] = fileId;
        pRegs[instId][2U + portId] = pixelClk;
    }
#endif
    return (retVal);
}

/**
 *  \brief  Bsp_platformTda2xxGetFtRev function to Get FT Revision Number
 */
UInt32 Bsp_platformTda2xxGetFtRev(void)
{
    UInt32 ftRev;

    ftRev = HW_RD_REG32(
        SOC_CTRL_MODULE_WKUP_CORE_REGISTERS_BASE +
        CTRL_WKUP_STD_FUSE_DIE_ID_2);

    /* FT revision is found in bits [15:8] */
    ftRev &= (UInt32) 0x0000FF00;

    ftRev = (ftRev >> 0x8);

    return (ftRev);
}

/**
 *  \brief  Bsp_platformTda2xxEnableHdmiPll function to enable/disable HDMI PLL
 *          PLL
 *
 * \param   enable.
 *          1 -  enable PLL
 *          0 -   Disable PLL
 *
 * \return  error status.If error has occured it returns a non zero value.
 *             If no error has occured then return status will be zero.
 *
 **/
Int32 Bsp_platformTda2xxEnableHdmiPll(UInt32 enable)
{
    Int32 retVal;

    retVal = PMLIBVideopllEnableHdmiPll(enable);

    return retVal;
}

static Int32 Bsp_platformTda2xxSetPinMux(
    const Bsp_PlatformInitParams *initParams)
{
    /* I2C mux */
    Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_I2C1_SDA,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_I2C1_SCL,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);

#ifdef TDA2EX_BUILD
    /* I2C5 mux */
    Bsp_platformSetPinmuxRegs((UInt32) 10, (UInt32) CTRL_CORE_PAD_MCASP1_AXR0,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs((UInt32) 10, (UInt32) CTRL_CORE_PAD_MCASP1_AXR1,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);
#else
    /* I2C2 mux */
    Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_I2C2_SDA,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_I2C2_SCL,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);
#endif

    /* UART1 mux */
    Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_UART1_RXD,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_UART1_TXD,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_UART1_CTSN,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_UART1_RTSN,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);

    /* GPIO mux ( for OV,LI,Aptina, Multi Deserialiser and SIL9127 Sensor) */
    if (BSP_PLATFORM_ID_ZEBU != Bsp_platformGetId())
    {
#ifndef TDA2EX_BUILD
        /* In TDA2XX EVM, needs to be configured as GPIO for mux programming
         * PAD=vin2a_d12, PIN=gpio4_13
         * PAD=vin2a_d13, PIN=gpio4_14
         * PAD=vin2a_d14, PIN=gpio4_15
         * PAD=vin2a_d15, PIN=gpio4_16 */
        Bsp_platformSetPinmuxRegs((UInt32) 14,
                                  (UInt32) CTRL_CORE_PAD_VIN2A_D12,
                                  (BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE
                                   |
                                   BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN |
                                   BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT));
        Bsp_platformSetPinmuxRegs((UInt32) 14,
                                  (UInt32) CTRL_CORE_PAD_VIN2A_D13,
                                  (BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE
                                   |
                                   BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN |
                                   BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT));
        Bsp_platformSetPinmuxRegs((UInt32) 14,
                                  (UInt32) CTRL_CORE_PAD_VIN2A_D14,
                                  (BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE
                                   |
                                   BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN |
                                   BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT));
        Bsp_platformSetPinmuxRegs((UInt32) 14,
                                  (UInt32) CTRL_CORE_PAD_VIN2A_D15,
                                  (BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE
                                   |
                                   BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN |
                                   BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT));

        /* PAD=mcasp2_axr6, PIN=gpio2_29
         * PAD=mcasp2_axr4, PIN=gpio1_4
         * PAD=mcasp2_axr5, PIN=gpio6_7 */
        Bsp_platformSetPinmuxRegs((UInt32) 14,
                                  (UInt32) CTRL_CORE_PAD_MCASP2_AXR6,
                                  (BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE
                                   |
                                   BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN |
                                   BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT));
        Bsp_platformSetPinmuxRegs((UInt32) 14,
                                  (UInt32) CTRL_CORE_PAD_MCASP2_AXR4,
                                  (BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE
                                   |
                                   BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN |
                                   BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT));
        Bsp_platformSetPinmuxRegs((UInt32) 14,
                                  (UInt32) CTRL_CORE_PAD_MCASP2_AXR5,
                                  (BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE
                                   |
                                   BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN |
                                   BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT));
#endif  /* #ifndef TDA2EX_BUILD */
    }

    /* GPIO mux, OV_PWDN of vision board is connected to GPIO6_17
     * PAD=xref_clk0, PIN=gpio6_17 */
    Bsp_platformSetPinmuxRegs((UInt32) 14, (UInt32) CTRL_CORE_PAD_XREF_CLK0,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);

#ifdef TDA2XX_MC_BUILD
    /* UART3 mux */
    Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_UART3_TXD,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_ENABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_UP);
    Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_UART3_RXD,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);

    /* I2C3 mux */
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_GPIO6_14,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_ENABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_UP);
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_GPIO6_15,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_ENABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_UP);
    /* I2C4 mux */
    Bsp_platformSetPinmuxRegs((UInt32) 4, (UInt32) CTRL_CORE_PAD_MCASP4_ACLKX,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_ENABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_UP);
    Bsp_platformSetPinmuxRegs((UInt32) 4, (UInt32) CTRL_CORE_PAD_MCASP4_FSX,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_ENABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_UP);
    /* I2C5 mux */
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_GPMC_A5,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_ENABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_UP);
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_GPMC_A4,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_ENABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_UP);

    /* UART1_CTSN  => (gpio7_24) CAM_S1_GPIO_0*/
    Bsp_platformSetPinmuxRegs((UInt32) 14, (UInt32) CTRL_CORE_PAD_UART1_CTSN,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_UP);

    /* UART1_RTSN  => (gpio7_25) CAM_S1_GPIO_0*/
    Bsp_platformSetPinmuxRegs((UInt32) 14, (UInt32) CTRL_CORE_PAD_UART1_RTSN,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_UP);

    /* I2C2_SDA  => HDMI_SDA*/
    Bsp_platformSetPinmuxRegs((UInt32) 1, (UInt32) CTRL_CORE_PAD_I2C2_SDA,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_UP);

    /* I2C2_SCL  => HDMI_SCL*/
    Bsp_platformSetPinmuxRegs((UInt32) 1, (UInt32) CTRL_CORE_PAD_I2C2_SCL,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_UP);

    /* GPIO6_11  => (GPIO6_11) CAM_S1_RESET*/
    Bsp_platformSetPinmuxRegs((UInt32) 14, (UInt32) CTRL_CORE_PAD_GPIO6_11,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_UP);

    /* CTRL_CORE_PAD_MCASP1_AXR4  => (gpio5_6) CAM_S2_RESET*/
    Bsp_platformSetPinmuxRegs((UInt32) 14, (UInt32) CTRL_CORE_PAD_I2C2_SCL,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_ENABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);

    /*VIN5A Configuration*/
    /*CAM_S1_D7*/
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_MMC3_CLK,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S1_D6*/
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_MMC3_CMD,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S1_D5*/
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_MMC3_DAT0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S1_D4*/
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_MMC3_DAT1,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S1_D3*/
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_MMC3_DAT2,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S1_D2*/
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_MMC3_DAT3,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S1_D1*/
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_MMC3_DAT4,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S1_D0*/
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_MMC3_DAT5,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S1_D8*/
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_MCASP5_AXR1,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S1_D9*/
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_MCASP5_AXR0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S1_D10*/
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_MCASP5_FSX,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S1_D11*/
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_MCASP5_ACLKX,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S1_D12*/
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_MCASP4_AXR1,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S1_D13*/
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_MCASP4_AXR0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S1_D14*/
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_MCASP4_FSX,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S1_D15*/
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_MCASP4_ACLKX,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S1_HS*/
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_MMC3_DAT6,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S1_VS*/
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_MMC3_DAT7,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S1_PCLK*/
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_GPIO6_10,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S1_RESET*/
    Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_GPIO6_11,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_ENABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_GPIO_2*/
    Bsp_platformSetPinmuxRegs((UInt32) 14, (UInt32) CTRL_CORE_PAD_MCASP2_AXR4,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_ENABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);

    /*VIN6A Configuration*/
    /*CAM_S2_RESET -> MCASP1_AXR4 (gpio5_6)*/
    Bsp_platformSetPinmuxRegs((UInt32) 14, (UInt32) CTRL_CORE_PAD_MCASP1_AXR4,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_ENABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_PCLK -> XREF_CLK1 (vin6a_clk0)*/
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_XREF_CLK1,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_VS -> MCASP1_AXR0 (vin6a_vsync0)*/
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_MCASP1_AXR0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_HS -> MCASP1_AXR1 (vin6a_hsync0)*/
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_MCASP1_AXR1,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_GPIO_0 -> MCASP1_AXR5 (gpio5_7)*/
    Bsp_platformSetPinmuxRegs((UInt32) 14, (UInt32) CTRL_CORE_PAD_MCASP1_AXR5,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_ENABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_GPIO_1 -> MCASP1_AXR6 (gpio5_8)*/
    Bsp_platformSetPinmuxRegs((UInt32) 14, (UInt32) CTRL_CORE_PAD_MCASP1_AXR6,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_ENABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_GPIO_2 -> MCASP1_AXR7 (gpio5_9)*/
    Bsp_platformSetPinmuxRegs((UInt32) 14, (UInt32) CTRL_CORE_PAD_MCASP1_AXR7,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_ENABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);

    /*CAM_S2_D7*/
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_MCASP2_ACLKX,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_D6*/
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_MCASP2_FSX,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_D5*/
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_MCASP2_AXR2,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_D4*/
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_MCASP2_AXR3,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_D3*/
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_MCASP3_ACLKX,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_D2*/
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_MCASP3_FSX,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_D1*/
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_MCASP3_AXR0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_D0*/
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_MCASP3_AXR1,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);

    /*CAM_S2_D8*/
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_MCASP1_AXR15,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_D9*/
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_MCASP1_AXR14,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_D10*/
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_MCASP1_AXR13,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_D11*/
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_MCASP1_AXR12,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_D12*/
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_MCASP1_AXR11,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_D13*/
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_MCASP1_AXR10,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_D14*/
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_MCASP1_AXR9,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_D15*/
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_MCASP1_AXR8,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);

#endif /* TDA2XX_MC_BUILD */
    return (BSP_SOK);
}

static Int32 Bsp_platformTda2xxEnableMcASP6(void)
{
    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + (UInt32) 0x204, 0x2);
    while ((HW_RD_REG32(SOC_L4PER_CM_CORE_BASE +
                        (UInt32) 0x204) & ((UInt32) (0x00030000))) != 0x0)
    {
        /* Do nothing - Busy wait */
    }

    return (BSP_SOK);
}

static Int32 Bsp_platformTda2xxEnableMcASP3(void)
{
    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + (UInt32) 0x168, PRCM_ENABLE);
    while ((HW_RD_REG32(SOC_L4PER_CM_CORE_BASE +
                        (UInt32) 0x168) & ((UInt32) (0x00030000))) != 0x0)
    {
        /* Do nothing - Busy wait */
    }

    return (BSP_SOK);
}

static Int32 Bsp_platformTda2xxEnableMcSPI1(void)
{
    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + (UInt32) 0xF0, PRCM_ENABLE);
    while ((HW_RD_REG32(SOC_L4PER_CM_CORE_BASE +
                        (UInt32) 0xF0) & ((UInt32) (0x00030000))) != 0x0)
    {
        /* Do nothing - Busy wait */
    }

    return (BSP_SOK);
}

#if defined (TDA2EX_BUILD) || defined (TDA2XX_MC_BUILD)
static Int32 Bsp_platformTda2xxEnableI2C5(void)
{
    HW_WR_REG32(
        SOC_IPU_CM_CORE_AON_BASE + CM_IPU_I2C5_CLKCTRL, PRCM_ENABLE);
    while ((HW_RD_REG32(SOC_IPU_CM_CORE_AON_BASE +
                        CM_IPU_I2C5_CLKCTRL) & ((UInt32) (0x00030000)))
           != 0x0)
    {
        /* Do nothing - Busy wait */
    }

    return (BSP_SOK);
}

#endif

Int32 Bsp_platformTda2xxSetLCDinputPolarity(UInt32 vencId, UInt32 polarity)
{
    Int32  retVal = BSP_SOK;
    UInt32 regVal;

    /* Unlock MMR_1 */
    Bsp_platformUnLockRegion(BSP_PLATFORM_MMR_REG_1);

    /* Convert FVID2 polarity values to DSS specific */
    if (polarity == FVID2_POL_LOW)
    {
        polarity = 1U;
    }
    else if (polarity == FVID2_POL_HIGH)
    {
        polarity = 0U;
    }
    else
    {
        retVal = BSP_EINVALID_PARAMS;
    }

    if (BSP_SOK == retVal)
    {
        regVal = HW_RD_REG32(
            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
            CTRL_CORE_SMA_SW_1);
        switch (vencId)
        {
            case BSP_PLATFORM_VENC_LCD1:
                HW_SET_FIELD32(regVal, CTRL_CORE_SMA_SW_1_DSS_CH0_IPC, polarity);
                break;
            case BSP_PLATFORM_VENC_LCD2:
                HW_SET_FIELD32(regVal, CTRL_CORE_SMA_SW_1_DSS_CH1_IPC, polarity);
                break;
            case BSP_PLATFORM_VENC_LCD3:
                HW_SET_FIELD32(regVal, CTRL_CORE_SMA_SW_1_DSS_CH2_IPC, polarity);
                break;
            default:
                retVal = BSP_EINVALID_PARAMS;
                break;
        }
    }

    if (BSP_SOK == retVal)
    {
        HW_WR_REG32(
            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_SMA_SW_1,
            regVal);
    }

    return (retVal);
}

Int32 Bsp_platformTda2xxSetLcdSyncPolarity(UInt32 vencId,
                                           UInt32 ctrlEnable,
                                           UInt32 edgePolarity)
{
    Int32  retVal = BSP_SOK;
    UInt32 regVal;

    /* Unlock MMR_1 */
    Bsp_platformUnLockRegion(BSP_PLATFORM_MMR_REG_1);

    /* Convert FVID2 polarity values to DSS specific */
    if (edgePolarity == FVID2_EDGE_POL_RISING)
    {
        edgePolarity = 1U;
    }
    else if (edgePolarity == FVID2_EDGE_POL_FALLING)
    {
        edgePolarity = 0U;
    }
    else
    {
        retVal = BSP_EINVALID_PARAMS;
    }

    if (BSP_SOK == retVal)
    {
        regVal = HW_RD_REG32(
            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
            CTRL_CORE_SMA_SW_1);
        switch (vencId)
        {
            case BSP_PLATFORM_VENC_LCD1:
                HW_SET_FIELD32(
                    regVal, CTRL_CORE_SMA_SW_1_DSS_CH0_ON_OFF, ctrlEnable);
                HW_SET_FIELD32(
                    regVal, CTRL_CORE_SMA_SW_1_DSS_CH0_RF, edgePolarity);
                break;
            case BSP_PLATFORM_VENC_LCD2:
                HW_SET_FIELD32(
                    regVal, CTRL_CORE_SMA_SW_1_DSS_CH1_ON_OFF, ctrlEnable);
                HW_SET_FIELD32(
                    regVal, CTRL_CORE_SMA_SW_1_DSS_CH1_RF, edgePolarity);
                break;
            case BSP_PLATFORM_VENC_LCD3:
                HW_SET_FIELD32(
                    regVal, CTRL_CORE_SMA_SW_1_DSS_CH2_ON_OFF, ctrlEnable);
                HW_SET_FIELD32(
                    regVal, CTRL_CORE_SMA_SW_1_DSS_CH2_RF, edgePolarity);
                break;
            default:
                retVal = BSP_EINVALID_PARAMS;
                break;
        }
    }

    if (BSP_SOK == retVal)
    {
        HW_WR_REG32(
            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_SMA_SW_1,
            regVal);
    }

    return (retVal);
}

Int32 Bsp_platformTda2xxSetVipClkInversion(UInt32 instId, UInt32 invEnable)
{
    Int32  status = BSP_SOK;
#ifdef VPS_VIP_BUILD
    UInt32 regVal;

    /* Unlock MMR_1 */
    Bsp_platformUnLockRegion(BSP_PLATFORM_MMR_REG_1);

    regVal = HW_RD_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_SMA_SW_1);
    switch (instId)
    {
        case VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA):
            HW_SET_FIELD32(
                regVal, CTRL_CORE_SMA_SW_1_VIP1_CLK_INV_PORT_1A, invEnable);
            break;
        case VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTB):
            HW_SET_FIELD32(
                regVal, CTRL_CORE_SMA_SW_1_VIP1_CLK_INV_PORT_1B, invEnable);
            break;
        case VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA):
            HW_SET_FIELD32(
                regVal, CTRL_CORE_SMA_SW_1_VIP1_CLK_INV_PORT_2A, invEnable);
            break;
        case VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTB):
            HW_SET_FIELD32(
                regVal, CTRL_CORE_SMA_SW_1_VIP1_CLK_INV_PORT_2B, invEnable);
            break;

#ifndef TDA2EX_BUILD
        case VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S0, VPS_VIP_PORTA):
            HW_SET_FIELD32(
                regVal, CTRL_CORE_SMA_SW_1_VIP2_CLK_INV_PORT_1A, invEnable);
            break;
        case VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S0, VPS_VIP_PORTB):
            HW_SET_FIELD32(
                regVal, CTRL_CORE_SMA_SW_1_VIP2_CLK_INV_PORT_1B, invEnable);
            break;
        case VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S1, VPS_VIP_PORTA):
            HW_SET_FIELD32(
                regVal, CTRL_CORE_SMA_SW_1_VIP2_CLK_INV_PORT_2A, invEnable);
            break;
        case VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S1, VPS_VIP_PORTB):
            HW_SET_FIELD32(
                regVal, CTRL_CORE_SMA_SW_1_VIP1_CLK_INV_PORT_2B, invEnable);
            break;

        case VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S0, VPS_VIP_PORTA):
            HW_SET_FIELD32(
                regVal, CTRL_CORE_SMA_SW_1_VIP3_CLK_INV_PORT_1A, invEnable);
            break;
        case VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S1, VPS_VIP_PORTA):
            HW_SET_FIELD32(
                regVal, CTRL_CORE_SMA_SW_1_VIP3_CLK_INV_PORT_2A, invEnable);
            break;
#endif  /* #ifndef TDA2EX_BUILD */

        default:
            status = BSP_EINVALID_PARAMS;
            break;
    }

    if (BSP_SOK == status)
    {
        HW_WR_REG32(
            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_SMA_SW_1,
            regVal);
    }
#endif  /* #ifdef VPS_VIP_BUILD */

    return (status);
}

static Int32 Bsp_platformTda2xxEnableMcSPI2(void)
{
    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + (UInt32) 0xF8, PRCM_ENABLE);
    while ((HW_RD_REG32(SOC_L4PER_CM_CORE_BASE +
                        (UInt32) 0xF8) & ((UInt32) (0x00030000))) != 0x0)
    {
        /* Do nothing - Busy wait */
    }

    return (BSP_SOK);
}

static Int32 Bsp_platformTda2xxEnableMcSPI3(void)
{
    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + (UInt32) 0x100, PRCM_ENABLE);
    while ((HW_RD_REG32(SOC_L4PER_CM_CORE_BASE +
                        (UInt32) 0x100) & ((UInt32) (0x00030000))) != 0x0)
    {
        /* Do nothing - Busy wait */
    }

    return (BSP_SOK);
}

static Int32 Bsp_platformTda2xxEnableMcSPI4(void)
{
    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + (UInt32) 0x108, PRCM_ENABLE);
    while ((HW_RD_REG32(SOC_L4PER_CM_CORE_BASE +
                        (UInt32) 0x108) & ((UInt32) (0x00030000))) != 0x0)
    {
        /* Do nothing - Busy wait */
    }

    return (BSP_SOK);
}

/*
** This function configures the DMA crossbar for McSPI4 TX and RX events.
*/
static Int32 Bsp_platformTda2xxMcSPI4DMAXbar(void)
{
    Int32 retVal;

    /* Configure the McSPI4 TX event. */
    retVal = DMAXBARConnect(
        (UInt32) SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
        (dma_id_t) EDMA,
        (UInt32) XBAR_INST_DMA_EDMA_DREQ_22,
        (xbar_evt_t) MCSPI4_DREQ_TX0);
    if (retVal == 0)
    {
        /* Configure the McSPI4 RX event. */
        retVal = DMAXBARConnect(
            (UInt32) SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
            (dma_id_t) EDMA,
            (UInt32) XBAR_INST_DMA_EDMA_DREQ_23,
            (xbar_evt_t) MCSPI4_DREQ_RX0);
    }

    return (retVal);
}

Int32 Bsp_platformTda2xxSetPinmuxRegs(UInt32 mode_index,
                                      UInt32 offset,
                                      UInt32 pupd_info)
{
    Int32  retVal = BSP_SOK;
    UInt32 muxVal;

    /* Unlock MMR_5 for pin muxing*/
    Bsp_platformUnLockRegion(BSP_PLATFORM_MMR_REG_5);

    /* IO input glitches may occur when switching pull type and
     * mux mode simultaneously. To avoid such glitches it is expected
     * two separate register writes to transition to the desired state */

    if (offset != (UInt32) 0xffff)
    {
        muxVal = HW_RD_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + offset);
        if (pupd_info != BSP_PLATFORM_IOPAD_CFG_DEFAULT)
        {
            muxVal &= ~(0x70000U);
            muxVal |= ((pupd_info & 0x07U) << 16U);
            HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + offset, muxVal);
        }
        muxVal &= ~(0x0FU);
        muxVal |= (mode_index & 0x0000000FU);
        HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + offset, muxVal);
    }

    /* Lock MMR_5 for pin muxing*/
    Bsp_platformLockRegion(BSP_PLATFORM_MMR_REG_5);

    return retVal;
}

Int32 Bsp_platformTda2xxLockRegion(Bsp_PlatformMmrRegion region)
{
    Int32 retVal = BSP_SOK;

#ifdef BSP_PLATFORM_MMR_REG_LOCK_ENABLE
    switch (region)
    {
        case BSP_PLATFORM_MMR_REG_1:
            HW_WR_REG32(0x4A002540U, 0x1A1C8144U);
            break;
        case BSP_PLATFORM_MMR_REG_2:
            HW_WR_REG32(0x4A002544U, 0xFDF45530U);
            break;
        case BSP_PLATFORM_MMR_REG_3:
            HW_WR_REG32(0x4A002548U, 0x1AE6E320U);
            break;
        case BSP_PLATFORM_MMR_REG_4:
            HW_WR_REG32(0x4A00254CU, 0x2FFA927CU);
            break;
        case BSP_PLATFORM_MMR_REG_5:
            HW_WR_REG32(0x4A002550U, 0x143F832CU);
            break;
        default:
            retVal = BSP_EFAIL;
            break;
    }
#endif
    return (retVal);
}

Int32 Bsp_platformTda2xxUnLockRegion(Bsp_PlatformMmrRegion region)
{
    Int32 retVal = BSP_SOK;

    switch (region)
    {
        case BSP_PLATFORM_MMR_REG_1:
            HW_WR_REG32(0x4A002540U, 0x2FF1AC2BU);
            break;
        case BSP_PLATFORM_MMR_REG_2:
            HW_WR_REG32(0x4A002544U, 0xF757FDC0U);
            break;
        case BSP_PLATFORM_MMR_REG_3:
            HW_WR_REG32(0x4A002548U, 0xE2BC3A6DU);
            break;
        case BSP_PLATFORM_MMR_REG_4:
            HW_WR_REG32(0x4A00254CU, 0x1EBF131DU);
            break;
        case BSP_PLATFORM_MMR_REG_5:
            HW_WR_REG32(0x4A002550U, 0x6F361E05U);
            break;
        default:
            retVal = BSP_EFAIL;
            break;
    }

    return (retVal);
}

