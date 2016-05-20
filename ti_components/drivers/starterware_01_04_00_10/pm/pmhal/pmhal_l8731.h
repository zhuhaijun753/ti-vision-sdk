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
 *  \file  pmhal_l8731.h
 *
 *  \brief The Power Management IC (PMIC) L8731 specific API definition.
 *
 *         The APIs defined here are to control the voltage of the
 *         PMIC rails and to query the status.
 */

#ifndef PM_L8731_H_
#define PM_L8731_H_

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

#define PMHAL_L8731_CHIP_ADDRESS             (0x59U)

/** \brief Maximum Number of PMIC Revisions available */
#define PMHAL_PMIC_MAX_REV                   (4U)

/** \brief The BUCK LDO Status register BUCK 1 voltage OK shift and mask. */
#define PMHAL_L8731_BKLDOSR_BK1_OK_SHIFT         (0U)
#define PMHAL_L8731_BKLDOSR_BK1_OK_MASK          (1U)

/** \brief The BUCK LDO Status register BUCK 2 voltage OK shift and mask. */
#define PMHAL_L8731_BKLDOSR_BK2_OK_SHIFT         (2U)
#define PMHAL_L8731_BKLDOSR_BK2_OK_MASK          (4U)

/** \brief The BUCK LDO Status register LDO 1 voltage OK shift and mask. */
#define PMHAL_L8731_BKLDOSR_LDO1_OK_SHIFT        (4U)
#define PMHAL_L8731_BKLDOSR_LDO1_OK_MASK         (0x10U)

/** \brief The BUCK LDO Status register LDO 2 voltage OK shift and mask. */
#define PMHAL_L8731_BKLDOSR_LDO2_OK_SHIFT        (5U)
#define PMHAL_L8731_BKLDOSR_LDO2_OK_MASK         (0x20U)

/**
 * \brief The VCCR register BUCK 1 Ramp Control Shift and Mask.
 *         Program 0 to hold the voltage to its current value.
 *         Program 1 to ramp to the target voltage.
 */
#define PMHAL_L8731_VCCR_BUCK1_RAMP_CTRL_SHIFT   (0U)
#define PMHAL_L8731_VCCR_BUCK1_RAMP_CTRL_MASK    (1U)

/**
 * \brief The VCCR register BUCK 1 Target Voltage Select Shift and Mask.
 *         Program 0 to ramp to voltage defined in Target Voltage register 1
 *         Program 1 to ramp to voltage defined in Target Voltage register 2
 */
#define PMHAL_L8731_VCCR_BUCK1_TARG_VOLT_SEL_SHIFT   (1U)
#define PMHAL_L8731_VCCR_BUCK1_TARG_VOLT_SEL_MASK    (2U)

/**
 * \brief The VCCR register BUCK 2 Ramp Control Shift and Mask.
 *         Program 0 to hold the voltage to its current value.
 *         Program 1 to ramp to the target voltage.
 */
#define PMHAL_L8731_VCCR_BUCK2_RAMP_CTRL_SHIFT   (4U)
#define PMHAL_L8731_VCCR_BUCK2_RAMP_CTRL_MASK    (0x10U)

/**
 * \brief The VCCR register BUCK 1 Target Voltage Select Shift and Mask.
 *         Program 0 to ramp to voltage defined in Target Voltage register 1
 *         Program 1 to ramp to voltage defined in Target Voltage register 2
 */
#define PMHAL_L8731_VCCR_BUCK2_TARG_VOLT_SEL_SHIFT   (5U)
#define PMHAL_L8731_VCCR_BUCK2_TARG_VOLT_SEL_MASK    (0x20U)

/** \brief Target Voltage Shift and Mask */
#define PMHAL_L8731_TARG_VOLT_SHIFT              (0U)
#define PMHAL_L8731_TARG_VOLT_MASK               (0x3FU)

/**
 * \brief Ramp Control register Shift and Mask. This determines the slew rate.
 *         Slew rate kept at default 8mv/us. Not programmed here.
 */
#define PMHAL_L8731_RAMP_CTRL_SHIFT               (0U)
#define PMHAL_L8731_RAMP_CTRL_MASK                (0xFU)

/** \brief LDO voltage control register shift and Mask. */
#define PMHAL_L8731_LDO_OUT_VOLT_SHIFT             (0U)
#define PMHAL_L8731_LDO_OUT_VOLT_MASK              (0x1FU)

/** \brief Invalid Page Address */
#define PMHAL_L8731_SLAVE_ADDR_INVALID   (0xFFU)

/** \brief       Control Status Macro for Off */
#define PMHAL_L8731_STATUS_OFF                   (0U)

/**
 * \brief Regulator Register Physical Addresses.
 */
#define PMHAL_L8731_BKLDOEN                 (0x10U)
#define PMHAL_L8731_BKLDOSR                 (0x11U)
#define PMHAL_L8731_BUCK_VCCR               (0x20U)
#define PMHAL_L8731_B1TV1                   (0x23U)
#define PMHAL_L8731_B1TV2                   (0x24U)
#define PMHAL_L8731_B1RC                    (0x25U)
#define PMHAL_L8731_B2TV1                   (0x29U)
#define PMHAL_L8731_B2TV2                   (0x2AU)
#define PMHAL_L8731_B2RC                    (0x2BU)
#define PMHAL_L8731_LDO1VCR                 (0x39U)
#define PMHAL_L8731_LDO2VCR                 (0x3AU)

/** \brief L8731 vendor ID LSB. */
#define PMHAL_L8731_PHYADDR_VENDOR_ID_LSB   (0x24FU)

/** \brief L8731 vendor ID MSB. */
#define PMHAL_L8731_PHYADDR_VENDOR_ID_MSB   (0x250U)

/** \brief L8731 Product ID LSB. */
#define PMHAL_L8731_PHYADDR_PRODUCT_ID_LSB  (0x251U)

/** \brief L8731 Product ID MSB. */
#define PMHAL_L8731_PHYADDR_PRODUCT_ID_MSB  (0x252U)

/** \brief Expected vendor ID values for L8731. */
#define PMHAL_L8731_VENDOR_ID            (0x0451U)

/** \brief Expected product ID values for L8731 1.0. */
#define PMHAL_L8731_1_0_PRODUCT_ID       (0x0917U)

/**
 * \brief L8731 device revision register physical address and the
 *        field definitions.
 */
#define PMHAL_L8731_PHYADDR_CHIP_REVISION_ID        (0x357U)

/** \brief Chip Revision ID mask */
#define PMHAL_L8731_CHIP_REVISION_ID_MASK          (0x0FU)

/** \brief Chip Revision ID Shift */
#define PMHAL_L8731_CHIP_REVISION_ID_SHIFT         (0x0U)

/** \brief Regulator Type for SMPS */
#define PMHAL_L8731_RTYPE_BUCK                (1U)

/** \brief Regulator Type for LDO */
#define PMHAL_L8731_RTYPE_LDO                 (2U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                      Global Variables Declarations                         */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   Get PMIC ops structure. All the other functions are accessed via
 *          function pointers whose array is exported by this function.
 *
 * \param   None
 *
 * \return  Return pointer to the PMIC ops structure.
 */
const pmhalPmicOperations_t *PMHALL8731GetPMICOps(void);

#ifdef __cplusplus
}
#endif

#endif

