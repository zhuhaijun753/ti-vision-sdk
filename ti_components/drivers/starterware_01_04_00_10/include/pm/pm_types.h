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
 *  \file  pm_types.h
 *
 *  \brief This file contains all the error types that are used for PM Layer.
 *
 */

#ifndef PM_TYPES_H_
#define PM_TYPES_H_

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

/**< \brief Define True and False Values */
#ifndef TRUE
#define TRUE  ((uint32_t) 1U)
#endif
#ifndef FALSE
#define FALSE ((uint32_t) 0U)
#endif

/**< \brief PM_TIMEOUT_INFINITE: Macro defining the flag for infinite timeout */
#define PM_TIMEOUT_INFINITE         (0xFFFFFFFFU)

/**< \brief PM_TIMEOUT_NOWAIT: Macro defining the flag for no time out */
#define PM_TIMEOUT_NOWAIT           ((uint32_t) 0x0U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
typedef enum
{
    /**-----------------------------------------------------------------------
     * Generic Error Codes.
     */
    PM_SUCCESS = 0,
    /**< return type SUCCESS */
    PM_FAIL = -1,
    /**< return type FAIL */
    PM_BADARGS = -2,
    /**< return type BADARGS */
    PM_TIMEOUT = -3,
    /**< return type TIMEOUT */
    /**-----------------------------------------------------------------------
     * Module Manager Error Codes
     */
    PM_INPUT_PARAM_BAD_MODULE_ID = -4,
    /**< return type INPUT PARAM BAD MODULE ID */
    PM_MM_MODULE_SYSCONFIG_NOT_AVAILABLE = -5,
    /**< return type PM_MM Module does not support a sysconfig register */
    PM_MM_MODULE_CLOCK_CTRL_REG_NOT_AVAILABLE = -6,
    /**< return type PM_MM Module does not support clock control register */
    PM_MM_MODULE_SYSCONFIG_CLKACTIVITY_NOT_PRESENT = -7,
    /**< return type PM_MM Module does not support sysconfig clock activity */
    PM_MM_MODULE_STANDBY_MODE_NOT_SUPPORTED = -8,
    /**< return type PM_MM Module does not support any standby mode */
    PM_INPUT_PARAM_BAD_MODULE_MODE = -9,
    /**< return type INPUT PARAM BAD MODULE MODE */
    PM_INPUT_MODULE_STANDBY_MODE_INVALID = -10,
    /**< return type INPUT Standby Mode Invalid */
    PM_INPUT_MODULE_IDLE_MODE_INVALID = -11,
    /**< return type INPUT Idle Mode Invalid */
    /**-----------------------------------------------------------------------
     * Reset Domain Manager Error Codes
     */
    PM_INPUT_PARAM_BAD_RESET_ID = -12,
    /**< return type INPUT PARAM BAD RESET ID */
    PM_INPUT_PARAM_NONCONFIGURABLE_RESET_DOMAIN_ID = -13,
    /**< return type INPUT PARAM NONCONFIGURABLE RESET DOMAIN ID */
    PM_RM_BAD_RESET_OCCURANCE_TYPE = -14,
    /**<return type PM_RM Bad Reset Occurrence given */
    /**-----------------------------------------------------------------------
     * Clock Manager Error Codes
     */
    PM_INPUT_PARAM_BAD_DPLL_ID = -15,
    /**< return type INPUT PARAM BAD DPLL ID */
    PM_CM_DPLL_CLK_SEL_REGISTER_INVALID = -16,
    /**< return type PM_CM Dpll Clock Selection Register Invalid */
    PM_CM_DPLL_CLK_MODE_REGISTER_INVALID = -17,
    /**< return type PM_CM Dpll Clock Mode Register Invalid */
    PM_CM_DPLL_IDLEST_REGISTER_INVALID = -18,
    /**< return type PM_CM Dpll Idle State Register Invalid */
    PM_CM_DPLL_POWER_MODE_NOT_SUPPORTED = -19,
    /**< return type PM_CM DPLL Power mode not supported */
    PM_CM_DPLL_MULTIPLIER_VALUE_OUT_OF_RANGE = -20,
    /**< return type PM_CM DPLL Multiplier value out of range */
    PM_CM_DPLL_DIVIDER_VALUE_OUT_OF_RANGE = -21,
    /**< return type PM_CM DPLL Divider value out of range */
    PM_CM_DPLL_AUTO_IDLE_REGISTER_INVALID = -22,
    /**< return type PM_CM DPLL Auto IDLE register is Invalid */
    PM_CM_DPLL_AUTO_IDLE_PROGRAMMING_NOT_AVAILABLE = -23,
    /**< return type PM_CM DPLL Auto IDLE register programming is not allowed */
    PM_INPUT_PARAM_BAD_CLOCK_ID = -24,
    /**< return type INPUT PARAM BAD CLOCK ID */
    PM_INPUT_PARAM_BAD_CLK_DOMAIN_ID = -25,
    /**< return type INPUT PARAM BAD CLK DOMAIN ID */
    PM_CM_MODULE_CLKSEL_CONFIG_NOT_AVAILABLE = -26,
    /**< return type PM_CM Module clock select configuration not available */
    PM_CM_CLOCK_DOMAIN_CLK_STATE_CTRL_REG_INVALID = -27,
    /**< return type PM_CM Clock Domain Clock State Ctrl Register Invalid */
    PM_INPUT_PARAM_BAD_MUX_ID = -28,
    /**< return type PM_CM Mux Id not valid */
    PM_INPUT_PARAM_BAD_DIV_ID = -29,
    /**< return type PM_CM Divider ID not valid */
    PM_CM_MUX_CLK_SEL_REGISTER_INVALID = -30,
    /**< return type PM_CM Mux Clock Select Register Invalid */
    PM_CM_CLK_DOMAIN_TRANS_MODE_NOT_SUPPORTED = -31,
    /**< return type PM_CM Clock Domain transition mode not supported */
    PM_CM_MUX_PARENT_SELECTION_INVALID = -32,
    /**< return type PM_CM Mux Parent Selection Not valid */
    PM_CM_POST_DIV_REGISTER_INVALID = -33,
    /**< return type PM_CM Post Divider register Invalid */
    PM_INPUT_PARAM_BAD_POST_DIV_ID = -34,
    /**< return type PM_CM Bad Post Divider ID */
    PM_CM_CLKSEL_CTRL_NOT_APPLICABLE = -35,
    /**< return type PM_CM Clock Selection control not applicable */
    PM_CM_DIV_SEL_REGISTER_NOT_APPLICABLE = -36,
    /**< return type PM_CM Clock Divider Select control not applicable */
    /**-----------------------------------------------------------------------
     * Voltage and PMIC Manager Error Codes
     */
    PM_INPUT_PARAM_BAD_VOLTAGE_ID = -37,
    /**< return type INPUT PARAM BAD VOLTAGE ID */
    PM_PMIC_VENDOR_ID_INVALID = -38,
    /**< return type PMIC VENDOR ID INVALID */
    PM_PMIC_PRODUCT_ID_INVALID = -39,
    /**< return type PMIC PRODUCT ID INVALID */
    PM_REGULATOR_STATE_INVALID = -40,
    /**< return type REGULATOR STATE INVALID */
    PM_PMIC_COMM_TIMEOUT_ERROR = -41,
    /**< return type PMIC_COMM TIMEOUT ERROR */
    PM_PMIC_COMM_NO_ACK_ERROR = -42,
    /**< return type PMIC_COMM NO ACK ERROR */
    PM_PMIC_COMM_ARB_LOST_ERROR = -43,
    /**< return type PMIC_COMM ARB LOST ERROR */
    PM_PMIC_COMM_ARDY_ERROR = -44,
    /**< return type PMIC_COMM ARDY ERROR */
    PM_VOLTAGE_INVALID = -45,
    /**< return type VOLTAGE INVALID */
    PM_OPP_INVALID = -46,
    /**< return type OPP INVALID */
    /**-----------------------------------------------------------------------
     * Power Domain Manager Error Codes
     */
    PM_INPUT_PARAM_BAD_POWER_DOMAIN_ID = -47,
    /**< return type INPUT PARAM BAD POWER DOMAIN ID */
    PM_PDM_PDSTATE_NOT_SUPPORTED = -48,
    /**<return type PM_PDM Power State not supported */
    PM_PDM_LOGIC_RET_STATE_NOT_SUPPORTED = -49,
    /**<return type PM_PDM Power State not supported */
    PM_PDM_LOW_POWER_REQUEST_NOT_SUPPORTED = -50,
    /**<return type PM_PDM Low Power request not supported */
    PM_PDM_MEM_RET_STATE_NOT_SUPPORTED = -51,
    /**<return type PM_PDM Memory retention state not supported */
    PM_PDM_POWER_STATE_CTRL_REGISTER_NOT_VALID = -52,
    /**<return type PM_PDM Power state Ctrl Register not valid */
    PM_PDM_POWER_STATE_STATUS_REGISTER_NOT_VALID = -53,
    /**<return type PM_PDM Power state status Register not valid */
    PM_INPUT_PARAM_BAD_PHYSICAL_MEMORY_ID = -54,
    /**< return type INPUT PARAM BAD PHYSICAL MEMORY ID */
    /**-----------------------------------------------------------------------
     * PMLIB System Config Error Codes
     */
    PM_SYS_CONFIG_MODULE_CANNOT_BE_ENABLED = -55,
    /**< return type PMLIB System Config Module Cannot be enabled */
    PM_SYS_CONFIG_MODULE_CANNOT_BE_DISABLED = -56,
    /**< return type PMLIB System Config Module Cannot be disabled */
    PM_SYS_CONFIG_MODULE_NOT_GETTING_DISABLED = -57,
    /**< return type PMLIB System Config Module not getting disabled */
    PM_SYS_CONFIG_MODULE_HAS_DEPENDENCIES = -58,
    /**< return type PMLIB System Config Module has dependencies */
    PM_SYS_CONFIG_MODULE_CANNOT_BE_AUTOCG = -59,
    /**< return type PMLIB System Config Module Cannot be auto clock gated */
    /**-----------------------------------------------------------------------
     * Static Dependency Interrupt Manager Error Codes
     */
    PM_SD_CLOCK_DOMAIN_DEPENDENCY_HARDWIRED = -60,
    /**< return type Static dependency Clock domain dependency hard wired */
    /**-----------------------------------------------------------------------
     * PRM Interrupt Manager Error Codes
     */
    PM_INPUT_PARAM_BAD_CPU_ID = -61,
    /**< return type INPUT PARAM BAD PM IRQ ID */
    /**-----------------------------------------------------------------------
     * Clocktree Manager Error Codes
     */
    PM_INPUT_PARAM_BAD_CLOCKTREE_NODE_ID = -62,
    /**< return type INPUT PARAM CLOCKTREE NODE ID */
    PM_INPUT_PARAM_BAD_CLOCKTREE_EDGE_PROPERTY_ID = -63,
    /**< return type INPUT PARAM CLOCKTREE EDGE PROPERTY ID */
    PM_CLOCTREE_EDGE_NOT_AVAILABLE = -64,
    /**< return type PM_CLOCTREE Edge is not available */
    /**-----------------------------------------------------------------------
     * Clockrate Manager Error Codes
     */
    PM_CLOCKRATE_ROOTCLK_NOT_SUPPORTED = -65,
    /**< return type PM_CLOCKRATE root clock is not supported */
    PM_CLOCKRATE_SAME_FREQ_CHANGE_REQ = -66,
    /**< return type PM_CLOCKRATE same frequency change requested */
    PM_CLOCKRATE_FREQ_NOT_SUPPORTED = -67,
    /**< return type PM_CLOCKRATE frequency not supported */
    /**-----------------------------------------------------------------------
     * VideoPLL Error Codes
     */
    PM_VIDEOPLL_HSDIV_NOT_VALID = -68,
    /**< return type PM Video PLL HSDIV is not valid */
    PM_VIDEOPLL_HSDIV_NOT_ENABLED = -69,
    /**< return type PM Video PLL HSDIV is not enabled */
    PM_VIDEOPLL_HSDIV_NOT_SUPPORTED = -70,
    /**< return type PM Video PLL HSDIV is not supported */
    PM_VIDEOPLL_CALC_PARAMS_FAILED = -71,
    /**< return type PM Video calc params failed */
    /**-----------------------------------------------------------------------
     * Book Keeping Error Codes
     */
    PM_MIN_ERR_CODE = PM_VIDEOPLL_CALC_PARAMS_FAILED,
    /**< Minimum Number of Return Codes */
    PM_COUNT_ERR_CODE = -PM_MIN_ERR_CODE + 1
                        /**< Number of Return Codes */
} pmErrCode_t;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif

