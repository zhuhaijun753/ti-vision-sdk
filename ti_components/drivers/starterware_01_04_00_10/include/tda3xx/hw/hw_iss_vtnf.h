/*
* hw_iss_vtnf.h
*
* Register-level header file for ISS_VTNF
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

#ifndef HW_ISS_VTNF_H_
#define HW_ISS_VTNF_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define VTNF_REVISION                                               (0x0U)
#define VTNF_CTRL                                                   (0x4U)
#define VTNF_CFG                                                    (0x8U)
#define VTNF_SZ                                                     (0xcU)
#define VTNF_CADR                                                   (0x10U)
#define VTNF_PADR                                                   (0x14U)
#define VTNF_OADR                                                   (0x18U)
#define VTNF_LOFST                                                  (0x1cU)
#define VTNF_WEIGHTS                                                (0x20U)
#define VTNF_LUT1_0                                                 (0x24U)
#define VTNF_LUT1_4                                                 (0x28U)
#define VTNF_LUT1_8                                                 (0x2cU)
#define VTNF_LUT1_12                                                (0x30U)
#define VTNF_LUT1_16                                                (0x34U)
#define VTNF_LUT1_20                                                (0x38U)
#define VTNF_LUT1_24                                                (0x3cU)
#define VTNF_LUT1_28                                                (0x40U)
#define VTNF_LUT2_0                                                 (0x44U)
#define VTNF_LUT2_4                                                 (0x48U)
#define VTNF_LUT2_8                                                 (0x4cU)
#define VTNF_LUT2_12                                                (0x50U)
#define VTNF_LUT2_16                                                (0x54U)
#define VTNF_LUT2_20                                                (0x58U)
#define VTNF_LUT2_24                                                (0x5cU)
#define VTNF_LUT2_28                                                (0x60U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define VTNF_REVISION_REV_SHIFT                                                         (0U)
#define VTNF_REVISION_REV_MASK                                                          (0x000000ffU)

#define VTNF_REVISION_RESERVED_SHIFT                                                    (8U)
#define VTNF_REVISION_RESERVED_MASK                                                     (0xffffff00U)

#define VTNF_CTRL_EN_SHIFT                                                              (0U)
#define VTNF_CTRL_EN_MASK                                                               (0x00000001U)

#define VTNF_CTRL_BUSY_SHIFT                                                            (16U)
#define VTNF_CTRL_BUSY_MASK                                                             (0x00010000U)

#define VTNF_CTRL_RESERVED2_SHIFT                                                       (17U)
#define VTNF_CTRL_RESERVED2_MASK                                                        (0xfffe0000U)

#define VTNF_CTRL_RESERVED_SHIFT                                                        (1U)
#define VTNF_CTRL_RESERVED_MASK                                                         (0x000000feU)

#define VTNF_CTRL_INTEN_SHIFT                                                           (8U)
#define VTNF_CTRL_INTEN_MASK                                                            (0x00000100U)

#define VTNF_CTRL_TRIG_SRC_SHIFT                                                        (9U)
#define VTNF_CTRL_TRIG_SRC_MASK                                                         (0x00000200U)

#define VTNF_CTRL_AUTOGATING_SHIFT                                                      (10U)
#define VTNF_CTRL_AUTOGATING_MASK                                                       (0x00000400U)

#define VTNF_CTRL_RESERVED1_SHIFT                                                       (11U)
#define VTNF_CTRL_RESERVED1_MASK                                                        (0x0000f800U)

#define VTNF_CFG_FMT_SHIFT                                                              (0U)
#define VTNF_CFG_FMT_MASK                                                               (0x00000001U)

#define VTNF_CFG_T_SHIFT                                                                (4U)
#define VTNF_CFG_T_MASK                                                                 (0x000000f0U)

#define VTNF_CFG_RESERVED_SHIFT                                                         (1U)
#define VTNF_CFG_RESERVED_MASK                                                          (0x0000000eU)

#define VTNF_CFG_RESERVED1_SHIFT                                                        (8U)
#define VTNF_CFG_RESERVED1_MASK                                                         (0xffffff00U)

#define VTNF_SZ_BLKW_SHIFT                                                              (0U)
#define VTNF_SZ_BLKW_MASK                                                               (0x0000ffffU)

#define VTNF_SZ_BLKH_SHIFT                                                              (16U)
#define VTNF_SZ_BLKH_MASK                                                               (0xffff0000U)

#define VTNF_CADR_ADDR_SHIFT                                                            (4U)
#define VTNF_CADR_ADDR_MASK                                                             (0x0000fff0U)

#define VTNF_CADR_RESERVED1_SHIFT                                                       (0U)
#define VTNF_CADR_RESERVED1_MASK                                                        (0x0000000fU)

#define VTNF_CADR_RESERVED_SHIFT                                                        (16U)
#define VTNF_CADR_RESERVED_MASK                                                         (0xffff0000U)

#define VTNF_PADR_ADDR_SHIFT                                                            (4U)
#define VTNF_PADR_ADDR_MASK                                                             (0x0000fff0U)

#define VTNF_PADR_RESERVED1_SHIFT                                                       (0U)
#define VTNF_PADR_RESERVED1_MASK                                                        (0x0000000fU)

#define VTNF_PADR_RESERVED_SHIFT                                                        (16U)
#define VTNF_PADR_RESERVED_MASK                                                         (0xffff0000U)

#define VTNF_OADR_ADDR_SHIFT                                                            (4U)
#define VTNF_OADR_ADDR_MASK                                                             (0x0000fff0U)

#define VTNF_OADR_RESERVED1_SHIFT                                                       (0U)
#define VTNF_OADR_RESERVED1_MASK                                                        (0x0000000fU)

#define VTNF_OADR_RESERVED_SHIFT                                                        (16U)
#define VTNF_OADR_RESERVED_MASK                                                         (0xffff0000U)

#define VTNF_LOFST_SHIFT                                                                (4U)
#define VTNF_LOFST_MASK                                                                 (0x0000fff0U)

#define VTNF_LOFST_RESERVED_SHIFT                                                       (0U)
#define VTNF_LOFST_RESERVED_MASK                                                        (0x0000000fU)

#define VTNF_LOFST_RESERVED1_SHIFT                                                      (16U)
#define VTNF_LOFST_RESERVED1_MASK                                                       (0xffff0000U)

#define VTNF_WEIGHTS_W1_SHIFT                                                           (0U)
#define VTNF_WEIGHTS_W1_MASK                                                            (0x0000003fU)

#define VTNF_WEIGHTS_W2_SHIFT                                                           (16U)
#define VTNF_WEIGHTS_W2_MASK                                                            (0x003f0000U)

#define VTNF_WEIGHTS_RESERVED_SHIFT                                                     (6U)
#define VTNF_WEIGHTS_RESERVED_MASK                                                      (0x0000ffc0U)

#define VTNF_WEIGHTS_RESERVED1_SHIFT                                                    (22U)
#define VTNF_WEIGHTS_RESERVED1_MASK                                                     (0xffc00000U)

#define VTNF_LUT1_0_LUT1_SHIFT(n)                                                       ((n) * 8U)
#define VTNF_LUT1_0_LUT1_MASK(n)                                                        (255U << ((n) * 8U))

#define VTNF_LUT1_4_LUT1_SHIFT(n)                                                       ((n) * 8U)
#define VTNF_LUT1_4_LUT1_MASK(n)                                                        (255U << ((n) * 8U))

#define VTNF_LUT1_8_LUT1_SHIFT(n)                                                       ((n) * 8U)
#define VTNF_LUT1_8_LUT1_MASK(n)                                                        (255U << ((n) * 8U))

#define VTNF_LUT1_12_LUT1_1_SHIFT(n)                                                    ((n) * 8U)
#define VTNF_LUT1_12_LUT1_1_MASK(n)                                                     (255U << ((n) * 8U))

#define VTNF_LUT1_16_LUT1_1_SHIFT(n)                                                    ((n) * 8U)
#define VTNF_LUT1_16_LUT1_1_MASK(n)                                                     (255U << ((n) * 8U))

#define VTNF_LUT1_20_LUT1_2_SHIFT(n)                                                    ((n) * 8U)
#define VTNF_LUT1_20_LUT1_2_MASK(n)                                                     (255U << ((n) * 8U))

#define VTNF_LUT1_24_LUT1_2_SHIFT(n)                                                    ((n) * 8U)
#define VTNF_LUT1_24_LUT1_2_MASK(n)                                                     (255U << ((n) * 8U))

#define VTNF_LUT1_28_LUT1_2_SHIFT(n)                                                    ((n) * 8U)
#define VTNF_LUT1_28_LUT1_2_MASK(n)                                                     (255U << ((n) * 8U))

#define VTNF_LUT2_0_LUT2_SHIFT(n)                                                       ((n) * 8U)
#define VTNF_LUT2_0_LUT2_MASK(n)                                                        (255U << ((n) * 8U))

#define VTNF_LUT2_4_LUT2_SHIFT(n)                                                       ((n) * 8U)
#define VTNF_LUT2_4_LUT2_MASK(n)                                                        (255U << ((n) * 8U))

#define VTNF_LUT2_8_LUT2_SHIFT(n)                                                       ((n) * 8U)
#define VTNF_LUT2_8_LUT2_MASK(n)                                                        (255U << ((n) * 8U))

#define VTNF_LUT2_12_LUT2_1_SHIFT(n)                                                    ((n) * 8U)
#define VTNF_LUT2_12_LUT2_1_MASK(n)                                                     (255U << ((n) * 8U))

#define VTNF_LUT2_16_LUT2_1_SHIFT(n)                                                    ((n) * 8U)
#define VTNF_LUT2_16_LUT2_1_MASK(n)                                                     (255U << ((n) * 8U))

#define VTNF_LUT2_20_LUT2_2_SHIFT(n)                                                    ((n) * 8U)
#define VTNF_LUT2_20_LUT2_2_MASK(n)                                                     (255U << ((n) * 8U))

#define VTNF_LUT2_24_LUT2_2_SHIFT(n)                                                    ((n) * 8U)
#define VTNF_LUT2_24_LUT2_2_MASK(n)                                                     (255U << ((n) * 8U))

#define VTNF_LUT2_28_LUT2_2_SHIFT(n)                                                    ((n) * 8U)
#define VTNF_LUT2_28_LUT2_2_MASK(n)                                                     (255U << ((n) * 8U))

#ifdef __cplusplus
}
#endif
#endif  /* HW_ISS_VTNF_H_ */

