/* =================================================================
 *   Copyright (C) 2013 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and
 *    conditionsstipulated in the agreement under which this program
 *     has been supplied.
 * =================================================================*/
/**
 *  @Component      sbl
 *
 *  @Filename       sbl_tda2xx_prcmlib_dpll.h
 *
 *  @Description    Contains vayu dpll structure declaration for different
 *                  sysclk
 *//*======================================================================== */

#ifndef SBL_TDA2XX_PRCMLIB_DPLL_H_
#define SBL_TDA2XX_PRCMLIB_DPLL_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/*-------------------------------------------------------------------------*/
/**
 * @TYPE            dpll_config_t
 *
 * @BRIEF           dpll configuration
 *
 * @DESCRIPTION     define content of dpll register. Please refer to
 *                  ATTILA prcm spec for details on DPLLs.
 *
 */
/*------------------------------------------------------------------------ */
struct dpll_config_t {
    uint32_t multiplier;
    uint32_t divider;
    uint32_t dpll_ramp_rate;
    uint32_t dpll_ramp_level;
    uint32_t auto_dpll_mode;
    uint32_t div_m2_clkcfg;       /* these clkcfg reg are full meaning, */
    uint32_t div_m3_clkcfg;       /* not only multiplier */
    uint32_t div_h11_clkcfg;
    uint32_t div_h12_clkcfg;
    uint32_t div_h13_clkcfg;      /* Corresponds to (HS13 +1) value given in TRM */
    uint32_t div_h14_clkcfg;
    uint32_t div_h21_clkcfg;
    uint32_t div_h22_clkcfg;
    uint32_t div_h23_clkcfg;
    uint32_t div_h24_clkcfg;
    uint32_t emu_override_multiplier;
    uint32_t emu_override_divider;
    int32_t  regm4x_en;
    int32_t  lpmode_en;
    int32_t  relock_ramp_en;
    int32_t  dpll_dcoclkldo_pwdn;
    int32_t  dpll_driftguard_en;
    int32_t  emu_override_ctrl_en;
    int32_t  dcc_en;
    int32_t  selfreqdco;
};

/* ========================================================================== */
/*                            Global Variables Declarations                   */
/* ========================================================================== */

extern struct dpll_config_t dpll_video1_cfg_opp100_20;
extern struct dpll_config_t dpll_video2_cfg_opp100_20;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif /*SBL_TDA2XX_PRCMLIB_DPLL_H_*/
