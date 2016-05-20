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
 *  \file bsp_platformTda3xx.c
 *
 *  \brief Implements the Tda3xx platform specific functions.
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
#include <hw/hw_ctrl_core_pad_io.h>
#include <bsp_platformTda3xx.h>
#include <irq_xbar_interrupt_ids.h>
#include <irq_xbar.h>
#include <soc.h>
#include <hw_ckgen_cm_core_aon.h>
#include <hw_ctrl_core.h>
#include <hw_ctrl_core_sec.h>
#include <soc_defines.h>
#include <fvid2/fvid2_dataTypes.h>
#include <hw_types.h>
#include <irq_xbar.h>
#include <soc_defines.h>
#include "pmlib_videopll.h"
#include "pmhal_prcm.h"
#ifdef VPS_VIP_BUILD
#include <vps/vps_capture.h>
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define CLKSEL_DPLL_DSP_EVE_VID         (0x0000000CU)
#define CM_IDLEST_DPLL_DSP_EVE_VID      (0x00000004U)

/** \brief Enables the MMR region lock  */
/**<  Note : Only if required Enable the macro to lock the MMR region
 *    In the code if unlock MMR and lock MMR is not taken care properly ,
 *    by enabling this macro will result in hang while configuring pinmux ,
 *    PRCM etc.,
 */
/* #define BSP_PLATFORM_MMR_REG_LOCK_ENABLE*/

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
static Int32 Bsp_platformTda3xxSetPinMux(
    const Bsp_PlatformInitParams *initParams);


/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */


/* ========================================================================== */
/*                          Function Declarations                              */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 Bsp_platformTda3xxInit(const Bsp_PlatformInitParams *initParams)
{
    Int32          retVal = BSP_SOK;
    Bsp_PlatformId platformId;

    if((TRUE == initParams->isPinMuxSettingReq))
    {
        platformId = Bsp_platformGetId();
        if((BSP_PLATFORM_ID_EVM == platformId)
           || (BSP_PLATFORM_ID_ZEBU == platformId)
           || (BSP_PLATFORM_ID_SIM == platformId))
        {
            retVal = Bsp_platformTda3xxSetPinMux(initParams);
        }
    }
    /* Cross bar setup */
    if(TRUE == initParams->isIrqXBarSettingReq)
    {
        /* Unlock MMR_LOCK_2 For XBAR settings */
        Bsp_platformUnLockRegion(BSP_PLATFORM_MMR_REG_2);

        /* XBAR VIP1_IRQ1 to IPU1_27 */
        IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                       CPU_IPU1, (UInt32)XBAR_INST_IPU1_IRQ_27, VIP1_IRQ);

#ifdef VPS_ISS_BUILD
        /* XBAR ISS_IRQ_INT0 to IPU1_33 */
        IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                       CPU_IPU1, (UInt32)XBAR_INST_IPU1_IRQ_33, ISS_IRQ_INT0);
#endif

        /* Lock MMR_LOCK_2 */
        Bsp_platformLockRegion(BSP_PLATFORM_MMR_REG_2);
    }

    /* Cross bar setup */
    if(TRUE == initParams->isIrqXBarSettingReq)
    {
        /* Unlock MMR_LOCK_2  */
        Bsp_platformUnLockRegion(BSP_PLATFORM_MMR_REG_2);

        /* XBAR VIP1_IRQ1 to IPU1_27 */
        IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                       CPU_IPU1, (UInt32)XBAR_INST_IPU1_IRQ_27, VIP1_IRQ);

        /* XBAR UART1_IRQ1(1st instance starting from 1) to IPU1_44 */
        IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                       CPU_IPU1, (UInt32)XBAR_INST_IPU1_IRQ_44, UART1_IRQ);

        /* XBAR UART2_IRQ1(1st instance starting from 1) to IPU1_43 */
        IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                       CPU_IPU1, (UInt32)XBAR_INST_IPU1_IRQ_43, UART2_IRQ);

        /* XBAR UART3_IRQ1(1st instance starting from 1) to IPU1_45 */
        IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                       CPU_IPU1, (UInt32)XBAR_INST_IPU1_IRQ_45, UART3_IRQ);

        /* XBAR DISPC_IRQ to IPU1_23 */
        IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                       CPU_IPU1, (UInt32)XBAR_INST_IPU1_IRQ_23, DISPC_IRQ);

        /* XBAR McSPI1_IRQ to IPU1_64 */
        IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                       CPU_IPU1, (UInt32)XBAR_INST_IPU1_IRQ_64, MCSPI1_IRQ);

        /* XBAR McSPI2_IRQ to IPU1_65 */
        IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                       CPU_IPU1, (UInt32)XBAR_INST_IPU1_IRQ_65, MCSPI2_IRQ);

        /* XBAR McSPI3_IRQ to IPU1_48 */
        IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                       CPU_IPU1, (UInt32)XBAR_INST_IPU1_IRQ_48, MCSPI3_IRQ);

        /* XBAR McSPI4_IRQ to IPU1_49 */
        IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                       CPU_IPU1, (UInt32)XBAR_INST_IPU1_IRQ_49, MCSPI4_IRQ);

        /* Lock MMR_LOCK_2 */
        Bsp_platformLockRegion(BSP_PLATFORM_MMR_REG_2);
    }

    return (retVal);
}

Int32 Bsp_platformTda3xxDeInit(void)
{
    Int32 retVal = BSP_SOK;

    return (retVal);
}

Bsp_PlatformCpuRev Bsp_platformTda3xxGetCpuRev(void)
{
    /* Todo - Read from Chip ID register */
    return (BSP_PLATFORM_CPU_REV_1_0);
}

Bsp_PlatformPackageType Bsp_platformTda3xxGetPackageType(void)
{
    UInt32 regVal;
    Bsp_PlatformPackageType packageType;

    regVal = HW_RD_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_BOOTSTRAP);
    if(regVal & CTRL_CORE_BOOTSTRAP_SYSBOOT_7_MASK)
    {
        packageType = BSP_PLATFORM_PACKAGE_TYPE_12x12;
    }
    else
    {
        packageType = BSP_PLATFORM_PACKAGE_TYPE_15x15;
    }

    return (packageType);
}

Int32 Bsp_platformTda3xxSetDispcFuncClkSrc(UInt32 fClkSrc)
{
    Int32 retVal = BSP_SOK;

    return (retVal);
}

Int32 Bsp_platformTda3xxSetVencClkSrc(const Bsp_PlatformVencSrc *vencPrms)
{
    Int32 retVal = BSP_SOK;

    if((vencPrms->outputVenc != BSP_PLATFORM_VENC_LCD1) ||
       (vencPrms->vencClkSrc != BSP_PLATFORM_CLKSRC_DPLL_EVE_VID_DSP))
    {
        GT_0trace(BspPlatTrace, GT_ERR, "\n Invalid PLL or Clock source ");
        retVal = BSP_EBADARGS;
    }

    return (retVal);
}

/**
 *  \brief  program_dss_video_pll function program the EVE_VID_DSP PLL
 *
 * \param   pointer to Bsp_PlatformSetPllFreq struct.
 *
 * \return  error status.If error has occured it returns a non zero value.
 *          If no error has occured then return status will be zero.
 *
 **/
Int32 Bsp_platformTda3xxSetPllFreq(const Bsp_PlatformSetPllFreq *pllFreq)
{
    Int32  retVal = BSP_EFAIL;
    pmhalPrcmNodeId_t videopllId;
    UInt32 timeDelay = 0xFFFFFFFFU;

    if(pllFreq->videoPll == BSP_PLATFORM_PLL_EVE_VID_DSP)
    {
        videopllId = PMHAL_PRCM_DPLL_EVE_VID_DSP;
        retVal      = BSP_SOK;
    }
    else
    {
        GT_0trace(BspPlatTrace, GT_ERR, "Invalid Video PLL selected \n");
        retVal = BSP_EBADARGS;
    }
    if(BSP_SOK == retVal)
    {
        retVal = PMLIBVideopllSetFreq( videopllId,
                                   (uint32_t)pllFreq->pixelClk,
                                    timeDelay);
    }
    return (retVal);
}

Int32 Bsp_platformTda3xxSimVideoInputSelect(UInt32 vipInstId,
                                            UInt32 fileId,
                                            UInt32 pixelClk)
{
    Int32 retVal = BSP_SOK;

    return (retVal);
}

static Int32 Bsp_platformTda3xxSetPinMux(
    const Bsp_PlatformInitParams *initParams)
{
    /* I2C1 mux */
    Bsp_platformSetPinmuxRegs((UInt32)0, (UInt32)CTRL_CORE_PAD_IO_I2C1_SDA,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs((UInt32)0, (UInt32)CTRL_CORE_PAD_IO_I2C1_SCL,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);

    /* I2C2 mux */
    Bsp_platformSetPinmuxRegs((UInt32)0, (UInt32)CTRL_CORE_PAD_IO_I2C2_SDA,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs((UInt32)0, (UInt32)CTRL_CORE_PAD_IO_I2C2_SCL,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);

    /* UART3 mux */
    Bsp_platformSetPinmuxRegs((UInt32)1, (UInt32) CTRL_CORE_PAD_IO_SPI1_SCLK,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs((UInt32)1, (UInt32) CTRL_CORE_PAD_IO_SPI1_CS0,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs((UInt32)1, (UInt32) CTRL_CORE_PAD_IO_SPI1_D1,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs((UInt32)1, (UInt32) CTRL_CORE_PAD_IO_SPI1_D0,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);

    return (0);
}

Int32 Bsp_platformTda3xxSetPinmuxRegs(UInt32 mode_index,
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

    if(offset != 0xffffU)
    {
        muxVal  = HW_RD_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + offset);
        if(pupd_info != BSP_PLATFORM_IOPAD_CFG_DEFAULT)
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

Int32 Bsp_platformTda3xxLockRegion(Bsp_PlatformMmrRegion region)
{
    Int32 retVal = BSP_SOK;

#ifdef BSP_PLATFORM_MMR_REG_LOCK_ENABLE
    switch(region)
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

Int32 Bsp_platformTda3xxUnLockRegion(Bsp_PlatformMmrRegion region)
{
    Int32 retVal = BSP_SOK;

    switch(region)
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

Int32 Bsp_platformTda3xxSetLCDinputPolarity(UInt32 vencId, UInt32 polarity)
{
    Int32  retVal = BSP_SOK;
    UInt32 regVal;

    /* Unlock MMR_1 */
    Bsp_platformUnLockRegion(BSP_PLATFORM_MMR_REG_1);

    /* Convert FVID2 polarity values to DSS specific */
    if(polarity == FVID2_POL_LOW)
    {
        polarity = 1U;
    }
    else if(polarity == FVID2_POL_HIGH)
    {
        polarity = 0U;
    }
    else
    {
        retVal = BSP_EINVALID_PARAMS;
    }

    if(BSP_SOK == retVal)
    {
        regVal = HW_RD_REG32(
                     SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                     CTRL_CORE_SMA_SW_1);
        switch(vencId)
        {
            case BSP_PLATFORM_VENC_LCD1:
                HW_SET_FIELD32(regVal, CTRL_CORE_SMA_SW_1_DSS_CH0_IPC, polarity);
                break;
            default:
                retVal = BSP_EINVALID_PARAMS;
                break;
        }
    }

    if(BSP_SOK == retVal)
    {
        HW_WR_REG32(
            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_SMA_SW_1,
            regVal);
    }

    return (retVal);
}

Int32 Bsp_platformTda3xxSetLcdSyncPolarity(UInt32 vencId,
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

Int32 Bsp_platformTda3xxSetVipClkInversion(UInt32 instId, UInt32 invEnable)
{
    Int32  status = BSP_SOK;
#ifdef VPS_VIP_BUILD
    UInt32 regVal;

    /* Unlock MMR_1 */
    Bsp_platformUnLockRegion(BSP_PLATFORM_MMR_REG_1);

    regVal = HW_RD_REG32(
                SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_SMA_SW_1);
    switch(instId)
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
        default:
            status = BSP_EINVALID_PARAMS;
            break;
    }

    if(BSP_SOK == status)
    {
        HW_WR_REG32(
            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_SMA_SW_1,
            regVal);
    }
#endif  /* #ifdef VPS_VIP_BUILD */

    return (status);
}
