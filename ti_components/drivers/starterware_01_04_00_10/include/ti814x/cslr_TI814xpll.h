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
#ifndef CSLR_TI814XPLL_H_
#define CSLR_TI814XPLL_H_

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif


typedef struct {
    UInt32          CONTROL_REVISION;
    UInt32          CONTROL_HWINFO;
    UInt32          RSVD0[2];
    UInt8           CONTROL_SYSCONFIG;
    UInt32          RSVD1[87];
    UInt32          DSSPLL_PWRCTRL;
    UInt32          DSSPLL_CLKCTRL;
    UInt32          DSSPLL_TENABLE;
    UInt32          DSSPLL_TENABLEDIV;
    UInt32          DSSPLL_M2NDIV;
    UInt32          DSSPLL_MN2DIV;
    UInt32          DSSPLL_FRACDIV;
    UInt32          DSSPLL_BWCTRL;
    UInt32          DSSPLL_FRACCTRL;
    UInt32          DSSPLL_STATUS;
    UInt32          RSVD2[2];
    struct
    {
        UInt32          PWRCTRL;
        UInt32          CLKCTRL;
        UInt32          TENABLE;
        UInt32          TENABLEDIV;
        UInt32          M2NDIV;
        UInt32          MN2DIV;
        UInt32          FRACDIV;
        UInt32          BWCTRL;
        UInt32          FRACCTRL ;
        UInt32          STATUS;
        UInt32          RSVD3[2];
    }VideoPll_Factors[3];
    UInt32          RSVD5[36];
    UInt32          OSC_SRC;
    UInt32          RSVD6[1];
    UInt32          VIDEO_PLL_CLKSRC; /* TODO Required */
    UInt32          RSVD7[4];
    UInt32          HDMI_I2S_CLKSRC;
}CSL_Pll_CtrlRegs;


typedef volatile CSL_Pll_CtrlRegs           *CSL_PllCtrlRegs;


#define CLKCTRL                 0x4
#define TENABLE                 0x8
#define TENABLEDIV              0xC
#define M2NDIV                  0x10
#define MN2DIV                  0x14
#define STATUS                  0x24
#define OSC_FREQ                20

/* Add the macros for the ADPLLLJx bitfields */

/* ADPLLLJx_PWRCTRL */
#define ADPLLLJx_PWRCTRL_PONIN_MASK                 (0x00000020U)
#define ADPLLLJx_PWRCTRL_PONIN_SHIFT                (0x5U)

#define ADPLLLJx_PWRCTRL_PGOODIN_MASK               (0x000000010U)
#define ADPLLLJx_PWRCTRL_PGOODIN_SHIFT              (0x4U)

#define ADPLLLJx_PWRCTRL_RET_MASK                   (0x00000008U)
#define ADPLLLJx_PWRCTRL_RET_SHIFT                  (0x3U)

#define ADPLLLJx_PWRCTRL_ISORET_MASK                (0x00000004U)
#define ADPLLLJx_PWRCTRL_ISORET_SHIFT               (0x2U)

#define ADPLLLJx_PWRCTRL_ISOSCAN_MASK               (0x00000002U)
#define ADPLLLJx_PWRCTRL_ISOSCAN_SHIFT              (0x1U)

#define ADPLLLJx_PWRCTRL_OFFMODE_MASK               (0x000000001U)
#define ADPLLLJx_PWRCTRL_OFFMODE_SHIFT              (0x0U)

#define ADPLLLJx_CLKCTRL_CYCLESLIPEN_MASK           (0x80000000U)
#define ADPLLLJx_CLKCTRL_CYCLESLIPEN_SHIFT          (31U)

#define ADPLLLJx_CLKCTRL_ENSSC_MASK                 (0x40000000U)
#define ADPLLLJx_CLKCTRL_ENSSC_SHIFT                (30U)

#define ADPLLLJx_CLKCTRL_NWELLTRIM_MASK             (0x1F000000U)
#define ADPLLLJx_CLKCTRL_NWELLTRIM_SHIFT            (24U)

#define ADPLLLJx_CLKCTRL_IDLE_MASK                  (0x00800000U)
#define ADPLLLJx_CLKCTRL_IDLE_SHIFT                 (23U)

#define ADPLLLJx_CLKCTRL_BYPASSACKZ_MASK            (0x00400000U)
#define ADPLLLJx_CLKCTRL_BYPASSACKZ_SHIFT           (22U)

#define ADPLLLJx_CLKCTRL_STBYRET_MASK               (0x00200000U)
#define ADPLLLJx_CLKCTRL_STBYRET_SHIFT              (21U)

#define ADPLLLJx_CLKCTRL_CLKOUTEN_MASK              (0x00100000U)
#define ADPLLLJx_CLKCTRL_CLKOUTEN_SHIFT             (20U)

#define ADPLLLJx_CLKCTRL_ULOWCLKEN_MASK             (0x00040000U)
#define ADPLLLJx_CLKCTRL_ULOWCLKEN_SHIFT            (18U)

#define ADPLLLJx_CLKCTRL_CLKDCOLDOPWDNZ_MASK        (0x00020000U)
#define ADPLLLJx_CLKCTRL_CLKDCOLDOPWDNZ_SHIFT       (17U)

#define ADPLLLJx_CLKCTRL_M2PWDNZ_MASK               (0x00010000U)
#define ADPLLLJx_CLKCTRL_M2PWDNZ_SHIFT              (16U)

#define ADPLLLJx_CLKCTRL_SELFREQDCO_MASK            (0x00001C00U)
#define ADPLLLJx_CLKCTRL_SELFREQDCO_SHIFT           (10U)

#define ADPLLLJx_CLKCTRL_RELAXED_LOCK_MASK          (0x00000100U)
#define ADPLLLJx_CLKCTRL_RELAXED_LOCK_SHIFT         (8U)

#define ADPLLLJx_CLKCTRL_TINITZ_MASK                (0x00000001U)
#define ADPLLLJx_CLKCTRL_TINITZ_SHIFT               (0U)

#define ADPLLLJx_TENABLE_MASK                       (0x00000001U)
#define ADPLLLJx_TENABLE_SHIFT                      (0U)

#define ADPLLLJx_TENABLEDIV_MASK                    (0x00000001U)
#define ADPLLLJx_TENABLEDIV_SHIFT                   (0U)

#define ADPLLLJx_M2NDIV_M_MASK                      (0x0x007F0000U)
#define ADPLLLJx_M2NDIV_M_SHIFT                     (16U)

#define ADPLLLJx_M2NDIV_N_MASK                      (0x000000FFU)
#define ADPLLLJx_M2NDIV_N_SHIFT                     (0U)

#define ADPLLLJx_FRACTONAL_DIVIDER_REGSD_MASK       (0xFF000000U)
#define ADPLLLJx_FRACTONAL_DIVIDER_REGSD_SHIFT      (24U)

#define ADPLLLJx_FRACTONAL_DIVIDER_FRACTIONALM_MASK (0x0003FFFFU)
#define ADPLLLJx_FRACTONAL_DIVIDER_FRACTIONALM_SHIFT (0x0)

#define ADPLLLJx_BWCTRL_BWCONTROL_MASK              (0x00000006U)
#define ADPLLLJx_BWCTRL_BWCONTROL_SHIFT             (1U)

#define ADPLLLJx_BWCTRL_BW_INCR_DECRZ_MASK          (0x00000001U)
#define ADPLLLJx_BWCTRL_BW_INCR_DECRZ_SHIFT         (0U)

#define ADPLLLJx_FRACT_CTRL_DOWNSPREAD_MASK         (0x80000000U)
#define ADPLLLJx_FRACT_CTRL_DOWNSPREAD_SHIFT        (31U)

#define ADPLLLJx_FRACT_CTRL_MODFREQDIVEXP_MASK      (0x70000000U)
#define ADPLLLJx_FRACT_CTRL_MODFREQDIVEXP_SHIFT     (28U)

#define ADPLLLJx_FRACT_CTRL_MODFREQDIVMAN_MASK      (0x0FE00000U)
#define ADPLLLJx_FRACT_CTRL_MODFREQDIVMAN_SHIFT     (21U)

#define ADPLLLJx_FRACT_CTRL_DELTAMSTEPINT_MASK      (0x001C0000U)
#define ADPLLLJx_FRACT_CTRL_DELTAMSTEPINT_SHIFT     (18U)

#define ADPLLLJx_FRACT_CTRL_DELTAMSTEPFRAC_MASK     (0x0003FFFFU)
#define ADPLLLJx_FRACT_CTRL_DELTAMSTEPFRAC_SHIFT     (0U)

#define ADPLLLJx_STATUS_PONOUT_MASK                 (0x80000000U)
#define ADPLLLJx_STATUS_PONOUT_SHIFT                (31U)

#define ADPLLLJx_STATUS_PGOODOUT_MASK               (0x40000000U)
#define ADPLLLJx_STATUS_PGOODOUT_SHIFT              (30U)

#define ADPLLLJx_STATUS_LDOPWDN_MASK                (0x20000000U)
#define ADPLLLJx_STATUS_LDOPWDN_SHIFT               (29U)

#define ADPLLLJx_STATUS_RECAL_BSTATUS3_MASK         (0x10000000U)
#define ADPLLLJx_STATUS_RECAL_BSTATUS3_SHIFT        (28U)

#define ADPLLLJx_STATUS_RECAL_OPPIN_MASK            (0x08000000U)
#define ADPLLLJx_STATUS_RECAL_OPPIN_SHIFT           (27U)

#define ADPLLLJx_STATUS_PHASELOCK_MASK              (0x00000400U)
#define ADPLLLJx_STATUS_PHASELOCK_SHIFT             (10U)

#define ADPLLLJx_STATUS_FREQLOCK_MASK               (0x00000200U)
#define ADPLLLJx_STATUS_FREQLOCK_SHIFT              (9U)

#define ADPLLLJx_STATUS_BYPASSACK_MASK              (0x00000100U)
#define ADPLLLJx_STATUS_BYPASSACK_SHIFT             (8U)

#define ADPLLLJx_STATUS_STBYRETACK_MASK             (0x00000080U)
#define ADPLLLJx_STATUS_STBYRETACK_SHIFT            (7U)

#define ADPLLLJx_STATUS_LOSSREF_MASK                (0x00000040U)
#define ADPLLLJx_STATUS_LOSSREF_SHIFT               (6U)

#define ADPLLLJx_STATUS_CLKOUTACK_MASK              (0x00000020U)
#define ADPLLLJx_STATUS_CLKOUTACK_SHIFT             (5U)

#define ADPLLLJx_STATUS_LOCK2_MASK                  (0x00000010U)
#define ADPLLLJx_STATUS_LOCK2_SHIFT                 (4U)

#define ADPLLLJx_STATUS_M2CHANGEACK_MASK            (0x00000008U)
#define ADPLLLJx_STATUS_M2CHANGEACK_SHIFT           (3U)

#define ADPLLLJx_STATUS_SSCACK_MASK                 (0x00000004U)
#define ADPLLLJx_STATUS_SSCACK_SHIFT                (2U)

#define ADPLLLJx_STATUS_HIGHJITTER_MASK             (0x00000002U)
#define ADPLLLJx_STATUS_HIGHJITTER_SHIFT            (1U)

#define ADPLLLJx_STATUS_BYPASS_MASK                 (0x00000001U)
#define ADPLLLJx_STATUS_BYPASS_SHIFT                (0U)

#define VID_PLL_CLK_SRC_DVO2_CLK_SRC_MASK      (0x01000000U)
#define VID_PLL_CLK_SRC_DVO2_CLK_SRC_SHIFT     (24U)

#define VID_PLL_CLK_SRC_VID_PLL_CLK2_SRC_MASK       (0x00000001U)
#define VID_PLL_CLK_SRC_VID_PLL_CLK2_SRC_SHIFT      (1U)

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif
#endif /* #ifndef CSLR_TI814XPLL_H_ */
