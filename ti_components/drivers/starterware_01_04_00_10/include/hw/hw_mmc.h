/*
* hw_mmc.h
*
* Register-level header file for MMC
*
* Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
*
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

#ifndef HW_MMC_H_
#define HW_MMC_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define MMC_HL_REV                                                                                          (0x0U)
#define MMC_HL_HWINFO                                                                                       (0x4U)
#define MMC_HL_SYSCONFIG                                                                                    (0x10U)
#define MMC_SYSCONFIG                                                                                       (0x110U)
#define MMC_SYSSTATUS                                                                                       (0x114U)
#define MMC_CSRE                                                                                            (0x124U)
#define MMC_SYSTEST                                                                                         (0x128U)
#define MMC_CON                                                                                             (0x12cU)
#define MMC_PWCNT                                                                                           (0x130U)
#define MMC_DLL                                                                                             (0x134U)
#define MMC_SDMASA                                                                                          (0x200U)
#define MMC_BLK                                                                                             (0x204U)
#define MMC_ARG                                                                                             (0x208U)
#define MMC_CMD                                                                                             (0x20cU)
#define MMC_RSP10                                                                                           (0x210U)
#define MMC_RSP32                                                                                           (0x214U)
#define MMC_RSP54                                                                                           (0x218U)
#define MMC_RSP76                                                                                           (0x21cU)
#define MMC_DATA                                                                                            (0x220U)
#define MMC_PSTATE                                                                                          (0x224U)
#define MMC_HCTL                                                                                            (0x228U)
#define MMC_SYSCTL                                                                                          (0x22cU)
#define MMC_STAT                                                                                            (0x230U)
#define MMC_IE                                                                                              (0x234U)
#define MMC_ISE                                                                                             (0x238U)
#define MMC_AC12                                                                                            (0x23cU)
#define MMC_CAPA                                                                                            (0x240U)
#define MMC_CAPA2                                                                                           (0x244U)
#define MMC_CUR_CAPA                                                                                        (0x248U)
#define MMC_FE                                                                                              (0x250U)
#define MMC_ADMAES                                                                                          (0x254U)
#define MMC_ADMASAL                                                                                         (0x258U)
#define MMC_PVINITSD                                                                                        (0x260U)
#define MMC_PVHSSDR12                                                                                       (0x264U)
#define MMC_PVSDR25SDR50                                                                                    (0x268U)
#define MMC_PVSDR104DDR50                                                                                   (0x26cU)
#define MMC_REV                                                                                             (0x2fcU)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define MMC_HL_REV_REVISION_SHIFT                                                                           (0U)
#define MMC_HL_REV_REVISION_MASK                                                                            (0xffffffffU)
#define MMC_HL_REV_REVISION_LEGACY                                                                           (0U)
#define MMC_HL_REV_REVISION_HIGHLANDER                                                                       (1U)

#define MMC_HL_HWINFO_MADMA_EN_SHIFT                                                                        (0U)
#define MMC_HL_HWINFO_MADMA_EN_MASK                                                                         (0x00000001U)
#define MMC_HL_HWINFO_MADMA_EN_NOMASTERDMA                                                                   (0U)
#define MMC_HL_HWINFO_MADMA_EN_SUPPORTADMA                                                                   (1U)

#define MMC_HL_HWINFO_MERGE_MEM_SHIFT                                                                       (1U)
#define MMC_HL_HWINFO_MERGE_MEM_MASK                                                                        (0x00000002U)
#define MMC_HL_HWINFO_MERGE_MEM_TWOMEMBUFFER                                                                 (0U)
#define MMC_HL_HWINFO_MERGE_MEM_SINGLEMEMBUFFER                                                              (1U)

#define MMC_HL_HWINFO_MEM_SIZE_SHIFT                                                                        (2U)
#define MMC_HL_HWINFO_MEM_SIZE_MASK                                                                         (0x0000003cU)
#define MMC_HL_HWINFO_MEM_SIZE_MEM_512                                                                       (1U)
#define MMC_HL_HWINFO_MEM_SIZE_MEM_1024                                                                      (2U)
#define MMC_HL_HWINFO_MEM_SIZE_MEM_2048                                                                      (4U)
#define MMC_HL_HWINFO_MEM_SIZE_MEM_4096                                                                      (8U)

#define MMC_HL_HWINFO_RETMODE_SHIFT                                                                         (6U)
#define MMC_HL_HWINFO_RETMODE_MASK                                                                          (0x00000040U)
#define MMC_HL_HWINFO_RETMODE_RETDISABLED                                                                    (0U)
#define MMC_HL_HWINFO_RETMODE_RETENABLED                                                                     (1U)

#define MMC_HL_HWINFO_RESERVED_SHIFT                                                                        (7U)
#define MMC_HL_HWINFO_RESERVED_MASK                                                                         (0xffffff80U)

#define MMC_HL_SYSCONFIG_SOFTRESET_SHIFT                                                                    (0U)
#define MMC_HL_SYSCONFIG_SOFTRESET_MASK                                                                     (0x00000001U)
#define MMC_HL_SYSCONFIG_SOFTRESET_RESETDONE                                                                 (0U)
#define MMC_HL_SYSCONFIG_SOFTRESET_NOACTION                                                                  (0U)
#define MMC_HL_SYSCONFIG_SOFTRESET_SOFTRESET                                                                 (1U)
#define MMC_HL_SYSCONFIG_SOFTRESET_RESETONGOING                                                              (1U)

#define MMC_HL_SYSCONFIG_FREEEMU_SHIFT                                                                      (1U)
#define MMC_HL_SYSCONFIG_FREEEMU_MASK                                                                       (0x00000002U)
#define MMC_HL_SYSCONFIG_FREEEMU_EMUEN                                                                       (0U)
#define MMC_HL_SYSCONFIG_FREEEMU_EMUDIS                                                                      (1U)

#define MMC_HL_SYSCONFIG_IDLEMODE_SHIFT                                                                     (2U)
#define MMC_HL_SYSCONFIG_IDLEMODE_MASK                                                                      (0x0000000cU)
#define MMC_HL_SYSCONFIG_IDLEMODE_FORCEIDLE                                                                  (0U)
#define MMC_HL_SYSCONFIG_IDLEMODE_NOIDLE                                                                     (1U)
#define MMC_HL_SYSCONFIG_IDLEMODE_SMARTIDLE                                                                  (2U)
#define MMC_HL_SYSCONFIG_IDLEMODE_SMARTIDLEWAKEUP                                                            (3U)

#define MMC_HL_SYSCONFIG_STANDBYMODE_SHIFT                                                                  (4U)
#define MMC_HL_SYSCONFIG_STANDBYMODE_MASK                                                                   (0x00000030U)
#define MMC_HL_SYSCONFIG_STANDBYMODE_SMARTSTANDBYWAKEUP                                                      (3U)
#define MMC_HL_SYSCONFIG_STANDBYMODE_SMARTSTANDBY                                                            (2U)
#define MMC_HL_SYSCONFIG_STANDBYMODE_NOSTANDBY                                                               (1U)
#define MMC_HL_SYSCONFIG_STANDBYMODE_FORCESTANDBY                                                            (0U)

#define MMC_HL_SYSCONFIG_RESERVED_SHIFT                                                                     (6U)
#define MMC_HL_SYSCONFIG_RESERVED_MASK                                                                      (0xffffffc0U)

#define MMC_SYSCONFIG_CLOCKACTIVITY_SHIFT                                                                   (8U)
#define MMC_SYSCONFIG_CLOCKACTIVITY_MASK                                                                    (0x00000300U)
#define MMC_SYSCONFIG_CLOCKACTIVITY_NONE                                                                     (0U)
#define MMC_SYSCONFIG_CLOCKACTIVITY_FUNC                                                                     (2U)
#define MMC_SYSCONFIG_CLOCKACTIVITY_OCP                                                                      (1U)
#define MMC_SYSCONFIG_CLOCKACTIVITY_BOTH                                                                     (3U)

#define MMC_SYSCONFIG_SIDLEMODE_SHIFT                                                                       (3U)
#define MMC_SYSCONFIG_SIDLEMODE_MASK                                                                        (0x00000018U)
#define MMC_SYSCONFIG_SIDLEMODE_SMART                                                                        (2U)
#define MMC_SYSCONFIG_SIDLEMODE_FORCE                                                                        (0U)
#define MMC_SYSCONFIG_SIDLEMODE_NOIDLE                                                                       (1U)
#define MMC_SYSCONFIG_SIDLEMODE_SMARTWAKE                                                                    (3U)

#define MMC_SYSCONFIG_SOFTRESET_SHIFT                                                                       (1U)
#define MMC_SYSCONFIG_SOFTRESET_MASK                                                                        (0x00000002U)
#define MMC_SYSCONFIG_SOFTRESET_NORESET_R                                                                    (0U)
#define MMC_SYSCONFIG_SOFTRESET_ONRESET_R                                                                    (1U)
#define MMC_SYSCONFIG_SOFTRESET_ST_UN_W                                                                      (0U)
#define MMC_SYSCONFIG_SOFTRESET_ST_RST_W                                                                     (1U)

#define MMC_SYSCONFIG_AUTOIDLE_SHIFT                                                                        (0U)
#define MMC_SYSCONFIG_AUTOIDLE_MASK                                                                         (0x00000001U)
#define MMC_SYSCONFIG_AUTOIDLE_OFF                                                                           (0U)
#define MMC_SYSCONFIG_AUTOIDLE_ON                                                                            (1U)

#define MMC_SYSCONFIG_ENAWAKEUP_SHIFT                                                                       (2U)
#define MMC_SYSCONFIG_ENAWAKEUP_MASK                                                                        (0x00000004U)
#define MMC_SYSCONFIG_ENAWAKEUP_DISABLED                                                                     (0U)
#define MMC_SYSCONFIG_ENAWAKEUP_ENABLE                                                                       (1U)

#define MMC_SYSCONFIG_STANDBYMODE_SHIFT                                                                     (12U)
#define MMC_SYSCONFIG_STANDBYMODE_MASK                                                                      (0x00003000U)
#define MMC_SYSCONFIG_STANDBYMODE_NOIDLE                                                                     (1U)
#define MMC_SYSCONFIG_STANDBYMODE_SMART                                                                      (2U)
#define MMC_SYSCONFIG_STANDBYMODE_SMARTWAKE                                                                  (3U)
#define MMC_SYSCONFIG_STANDBYMODE_FORCE                                                                      (0U)

#define MMC_SYSCONFIG_RESERVED_SHIFT                                                                        (5U)
#define MMC_SYSCONFIG_RESERVED_MASK                                                                         (0x000000e0U)

#define MMC_SYSCONFIG_RESERVED1_SHIFT                                                                       (10U)
#define MMC_SYSCONFIG_RESERVED1_MASK                                                                        (0x00000c00U)

#define MMC_SYSCONFIG_RESERVED2_SHIFT                                                                       (14U)
#define MMC_SYSCONFIG_RESERVED2_MASK                                                                        (0xffffc000U)

#define MMC_SYSSTATUS_RESETDONE_SHIFT                                                                       (0U)
#define MMC_SYSSTATUS_RESETDONE_MASK                                                                        (0x00000001U)
#define MMC_SYSSTATUS_RESETDONE_DONE                                                                         (1U)
#define MMC_SYSSTATUS_RESETDONE_ONGOING                                                                      (0U)

#define MMC_SYSSTATUS_RESERVED_SHIFT                                                                        (1U)
#define MMC_SYSSTATUS_RESERVED_MASK                                                                         (0xfffffffeU)

#define MMC_CSRE_CSRE_SHIFT                                                                                 (0U)
#define MMC_CSRE_CSRE_MASK                                                                                  (0xffffffffU)

#define MMC_SYSTEST_WAKD_SHIFT                                                                              (13U)
#define MMC_SYSTEST_WAKD_MASK                                                                               (0x00002000U)
#define MMC_SYSTEST_WAKD_DRIVENHIGH_W                                                                        (1U)
#define MMC_SYSTEST_WAKD_ZERO_R                                                                              (0U)
#define MMC_SYSTEST_WAKD_ONE_R                                                                               (1U)
#define MMC_SYSTEST_WAKD_DRIVENLOW_W                                                                         (0U)

#define MMC_SYSTEST_D4D_SHIFT                                                                               (8U)
#define MMC_SYSTEST_D4D_MASK                                                                                (0x00000100U)
#define MMC_SYSTEST_D4D_DRIVEHIGH_W                                                                          (1U)
#define MMC_SYSTEST_D4D_ZERO_R                                                                               (0U)
#define MMC_SYSTEST_D4D_ONE_R                                                                                (1U)
#define MMC_SYSTEST_D4D_DRIVELOW_W                                                                           (0U)

#define MMC_SYSTEST_CDIR_SHIFT                                                                              (1U)
#define MMC_SYSTEST_CDIR_MASK                                                                               (0x00000002U)
#define MMC_SYSTEST_CDIR_IN_W                                                                                (1U)
#define MMC_SYSTEST_CDIR_ZERO_R                                                                              (0U)
#define MMC_SYSTEST_CDIR_OUT_W                                                                               (0U)
#define MMC_SYSTEST_CDIR_ONE_R                                                                               (1U)

#define MMC_SYSTEST_D1D_SHIFT                                                                               (5U)
#define MMC_SYSTEST_D1D_MASK                                                                                (0x00000020U)
#define MMC_SYSTEST_D1D_DRIVEHIGH_W                                                                          (1U)
#define MMC_SYSTEST_D1D_ONE_R                                                                                (1U)
#define MMC_SYSTEST_D1D_DRIVELOW_W                                                                           (0U)
#define MMC_SYSTEST_D1D_ZERO_R                                                                               (0U)

#define MMC_SYSTEST_SDWP_SHIFT                                                                              (14U)
#define MMC_SYSTEST_SDWP_MASK                                                                               (0x00004000U)
#define MMC_SYSTEST_SDWP_DRIVENHIGH                                                                          (1U)
#define MMC_SYSTEST_SDWP_DRIVENLOW                                                                           (0U)

#define MMC_SYSTEST_D2D_SHIFT                                                                               (6U)
#define MMC_SYSTEST_D2D_MASK                                                                                (0x00000040U)
#define MMC_SYSTEST_D2D_DRIVELOW_W                                                                           (0U)
#define MMC_SYSTEST_D2D_ONE_R                                                                                (1U)
#define MMC_SYSTEST_D2D_ZERO_R                                                                               (0U)
#define MMC_SYSTEST_D2D_DRIVEHIGH_W                                                                          (1U)

#define MMC_SYSTEST_DDIR_SHIFT                                                                              (3U)
#define MMC_SYSTEST_DDIR_MASK                                                                               (0x00000008U)
#define MMC_SYSTEST_DDIR_IN_W                                                                                (1U)
#define MMC_SYSTEST_DDIR_ONE_R                                                                               (1U)
#define MMC_SYSTEST_DDIR_ZERO_R                                                                              (0U)
#define MMC_SYSTEST_DDIR_OUT_W                                                                               (0U)

#define MMC_SYSTEST_CDAT_SHIFT                                                                              (2U)
#define MMC_SYSTEST_CDAT_MASK                                                                               (0x00000004U)
#define MMC_SYSTEST_CDAT_ONE_R                                                                               (1U)
#define MMC_SYSTEST_CDAT_DRIVELOW_W                                                                          (0U)
#define MMC_SYSTEST_CDAT_ZERO_R                                                                              (0U)
#define MMC_SYSTEST_CDAT_DRIVEHIGH_W                                                                         (1U)

#define MMC_SYSTEST_D5D_SHIFT                                                                               (9U)
#define MMC_SYSTEST_D5D_MASK                                                                                (0x00000200U)
#define MMC_SYSTEST_D5D_DRIVELOW_W                                                                           (0U)
#define MMC_SYSTEST_D5D_ZERO_R                                                                               (0U)
#define MMC_SYSTEST_D5D_DRIVEHIGH_W                                                                          (1U)
#define MMC_SYSTEST_D5D_ONE_R                                                                                (1U)

#define MMC_SYSTEST_D6D_SHIFT                                                                               (10U)
#define MMC_SYSTEST_D6D_MASK                                                                                (0x00000400U)
#define MMC_SYSTEST_D6D_DRIVELOW_W                                                                           (0U)
#define MMC_SYSTEST_D6D_ZERO_R                                                                               (0U)
#define MMC_SYSTEST_D6D_DRIVEHIGH_W                                                                          (1U)
#define MMC_SYSTEST_D6D_ONE_R                                                                                (1U)

#define MMC_SYSTEST_SSB_SHIFT                                                                               (12U)
#define MMC_SYSTEST_SSB_MASK                                                                                (0x00001000U)
#define MMC_SYSTEST_SSB_SETTHEMALL_W                                                                         (1U)
#define MMC_SYSTEST_SSB_CLEAR_W                                                                              (0U)
#define MMC_SYSTEST_SSB_ZERO_R                                                                               (0U)
#define MMC_SYSTEST_SSB_ONE_R                                                                                (1U)

#define MMC_SYSTEST_D3D_SHIFT                                                                               (7U)
#define MMC_SYSTEST_D3D_MASK                                                                                (0x00000080U)
#define MMC_SYSTEST_D3D_ONE_R                                                                                (1U)
#define MMC_SYSTEST_D3D_ZERO_R                                                                               (0U)
#define MMC_SYSTEST_D3D_DRIVEHIGH_W                                                                          (1U)
#define MMC_SYSTEST_D3D_DRIVELOW_W                                                                           (0U)

#define MMC_SYSTEST_MCKD_SHIFT                                                                              (0U)
#define MMC_SYSTEST_MCKD_MASK                                                                               (0x00000001U)
#define MMC_SYSTEST_MCKD_DRIVENLOW_W                                                                         (0U)
#define MMC_SYSTEST_MCKD_DRIVENHIGH_W                                                                        (1U)
#define MMC_SYSTEST_MCKD_ONE_R                                                                               (1U)
#define MMC_SYSTEST_MCKD_ZERO_R                                                                              (0U)

#define MMC_SYSTEST_D0D_SHIFT                                                                               (4U)
#define MMC_SYSTEST_D0D_MASK                                                                                (0x00000010U)
#define MMC_SYSTEST_D0D_ONE_R                                                                                (1U)
#define MMC_SYSTEST_D0D_DRIVEHIGH_W                                                                          (1U)
#define MMC_SYSTEST_D0D_ZERO_R                                                                               (0U)
#define MMC_SYSTEST_D0D_ZERO_W                                                                               (0U)

#define MMC_SYSTEST_D7D_SHIFT                                                                               (11U)
#define MMC_SYSTEST_D7D_MASK                                                                                (0x00000800U)
#define MMC_SYSTEST_D7D_ZERO_R                                                                               (0U)
#define MMC_SYSTEST_D7D_DRIVEHIGH_W                                                                          (1U)
#define MMC_SYSTEST_D7D_DRIVELOW_W                                                                           (0U)
#define MMC_SYSTEST_D7D_ONE_R                                                                                (1U)

#define MMC_SYSTEST_SDCD_SHIFT                                                                              (15U)
#define MMC_SYSTEST_SDCD_MASK                                                                               (0x00008000U)
#define MMC_SYSTEST_SDCD_DRIVENHIGH                                                                          (1U)
#define MMC_SYSTEST_SDCD_DRIVENLOW                                                                           (0U)

#define MMC_SYSTEST_OBI_SHIFT                                                                               (16U)
#define MMC_SYSTEST_OBI_MASK                                                                                (0x00010000U)
#define MMC_SYSTEST_OBI_HIGHLEVEL                                                                            (1U)
#define MMC_SYSTEST_OBI_LOWLEVEL                                                                             (0U)

#define MMC_SYSTEST_RESERVED_SHIFT                                                                          (17U)
#define MMC_SYSTEST_RESERVED_MASK                                                                           (0xfffe0000U)

#define MMC_CON_HR_SHIFT                                                                                    (2U)
#define MMC_CON_HR_MASK                                                                                     (0x00000004U)
#define MMC_CON_HR_HOSTRESP                                                                                  (1U)
#define MMC_CON_HR_NOHOSTRESP                                                                                (0U)

#define MMC_CON_WPP_SHIFT                                                                                   (8U)
#define MMC_CON_WPP_MASK                                                                                    (0x00000100U)
#define MMC_CON_WPP_ACTIVEHIGH                                                                               (0U)
#define MMC_CON_WPP_ACTIVELOW                                                                                (1U)

#define MMC_CON_STR_SHIFT                                                                                   (3U)
#define MMC_CON_STR_MASK                                                                                    (0x00000008U)
#define MMC_CON_STR_STREAM                                                                                   (1U)
#define MMC_CON_STR_BLOCK                                                                                    (0U)

#define MMC_CON_OD_SHIFT                                                                                    (0U)
#define MMC_CON_OD_MASK                                                                                     (0x00000001U)
#define MMC_CON_OD_OPENDRAIN                                                                                 (1U)
#define MMC_CON_OD_NOOPENDRAIN                                                                               (0U)

#define MMC_CON_DVAL_SHIFT                                                                                  (9U)
#define MMC_CON_DVAL_MASK                                                                                   (0x00000600U)
#define MMC_CON_DVAL_FILTERLEVEL1                                                                            (1U)
#define MMC_CON_DVAL_FILTERLEVEL2                                                                            (2U)
#define MMC_CON_DVAL_FILTERLEVEL0                                                                            (0U)
#define MMC_CON_DVAL_FILTERLEVEL3                                                                            (3U)

#define MMC_CON_INIT_SHIFT                                                                                  (1U)
#define MMC_CON_INIT_MASK                                                                                   (0x00000002U)
#define MMC_CON_INIT_NOINIT                                                                                  (0U)
#define MMC_CON_INIT_INITSTREAM                                                                              (1U)

#define MMC_CON_MIT_SHIFT                                                                                   (6U)
#define MMC_CON_MIT_MASK                                                                                    (0x00000040U)
#define MMC_CON_MIT_CTO                                                                                      (0U)
#define MMC_CON_MIT_NO_CTO                                                                                   (1U)

#define MMC_CON_CDP_SHIFT                                                                                   (7U)
#define MMC_CON_CDP_MASK                                                                                    (0x00000080U)
#define MMC_CON_CDP_ACTIVEHIGH                                                                               (1U)
#define MMC_CON_CDP_ACTIVELOW                                                                                (0U)

#define MMC_CON_DW8_SHIFT                                                                                   (5U)
#define MMC_CON_DW8_MASK                                                                                    (0x00000020U)
#define MMC_CON_DW8_8BITMODE                                                                                 (1U)
#define MMC_CON_DW8_1_4BITMODE                                                                               (0U)

#define MMC_CON_MODE_SHIFT                                                                                  (4U)
#define MMC_CON_MODE_MASK                                                                                   (0x00000010U)
#define MMC_CON_MODE_SYSTEST                                                                                 (1U)
#define MMC_CON_MODE_FUNC                                                                                    (0U)

#define MMC_CON_CTPL_SHIFT                                                                                  (11U)
#define MMC_CON_CTPL_MASK                                                                                   (0x00000800U)
#define MMC_CON_CTPL_MMC_SD                                                                                  (0U)
#define MMC_CON_CTPL_SDIO                                                                                    (1U)

#define MMC_CON_CEATA_SHIFT                                                                                 (12U)
#define MMC_CON_CEATA_MASK                                                                                  (0x00001000U)
#define MMC_CON_CEATA_NORMALMODE                                                                             (0U)
#define MMC_CON_CEATA_CEATAMODE                                                                              (1U)

#define MMC_CON_OBIP_SHIFT                                                                                  (13U)
#define MMC_CON_OBIP_MASK                                                                                   (0x00002000U)
#define MMC_CON_OBIP_ACTIVEHIGH                                                                              (0U)
#define MMC_CON_OBIP_ACTIVELOW                                                                               (1U)

#define MMC_CON_OBIE_SHIFT                                                                                  (14U)
#define MMC_CON_OBIE_MASK                                                                                   (0x00004000U)
#define MMC_CON_OBIE_OBINTMODE                                                                               (1U)
#define MMC_CON_OBIE_NORMALMODE                                                                              (0U)

#define MMC_CON_PADEN_SHIFT                                                                                 (15U)
#define MMC_CON_PADEN_MASK                                                                                  (0x00008000U)
#define MMC_CON_PADEN_DISABLE                                                                                (0U)
#define MMC_CON_PADEN_ENABLE                                                                                 (1U)

#define MMC_CON_CLKEXTFREE_SHIFT                                                                            (16U)
#define MMC_CON_CLKEXTFREE_MASK                                                                             (0x00010000U)
#define MMC_CON_CLKEXTFREE_AUTOGATING                                                                        (0U)
#define MMC_CON_CLKEXTFREE_FREERUNNING                                                                       (1U)

#define MMC_CON_BOOT_ACK_SHIFT                                                                              (17U)
#define MMC_CON_BOOT_ACK_MASK                                                                               (0x00020000U)
#define MMC_CON_BOOT_ACK_BOOTNOACK                                                                           (0U)
#define MMC_CON_BOOT_ACK_BOOTACK                                                                             (1U)

#define MMC_CON_BOOT_CF0_SHIFT                                                                              (18U)
#define MMC_CON_BOOT_CF0_MASK                                                                               (0x00040000U)
#define MMC_CON_BOOT_CF0_NOCMDFORCE                                                                          (0U)
#define MMC_CON_BOOT_CF0_CMDFORCED                                                                           (1U)
#define MMC_CON_BOOT_CF0_CMDFORCEREQ                                                                         (1U)
#define MMC_CON_BOOT_CF0_CMDRELEASED                                                                         (0U)

#define MMC_CON_DDR_SHIFT                                                                                   (19U)
#define MMC_CON_DDR_MASK                                                                                    (0x00080000U)
#define MMC_CON_DDR_NORMALMODE                                                                               (0U)
#define MMC_CON_DDR_DDRMODE                                                                                  (1U)

#define MMC_CON_DMA_MNS_SHIFT                                                                               (20U)
#define MMC_CON_DMA_MNS_MASK                                                                                (0x00100000U)
#define MMC_CON_DMA_MNS_MASTERDMADIS                                                                         (0U)
#define MMC_CON_DMA_MNS_MASTERDMAEN                                                                          (1U)

#define MMC_CON_SDMA_LNE_SHIFT                                                                              (21U)
#define MMC_CON_SDMA_LNE_MASK                                                                               (0x00200000U)
#define MMC_CON_SDMA_LNE_LATEDEASSERT                                                                        (1U)
#define MMC_CON_SDMA_LNE_EARLYDEASSERT                                                                       (0U)

#define MMC_CON_RESERVED_SHIFT                                                                              (22U)
#define MMC_CON_RESERVED_MASK                                                                               (0xffc00000U)

#define MMC_PWCNT_PWRCNT_SHIFT                                                                              (0U)
#define MMC_PWCNT_PWRCNT_MASK                                                                               (0x0000ffffU)
#define MMC_PWCNT_PWRCNT_65535CYCLES                                                                         (65535U)
#define MMC_PWCNT_PWRCNT_65534CYCLES                                                                         (65534U)
#define MMC_PWCNT_PWRCNT_2CYCLES                                                                             (2U)
#define MMC_PWCNT_PWRCNT_1CYCLES                                                                             (1U)
#define MMC_PWCNT_PWRCNT_NODELAY                                                                             (0U)

#define MMC_PWCNT_RESERVED_SHIFT                                                                            (16U)
#define MMC_PWCNT_RESERVED_MASK                                                                             (0xffff0000U)

#define MMC_DLL_DLL_LOCK_SHIFT                                                                              (0U)
#define MMC_DLL_DLL_LOCK_MASK                                                                               (0x00000001U)
#define MMC_DLL_DLL_LOCK_NOTLOCKED                                                                           (0U)
#define MMC_DLL_DLL_LOCK_LOCKED                                                                              (1U)

#define MMC_DLL_DLL_CALIB_SHIFT                                                                             (1U)
#define MMC_DLL_DLL_CALIB_MASK                                                                              (0x00000002U)
#define MMC_DLL_DLL_CALIB_ENABLED                                                                            (1U)
#define MMC_DLL_DLL_CALIB_DISABLED                                                                           (0U)

#define MMC_DLL_SLAVE_RATIO_SHIFT                                                                           (6U)
#define MMC_DLL_SLAVE_RATIO_MASK                                                                            (0x00000fc0U)
#define MMC_DLL_SLAVE_RATIO_PLUS0                                                                            (0U)
#define MMC_DLL_SLAVE_RATIO_PLUS45                                                                           (2U)
#define MMC_DLL_SLAVE_RATIO_PLUS90                                                                           (4U)
#define MMC_DLL_SLAVE_RATIO_PLUS135                                                                          (6U)
#define MMC_DLL_SLAVE_RATIO_PLUS180                                                                          (8U)
#define MMC_DLL_SLAVE_RATIO_PLUS225                                                                          (10U)
#define MMC_DLL_SLAVE_RATIO_PLUS270                                                                          (12U)
#define MMC_DLL_SLAVE_RATIO_PLUS315                                                                          (14U)
#define MMC_DLL_SLAVE_RATIO_PLUS380                                                                          (16U)
#define MMC_DLL_SLAVE_RATIO_FOURCYCLES                                                                       (63U)

#define MMC_DLL_MAX_LOCK_DIFF_SHIFT                                                                         (22U)
#define MMC_DLL_MAX_LOCK_DIFF_MASK                                                                          (0x3fc00000U)

#define MMC_DLL_LOCK_TIMER_SHIFT                                                                            (30U)
#define MMC_DLL_LOCK_TIMER_MASK                                                                             (0x40000000U)
#define MMC_DLL_LOCK_TIMER_DLL_FAST_MODE                                                                     (0U)
#define MMC_DLL_LOCK_TIMER_OTHER                                                                             (1U)

#define MMC_DLL_FORCE_VALUE_SHIFT                                                                           (12U)
#define MMC_DLL_FORCE_VALUE_MASK                                                                            (0x00001000U)
#define MMC_DLL_FORCE_VALUE_NO_FORCE                                                                         (0U)
#define MMC_DLL_FORCE_VALUE_FORCE                                                                            (1U)

#define MMC_DLL_FORCE_SR_C_SHIFT                                                                            (13U)
#define MMC_DLL_FORCE_SR_C_MASK                                                                             (0x000fe000U)

#define MMC_DLL_FORCE_SR_F_SHIFT                                                                            (20U)
#define MMC_DLL_FORCE_SR_F_MASK                                                                             (0x00300000U)

#define MMC_DLL_DLL_SOFT_RESET_SHIFT                                                                        (31U)
#define MMC_DLL_DLL_SOFT_RESET_MASK                                                                         (0x80000000U)
#define MMC_DLL_DLL_SOFT_RESET_WRITE_1                                                                       (1U)
#define MMC_DLL_DLL_SOFT_RESET_WRITE_0                                                                       (0U)
#define MMC_DLL_DLL_SOFT_RESET_READ_1                                                                        (1U)
#define MMC_DLL_DLL_SOFT_RESET_READ_0                                                                        (0U)

#define MMC_DLL_DLL_UNLOCK_STICKY_SHIFT                                                                     (2U)
#define MMC_DLL_DLL_UNLOCK_STICKY_MASK                                                                      (0x00000004U)

#define MMC_DLL_DLL_UNLOCK_CLEAR_SHIFT                                                                      (3U)
#define MMC_DLL_DLL_UNLOCK_CLEAR_MASK                                                                       (0x00000008U)
#define MMC_DLL_DLL_UNLOCK_CLEAR_1                                                                           (1U)
#define MMC_DLL_DLL_UNLOCK_CLEAR_0                                                                           (0U)

#define MMC_DLL_RESERVED_SHIFT                                                                              (4U)
#define MMC_DLL_RESERVED_MASK                                                                               (0x00000030U)

#define MMC_SDMASA_SDMA_ARG2_SHIFT                                                                          (0U)
#define MMC_SDMASA_SDMA_ARG2_MASK                                                                           (0xffffffffU)

#define MMC_BLK_NBLK_SHIFT                                                                                  (16U)
#define MMC_BLK_NBLK_MASK                                                                                   (0xffff0000U)
#define MMC_BLK_NBLK_1BLK                                                                                    (1U)
#define MMC_BLK_NBLK_2BLKS                                                                                   (2U)
#define MMC_BLK_NBLK_65535BLKS                                                                               (65535U)
#define MMC_BLK_NBLK_STPCNT                                                                                  (0U)

#define MMC_BLK_BLEN_SHIFT                                                                                  (0U)
#define MMC_BLK_BLEN_MASK                                                                                   (0x00000fffU)
#define MMC_BLK_BLEN_1BYTELEN                                                                                (1U)
#define MMC_BLK_BLEN_2048BYTESLEN                                                                            (2048U)
#define MMC_BLK_BLEN_3BYTESLEN                                                                               (3U)
#define MMC_BLK_BLEN_2047BYTESLEN                                                                            (2047U)
#define MMC_BLK_BLEN_2BYTESLEN                                                                               (2U)
#define MMC_BLK_BLEN_511BYTESLEN                                                                             (511U)
#define MMC_BLK_BLEN_512BYTESLEN                                                                             (512U)
#define MMC_BLK_BLEN_NOTRANSFER                                                                              (0U)

#define MMC_BLK_RESERVED_SHIFT                                                                              (12U)
#define MMC_BLK_RESERVED_MASK                                                                               (0x0000f000U)

#define MMC_ARG_ARG_SHIFT                                                                                   (0U)
#define MMC_ARG_ARG_MASK                                                                                    (0xffffffffU)

#define MMC_CMD_RSP_TYPE_SHIFT                                                                              (16U)
#define MMC_CMD_RSP_TYPE_MASK                                                                               (0x00030000U)
#define MMC_CMD_RSP_TYPE_LGHT48B                                                                             (3U)
#define MMC_CMD_RSP_TYPE_NORSP                                                                               (0U)
#define MMC_CMD_RSP_TYPE_LGHT36                                                                              (1U)
#define MMC_CMD_RSP_TYPE_LGHT48                                                                              (2U)

#define MMC_CMD_CCCE_SHIFT                                                                                  (19U)
#define MMC_CMD_CCCE_MASK                                                                                   (0x00080000U)
#define MMC_CMD_CCCE_NOCHECK                                                                                 (0U)
#define MMC_CMD_CCCE_CHECK                                                                                   (1U)

#define MMC_CMD_ACEN_SHIFT                                                                                  (2U)
#define MMC_CMD_ACEN_MASK                                                                                   (0x0000000cU)
#define MMC_CMD_ACEN_DISABLE                                                                                 (0U)
#define MMC_CMD_ACEN_ENABLECMD12                                                                             (1U)
#define MMC_CMD_ACEN_ENABLECMD23                                                                             (2U)
#define MMC_CMD_ACEN_RESERVED                                                                                (3U)

#define MMC_CMD_INDX_SHIFT                                                                                  (24U)
#define MMC_CMD_INDX_MASK                                                                                   (0x3f000000U)
#define MMC_CMD_INDX_CMD0                                                                                    (0U)
#define MMC_CMD_INDX_CMD1                                                                                    (1U)
#define MMC_CMD_INDX_CMD2                                                                                    (2U)
#define MMC_CMD_INDX_CMD3                                                                                    (3U)
#define MMC_CMD_INDX_CMD4                                                                                    (4U)
#define MMC_CMD_INDX_CMD5                                                                                    (5U)
#define MMC_CMD_INDX_CMD6                                                                                    (6U)
#define MMC_CMD_INDX_CMD7                                                                                    (7U)
#define MMC_CMD_INDX_CMD8                                                                                    (8U)
#define MMC_CMD_INDX_CMD9                                                                                    (9U)
#define MMC_CMD_INDX_CMD10                                                                                   (10U)
#define MMC_CMD_INDX_CMD11                                                                                   (11U)
#define MMC_CMD_INDX_CMD12                                                                                   (12U)
#define MMC_CMD_INDX_CMD13                                                                                   (13U)
#define MMC_CMD_INDX_CMD14                                                                                   (14U)
#define MMC_CMD_INDX_CMD15                                                                                   (15U)
#define MMC_CMD_INDX_CMD16                                                                                   (16U)
#define MMC_CMD_INDX_CMD17                                                                                   (17U)
#define MMC_CMD_INDX_CMD18                                                                                   (18U)
#define MMC_CMD_INDX_CMD19                                                                                   (19U)
#define MMC_CMD_INDX_CMD20                                                                                   (20U)
#define MMC_CMD_INDX_CMD21                                                                                   (21U)
#define MMC_CMD_INDX_CMD22                                                                                   (22U)
#define MMC_CMD_INDX_CMD23                                                                                   (23U)
#define MMC_CMD_INDX_CMD24                                                                                   (24U)
#define MMC_CMD_INDX_CMD25                                                                                   (25U)
#define MMC_CMD_INDX_CMD26                                                                                   (26U)
#define MMC_CMD_INDX_CMD27                                                                                   (27U)
#define MMC_CMD_INDX_CMD28                                                                                   (28U)
#define MMC_CMD_INDX_CMD29                                                                                   (29U)
#define MMC_CMD_INDX_CMD30                                                                                   (30U)
#define MMC_CMD_INDX_CMD31                                                                                   (31U)
#define MMC_CMD_INDX_CMD32                                                                                   (32U)
#define MMC_CMD_INDX_CMD33                                                                                   (33U)
#define MMC_CMD_INDX_CMD34                                                                                   (34U)
#define MMC_CMD_INDX_CMD35                                                                                   (35U)
#define MMC_CMD_INDX_CMD36                                                                                   (36U)
#define MMC_CMD_INDX_CMD37                                                                                   (37U)
#define MMC_CMD_INDX_CMD38                                                                                   (38U)
#define MMC_CMD_INDX_CMD39                                                                                   (39U)
#define MMC_CMD_INDX_CMD40                                                                                   (40U)
#define MMC_CMD_INDX_CMD41                                                                                   (41U)
#define MMC_CMD_INDX_CMD42                                                                                   (42U)
#define MMC_CMD_INDX_CMD43                                                                                   (43U)
#define MMC_CMD_INDX_CMD44                                                                                   (44U)
#define MMC_CMD_INDX_CMD45                                                                                   (45U)
#define MMC_CMD_INDX_CMD46                                                                                   (46U)
#define MMC_CMD_INDX_CMD47                                                                                   (47U)
#define MMC_CMD_INDX_CMD48                                                                                   (48U)
#define MMC_CMD_INDX_CMD49                                                                                   (49U)
#define MMC_CMD_INDX_CMD50                                                                                   (50U)
#define MMC_CMD_INDX_CMD51                                                                                   (51U)
#define MMC_CMD_INDX_CMD52                                                                                   (52U)
#define MMC_CMD_INDX_CMD53                                                                                   (53U)
#define MMC_CMD_INDX_CMD54                                                                                   (54U)
#define MMC_CMD_INDX_CMD55                                                                                   (55U)
#define MMC_CMD_INDX_CMD56                                                                                   (56U)
#define MMC_CMD_INDX_CMD57                                                                                   (57U)
#define MMC_CMD_INDX_CMD58                                                                                   (58U)
#define MMC_CMD_INDX_CMD59                                                                                   (59U)
#define MMC_CMD_INDX_CMD60                                                                                   (60U)
#define MMC_CMD_INDX_CMD61                                                                                   (61U)
#define MMC_CMD_INDX_CMD62                                                                                   (62U)
#define MMC_CMD_INDX_CMD63                                                                                   (63U)

#define MMC_CMD_DE_SHIFT                                                                                    (0U)
#define MMC_CMD_DE_MASK                                                                                     (0x00000001U)
#define MMC_CMD_DE_DISABLE                                                                                   (0U)
#define MMC_CMD_DE_ENABLE                                                                                    (1U)

#define MMC_CMD_BCE_SHIFT                                                                                   (1U)
#define MMC_CMD_BCE_MASK                                                                                    (0x00000002U)
#define MMC_CMD_BCE_DISABLE                                                                                  (0U)
#define MMC_CMD_BCE_ENABLE                                                                                   (1U)

#define MMC_CMD_CICE_SHIFT                                                                                  (20U)
#define MMC_CMD_CICE_MASK                                                                                   (0x00100000U)
#define MMC_CMD_CICE_CHECK                                                                                   (1U)
#define MMC_CMD_CICE_NOCHECK                                                                                 (0U)

#define MMC_CMD_MSBS_SHIFT                                                                                  (5U)
#define MMC_CMD_MSBS_MASK                                                                                   (0x00000020U)
#define MMC_CMD_MSBS_MULTIBLK                                                                                (1U)
#define MMC_CMD_MSBS_SGLEBLK                                                                                 (0U)

#define MMC_CMD_CMD_TYPE_SHIFT                                                                              (22U)
#define MMC_CMD_CMD_TYPE_MASK                                                                               (0x00c00000U)
#define MMC_CMD_CMD_TYPE_RESUME                                                                              (2U)
#define MMC_CMD_CMD_TYPE_SUSPEND                                                                             (1U)
#define MMC_CMD_CMD_TYPE_NORMAL                                                                              (0U)
#define MMC_CMD_CMD_TYPE_ABORT                                                                               (3U)

#define MMC_CMD_DP_SHIFT                                                                                    (21U)
#define MMC_CMD_DP_MASK                                                                                     (0x00200000U)
#define MMC_CMD_DP_NODATA                                                                                    (0U)
#define MMC_CMD_DP_DATA                                                                                      (1U)

#define MMC_CMD_DDIR_SHIFT                                                                                  (4U)
#define MMC_CMD_DDIR_MASK                                                                                   (0x00000010U)
#define MMC_CMD_DDIR_READ                                                                                    (1U)
#define MMC_CMD_DDIR_WRITE                                                                                   (0U)

#define MMC_CMD_RESERVED_SHIFT                                                                              (6U)
#define MMC_CMD_RESERVED_MASK                                                                               (0x0000ffc0U)

#define MMC_CMD_RESERVED1_SHIFT                                                                             (18U)
#define MMC_CMD_RESERVED1_MASK                                                                              (0x00040000U)

#define MMC_CMD_RESERVED2_SHIFT                                                                             (30U)
#define MMC_CMD_RESERVED2_MASK                                                                              (0xc0000000U)

#define MMC_RSP10_RSP1_SHIFT                                                                                (16U)
#define MMC_RSP10_RSP1_MASK                                                                                 (0xffff0000U)

#define MMC_RSP10_RSP0_SHIFT                                                                                (0U)
#define MMC_RSP10_RSP0_MASK                                                                                 (0x0000ffffU)

#define MMC_RSP32_RSP3_SHIFT                                                                                (16U)
#define MMC_RSP32_RSP3_MASK                                                                                 (0xffff0000U)

#define MMC_RSP32_RSP2_SHIFT                                                                                (0U)
#define MMC_RSP32_RSP2_MASK                                                                                 (0x0000ffffU)

#define MMC_RSP54_RSP5_SHIFT                                                                                (16U)
#define MMC_RSP54_RSP5_MASK                                                                                 (0xffff0000U)

#define MMC_RSP54_RSP4_SHIFT                                                                                (0U)
#define MMC_RSP54_RSP4_MASK                                                                                 (0x0000ffffU)

#define MMC_RSP76_RSP6_SHIFT                                                                                (0U)
#define MMC_RSP76_RSP6_MASK                                                                                 (0x0000ffffU)

#define MMC_RSP76_RSP7_SHIFT                                                                                (16U)
#define MMC_RSP76_RSP7_MASK                                                                                 (0xffff0000U)

#define MMC_DATA_DATA_SHIFT                                                                                 (0U)
#define MMC_DATA_DATA_MASK                                                                                  (0xffffffffU)

#define MMC_PSTATE_RTA_SHIFT                                                                                (9U)
#define MMC_PSTATE_RTA_MASK                                                                                 (0x00000200U)
#define MMC_PSTATE_RTA_TRANSFER                                                                              (1U)
#define MMC_PSTATE_RTA_NOTRANSFER                                                                            (0U)

#define MMC_PSTATE_WTA_SHIFT                                                                                (8U)
#define MMC_PSTATE_WTA_MASK                                                                                 (0x00000100U)
#define MMC_PSTATE_WTA_NOTRANSFER                                                                            (0U)
#define MMC_PSTATE_WTA_TRANSFER                                                                              (1U)

#define MMC_PSTATE_BRE_SHIFT                                                                                (11U)
#define MMC_PSTATE_BRE_MASK                                                                                 (0x00000800U)
#define MMC_PSTATE_BRE_RDDISABLE                                                                             (0U)
#define MMC_PSTATE_BRE_RDENABLE                                                                              (1U)

#define MMC_PSTATE_CSS_SHIFT                                                                                (17U)
#define MMC_PSTATE_CSS_MASK                                                                                 (0x00020000U)
#define MMC_PSTATE_CSS_STABLE                                                                                (1U)
#define MMC_PSTATE_CSS_DEBOUNCING                                                                            (0U)

#define MMC_PSTATE_DLEV_SHIFT                                                                               (20U)
#define MMC_PSTATE_DLEV_MASK                                                                                (0x00f00000U)

#define MMC_PSTATE_CDPL_SHIFT                                                                               (18U)
#define MMC_PSTATE_CDPL_MASK                                                                                (0x00040000U)
#define MMC_PSTATE_CDPL_ZERO                                                                                 (0U)
#define MMC_PSTATE_CDPL_ONE                                                                                  (1U)

#define MMC_PSTATE_CLEV_SHIFT                                                                               (24U)
#define MMC_PSTATE_CLEV_MASK                                                                                (0x01000000U)
#define MMC_PSTATE_CLEV_ZERO                                                                                 (0U)
#define MMC_PSTATE_CLEV_ONE                                                                                  (1U)

#define MMC_PSTATE_CINS_SHIFT                                                                               (16U)
#define MMC_PSTATE_CINS_MASK                                                                                (0x00010000U)
#define MMC_PSTATE_CINS_ZERO                                                                                 (0U)
#define MMC_PSTATE_CINS_ONE                                                                                  (1U)

#define MMC_PSTATE_DATI_SHIFT                                                                               (1U)
#define MMC_PSTATE_DATI_MASK                                                                                (0x00000002U)
#define MMC_PSTATE_DATI_CMDDIS                                                                               (1U)
#define MMC_PSTATE_DATI_CMDEN                                                                                (0U)

#define MMC_PSTATE_WP_SHIFT                                                                                 (19U)
#define MMC_PSTATE_WP_MASK                                                                                  (0x00080000U)
#define MMC_PSTATE_WP_ONE                                                                                    (1U)
#define MMC_PSTATE_WP_ZERO                                                                                   (0U)

#define MMC_PSTATE_CMDI_SHIFT                                                                               (0U)
#define MMC_PSTATE_CMDI_MASK                                                                                (0x00000001U)
#define MMC_PSTATE_CMDI_CMDDIS                                                                               (1U)
#define MMC_PSTATE_CMDI_CMDEN                                                                                (0U)

#define MMC_PSTATE_DLA_SHIFT                                                                                (2U)
#define MMC_PSTATE_DLA_MASK                                                                                 (0x00000004U)
#define MMC_PSTATE_DLA_ZERO                                                                                  (0U)
#define MMC_PSTATE_DLA_ONE                                                                                   (1U)

#define MMC_PSTATE_BWE_SHIFT                                                                                (10U)
#define MMC_PSTATE_BWE_MASK                                                                                 (0x00000400U)
#define MMC_PSTATE_BWE_WRENABLE                                                                              (1U)
#define MMC_PSTATE_BWE_WRDISABLE                                                                             (0U)

#define MMC_PSTATE_RTR_SHIFT                                                                                (3U)
#define MMC_PSTATE_RTR_MASK                                                                                 (0x00000008U)
#define MMC_PSTATE_RTR_NOTUNING                                                                              (0U)
#define MMC_PSTATE_RTR_TUNING                                                                                (1U)

#define MMC_PSTATE_RESERVED_SHIFT                                                                           (4U)
#define MMC_PSTATE_RESERVED_MASK                                                                            (0x000000f0U)

#define MMC_PSTATE_RESERVED1_SHIFT                                                                          (12U)
#define MMC_PSTATE_RESERVED1_MASK                                                                           (0x0000f000U)

#define MMC_PSTATE_RESERVED2_SHIFT                                                                          (25U)
#define MMC_PSTATE_RESERVED2_MASK                                                                           (0xfe000000U)

#define MMC_HCTL_SDVS_SHIFT                                                                                 (9U)
#define MMC_HCTL_SDVS_MASK                                                                                  (0x00000e00U)
#define MMC_HCTL_SDVS_1V8                                                                                    (5U)
#define MMC_HCTL_SDVS_3V0                                                                                    (6U)
#define MMC_HCTL_SDVS_3V3                                                                                    (7U)

#define MMC_HCTL_LED_SHIFT                                                                                  (0U)
#define MMC_HCTL_LED_MASK                                                                                   (0x00000001U)

#define MMC_HCTL_DTW_SHIFT                                                                                  (1U)
#define MMC_HCTL_DTW_MASK                                                                                   (0x00000002U)
#define MMC_HCTL_DTW_1_BITMODE                                                                               (0U)
#define MMC_HCTL_DTW_4_BITMODE                                                                               (1U)

#define MMC_HCTL_SBGR_SHIFT                                                                                 (16U)
#define MMC_HCTL_SBGR_MASK                                                                                  (0x00010000U)
#define MMC_HCTL_SBGR_TRANSFER                                                                               (0U)
#define MMC_HCTL_SBGR_STPBLK                                                                                 (1U)

#define MMC_HCTL_REM_SHIFT                                                                                  (26U)
#define MMC_HCTL_REM_MASK                                                                                   (0x04000000U)
#define MMC_HCTL_REM_ENABLE                                                                                  (1U)
#define MMC_HCTL_REM_DISABLE                                                                                 (0U)

#define MMC_HCTL_IBG_SHIFT                                                                                  (19U)
#define MMC_HCTL_IBG_MASK                                                                                   (0x00080000U)
#define MMC_HCTL_IBG_ITDIABLE                                                                                (0U)
#define MMC_HCTL_IBG_ITENABLE                                                                                (1U)

#define MMC_HCTL_SDBP_SHIFT                                                                                 (8U)
#define MMC_HCTL_SDBP_MASK                                                                                  (0x00000100U)
#define MMC_HCTL_SDBP_PWROFF                                                                                 (0U)
#define MMC_HCTL_SDBP_PWRON                                                                                  (1U)

#define MMC_HCTL_INS_SHIFT                                                                                  (25U)
#define MMC_HCTL_INS_MASK                                                                                   (0x02000000U)
#define MMC_HCTL_INS_ENABLE                                                                                  (1U)
#define MMC_HCTL_INS_DISABLE                                                                                 (0U)

#define MMC_HCTL_IWE_SHIFT                                                                                  (24U)
#define MMC_HCTL_IWE_MASK                                                                                   (0x01000000U)
#define MMC_HCTL_IWE_ENABLE                                                                                  (1U)
#define MMC_HCTL_IWE_DISABLE                                                                                 (0U)

#define MMC_HCTL_HSPE_SHIFT                                                                                 (2U)
#define MMC_HCTL_HSPE_MASK                                                                                  (0x00000004U)
#define MMC_HCTL_HSPE_NORMALSPEED                                                                            (0U)
#define MMC_HCTL_HSPE_HIGHSPEED                                                                              (1U)

#define MMC_HCTL_CR_SHIFT                                                                                   (17U)
#define MMC_HCTL_CR_MASK                                                                                    (0x00020000U)
#define MMC_HCTL_CR_NONE                                                                                     (0U)
#define MMC_HCTL_CR_RESTART                                                                                  (1U)

#define MMC_HCTL_RWC_SHIFT                                                                                  (18U)
#define MMC_HCTL_RWC_MASK                                                                                   (0x00040000U)
#define MMC_HCTL_RWC_RW                                                                                      (1U)
#define MMC_HCTL_RWC_NORW                                                                                    (0U)

#define MMC_HCTL_OBWE_SHIFT                                                                                 (27U)
#define MMC_HCTL_OBWE_MASK                                                                                  (0x08000000U)
#define MMC_HCTL_OBWE_DISABLE                                                                                (0U)
#define MMC_HCTL_OBWE_ENABLE                                                                                 (1U)

#define MMC_HCTL_DMAS_SHIFT                                                                                 (3U)
#define MMC_HCTL_DMAS_MASK                                                                                  (0x00000018U)
#define MMC_HCTL_DMAS_RESERVED                                                                               (0U)
#define MMC_HCTL_DMAS_RESERVED1                                                                              (1U)
#define MMC_HCTL_DMAS_ADMA2                                                                                  (2U)
#define MMC_HCTL_DMAS_RESERVED2                                                                              (3U)

#define MMC_HCTL_CDTL_SHIFT                                                                                 (6U)
#define MMC_HCTL_CDTL_MASK                                                                                  (0x00000040U)
#define MMC_HCTL_CDTL_NOCARD                                                                                 (0U)
#define MMC_HCTL_CDTL_CARDINS                                                                                (1U)

#define MMC_HCTL_CDSS_SHIFT                                                                                 (7U)
#define MMC_HCTL_CDSS_MASK                                                                                  (0x00000080U)
#define MMC_HCTL_CDSS_SDCDSEL                                                                                (0U)
#define MMC_HCTL_CDSS_CDTLSEL                                                                                (1U)

#define MMC_HCTL_RESERVED_SHIFT                                                                             (5U)
#define MMC_HCTL_RESERVED_MASK                                                                              (0x00000020U)

#define MMC_HCTL_RESERVED1_SHIFT                                                                            (12U)
#define MMC_HCTL_RESERVED1_MASK                                                                             (0x0000f000U)

#define MMC_HCTL_RESERVED2_SHIFT                                                                            (20U)
#define MMC_HCTL_RESERVED2_MASK                                                                             (0x00f00000U)

#define MMC_HCTL_RESERVED3_SHIFT                                                                            (28U)
#define MMC_HCTL_RESERVED3_MASK                                                                             (0xf0000000U)

#define MMC_SYSCTL_ICS_SHIFT                                                                                (1U)
#define MMC_SYSCTL_ICS_MASK                                                                                 (0x00000002U)
#define MMC_SYSCTL_ICS_NOTREADY                                                                              (0U)
#define MMC_SYSCTL_ICS_READY                                                                                 (1U)

#define MMC_SYSCTL_SRA_SHIFT                                                                                (24U)
#define MMC_SYSCTL_SRA_MASK                                                                                 (0x01000000U)
#define MMC_SYSCTL_SRA_WORK                                                                                  (0U)
#define MMC_SYSCTL_SRA_RESET                                                                                 (1U)

#define MMC_SYSCTL_ICE_SHIFT                                                                                (0U)
#define MMC_SYSCTL_ICE_MASK                                                                                 (0x00000001U)
#define MMC_SYSCTL_ICE_OSCILLATE                                                                             (1U)
#define MMC_SYSCTL_ICE_STOP                                                                                  (0U)

#define MMC_SYSCTL_CEN_SHIFT                                                                                (2U)
#define MMC_SYSCTL_CEN_MASK                                                                                 (0x00000004U)
#define MMC_SYSCTL_CEN_ENABLE                                                                                (1U)
#define MMC_SYSCTL_CEN_DISABLE                                                                               (0U)

#define MMC_SYSCTL_CLKD_SHIFT                                                                               (6U)
#define MMC_SYSCTL_CLKD_MASK                                                                                (0x0000ffc0U)
#define MMC_SYSCTL_CLKD_BYPASS1                                                                              (1U)
#define MMC_SYSCTL_CLKD_DIV2                                                                                 (2U)
#define MMC_SYSCTL_CLKD_DIV3                                                                                 (3U)
#define MMC_SYSCTL_CLKD_BYPASS0                                                                              (0U)
#define MMC_SYSCTL_CLKD_DIV1023                                                                              (1023U)

#define MMC_SYSCTL_SRD_SHIFT                                                                                (26U)
#define MMC_SYSCTL_SRD_MASK                                                                                 (0x04000000U)
#define MMC_SYSCTL_SRD_WORK                                                                                  (0U)
#define MMC_SYSCTL_SRD_RESET                                                                                 (1U)

#define MMC_SYSCTL_DTO_SHIFT                                                                                (16U)
#define MMC_SYSCTL_DTO_MASK                                                                                 (0x000f0000U)
#define MMC_SYSCTL_DTO_15THDTO                                                                               (14U)
#define MMC_SYSCTL_DTO_RSVD                                                                                  (15U)
#define MMC_SYSCTL_DTO_1STDTO                                                                                (0U)
#define MMC_SYSCTL_DTO_2NDDTO                                                                                (1U)

#define MMC_SYSCTL_SRC_SHIFT                                                                                (25U)
#define MMC_SYSCTL_SRC_MASK                                                                                 (0x02000000U)
#define MMC_SYSCTL_SRC_WORK                                                                                  (0U)
#define MMC_SYSCTL_SRC_RESET                                                                                 (1U)

#define MMC_SYSCTL_CGS_SHIFT                                                                                (5U)
#define MMC_SYSCTL_CGS_MASK                                                                                 (0x00000020U)

#define MMC_SYSCTL_RESERVED_SHIFT                                                                           (3U)
#define MMC_SYSCTL_RESERVED_MASK                                                                            (0x00000018U)

#define MMC_SYSCTL_RESERVED1_SHIFT                                                                          (20U)
#define MMC_SYSCTL_RESERVED1_MASK                                                                           (0x00f00000U)

#define MMC_SYSCTL_RESERVED2_SHIFT                                                                          (27U)
#define MMC_SYSCTL_RESERVED2_MASK                                                                           (0xf8000000U)

#define MMC_STAT_ERRI_SHIFT                                                                                 (15U)
#define MMC_STAT_ERRI_MASK                                                                                  (0x00008000U)
#define MMC_STAT_ERRI_IRQ_FAL_R                                                                              (0U)
#define MMC_STAT_ERRI_IRQ_TRU_R                                                                              (1U)

#define MMC_STAT_BGE_SHIFT                                                                                  (2U)
#define MMC_STAT_BGE_MASK                                                                                   (0x00000004U)
#define MMC_STAT_BGE_ST_UN_W                                                                                 (0U)
#define MMC_STAT_BGE_IRQ_FAL_R                                                                               (0U)
#define MMC_STAT_BGE_IRQ_TRU_R                                                                               (1U)
#define MMC_STAT_BGE_ST_RST_W                                                                                (1U)

#define MMC_STAT_CERR_SHIFT                                                                                 (28U)
#define MMC_STAT_CERR_MASK                                                                                  (0x10000000U)
#define MMC_STAT_CERR_ST_RST_W                                                                               (1U)
#define MMC_STAT_CERR_IRQ_FAL_R                                                                              (0U)
#define MMC_STAT_CERR_IRQ_TRU_R                                                                              (1U)
#define MMC_STAT_CERR_ST_UN_W                                                                                (0U)

#define MMC_STAT_CIRQ_SHIFT                                                                                 (8U)
#define MMC_STAT_CIRQ_MASK                                                                                  (0x00000100U)
#define MMC_STAT_CIRQ_IRQ_FAL_R                                                                              (0U)
#define MMC_STAT_CIRQ_IRQ_TRU_R                                                                              (1U)

#define MMC_STAT_CREM_SHIFT                                                                                 (7U)
#define MMC_STAT_CREM_MASK                                                                                  (0x00000080U)
#define MMC_STAT_CREM_IRQ_FAL_R                                                                              (0U)
#define MMC_STAT_CREM_ST_UN_W                                                                                (0U)
#define MMC_STAT_CREM_ST_RST_W                                                                               (1U)
#define MMC_STAT_CREM_IRQ_TRU_R                                                                              (1U)

#define MMC_STAT_DEB_SHIFT                                                                                  (22U)
#define MMC_STAT_DEB_MASK                                                                                   (0x00400000U)
#define MMC_STAT_DEB_IRQ_FAL_R                                                                               (0U)
#define MMC_STAT_DEB_IRQ_TRU_R                                                                               (1U)
#define MMC_STAT_DEB_ST_UN_W                                                                                 (0U)
#define MMC_STAT_DEB_ST_RST_W                                                                                (1U)

#define MMC_STAT_CC_SHIFT                                                                                   (0U)
#define MMC_STAT_CC_MASK                                                                                    (0x00000001U)
#define MMC_STAT_CC_IRQ_TRU_R                                                                                (1U)
#define MMC_STAT_CC_ST_RST_W                                                                                 (1U)
#define MMC_STAT_CC_IRQ_FAL_R                                                                                (0U)
#define MMC_STAT_CC_ST_UN_W                                                                                  (0U)

#define MMC_STAT_BWR_SHIFT                                                                                  (4U)
#define MMC_STAT_BWR_MASK                                                                                   (0x00000010U)
#define MMC_STAT_BWR_ST_RST_W                                                                                (1U)
#define MMC_STAT_BWR_IRQ_TRU_R                                                                               (1U)
#define MMC_STAT_BWR_IRQ_FAL_R                                                                               (0U)
#define MMC_STAT_BWR_ST_UN_W                                                                                 (0U)

#define MMC_STAT_ACE_SHIFT                                                                                  (24U)
#define MMC_STAT_ACE_MASK                                                                                   (0x01000000U)
#define MMC_STAT_ACE_IRQ_FAL_R                                                                               (0U)
#define MMC_STAT_ACE_ST_UN_W                                                                                 (0U)
#define MMC_STAT_ACE_ST_RST_W                                                                                (1U)
#define MMC_STAT_ACE_IRQ_TRU_R                                                                               (1U)

#define MMC_STAT_DMA_SHIFT                                                                                  (3U)
#define MMC_STAT_DMA_MASK                                                                                   (0x00000008U)
#define MMC_STAT_DMA_ST_UN_W                                                                                 (0U)
#define MMC_STAT_DMA_IRQ_FAL_R                                                                               (0U)
#define MMC_STAT_DMA_IRQ_TRU_R                                                                               (1U)
#define MMC_STAT_DMA_ST_RST_W                                                                                (1U)

#define MMC_STAT_CTO_SHIFT                                                                                  (16U)
#define MMC_STAT_CTO_MASK                                                                                   (0x00010000U)
#define MMC_STAT_CTO_IRQ_TRU_R                                                                               (1U)
#define MMC_STAT_CTO_IRQ_FAL_R                                                                               (0U)
#define MMC_STAT_CTO_ST_RST_W                                                                                (1U)
#define MMC_STAT_CTO_ST_UN_W                                                                                 (0U)

#define MMC_STAT_DCRC_SHIFT                                                                                 (21U)
#define MMC_STAT_DCRC_MASK                                                                                  (0x00200000U)
#define MMC_STAT_DCRC_ST_RST_W                                                                               (1U)
#define MMC_STAT_DCRC_IRQ_FAL_R                                                                              (0U)
#define MMC_STAT_DCRC_ST_UN_W                                                                                (0U)
#define MMC_STAT_DCRC_IRQ_TRU_R                                                                              (1U)

#define MMC_STAT_CCRC_SHIFT                                                                                 (17U)
#define MMC_STAT_CCRC_MASK                                                                                  (0x00020000U)
#define MMC_STAT_CCRC_IRQ_TRU_R                                                                              (1U)
#define MMC_STAT_CCRC_IRQ_FAL_R                                                                              (0U)
#define MMC_STAT_CCRC_ST_UN_W                                                                                (0U)
#define MMC_STAT_CCRC_ST_RST_W                                                                               (1U)

#define MMC_STAT_TC_SHIFT                                                                                   (1U)
#define MMC_STAT_TC_MASK                                                                                    (0x00000002U)
#define MMC_STAT_TC_IRQ_TRU_R                                                                                (1U)
#define MMC_STAT_TC_ST_RST_W                                                                                 (1U)
#define MMC_STAT_TC_IRQ_FAL_R                                                                                (0U)
#define MMC_STAT_TC_ST_UN_W                                                                                  (0U)

#define MMC_STAT_BRR_SHIFT                                                                                  (5U)
#define MMC_STAT_BRR_MASK                                                                                   (0x00000020U)
#define MMC_STAT_BRR_IRQ_FAL_R                                                                               (0U)
#define MMC_STAT_BRR_ST_RST_W                                                                                (1U)
#define MMC_STAT_BRR_ST_UN_W                                                                                 (0U)
#define MMC_STAT_BRR_IRQ_TRU_R                                                                               (1U)

#define MMC_STAT_CIE_SHIFT                                                                                  (19U)
#define MMC_STAT_CIE_MASK                                                                                   (0x00080000U)
#define MMC_STAT_CIE_ST_UN_W                                                                                 (0U)
#define MMC_STAT_CIE_IRQ_TRU_R                                                                               (1U)
#define MMC_STAT_CIE_ST_RST_W                                                                                (1U)
#define MMC_STAT_CIE_IRQ_FAL_R                                                                               (0U)

#define MMC_STAT_DTO_SHIFT                                                                                  (20U)
#define MMC_STAT_DTO_MASK                                                                                   (0x00100000U)
#define MMC_STAT_DTO_IRQ_FAL_R                                                                               (0U)
#define MMC_STAT_DTO_IRQ_TRU_R                                                                               (1U)
#define MMC_STAT_DTO_ST_UN_W                                                                                 (0U)
#define MMC_STAT_DTO_ST_RST_W                                                                                (1U)

#define MMC_STAT_CINS_SHIFT                                                                                 (6U)
#define MMC_STAT_CINS_MASK                                                                                  (0x00000040U)
#define MMC_STAT_CINS_IRQ_TRU_R                                                                              (1U)
#define MMC_STAT_CINS_IRQ_FAL_R                                                                              (0U)
#define MMC_STAT_CINS_ST_UN_W                                                                                (0U)
#define MMC_STAT_CINS_ST_RST_W                                                                               (1U)

#define MMC_STAT_BADA_SHIFT                                                                                 (29U)
#define MMC_STAT_BADA_MASK                                                                                  (0x20000000U)
#define MMC_STAT_BADA_ST_UN_W                                                                                (0U)
#define MMC_STAT_BADA_ST_RST_W                                                                               (1U)
#define MMC_STAT_BADA_IRQ_FAL_R                                                                              (0U)
#define MMC_STAT_BADA_IRQ_TRU_R                                                                              (1U)

#define MMC_STAT_CEB_SHIFT                                                                                  (18U)
#define MMC_STAT_CEB_MASK                                                                                   (0x00040000U)
#define MMC_STAT_CEB_IRQ_FAL_R                                                                               (0U)
#define MMC_STAT_CEB_IRQ_TRU_R                                                                               (1U)
#define MMC_STAT_CEB_ST_RST_W                                                                                (1U)
#define MMC_STAT_CEB_ST_UN_W                                                                                 (0U)

#define MMC_STAT_OBI_SHIFT                                                                                  (9U)
#define MMC_STAT_OBI_MASK                                                                                   (0x00000200U)
#define MMC_STAT_OBI_ST_UN_W                                                                                 (0U)
#define MMC_STAT_OBI_IRQ_FAL_R                                                                               (0U)
#define MMC_STAT_OBI_ST_RST_W                                                                                (1U)
#define MMC_STAT_OBI_IRQ_TRU_R                                                                               (1U)

#define MMC_STAT_BSR_SHIFT                                                                                  (10U)
#define MMC_STAT_BSR_MASK                                                                                   (0x00000400U)
#define MMC_STAT_BSR_IRQ_TRU_R                                                                               (1U)
#define MMC_STAT_BSR_ST_RST_W                                                                                (1U)
#define MMC_STAT_BSR_IRQ_FAL_R                                                                               (0U)
#define MMC_STAT_BSR_ST_UN_W                                                                                 (0U)

#define MMC_STAT_ADMAE_SHIFT                                                                                (25U)
#define MMC_STAT_ADMAE_MASK                                                                                 (0x02000000U)
#define MMC_STAT_ADMAE_IRQ_TRU_R                                                                             (1U)
#define MMC_STAT_ADMAE_ST_RST_W                                                                              (1U)
#define MMC_STAT_ADMAE_IRQ_FAL_R                                                                             (0U)
#define MMC_STAT_ADMAE_ST_UN_W                                                                               (0U)

#define MMC_STAT_TE_SHIFT                                                                                   (26U)
#define MMC_STAT_TE_MASK                                                                                    (0x04000000U)
#define MMC_STAT_TE_ERROR                                                                                    (1U)
#define MMC_STAT_TE_NOERROR                                                                                  (0U)

#define MMC_STAT_RESERVED_SHIFT                                                                             (11U)
#define MMC_STAT_RESERVED_MASK                                                                              (0x00007800U)

#define MMC_STAT_RESERVED2_SHIFT                                                                            (27U)
#define MMC_STAT_RESERVED2_MASK                                                                             (0x08000000U)

#define MMC_STAT_RESERVED3_SHIFT                                                                            (30U)
#define MMC_STAT_RESERVED3_MASK                                                                             (0xc0000000U)

#define MMC_STAT_RESERVED4_SHIFT                                                                            (23U)
#define MMC_STAT_RESERVED4_MASK                                                                             (0x00800000U)

#define MMC_IE_DCRC_ENABLE_SHIFT                                                                            (21U)
#define MMC_IE_DCRC_ENABLE_MASK                                                                             (0x00200000U)
#define MMC_IE_DCRC_ENABLE_ENABLED                                                                           (1U)
#define MMC_IE_DCRC_ENABLE_MASKED                                                                            (0U)

#define MMC_IE_BWR_ENABLE_SHIFT                                                                             (4U)
#define MMC_IE_BWR_ENABLE_MASK                                                                              (0x00000010U)
#define MMC_IE_BWR_ENABLE_ENABLED                                                                            (1U)
#define MMC_IE_BWR_ENABLE_MASKED                                                                             (0U)

#define MMC_IE_DMA_ENABLE_SHIFT                                                                             (3U)
#define MMC_IE_DMA_ENABLE_MASK                                                                              (0x00000008U)
#define MMC_IE_DMA_ENABLE_MASKED                                                                             (0U)
#define MMC_IE_DMA_ENABLE_ENABLED                                                                            (1U)

#define MMC_IE_TC_ENABLE_SHIFT                                                                              (1U)
#define MMC_IE_TC_ENABLE_MASK                                                                               (0x00000002U)
#define MMC_IE_TC_ENABLE_ENABLED                                                                             (1U)
#define MMC_IE_TC_ENABLE_MASKED                                                                              (0U)

#define MMC_IE_CEB_ENABLE_SHIFT                                                                             (18U)
#define MMC_IE_CEB_ENABLE_MASK                                                                              (0x00040000U)
#define MMC_IE_CEB_ENABLE_MASKED                                                                             (0U)
#define MMC_IE_CEB_ENABLE_ENABLED                                                                            (1U)

#define MMC_IE_BRR_ENABLE_SHIFT                                                                             (5U)
#define MMC_IE_BRR_ENABLE_MASK                                                                              (0x00000020U)
#define MMC_IE_BRR_ENABLE_ENABLED                                                                            (1U)
#define MMC_IE_BRR_ENABLE_MASKED                                                                             (0U)

#define MMC_IE_CERR_ENABLE_SHIFT                                                                            (28U)
#define MMC_IE_CERR_ENABLE_MASK                                                                             (0x10000000U)
#define MMC_IE_CERR_ENABLE_ENABLED                                                                           (1U)
#define MMC_IE_CERR_ENABLE_MASKED                                                                            (0U)

#define MMC_IE_CIRQ_ENABLE_SHIFT                                                                            (8U)
#define MMC_IE_CIRQ_ENABLE_MASK                                                                             (0x00000100U)
#define MMC_IE_CIRQ_ENABLE_MASKED                                                                            (0U)
#define MMC_IE_CIRQ_ENABLE_ENABLED                                                                           (1U)

#define MMC_IE_CC_ENABLE_SHIFT                                                                              (0U)
#define MMC_IE_CC_ENABLE_MASK                                                                               (0x00000001U)
#define MMC_IE_CC_ENABLE_MASKED                                                                              (0U)
#define MMC_IE_CC_ENABLE_ENABLED                                                                             (1U)

#define MMC_IE_CIE_ENABLE_SHIFT                                                                             (19U)
#define MMC_IE_CIE_ENABLE_MASK                                                                              (0x00080000U)
#define MMC_IE_CIE_ENABLE_MASKED                                                                             (0U)
#define MMC_IE_CIE_ENABLE_ENABLED                                                                            (1U)

#define MMC_IE_BADA_ENABLE_SHIFT                                                                            (29U)
#define MMC_IE_BADA_ENABLE_MASK                                                                             (0x20000000U)
#define MMC_IE_BADA_ENABLE_ENABLED                                                                           (1U)
#define MMC_IE_BADA_ENABLE_MASKED                                                                            (0U)

#define MMC_IE_DTO_ENABLE_SHIFT                                                                             (20U)
#define MMC_IE_DTO_ENABLE_MASK                                                                              (0x00100000U)
#define MMC_IE_DTO_ENABLE_ENABLED                                                                            (1U)
#define MMC_IE_DTO_ENABLE_MASKED                                                                             (0U)

#define MMC_IE_CINS_ENABLE_SHIFT                                                                            (6U)
#define MMC_IE_CINS_ENABLE_MASK                                                                             (0x00000040U)
#define MMC_IE_CINS_ENABLE_ENABLED                                                                           (1U)
#define MMC_IE_CINS_ENABLE_MASKED                                                                            (0U)

#define MMC_IE_DEB_ENABLE_SHIFT                                                                             (22U)
#define MMC_IE_DEB_ENABLE_MASK                                                                              (0x00400000U)
#define MMC_IE_DEB_ENABLE_ENABLED                                                                            (1U)
#define MMC_IE_DEB_ENABLE_MASKED                                                                             (0U)

#define MMC_IE_ACE_ENABLE_SHIFT                                                                             (24U)
#define MMC_IE_ACE_ENABLE_MASK                                                                              (0x01000000U)
#define MMC_IE_ACE_ENABLE_MASKED                                                                             (0U)
#define MMC_IE_ACE_ENABLE_ENABLED                                                                            (1U)

#define MMC_IE_BGE_ENABLE_SHIFT                                                                             (2U)
#define MMC_IE_BGE_ENABLE_MASK                                                                              (0x00000004U)
#define MMC_IE_BGE_ENABLE_ENABLED                                                                            (1U)
#define MMC_IE_BGE_ENABLE_MASKED                                                                             (0U)

#define MMC_IE_CCRC_ENABLE_SHIFT                                                                            (17U)
#define MMC_IE_CCRC_ENABLE_MASK                                                                             (0x00020000U)
#define MMC_IE_CCRC_ENABLE_MASKED                                                                            (0U)
#define MMC_IE_CCRC_ENABLE_ENABLED                                                                           (1U)

#define MMC_IE_NULL_SHIFT                                                                                   (15U)
#define MMC_IE_NULL_MASK                                                                                    (0x00008000U)

#define MMC_IE_CREM_ENABLE_SHIFT                                                                            (7U)
#define MMC_IE_CREM_ENABLE_MASK                                                                             (0x00000080U)
#define MMC_IE_CREM_ENABLE_MASKED                                                                            (0U)
#define MMC_IE_CREM_ENABLE_ENABLED                                                                           (1U)

#define MMC_IE_CTO_ENABLE_SHIFT                                                                             (16U)
#define MMC_IE_CTO_ENABLE_MASK                                                                              (0x00010000U)
#define MMC_IE_CTO_ENABLE_ENABLED                                                                            (1U)
#define MMC_IE_CTO_ENABLE_MASKED                                                                             (0U)

#define MMC_IE_OBI_ENABLE_SHIFT                                                                             (9U)
#define MMC_IE_OBI_ENABLE_MASK                                                                              (0x00000200U)
#define MMC_IE_OBI_ENABLE_MASKED                                                                             (0U)
#define MMC_IE_OBI_ENABLE_ENABLED                                                                            (1U)

#define MMC_IE_ADMAE_ENABLE_SHIFT                                                                           (25U)
#define MMC_IE_ADMAE_ENABLE_MASK                                                                            (0x02000000U)
#define MMC_IE_ADMAE_ENABLE_ENABLED                                                                          (1U)
#define MMC_IE_ADMAE_ENABLE_MASKED                                                                           (0U)

#define MMC_IE_BSR_ENABLE_SHIFT                                                                             (10U)
#define MMC_IE_BSR_ENABLE_MASK                                                                              (0x00000400U)
#define MMC_IE_BSR_ENABLE_ENABLED                                                                            (1U)
#define MMC_IE_BSR_ENABLE_MASKED                                                                             (0U)

#define MMC_IE_RESERVED_SHIFT                                                                               (11U)
#define MMC_IE_RESERVED_MASK                                                                                (0x00007800U)

#define MMC_IE_RESERVED2_SHIFT                                                                              (27U)
#define MMC_IE_RESERVED2_MASK                                                                               (0x08000000U)

#define MMC_IE_RESERVED3_SHIFT                                                                              (30U)
#define MMC_IE_RESERVED3_MASK                                                                               (0xc0000000U)

#define MMC_IE_TE_ENABLE_SHIFT                                                                              (26U)
#define MMC_IE_TE_ENABLE_MASK                                                                               (0x04000000U)
#define MMC_IE_TE_ENABLE_MASKED                                                                              (0U)
#define MMC_IE_TE_ENABLE_ENABLED                                                                             (1U)

#define MMC_IE_RESERVED4_SHIFT                                                                              (23U)
#define MMC_IE_RESERVED4_MASK                                                                               (0x00800000U)

#define MMC_ISE_BWR_SIGEN_SHIFT                                                                             (4U)
#define MMC_ISE_BWR_SIGEN_MASK                                                                              (0x00000010U)
#define MMC_ISE_BWR_SIGEN_MASKED                                                                             (0U)
#define MMC_ISE_BWR_SIGEN_ENABLED                                                                            (1U)

#define MMC_ISE_DEB_SIGEN_SHIFT                                                                             (22U)
#define MMC_ISE_DEB_SIGEN_MASK                                                                              (0x00400000U)
#define MMC_ISE_DEB_SIGEN_ENABLED                                                                            (1U)
#define MMC_ISE_DEB_SIGEN_MASKED                                                                             (0U)

#define MMC_ISE_CREM_SIGEN_SHIFT                                                                            (7U)
#define MMC_ISE_CREM_SIGEN_MASK                                                                             (0x00000080U)
#define MMC_ISE_CREM_SIGEN_MASKED                                                                            (0U)
#define MMC_ISE_CREM_SIGEN_ENABLED                                                                           (1U)

#define MMC_ISE_NULL_SHIFT                                                                                  (15U)
#define MMC_ISE_NULL_MASK                                                                                   (0x00008000U)

#define MMC_ISE_CIRQ_SIGEN_SHIFT                                                                            (8U)
#define MMC_ISE_CIRQ_SIGEN_MASK                                                                             (0x00000100U)
#define MMC_ISE_CIRQ_SIGEN_ENABLED                                                                           (1U)
#define MMC_ISE_CIRQ_SIGEN_MASKED                                                                            (0U)

#define MMC_ISE_CCRC_SIGEN_SHIFT                                                                            (17U)
#define MMC_ISE_CCRC_SIGEN_MASK                                                                             (0x00020000U)
#define MMC_ISE_CCRC_SIGEN_MASKED                                                                            (0U)
#define MMC_ISE_CCRC_SIGEN_ENABLED                                                                           (1U)

#define MMC_ISE_ACE_SIGEN_SHIFT                                                                             (24U)
#define MMC_ISE_ACE_SIGEN_MASK                                                                              (0x01000000U)
#define MMC_ISE_ACE_SIGEN_MASKED                                                                             (0U)
#define MMC_ISE_ACE_SIGEN_ENABLED                                                                            (1U)

#define MMC_ISE_BGE_SIGEN_SHIFT                                                                             (2U)
#define MMC_ISE_BGE_SIGEN_MASK                                                                              (0x00000004U)
#define MMC_ISE_BGE_SIGEN_MASKED                                                                             (0U)
#define MMC_ISE_BGE_SIGEN_ENABLED                                                                            (1U)

#define MMC_ISE_CERR_SIGEN_SHIFT                                                                            (28U)
#define MMC_ISE_CERR_SIGEN_MASK                                                                             (0x10000000U)
#define MMC_ISE_CERR_SIGEN_MASKED                                                                            (0U)
#define MMC_ISE_CERR_SIGEN_ENABLED                                                                           (1U)

#define MMC_ISE_CINS_SIGEN_SHIFT                                                                            (6U)
#define MMC_ISE_CINS_SIGEN_MASK                                                                             (0x00000040U)
#define MMC_ISE_CINS_SIGEN_ENABLED                                                                           (1U)
#define MMC_ISE_CINS_SIGEN_MASKED                                                                            (0U)

#define MMC_ISE_RESERVED4_SHIFT                                                                             (23U)
#define MMC_ISE_RESERVED4_MASK                                                                              (0x00800000U)

#define MMC_ISE_CC_SIGEN_SHIFT                                                                              (0U)
#define MMC_ISE_CC_SIGEN_MASK                                                                               (0x00000001U)
#define MMC_ISE_CC_SIGEN_MASKED                                                                              (0U)
#define MMC_ISE_CC_SIGEN_ENABLED                                                                             (1U)

#define MMC_ISE_CTO_SIGEN_SHIFT                                                                             (16U)
#define MMC_ISE_CTO_SIGEN_MASK                                                                              (0x00010000U)
#define MMC_ISE_CTO_SIGEN_ENABLED                                                                            (1U)
#define MMC_ISE_CTO_SIGEN_MASKED                                                                             (0U)

#define MMC_ISE_TC_SIGEN_SHIFT                                                                              (1U)
#define MMC_ISE_TC_SIGEN_MASK                                                                               (0x00000002U)
#define MMC_ISE_TC_SIGEN_MASKED                                                                              (0U)
#define MMC_ISE_TC_SIGEN_ENABLED                                                                             (1U)

#define MMC_ISE_BADA_SIGEN_SHIFT                                                                            (29U)
#define MMC_ISE_BADA_SIGEN_MASK                                                                             (0x20000000U)
#define MMC_ISE_BADA_SIGEN_ENABLED                                                                           (1U)
#define MMC_ISE_BADA_SIGEN_MASKED                                                                            (0U)

#define MMC_ISE_DCRC_SIGEN_SHIFT                                                                            (21U)
#define MMC_ISE_DCRC_SIGEN_MASK                                                                             (0x00200000U)
#define MMC_ISE_DCRC_SIGEN_MASKED                                                                            (0U)
#define MMC_ISE_DCRC_SIGEN_ENABLED                                                                           (1U)

#define MMC_ISE_DTO_SIGEN_SHIFT                                                                             (20U)
#define MMC_ISE_DTO_SIGEN_MASK                                                                              (0x00100000U)
#define MMC_ISE_DTO_SIGEN_ENABLED                                                                            (1U)
#define MMC_ISE_DTO_SIGEN_MASKED                                                                             (0U)

#define MMC_ISE_CIE_SIGEN_SHIFT                                                                             (19U)
#define MMC_ISE_CIE_SIGEN_MASK                                                                              (0x00080000U)
#define MMC_ISE_CIE_SIGEN_MASKED                                                                             (0U)
#define MMC_ISE_CIE_SIGEN_ENABLED                                                                            (1U)

#define MMC_ISE_CEB_SIGEN_SHIFT                                                                             (18U)
#define MMC_ISE_CEB_SIGEN_MASK                                                                              (0x00040000U)
#define MMC_ISE_CEB_SIGEN_MASKED                                                                             (0U)
#define MMC_ISE_CEB_SIGEN_ENABLED                                                                            (1U)

#define MMC_ISE_DMA_SIGEN_SHIFT                                                                             (3U)
#define MMC_ISE_DMA_SIGEN_MASK                                                                              (0x00000008U)
#define MMC_ISE_DMA_SIGEN_ENABLED                                                                            (1U)
#define MMC_ISE_DMA_SIGEN_MASKED                                                                             (0U)

#define MMC_ISE_BRR_SIGEN_SHIFT                                                                             (5U)
#define MMC_ISE_BRR_SIGEN_MASK                                                                              (0x00000020U)
#define MMC_ISE_BRR_SIGEN_MASKED                                                                             (0U)
#define MMC_ISE_BRR_SIGEN_ENABLED                                                                            (1U)

#define MMC_ISE_OBI_SIGEN_SHIFT                                                                             (9U)
#define MMC_ISE_OBI_SIGEN_MASK                                                                              (0x00000200U)
#define MMC_ISE_OBI_SIGEN_MASKED                                                                             (0U)
#define MMC_ISE_OBI_SIGEN_ENABLED                                                                            (1U)

#define MMC_ISE_ADMAE_SIGEN_SHIFT                                                                           (25U)
#define MMC_ISE_ADMAE_SIGEN_MASK                                                                            (0x02000000U)
#define MMC_ISE_ADMAE_SIGEN_ENABLED                                                                          (1U)
#define MMC_ISE_ADMAE_SIGEN_MASKED                                                                           (0U)

#define MMC_ISE_BSR_SIGEN_SHIFT                                                                             (10U)
#define MMC_ISE_BSR_SIGEN_MASK                                                                              (0x00000400U)
#define MMC_ISE_BSR_SIGEN_ENABLED                                                                            (1U)
#define MMC_ISE_BSR_SIGEN_MASKED                                                                             (0U)

#define MMC_ISE_TE_SIGEN_SHIFT                                                                              (26U)
#define MMC_ISE_TE_SIGEN_MASK                                                                               (0x04000000U)
#define MMC_ISE_TE_SIGEN_MASKED                                                                              (0U)
#define MMC_ISE_TE_SIGEN_ENABLED                                                                             (1U)

#define MMC_ISE_RESERVED_SHIFT                                                                              (11U)
#define MMC_ISE_RESERVED_MASK                                                                               (0x00007800U)

#define MMC_ISE_RESERVED2_SHIFT                                                                             (27U)
#define MMC_ISE_RESERVED2_MASK                                                                              (0x08000000U)

#define MMC_ISE_RESERVED3_SHIFT                                                                             (30U)
#define MMC_ISE_RESERVED3_MASK                                                                              (0xc0000000U)

#define MMC_AC12_CNI_SHIFT                                                                                  (7U)
#define MMC_AC12_CNI_MASK                                                                                   (0x00000080U)
#define MMC_AC12_CNI_CMDNI                                                                                   (1U)
#define MMC_AC12_CNI_NOERR                                                                                   (0U)

#define MMC_AC12_ACTO_SHIFT                                                                                 (1U)
#define MMC_AC12_ACTO_MASK                                                                                  (0x00000002U)
#define MMC_AC12_ACTO_TIMEOUT                                                                                (1U)
#define MMC_AC12_ACTO_NOERR                                                                                  (0U)

#define MMC_AC12_ACEB_SHIFT                                                                                 (3U)
#define MMC_AC12_ACEB_MASK                                                                                  (0x00000008U)
#define MMC_AC12_ACEB_ERR                                                                                    (1U)
#define MMC_AC12_ACEB_NOERR                                                                                  (0U)

#define MMC_AC12_ACIE_SHIFT                                                                                 (4U)
#define MMC_AC12_ACIE_MASK                                                                                  (0x00000010U)
#define MMC_AC12_ACIE_NOERR                                                                                  (0U)
#define MMC_AC12_ACIE_ERR                                                                                    (1U)

#define MMC_AC12_ACCE_SHIFT                                                                                 (2U)
#define MMC_AC12_ACCE_MASK                                                                                  (0x00000004U)
#define MMC_AC12_ACCE_NOERR                                                                                  (0U)
#define MMC_AC12_ACCE_ERR                                                                                    (1U)

#define MMC_AC12_ACNE_SHIFT                                                                                 (0U)
#define MMC_AC12_ACNE_MASK                                                                                  (0x00000001U)
#define MMC_AC12_ACNE_EXE                                                                                    (0U)
#define MMC_AC12_ACNE_NOTEXE                                                                                 (1U)

#define MMC_AC12_UHSMS_SHIFT                                                                                (16U)
#define MMC_AC12_UHSMS_MASK                                                                                 (0x00070000U)
#define MMC_AC12_UHSMS_SDR12                                                                                 (0U)
#define MMC_AC12_UHSMS_SDR25                                                                                 (1U)
#define MMC_AC12_UHSMS_SDR50                                                                                 (2U)
#define MMC_AC12_UHSMS_SDR104                                                                                (3U)
#define MMC_AC12_UHSMS_DDR50                                                                                 (4U)
#define MMC_AC12_UHSMS_RESERVED1                                                                             (5U)
#define MMC_AC12_UHSMS_RESERVED2                                                                             (6U)
#define MMC_AC12_UHSMS_RESERVED3                                                                             (7U)

#define MMC_AC12_V1V8_SIGEN_SHIFT                                                                           (19U)
#define MMC_AC12_V1V8_SIGEN_MASK                                                                            (0x00080000U)
#define MMC_AC12_V1V8_SIGEN_1V8                                                                              (1U)
#define MMC_AC12_V1V8_SIGEN_3V3                                                                              (0U)

#define MMC_AC12_DS_SEL_SHIFT                                                                               (20U)
#define MMC_AC12_DS_SEL_MASK                                                                                (0x00300000U)
#define MMC_AC12_DS_SEL_DTB                                                                                  (0U)
#define MMC_AC12_DS_SEL_DTA                                                                                  (1U)
#define MMC_AC12_DS_SEL_DTC                                                                                  (2U)
#define MMC_AC12_DS_SEL_DTD                                                                                  (3U)

#define MMC_AC12_ET_SHIFT                                                                                   (22U)
#define MMC_AC12_ET_MASK                                                                                    (0x00400000U)
#define MMC_AC12_ET_EXECUTE                                                                                  (1U)
#define MMC_AC12_ET_COMPLETED                                                                                (0U)

#define MMC_AC12_SCLK_SEL_SHIFT                                                                             (23U)
#define MMC_AC12_SCLK_SEL_MASK                                                                              (0x00800000U)
#define MMC_AC12_SCLK_SEL_TUNED                                                                              (1U)
#define MMC_AC12_SCLK_SEL_FIXED                                                                              (0U)

#define MMC_AC12_AI_ENABLE_SHIFT                                                                            (30U)
#define MMC_AC12_AI_ENABLE_MASK                                                                             (0x40000000U)
#define MMC_AC12_AI_ENABLE_ENABLED                                                                           (1U)
#define MMC_AC12_AI_ENABLE_DISABLED                                                                          (0U)

#define MMC_AC12_PV_ENABLE_SHIFT                                                                            (31U)
#define MMC_AC12_PV_ENABLE_MASK                                                                             (0x80000000U)
#define MMC_AC12_PV_ENABLE_ENABLED                                                                           (1U)
#define MMC_AC12_PV_ENABLE_DISABLED                                                                          (0U)

#define MMC_AC12_RESERVED_SHIFT                                                                             (5U)
#define MMC_AC12_RESERVED_MASK                                                                              (0x00000060U)

#define MMC_AC12_RESERVED1_SHIFT                                                                            (8U)
#define MMC_AC12_RESERVED1_MASK                                                                             (0x0000ff00U)

#define MMC_AC12_RESERVED2_SHIFT                                                                            (24U)
#define MMC_AC12_RESERVED2_MASK                                                                             (0x3f000000U)

#define MMC_CAPA_HSS_SHIFT                                                                                  (21U)
#define MMC_CAPA_HSS_MASK                                                                                   (0x00200000U)
#define MMC_CAPA_HSS_NOTSUPPORTED                                                                            (0U)
#define MMC_CAPA_HSS_SUPPORTED                                                                               (1U)

#define MMC_CAPA_SRS_SHIFT                                                                                  (23U)
#define MMC_CAPA_SRS_MASK                                                                                   (0x00800000U)
#define MMC_CAPA_SRS_NOTSUPPORTED                                                                            (0U)
#define MMC_CAPA_SRS_SUPPORTED                                                                               (1U)

#define MMC_CAPA_DS_SHIFT                                                                                   (22U)
#define MMC_CAPA_DS_MASK                                                                                    (0x00400000U)
#define MMC_CAPA_DS_NOTSUPPORTED                                                                             (0U)
#define MMC_CAPA_DS_SUPPORTED                                                                                (1U)

#define MMC_CAPA_BCF_SHIFT                                                                                  (8U)
#define MMC_CAPA_BCF_MASK                                                                                   (0x0000ff00U)
#define MMC_CAPA_BCF_OMETH                                                                                   (0U)

#define MMC_CAPA_MBL_SHIFT                                                                                  (16U)
#define MMC_CAPA_MBL_MASK                                                                                   (0x00030000U)
#define MMC_CAPA_MBL_512                                                                                     (0U)
#define MMC_CAPA_MBL_1024                                                                                    (1U)
#define MMC_CAPA_MBL_2048                                                                                    (2U)

#define MMC_CAPA_VS18_SHIFT                                                                                 (26U)
#define MMC_CAPA_VS18_MASK                                                                                  (0x04000000U)
#define MMC_CAPA_VS18_ST_1V8SUP_W                                                                            (1U)
#define MMC_CAPA_VS18_1V8_SUP_R                                                                              (1U)
#define MMC_CAPA_VS18_1V8_NOTSUP_R                                                                           (0U)
#define MMC_CAPA_VS18_ST_1V8NOTSUP_W                                                                         (0U)

#define MMC_CAPA_TCU_SHIFT                                                                                  (7U)
#define MMC_CAPA_TCU_MASK                                                                                   (0x00000080U)
#define MMC_CAPA_TCU_MHZ                                                                                     (0U)
#define MMC_CAPA_TCU_KHZ                                                                                     (1U)

#define MMC_CAPA_VS33_SHIFT                                                                                 (24U)
#define MMC_CAPA_VS33_MASK                                                                                  (0x01000000U)
#define MMC_CAPA_VS33_ST_3V3SUP_W                                                                            (1U)
#define MMC_CAPA_VS33_ST_3V3NOTSUP_W                                                                         (0U)
#define MMC_CAPA_VS33_3V3_SUP_R                                                                              (1U)
#define MMC_CAPA_VS33_3V3_NOTSUP_R                                                                           (0U)

#define MMC_CAPA_VS30_SHIFT                                                                                 (25U)
#define MMC_CAPA_VS30_MASK                                                                                  (0x02000000U)
#define MMC_CAPA_VS30_ST_3V0NOTSUP_W                                                                         (0U)
#define MMC_CAPA_VS30_3V0_NOTSUP_R                                                                           (0U)
#define MMC_CAPA_VS30_3V0_SUP_R                                                                              (1U)
#define MMC_CAPA_VS30_ST_3V0SUP_W                                                                            (1U)

#define MMC_CAPA_TCF_SHIFT                                                                                  (0U)
#define MMC_CAPA_TCF_MASK                                                                                   (0x0000003fU)
#define MMC_CAPA_TCF_OMETH                                                                                   (0U)

#define MMC_CAPA_BIT64_SHIFT                                                                                (28U)
#define MMC_CAPA_BIT64_MASK                                                                                 (0x10000000U)
#define MMC_CAPA_BIT64_SYSADDR32B                                                                            (0U)
#define MMC_CAPA_BIT64_SYSADDR64B                                                                            (1U)

#define MMC_CAPA_AD2S_SHIFT                                                                                 (19U)
#define MMC_CAPA_AD2S_MASK                                                                                  (0x00080000U)
#define MMC_CAPA_AD2S_ADMA2NOTSUPPORTED                                                                      (0U)
#define MMC_CAPA_AD2S_ADMA2SUPPORTED                                                                         (1U)

#define MMC_CAPA_RESERVED_SHIFT                                                                             (6U)
#define MMC_CAPA_RESERVED_MASK                                                                              (0x00000040U)

#define MMC_CAPA_RESERVED1_SHIFT                                                                            (18U)
#define MMC_CAPA_RESERVED1_MASK                                                                             (0x00040000U)

#define MMC_CAPA_RESERVED2_SHIFT                                                                            (20U)
#define MMC_CAPA_RESERVED2_MASK                                                                             (0x00100000U)

#define MMC_CAPA_RESERVED3_SHIFT                                                                            (27U)
#define MMC_CAPA_RESERVED3_MASK                                                                             (0x08000000U)

#define MMC_CAPA_RESERVED4_SHIFT                                                                            (30U)
#define MMC_CAPA_RESERVED4_MASK                                                                             (0xc0000000U)

#define MMC_CAPA_AIS_SHIFT                                                                                  (29U)
#define MMC_CAPA_AIS_MASK                                                                                   (0x20000000U)
#define MMC_CAPA_AIS_AIS_SUP                                                                                 (1U)
#define MMC_CAPA_AIS_AIS_NOTSUP                                                                              (0U)

#define MMC_CAPA2_SDR50_SHIFT                                                                               (0U)
#define MMC_CAPA2_SDR50_MASK                                                                                (0x00000001U)
#define MMC_CAPA2_SDR50_SUPPORTED                                                                            (1U)
#define MMC_CAPA2_SDR50_NOTSUPPORTED                                                                         (0U)

#define MMC_CAPA2_SDR104_SHIFT                                                                              (1U)
#define MMC_CAPA2_SDR104_MASK                                                                               (0x00000002U)
#define MMC_CAPA2_SDR104_SUPPORTED                                                                           (1U)
#define MMC_CAPA2_SDR104_NOTSUPPORTED                                                                        (0U)

#define MMC_CAPA2_DDR50_SHIFT                                                                               (2U)
#define MMC_CAPA2_DDR50_MASK                                                                                (0x00000004U)
#define MMC_CAPA2_DDR50_SUPPORTED                                                                            (1U)
#define MMC_CAPA2_DDR50_NOTSUPPORTED                                                                         (0U)

#define MMC_CAPA2_DTA_SHIFT                                                                                 (4U)
#define MMC_CAPA2_DTA_MASK                                                                                  (0x00000010U)
#define MMC_CAPA2_DTA_SUPPORTED                                                                              (1U)
#define MMC_CAPA2_DTA_NOTSUPPORTED                                                                           (0U)

#define MMC_CAPA2_DTC_SHIFT                                                                                 (5U)
#define MMC_CAPA2_DTC_MASK                                                                                  (0x00000020U)
#define MMC_CAPA2_DTC_SUPPORTED                                                                              (1U)
#define MMC_CAPA2_DTC_NOTSUPPORTED                                                                           (0U)

#define MMC_CAPA2_DTD_SHIFT                                                                                 (6U)
#define MMC_CAPA2_DTD_MASK                                                                                  (0x00000040U)
#define MMC_CAPA2_DTD_SUPPORTED                                                                              (1U)
#define MMC_CAPA2_DTD_NOTSUPPORTED                                                                           (0U)

#define MMC_CAPA2_TCRT_SHIFT                                                                                (8U)
#define MMC_CAPA2_TCRT_MASK                                                                                 (0x00000f00U)
#define MMC_CAPA2_TCRT_DISABLED                                                                              (0U)
#define MMC_CAPA2_TCRT_1                                                                                     (1U)
#define MMC_CAPA2_TCRT_2                                                                                     (2U)
#define MMC_CAPA2_TCRT_3                                                                                     (3U)
#define MMC_CAPA2_TCRT_4                                                                                     (4U)
#define MMC_CAPA2_TCRT_5                                                                                     (5U)
#define MMC_CAPA2_TCRT_6                                                                                     (6U)
#define MMC_CAPA2_TCRT_7                                                                                     (7U)
#define MMC_CAPA2_TCRT_8                                                                                     (8U)
#define MMC_CAPA2_TCRT_9                                                                                     (9U)
#define MMC_CAPA2_TCRT_10                                                                                    (10U)
#define MMC_CAPA2_TCRT_11                                                                                    (11U)
#define MMC_CAPA2_TCRT_RESERVED1                                                                             (12U)
#define MMC_CAPA2_TCRT_RESERVED2                                                                             (13U)
#define MMC_CAPA2_TCRT_RESERVED3                                                                             (14U)
#define MMC_CAPA2_TCRT_OTHERSOURCE                                                                           (15U)

#define MMC_CAPA2_TSDR50_SHIFT                                                                              (13U)
#define MMC_CAPA2_TSDR50_MASK                                                                               (0x00002000U)
#define MMC_CAPA2_TSDR50_REQUIRED                                                                            (1U)
#define MMC_CAPA2_TSDR50_NOTREQUIRED                                                                         (0U)

#define MMC_CAPA2_RTM_SHIFT                                                                                 (14U)
#define MMC_CAPA2_RTM_MASK                                                                                  (0x0000c000U)
#define MMC_CAPA2_RTM_MODE1                                                                                  (0U)
#define MMC_CAPA2_RTM_MODE2                                                                                  (1U)
#define MMC_CAPA2_RTM_MODE3                                                                                  (2U)
#define MMC_CAPA2_RTM_RESERVED                                                                               (3U)

#define MMC_CAPA2_CM_SHIFT                                                                                  (16U)
#define MMC_CAPA2_CM_MASK                                                                                   (0x00ff0000U)

#define MMC_CAPA2_RESERVED_SHIFT                                                                            (3U)
#define MMC_CAPA2_RESERVED_MASK                                                                             (0x00000008U)

#define MMC_CAPA2_RESERVED1_SHIFT                                                                           (7U)
#define MMC_CAPA2_RESERVED1_MASK                                                                            (0x00000080U)

#define MMC_CAPA2_RESERVED2_SHIFT                                                                           (12U)
#define MMC_CAPA2_RESERVED2_MASK                                                                            (0x00001000U)

#define MMC_CAPA2_RESERVED3_SHIFT                                                                           (24U)
#define MMC_CAPA2_RESERVED3_MASK                                                                            (0xff000000U)

#define MMC_CUR_CAPA_CUR_3V3_SHIFT                                                                          (0U)
#define MMC_CUR_CAPA_CUR_3V3_MASK                                                                           (0x000000ffU)
#define MMC_CUR_CAPA_CUR_3V3_OMETH                                                                           (0U)

#define MMC_CUR_CAPA_CUR_1V8_SHIFT                                                                          (16U)
#define MMC_CUR_CAPA_CUR_1V8_MASK                                                                           (0x00ff0000U)
#define MMC_CUR_CAPA_CUR_1V8_OMETH                                                                           (0U)

#define MMC_CUR_CAPA_CUR_3V0_SHIFT                                                                          (8U)
#define MMC_CUR_CAPA_CUR_3V0_MASK                                                                           (0x0000ff00U)
#define MMC_CUR_CAPA_CUR_3V0_OMETH                                                                           (0U)

#define MMC_CUR_CAPA_RESERVED_SHIFT                                                                         (24U)
#define MMC_CUR_CAPA_RESERVED_MASK                                                                          (0xff000000U)

#define MMC_FE_FE_CEB_SHIFT                                                                                 (18U)
#define MMC_FE_FE_CEB_MASK                                                                                  (0x00040000U)
#define MMC_FE_FE_CEB_NOACTION                                                                               (0U)
#define MMC_FE_FE_CEB_INTFORCED                                                                              (1U)

#define MMC_FE_FE_CTO_SHIFT                                                                                 (16U)
#define MMC_FE_FE_CTO_MASK                                                                                  (0x00010000U)
#define MMC_FE_FE_CTO_ST_UN_W                                                                                (0U)
#define MMC_FE_FE_CTO_ST_RST_W                                                                               (1U)

#define MMC_FE_FE_DCRC_SHIFT                                                                                (21U)
#define MMC_FE_FE_DCRC_MASK                                                                                 (0x00200000U)
#define MMC_FE_FE_DCRC_INTFORCED                                                                             (1U)
#define MMC_FE_FE_DCRC_NOACTION                                                                              (0U)

#define MMC_FE_FE_BADA_SHIFT                                                                                (29U)
#define MMC_FE_FE_BADA_MASK                                                                                 (0x20000000U)
#define MMC_FE_FE_BADA_NOACTION                                                                              (0U)
#define MMC_FE_FE_BADA_INTFORCED                                                                             (1U)

#define MMC_FE_FE_CCRC_SHIFT                                                                                (17U)
#define MMC_FE_FE_CCRC_MASK                                                                                 (0x00020000U)
#define MMC_FE_FE_CCRC_INTFORCED                                                                             (1U)
#define MMC_FE_FE_CCRC_NOACTION                                                                              (0U)

#define MMC_FE_FE_ACE_SHIFT                                                                                 (24U)
#define MMC_FE_FE_ACE_MASK                                                                                  (0x01000000U)
#define MMC_FE_FE_ACE_INTFORCED                                                                              (1U)
#define MMC_FE_FE_ACE_NOACTION                                                                               (0U)

#define MMC_FE_FE_DEB_SHIFT                                                                                 (22U)
#define MMC_FE_FE_DEB_MASK                                                                                  (0x00400000U)
#define MMC_FE_FE_DEB_NOACTION                                                                               (0U)
#define MMC_FE_FE_DEB_INTFORCED                                                                              (1U)

#define MMC_FE_FE_CIE_SHIFT                                                                                 (19U)
#define MMC_FE_FE_CIE_MASK                                                                                  (0x00080000U)
#define MMC_FE_FE_CIE_INTFORCED                                                                              (1U)
#define MMC_FE_FE_CIE_NOACTION                                                                               (0U)

#define MMC_FE_FE_DTO_SHIFT                                                                                 (20U)
#define MMC_FE_FE_DTO_MASK                                                                                  (0x00100000U)
#define MMC_FE_FE_DTO_NOACTION                                                                               (0U)
#define MMC_FE_FE_DTO_INTFORCED                                                                              (1U)

#define MMC_FE_FE_CERR_SHIFT                                                                                (28U)
#define MMC_FE_FE_CERR_MASK                                                                                 (0x10000000U)
#define MMC_FE_FE_CERR_INTFORCED                                                                             (1U)
#define MMC_FE_FE_CERR_NOACTION                                                                              (0U)

#define MMC_FE_RESERVED4_SHIFT                                                                              (23U)
#define MMC_FE_RESERVED4_MASK                                                                               (0x00800000U)

#define MMC_FE_FE_ADMAE_SHIFT                                                                               (25U)
#define MMC_FE_FE_ADMAE_MASK                                                                                (0x02000000U)
#define MMC_FE_FE_ADMAE_NOACTION                                                                             (0U)
#define MMC_FE_FE_ADMAE_INTFORCED                                                                            (1U)

#define MMC_FE_FE_ACNE_SHIFT                                                                                (0U)
#define MMC_FE_FE_ACNE_MASK                                                                                 (0x00000001U)
#define MMC_FE_FE_ACNE_INTFORCED                                                                             (1U)
#define MMC_FE_FE_ACNE_NOACTION                                                                              (0U)

#define MMC_FE_FE_ACCE_SHIFT                                                                                (2U)
#define MMC_FE_FE_ACCE_MASK                                                                                 (0x00000004U)
#define MMC_FE_FE_ACCE_INTFORCED                                                                             (1U)
#define MMC_FE_FE_ACCE_NOACTION                                                                              (0U)

#define MMC_FE_FE_ACIE_SHIFT                                                                                (4U)
#define MMC_FE_FE_ACIE_MASK                                                                                 (0x00000010U)
#define MMC_FE_FE_ACIE_INTFORCED                                                                             (1U)
#define MMC_FE_FE_ACIE_NOACTION                                                                              (0U)

#define MMC_FE_FE_ACEB_SHIFT                                                                                (3U)
#define MMC_FE_FE_ACEB_MASK                                                                                 (0x00000008U)
#define MMC_FE_FE_ACEB_NOACTION                                                                              (0U)
#define MMC_FE_FE_ACEB_INTFORCED                                                                             (1U)

#define MMC_FE_FE_ACTO_SHIFT                                                                                (1U)
#define MMC_FE_FE_ACTO_MASK                                                                                 (0x00000002U)
#define MMC_FE_FE_ACTO_NOACTION                                                                              (0U)
#define MMC_FE_FE_ACTO_INTFORCED                                                                             (1U)

#define MMC_FE_FE_CNI_SHIFT                                                                                 (7U)
#define MMC_FE_FE_CNI_MASK                                                                                  (0x00000080U)
#define MMC_FE_FE_CNI_NOACTION                                                                               (0U)
#define MMC_FE_FE_CNI_INTFORCED                                                                              (1U)

#define MMC_FE_RESERVED_SHIFT                                                                               (5U)
#define MMC_FE_RESERVED_MASK                                                                                (0x00000060U)

#define MMC_FE_RESERVED1_SHIFT                                                                              (8U)
#define MMC_FE_RESERVED1_MASK                                                                               (0x0000ff00U)

#define MMC_FE_RESERVED2_SHIFT                                                                              (26U)
#define MMC_FE_RESERVED2_MASK                                                                               (0x0c000000U)

#define MMC_FE_RESERVED3_SHIFT                                                                              (30U)
#define MMC_FE_RESERVED3_MASK                                                                               (0xc0000000U)

#define MMC_ADMAES_LME_SHIFT                                                                                (2U)
#define MMC_ADMAES_LME_MASK                                                                                 (0x00000004U)
#define MMC_ADMAES_LME_NOERROR                                                                               (0U)
#define MMC_ADMAES_LME_ERROR                                                                                 (1U)

#define MMC_ADMAES_AES_SHIFT                                                                                (0U)
#define MMC_ADMAES_AES_MASK                                                                                 (0x00000003U)
#define MMC_ADMAES_AES_SYSSDR                                                                                (0U)
#define MMC_ADMAES_AES_LINKDESC                                                                              (1U)
#define MMC_ADMAES_AES_RESERVED                                                                              (2U)
#define MMC_ADMAES_AES_TRANSDATA                                                                             (3U)

#define MMC_ADMAES_RESERVED_SHIFT                                                                           (3U)
#define MMC_ADMAES_RESERVED_MASK                                                                            (0xfffffff8U)

#define MMC_ADMASAL_ADMA_A32B_SHIFT                                                                         (0U)
#define MMC_ADMASAL_ADMA_A32B_MASK                                                                          (0xffffffffU)

#define MMC_PVINITSD_INITSDCLK_SEL_SHIFT                                                                    (0U)
#define MMC_PVINITSD_INITSDCLK_SEL_MASK                                                                     (0x000003ffU)

#define MMC_PVINITSD_INITCLKGEN_SEL_SHIFT                                                                   (10U)
#define MMC_PVINITSD_INITCLKGEN_SEL_MASK                                                                    (0x00000400U)
#define MMC_PVINITSD_INITCLKGEN_SEL_PROG                                                                     (1U)
#define MMC_PVINITSD_INITCLKGEN_SEL_HOST                                                                     (0U)

#define MMC_PVINITSD_INITDS_SEL_SHIFT                                                                       (14U)
#define MMC_PVINITSD_INITDS_SEL_MASK                                                                        (0x0000c000U)
#define MMC_PVINITSD_INITDS_SEL_DTD                                                                          (3U)
#define MMC_PVINITSD_INITDS_SEL_DTC                                                                          (2U)
#define MMC_PVINITSD_INITDS_SEL_DTA                                                                          (1U)
#define MMC_PVINITSD_INITDS_SEL_DTB                                                                          (0U)

#define MMC_PVINITSD_DSSDCLK_SEL_SHIFT                                                                      (16U)
#define MMC_PVINITSD_DSSDCLK_SEL_MASK                                                                       (0x03ff0000U)

#define MMC_PVINITSD_DSCLKGEN_SEL_SHIFT                                                                     (26U)
#define MMC_PVINITSD_DSCLKGEN_SEL_MASK                                                                      (0x04000000U)
#define MMC_PVINITSD_DSCLKGEN_SEL_PROG                                                                       (1U)
#define MMC_PVINITSD_DSCLKGEN_SEL_HOST                                                                       (0U)

#define MMC_PVINITSD_DSDS_SEL_SHIFT                                                                         (30U)
#define MMC_PVINITSD_DSDS_SEL_MASK                                                                          (0xc0000000U)
#define MMC_PVINITSD_DSDS_SEL_DTD                                                                            (3U)
#define MMC_PVINITSD_DSDS_SEL_DTC                                                                            (2U)
#define MMC_PVINITSD_DSDS_SEL_DTA                                                                            (1U)
#define MMC_PVINITSD_DSDS_SEL_DTB                                                                            (0U)

#define MMC_PVINITSD_RESERVED_SHIFT                                                                         (11U)
#define MMC_PVINITSD_RESERVED_MASK                                                                          (0x00003800U)

#define MMC_PVINITSD_RESERVED1_SHIFT                                                                        (27U)
#define MMC_PVINITSD_RESERVED1_MASK                                                                         (0x38000000U)

#define MMC_PVHSSDR12_HSSDCLK_SEL_SHIFT                                                                     (0U)
#define MMC_PVHSSDR12_HSSDCLK_SEL_MASK                                                                      (0x000003ffU)

#define MMC_PVHSSDR12_HSCLKGEN_SEL_SHIFT                                                                    (10U)
#define MMC_PVHSSDR12_HSCLKGEN_SEL_MASK                                                                     (0x00000400U)
#define MMC_PVHSSDR12_HSCLKGEN_SEL_PROG                                                                      (1U)
#define MMC_PVHSSDR12_HSCLKGEN_SEL_HOST                                                                      (0U)

#define MMC_PVHSSDR12_HSDS_SEL_SHIFT                                                                        (14U)
#define MMC_PVHSSDR12_HSDS_SEL_MASK                                                                         (0x0000c000U)
#define MMC_PVHSSDR12_HSDS_SEL_DTB                                                                           (0U)
#define MMC_PVHSSDR12_HSDS_SEL_DTA                                                                           (1U)
#define MMC_PVHSSDR12_HSDS_SEL_DTC                                                                           (2U)
#define MMC_PVHSSDR12_HSDS_SEL_DTD                                                                           (3U)

#define MMC_PVHSSDR12_SDR12SDCLK_SEL_SHIFT                                                                  (16U)
#define MMC_PVHSSDR12_SDR12SDCLK_SEL_MASK                                                                   (0x03ff0000U)

#define MMC_PVHSSDR12_SDR12CLKGEN_SEL_SHIFT                                                                 (26U)
#define MMC_PVHSSDR12_SDR12CLKGEN_SEL_MASK                                                                  (0x04000000U)
#define MMC_PVHSSDR12_SDR12CLKGEN_SEL_PROG                                                                   (1U)
#define MMC_PVHSSDR12_SDR12CLKGEN_SEL_HOST                                                                   (0U)

#define MMC_PVHSSDR12_SDR12DS_SEL_SHIFT                                                                     (30U)
#define MMC_PVHSSDR12_SDR12DS_SEL_MASK                                                                      (0xc0000000U)
#define MMC_PVHSSDR12_SDR12DS_SEL_DTD                                                                        (3U)
#define MMC_PVHSSDR12_SDR12DS_SEL_DTC                                                                        (2U)
#define MMC_PVHSSDR12_SDR12DS_SEL_DTA                                                                        (1U)
#define MMC_PVHSSDR12_SDR12DS_SEL_DTB                                                                        (0U)

#define MMC_PVHSSDR12_RESERVED_SHIFT                                                                        (11U)
#define MMC_PVHSSDR12_RESERVED_MASK                                                                         (0x00003800U)

#define MMC_PVHSSDR12_RESERVED1_SHIFT                                                                       (27U)
#define MMC_PVHSSDR12_RESERVED1_MASK                                                                        (0x38000000U)

#define MMC_PVSDR25SDR50_SDR25SDCLK_SEL_SHIFT                                                               (0U)
#define MMC_PVSDR25SDR50_SDR25SDCLK_SEL_MASK                                                                (0x000003ffU)

#define MMC_PVSDR25SDR50_SDR25CLKGEN_SEL_SHIFT                                                              (10U)
#define MMC_PVSDR25SDR50_SDR25CLKGEN_SEL_MASK                                                               (0x00000400U)
#define MMC_PVSDR25SDR50_SDR25CLKGEN_SEL_PROG                                                                (1U)
#define MMC_PVSDR25SDR50_SDR25CLKGEN_SEL_HOST                                                                (0U)

#define MMC_PVSDR25SDR50_SDR25DS_SEL_SHIFT                                                                  (14U)
#define MMC_PVSDR25SDR50_SDR25DS_SEL_MASK                                                                   (0x0000c000U)
#define MMC_PVSDR25SDR50_SDR25DS_SEL_DTD                                                                     (3U)
#define MMC_PVSDR25SDR50_SDR25DS_SEL_DTC                                                                     (2U)
#define MMC_PVSDR25SDR50_SDR25DS_SEL_DTA                                                                     (1U)
#define MMC_PVSDR25SDR50_SDR25DS_SEL_DTB                                                                     (0U)

#define MMC_PVSDR25SDR50_SDR50SDCLK_SEL_SHIFT                                                               (16U)
#define MMC_PVSDR25SDR50_SDR50SDCLK_SEL_MASK                                                                (0x03ff0000U)

#define MMC_PVSDR25SDR50_SDR50CLKGEN_SEL_SHIFT                                                              (26U)
#define MMC_PVSDR25SDR50_SDR50CLKGEN_SEL_MASK                                                               (0x04000000U)
#define MMC_PVSDR25SDR50_SDR50CLKGEN_SEL_PROG                                                                (1U)
#define MMC_PVSDR25SDR50_SDR50CLKGEN_SEL_HOST                                                                (0U)

#define MMC_PVSDR25SDR50_SDR50DS_SEL_SHIFT                                                                  (30U)
#define MMC_PVSDR25SDR50_SDR50DS_SEL_MASK                                                                   (0xc0000000U)
#define MMC_PVSDR25SDR50_SDR50DS_SEL_DTD                                                                     (3U)
#define MMC_PVSDR25SDR50_SDR50DS_SEL_DTC                                                                     (2U)
#define MMC_PVSDR25SDR50_SDR50DS_SEL_DTA                                                                     (1U)
#define MMC_PVSDR25SDR50_SDR50DS_SEL_DTB                                                                     (0U)

#define MMC_PVSDR25SDR50_RESERVED_SHIFT                                                                     (11U)
#define MMC_PVSDR25SDR50_RESERVED_MASK                                                                      (0x00003800U)

#define MMC_PVSDR25SDR50_RESERVED1_SHIFT                                                                    (27U)
#define MMC_PVSDR25SDR50_RESERVED1_MASK                                                                     (0x38000000U)

#define MMC_PVSDR104DDR50_SDR104SDCLK_SEL_SHIFT                                                             (0U)
#define MMC_PVSDR104DDR50_SDR104SDCLK_SEL_MASK                                                              (0x000003ffU)

#define MMC_PVSDR104DDR50_SDR104CLKGEN_SEL_SHIFT                                                            (10U)
#define MMC_PVSDR104DDR50_SDR104CLKGEN_SEL_MASK                                                             (0x00000400U)
#define MMC_PVSDR104DDR50_SDR104CLKGEN_SEL_PROG                                                              (1U)
#define MMC_PVSDR104DDR50_SDR104CLKGEN_SEL_HOST                                                              (0U)

#define MMC_PVSDR104DDR50_SDR104DS_SEL_SHIFT                                                                (14U)
#define MMC_PVSDR104DDR50_SDR104DS_SEL_MASK                                                                 (0x0000c000U)
#define MMC_PVSDR104DDR50_SDR104DS_SEL_DTD                                                                   (3U)
#define MMC_PVSDR104DDR50_SDR104DS_SEL_DTC                                                                   (2U)
#define MMC_PVSDR104DDR50_SDR104DS_SEL_DTA                                                                   (1U)
#define MMC_PVSDR104DDR50_SDR104DS_SEL_DTB                                                                   (0U)

#define MMC_PVSDR104DDR50_DDR50SDCLK_SEL_SHIFT                                                              (16U)
#define MMC_PVSDR104DDR50_DDR50SDCLK_SEL_MASK                                                               (0x03ff0000U)

#define MMC_PVSDR104DDR50_DDR50CLKGEN_SEL_SHIFT                                                             (26U)
#define MMC_PVSDR104DDR50_DDR50CLKGEN_SEL_MASK                                                              (0x04000000U)
#define MMC_PVSDR104DDR50_DDR50CLKGEN_SEL_PROG                                                               (1U)
#define MMC_PVSDR104DDR50_DDR50CLKGEN_SEL_HOST                                                               (0U)

#define MMC_PVSDR104DDR50_DDR50DS_SEL_SHIFT                                                                 (30U)
#define MMC_PVSDR104DDR50_DDR50DS_SEL_MASK                                                                  (0xc0000000U)
#define MMC_PVSDR104DDR50_DDR50DS_SEL_DTD                                                                    (3U)
#define MMC_PVSDR104DDR50_DDR50DS_SEL_DTC                                                                    (2U)
#define MMC_PVSDR104DDR50_DDR50DS_SEL_DTA                                                                    (1U)
#define MMC_PVSDR104DDR50_DDR50DS_SEL_DTB                                                                    (0U)

#define MMC_PVSDR104DDR50_RESERVED_SHIFT                                                                    (11U)
#define MMC_PVSDR104DDR50_RESERVED_MASK                                                                     (0x00003800U)

#define MMC_PVSDR104DDR50_RESERVED1_SHIFT                                                                   (27U)
#define MMC_PVSDR104DDR50_RESERVED1_MASK                                                                    (0x38000000U)

#define MMC_REV_VREV_SHIFT                                                                                  (24U)
#define MMC_REV_VREV_MASK                                                                                   (0xff000000U)

#define MMC_REV_SIS_SHIFT                                                                                   (0U)
#define MMC_REV_SIS_MASK                                                                                    (0x00000001U)

#define MMC_REV_SREV_SHIFT                                                                                  (16U)
#define MMC_REV_SREV_MASK                                                                                   (0x00ff0000U)
#define MMC_REV_SREV_VER1                                                                                    (0U)
#define MMC_REV_SREV_VER2                                                                                    (1U)
#define MMC_REV_SREV_VER3                                                                                    (2U)
#define MMC_REV_SREV_OTHER                                                                                   (3U)

#define MMC_REV_RESERVED_SHIFT                                                                              (1U)
#define MMC_REV_RESERVED_MASK                                                                               (0x0000fffeU)

#ifdef __cplusplus
}
#endif
#endif  /* HW_MMC_H_ */

