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
 *  \file bsp_platformTI814x.c
 *
 *  \brief Implements the TI814x platform specific functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <xdc/std.h>
#include <common/bsp_types.h>
#include <osal/bsp_osal.h>
#include <common/trace.h>
#include <common/bsp_config.h>
#include <platforms/bsp_platform.h>
#include <ti814x/soc_defines.h>
#include <ti814x/cslr_TI814xprcm.h>
#include <ti814x/cslr_TI814xpll.h>
#include <soc.h>
#include <hw/hw_types.h>
#include <bsp_platformTI814x.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief PLL Control Module Base Address*/
#define BSP_CONTROL_MODULE_PLL_CTRL_BASE_ADDR   (CSL_PLL_BASE)

/** \brief Control Module Device Configuration Base Address */
#define BSP_CTRL_MODULE_DEV_CFG_BASE_ADDR       (CSL_CTRL_MODULE_BASE + \
                                                 0x0600U)

/* Default Values for DDR PLL configuration to get clock for I2C and CEC */
#define BSP_DDR_INT_FREQ2               (0x8U)
#define BSP_DDR_FRACT_FREQ2             (0xD99999U)
#define BSP_DDR_MDIV2                   (0x1EU)
#define BSP_DDR_SYCCLK10_DIV            (0x0U)

#define BSP_PRCM_CLKTRCTRL_NO_SLEEP     (0U)
#define BSP_PRCM_CLKTRCTRL_SW_SLEEP     (1U)
#define BSP_PRCM_CLKTRCTRL_SW_WKUP      (2U)
#define BSP_PRCM_CLKTRCTRL_HW_AUTO      (3U)

#define BSP_PRCM_MODULE_DISABLE         (0U)
#define BSP_PRCM_MODULE_ENABLE          (2U)

#define BSP_PRCM_MAX_REP_CNT            (100U)

/* ADPLLJ_CLKCRTL_Register Value Configurations
 * ADPLLJ_CLKCRTL_Register SPEC bug  bit 19,bit29 -- CLKLDOEN,CLKDCOEN */
#define ADPLLJ_CLKCRTL_HS2              (0x00000801U)
/*HS2 Mode,TINTZ =1  --used by all PLL's except HDMI */
#define ADPLLJ_CLKCRTL_HS1              (0x00001001U)
/* HS1 Mode,TINTZ =1  --used only for HDMI  */
#define ADPLLJ_CLKCRTL_CLKDCO           (0x200a0000U)
/* Enable CLKDCOEN,CLKLDOEN,CLKDCOPWDNZ -- used for HDMI,USB */
#define BSP_TI814X_KHz                  (1000U)
#define BSP_TI814X_MHz                  (BSP_TI814X_KHz * BSP_TI814X_KHz)
#define BSP_TI814X_EVM_OSC_FREQ         (20U * BSP_TI814X_MHz)
#define UINT32_VALUE_ZERO           (UInt32) (0U)
#define UINT32_VALUE_ONE            (UInt32) (1U)
#define UINT32_VALUE_TWO            (UInt32) (2U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* \brief structure to keep track of pll configurations for a video mode */
typedef struct
{
    UInt32 dividerN;
    /**< Divider N for the PLL.*/
    UInt32 multiplierM;
    /**< Multiplier M for the PLL.*/
    UInt32 dividerM2;
    /**< Divider M2 for the PLL.*/
    UInt32 clkCtrlValue;
    /**< For comparison based on the clkOut used */
} Bsp_VideoPllCtrl;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
#ifdef TI814X_FAMILY_BUILD

static Int32 Bsp_platformTI814xSetPinMux(void);
static Int32 Bsp_platformTI814xSetIntMux(void);
static Int32 Bsp_platformTI814xEnableHdvpssClk(void);
static Int32 Bsp_platformTI814xEnableI2c(void);
static void udelay(Int32 delay_usec);

static Int32 Bsp_platformPllCfg(volatile UInt32 baseAddr,
                                UInt32          N,
                                UInt32          M,
                                UInt32          M2,
                                UInt32          clkCtrlValue);
static Int32 Bsp_platformTI814xConfigHdvpssPll(void);
static Int32 Bsp_getDividers(Bsp_VideoPllCtrl *config,
                             UInt32            reqOutClk,
                             UInt32            vencClk);
Int32 Bsp_platformTI814xSetVencPixClk(const Bsp_SystemVPllClk *vpllCfg);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static CSL_PrcmRegs    gBspPrcmRegs = (CSL_PrcmRegs) CSL_PRCM_BASE;

static CSL_PllCtrlRegs gBspPllCtrlRegs =
    (CSL_PllCtrlRegs) BSP_CONTROL_MODULE_PLL_CTRL_BASE_ADDR;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 Bsp_platformTI814xInit(const Bsp_PlatformInitParams *initParams)
{
    Int32 status = BSP_SOK;

    if (TRUE == initParams->isPinMuxSettingReq)
    {
        Bsp_platformTI814xSetPinMux();
    }

    Bsp_platformTI814xSetIntMux();

    /* Initialize Pixel Clock */
    status += Bsp_platformTI814xConfigHdvpssPll();
    status += Bsp_platformTI814xEnableHdvpssClk();
    status += Bsp_platformTI814xEnableI2c();

    return (status);
}

Int32 Bsp_platformTI814xDeInit(void)
{
    Int32 status = BSP_SOK;

    return (status);
}

static Int32 Bsp_platformTI814xConfigHdvpssPll(void)
{
    UInt32 baseAddr;
    baseAddr = (UInt32) & gBspPllCtrlRegs->DSSPLL_PWRCTRL;
    Bsp_platformPllCfg(baseAddr, (UInt32) 19, (UInt32) 800, (UInt32) 4,
                       (UInt32) ADPLLJ_CLKCRTL_HS2);
    return (BSP_SOK);
}

Int32 Bsp_platformTI814xSetVencPixClk(const Bsp_SystemVPllClk *vpllCfg)
{
    Bsp_VideoPllCtrl  pllDividers;
    Int32 rtnValue = BSP_SOK;
    Bsp_VPllOutputClk pllOutputClk;
    GT_assert(BspPlatTrace, NULL != gBspPllCtrlRegs);
    GT_assert(BspPlatTrace, NULL != gBspPrcmRegs);
    GT_assert(BspPlatTrace, NULL != vpllCfg);

    if (BSP_SYSTEM_VPLL_OUTPUT_VENC_RF == vpllCfg->outputVenc)
    {
        GT_assert(BspPlatTrace, 54000U == vpllCfg->outputClk);
    }
    else if ((BSP_SYSTEM_VPLL_OUTPUT_VENC_A == vpllCfg->outputVenc) ||
             (BSP_SYSTEM_VPLL_OUTPUT_VENC_D == vpllCfg->outputVenc))
    {
        GT_assert(BspPlatTrace, 54000U != vpllCfg->outputClk);
    }
    else
    {
        /* MISRA IF.NO.ELSE Not a valid case */
        GT_assert(BspPlatTrace, FALSE);
    }

    if (rtnValue == BSP_SOK)
    {
        rtnValue = Bsp_getDividers(&pllDividers, vpllCfg->outputClk,
                                   vpllCfg->outputVenc);

        if (rtnValue == BSP_SOK)
        {
            /*HDMI shares the same PLL as VENC_A*/
            if (vpllCfg->outputVenc == BSP_SYSTEM_VPLL_OUTPUT_HDMI)
            {
                pllOutputClk = BSP_SYSTEM_VPLL_OUTPUT_VENC_A;
            }
            else
            {
                pllOutputClk = (Bsp_VPllOutputClk) vpllCfg->outputVenc;
            }

            GT_assert(BspAppTrace, (pllOutputClk <= BSP_SYSTEM_VPLL_OUTPUT_HDMI));

            rtnValue = Bsp_platformPllCfg((UInt32)
                                          & gBspPllCtrlRegs->VideoPll_Factors[
                                              pllOutputClk].PWRCTRL,
                                          pllDividers.dividerN,
                                          pllDividers.multiplierM,
                                          pllDividers.dividerM2,
                                          pllDividers.clkCtrlValue);
        }
    }

    return (rtnValue);
}

/*******************************************************************************
 ****
 ****                                   ********* RANGE ************
 ****   REF_CLK       = (OSC_FREQ)/N+1  [  REF_CLK < 2.5MHz      ]
 ****   DCOCLK_HS2    = (REF_CLK)*M     [500  < DCOCLK < 1000MHz ]
 ****   DCOCLK_HS1    = (REF_CLK)*M     [1000 < DCOCLK < 2000MHz ]--used for
 ****   HDMI CLKDCO
 ****   CLKOUT        =  DCOCLK/M2      [10   < CLKOUT < 2000MHz ]--used for
 ****   DVO2, SD
 ****   N+1                             [1..256]
 ****   M                               [2..4095]
 ****   M2                              [1..127]
 ****
 ****
 *******************************************************************************/
/* Get the divider value for video PLL for the specified frequency.
 * N requires to start with 19 - TODO check with 0x0 */
static Int32 Bsp_getDividers(Bsp_VideoPllCtrl *config, UInt32 reqOutClk,
                             UInt32 vencClk)
{
    Int32  rtnValue = BSP_EFAIL;
    Int32  n, m, m2;
    Float  refClk, dcoClk;
    UInt32 clkOut;
    UInt8  hsMode = 1U;  /* 1: HS2, 2:HS1*/
    UInt8  factor = 1U;
    UInt32 padding;
    UInt32 tempVal;
    /* The input clock is specified in terms of KiloHertz, require MHz to work
     * with */
    if (vencClk == BSP_SYSTEM_VPLL_OUTPUT_HDMI)
    {
        padding = reqOutClk % 500U;
        if (padding)
        {
            if (padding >= 250U)
            {
                reqOutClk += (500U - padding);
            }
            else
            {
                reqOutClk -= padding;
            }
        }
        /*if Freq is less than 50MHz, post-M2 clock is used to drive
         * HDMI, therefore factor should b1. the other case factor is 10 since
         * pre-M2 clock is to driver the HDMI
         * check HDMI wrapper spec and TI814X Clock Arch document to
         * further understand this*/
        if (reqOutClk >= 50000U)
        {
            factor = 10U;
        }
        /*CLK must be 10x if it is for HDMI*/
        reqOutClk *= 1000U * 10U;
    }
    else
    {
        factor     = 1U;
        reqOutClk *= 1000U;
    }
    if (reqOutClk > (1000U * BSP_TI814X_MHz))
    {
        /*must use HS1 mode*/
        hsMode = 2U;
    }

    for (n = (Int32) 19; ((n < (Int32) 256) && (rtnValue != BSP_SOK)); n++)
    {
        tempVal = (UInt32) n + 1U;
        refClk  = (Float) BSP_TI814X_EVM_OSC_FREQ / (Float) tempVal;
        if (refClk < ((Float) 2.5 * (Float) BSP_TI814X_MHz))
        {
            for (m = 2; ((m < 4095) && (rtnValue != BSP_SOK)); m++)
            {
                dcoClk = (refClk) * (Float) m;
                if ((dcoClk >
                     ((Float) 500 * (Float) BSP_TI814X_MHz *
                      (Float) hsMode)) &&
                    (dcoClk <
                     ((Float) 1000 * (Float) BSP_TI814X_MHz * (Float) hsMode)))
                {
                    for (m2 = 1; m2 <= 127; m2++)
                    {
                        clkOut = ((UInt32) dcoClk / (UInt32) m2);
                        if (clkOut == reqOutClk)
                        {
                            config->dividerN    = n;
                            config->multiplierM = m;
                            config->dividerM2   = (UInt32) m2 * (UInt32) factor;
                            if (hsMode == 1U)
                            {
                                config->clkCtrlValue = ADPLLJ_CLKCRTL_HS2;
                            }
                            else
                            {
                                config->clkCtrlValue = ADPLLJ_CLKCRTL_HS1;
                            }
                            /*enable the CLKDCOLDO and CLKOUTLDO for HDMI*/
                            if (vencClk == BSP_SYSTEM_VPLL_OUTPUT_HDMI)
                            {
                                config->clkCtrlValue |= ADPLLJ_CLKCRTL_CLKDCO;
                            }
                            rtnValue = BSP_SOK;
                            break;
                        }
                    }
                }
            }
            /* Work around for the hardware bug where it failed to set
             * 54k frequency with generated with the values generated by
             * getdivider function - Essentially m = 540 and M2 == 10 will not
             * work */
            if (reqOutClk == (54000U * 1000U))
            {
                config->dividerN    = 19;
                config->multiplierM = 1080;
                config->dividerM2   = 20;
                break;
            }
        }
    }
    return (rtnValue);
}

/*
 *  Setup pinmux in for capture/display
 *
 *  Pinmux setup is as shown below,
 *
 *  VIP0
 *  - YCC 16-bit        - Always ENABLED
 *  - YCC 24-bit        - ENABLED
 *  - CLK0              - Always ENABLED
 *  - CLK1              - Always ENABLED
 *  - HD/VD/DE/FLD0     - ENABLED
 *  - HD/VD/DE/FLD1     - DISABLED
 *
 *  VIP1
 *  - YCC 16-bit        - ENABLED
 *  - CLK0              - ENABLED
 *  - CLK1              - ENABLED
 *  - HD/VD/DE/FLD0     - DISABLED
 *  - HD/VD/DE/FLD1     - DISABLED
 *
 *  VOUT0 (DVO2)
 *  - CLK               - Always ENABLED
 *  - HD/VD/DE/FLD      - ENABLED
 *  - YCC 16-bit        - Always ENABLED
 *  - YCC 20-bit        - ENABLED
 *  - RGB/YCC 24-bit    - ENABLED
 *  - RGB/YCC 30-bit    - ENABLED
 *
 *  VOUT1 (DVO1)
 *  - CLK               - DISABLED
 *  - HD/VD/DE/FLD      - DISABLED
 *  - YCC 16-bit        - DISABLED
 *  - YCC 20-bit        - DISABLED
 *  - RGB/YCC 24-bit    - DISABLED
 *  - RGB/YCC 30-bit    - DISABLED
 *
 *  I2C2
 *  - SDA               - ENABLED
 *  - SCL               - ENABLED
 *
 *  HDMI I2C0
 *  - SDA               - ENABLED
 *  - SCL               - ENABLED
 */
static Int32 Bsp_platformTI814xSetPinMux(void)
{
    /*Configure Pin mux for MCASP Instance 2 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0898U, 0x60001U); /* ACLKX */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x089CU, 0x60001U); /* FSX */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x08A0U, 0x60001U); /* AXR0 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x08A4U, 0x60001U); /* AXR1 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x083CU, 0x60001U); /* AHCLKX */

    /*Configure Pin mux for UART Instance 0 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0914U, 0x60001U);
    /* PINCTRL_UART0_RXD */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0918U, 0x60001U);
    /* PINCTRL_UART0_TXD */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x091CU, 0x60001U);
    /* PINCTRL_UART0_CTSn */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0920U, 0x60001U);
    /* PINCTRL_UART0_RTSn */

    /* McSPI Instance configuration */
    /*Configure Pin mux for McSPI Instance 0 (McSPI1) */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x093CU, 0x60001U); /* CS1 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0940U, 0x60001U); /* CS0 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0944U, 0x40001U); /* SCLK */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0948U, 0x40001U); /* D1 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x094CU, 0x60001U); /* D0 */

    /*Configure Pin mux for McSPI Instance 1 (McSPI2) */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0950U, 0x60001U); /* CS1 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0954U, 0x60001U); /* CS0 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0958U, 0x40001U); /* SCLK */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x095CU, 0x40001U); /* D1 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0960U, 0x60001U); /* D0 */

    /* I2c2  configuration Function 6*/
    /* i2c2_scl_mux0 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0924U, 0x60020U);
    /* i2c2_sda_mux0 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0928U, 0x60020U);
    /* HDMI I2C_scl and I2C_sda Function 2*/
    /* hdmi_ddc_scl_mux0 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0934U, 0x60002U);
    /* hdmi_ddc_sda_mux0 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0938U, 0x60002U);
    /* hdmi_hpd_mux0 pinmmr112[4] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x09BCU, 0x40010U);
    /* hdmi_cec_mux0 pinmmr111[4] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x09B8U, 0x60010U);
    /* TODO HDMI CEC and HPD to be added in pinmux */
    /* Currently its shared with GPMC. */

    /* VIN0 TODO Do we need to enable RXACTIVE Bit in pinmux for input pins? */
    /* Vin0 hsync1 and vin0 vsync1 */
    /* vin0_clk1 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0A14U, 0x50001U);
    /* vin0_de0_mux0 DeSelect input */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0A18U, UINT32_VALUE_ZERO);
    /* vin0_fld0_mux0 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0A1CU, 0x50001U);
    /* vin0_clk0 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0A20U, 0x50001U);
    /* vin0_hsync0 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0A24U, 0x50001U);
    /* vin0_vsync0 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0A28U, 0x50001U);
    /* vin0_d0 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0A2CU, 0x50001U);
    /* vin0_d1 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0A30U, 0x50001U);
    /* vin0_d2 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0A34U, 0x50001U);
    /* vin0_d3 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0A38U, 0x50001U);
    /* vin0_d4 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0A3cU, 0x50001U);
    /* vin0_d5 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0A40U, 0x50001U);
    /* vin0_d6 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0A44U, 0x50001U);
    /* vin0_d7 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0A48U, 0x50001U);
    /* vin0_d8 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0A4cU, 0x50001U);
    /* vin0_d9 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0A50U, 0x50001U);
    /* vin0_d10 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0A54U, 0x50001U);
    /* vin0_d11 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0A58U, 0x50001U);
    /* vin0_d12 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0A5CU, 0x50001U);
    /* vin0_d13 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0A60U, 0x50001U);
    /* vin0_d14 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0A64U, 0x50001U);
    /* vin0_d15 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0A68U, 0x50001U);
    /* vin0_d16 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0A6CU, 0x50001U);
    /* vin0_d17 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0A70U, 0x50001U);
    /* vin0_d18 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0A74U, 0x50001U);
    /* vin0_d19 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0A78U, 0x50001U);
    /* vin0_d20 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0A7CU, 0x50001U);
    /* vin0_d21 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0A80U, 0x50001U);
    /* vin0_d22 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0A84U, 0x50001U);
    /* vin0_d23 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0A88U, 0x50001U);
    /* vin0_de0_mux1 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0A8CU, 0x50001U);
    /* vin0_de1 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0A90U, 0x50001U);
    /* vin0_fld0_mux1 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0A94U, 0x50001U);
    /* vin0_fld1 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0A98U, 0x50001U);

    /* Vout 0 configuration DVO2 Function 1*/
    /* TODO There are two pins for the fid. Need to see whichone is used */
    /* vout0_fid_mux1 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0AB8U, UINT32_VALUE_ZERO);
    /* vout0_clk */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0ABCU, UINT32_VALUE_ZERO);
    /* vout0_hsync */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0AC0U, UINT32_VALUE_ZERO);
    /* vout0_vsync */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0AC4U, UINT32_VALUE_ZERO);
    /* vout0_avid */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0AC8U, UINT32_VALUE_ZERO);
    /* vout0_b_cb_c[2] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0ACCU, UINT32_VALUE_ZERO);
    /* vout0_b_cb_c[3] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0AD0U, UINT32_VALUE_ZERO);
    /* vout0_b_cb_c[4] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0AD4U, UINT32_VALUE_ZERO);
    /* vout0_b_cb_c[5] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0AD8U, UINT32_VALUE_ZERO);
    /* vout0_b_cb_c[6] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0ADCU, UINT32_VALUE_ZERO);
    /* vout0_b_cb_c[7] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0AE0U, UINT32_VALUE_ZERO);
    /* vout0_b_cb_c[8] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0AE4U, UINT32_VALUE_ZERO);
    /* vout0_b_cb_c[9] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0AE8U, UINT32_VALUE_ZERO);
    /* vout0_g_y_yc[2] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0AECU, UINT32_VALUE_ZERO);
    /* vout0_g_y_yc[3] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0AF0U, UINT32_VALUE_ZERO);
    /* vout0_g_y_yc[4] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0AF4U, UINT32_VALUE_ZERO);
    /* vout0_g_y_yc[5] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0AF8U, UINT32_VALUE_ZERO);
    /* vout0_g_y_yc[6] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0AFCU, UINT32_VALUE_ZERO);
    /* vout0_g_y_yc[7] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B00U, UINT32_VALUE_ZERO);
    /* vout0_g_y_yc[8] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B04U, UINT32_VALUE_ZERO);
    /* vout0_g_y_yc[9] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B08U, UINT32_VALUE_ZERO);
    /* vout0_r_cr[2] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B0CU, UINT32_VALUE_ZERO);
    /* vout0_r_cr[3] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B10U, UINT32_VALUE_ZERO);
    /* vout0_r_cr[4] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B14U, UINT32_VALUE_ZERO);
    /* vout0_r_cr[5] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B18U, UINT32_VALUE_ZERO);
    /* vout0_r_cr[6] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B1CU, UINT32_VALUE_ZERO);
    /* vout0_r_cr[7] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B20U, UINT32_VALUE_ZERO);
    /* vout0_r_cr[8] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B24U, UINT32_VALUE_ZERO);
    /* vout0_r_cr[9] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B28U, UINT32_VALUE_ZERO);

    /* VIN1 Configuration Function 3*/
    /* vin1_hsync0 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B2CU, 0x50004U);
    /* this is function 2 */
    /* vin1_clk1 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x09F0U, 0x50002U);
    /* vin1_vsync0 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B30U, 0x50004U);
#ifdef ORIGIAL_PORT
    /* vin1_fid0 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B34U, 0x50004U);
#endif /* ORIGIAL_PORT */
       /* vin1_de0 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B34U, 0x50008U);

    /* vin1_clk0 */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B38U, 0x50004U);
    /* vin1a_d[0] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B3CU, 0x50004U);
    /* vin1a_d[1] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B40U, 0x50004U);
    /* vin1a_d[2] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B44U, 0x50004U);
    /* vin1a_d[3] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B48U, 0x50004U);
    /* vin1a_d[4] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B4CU, 0x50004U);
    /* vin1a_d[5] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B50U, 0x50004U);
    /* vin1a_d[6] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B54U, 0x50004U);
    /* vin1a_d[8] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B58U, 0x50004U);
    /* vin1a_d[9] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B5CU, 0x50004U);
    /* vin1a_d[10] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B60U, 0x50004U);
    /* vin1a_d[11] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B64U, 0x50004U);
    /* vin1a_d[12] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B68U, 0x50004U);
    /* vin1a_d[13] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B6CU, 0x50004U);
    /* vin1a_d[14] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B70U, 0x50004U);
    /* vin1a_d[15] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B74U, 0x50004U);
    /* vin1a_d[16] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B78U, 0x50004U);
    /* vin1a_d[17] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B7CU, 0x50004U);
    /* vin1a_d[18] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B80U, 0x50004U);
    /* vin1a_d[19] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B84U, 0x50004U);
    /* vin1a_d[20] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B88U, 0x50004U);
    /* vin1a_d[21] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B8CU, 0x50004U);
    /* vin1a_d[22] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B90U, 0x50004U);
    /* vin1a_d[23] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B94U, 0x50004U);
    /* vin1a_d[7] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0B98U, 0x50004U);

#ifdef ORIGIAL_PORT
    /* Function 2 */
    /* vin1a_d[0] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0BA8U, 0x50002U);
    /* vin1a_d[1] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0BACU, 0x50002U);
    /* vin1a_d[2] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0BB0U, 0x50002U);
    /* vin1a_d[3] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0BB4U, 0x50002U);
    /* vin1a_d[4] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0BB8U, 0x50002U);
    /* vin1a_d[5] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0BBCU, 0x50002U);
    /* vin1a_d[6] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0BC0U, 0x50002U);
    /* vin1a_d[7] */
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0BC4U, 0x50002U);
#endif /* ORIGIAL_PORT */

    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0C18U, 0x60001U);      /*I2c0-SDA*/
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0C1CU, 0x60001U);      /*I2c0-SCL*/

    /* Power ON the McSPI Instances in the PRCM  */
    HW_WR_REG32(0x48181588U, UINT32_VALUE_TWO);
    HW_WR_REG32(0x4818158CU, UINT32_VALUE_TWO);
    HW_WR_REG32(0x48181590U, UINT32_VALUE_TWO);

    /* Power ON the UART Instances in the PRCM  */
    HW_WR_REG32(0x48180000U + 0x1550U, UINT32_VALUE_TWO); /* UART0 */
    HW_WR_REG32(0x48180000U + 0x1554U, UINT32_VALUE_TWO); /* UART1 */
    HW_WR_REG32(0x48180000U + 0x1558U, UINT32_VALUE_TWO); /* UART2 */
    HW_WR_REG32(0x48180000U + 0x1400U, (UInt32) 0x2100U); /* UART3 */

    /* Power on the McASP instances 2 in the PRCM */
    HW_WR_REG32(0x48180000U + 0x1548U, UINT32_VALUE_TWO);

    /* TODO Find proper place for this Set the divider for the SYSCLK10 */
    *(UInt32 *) 0x48180324 = 3;

    return (BSP_SOK);
}

static Int32 Bsp_platformTI814xSetIntMux(void)
{
    volatile UInt32 int_mux;

    /* I2C2 interrupt is routed through I2C1 interrupt through the
     * crossbar. For this, INT_MUX_[#int_number] register in the
     * Chip Control Module needs to be programmed.
     * INT_MUX_[#int_number] registers start from 0xF54
     * offset and one register is used to program 4 interrupt
     * muxes (6 bits for each mux, 2 bits reserved).
     * After reset INT_MUX_[#int_number] defaults to 000000, which
     * maps the interrupt from default mapping to interrupt_[#int_number].
     *
     * I2C_INT1 is mapped to interrupt line 19 and
     * INTMUX 16 to 19 --> 0x0f64. So read it first,
     * modify the respective bit field and write is back.
     */
    int_mux = HW_RD_REG32(CSL_CTRL_MODULE_BASE + 0x0f64U);
    /* I2CINT2 value = 4, INT_MUX_19_SHIFT = 24*/
    int_mux |= ((UInt32) 4U << 24U);
    HW_WR_REG32(CSL_CTRL_MODULE_BASE + 0x0f64U, int_mux);

    return (BSP_SOK);
}

Bsp_PlatformCpuRev Bsp_platformTI814xGetCpuRev(void)
{
    UInt32 cpuId, cpuRev;
    Bsp_PlatformCpuRev cpuRevEnum;

    /* Read CPU ID */
    cpuId = HW_RD_REG32(BSP_CTRL_MODULE_DEV_CFG_BASE_ADDR + 0x0000U);

    cpuRev = ((cpuId >> 28U) & 0x0FU);
    switch (cpuRev)
    {
#ifdef TI8149_BUILD
        case 0x8U:
#endif  /* TI8149_BUILD */
        case 0x0U:
            cpuRevEnum = BSP_PLATFORM_CPU_REV_1_0;
            break;

        case 0xCU:  /* Certain intial sample of PG 2.1 has C but the production
                     * samples should read out 3 */
        case 0x3U:
            cpuRevEnum = BSP_PLATFORM_CPU_REV_2_1;
            break;

        case 0x4U:
            cpuRevEnum = BSP_PLATFORM_CPU_REV_3_0;
            break;

        default:
            /* Default to last known version */
            GT_0trace(
                BspPlatTrace, GT_INFO,
                "PLATFORM: UNKNOWN CPU detected, defaulting to BSP_PLATFORM_CPU_REV_2_1\n");
            cpuRevEnum = BSP_PLATFORM_CPU_REV_2_1;
            break;
    }

    return (cpuRevEnum);
}

Bsp_PlatformPackageType Bsp_platformTI814xGetPackageType(void)
{
    return (BSP_PLATFORM_PACKAGE_TYPE_UNKNOWN);
}

Int32 Bsp_platformTI814xSimVideoInputSelect(UInt32 vipInstId,
                                            UInt32 fileId,
                                            UInt32 pixelClk)
{
    volatile UInt32 *pRegs[2];
    UInt32           instId, portId;
    Int32 status = BSP_SOK;

    if (vipInstId >= 4U)
    {
        status = BSP_EFAIL;
    }

    if (BSP_SOK == status)
    {
        pRegs[0] = (UInt32 *) (SOC_HDVPSS_BASE + 0xE100U);
        pRegs[1] = (UInt32 *) (SOC_HDVPSS_BASE + 0xE200U);

        instId = vipInstId / 2U;
        portId = vipInstId % 2U;

        pRegs[instId][0U + portId] = fileId; /* MISRA.PTR.ARITH */
        pRegs[instId][2U + portId] = pixelClk;
    }

    return status;
}

/** \brief Function to enable HDVPSS clock */
static Int32 Bsp_platformTI814xEnableHdvpssClk(void)
{
    volatile UInt32 repeatCnt;
    volatile UInt32 regValue;

    GT_assert(BspPlatTrace, NULL != gBspPrcmRegs);
    /* Bring the HDVPSS and HDMI out of reset */
    gBspPrcmRegs->RM_HDVPSS_RSTCTRL = 0x0;

    /* Start a software forced  wakeup transition on the domain.*/
    regValue = (UInt32) 0x2;
    gBspPrcmRegs->CM_HDVPSS_CLKSTCTRL = regValue;
    /* Wait for 1000 cycles before checking for power update */
    udelay((Int32) 1000);

    /* Enable HDVPSS Clocks */
    regValue = (UInt32) 0x2;
    gBspPrcmRegs->CM_HDVPSS_HDVPSS_CLK_CTRL = regValue;
    /* Enable HDMI Clocks */
    regValue = (UInt32) 0x2;
    gBspPrcmRegs->CM_HDVPSS_HDMI_CLKCTRL = regValue;

    repeatCnt = 0;
    while (repeatCnt < BSP_PRCM_MAX_REP_CNT)
    {
        /* Check for
         * Current Power State Status
         * HDVPSS memory state status
         * Logic state status */
        regValue = gBspPrcmRegs->CM_HDVPSS_CLKSTCTRL;
        if ((regValue & (UInt32) 0x100) == (UInt32) 0x100)
        {
            break;
        }
        udelay((Int32) 1000);
        repeatCnt++;
    }
    if ((regValue & (UInt32) 0x100) != (UInt32) 0x100)
    {
        GT_0trace(BspPlatTrace, GT_ERR, "HDVPSS Clocks not enabled\n");
    }
    repeatCnt = 0;
    while (repeatCnt < BSP_PRCM_MAX_REP_CNT)
    {
        /* Check for
         * Current Power State Status
         * HDVPSS memory state status
         * Logic state status */
        regValue = gBspPrcmRegs->CM_HDVPSS_HDVPSS_CLK_CTRL;
        if ((regValue & (UInt32) 0x2) == (UInt32) 0x2)
        {
            break;
        }
        udelay((Int32) 1000);
        repeatCnt++;
    }
    if ((regValue & (UInt32) 0x2) != (UInt32) 0x2)
    {
        GT_0trace(BspPlatTrace, GT_ERR, "HDVPSS Clocks not enabled\n");
    }
    /* Bring the HDVPSS and HDMI out of reset */
    gBspPrcmRegs->RM_HDVPSS_RSTCTRL = 0x0;
    return (BSP_SOK);
}

/** \brief Function sets the SYSCLK10 to 48MHz. SysClk10 is used for CEC
 *   and I2C */
static Int32 Bsp_platformTI814xEnableI2c(void)
{
    volatile UInt32 repeatCnt;
    Int32           status = BSP_SOK;

    GT_assert(BspPlatTrace, NULL != gBspPrcmRegs);

    /* Enable Power Domain Transition */
    gBspPrcmRegs->CM_ALWON_I2C_02_CLKCTRL = 0x2;

    repeatCnt = 0U;
    while (repeatCnt < BSP_PRCM_MAX_REP_CNT)
    {
        if (((gBspPrcmRegs->CM_ALWON_I2C_02_CLKCTRL &
              CM_ALWON_I2C_02_CLKCTRL_IDLEST_MASK) >>
             CM_ALWON_I2C_02_CLKCTRL_IDLEST_SHIFT) == 0U)
        {
            break;
        }

        /* Wait for the 100 cycles */
        udelay((Int32) 1000);

        repeatCnt++;
    }

    if (((gBspPrcmRegs->CM_ALWON_I2C_02_CLKCTRL &
          CM_ALWON_I2C_02_CLKCTRL_IDLEST_MASK) >>
         CM_ALWON_I2C_02_CLKCTRL_IDLEST_SHIFT) != 0U)
    {
        GT_0trace(BspPlatTrace, GT_ERR, "=== I2C0/2 Clk is Non active ===\n");
        status = BSP_ETIMEOUT;
    }
    else
    {
        GT_0trace(BspPlatTrace, GT_INFO, "=== I2C0/2 Clk is active ===\n");
    }

    return status;
}

static void udelay(Int32 delay_usec)
{
    Int32 delay_msec;

    delay_msec = delay_usec / 1000;
    if (delay_msec == 0)
    {
        delay_msec = 1;
    }
    BspOsal_sleep((UInt32) delay_msec);
}

static Int32 Bsp_platformPllCfg(volatile UInt32 baseAddr,
                                UInt32          N,
                                UInt32          M,
                                UInt32          M2,
                                UInt32          clkCtrlValue)
{
    Int32           rtnValue;
    UInt32          m2nval, mn2val, read_clkctrl;
    volatile UInt32 repeatCnt = 0;
    volatile UInt32 clkCtrlVal;
    volatile UInt32 regReadVal;

    /* Put the PLL in bypass mode */
    clkCtrlVal  = HW_RD_REG32(baseAddr + (UInt32) CLKCTRL);
    clkCtrlVal |= UINT32_VALUE_ONE << 23U;
    HW_WR_REG32((baseAddr + (UInt32) CLKCTRL), clkCtrlVal);

    repeatCnt = 0U;
    while (repeatCnt < BSP_PRCM_MAX_REP_CNT)
    {
        if (((HW_RD_REG32(baseAddr + (UInt32) STATUS)) & 0x00000101U) ==
            0x00000101U)
        {
            break;
        }
        /* Wait for the 100 cycles */
        udelay((Int32) 10000);
        repeatCnt++;
    }
    if (((HW_RD_REG32(baseAddr + (UInt32) STATUS)) & 0x00000101U) ==
        0x00000101U)
    {
        ;
    }
    else
    {
        GT_0trace(BspPlatTrace, GT_ERR, "Not able to put PLL in idle!!!\n");
    }

    regReadVal  = HW_RD_REG32(baseAddr + (UInt32) CLKCTRL);
    regReadVal &= 0xfffffffeU;
    /* we would require a soft reset before we program the dividers */
    HW_WR_REG32(baseAddr + (UInt32) CLKCTRL, regReadVal);
    udelay((Int32) 3);

    /* Program the PLL for required frequency */
    m2nval = (M2 << 16) | N;
    mn2val = M;
    /*ref_clk     = OSC_FREQ/(N+1);
     * clkout_dco  = ref_clk*M;
     * clk_out     = clkout_dco/M2;
     */
    HW_WR_REG32((baseAddr + (UInt32) M2NDIV), m2nval);
    HW_WR_REG32((baseAddr + (UInt32) MN2DIV), mn2val);
    udelay((Int32) 3);
    HW_WR_REG32((baseAddr + (UInt32) TENABLEDIV), UINT32_VALUE_ONE);
    udelay((Int32) 3);
    HW_WR_REG32((baseAddr + (UInt32) TENABLEDIV), UINT32_VALUE_ZERO);
    udelay((Int32) 3);
    HW_WR_REG32((baseAddr + (UInt32) TENABLE), UINT32_VALUE_ONE);
    udelay((Int32) 3);
    HW_WR_REG32((baseAddr + (UInt32) TENABLE), UINT32_VALUE_ZERO);
    udelay((Int32) 3);
    read_clkctrl = HW_RD_REG32(baseAddr + (UInt32) CLKCTRL);
    /*configure the TINITZ(bit0) and CLKDCO bits if required */
    HW_WR_REG32(baseAddr + (UInt32) CLKCTRL,
                (read_clkctrl & 0xff7fe3ffU) | clkCtrlValue);
    read_clkctrl = HW_RD_REG32(baseAddr + (UInt32) CLKCTRL);

    /* poll for the freq,phase lock to occur */
    repeatCnt = 0U;
    while (repeatCnt < BSP_PRCM_MAX_REP_CNT)
    {
        if (((HW_RD_REG32(baseAddr + (UInt32) STATUS)) & 0x00000600U) ==
            0x00000600U)
        {
            break;
        }
        /* Wait for the 100 cycles */
        udelay((Int32) 10000);
        repeatCnt++;
    }
    if (((HW_RD_REG32(baseAddr + (UInt32) STATUS)) & 0x00000600U) ==
        0x00000600U)
    {
        rtnValue = BSP_SOK;
    }
    else
    {
        GT_0trace(BspPlatTrace, GT_ERR, "PLL Not Getting Locked!!!\n");
        rtnValue = BSP_EFAIL;
    }
    /*wait fot the clocks to get stabized */
    udelay((Int32) 1000);
    return (rtnValue);
}

#endif
