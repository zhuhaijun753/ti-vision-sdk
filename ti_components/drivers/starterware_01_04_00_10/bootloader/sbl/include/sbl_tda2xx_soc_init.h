/* ======================================================================
 *   Copyright (C) 2013 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */
/**
 *   Component:         SBL
 *
 *   Filename:          sbl_tda2xx_soc_init.h
 *
 *   Description:       This file contains SoC init functions like configure
 *                      dpll, clock domain wake-up & PRCM module enable.
 */
#ifndef SBL_TDA2xx_SOC_INIT_H_
#define SBL_TDA2xx_SOC_INIT_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "stdint.h"
#include "hw_types.h"
#include "pmhal_prcm.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
enum dss_dpll
{
    dss_dpll_video1,
    dss_dpll_video2,
    dss_dpll_hdmi
};

/**
 *  \brief This structure defines the Power Domain's configuration for
 *         configuring state of Power domain
 */
typedef struct sbllibPowerDomainStateConfig
{
    pmhalPrcmPdId_t    domainId;
    /**< Power Domain Id, refer to enum #pmhalPrcmPdId_t for values */
    pmhalPrcmPdState_t powerDomainState;
    /**< State for which power domain should be configured */
    const char        *powerDomainName;
    /**< Power domain name */
} SBLPDStateConfig_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
uint32_t get_current_opp(void);
int32_t ConfigPowerDomains(void);
int32_t configure_dpll(void);
int32_t configure_clock_domains(void);
int32_t enable_vip_dss(void);
int32_t program_dss_video_pll(void);
int32_t enable_ocmc(void);
int32_t enable_serial_per(void);
int32_t enable_core(void);
int32_t enable_mem(void);
int32_t enable_interconnect(void);
int32_t enable_iva(void);
int32_t enable_ipc(void);
int32_t enable_timer(void);
int32_t enable_per(void);
int32_t SBL_UART_PRCM(UART_INST_t num);
int32_t ti_tda2xx_evm_configure_pad(void);
int32_t ti_tda2xx_mc_configure_pad(void);
int32_t enable_cpgmac(void);
int32_t enable_i2c1(void);

/** \brief Function to configure the static dependencies from master clock
 *         domains to slave clock domains.
 *
 *  \param None
 *
 *  \return Status of the API.
 *
 */
int32_t SBLConfigStaticDependency(void);

#ifdef __cplusplus
}
#endif

#endif /*SBL_TDA2xx_SOC_INIT_H_*/

