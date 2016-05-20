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
#ifndef CSLR_TI814XPRCM_H_
#define CSLR_TI814XPRCM_H_

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif


typedef struct {
    volatile UInt32      RSVD0[64];
    /**< PRM_DEVICE */
    volatile UInt32      RSVD1[64];
    /**< CM_DEVICE */
    volatile UInt32      RSVD2[64];
    /**< Revision PRM */
    volatile UInt32      RSVD3[43];
    /**< CM_DPLL registers */
    volatile UInt32     CM_HDMI_CLKSEL;
    /**< HDMI CLK Sel */
    volatile UInt32      RSVD4[20];
    /**< CM_DPLL registers */
    volatile UInt32      RSVD5[64];
    /**< CM_DSP */
    volatile UInt32      RSVD6[64];
    /**< CM_ALWON2 */
    volatile UInt32      RSVD7[64];
    /**< CM_HDVICP */
    volatile UInt32      RSVD8[64];
    /**< CM_ISS */
    volatile UInt32     CM_HDVPSS_CLKSTCTRL;
    /**< CM_HDVPSS_CLKSTCTRL */
    volatile UInt32     RSVD9[7];
    volatile UInt32     CM_HDVPSS_HDVPSS_CLK_CTRL;
    /**< CM_HDVPSS_HDVPSS_CLK_CTRL */
    volatile UInt32     CM_HDVPSS_HDMI_CLKCTRL;
    /**< CM_HDVPSS_HDMI_CLKCTRL */
    volatile UInt32      RSVD10[54];
    /**< CM_HDVPSS */
    volatile UInt32      RSVD11[64];
    /**< PRM_DSP  */
    volatile UInt32      RSVD12[64];
    /**< PRM_DSP */
    volatile UInt32      RSVD13[64];
    /**< PRM_ALWON2 */
    volatile UInt32      RSVD14[64];
    /**< PRM_HDVICP */
    volatile UInt32      RSVD15[64];
    /**< PRM_ISP */
    volatile UInt32     PM_HDVPSS_PWRSTCTRL;
    /**< PM_HDVPSS_PWRSTCTRL */
    volatile UInt32     PM_HDVPSS_PWRSTST;
    /**< PM_HDVPSS_PWRSTST */
    volatile UInt32     RSVD[2];
    /**< Reserved */
    volatile UInt32     RM_HDVPSS_RSTCTRL;
    /**< RM_HDVPSS_RSTCTRL */
    volatile UInt32     RM_HDVPSS_RSTST;
    /**< RM_HDVPSS_RSTST */
    volatile UInt32     RSVD16[58];
    /**< HDVPSS remaining reserved registers */
    volatile UInt32     RSVD17[64];
    /** PRM_GFX */
    volatile UInt32     RSVD18[256];
    /**< RSVD No registers */
    volatile UInt32     RSVD19[89];
    /** CM_ALWON */
    volatile UInt32     CM_ALWON_I2C_02_CLKCTRL ;
    /**< I2c02 clk control */
    volatile UInt32     CM_ALWON_I2C_13_CLKCTRL;
    /**< I2c02 interface clock control */
    volatile UInt32     RSVD20[165];
    /**< Remaining CM_ALWON registers */
    volatile UInt32      RSVD21[256];
    /**< PRM_ALWON  */
}CSL_Prcm_Regs;

typedef volatile CSL_Prcm_Regs           *CSL_PrcmRegs;

#define HDVPSS_CLKSTCTRL_CLKACTIVITY_HDVPSS_GCLK_MASK       (0x00000100U)
#define HDVPSS_CLKSTCTRL_CLKACTIVITY_HDVPSS_GCLK_SHIFT      (0x8U)

#define HDVPSS_CLKSTCTRL_CLKTRCTRL_MASK                     (0x00000003U)
#define HDVPSS_CLKSTCTRL_CLKTRCTRL_SHIFT                    (0x00000000U)

#define HDVPSS_CLKCTRL_STBYST_MASK                          (0x00040000U)
#define HDVPSS_CLKCTRL_STBYST_SHIFT                         (0x00000013U)

#define HDVPSS_CLKCTRL_IDLEST_MASK                          (0x00030000U)
#define HDVPSS_CLKCTRL_IDLEST_SHIFT                         (0x00000010U)

#define HDVPSS_CLKCTRL_MODULEMODE_MASK                      (0x00000003U)
#define HDVPSS_CLKCTRL_MODULEMODE_SHIFT                     (0x0U)

#define HDMI_CLKCTRL_IDLEST_MASK                            (0x00030000U)
#define HDMI_CLKCTRL_IDLEST_SHIFT                           (0x00000010U)

#define HDMI_CLKCTRL_MODULEMODE_MASK                        (0x00000003U)
#define HDMI_CLKCTRL_MODULEMODE_SHIFT                       (0x0U)


#define HDVPSS_PM_PWRSTST_INTRANSITION_MASK                    (0x00100000U)
#define HDVPSS_PM_PWRSTST_INTRANSITION_SHIFT                (0x00000014U)

#define HDVPSS_PM_PWRSTST_MEM_STATEST_MASK                  (0x00000030U)
#define HDVPSS_PM_PWRSTST_MEM_STATEST_SHIFT                 (0x00000004U)

#define HDVPSS_PM_PWRSTST_LOGICSTATEST_MASK                 (0x00000004U)
#define HDVPSS_PM_PWRSTST_LOGICSTATEST_SHIFT                (0x00000002U)

#define HDVPSS_PM_PWRSTST_POWERSTATEST_MASK                 (0x00000003U)
#define HDVPSS_PM_PWRSTST_POWERSTATEST_SHIFT                (0x00000000U)

#define HDVPSS_RM_RSTCTRL_HDVPSS_RST_MASK                   (0x00000004U)
#define HDVPSS_RM_RSTCTRL_HDVPSS_RST_SHIFT                  (0x00000002U)

#define HDVPSS_RM_RSTST_HDVPSS_RST_MASK                     (0x00000004U)
#define HDVPSS_RM_RSTST_HDVPSS_RST_SHIFT                    (0x00000002U)

#define CM_ALWON_I2C_02_CLKCTRL_IDLEST_MASK                 (0x00030000U)
#define CM_ALWON_I2C_02_CLKCTRL_IDLEST_SHIFT                (0x00000010U)

#define CM_ALWON_I2C_02_CLKCTRL_MODULEMODE_MASK             (0x00000003U)
#define CM_ALWON_I2C_02_CLKCTRL_MODULEMODE_SHIFT            (0x00000000U)


#define CM_ALWON_I2C_13_CLKCTRL_IDLEST_MASK                 (0x00030000U)
#define CM_ALWON_I2C_13_CLKCTRL_IDLEST_SHIFT                (0x00000010U)

#define CM_ALWON_I2C_13_CLKCTRL_MODULEMODE_MASK             (0x00000003U)
#define CM_ALWON_I2C_13_CLKCTRL_MODULEMODE_SHIFT            (0x00000000U)


/* Chip configuration registers offsets */
#define HDMI_PHY_CTRL_REG_OFF                               0x1300
#define HDMI_PHY_CTRL_PD_PULLUPDET_MASK                     0x00000002
#define HDMI_PHY_CTRL_PD_PULLUPDET_SHIFT                    0x1
#define HDMI_PHY_CTRL_ENBYPASSCLK_MASK                      0x00000001
#define HDMI_PHY_CTRL_ENBYPASSCLK_SHIFT                     0x0


#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif /* CSLR_TI814XPRCM_H_ */
