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
 *  \file        pmhal_l8731.c
 *
 *  \brief       Power Management IC - L8731 specific API implementation.
 *               APIs are exported by using function pointers.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include "hw_types.h"
#include "pm_types.h"
#include "pm_utils.h"
#include "pmhal/pmhal_pmic.h"
#include "pmhal_l8731.h"
#include "pmhal_pmicComm.h"
#include "pmhal_prcm.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 * \brief Abstract Enumeration for the Regulators.
 */
typedef enum pmhalL8731RegulatorId
{
    PMHAL_L8731_REGULATOR_INVALID = -1,
    /**< Invalid PMIC regulator ID */
    PMHAL_L8731_REGULATOR_MIN = 0,
    /**< Minimum Abstracted PMIC Regulator ID */
    PMHAL_L8731_REGULATOR_BUCK11 = PMHAL_PRCM_PMIC_REGULATOR_MIN,
    /**< Abstracted PMIC Regulator ID for First L8731 BUCK 1 */
    PMHAL_L8731_REGULATOR_BUCK12 = 1,
    /**< Abstracted PMIC Regulator ID for First L8731 BUCK 2 */
    PMHAL_L8731_REGULATOR_BUCK21 = 2,
    /**< Abstracted PMIC Regulator ID for Second L8731 BUCK 1 */
    PMHAL_L8731_REGULATOR_BUCK22 = 3,
    /**< Abstracted PMIC Regulator ID for Second L8731 BUCK 2*/
    PMHAL_L8731_REGULATOR_LDO21 = 4,
    /**< Abstracted PMIC Regulator ID for Second L8731 LDO 1 */
    PMHAL_L8731_REGULATOR_MAX = (PMHAL_L8731_REGULATOR_LDO21 + 1)
                                /**< Maximum Abstracted PMIC Regulator ID */
} pmhalL8731RegulatorId_t;

/**
 * \brief L8731 Regulator description structure
 */
typedef struct pmhalL8731Regulator
{
    uint16_t minVolt;
    /**< Minimum voltage supported by the regulator in 10^ (-4) V. */
    uint16_t maxVolt;
    /**< Maximum voltage supported by the regulator in 10^ (-4) V. */
    uint8_t  stepVolt;
    /**< Step voltage in 10^ (-4) V. */
    uint8_t  type;
    /**< The regulator type namely PMHAL_L8731_SMPS or PMHAL_L8731_LDO. */
    uint16_t slewRate;
    /**< The voltage ramp delay in uV/us */
    uint8_t  minVoltVsel;
    /**< VSEL value corresponding to the minVolt.*/
    uint8_t  maxVoltVsel;
    /**< VSEL value corresponding to the maxVolt.*/
    uint8_t  voltEnRegShift;
    /**< Buck/LDO Output Voltage Enable Register bit field shift */
    uint8_t  voltStatusRegShift;
    /**< Buck/LDO Output Voltage Status Register bit field shift */
    uint8_t  vccrRampCtrlShift;
    /**< Bit field to enable ramp to a given voltage */
    uint8_t  vccrTargetVoltSelShift;
    /**< Bit field to select the target voltage */
    uint8_t  voltageControlReg;
    /**< Address of the voltage control register */
    uint8_t  i2cNum;
    /**< Indicates which regulator is connected to which PMIC IC I2C Bus */
} pmhalL8731Regulator_t;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief   Check if the L8731 PMIC is present. The declaration is present
 *          here to ensure this function is used only via function pointer.
 *
 * \param   void
 *
 * \return  PM_SUCCESS - L8731 PMIC is present.
 *          PM_PMHAL_PMIC_VENDOR_ID_INVALID - PMIC vendor id doesn't match the
 *                                     expected value.
 *          PM_PMHAL_PMIC_PRODUCT_ID_INVALID - PMIC product id doesn't match the
 *                                      expected value.
 */
static pmErrCode_t PMHALL8731IsPresent(void);

/**
 * \brief   Get the L8731 PMIC chip revision. The declaration is present
 *          here to ensure this function is used only via function pointer.
 *
 * \param   void
 *
 * \return  revString - The revision. "INVALID" is returned in case of error.
 */
static const char *PMHALL8731GetRevision(void);

/**
 * \brief   Return the PMIC Vendor ID. The declaration is present
 *          here to ensure this function is used only via function pointer.
 *
 * \param   vendorId    The Vendor ID is populated in this parameter.
 *
 * \return  status      PM_SUCCESS if API is a success. PM_BADARGS otherwise.
 */
static pmErrCode_t PMHALL8731GetVendorId(uint32_t *vendorId);

/**
 * \brief   Return the PMIC Product ID. The declaration is present
 *          here to ensure this function is used only via function pointer.
 *
 * \param   productId   The Product ID is populated in this parameter.
 *
 * \return  status      PM_SUCCESS if API is a success. PM_BADARGS otherwise.
 */
static pmErrCode_t PMHALL8731GetProductId(uint32_t *productId);

/**
 * \brief  Get the voltage setting of the given regulator. The declaration is
 *         present here to ensure this function is used only via function
 *         pointer.
 *
 * \param  regId    Regulator Id. Refer Enum #pmhalPrcmPmicRegulatorId_t
 * \param  voltage  Voltage in mV returned.
 *
 * \return status   PM_SUCCESS if API is a success. PM_BADARGS otherwise.
 */
static pmErrCode_t PMHALL8731GetRegulatorVoltage(
    pmhalPrcmPmicRegulatorId_t regId,
    uint32_t                  *voltage);

/**
 * \brief  Set the voltage of the regulator to the mV given. The declaration is
 *         present here to ensure this function is used only via function
 *         pointer.
 *
 *         NOTE:
 *         PMIC allows controlling the voltage in many ways. The approach
 *         taken by this routine is to use the current configuration for
 *         voltage setting and try to succeed. It doesn't try to alter the
 *         configuration to ensure success. For example, if ROOF_FLOOR_EN
 *         control bit is set to 1 to mean that the voltage is controlled
 *         by the device resource pins, then this routine returns error;
 *         even though this bit can be changed to 0U to succeed.
 *
 * \param  regId    Regulator Id. Refer Enum #pmhalPrcmPmicRegulatorId_t
 * \param  voltage  Voltage in mV returned.
 * \param  timeout  Timeout iterations to wait for setting the right regulator
 *                  voltage value. Possible values can be:
 *                  PM_TIMEOUT_NOWAIT   Do not wait for voltage setting.
 *                  PM_TIMEOUT_INFINITE Wait infinitely till the voltage is set.
 *                  Non Zero Value      Wait for the time provided by the user.
 *
 * \return Status   PM_SUCCESS if API is a success. PM_BADARGS otherwise.
 */
static pmErrCode_t PMHALL8731SetRegulatorVoltage(
    pmhalPrcmPmicRegulatorId_t regId,
    uint32_t                   voltage,
    uint32_t                   timeout);

/**
 * \brief  API to check if the given regulator enabled. The declaration is
 *         present here to ensure this function is used only via function
 *         pointer.
 *
 * \param  regId  Regulator Id. Refer Enum #pmhalPrcmPmicRegulatorId_t
 *
 * \return enabled  TRUE if regulator is enabled; FALSE otherwise.
 */
static uint32_t    PMHALL8731IsRegulatorEnabled(
    pmhalPrcmPmicRegulatorId_t regId);

/**
 * \brief  Enable the given regulator. The declaration is
 *         present here to ensure this function is used only via function
 *         pointer.
 *
 * \param  regId  Regulator Id. Refer Enum #pmhalPrcmPmicRegulatorId_t
 *
 * \return status PM_SUCCESS if API is a success. PM_BADARGS/FAIL otherwise.
 */
static pmErrCode_t PMHALL8731EnableRegulator(
    pmhalPrcmPmicRegulatorId_t regId);

/**
 * \brief  Disable the given regulator. The declaration is
 *         present here to ensure this function is used only via function
 *         pointer.
 *
 * \param  regId  Regulator Id. Refer Enum #pmhalPrcmPmicRegulatorId_t
 *
 * \return status PM_SUCCESS if API is a success. PM_BADARGS/FAIL otherwise.
 */
static pmErrCode_t PMHALL8731DisableRegulator(
    pmhalPrcmPmicRegulatorId_t regId);

/**
 * \brief   Return the Regulator Step voltage size. This is required by the
 *          voltage manager to understand the opp for the given voltage set for
 *          the given voltage rail.
 *
 * \param   regId       Regulator ID. Refer #pmhalPrcmPmicRegulatorId_t for
 *                      details.
 * \param   avsVoltage     AVS voltage which is to be converted to regulator
 *                      voltage
 *
 * \return  convVolt    The voltage that would be supplied by the regulator if
 *                      the AVS voltage is given to the API.
 *                      NOTE: This API does not program the PMIC. It just
 *                      returns the calculated value of AVS voltage converted to
 *                      PMIC voltage based on the PMIC voltage resolution.
 */
static uint32_t PMHALL8731GetRegulatorConvVoltage(
    pmhalPrcmPmicRegulatorId_t regId,
    uint32_t                   avsVoltage);

#ifdef __cplusplus
}
#endif

/**
 * \brief Given voltage in mV and range, return the VSEL offset
 *
 * \param   regId   Regulator Id. Refer Enum #pmhalPrcmPmicRegulatorId_t
 * \param   voltage Voltage in mV.
 * \param   vsel    VSEL value returned.
 *
 * \return  status
 */
static pmErrCode_t PmhalL8731VoltageToVselOffset(
    pmhalPrcmPmicRegulatorId_t regId,
    uint32_t                   voltage,
    uint32_t                  *vsel);

/**
 * \brief Given VSEL offset convert it to voltage in mV and return.
 *
 * \param   regId   Regulator Id. Refer Enum #pmhalPrcmPmicRegulatorId_t
 * \param   vsel    VSEL value returned.
 *
 * \return  voltage Voltage in mV.
 */
static uint32_t    PmhalL8731VselOffsetToVoltage(
    pmhalPrcmPmicRegulatorId_t regId,
    uint32_t                   vsel);

/**
 * \brief  Read the register value at the given physical address.
 *
 * \param   i2cNumber   The I2C number used on the board to connect to the
 *                      desired PMIC.
 * \param   phyAddr     Address to be read.
 * \param   value       Returns the value read.
 *
 * \return  status      Return PM_SUCCESS if read is successful. Else returns
 *                      PM_FAIL.
 */
static pmErrCode_t PmhalL8731ReadPhyAddr(uint8_t i2cNumber,
                                         uint32_t phyAddr, uint32_t *value);

/**
 * \brief  Write the given register value at the given physical address.
 *
 * \param   i2cNumber   The I2C number used on the board to connect to the
 *                      desired PMIC.
 * \param   phyAddr     Address to be written to.
 * \param   value       Returns the value to be written.
 *
 * \return Return success or failure.
 */
static pmErrCode_t PmhalL8731WritePhyAddr(uint8_t i2cNumber,
                                          uint32_t phyAddr, uint32_t value);

/**
 * \brief  Is the given regulator enabled?
 *         This utility function must only be called by functions in this
 *         file and the caller must ensure that the PMIC communication is
 *         configured and enabled before calling this function.
 *
 * \param  regId  Regulator Id. Refer Enum #pmhalPrcmPmicRegulatorId_t
 *
 * \return TRUE if regulator is enabled; FALSE otherwise.
 */
static uint32_t PmhalL8731CheckRegulatorEnabled
    (pmhalPrcmPmicRegulatorId_t regId);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Power Management IC device callbacks. */
const pmhalPmicOperations_t  gPmhalL8731Ops =
{
    &PMHALL8731IsPresent,               /* isPresent */
    &PMHALL8731GetRevision,             /* getRevision */
    &PMHALL8731GetVendorId,             /* getVendorId */
    &PMHALL8731GetProductId,            /* getProductId */
    &PMHALL8731IsRegulatorEnabled,      /* isRegulatorEnabled */
    &PMHALL8731EnableRegulator,         /* regulatorEnable */
    &PMHALL8731DisableRegulator,        /* regulatorDisable */
    &PMHALL8731GetRegulatorVoltage,     /* regulatorGetVoltage */
    &PMHALL8731SetRegulatorVoltage,     /* regulatorSetVoltage */
    &PMHALL8731GetRegulatorConvVoltage, /* regulatorGetConvVoltage */
};

/* Data structure to describe the regulator for all the regulators. */
const pmhalL8731Regulator_t  gPmhalL8731Regulator[
    PMHAL_L8731_REGULATOR_MAX] =
{
    /* PMHAL_L8731_REGULATOR_BUCK11 */
    {
        8875U, 16750U, 125U, PMHAL_L8731_RTYPE_BUCK, 8000U, 0x00U, 0x3FU,
        PMHAL_L8731_BKLDOSR_BK1_OK_SHIFT, PMHAL_L8731_BKLDOSR_BK1_OK_SHIFT,
        PMHAL_L8731_VCCR_BUCK1_RAMP_CTRL_SHIFT,
        PMHAL_L8731_VCCR_BUCK1_TARG_VOLT_SEL_SHIFT, PMHAL_L8731_B1TV1, 0U
    },
    /* PMHAL_L8731_REGULATOR_BUCK12 */
    {
        8875U, 16750U, 125U, PMHAL_L8731_RTYPE_BUCK, 8000U, 0x00U, 0x3FU,
        PMHAL_L8731_BKLDOSR_BK2_OK_SHIFT, PMHAL_L8731_BKLDOSR_BK2_OK_SHIFT,
        PMHAL_L8731_VCCR_BUCK2_RAMP_CTRL_SHIFT,
        PMHAL_L8731_VCCR_BUCK2_TARG_VOLT_SEL_SHIFT, PMHAL_L8731_B2TV1, 0U
    },
    /* PMHAL_L8731_REGULATOR_BUCK21 */
    {
        8875U, 16750U, 125U, PMHAL_L8731_RTYPE_BUCK, 8000U, 0x00U, 0x3FU,
        PMHAL_L8731_BKLDOSR_BK1_OK_SHIFT, PMHAL_L8731_BKLDOSR_BK1_OK_SHIFT,
        PMHAL_L8731_VCCR_BUCK1_RAMP_CTRL_SHIFT,
        PMHAL_L8731_VCCR_BUCK1_TARG_VOLT_SEL_SHIFT, PMHAL_L8731_B1TV1, 1U
    },
    /* PMHAL_L8731_REGULATOR_BUCK22 */
    {
        8875U, 16750U, 125U, PMHAL_L8731_RTYPE_BUCK, 8000U, 0x00U, 0x3FU,
        PMHAL_L8731_BKLDOSR_BK2_OK_SHIFT, PMHAL_L8731_BKLDOSR_BK2_OK_SHIFT,
        PMHAL_L8731_VCCR_BUCK2_RAMP_CTRL_SHIFT,
        PMHAL_L8731_VCCR_BUCK2_TARG_VOLT_SEL_SHIFT, PMHAL_L8731_B2TV1, 1U
    },
    /*  PMHAL_L8731_REGULATOR_LDO21 */
    {
        8000U, 33000U, 50U, PMHAL_L8731_RTYPE_LDO, 8000U, 0x00U, 0x19U,
        PMHAL_L8731_BKLDOSR_LDO1_OK_SHIFT, PMHAL_L8731_BKLDOSR_LDO1_OK_SHIFT,
        0x0U, 0x0U, PMHAL_L8731_LDO1VCR, 1U
    }
};

/* Table mapping from SMPS/LDO to Voltage Rails on the device */
const pmhalL8731Regulator_t *gPmhalL8731RegulatorTable[
    PMHAL_PRCM_PMIC_REGULATOR_COUNT] =
{
    &gPmhalL8731Regulator[PMHAL_L8731_REGULATOR_BUCK11],
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_CORE */
    &gPmhalL8731Regulator[PMHAL_L8731_REGULATOR_BUCK12],
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_DSPEVE */
    &gPmhalL8731Regulator[PMHAL_L8731_REGULATOR_BUCK22],
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_1V8PHY */
    &gPmhalL8731Regulator[PMHAL_L8731_REGULATOR_BUCK21],
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_DDR */
    &gPmhalL8731Regulator[PMHAL_L8731_REGULATOR_LDO21]
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_1V8PLL */
};

/* Chip Revisions of the PMIC. */
const char *gPmhalL8731RevStrings[PMHAL_PMIC_MAX_REV] =
{"CS1.0", "CS2.0", "CS2.1", "CS2.2"};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

const pmhalPmicOperations_t *PMHALL8731GetPMICOps(void)
{
    return &gPmhalL8731Ops;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static pmErrCode_t PMHALL8731GetVendorId(uint32_t *vendorId)
{
    /* This is a dummy function to match with the other PMIC ICs. Vendor ID
     * Register not defined in the data sheet.
     */
    pmErrCode_t status = PM_SUCCESS;

    if (NULL == vendorId)
    {
        status = PM_BADARGS;
    }
    else
    {
        *vendorId = PMHAL_L8731_VENDOR_ID;
    }

    return status;
}

static pmErrCode_t PMHALL8731GetProductId(uint32_t *productId)
{
    /* This is a dummy function to match with the other PMIC ICs. Product ID
     * Register not defined in the data sheet.
     */
    pmErrCode_t status = PM_SUCCESS;

    if (NULL == productId)
    {
        status = PM_BADARGS;
    }
    else
    {
        *productId = PMHAL_L8731_1_0_PRODUCT_ID;
    }

    return status;
}

static pmErrCode_t PMHALL8731IsPresent(void)
{
    uint32_t    prodId = 0U, vendorId = 0U;
    pmErrCode_t status = PM_SUCCESS;

    /*
     * Check if the L8731 PMIC is present. This function
     * ensures that this specific PMIC is in the system by
     * reading and verifying the vendor ID and product ID.
     * Return success only if the vendor ID and product ID
     * matches the expected value.
     */

    /* Check the Vendor ID. */
    status = PMHALL8731GetVendorId(&vendorId);

    /* Check the Product ID. */
    if (PMHAL_L8731_VENDOR_ID == vendorId)
    {
        status = PMHALL8731GetProductId(&prodId);
    }

    return status;
}

static const char *PMHALL8731GetRevision(void)
{
    /* This is a dummy function to match with the other PMIC ICs. Revision ID
     * Register not defined in the data sheet.
     */
    uint32_t    rev;
    const char *revString = "INVALID";

    rev = 0U;
    if (rev < PMHAL_PMIC_MAX_REV)
    {
        revString = gPmhalL8731RevStrings[rev];
    }

    return revString;
}

static pmErrCode_t PMHALL8731GetRegulatorVoltage(
    pmhalPrcmPmicRegulatorId_t regId,
    uint32_t                  *voltage)
{
    pmErrCode_t status = PM_SUCCESS;
    uint32_t    ctrl;
    uint32_t    vsel = 0U;
    const pmhalL8731Regulator_t *regulator;
    uint8_t     i2cNumber;

    if ((NULL == voltage) || (regId >= PMHAL_PRCM_PMIC_REGULATOR_COUNT) ||
        (regId < PMHAL_PRCM_PMIC_REGULATOR_MIN))
    {
        status = PM_BADARGS;
    }
    else
    {
        regulator = gPmhalL8731RegulatorTable[regId];
        /* There are 2 ICs which provide for the voltage rails on different
         * I2C lines. Depending on the regulator ID read which I2C line does
         * this correspond to.
         */
        i2cNumber = regulator->i2cNum;
        *voltage  = 0U;
        /*
         * Configure and enable PMIC communication bus.
         */
        status = PMHALPmicCommConfigure(i2cNumber);

        if ((TRUE == PmhalL8731CheckRegulatorEnabled(regId)) &&
            (PM_SUCCESS == status))
        {
            if (PMHAL_L8731_RTYPE_BUCK == regulator->type)
            {
                /* The VCCR register holds the information as to which target
                 * voltage register must be read to see if the voltage is
                 * set correctly.
                 */
                status = PmhalL8731ReadPhyAddr((uint8_t) i2cNumber,
                                               (uint32_t) PMHAL_L8731_BUCK_VCCR,
                                               &ctrl);
                /* Read the corresponding target voltage register */
                if ((ctrl &
                     ((uint32_t) 1U <<
                      (uint32_t) regulator->vccrTargetVoltSelShift)) ==
                    (uint32_t) 0U)
                {
                    status = PmhalL8731ReadPhyAddr(
                        i2cNumber,
                        (uint32_t) regulator->
                        voltageControlReg,
                        &vsel);
                }
                else
                {
                    status = PmhalL8731ReadPhyAddr(i2cNumber,
                                                   ((uint32_t) regulator->
                                                    voltageControlReg
                                                    + (uint32_t) 0x4U), &vsel);
                }
                if (PM_SUCCESS == status)
                {
                    *voltage = PmhalL8731VselOffsetToVoltage(regId, vsel);
                }
            }
            else
            {
                /* For the LDOs there are dedicated target voltage registers */
                status = PmhalL8731ReadPhyAddr(i2cNumber,
                                               regulator->voltageControlReg,
                                               &vsel);
                if (PM_SUCCESS == status)
                {
                    *voltage = PmhalL8731VselOffsetToVoltage(regId, vsel);
                }
            }
        }
    }

    return status;
}

static pmErrCode_t PMHALL8731SetRegulatorVoltage(
    pmhalPrcmPmicRegulatorId_t regId,
    uint32_t                   voltage,
    uint32_t                   timeout)
{
    pmErrCode_t status = PM_SUCCESS;
    uint32_t    ctrl   = 0U;
    uint32_t    vsel   = 0U;
    const pmhalL8731Regulator_t *regulator;
    uint8_t     i2cNumber;
    uint32_t    currVolt = 0U;

    /*
     * Check whether input arguments are correct. Check for the voltage is done
     * later in the function.
     */
    if ((regId >= PMHAL_PRCM_PMIC_REGULATOR_COUNT) ||
        (regId < PMHAL_PRCM_PMIC_REGULATOR_MIN))
    {
        status = PM_BADARGS;
    }
    else
    {
        regulator = gPmhalL8731RegulatorTable[regId];
        /* There are 2 ICs which provide for the voltage rails on different
         * I2C lines. Depending on the regulator ID read which I2C line does
         * this correspond to.
         */
        i2cNumber = regulator->i2cNum;
        /*
         * Configure and enable PMIC communication bus.
         */
        status = PMHALPmicCommConfigure(i2cNumber);

        if (TRUE == PmhalL8731CheckRegulatorEnabled(regId))
        {
            PmhalL8731VoltageToVselOffset(regId, voltage, &vsel);
            if (PMHAL_L8731_RTYPE_BUCK == regulator->type)
            {
                /* Configure the target voltage. Then set the VCCR register to
                 * read the desired target voltage register and then ramp the
                 * voltage to the desired target register.
                 */
                PmhalL8731WritePhyAddr(i2cNumber, regulator->voltageControlReg,
                                       vsel);
                PmhalL8731ReadPhyAddr(i2cNumber,
                                      (uint32_t) PMHAL_L8731_BUCK_VCCR,
                                      &ctrl);
                ctrl = ctrl &
                       ~((uint32_t) 1U <<
                         (uint32_t) regulator->vccrTargetVoltSelShift);
                PmhalL8731WritePhyAddr(i2cNumber,
                                       (uint32_t) PMHAL_L8731_BUCK_VCCR,
                                       ctrl);
                /* Ramp to voltage */
                ctrl = ctrl |
                       ((uint32_t) 1U <<
                        (uint32_t) regulator->vccrRampCtrlShift);
                PmhalL8731WritePhyAddr(i2cNumber,
                                       (uint32_t) PMHAL_L8731_BUCK_VCCR,
                                       ctrl);
            }
            else
            {
                /* For LDO just configure the voltage. No status registers to
                 * observe.
                 */
                PmhalL8731WritePhyAddr(i2cNumber,
                                       (uint32_t) regulator->voltageControlReg,
                                       vsel);
            }
        }
        /*
         * Wait for the voltage ramp up to complete. The caller can perform
         * operations that require the voltage rail to be at the given voltage
         * right after this call. So, ensure the voltage ramps up before
         * returning.
         */
        if (PM_SUCCESS == status)
        {
            uint32_t newV = PmhalL8731VselOffsetToVoltage(regId, vsel);

            if (PM_TIMEOUT_INFINITE == timeout)
            {
                while (newV != currVolt)
                {
                    PMHALL8731GetRegulatorVoltage(regId, &currVolt);
                }
            }
            else if (PM_TIMEOUT_NOWAIT == timeout)
            {
                ; /* nothing to do here */
            }
            else
            {
                uint32_t timeToWait = timeout;

                while ((newV != currVolt) && (0U != timeToWait))
                {
                    PMHALL8731GetRegulatorVoltage(regId, &currVolt);
                    timeToWait--;
                }

                if (0U == timeToWait)
                {
                    status = PM_FAIL;
                }
            }
        }
    }
    return status;
}

static uint32_t PMHALL8731IsRegulatorEnabled(
    pmhalPrcmPmicRegulatorId_t regId)
{
    uint32_t    enabled = 0U;
    pmErrCode_t status  = PM_SUCCESS;
    const pmhalL8731Regulator_t *regulator;
    uint8_t     i2cNumber = (uint8_t) 0U;

    if ((regId >= PMHAL_PRCM_PMIC_REGULATOR_COUNT) ||
        (regId < PMHAL_PRCM_PMIC_REGULATOR_MIN))
    {
        status = PM_BADARGS;
    }
    else
    {
        regulator = gPmhalL8731RegulatorTable[regId];
        /* There are 2 ICs which provide for the voltage rails on different
         * I2C lines. Depending on the regulator ID read which I2C line does
         * this correspond to.
         */
        i2cNumber = regulator->i2cNum;
        /* Configure and enable PMIC communication bus.  */
        status = PMHALPmicCommConfigure(i2cNumber);
    }

    if (PM_SUCCESS == status)
    {
        enabled = (uint32_t) PmhalL8731CheckRegulatorEnabled(regId);
    }

    return enabled;
}

static pmErrCode_t PMHALL8731EnableRegulator(
    pmhalPrcmPmicRegulatorId_t regId)
{
    pmErrCode_t status = PM_SUCCESS;
    const pmhalL8731Regulator_t *regulator;
    uint32_t    value   = 0U;
    uint32_t    enabled = FALSE;
    uint8_t     i2cNumber;

    if ((regId >= PMHAL_PRCM_PMIC_REGULATOR_COUNT) ||
        (regId < PMHAL_PRCM_PMIC_REGULATOR_MIN))
    {
        status = PM_BADARGS;
    }
    else
    {
        regulator = gPmhalL8731RegulatorTable[regId];
        /* There are 2 ICs which provide for the voltage rails on different
         * I2C lines. Depending on the regulator ID read which I2C line does
         * this correspond to.
         */
        i2cNumber = regulator->i2cNum;

        /* Configure and enable PMIC communication bus.  */
        status = PMHALPmicCommConfigure(i2cNumber);
        if (PM_SUCCESS == status)
        {
            /*
             * If the Regulator is disabled, enable by setting the MODE_ACTIVE
             * and MODE_SLEEP to 0x01 (Forced PWM)
             */
            enabled = PmhalL8731CheckRegulatorEnabled(regId);
            if (FALSE == enabled)
            {
                PmhalL8731ReadPhyAddr(i2cNumber, (uint32_t) PMHAL_L8731_BKLDOEN,
                                      &value);
                value = value |
                        ((uint32_t) 1U << (uint32_t) regulator->voltEnRegShift);
                PmhalL8731WritePhyAddr(i2cNumber,
                                       (uint32_t) PMHAL_L8731_BKLDOEN,
                                       value);

                enabled = PmhalL8731CheckRegulatorEnabled(regId);
                if (FALSE == enabled)
                {
                    status = PM_FAIL;
                }
            }
        }
    }
    return status;
}

static pmErrCode_t PMHALL8731DisableRegulator(
    pmhalPrcmPmicRegulatorId_t regId)
{
    pmErrCode_t status = PM_SUCCESS;
    uint8_t     i2cNumber;
    uint32_t    value;
    const pmhalL8731Regulator_t *regulator;

    if ((regId >= PMHAL_PRCM_PMIC_REGULATOR_COUNT) ||
        (regId < PMHAL_PRCM_PMIC_REGULATOR_MIN))
    {
        status = PM_BADARGS;
    }
    else
    {
        regulator = gPmhalL8731RegulatorTable[regId];
        /* There are 2 ICs which provide for the voltage rails on different
         * I2C lines. Depending on the regulator ID read which I2C line does
         * this correspond to.
         */
        i2cNumber = regulator->i2cNum;

        /* Configure and enable PMIC communication bus. */
        status = PMHALPmicCommConfigure(i2cNumber);

        /* If the Regulator is enabled, disable by setting the voltage to 0U. */
        if (PM_SUCCESS == status)
        {
            if (TRUE == PmhalL8731CheckRegulatorEnabled(regId))
            {
                PmhalL8731ReadPhyAddr(i2cNumber, (uint32_t) PMHAL_L8731_BKLDOEN,
                                      &value);
                value = value &
                        ~((uint32_t) 1U << (uint32_t) regulator->voltEnRegShift);
                PmhalL8731WritePhyAddr(i2cNumber,
                                       (uint32_t) PMHAL_L8731_BKLDOEN,
                                       value);

                /* Check if the regulator is truly disabled */
                if (TRUE == PmhalL8731CheckRegulatorEnabled(regId))
                {
                    status = PM_FAIL;
                }
            }
        }
    }

    return status;
}

static uint32_t PMHALL8731GetRegulatorConvVoltage(
    pmhalPrcmPmicRegulatorId_t regId,
    uint32_t                   avsVoltage)
{
    pmErrCode_t status       = PM_SUCCESS;
    uint32_t    convVoltage  = 0U;
    uint32_t    internalVsel = 0U;

    status = PmhalL8731VoltageToVselOffset(regId, avsVoltage, &internalVsel);
    if (PM_SUCCESS == status)
    {
        convVoltage = PmhalL8731VselOffsetToVoltage(regId, internalVsel);
    }

    return convVoltage;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static uint32_t PmhalL8731CheckRegulatorEnabled(
    pmhalPrcmPmicRegulatorId_t regId)
{
    uint32_t enabled = FALSE;
    uint32_t ctrl    = 0U;
    uint8_t  i2cNumber;
    /*
     * regId checks are not done here as this is an internal function and
     * the check would have happened before calling this function.
     */
    const pmhalL8731Regulator_t *regulator =
        gPmhalL8731RegulatorTable[regId];
    i2cNumber = regulator->i2cNum;

    /* Read the regulator CTRL_STATUS and return the status. */
    if (PM_SUCCESS ==
        PmhalL8731ReadPhyAddr(i2cNumber, (uint32_t) PMHAL_L8731_BKLDOEN, &ctrl))
    {
        if ((ctrl &
             ((uint32_t) 1U << (uint32_t) regulator->voltStatusRegShift)) !=
            (uint32_t) PMHAL_L8731_STATUS_OFF)
        {
            enabled = TRUE;
        }
    }

    return enabled;
}

static pmErrCode_t PmhalL8731VoltageToVselOffset(
    pmhalPrcmPmicRegulatorId_t regId,
    uint32_t                   voltage,
    uint32_t                  *vsel)
{
    pmErrCode_t status       = PM_SUCCESS;
    uint32_t    internalVsel = 0U;
    /*
     * regId checks are not done here as this is an internal function and
     * the check would have happened before calling this function.
     */
    const pmhalL8731Regulator_t *regulator =
        gPmhalL8731RegulatorTable[regId];

    if (NULL == vsel)
    {
        status = PM_BADARGS;
    }
    else
    {
        /* Convert the Voltage from mV to 10 ^ (-4) V */
        voltage = voltage * 10U;

        if (0U == voltage)
        {
            internalVsel = 0U;
        }
        else if (voltage > regulator->maxVolt)
        {
            internalVsel = regulator->maxVoltVsel;
            status       = PM_BADARGS;
        }
        else
        {
            /* +1 is added here to ensure the voltage would be higher than
             * requested when the voltage is not an exact multiple of step
             * voltage.
             */
            uint32_t remainder = (voltage - regulator->minVolt) %
                                 regulator->stepVolt;
            if (remainder > 0U)
            {
                internalVsel =
                    ((voltage - regulator->minVolt) / regulator->stepVolt) +
                    regulator->minVoltVsel + 1U;
            }
            else
            {
                internalVsel =
                    ((voltage - regulator->minVolt) / regulator->stepVolt) +
                    regulator->minVoltVsel;
            }
        }

        if (PMHAL_L8731_RTYPE_BUCK == regulator->type)
        {
            /* In the BUCK target voltage register the voltage is represented
             * as the following table:
             *
             * ---------------------------------------------------------------
             * | D7 - D6       |    D5       |   D4 -D0      |   Voltage     |
             * | Reserved      | 12p5 mV Step|    B1TV1      |      (V)      |
             * ---------------------------------------------------------------
             * |               |     0b0     |   0b0 0000    |   0.8875      |
             * |               |     0b1     |   0b0 0000    |   0.9000      |
             * |               |     0b0     |   0b0 0001    |   0.9125      |
             * |               |     0b1     |   0b0 0001    |   0.9000      |
             * | ....................................
             * |               |     0b1     |   0b1 1110    |   1.6500      |
             * |               |     0b0     |   0b1 1111    |   1.6625      |
             * |               |     0b1     |   0b1 1111    |   1.6750      |
             * ---------------------------------------------------------------
             * As can be seen re-arranging the bits as 0b D4 D3 D2 D1 D0 D5 then
             * a sequential numbering scheme can be obtained. Hence even the
             * limits for VSEL are given as the sequential numbering scheme to
             * make the conversion easy.
             */
            *vsel = ((internalVsel & (uint32_t) 0x1U) << (uint32_t) 5U) |
                    ((internalVsel & (uint32_t) 0x1E) >> (uint32_t) 1U);
        }
        else
        {
            *vsel = internalVsel;
        }
    }
    return status;
}

static uint32_t PmhalL8731VselOffsetToVoltage(pmhalPrcmPmicRegulatorId_t regId,
                                              uint32_t                   vsel)
{
    uint32_t mv;
    uint32_t modVsel = 0U;
    /*
     * regId checks are not done here as this is an internal function and
     * the check would have happened before calling this function.
     */
    const pmhalL8731Regulator_t *regulator =
        gPmhalL8731RegulatorTable[regId];

    if (PMHAL_L8731_RTYPE_BUCK == regulator->type)
    {
        /* In the BUCK target voltage register the voltage is represented
         * as the following table:
         *
         * ---------------------------------------------------------------
         * | D7 - D6       |    D5       |   D4 -D0      |   Voltage     |
         * | Reserved      | 12p5 mV Step|    B1TV1      |      (V)      |
         * ---------------------------------------------------------------
         * |               |     0b0     |   0b0 0000    |   0.8875      |
         * |               |     0b1     |   0b0 0000    |   0.9000      |
         * |               |     0b0     |   0b0 0001    |   0.9125      |
         * |               |     0b1     |   0b0 0001    |   0.9000      |
         * | ....................................
         * |               |     0b1     |   0b1 1110    |   1.6500      |
         * |               |     0b0     |   0b1 1111    |   1.6625      |
         * |               |     0b1     |   0b1 1111    |   1.6750      |
         * ---------------------------------------------------------------
         * As can be seen re-arranging the bits as 0b D4 D3 D2 D1 D0 D5 then
         * a sequential numbering scheme can be obtained. Hence even the
         * limits for VSEL are given as the sequential numbering scheme to make
         * the conversion easy.
         */
        modVsel = ((vsel & (uint32_t) 0x1FU) << (uint32_t) 1U) |
                  ((vsel & (uint32_t) 0x20U) >> (uint32_t) 5U);
    }
    else
    {
        modVsel = vsel;
    }

    if (0U == vsel)
    {
        mv = 0U;
    }
    else if (modVsel <= regulator->minVoltVsel)
    {
        mv = regulator->minVolt;
    }
    else if (modVsel >= regulator->maxVoltVsel)
    {
        mv = regulator->maxVolt;
    }
    else
    {
        mv = regulator->minVolt +
             (regulator->stepVolt * (modVsel - regulator->minVoltVsel));
    }
    /* To Convert to milli volt from 10 ^ (-4) volts*/
    mv = mv / 10U;

    return mv;
}

static pmErrCode_t PmhalL8731ReadPhyAddr(uint8_t i2cNumber,
                                         uint32_t phyAddr, uint32_t *value)
{
    uint8_t     slaveAddr;
    uint8_t     regAddr;
    pmErrCode_t status;
    uint8_t     byte;

    if (NULL == value)
    {
        status = PM_BADARGS;
    }
    else
    {
        byte      = (uint8_t) *value;
        slaveAddr = (uint8_t) PMHAL_L8731_CHIP_ADDRESS;
        regAddr   = (uint8_t) phyAddr;
        status    = PMHALPmicCommReadByte(i2cNumber, slaveAddr, regAddr, &byte);
        *value    = byte;
    }

    return status;
}

static pmErrCode_t PmhalL8731WritePhyAddr(uint8_t i2cNumber,
                                          uint32_t phyAddr, uint32_t value)
{
    uint8_t     slaveAddr;
    uint8_t     regAddr;
    uint8_t     byte;
    pmErrCode_t status;

    byte      = (uint8_t) value;
    slaveAddr = (uint8_t) PMHAL_L8731_CHIP_ADDRESS;
    regAddr   = (uint8_t) phyAddr;
    status    = PMHALPmicCommWriteByte(i2cNumber, slaveAddr, regAddr, byte);

    return status;
}

