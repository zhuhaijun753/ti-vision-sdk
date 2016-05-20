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
 *  \ingroup BSP_DRV_PLATFORM_API Platform Specific API
 *  \addtogroup BSP_DRV_PLATFORM_TDA2XX_API TDA2XX Platform Specific API
 *  @{
 */

/**
 *  \file bsp_platformTda2xx_Priv.h
 *
 *  \brief Register-level header file for VIDEO1_PLL.
 *
 */

#ifndef BSP_PLATFORM_TDA2XX_PRIV_H_
#define BSP_PLATFORM_TDA2XX_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  Field Definition Macros
 */

#define VIDEO_PLL_CONFIGURATION1_REGM_SHIFT                      (9U)
#define VIDEO_PLL_CONFIGURATION1_REGM_MASK                       (0x001ffe00U)

#define VIDEO_PLL_CONFIGURATION1_REGN_SHIFT                      (1U)
#define VIDEO_PLL_CONFIGURATION1_REGN_MASK                       (0x000001feU)

#define VIDEO_PLL_CONFIGURATION1_M4_CLOCK_DIV_SHIFT              (21U)
#define VIDEO_PLL_CONFIGURATION1_M4_CLOCK_DIV_MASK               (0x03e00000U)

#define VIDEO_PLL_CONFIGURATION1_M6_CLOCK_DIV_SHIFT              (0U)
#define VIDEO_PLL_CONFIGURATION1_M6_CLOCK_DIV_MASK               (0x1FU)

#define VIDEO_PLL_CONFIGURATION2_LOCKSEL_SHIFT                   (9U)
#define VIDEO_PLL_CONFIGURATION2_LOCKSEL_MASK                    (0x00000600U)
#define VIDEO_PLL_CONFIGURATION2_LOCKSEL_PHASELOCK                (0U)
#define VIDEO_PLL_CONFIGURATION2_LOCKSEL_FREQLOCK                 (1U)
#define VIDEO_PLL_CONFIGURATION2_LOCKSEL_SPARE                    (2U)

#define VIDEO_PLL_CONFIGURATION2_PLLLPMODE_SHIFT                 (5U)
#define VIDEO_PLL_CONFIGURATION2_PLLLPMODE_MASK                  (0x00000020U)
#define VIDEO_PLL_CONFIGURATION2_PLLLPMODE_FULL_PERF              (0U)
#define VIDEO_PLL_CONFIGURATION2_PLLLPMODE_REDUCE_PERF            (1U)

#define VIDEO_PLL_CONFIGURATION2_IDLE_SHIFT                      (0U)
#define VIDEO_PLL_CONFIGURATION2_IDLE_MASK                       (0x00000001U)
#define VIDEO_PLL_CONFIGURATION2_IDLE_NOTSEL                      (0U)
#define VIDEO_PLL_CONFIGURATION2_IDLE_SEL                         (1U)

#define VIDEO_PLL_CONFIGURATION2_LOWCURRSTBY_SHIFT               (6U)
#define VIDEO_PLL_CONFIGURATION2_LOWCURRSTBY_MASK                (0x00000040U)
#define VIDEO_PLL_CONFIGURATION2_LOWCURRSTBY_NOTSEL               (0U)
#define VIDEO_PLL_CONFIGURATION2_LOWCURRSTBY_SEL                  (1U)

#define VIDEO_PLL_CONFIGURATION2_TIGHTPHASELOCK_SHIFT             (7U)
#define VIDEO_PLL_CONFIGURATION2_TIGHTPHASELOCK_MASK              (0x00000080U)

#define VIDEO_PLL_CONFIGURATION2_DRIFTGUARDEN_SHIFT              (8U)
#define VIDEO_PLL_CONFIGURATION2_DRIFTGUARDEN_MASK               (0x00000100U)
#define VIDEO_PLL_CONFIGURATION2_DRIFTGUARDEN_DRIFT_GUARD_DIS     (0U)
#define VIDEO_PLL_CONFIGURATION2_DRIFTGUARDEN_DRIFT_GUARD_EN      (1U)

#define VIDEO_PLL_CONFIGURATION2_REFEN_SHIFT                     (13U)
#define VIDEO_PLL_CONFIGURATION2_REFEN_MASK                      (0x00002000U)
#define VIDEO_PLL_CONFIGURATION2_REFEN_REF_DIS                    (0U)
#define VIDEO_PLL_CONFIGURATION2_REFEN_REF_EN                     (1U)

#define VIDEO_PLL_CONFIGURATION2_M4_CLOCK_EN_SHIFT               (16U)
#define VIDEO_PLL_CONFIGURATION2_M4_CLOCK_EN_MASK                (0x00010000U)
#define VIDEO_PLL_CONFIGURATION2_M4_CLOCK_EN_SS_CLK_DIS           (0U)
#define VIDEO_PLL_CONFIGURATION2_M4_CLOCK_EN_SS_CLK_EN            (1U)

#define VIDEO_PLL_CONFIGURATION2_M4_CLOCK_PWDN_SHIFT              (17U)
#define VIDEO_PLL_CONFIGURATION2_M4_CLOCK_PWDN_MASK               (0x00020000U)

#define VIDEO_PLL_CONFIGURATION2_M6_CLOCK_EN_SHIFT               (23U)
#define VIDEO_PLL_CONFIGURATION2_M6_CLOCK_EN_MASK                (0x00800000U)

#define VIDEO_PLL_CONFIGURATION2_PHY_CLKINEN_SHIFT               (14U)
#define VIDEO_PLL_CONFIGURATION2_PHY_CLKINEN_MASK                (0x00004000U)
#define VIDEO_PLL_CONFIGURATION2_PHY_CLKINEN_CLK_DIS              (0U)
#define VIDEO_PLL_CONFIGURATION2_PHY_CLKINEN_CLK_EN               (1U)

#define VIDEO_PLL_CONFIGURATION2_BYPASSEN_SHIFT                  (15U)
#define VIDEO_PLL_CONFIGURATION2_BYPASSEN_MASK                   (0x00008000U)
#define VIDEO_PLL_CONFIGURATION2_BYPASSEN_CLK                     (0U)
#define VIDEO_PLL_CONFIGURATION2_BYPASSEN_CLK_BYPASS              (1U)

#define VIDEO_PLL_CONFIGURATION2_HSDIVBYPASS_SHIFT               (20U)
#define VIDEO_PLL_CONFIGURATION2_HSDIVBYPASS_MASK                (0x00100000U)
#define VIDEO_PLL_CONFIGURATION2_HSDIVBYPASS_HSDIV_NORMAL         (0U)
#define VIDEO_PLL_CONFIGURATION2_HSDIVBYPASS_HSDIV_FORCE_BYP      (1U)

#define VIDEO_PLL_CONFIGURATION2_REFSEL_SHIFT                    (21U)
#define VIDEO_PLL_CONFIGURATION2_REFSEL_MASK                     (0x00600000U)
#define VIDEO_PLL_CONFIGURATION2_REFSEL_REF_PCLK                  (0U)
#define VIDEO_PLL_CONFIGURATION2_REFSEL_REF_1                     (1U)
#define VIDEO_PLL_CONFIGURATION2_REFSEL_REF_2                     (2U)
#define VIDEO_PLL_CONFIGURATION2_REFSEL_REF_SYSCLK                (3U)

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BSP_PLATFORM_TDA2XX_PRIV_H_ */

/* @} */

