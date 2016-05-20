/******************************************************************************
*
* hw_ctrl_wkup_pad.h - register-level header file for CTRL_WKUP
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
#ifndef HW_CTRL_WKUP_PAD_H_
#define HW_CTRL_WKUP_PAD_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define CTRL_WKUP_CONTROL_XTAL_OSCILLATOR                                                                  (0x4U)
#define CTRL_WKUP_CONTROL_CKOBUFFER                                                                        (0xcU)
#define CTRL_WKUP_EFUSE_1                                                                                  (0x20U)
#define CTRL_WKUP_EFUSE_2                                                                                  (0x24U)
#define CTRL_WKUP_EFUSE_3                                                                                  (0x28U)
#define CTRL_WKUP_EFUSE_4                                                                                  (0x2cU)
#define CTRL_WKUP_EFUSE_13                                                                                 (0x50U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define CTRL_WKUP_CONTROL_XTAL_OSCILLATOR_OSCILLATOR0_BOOST_SHIFT                                         (31U)
#define CTRL_WKUP_CONTROL_XTAL_OSCILLATOR_OSCILLATOR0_BOOST_MASK                                          (0x80000000U)
#define CTRL_WKUP_CONTROL_XTAL_OSCILLATOR_OSCILLATOR0_BOOST_ENABLE                                        (1U)
#define CTRL_WKUP_CONTROL_XTAL_OSCILLATOR_OSCILLATOR0_BOOST_DISABLE                                       (0U)

#define CTRL_WKUP_CONTROL_XTAL_OSCILLATOR_OSCILLATOR0_OS_OUT_SHIFT                                        (30U)
#define CTRL_WKUP_CONTROL_XTAL_OSCILLATOR_OSCILLATOR0_OS_OUT_MASK                                         (0x40000000U)
#define CTRL_WKUP_CONTROL_XTAL_OSCILLATOR_OSCILLATOR0_OS_OUT_DISABLE                                      (1U)
#define CTRL_WKUP_CONTROL_XTAL_OSCILLATOR_OSCILLATOR0_OS_OUT_ENABLE                                       (0U)

#define CTRL_WKUP_CONTROL_XTAL_OSCILLATOR_OSCILLATOR1_BOOST_SHIFT                                         (29U)
#define CTRL_WKUP_CONTROL_XTAL_OSCILLATOR_OSCILLATOR1_BOOST_MASK                                          (0x20000000U)
#define CTRL_WKUP_CONTROL_XTAL_OSCILLATOR_OSCILLATOR1_BOOST_ENABLE                                        (1U)
#define CTRL_WKUP_CONTROL_XTAL_OSCILLATOR_OSCILLATOR1_BOOST_DISABLE                                       (0U)

#define CTRL_WKUP_CONTROL_XTAL_OSCILLATOR_OSCILLATOR1_OS_OUT_SHIFT                                        (28U)
#define CTRL_WKUP_CONTROL_XTAL_OSCILLATOR_OSCILLATOR1_OS_OUT_MASK                                         (0x10000000U)
#define CTRL_WKUP_CONTROL_XTAL_OSCILLATOR_OSCILLATOR1_OS_OUT_DISABLE                                      (1U)
#define CTRL_WKUP_CONTROL_XTAL_OSCILLATOR_OSCILLATOR1_OS_OUT_ENABLE                                       (0U)

#define CTRL_WKUP_CONTROL_XTAL_OSCILLATOR_RESERVED_0_SHIFT                                                (0U)
#define CTRL_WKUP_CONTROL_XTAL_OSCILLATOR_RESERVED_0_MASK                                                 (0x0fffffffU)

#define CTRL_WKUP_CONTROL_CKOBUFFER_CKOBUFFER_OUT_EN_SHIFT                                                (31U)
#define CTRL_WKUP_CONTROL_CKOBUFFER_CKOBUFFER_OUT_EN_MASK                                                 (0x80000000U)

#define CTRL_WKUP_CONTROL_CKOBUFFER_CKOBUFFER_ALTSEL_SHIFT                                                (30U)
#define CTRL_WKUP_CONTROL_CKOBUFFER_CKOBUFFER_ALTSEL_MASK                                                 (0x40000000U)

#define CTRL_WKUP_CONTROL_CKOBUFFER_CKOBUFFER_POLARITY_SHIFT                                              (29U)
#define CTRL_WKUP_CONTROL_CKOBUFFER_CKOBUFFER_POLARITY_MASK                                               (0x20000000U)

#define CTRL_WKUP_CONTROL_CKOBUFFER_CKOBUFFER_CLK_EN_SHIFT                                                (28U)
#define CTRL_WKUP_CONTROL_CKOBUFFER_CKOBUFFER_CLK_EN_MASK                                                 (0x10000000U)

#define CTRL_WKUP_CONTROL_CKOBUFFER_RESERVED_0_SHIFT                                                      (0U)
#define CTRL_WKUP_CONTROL_CKOBUFFER_RESERVED_0_MASK                                                       (0x0fffffffU)

#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_NORTH_SIDE_N5_SHIFT                                                 (31U)
#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_NORTH_SIDE_N5_MASK                                                  (0x80000000U)

#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_NORTH_SIDE_N4_SHIFT                                                 (30U)
#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_NORTH_SIDE_N4_MASK                                                  (0x40000000U)

#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_NORTH_SIDE_N3_SHIFT                                                 (29U)
#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_NORTH_SIDE_N3_MASK                                                  (0x20000000U)

#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_NORTH_SIDE_N2_SHIFT                                                 (28U)
#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_NORTH_SIDE_N2_MASK                                                  (0x10000000U)

#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_NORTH_SIDE_N1_SHIFT                                                 (27U)
#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_NORTH_SIDE_N1_MASK                                                  (0x08000000U)

#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_NORTH_SIDE_N0_SHIFT                                                 (26U)
#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_NORTH_SIDE_N0_MASK                                                  (0x04000000U)

#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_NORTH_SIDE_P5_SHIFT                                                 (25U)
#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_NORTH_SIDE_P5_MASK                                                  (0x02000000U)

#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_NORTH_SIDE_P4_SHIFT                                                 (24U)
#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_NORTH_SIDE_P4_MASK                                                  (0x01000000U)

#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_NORTH_SIDE_P3_SHIFT                                                 (23U)
#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_NORTH_SIDE_P3_MASK                                                  (0x00800000U)

#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_NORTH_SIDE_P2_SHIFT                                                 (22U)
#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_NORTH_SIDE_P2_MASK                                                  (0x00400000U)

#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_NORTH_SIDE_P1_SHIFT                                                 (21U)
#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_NORTH_SIDE_P1_MASK                                                  (0x00200000U)

#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_NORTH_SIDE_P0_SHIFT                                                 (20U)
#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_NORTH_SIDE_P0_MASK                                                  (0x00100000U)

#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_EAST_SIDE_N5_SHIFT                                                  (19U)
#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_EAST_SIDE_N5_MASK                                                   (0x00080000U)

#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_EAST_SIDE_N4_SHIFT                                                  (18U)
#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_EAST_SIDE_N4_MASK                                                   (0x00040000U)

#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_EAST_SIDE_N3_SHIFT                                                  (17U)
#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_EAST_SIDE_N3_MASK                                                   (0x00020000U)

#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_EAST_SIDE_N2_SHIFT                                                  (16U)
#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_EAST_SIDE_N2_MASK                                                   (0x00010000U)

#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_EAST_SIDE_N1_SHIFT                                                  (15U)
#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_EAST_SIDE_N1_MASK                                                   (0x00008000U)

#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_EAST_SIDE_N0_SHIFT                                                  (14U)
#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_EAST_SIDE_N0_MASK                                                   (0x00004000U)

#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_EAST_SIDE_P5_SHIFT                                                  (13U)
#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_EAST_SIDE_P5_MASK                                                   (0x00002000U)

#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_EAST_SIDE_P4_SHIFT                                                  (12U)
#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_EAST_SIDE_P4_MASK                                                   (0x00001000U)

#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_EAST_SIDE_P3_SHIFT                                                  (11U)
#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_EAST_SIDE_P3_MASK                                                   (0x00000800U)

#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_EAST_SIDE_P2_SHIFT                                                  (10U)
#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_EAST_SIDE_P2_MASK                                                   (0x00000400U)

#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_EAST_SIDE_P1_SHIFT                                                  (9U)
#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_EAST_SIDE_P1_MASK                                                   (0x00000200U)

#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_EAST_SIDE_P0_SHIFT                                                  (8U)
#define CTRL_WKUP_EFUSE_1_DDRDIFF_PTV_EAST_SIDE_P0_MASK                                                   (0x00000100U)

#define CTRL_WKUP_EFUSE_1_RESERVED_0_SHIFT                                                                (0U)
#define CTRL_WKUP_EFUSE_1_RESERVED_0_MASK                                                                 (0x000000ffU)

#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_SOUTH_SIDE_N5_SHIFT                                                 (31U)
#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_SOUTH_SIDE_N5_MASK                                                  (0x80000000U)

#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_SOUTH_SIDE_N4_SHIFT                                                 (30U)
#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_SOUTH_SIDE_N4_MASK                                                  (0x40000000U)

#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_SOUTH_SIDE_N3_SHIFT                                                 (29U)
#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_SOUTH_SIDE_N3_MASK                                                  (0x20000000U)

#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_SOUTH_SIDE_N2_SHIFT                                                 (28U)
#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_SOUTH_SIDE_N2_MASK                                                  (0x10000000U)

#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_SOUTH_SIDE_N1_SHIFT                                                 (27U)
#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_SOUTH_SIDE_N1_MASK                                                  (0x08000000U)

#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_SOUTH_SIDE_N0_SHIFT                                                 (26U)
#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_SOUTH_SIDE_N0_MASK                                                  (0x04000000U)

#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_SOUTH_SIDE_P5_SHIFT                                                 (25U)
#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_SOUTH_SIDE_P5_MASK                                                  (0x02000000U)

#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_SOUTH_SIDE_P4_SHIFT                                                 (24U)
#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_SOUTH_SIDE_P4_MASK                                                  (0x01000000U)

#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_SOUTH_SIDE_P3_SHIFT                                                 (23U)
#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_SOUTH_SIDE_P3_MASK                                                  (0x00800000U)

#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_SOUTH_SIDE_P2_SHIFT                                                 (22U)
#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_SOUTH_SIDE_P2_MASK                                                  (0x00400000U)

#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_SOUTH_SIDE_P1_SHIFT                                                 (21U)
#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_SOUTH_SIDE_P1_MASK                                                  (0x00200000U)

#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_SOUTH_SIDE_P0_SHIFT                                                 (20U)
#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_SOUTH_SIDE_P0_MASK                                                  (0x00100000U)

#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_WEST_SIDE_N5_SHIFT                                                  (19U)
#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_WEST_SIDE_N5_MASK                                                   (0x00080000U)

#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_WEST_SIDE_N4_SHIFT                                                  (18U)
#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_WEST_SIDE_N4_MASK                                                   (0x00040000U)

#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_WEST_SIDE_N3_SHIFT                                                  (17U)
#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_WEST_SIDE_N3_MASK                                                   (0x00020000U)

#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_WEST_SIDE_N2_SHIFT                                                  (16U)
#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_WEST_SIDE_N2_MASK                                                   (0x00010000U)

#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_WEST_SIDE_N1_SHIFT                                                  (15U)
#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_WEST_SIDE_N1_MASK                                                   (0x00008000U)

#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_WEST_SIDE_N0_SHIFT                                                  (14U)
#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_WEST_SIDE_N0_MASK                                                   (0x00004000U)

#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_WEST_SIDE_P5_SHIFT                                                  (13U)
#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_WEST_SIDE_P5_MASK                                                   (0x00002000U)

#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_WEST_SIDE_P4_SHIFT                                                  (12U)
#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_WEST_SIDE_P4_MASK                                                   (0x00001000U)

#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_WEST_SIDE_P3_SHIFT                                                  (11U)
#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_WEST_SIDE_P3_MASK                                                   (0x00000800U)

#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_WEST_SIDE_P2_SHIFT                                                  (10U)
#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_WEST_SIDE_P2_MASK                                                   (0x00000400U)

#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_WEST_SIDE_P1_SHIFT                                                  (9U)
#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_WEST_SIDE_P1_MASK                                                   (0x00000200U)

#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_WEST_SIDE_P0_SHIFT                                                  (8U)
#define CTRL_WKUP_EFUSE_2_DDRDIFF_PTV_WEST_SIDE_P0_MASK                                                   (0x00000100U)

#define CTRL_WKUP_EFUSE_2_RESERVED_0_SHIFT                                                                (0U)
#define CTRL_WKUP_EFUSE_2_RESERVED_0_MASK                                                                 (0x000000ffU)

#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_NORTH_SIDE_N5_SHIFT                                                   (31U)
#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_NORTH_SIDE_N5_MASK                                                    (0x80000000U)

#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_NORTH_SIDE_N4_SHIFT                                                   (30U)
#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_NORTH_SIDE_N4_MASK                                                    (0x40000000U)

#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_NORTH_SIDE_N3_SHIFT                                                   (29U)
#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_NORTH_SIDE_N3_MASK                                                    (0x20000000U)

#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_NORTH_SIDE_N2_SHIFT                                                   (28U)
#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_NORTH_SIDE_N2_MASK                                                    (0x10000000U)

#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_NORTH_SIDE_N1_SHIFT                                                   (27U)
#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_NORTH_SIDE_N1_MASK                                                    (0x08000000U)

#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_NORTH_SIDE_N0_SHIFT                                                   (26U)
#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_NORTH_SIDE_N0_MASK                                                    (0x04000000U)

#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_NORTH_SIDE_P5_SHIFT                                                   (25U)
#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_NORTH_SIDE_P5_MASK                                                    (0x02000000U)

#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_NORTH_SIDE_P4_SHIFT                                                   (24U)
#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_NORTH_SIDE_P4_MASK                                                    (0x01000000U)

#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_NORTH_SIDE_P3_SHIFT                                                   (23U)
#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_NORTH_SIDE_P3_MASK                                                    (0x00800000U)

#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_NORTH_SIDE_P2_SHIFT                                                   (22U)
#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_NORTH_SIDE_P2_MASK                                                    (0x00400000U)

#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_NORTH_SIDE_P1_SHIFT                                                   (21U)
#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_NORTH_SIDE_P1_MASK                                                    (0x00200000U)

#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_NORTH_SIDE_P0_SHIFT                                                   (20U)
#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_NORTH_SIDE_P0_MASK                                                    (0x00100000U)

#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_EAST_SIDE_N5_SHIFT                                                    (19U)
#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_EAST_SIDE_N5_MASK                                                     (0x00080000U)

#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_EAST_SIDE_N4_SHIFT                                                    (18U)
#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_EAST_SIDE_N4_MASK                                                     (0x00040000U)

#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_EAST_SIDE_N3_SHIFT                                                    (17U)
#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_EAST_SIDE_N3_MASK                                                     (0x00020000U)

#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_EAST_SIDE_N2_SHIFT                                                    (16U)
#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_EAST_SIDE_N2_MASK                                                     (0x00010000U)

#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_EAST_SIDE_N1_SHIFT                                                    (15U)
#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_EAST_SIDE_N1_MASK                                                     (0x00008000U)

#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_EAST_SIDE_N0_SHIFT                                                    (14U)
#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_EAST_SIDE_N0_MASK                                                     (0x00004000U)

#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_EAST_SIDE_P5_SHIFT                                                    (13U)
#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_EAST_SIDE_P5_MASK                                                     (0x00002000U)

#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_EAST_SIDE_P4_SHIFT                                                    (12U)
#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_EAST_SIDE_P4_MASK                                                     (0x00001000U)

#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_EAST_SIDE_P3_SHIFT                                                    (11U)
#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_EAST_SIDE_P3_MASK                                                     (0x00000800U)

#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_EAST_SIDE_P2_SHIFT                                                    (10U)
#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_EAST_SIDE_P2_MASK                                                     (0x00000400U)

#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_EAST_SIDE_P1_SHIFT                                                    (9U)
#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_EAST_SIDE_P1_MASK                                                     (0x00000200U)

#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_EAST_SIDE_P0_SHIFT                                                    (8U)
#define CTRL_WKUP_EFUSE_3_DDRSE_PTV_EAST_SIDE_P0_MASK                                                     (0x00000100U)

#define CTRL_WKUP_EFUSE_3_RESERVED_0_SHIFT                                                                (0U)
#define CTRL_WKUP_EFUSE_3_RESERVED_0_MASK                                                                 (0x000000ffU)

#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_SOUTH_SIDE_N5_SHIFT                                                   (31U)
#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_SOUTH_SIDE_N5_MASK                                                    (0x80000000U)

#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_SOUTH_SIDE_N4_SHIFT                                                   (30U)
#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_SOUTH_SIDE_N4_MASK                                                    (0x40000000U)

#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_SOUTH_SIDE_N3_SHIFT                                                   (29U)
#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_SOUTH_SIDE_N3_MASK                                                    (0x20000000U)

#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_SOUTH_SIDE_N2_SHIFT                                                   (28U)
#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_SOUTH_SIDE_N2_MASK                                                    (0x10000000U)

#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_SOUTH_SIDE_N1_SHIFT                                                   (27U)
#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_SOUTH_SIDE_N1_MASK                                                    (0x08000000U)

#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_SOUTH_SIDE_N0_SHIFT                                                   (26U)
#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_SOUTH_SIDE_N0_MASK                                                    (0x04000000U)

#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_SOUTH_SIDE_P5_SHIFT                                                   (25U)
#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_SOUTH_SIDE_P5_MASK                                                    (0x02000000U)

#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_SOUTH_SIDE_P4_SHIFT                                                   (24U)
#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_SOUTH_SIDE_P4_MASK                                                    (0x01000000U)

#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_SOUTH_SIDE_P3_SHIFT                                                   (23U)
#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_SOUTH_SIDE_P3_MASK                                                    (0x00800000U)

#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_SOUTH_SIDE_P2_SHIFT                                                   (22U)
#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_SOUTH_SIDE_P2_MASK                                                    (0x00400000U)

#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_SOUTH_SIDE_P1_SHIFT                                                   (21U)
#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_SOUTH_SIDE_P1_MASK                                                    (0x00200000U)

#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_SOUTH_SIDE_P0_SHIFT                                                   (20U)
#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_SOUTH_SIDE_P0_MASK                                                    (0x00100000U)

#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_WEST_SIDE_N5_SHIFT                                                    (19U)
#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_WEST_SIDE_N5_MASK                                                     (0x00080000U)

#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_WEST_SIDE_N4_SHIFT                                                    (18U)
#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_WEST_SIDE_N4_MASK                                                     (0x00040000U)

#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_WEST_SIDE_N3_SHIFT                                                    (17U)
#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_WEST_SIDE_N3_MASK                                                     (0x00020000U)

#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_WEST_SIDE_N2_SHIFT                                                    (16U)
#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_WEST_SIDE_N2_MASK                                                     (0x00010000U)

#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_WEST_SIDE_N1_SHIFT                                                    (15U)
#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_WEST_SIDE_N1_MASK                                                     (0x00008000U)

#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_WEST_SIDE_N0_SHIFT                                                    (14U)
#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_WEST_SIDE_N0_MASK                                                     (0x00004000U)

#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_WEST_SIDE_P5_SHIFT                                                    (13U)
#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_WEST_SIDE_P5_MASK                                                     (0x00002000U)

#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_WEST_SIDE_P4_SHIFT                                                    (12U)
#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_WEST_SIDE_P4_MASK                                                     (0x00001000U)

#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_WEST_SIDE_P3_SHIFT                                                    (11U)
#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_WEST_SIDE_P3_MASK                                                     (0x00000800U)

#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_WEST_SIDE_P2_SHIFT                                                    (10U)
#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_WEST_SIDE_P2_MASK                                                     (0x00000400U)

#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_WEST_SIDE_P1_SHIFT                                                    (9U)
#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_WEST_SIDE_P1_MASK                                                     (0x00000200U)

#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_WEST_SIDE_P0_SHIFT                                                    (8U)
#define CTRL_WKUP_EFUSE_4_DDRSE_PTV_WEST_SIDE_P0_MASK                                                     (0x00000100U)

#define CTRL_WKUP_EFUSE_4_RESERVED_0_SHIFT                                                                (0U)
#define CTRL_WKUP_EFUSE_4_RESERVED_0_MASK                                                                 (0x000000ffU)

#define CTRL_WKUP_EFUSE_13_SDIO1833_PTV_N5_SHIFT                                                          (31U)
#define CTRL_WKUP_EFUSE_13_SDIO1833_PTV_N5_MASK                                                           (0x80000000U)

#define CTRL_WKUP_EFUSE_13_SDIO1833_PTV_N4_SHIFT                                                          (30U)
#define CTRL_WKUP_EFUSE_13_SDIO1833_PTV_N4_MASK                                                           (0x40000000U)

#define CTRL_WKUP_EFUSE_13_SDIO1833_PTV_N3_SHIFT                                                          (29U)
#define CTRL_WKUP_EFUSE_13_SDIO1833_PTV_N3_MASK                                                           (0x20000000U)

#define CTRL_WKUP_EFUSE_13_SDIO1833_PTV_N2_SHIFT                                                          (28U)
#define CTRL_WKUP_EFUSE_13_SDIO1833_PTV_N2_MASK                                                           (0x10000000U)

#define CTRL_WKUP_EFUSE_13_SDIO1833_PTV_N1_SHIFT                                                          (27U)
#define CTRL_WKUP_EFUSE_13_SDIO1833_PTV_N1_MASK                                                           (0x08000000U)

#define CTRL_WKUP_EFUSE_13_SDIO1833_PTV_N0_SHIFT                                                          (26U)
#define CTRL_WKUP_EFUSE_13_SDIO1833_PTV_N0_MASK                                                           (0x04000000U)

#define CTRL_WKUP_EFUSE_13_SDIO1833_PTV_P5_SHIFT                                                          (25U)
#define CTRL_WKUP_EFUSE_13_SDIO1833_PTV_P5_MASK                                                           (0x02000000U)

#define CTRL_WKUP_EFUSE_13_SDIO1833_PTV_P4_SHIFT                                                          (24U)
#define CTRL_WKUP_EFUSE_13_SDIO1833_PTV_P4_MASK                                                           (0x01000000U)

#define CTRL_WKUP_EFUSE_13_SDIO1833_PTV_P3_SHIFT                                                          (23U)
#define CTRL_WKUP_EFUSE_13_SDIO1833_PTV_P3_MASK                                                           (0x00800000U)

#define CTRL_WKUP_EFUSE_13_SDIO1833_PTV_P2_SHIFT                                                          (22U)
#define CTRL_WKUP_EFUSE_13_SDIO1833_PTV_P2_MASK                                                           (0x00400000U)

#define CTRL_WKUP_EFUSE_13_SDIO1833_PTV_P1_SHIFT                                                          (21U)
#define CTRL_WKUP_EFUSE_13_SDIO1833_PTV_P1_MASK                                                           (0x00200000U)

#define CTRL_WKUP_EFUSE_13_SDIO1833_PTV_P0_SHIFT                                                          (20U)
#define CTRL_WKUP_EFUSE_13_SDIO1833_PTV_P0_MASK                                                           (0x00100000U)

#define CTRL_WKUP_EFUSE_13_RESERVED_0_SHIFT                                                               (0U)
#define CTRL_WKUP_EFUSE_13_RESERVED_0_MASK                                                                (0x000fffffU)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_CTRL_WKUP_PAD_H_ */
