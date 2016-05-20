/******************************************************************************
*
* hw_mailbox.h - register-level header file for MAILBOX
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
#ifndef HW_MAILBOX_H_
#define HW_MAILBOX_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define MAILBOX_REVISION                                                                                   (0x0U)
#define MAILBOX_SYSCONFIG                                                                                  (0x10U)
#define MAILBOX_MESSAGE(n)                                                                                 ((uint32_t)0x40U + ((n) * 4U))
#define MAILBOX_FIFOSTATUS(n)                                                                              ((uint32_t)0x80U + ((n) * 4U))
#define MAILBOX_MSGSTATUS(n)                                                                               ((uint32_t)0xc0U + ((n) * 4U))
#define MAILBOX_IRQSTATUS_RAW(n)                                                                           ((uint32_t)0x100U + ((n) * 16U))
#define MAILBOX_IRQSTATUS_CLR(n)                                                                           ((uint32_t)0x104U + ((n) * 16U))
#define MAILBOX_IRQENABLE_CLR(n)                                                                           ((uint32_t)0x10cU + ((n) * 16U))
#define MAILBOX_IRQENABLE_SET(n)                                                                           ((uint32_t)0x108U + ((n) * 16U))

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define MAILBOX_REVISION_REVISION_SHIFT                                                                   (0U)
#define MAILBOX_REVISION_REVISION_MASK                                                                    (0xffffffffU)

#define MAILBOX_SYSCONFIG_SOFTRESET_SHIFT                                                                 (0U)
#define MAILBOX_SYSCONFIG_SOFTRESET_MASK                                                                  (0x00000001U)
#define MAILBOX_SYSCONFIG_SOFTRESET_B0                                                                    (0U)
#define MAILBOX_SYSCONFIG_SOFTRESET_B1                                                                    (1U)

#define MAILBOX_SYSCONFIG_SIDLEMODE_SHIFT                                                                 (2U)
#define MAILBOX_SYSCONFIG_SIDLEMODE_MASK                                                                  (0x0000000cU)
#define MAILBOX_SYSCONFIG_SIDLEMODE_B00                                                                   (0U)
#define MAILBOX_SYSCONFIG_SIDLEMODE_B01                                                                   (1U)
#define MAILBOX_SYSCONFIG_SIDLEMODE_B10                                                                   (2U)
#define MAILBOX_SYSCONFIG_SIDLEMODE_B11                                                                   (3U)

#define MAILBOX_SYSCONFIG_RESERVED_1_SHIFT                                                                (1U)
#define MAILBOX_SYSCONFIG_RESERVED_1_MASK                                                                 (0x00000002U)
#define MAILBOX_SYSCONFIG_RESERVED_1_B0                                                                   (0U)
#define MAILBOX_SYSCONFIG_RESERVED_1_B1                                                                   (1U)

#define MAILBOX_SYSCONFIG_RESERVED_2_SHIFT                                                                (4U)
#define MAILBOX_SYSCONFIG_RESERVED_2_MASK                                                                 (0xfffffff0U)

#define MAILBOX_MESSAGE_MESSAGEVALUEMBM_SHIFT                                                             (0U)
#define MAILBOX_MESSAGE_MESSAGEVALUEMBM_MASK                                                              (0xffffffffU)

#define MAILBOX_FIFOSTATUS_FIFOFULLMBM_SHIFT                                                              (0U)
#define MAILBOX_FIFOSTATUS_FIFOFULLMBM_MASK                                                               (0x00000001U)

#define MAILBOX_FIFOSTATUS_RESERVED_0_SHIFT                                                               (1U)
#define MAILBOX_FIFOSTATUS_RESERVED_0_MASK                                                                (0xfffffffeU)

#define MAILBOX_MSGSTATUS_NBOFMSGMBM_SHIFT                                                                (0U)
#define MAILBOX_MSGSTATUS_NBOFMSGMBM_MASK                                                                 (0x0000007fU)

#define MAILBOX_MSGSTATUS_RESERVED_SHIFT                                                                  (7U)
#define MAILBOX_MSGSTATUS_RESERVED_MASK                                                                   (0xffffff80U)

#define MAILBOX_IRQSTATUS_RAW_NEWMSGSTATUSUUMB0_SHIFT                                                     (0U)
#define MAILBOX_IRQSTATUS_RAW_NEWMSGSTATUSUUMB0_MASK                                                      (0x00000001U)

#define MAILBOX_IRQSTATUS_RAW_NEWMSGSTATUSUUMB1_SHIFT                                                     (2U)
#define MAILBOX_IRQSTATUS_RAW_NEWMSGSTATUSUUMB1_MASK                                                      (0x00000004U)

#define MAILBOX_IRQSTATUS_RAW_NOTFULLSTATUSUUMB1_SHIFT                                                    (3U)
#define MAILBOX_IRQSTATUS_RAW_NOTFULLSTATUSUUMB1_MASK                                                     (0x00000008U)

#define MAILBOX_IRQSTATUS_RAW_NOTFULLSTATUSUUMB0_SHIFT                                                    (1U)
#define MAILBOX_IRQSTATUS_RAW_NOTFULLSTATUSUUMB0_MASK                                                     (0x00000002U)

#define MAILBOX_IRQSTATUS_RAW_NEWMSGSTATUSUUMB2_SHIFT                                                     (4U)
#define MAILBOX_IRQSTATUS_RAW_NEWMSGSTATUSUUMB2_MASK                                                      (0x00000010U)

#define MAILBOX_IRQSTATUS_RAW_NOTFULLSTATUSUUMB2_SHIFT                                                    (5U)
#define MAILBOX_IRQSTATUS_RAW_NOTFULLSTATUSUUMB2_MASK                                                     (0x00000020U)

#define MAILBOX_IRQSTATUS_RAW_NEWMSGSTATUSUUMB3_SHIFT                                                     (6U)
#define MAILBOX_IRQSTATUS_RAW_NEWMSGSTATUSUUMB3_MASK                                                      (0x00000040U)

#define MAILBOX_IRQSTATUS_RAW_NOTFULLSTATUSUUMB3_SHIFT                                                    (7U)
#define MAILBOX_IRQSTATUS_RAW_NOTFULLSTATUSUUMB3_MASK                                                     (0x00000080U)

#define MAILBOX_IRQSTATUS_RAW_NEWMSGSTATUSUUMB4_SHIFT                                                     (8U)
#define MAILBOX_IRQSTATUS_RAW_NEWMSGSTATUSUUMB4_MASK                                                      (0x00000100U)

#define MAILBOX_IRQSTATUS_RAW_NOTFULLSTATUSUUMB4_SHIFT                                                    (9U)
#define MAILBOX_IRQSTATUS_RAW_NOTFULLSTATUSUUMB4_MASK                                                     (0x00000200U)

#define MAILBOX_IRQSTATUS_RAW_NEWMSGSTATUSUUMB5_SHIFT                                                     (10U)
#define MAILBOX_IRQSTATUS_RAW_NEWMSGSTATUSUUMB5_MASK                                                      (0x00000400U)

#define MAILBOX_IRQSTATUS_RAW_NOTFULLSTATUSUUMB5_SHIFT                                                    (11U)
#define MAILBOX_IRQSTATUS_RAW_NOTFULLSTATUSUUMB5_MASK                                                     (0x00000800U)

#define MAILBOX_IRQSTATUS_RAW_NOTFULLSTATUSUUMB6_SHIFT                                                    (13U)
#define MAILBOX_IRQSTATUS_RAW_NOTFULLSTATUSUUMB6_MASK                                                     (0x00002000U)

#define MAILBOX_IRQSTATUS_RAW_NEWMSGSTATUSUUMB6_SHIFT                                                     (12U)
#define MAILBOX_IRQSTATUS_RAW_NEWMSGSTATUSUUMB6_MASK                                                      (0x00001000U)

#define MAILBOX_IRQSTATUS_RAW_NEWMSGSTATUSUUMB7_SHIFT                                                     (14U)
#define MAILBOX_IRQSTATUS_RAW_NEWMSGSTATUSUUMB7_MASK                                                      (0x00004000U)

#define MAILBOX_IRQSTATUS_RAW_NOTFULLSTATUSUUMB7_SHIFT                                                    (15U)
#define MAILBOX_IRQSTATUS_RAW_NOTFULLSTATUSUUMB7_MASK                                                     (0x00008000U)

#define MAILBOX_IRQSTATUS_RAW_RESERVED_SHIFT                                                              (16U)
#define MAILBOX_IRQSTATUS_RAW_RESERVED_MASK                                                               (0xffff0000U)

#define MAILBOX_IRQSTATUS_CLR_NOTFULLSTATUSENUUMB0_SHIFT                                                  (1U)
#define MAILBOX_IRQSTATUS_CLR_NOTFULLSTATUSENUUMB0_MASK                                                   (0x00000002U)

#define MAILBOX_IRQSTATUS_CLR_NOTFULLSTATUSENUUMB1_SHIFT                                                  (3U)
#define MAILBOX_IRQSTATUS_CLR_NOTFULLSTATUSENUUMB1_MASK                                                   (0x00000008U)

#define MAILBOX_IRQSTATUS_CLR_NOTFULLSTATUSENUUMB2_SHIFT                                                  (5U)
#define MAILBOX_IRQSTATUS_CLR_NOTFULLSTATUSENUUMB2_MASK                                                   (0x00000020U)

#define MAILBOX_IRQSTATUS_CLR_NOTFULLSTATUSENUUMB3_SHIFT                                                  (7U)
#define MAILBOX_IRQSTATUS_CLR_NOTFULLSTATUSENUUMB3_MASK                                                   (0x00000080U)

#define MAILBOX_IRQSTATUS_CLR_NOTFULLSTATUSENUUMB4_SHIFT                                                  (9U)
#define MAILBOX_IRQSTATUS_CLR_NOTFULLSTATUSENUUMB4_MASK                                                   (0x00000200U)

#define MAILBOX_IRQSTATUS_CLR_NOTFULLSTATUSENUUMB5_SHIFT                                                  (11U)
#define MAILBOX_IRQSTATUS_CLR_NOTFULLSTATUSENUUMB5_MASK                                                   (0x00000800U)

#define MAILBOX_IRQSTATUS_CLR_NOTFULLSTATUSENUUMB6_SHIFT                                                  (13U)
#define MAILBOX_IRQSTATUS_CLR_NOTFULLSTATUSENUUMB6_MASK                                                   (0x00002000U)

#define MAILBOX_IRQSTATUS_CLR_NOTFULLSTATUSENUUMB7_SHIFT                                                  (15U)
#define MAILBOX_IRQSTATUS_CLR_NOTFULLSTATUSENUUMB7_MASK                                                   (0x00008000U)

#define MAILBOX_IRQSTATUS_CLR_NEWMSGSTATUSENUUMB0_SHIFT                                                   (0U)
#define MAILBOX_IRQSTATUS_CLR_NEWMSGSTATUSENUUMB0_MASK                                                    (0x00000001U)

#define MAILBOX_IRQSTATUS_CLR_NEWMSGSTATUSENUUMB1_SHIFT                                                   (2U)
#define MAILBOX_IRQSTATUS_CLR_NEWMSGSTATUSENUUMB1_MASK                                                    (0x00000004U)

#define MAILBOX_IRQSTATUS_CLR_NEWMSGSTATUSENUUMB2_SHIFT                                                   (4U)
#define MAILBOX_IRQSTATUS_CLR_NEWMSGSTATUSENUUMB2_MASK                                                    (0x00000010U)

#define MAILBOX_IRQSTATUS_CLR_NEWMSGSTATUSENUUMB3_SHIFT                                                   (6U)
#define MAILBOX_IRQSTATUS_CLR_NEWMSGSTATUSENUUMB3_MASK                                                    (0x00000040U)

#define MAILBOX_IRQSTATUS_CLR_NEWMSGSTATUSENUUMB4_SHIFT                                                   (8U)
#define MAILBOX_IRQSTATUS_CLR_NEWMSGSTATUSENUUMB4_MASK                                                    (0x00000100U)

#define MAILBOX_IRQSTATUS_CLR_NEWMSGSTATUSENUUMB5_SHIFT                                                   (10U)
#define MAILBOX_IRQSTATUS_CLR_NEWMSGSTATUSENUUMB5_MASK                                                    (0x00000400U)

#define MAILBOX_IRQSTATUS_CLR_NEWMSGSTATUSENUUMB6_SHIFT                                                   (12U)
#define MAILBOX_IRQSTATUS_CLR_NEWMSGSTATUSENUUMB6_MASK                                                    (0x00001000U)

#define MAILBOX_IRQSTATUS_CLR_NEWMSGSTATUSENUUMB7_SHIFT                                                   (14U)
#define MAILBOX_IRQSTATUS_CLR_NEWMSGSTATUSENUUMB7_MASK                                                    (0x00004000U)

#define MAILBOX_IRQSTATUS_CLR_RESERVED_SHIFT                                                              (16U)
#define MAILBOX_IRQSTATUS_CLR_RESERVED_MASK                                                               (0xffff0000U)

#define MAILBOX_IRQENABLE_CLR_NEWMSGENABLEUUMB0_SHIFT                                                     (0U)
#define MAILBOX_IRQENABLE_CLR_NEWMSGENABLEUUMB0_MASK                                                      (0x00000001U)

#define MAILBOX_IRQENABLE_CLR_NEWMSGENABLEUUMB1_SHIFT                                                     (2U)
#define MAILBOX_IRQENABLE_CLR_NEWMSGENABLEUUMB1_MASK                                                      (0x00000004U)

#define MAILBOX_IRQENABLE_CLR_NEWMSGENABLEUUMB5_SHIFT                                                     (10U)
#define MAILBOX_IRQENABLE_CLR_NEWMSGENABLEUUMB5_MASK                                                      (0x00000400U)

#define MAILBOX_IRQENABLE_CLR_NEWMSGENABLEUUMB3_SHIFT                                                     (6U)
#define MAILBOX_IRQENABLE_CLR_NEWMSGENABLEUUMB3_MASK                                                      (0x00000040U)

#define MAILBOX_IRQENABLE_CLR_NEWMSGENABLEUUMB2_SHIFT                                                     (4U)
#define MAILBOX_IRQENABLE_CLR_NEWMSGENABLEUUMB2_MASK                                                      (0x00000010U)

#define MAILBOX_IRQENABLE_CLR_NEWMSGENABLEUUMB6_SHIFT                                                     (12U)
#define MAILBOX_IRQENABLE_CLR_NEWMSGENABLEUUMB6_MASK                                                      (0x00001000U)

#define MAILBOX_IRQENABLE_CLR_NEWMSGENABLEUUMB7_SHIFT                                                     (14U)
#define MAILBOX_IRQENABLE_CLR_NEWMSGENABLEUUMB7_MASK                                                      (0x00004000U)

#define MAILBOX_IRQENABLE_CLR_NOTFULLENABLEUUMB6_SHIFT                                                    (13U)
#define MAILBOX_IRQENABLE_CLR_NOTFULLENABLEUUMB6_MASK                                                     (0x00002000U)

#define MAILBOX_IRQENABLE_CLR_NOTFULLENABLEUUMB2_SHIFT                                                    (5U)
#define MAILBOX_IRQENABLE_CLR_NOTFULLENABLEUUMB2_MASK                                                     (0x00000020U)

#define MAILBOX_IRQENABLE_CLR_NOTFULLENABLEUUMB7_SHIFT                                                    (15U)
#define MAILBOX_IRQENABLE_CLR_NOTFULLENABLEUUMB7_MASK                                                     (0x00008000U)

#define MAILBOX_IRQENABLE_CLR_NOTFULLENABLEUUMB5_SHIFT                                                    (11U)
#define MAILBOX_IRQENABLE_CLR_NOTFULLENABLEUUMB5_MASK                                                     (0x00000800U)

#define MAILBOX_IRQENABLE_CLR_NOTFULLENABLEUUMB1_SHIFT                                                    (3U)
#define MAILBOX_IRQENABLE_CLR_NOTFULLENABLEUUMB1_MASK                                                     (0x00000008U)

#define MAILBOX_IRQENABLE_CLR_NOTFULLENABLEUUMB3_SHIFT                                                    (7U)
#define MAILBOX_IRQENABLE_CLR_NOTFULLENABLEUUMB3_MASK                                                     (0x00000080U)

#define MAILBOX_IRQENABLE_CLR_NOTFULLENABLEUUMB8_SHIFT                                                    (17U)
#define MAILBOX_IRQENABLE_CLR_NOTFULLENABLEUUMB8_MASK                                                     (0x00020000U)

#define MAILBOX_IRQENABLE_CLR_NOTFULLENABLEUUMB4_SHIFT                                                    (9U)
#define MAILBOX_IRQENABLE_CLR_NOTFULLENABLEUUMB4_MASK                                                     (0x00000200U)

#define MAILBOX_IRQENABLE_CLR_NOTFULLENABLEUUMB0_SHIFT                                                    (1U)
#define MAILBOX_IRQENABLE_CLR_NOTFULLENABLEUUMB0_MASK                                                     (0x00000002U)

#define MAILBOX_IRQENABLE_CLR_NEWMSGENABLEUUMB4_SHIFT                                                     (8U)
#define MAILBOX_IRQENABLE_CLR_NEWMSGENABLEUUMB4_MASK                                                      (0x00000100U)

#define MAILBOX_IRQENABLE_CLR_RESERVED_SHIFT                                                              (16U)
#define MAILBOX_IRQENABLE_CLR_RESERVED_MASK                                                               (0xffff0000U)

#define MAILBOX_IRQENABLE_SET_NOTFULLENABLEUUMB0_SHIFT                                                    (1U)
#define MAILBOX_IRQENABLE_SET_NOTFULLENABLEUUMB0_MASK                                                     (0x00000002U)

#define MAILBOX_IRQENABLE_SET_NOTFULLENABLEUUMB4_SHIFT                                                    (9U)
#define MAILBOX_IRQENABLE_SET_NOTFULLENABLEUUMB4_MASK                                                     (0x00000200U)

#define MAILBOX_IRQENABLE_SET_NOTFULLENABLEUUMB3_SHIFT                                                    (7U)
#define MAILBOX_IRQENABLE_SET_NOTFULLENABLEUUMB3_MASK                                                     (0x00000080U)

#define MAILBOX_IRQENABLE_SET_NOTFULLENABLEUUMB1_SHIFT                                                    (3U)
#define MAILBOX_IRQENABLE_SET_NOTFULLENABLEUUMB1_MASK                                                     (0x00000008U)

#define MAILBOX_IRQENABLE_SET_NOTFULLENABLEUUMB5_SHIFT                                                    (11U)
#define MAILBOX_IRQENABLE_SET_NOTFULLENABLEUUMB5_MASK                                                     (0x00000800U)

#define MAILBOX_IRQENABLE_SET_NOTFULLENABLEUUMB6_SHIFT                                                    (13U)
#define MAILBOX_IRQENABLE_SET_NOTFULLENABLEUUMB6_MASK                                                     (0x00002000U)

#define MAILBOX_IRQENABLE_SET_NOTFULLENABLEUUMB7_SHIFT                                                    (15U)
#define MAILBOX_IRQENABLE_SET_NOTFULLENABLEUUMB7_MASK                                                     (0x00008000U)

#define MAILBOX_IRQENABLE_SET_NOTFULLENABLEUUMB2_SHIFT                                                    (5U)
#define MAILBOX_IRQENABLE_SET_NOTFULLENABLEUUMB2_MASK                                                     (0x00000020U)

#define MAILBOX_IRQENABLE_SET_NEWMSGENABLEUUMB7_SHIFT                                                     (14U)
#define MAILBOX_IRQENABLE_SET_NEWMSGENABLEUUMB7_MASK                                                      (0x00004000U)

#define MAILBOX_IRQENABLE_SET_NEWMSGENABLEUUMB2_SHIFT                                                     (4U)
#define MAILBOX_IRQENABLE_SET_NEWMSGENABLEUUMB2_MASK                                                      (0x00000010U)

#define MAILBOX_IRQENABLE_SET_NEWMSGENABLEUUMB6_SHIFT                                                     (12U)
#define MAILBOX_IRQENABLE_SET_NEWMSGENABLEUUMB6_MASK                                                      (0x00001000U)

#define MAILBOX_IRQENABLE_SET_NEWMSGENABLEUUMB5_SHIFT                                                     (10U)
#define MAILBOX_IRQENABLE_SET_NEWMSGENABLEUUMB5_MASK                                                      (0x00000400U)

#define MAILBOX_IRQENABLE_SET_NEWMSGENABLEUUMB1_SHIFT                                                     (2U)
#define MAILBOX_IRQENABLE_SET_NEWMSGENABLEUUMB1_MASK                                                      (0x00000004U)

#define MAILBOX_IRQENABLE_SET_NEWMSGENABLEUUMB3_SHIFT                                                     (6U)
#define MAILBOX_IRQENABLE_SET_NEWMSGENABLEUUMB3_MASK                                                      (0x00000040U)

#define MAILBOX_IRQENABLE_SET_NEWMSGENABLEUUMB4_SHIFT                                                     (8U)
#define MAILBOX_IRQENABLE_SET_NEWMSGENABLEUUMB4_MASK                                                      (0x00000100U)

#define MAILBOX_IRQENABLE_SET_NEWMSGENABLEUUMB0_SHIFT                                                     (0U)
#define MAILBOX_IRQENABLE_SET_NEWMSGENABLEUUMB0_MASK                                                      (0x00000001U)

#define MAILBOX_IRQENABLE_SET_RESERVED_SHIFT                                                              (16U)
#define MAILBOX_IRQENABLE_SET_RESERVED_MASK                                                               (0xffff0000U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_MAILBOX_H_ */
