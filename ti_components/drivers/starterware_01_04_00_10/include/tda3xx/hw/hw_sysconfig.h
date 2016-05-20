/*
* hw_sysconfig.h
*
* register-level header file for IPs missing Sysconfig register
*
* Copyright (c) 2013 Texas Instruments Incorporated.
*
* Except for those rights granted to you in your license from TI,
* all rights reserved.
*
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
* NO WARRANTIES APPLY TO THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR
* STATUTORY.  EXAMPLES OF EXCLUDED WARRANTIES ARE IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE AND WARRANTIES
* OF NON-INFRINGEMENT, BUT ALL OTHER WARRANTY EXCLUSIONS ALSO APPLY.
* FURTHERMORE, TI SHALL NOT, UNDER ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL,
* INCIDENTAL, CONSEQUENTIAL OR PUNITIVE DAMAGES, FOR ANY REASON WHATSOEVER.
*/

#ifndef HW_SYSCONFIG_H_
#define HW_SYSCONFIG_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define ELM_SYSCONFIG                   (0x10U)
#define DMA4_OCP_SYSCONFIG              (0x2CU)
#define PWMSS_SYSCONFIG                 (0x4U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define ELM_SYSCONFIG_SIDLEMODE_SHIFT                                                                       (3U)
#define ELM_SYSCONFIG_SIDLEMODE_MASK                                                                        (0x00000018U)
#define ELM_SYSCONFIG_SIDLEMODE_FORCE_IDLE                                                                   (0U)
#define ELM_SYSCONFIG_SIDLEMODE_NOIDLE                                                                       (1U)
#define ELM_SYSCONFIG_SIDLEMODE_SMARTIDLE                                                                    (2U)
#define ELM_SYSCONFIG_SIDLEMODE_RESERVED3                                                                    (3U)

#define ELM_SYSCONFIG_SOFTRESET_SHIFT                                                                    (1U)
#define ELM_SYSCONFIG_SOFTRESET_MASK                                                                     (0x00000002U)

#define ELM_SYSCONFIG_AUTOIDLE_SHIFT                                                                  (0U)
#define ELM_SYSCONFIG_AUTOIDLE_MASK                                                                   (0x00000001U)
#define ELM_SYSCONFIG_AUTOIDLE_CLKFREE                                                                 (0U)
#define ELM_SYSCONFIG_AUTOIDLE_CLKGATED                                                                (1U)

#define ELM_SYSCONFIG_CLOCKACTIVITY_SHIFT                                                                   (8U)
#define ELM_SYSCONFIG_CLOCKACTIVITY_MASK                                                                    (0x00000100U)
#define ELM_SYSCONFIG_CLOCKACTIVITY_NONE                                                                     (0U)
#define ELM_SYSCONFIG_CLOCKACTIVITY_OCP                                                                      (1U)

#define PWMSS_SYSCONFIG_IDLEMODE_SHIFT                                                                       (2U)
#define PWMSS_SYSCONFIG_IDLEMODE_MASK                                                                        (0x000000cU)
#define PWMSS_SYSCONFIG_IDLEMODE_FORCE_IDLE                                                                    (0U)
#define PWMSS_SYSCONFIG_IDLEMODE_NOIDLE                                                                       (1U)
#define PWMSS_SYSCONFIG_IDLEMODE_SMARTIDLE                                                                    (2U)
#define PWMSS_SYSCONFIG_IDLEMODE_RESERVED3                                                                    (3U)

#define PWMSS_SYSCONFIG_SOFTRESET_SHIFT                                                                    (0U)
#define PWMSS_SYSCONFIG_SOFTRESET_MASK                                                                     (0x00000001U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_SYSCONFIG_H_ */
