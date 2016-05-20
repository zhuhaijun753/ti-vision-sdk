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
 *  \file vpshalDeiDefaults.h
 *
 *  \brief VPS DEI HAL default configuration file
 *  This file contains default configuration i.e. expert values for
 *  Deinterlacer.
 *
 */

#ifndef VPSHAL_DEIDEFAULTS_H_
#define VPSHAL_DEIDEFAULTS_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  Values to be programmed for expert registers. These values needs to
 *  be programmed according to the recommended configuration.
 *  Note: These macros needs to be changed as when the recommended value
 *  changes in specification.
 */
#define VPSHAL_DEI_DEFAULT_EXPERT_VAL                                     \
    {                                                                     \
        0x020C0804U,            /* Expert value for DEI REG2 register */  \
        0x0118100FU,            /* Expert value for DEI REG3 register */  \
        0x08040200U,            /* Expert value for DEI REG4 register */  \
        0x1010100CU,            /* Expert value for DEI REG5 register */  \
        0x10101010U,            /* Expert value for DEI REG6 register */  \
        0x10101010U,            /* Expert value for DEI REG7 register */  \
        0x080A0000U,            /* Expert value for DEI REG10 register */ \
        0x00002004U             /* Expert value for DEI REG11 register */ \
    }

/**
 *  Below default values could be used instead of VPSHAL_DEI_DEFAULT_EXPERT_VAL
 *  when deinterlacing with fast motion images.
 */
#define VPSHAL_DEI_WITHOUT_ARTIFACT_FAST_MOTION_EXPERT_VAL                \
    {                                                                     \
        0x00201610U,            /* Expert value for DEI REG2 register */  \
        0x0118100FU,            /* Expert value for DEI REG3 register */  \
        0x100C0A06U,            /* Expert value for DEI REG4 register */  \
        0x1010100CU,            /* Expert value for DEI REG5 register */  \
        0x10101010U,            /* Expert value for DEI REG6 register */  \
        0x10101010U,            /* Expert value for DEI REG7 register */  \
        0x080A0000U,            /* Expert value for DEI REG10 register */ \
        0x00002004U             /* Expert value for DEI REG11 register */ \
    }

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct VpsHal_DeiExpertConfig
 *  \brief Structure containing the default values for the expert registers.
 */
typedef struct
{
    UInt32 deiReg2;
    /**< DEI REG2 register */
    UInt32 deiReg3;
    /**< DEI REG3 register */
    UInt32 deiReg4;
    /**< DEI REG4 register */
    UInt32 deiReg5;
    /**< DEI REG5 register */
    UInt32 deiReg6;
    /**< DEI REG6 register */
    UInt32 deiReg7;
    /**< DEI REG7 register */
    UInt32 deiReg10;
    /**< DEI REG10 register */
    UInt32 deiReg11;
    /**< DEI REG11 register */
} VpsHal_DeiExpertConfig;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef VPSHAL_DEIDEFAULTS_H_ */
