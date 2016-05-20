/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2014
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 *  \file      hw_prcm_data_names.h
 *
 *  \brief     This file contains macros to select module names.
 *
 *  \warning   This file is auto generated. So avoid manual changes.
 *              If manual changes are required the implications of the
 *              change in this and other auto generated files has to be
 *              completely understood.
 */

#ifndef HW_PMHAL_DATA_NAMES_H_
#define HW_PMHAL_DATA_NAMES_H_

/* ========================================================================== */
/*                                Include Files                               */
/* ========================================================================== */

#include "pmhal_prcm.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Macros and Typedefs                            */
/* ========================================================================== */

/*
 * \brief Macros for internal use
 */
#define IS_ENUM_INRANGE_(en, id) \
    (((en) ## _MIN <= (id)) && ((id) <= (en) ## _MAX))

#define CALC_ENUM_OFFSET_(en, id) \
    ((IS_ENUM_INRANGE_((en), (id))) ? (id) - ((en) ## _MIN) : ((en) ## _UNDEF))

#define NAME_(x)  (# x)

#ifdef NDEBUG
  #define GET_ENUM_NAME_(en, id) \
    "[name is only available in debug mode (NDEBUG=0)"
  #define GET_NODE_NAME_(en, id) \
    "[name is only available in debug mode (NDEBUG=0)"

#else
/* Name vector for PRCM elements */
  #define VNAME_PMHAL_PRCM_VD_        (pmhalVoltageDomain_t_names)
  #define VNAME_PMHAL_PRCM_PD_        (pmhalPowerDomain_t_names)
  #define VNAME_PMHAL_PRCM_CLK_       (pmhalClockList_names)
  #define VNAME_PMHAL_PRCM_RG_        (pmhalResetGroupList_names)
  #define VNAME_PMHAL_PRCM_GLB_RG_    (pmhalGlobalResetGroupList_names)
  #define VNAME_PMHAL_PRCM_RESET_     (pmhalResetList_names)
  #define VNAME_PMHAL_PRCM_MEM_       (pmhalPhysicalMemory_t_names)
  #define VNAME_PMHAL_PRCM_BANK_      (pmhalPhysicalMemoryBank_t_names)
  #define VNAME_PMHAL_PRCM_SYSCFG_    (pmhalSysConfigModuleId_t_names)
  #define VNAME_PMHAL_PRCM_NODE_      (pmhalNodeList_names)
  #define VNAME_PMHAL_PRCM_ROOT_CLK_  (VNAME_PMHAL_PRCM_NODE_)
  #define VNAME_PMHAL_PRCM_MUX_       (VNAME_PMHAL_PRCM_NODE_)
  #define VNAME_PMHAL_PRCM_DIV_       (VNAME_PMHAL_PRCM_NODE_)
  #define VNAME_PMHAL_PRCM_DPLL_      (VNAME_PMHAL_PRCM_NODE_)
  #define VNAME_PMHAL_PRCM_MOD_       (VNAME_PMHAL_PRCM_NODE_)

/* Minimum index of vector for PRCM elements */
  #define VMIN_PMHAL_PRCM_VD_         (PMHAL_PRCM_VD_MIN)
  #define VMIN_PMHAL_PRCM_PD_         (PMHAL_PRCM_PD_MIN)
  #define VMIN_PMHAL_PRCM_CLK_        (PMHAL_PRCM_CLK_MIN)
  #define VMIN_PMHAL_PRCM_RG_         (PMHAL_PRCM_RG_MIN)
  #define VMIN_PMHAL_PRCM_GLB_RG_     (PMHAL_PRCM_GLB_RG_MIN)
  #define VMIN_PMHAL_PRCM_RESET_      (PMHAL_PRCM_RESET_MIN)
  #define VMIN_PMHAL_PRCM_MEM_        (PMHAL_PRCM_MEM_MIN)
  #define VMIN_PMHAL_PRCM_BANK_       (PMHAL_PRCM_PHY_BANK_MIN)
  #define VMIN_PMHAL_PRCM_SYSCFG_     (PMHAL_PRCM_SYSCFG_MIN)
  #define VMIN_PMHAL_PRCM_NODE_       (PMHAL_PRCM_NODE_MIN)
  #define VMIN_PMHAL_PRCM_ROOT_CLK_   (VMIN_PMHAL_PRCM_NODE_)
  #define VMIN_PMHAL_PRCM_MUX_        (VMIN_PMHAL_PRCM_NODE_)
  #define VMIN_PMHAL_PRCM_DIV_        (VMIN_PMHAL_PRCM_NODE_)
  #define VMIN_PMHAL_PRCM_DPLL_       (VMIN_PMHAL_PRCM_NODE_)
  #define VMIN_PMHAL_PRCM_MOD_        (VMIN_PMHAL_PRCM_NODE_)

  #define GET_ENUM_NAME_(en, id)          \
    (IS_ ## en ? VNAME_ ## en ## _[(id) - \
                                   VMIN_ ## en ## _] : NAME_(en ## _UNDEF))

#endif /* NDEBUG */

/*
 * \brief Macros to confirm membership of a group
 */
#define IS_PMHAL_PRCM_VD(id)          (IS_ENUM_INRANGE_(PMHAL_PRCM_VD, (id)))
#define IS_PMHAL_PRCM_PD(id)          (IS_ENUM_INRANGE_(PMHAL_PRCM_PD, (id)))
#define IS_PMHAL_PRCM_CD(id)          (IS_ENUM_INRANGE_(PMHAL_PRCM_CD, (id)))
#define IS_PMHAL_PRCM_CLK(id)         (IS_ENUM_INRANGE_(PMHAL_PRCM_CLK, (id)))
#define IS_PMHAL_PRCM_MUX(id)         (IS_ENUM_INRANGE_(PMHAL_PRCM_MUX, (id)))
#define IS_PMHAL_PRCM_DIV(id)         (IS_ENUM_INRANGE_(PMHAL_PRCM_DIV, (id)))
#define IS_PMHAL_PRCM_ROOT_CLK(id)    (IS_ENUM_INRANGE_(PMHAL_PRCM_ROOT_CLK, \
                                                        (id)))
#define IS_PMHAL_PRCM_DPLL(id)        (IS_ENUM_INRANGE_(PMHAL_PRCM_DPLL, (id)))
#define IS_PMHAL_PRCM_MOD(id)         (IS_ENUM_INRANGE_(PMHAL_PRCM_MOD, (id)))
#define IS_PMHAL_PRCM_NODE(id) \
    (IS_ENUM_INRANGE_(PMHAL_PRCM_NODE, (id)) || IS_ENUM_INRANGE_(PMHAL_PRCM_MOD))

/*
 * \brief Macros to calculate offset within a group
 */
#define GET_PMHAL_PRCM_VD_OFFSET(id)       (CALC_ENUM_OFFSET_(PMHAL_PRCM_VD, \
                                                              (id)))
#define GET_PMHAL_PRCM_PD_OFFSET(id)       (CALC_ENUM_OFFSET_(PMHAL_PRCM_PD, \
                                                              (id)))
#define GET_PMHAL_PRCM_CD_OFFSET(id)       (CALC_ENUM_OFFSET_(PMHAL_PRCM_CD, \
                                                              (id)))
#define GET_PMHAL_PRCM_CLK_OFFSET(id)      (CALC_ENUM_OFFSET_(PMHAL_PRCM_CLK, \
                                                              (id)))
#define GET_PMHAL_PRCM_ROOT_CLK_OFFSET(id) \
    (CALC_ENUM_OFFSET_(PMHAL_PRCM_ROOT_CLK, (id)))
#define GET_PMHAL_PRCM_MUX_OFFSET(id)      (CALC_ENUM_OFFSET_(PMHAL_PRCM_MUX, \
                                                              (id)))
#define GET_PMHAL_PRCM_DIV_OFFSET(id)      (CALC_ENUM_OFFSET_(PMHAL_PRCM_DIV, \
                                                              (id)))
#define GET_PMHAL_PRCM_DPLL_OFFSET(id) \
    (CALC_ENUM_OFFSET_(PMHAL_PRCM_DPLL, (id)))
#define GET_PMHAL_PRCM_MOD_OFFSET(id)      (CALC_ENUM_OFFSET_(PMHAL_PRCM_MOD, \
                                                              (id)))

/*
 * \brief Macros to determine name of the given ID.
 *        Note: Enabled only in debug mode
 */
#define PMHAL_PRCM_GET_VD_NAME(id)        (GET_ENUM_NAME_(PMHAL_PRCM_VD, (id)))
#define PMHAL_PRCM_GET_PD_NAME(id)        (GET_ENUM_NAME_(PMHAL_PRCM_PD, (id)))
#define PMHAL_PRCM_GET_CD_NAME(id)        (GET_ENUM_NAME_(PMHAL_PRCM_CD, (id)))
#define PMHAL_PRCM_GET_CLK_NAME(id)       (GET_ENUM_NAME_(PMHAL_PRCM_CLK, (id)))
#define PMHAL_PRCM_GET_ROOT_CLK_NAME(id) \
    (GET_NODE_NAME_(PMHAL_PRCM_ROOT_CLK, (id)))
#define PMHAL_PRCM_GET_MUX_NAME(id)       (GET_NODE_NAME_(PMHAL_PRCM_MUX, (id)))
#define PMHAL_PRCM_GET_DIV_NAME(id)       (GET_NODE_NAME_(PMHAL_PRCM_DIV, (id)))
#define PMHAL_PRCM_GET_DPLL_NAME(id)      (GET_NODE_NAME_(PMHAL_PRCM_DPLL, (id)))
#define PMHAL_PRCM_GET_MOD_NAME(id)       (GET_NODE_NAME_(PMHAL_PRCM_MOD, (id)))
#define PMHAL_PRCM_GET_NODE_NAME(id)      (GET_NODE_NAME_(PMHAL_PRCM_NODE, (id)))

/* ========================================================================== */
/*                            Structures and Enums                            */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

extern const char *pmhalVoltageDomain_t_names[PMHAL_PRCM_VD_COUNT];
extern const char *pmhalPowerDomain_t_names[PMHAL_PRCM_PD_COUNT];
extern const char *pmhalClkDomain_t_names[PMHAL_PRCM_CD_COUNT];
extern const char *pmhalClockList_names[PMHAL_PRCM_CLK_GENERIC+1U];
extern const char *pmhalResetGroupList_names[PMHAL_PRCM_RG_COUNT];
extern const char *pmhalGlobalResetGroupList_names[PMHAL_PRCM_GLB_RG_COUNT];
extern const char *pmhalResetList_names[PMHAL_PRCM_RST_COUNT];
extern const char *pmhalSysConfigModuleId_t_names[PMHAL_PRCM_SYSCFG_COUNT];
extern const char *pmhalPhysicalMemoryBank_t_names[PMHAL_PRCM_PHY_BANK_COUNT];
extern const char *pmhalNodeList_names[PMHAL_PRCM_MOD_COUNT];
extern const char *pmhalPostDivList_names[PMHAL_PRCM_DPLL_POST_DIV_COUNT];

#ifdef __cplusplus
}
#endif

/* ========================================================================== */
/*                            Function Declarations                           */
/* ========================================================================== */

/* None */

#endif /* HW_PMHAL_DATA_NAMES_H_ */

