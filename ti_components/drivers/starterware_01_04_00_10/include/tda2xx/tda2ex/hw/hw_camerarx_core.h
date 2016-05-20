/*
* hw_camerarx_core.h
*
* Register-level header file for CAMERARX_CORE
*
* Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef _HW_CAMERARX_CORE_H_
#define _HW_CAMERARX_CORE_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define REG0                                                        (0x0U)
#define REG1                                                        (0x4U)
#define REG2                                                        (0x8U)
#define REG3                                                        (0xcU)
#define REG4                                                        (0x10U)
#define REG5                                                        (0x14U)
#define REG6                                                        (0x18U)
#define REG7                                                        (0x1cU)
#define REG8                                                        (0x20U)
#define REG9                                                        (0x24U)
#define REG10                                                       (0x28U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define REG0_THS_SETTLE_SHIFT                                                           (0U)
#define REG0_THS_SETTLE_MASK                                                            (0x000000ffU)

#define REG0_THS_TERM_SHIFT                                                             (8U)
#define REG0_THS_TERM_MASK                                                              (0x0000ff00U)

#define REG0_HSCLOCKCONFIG_SHIFT                                                        (24U)
#define REG0_HSCLOCKCONFIG_MASK                                                         (0x01000000U)

#define REG1_TCLK_SETTLE_SHIFT                                                          (0U)
#define REG1_TCLK_SETTLE_MASK                                                           (0x000000ffU)

#define REG1_TCLK_DIV_SHIFT                                                             (8U)
#define REG1_TCLK_DIV_MASK                                                              (0x00000300U)

#define REG1_DPHY_HS_SYNC_PATTERN_SHIFT                                                 (10U)
#define REG1_DPHY_HS_SYNC_PATTERN_MASK                                                  (0x0003fc00U)

#define REG1_TCLK_TERM_SHIFT                                                            (18U)
#define REG1_TCLK_TERM_MASK                                                             (0x01fc0000U)

#define REG1_CLOCK_MISS_DETECTOR_STATUS_SHIFT                                           (25U)
#define REG1_CLOCK_MISS_DETECTOR_STATUS_MASK                                            (0x02000000U)

#define REG1_RESET_DONE_STATUS_SHIFT                                                    (28U)
#define REG1_RESET_DONE_STATUS_MASK                                                     (0x30000000U)

#define REG1_RESET_DONE_STATUS1_SHIFT                                                   (30U)
#define REG1_RESET_DONE_STATUS1_MASK                                                    (0xc0000000U)

#define REG2_CCP2_SYNC_PATTERN_SHIFT                                                    (0U)
#define REG2_CCP2_SYNC_PATTERN_MASK                                                     (0x00ffffffU)

#define REG2_TRIGGER_CMD_RXTRIGESC3_SHIFT                                               (24U)
#define REG2_TRIGGER_CMD_RXTRIGESC3_MASK                                                (0x03000000U)

#define REG2_TRIGGER_CMD_RXTRIGESC2_SHIFT                                               (26U)
#define REG2_TRIGGER_CMD_RXTRIGESC2_MASK                                                (0x0c000000U)

#define REG2_TRIGGER_CMD_RXTRIGESC1_SHIFT                                               (28U)
#define REG2_TRIGGER_CMD_RXTRIGESC1_MASK                                                (0x30000000U)

#define REG2_TRIGGER_CMD_RXTRIGESC0_SHIFT                                               (30U)
#define REG2_TRIGGER_CMD_RXTRIGESC0_MASK                                                (0xc0000000U)

#define REG3_RECALIB_BIAS_CURRENT_SHIFT                                                 (0U)
#define REG3_RECALIB_BIAS_CURRENT_MASK                                                  (0x00000001U)

#define REG3_RECALIB_HSRX_COMP_OFFSET_SHIFT                                             (1U)
#define REG3_RECALIB_HSRX_COMP_OFFSET_MASK                                              (0x00000002U)

#define REG3_ENCCP_OVRRD_HSRX_SHIFT                                                     (3U)
#define REG3_ENCCP_OVRRD_HSRX_MASK                                                      (0x00000008U)

#define REG3_OVERRIDE_ENCCP_SHIFT                                                       (4U)
#define REG3_OVERRIDE_ENCCP_MASK                                                        (0x00000010U)

#define REG3_ENABLE_BIAS_SHIFT                                                          (5U)
#define REG3_ENABLE_BIAS_MASK                                                           (0x00000020U)

#define REG3_BIAS_EN_OVRD_SHIFT                                                         (6U)
#define REG3_BIAS_EN_OVRD_MASK                                                          (0x00000040U)

#define REG3_EN_LDO_SHIFT                                                               (7U)
#define REG3_EN_LDO_MASK                                                                (0x00000080U)

#define REG3_LDO_EN_OVRD_SHIFT                                                          (8U)
#define REG3_LDO_EN_OVRD_MASK                                                           (0x00000100U)

#define REG3_ENULPRX_SHIFT                                                              (9U)
#define REG3_ENULPRX_MASK                                                               (0x00003e00U)

#define REG3_ENLPRX_SHIFT                                                               (14U)
#define REG3_ENLPRX_MASK                                                                (0x0007c000U)

#define REG3_OVRD_LPRXEN_ULPRXEN_SHIFT                                                  (19U)
#define REG3_OVRD_LPRXEN_ULPRXEN_MASK                                                   (0x00080000U)

#define REG3_ENRXTERM_SHIFT                                                             (20U)
#define REG3_ENRXTERM_MASK                                                              (0x01f00000U)

#define REG3_OVRD_HSRXTERM_SHIFT                                                        (25U)
#define REG3_OVRD_HSRXTERM_MASK                                                         (0x02000000U)

#define REG3_ENHSRX_SHIFT                                                               (26U)
#define REG3_ENHSRX_MASK                                                                (0x7c000000U)

#define REG3_OVRD_HSRXEN_SHIFT                                                          (31U)
#define REG3_OVRD_HSRXEN_MASK                                                           (0x80000000U)

#define REG4_BYPASS_EFUSE_TERM_RESA_ALL_SHIFT                                           (0U)
#define REG4_BYPASS_EFUSE_TERM_RESA_ALL_MASK                                            (0x00000001U)

#define REG4_BYPASS_EFUSE_TERM_RES_SHIFT                                                (1U)
#define REG4_BYPASS_EFUSE_TERM_RES_MASK                                                 (0x00000002U)

#define REG4_TRIM_TERM_LANE0_SHIFT                                                      (2U)
#define REG4_TRIM_TERM_LANE0_MASK                                                       (0x0000007cU)

#define REG4_TRIM_TERM_LANE1_SHIFT                                                      (7U)
#define REG4_TRIM_TERM_LANE1_MASK                                                       (0x00000f80U)

#define REG4_TRIM_TERM_LANE2_SHIFT                                                      (12U)
#define REG4_TRIM_TERM_LANE2_MASK                                                       (0x0001f000U)

#define REG4_TRIM_TERM_LANE3_SHIFT                                                      (17U)
#define REG4_TRIM_TERM_LANE3_MASK                                                       (0x003e0000U)

#define REG4_TRIM_TERM_LANE4_SHIFT                                                      (22U)
#define REG4_TRIM_TERM_LANE4_MASK                                                       (0x07c00000U)

#define REG4_TRIM_BIASGEN_CURRENT_SHIFT                                                 (27U)
#define REG4_TRIM_BIASGEN_CURRENT_MASK                                                  (0xf8000000U)

#define REG5_BYPASS_CALIBRATED_OFFSET_SHIFT                                             (1U)
#define REG5_BYPASS_CALIBRATED_OFFSET_MASK                                              (0x00000002U)

#define REG5_TRIMOFFSET_LANE0_HS_RX_SHIFT                                               (2U)
#define REG5_TRIMOFFSET_LANE0_HS_RX_MASK                                                (0x000000fcU)

#define REG5_TRIMOFFSET_LANE1_HS_RX_SHIFT                                               (8U)
#define REG5_TRIMOFFSET_LANE1_HS_RX_MASK                                                (0x00003f00U)

#define REG5_TRIMOFFSET_LANE2_HS_RX_SHIFT                                               (14U)
#define REG5_TRIMOFFSET_LANE2_HS_RX_MASK                                                (0x000fc000U)

#define REG5_TRIMOFFSET_LANE3HS_RX_SHIFT                                                (20U)
#define REG5_TRIMOFFSET_LANE3HS_RX_MASK                                                 (0x03f00000U)

#define REG5_TRIMOFFSET_LANE4HS_RX_SHIFT                                                (26U)
#define REG5_TRIMOFFSET_LANE4HS_RX_MASK                                                 (0xfc000000U)

#define REG6_BIAS_CALIB_OVRD_VAL_SHIFT                                                  (0U)
#define REG6_BIAS_CALIB_OVRD_VAL_MASK                                                   (0x0000001fU)

#define REG6_OVRD_BIASGEN_CALIB_SHIFT                                                   (5U)
#define REG6_OVRD_BIASGEN_CALIB_MASK                                                    (0x00000020U)

#define REG6_BIAS_CRNT_DXA_SHIFT                                                        (7U)
#define REG6_BIAS_CRNT_DXA_MASK                                                         (0x00000080U)

#define REG6_LDO_VLTG_DYA_SHIFT                                                         (8U)
#define REG6_LDO_VLTG_DYA_MASK                                                          (0x00000100U)

#define REG6_BYPASS_LDO_REF_SHIFT                                                       (9U)
#define REG6_BYPASS_LDO_REF_MASK                                                        (0x00000200U)

#define REG6_HSCOMPOUT_FAR_SHIFT                                                        (10U)
#define REG6_HSCOMPOUT_FAR_MASK                                                         (0x00000400U)

#define REG6_SEL_AFE_LANE_POLARITY_SHIFT                                                (11U)
#define REG6_SEL_AFE_LANE_POLARITY_MASK                                                 (0x00000800U)

#define REG6_AFE_LANE_SELECT_SHIFT                                                      (12U)
#define REG6_AFE_LANE_SELECT_MASK                                                       (0x000ff000U)

#define REG6_OVRD_AFE_INPUTS_SHIFT                                                      (20U)
#define REG6_OVRD_AFE_INPUTS_MASK                                                       (0x00100000U)

#define REG6_ENBIASCALIB_EN_OVRD_SHIFT                                                  (21U)
#define REG6_ENBIASCALIB_EN_OVRD_MASK                                                   (0x00200000U)

#define REG6_ENBIASCALIB_EN_SHIFT                                                       (22U)
#define REG6_ENBIASCALIB_EN_MASK                                                        (0x00400000U)

#define REG6_ENCALIB_EN_OVRD_SHIFT                                                      (23U)
#define REG6_ENCALIB_EN_OVRD_MASK                                                       (0x00800000U)

#define REG6_ENCALIB_EN_SHIFT                                                           (24U)
#define REG6_ENCALIB_EN_MASK                                                            (0x01000000U)

#define REG6_LDO_RDY_EN_SHIFT                                                           (25U)
#define REG6_LDO_RDY_EN_MASK                                                            (0x02000000U)

#define REG6_LDO_RDY_EN_OVRD_SHIFT                                                      (26U)
#define REG6_LDO_RDY_EN_OVRD_MASK                                                       (0x04000000U)

#define REG6_BYP_LPSOT_SHIFT                                                            (27U)
#define REG6_BYP_LPSOT_MASK                                                             (0x08000000U)

#define REG6_BYP_HS_SYNC_SHIFT                                                          (28U)
#define REG6_BYP_HS_SYNC_MASK                                                           (0x10000000U)

#define REG6_BGAP_EN_SHIFT                                                              (29U)
#define REG6_BGAP_EN_MASK                                                               (0x20000000U)

#define REG6_BGAP_EN_OVRD_SHIFT                                                         (30U)
#define REG6_BGAP_EN_OVRD_MASK                                                          (0x40000000U)

#define REG7_DIS_HS_TERM_SHIFT                                                          (0U)
#define REG7_DIS_HS_TERM_MASK                                                           (0x0000001fU)

#define REG7_BIAS_COMP_OP_SHIFT                                                         (5U)
#define REG7_BIAS_COMP_OP_MASK                                                          (0x00000020U)

#define REG7_BIAS_COMP_OP_OVRD_SHIFT                                                    (6U)
#define REG7_BIAS_COMP_OP_OVRD_MASK                                                     (0x00000040U)

#define REG7_DUTY_CYC_HSRX_SHIFT                                                        (12U)
#define REG7_DUTY_CYC_HSRX_MASK                                                         (0x00003000U)

#define REG7_BG_MAG_TRIM_BITS_SHIFT                                                     (14U)
#define REG7_BG_MAG_TRIM_BITS_MASK                                                      (0x003fc000U)

#define REG7_BG_MAG_TRIM_BITS_OVRD_SHIFT                                                (22U)
#define REG7_BG_MAG_TRIM_BITS_OVRD_MASK                                                 (0x00400000U)

#define REG7_BG_TRIM_BITS_SHIFT                                                         (23U)
#define REG7_BG_TRIM_BITS_MASK                                                          (0x7f800000U)

#define REG7_BG_TRIM_BITS_OVRD_SHIFT                                                    (31U)
#define REG7_BG_TRIM_BITS_OVRD_MASK                                                     (0x80000000U)

#define REG7_DOUBLER_DIV_SHIFT                                                          (9U)
#define REG7_DOUBLER_DIV_MASK                                                           (0x00000600U)

#define REG7_DOUBLER_EN_SHIFT                                                           (7U)
#define REG7_DOUBLER_EN_MASK                                                            (0x00000080U)

#define REG7_DOUBLER_EN_OVRD_SHIFT                                                      (8U)
#define REG7_DOUBLER_EN_OVRD_MASK                                                       (0x00000100U)

#define REG7_RESERVERED_SHIFT                                                           (11U)
#define REG7_RESERVERED_MASK                                                            (0x00000800U)

#define REG8_PIPD_SHIFT                                                                 (0U)
#define REG8_PIPD_MASK                                                                  (0x00000001U)

#define REG8_PIPD_OVRD_SHIFT                                                            (1U)
#define REG8_PIPD_OVRD_MASK                                                             (0x00000002U)

#define REG8_PIPU_SHIFT                                                                 (2U)
#define REG8_PIPU_MASK                                                                  (0x00000004U)

#define REG8_PIPU_OVRD_SHIFT                                                            (3U)
#define REG8_PIPU_OVRD_MASK                                                             (0x00000008U)

#define REG8_IE_SHIFT                                                                   (4U)
#define REG8_IE_MASK                                                                    (0x00000010U)

#define REG8_IE_OVRD_SHIFT                                                              (5U)
#define REG8_IE_OVRD_MASK                                                               (0x00000020U)

#define REG8_EN_LPBK_SHIFT                                                              (6U)
#define REG8_EN_LPBK_MASK                                                               (0x00000040U)

#define REG8_EN_LPBK_OVRD_SHIFT                                                         (7U)
#define REG8_EN_LPBK_OVRD_MASK                                                          (0x00000080U)

#define REG8_BYP_DX_SHIFT                                                               (8U)
#define REG8_BYP_DX_MASK                                                                (0x00001f00U)

#define REG8_BYP_DY_SHIFT                                                               (13U)
#define REG8_BYP_DY_MASK                                                                (0x0003e000U)

#define REG8_BYP_DX_DY_OVRD_SHIFT                                                       (18U)
#define REG8_BYP_DX_DY_OVRD_MASK                                                        (0x00040000U)

#define REG8_HSCLK_COMPOUT_SHIFT                                                        (19U)
#define REG8_HSCLK_COMPOUT_MASK                                                         (0x00080000U)

#define REG8_HSRXDF_SHIFT                                                               (20U)
#define REG8_HSRXDF_MASK                                                                (0x00f00000U)

#define REG8_HSRXDR_SHIFT                                                               (24U)
#define REG8_HSRXDR_MASK                                                                (0x0f000000U)

#define REG8_HSRX_OVRD_SHIFT                                                            (28U)
#define REG8_HSRX_OVRD_MASK                                                             (0x10000000U)

#define REG8_CCP_LANEA_SHIFT                                                            (29U)
#define REG8_CCP_LANEA_MASK                                                             (0x20000000U)

#define REG8_CCP_LANEB_SHIFT                                                            (30U)
#define REG8_CCP_LANEB_MASK                                                             (0x40000000U)

#define REG8_CCP_OVRD_SHIFT                                                             (31U)
#define REG8_CCP_OVRD_MASK                                                              (0x80000000U)

#define REG9_ULPRXDY_FAR_SHIFT                                                          (10U)
#define REG9_ULPRXDY_FAR_MASK                                                           (0x00000400U)

#define REG9_ULPRXDX_FAR_SHIFT                                                          (11U)
#define REG9_ULPRXDX_FAR_MASK                                                           (0x00000800U)

#define REG9_ULPRXDY_BOT_SHIFT                                                          (12U)
#define REG9_ULPRXDY_BOT_MASK                                                           (0x00001000U)

#define REG9_ULPRXDX_BOT_SHIFT                                                          (13U)
#define REG9_ULPRXDX_BOT_MASK                                                           (0x00002000U)

#define REG9_ULPRXDY_TOP_SHIFT                                                          (14U)
#define REG9_ULPRXDY_TOP_MASK                                                           (0x00004000U)

#define REG9_ULPRXDX_TOP_SHIFT                                                          (15U)
#define REG9_ULPRXDX_TOP_MASK                                                           (0x00008000U)

#define REG9_ULPRXDYB_SHIFT                                                             (16U)
#define REG9_ULPRXDYB_MASK                                                              (0x00010000U)

#define REG9_ULPRXDXB_SHIFT                                                             (17U)
#define REG9_ULPRXDXB_MASK                                                              (0x00020000U)

#define REG9_ULPRXDYA_SHIFT                                                             (18U)
#define REG9_ULPRXDYA_MASK                                                              (0x00040000U)

#define REG9_ULPRXDXA_SHIFT                                                             (19U)
#define REG9_ULPRXDXA_MASK                                                              (0x00080000U)

#define REG9_ULPRX_OVRD_SHIFT                                                           (20U)
#define REG9_ULPRX_OVRD_MASK                                                            (0x00100000U)

#define REG9_LPRXDY_FAR_SHIFT                                                           (21U)
#define REG9_LPRXDY_FAR_MASK                                                            (0x00200000U)

#define REG9_LPRXDX_FAR_SHIFT                                                           (22U)
#define REG9_LPRXDX_FAR_MASK                                                            (0x00400000U)

#define REG9_LPRXDY_BOT_SHIFT                                                           (23U)
#define REG9_LPRXDY_BOT_MASK                                                            (0x00800000U)

#define REG9_LPRXDX_BOT_SHIFT                                                           (24U)
#define REG9_LPRXDX_BOT_MASK                                                            (0x01000000U)

#define REG9_LPRXDY_TOP_SHIFT                                                           (25U)
#define REG9_LPRXDY_TOP_MASK                                                            (0x02000000U)

#define REG9_LPRXDX_TOP_SHIFT                                                           (26U)
#define REG9_LPRXDX_TOP_MASK                                                            (0x04000000U)

#define REG9_LPRXDYB_SHIFT                                                              (27U)
#define REG9_LPRXDYB_MASK                                                               (0x08000000U)

#define REG9_LPRXDXB_SHIFT                                                              (28U)
#define REG9_LPRXDXB_MASK                                                               (0x10000000U)

#define REG9_LPRXDYA_SHIFT                                                              (29U)
#define REG9_LPRXDYA_MASK                                                               (0x20000000U)

#define REG9_LPRXDXA_SHIFT                                                              (30U)
#define REG9_LPRXDXA_MASK                                                               (0x40000000U)

#define REG9_LPRX_OVRD_SHIFT                                                            (31U)
#define REG9_LPRX_OVRD_MASK                                                             (0x80000000U)

#define REG10_SPAREIN_ANATOP_SHIFT                                                      (0U)
#define REG10_SPAREIN_ANATOP_MASK                                                       (0x0000ffffU)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_CAMERARX_CORE_H_ */
