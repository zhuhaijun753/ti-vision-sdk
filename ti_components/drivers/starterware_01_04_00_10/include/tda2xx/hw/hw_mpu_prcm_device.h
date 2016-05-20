/******************************************************************************
*
* hw_mpu_prcm_device.h - register-level header file for MPU
*
* Copyright (c) 2008-2013 Texas Instruments Incorporated.  All rights reserved.
* Software License Agreement
*
* Texas Instruments (TI) is supplying this software for use solely and
* exclusively on TI devices. The software is owned by TI and/or its
* suppliers, and is protected under applicable patent and copyright laws.
*
* You may not combine this software with any open-source software if such
* combination would cause this software to become subject to any of the
* license terms applicable to such open source software.
*
* THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
* NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
* NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
* CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
* DAMAGES, FOR ANY REASON WHATSOEVER.
* 
******************************************************************************
*/
#ifndef HW_MPU_PRCM_DEVICE_H_
#define HW_MPU_PRCM_DEVICE_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define MPU_PRM_RSTST                                                                                      (0x0U)
#define MPU_PRM_PSCON_COUNT                                                                                (0x4U)
#define MPU_PRM_FRAC_INCREMENTER_NUMERATOR                                                                 (0x10U)
#define MPU_PRM_FRAC_INCREMENTER_DENUMERATOR_RELOAD                                                        (0x14U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define MPU_PRM_RSTST_GLOBAL_COLD_RST_SHIFT                                                               (0U)
#define MPU_PRM_RSTST_GLOBAL_COLD_RST_MASK                                                                (0x00000001U)
#define MPU_PRM_RSTST_GLOBAL_COLD_RST_0X0                                                                 (0U)
#define MPU_PRM_RSTST_GLOBAL_COLD_RST_0X1                                                                 (1U)

#define MPU_PRM_RSTST_GLOBAL_WARM_RST_SHIFT                                                               (1U)
#define MPU_PRM_RSTST_GLOBAL_WARM_RST_MASK                                                                (0x00000002U)
#define MPU_PRM_RSTST_GLOBAL_WARM_RST_0X0                                                                 (0U)
#define MPU_PRM_RSTST_GLOBAL_WARM_RST_0X1                                                                 (1U)

#define MPU_PRM_RSTST_RESERVED_SHIFT                                                                      (2U)
#define MPU_PRM_RSTST_RESERVED_MASK                                                                       (0xfffffffcU)

#define MPU_PRM_PSCON_COUNT_PCHARGE_TIME_SHIFT                                                            (0U)
#define MPU_PRM_PSCON_COUNT_PCHARGE_TIME_MASK                                                             (0x000000ffU)

#define MPU_PRM_PSCON_COUNT_RESERVED_SHIFT                                                                (8U)
#define MPU_PRM_PSCON_COUNT_RESERVED_MASK                                                                 (0x0000ff00U)

#define MPU_PRM_PSCON_COUNT_RESERVED1_SHIFT                                                               (26U)
#define MPU_PRM_PSCON_COUNT_RESERVED1_MASK                                                                (0xfc000000U)

#define MPU_PRM_PSCON_COUNT_HG_PONOUT_2_PGDOODIN_TIME_SHIFT                                               (16U)
#define MPU_PRM_PSCON_COUNT_HG_PONOUT_2_PGDOODIN_TIME_MASK                                                (0x00ff0000U)

#define MPU_PRM_PSCON_COUNT_HG_RAMPUP_SHIFT                                                               (25U)
#define MPU_PRM_PSCON_COUNT_HG_RAMPUP_MASK                                                                (0x02000000U)
#define MPU_PRM_PSCON_COUNT_HG_RAMPUP_SLOW                                                                (0U)
#define MPU_PRM_PSCON_COUNT_HG_RAMPUP_FAST                                                                (1U)

#define MPU_PRM_PSCON_COUNT_HG_EN_SHIFT                                                                   (24U)
#define MPU_PRM_PSCON_COUNT_HG_EN_MASK                                                                    (0x01000000U)
#define MPU_PRM_PSCON_COUNT_HG_EN_HG_DISABLE                                                              (0U)
#define MPU_PRM_PSCON_COUNT_HG_EN_HG_ENABLE                                                               (1U)

#define MPU_PRM_FRAC_INCREMENTER_NUMERATOR_SYS_MODE_NUMERATOR_SHIFT                                       (0U)
#define MPU_PRM_FRAC_INCREMENTER_NUMERATOR_SYS_MODE_NUMERATOR_MASK                                        (0x00000fffU)

#define MPU_PRM_FRAC_INCREMENTER_NUMERATOR_RESERVED_SHIFT                                                 (12U)
#define MPU_PRM_FRAC_INCREMENTER_NUMERATOR_RESERVED_MASK                                                  (0x0000f000U)

#define MPU_PRM_FRAC_INCREMENTER_NUMERATOR_RESERVED1_SHIFT                                                (28U)
#define MPU_PRM_FRAC_INCREMENTER_NUMERATOR_RESERVED1_MASK                                                 (0xf0000000U)

#define MPU_PRM_FRAC_INCREMENTER_NUMERATOR_ABE_LP_MODE_NUMERATOR_SHIFT                                    (16U)
#define MPU_PRM_FRAC_INCREMENTER_NUMERATOR_ABE_LP_MODE_NUMERATOR_MASK                                     (0x0fff0000U)

#define MPU_PRM_FRAC_INCREMENTER_DENUMERATOR_RELOAD_DENOMINATOR_SHIFT                                     (0U)
#define MPU_PRM_FRAC_INCREMENTER_DENUMERATOR_RELOAD_DENOMINATOR_MASK                                      (0x00000fffU)

#define MPU_PRM_FRAC_INCREMENTER_DENUMERATOR_RELOAD_RESERVED_SHIFT                                        (12U)
#define MPU_PRM_FRAC_INCREMENTER_DENUMERATOR_RELOAD_RESERVED_MASK                                         (0x0000f000U)

#define MPU_PRM_FRAC_INCREMENTER_DENUMERATOR_RELOAD_RESERVED1_SHIFT                                       (17U)
#define MPU_PRM_FRAC_INCREMENTER_DENUMERATOR_RELOAD_RESERVED1_MASK                                        (0xfffe0000U)

#define MPU_PRM_FRAC_INCREMENTER_DENUMERATOR_RELOAD_RELOAD_SHIFT                                          (16U)
#define MPU_PRM_FRAC_INCREMENTER_DENUMERATOR_RELOAD_RELOAD_MASK                                           (0x00010000U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_MPU_PRCM_DEVICE_H_ */
