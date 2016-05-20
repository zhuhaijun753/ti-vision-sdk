/**
 *  \file     pcie_app.h
 *
 *  \brief    This file contains the function declarations and macros
 *            corresponding to the pcie.
 *
 *  \copyright Copyright (C) 2013 Texas Instruments Incorporated -
 *             http://www.ti.com/
 */

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

#ifndef PCIE_APP_H_
#define PCIE_APP_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "pcie.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

#define PCIE_CONFIG_ENABLE                  ((uint32_t) 1U)
#define PCIE_CONFIG_DISABLE                 ((uint32_t) 0U)

#define PCIE_NUMBER_OF_LANES                ((uint32_t) 1U)
#define PCIE_UPPER_ADDRESS                  ((uint32_t) 0U)

#define OUTBOUND_CFG_OFFSET                 ((uint32_t) 0x00001000U)
#define OUTBOUND_CFG_OFFSET_LIMIT           ((uint32_t) 0x00000FFFU)
#define OUTBOUND_MEM_SPACE                  ((uint32_t) 0x05000000U)
#define OUTBOUND_MEM_SPACE_LIMIT            ((uint32_t) 0x00FFFFFFU)

#define INBOUND_PCIE_LIMIT                  ((uint32_t) 0x0FFFFFFFU)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This API configures Uart to be used in example.
 *
 * \param   none.
 *
 * \return  none.
 */
void PCIEAppUartInit(void);

/**
 * \brief   This API configures the PCIeSS1 PLL and clocks, resets the PCIeSS1
 *          and configures PHY.
 *
 * \param   none.
 *
 * \return  none.
 */
void PCIEAppPrcmConfig(void);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef PCIE_APP_H_ */