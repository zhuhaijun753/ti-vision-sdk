/*
 * Aic31Local.h
 *
 * Aic3106 Codec Driver internal header file
 *
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
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

/*
 *  ======== platforms/codec/include/Aic31Local.h ========
 *
 */

#ifndef AIC31LOCAL_H_
#define AIC31LOCAL_H_

#include <xdc/std.h>
#include <ti/sysbios/io/GIO.h>
#include <ti/sysbios/io/DEV.h>

#include <devices/bsp_audioICodec.h>
#include <devices/bsp_aic31.h>

#ifdef __cplusplus
extern "C" {
#endif

/* -------- constants -------- */

#define Aic31_P0_REG0      (UInt8) (0)    /**< Page Select */
#define Aic31_P0_REG1      (UInt8) (1)    /**<  Software Reset */
#define Aic31_P0_REG2      (UInt8) (2)    /**<  Codec Sample Rate Select */
#define Aic31_P0_REG3      (UInt8) (3)    /**<  PLL Programming A */
#define Aic31_P0_REG4      (UInt8) (4)    /**<  PLL Programming B */
#define Aic31_P0_REG5      (UInt8) (5)    /**<  PLL Programming C */
#define Aic31_P0_REG6      (UInt8) (6)    /**<  PLL Programming D */
#define Aic31_P0_REG7      (UInt8) (7)    /**<  Codec Datapath Setup */
#define Aic31_P0_REG8      (UInt8) (8)    /**<  Audio Serial Data Interface
                                           *   Control A */
#define Aic31_P0_REG9      (UInt8) (9)    /**<  Audio Serial Data Interface
                                           *   Control B */
#define Aic31_P0_REG10     (UInt8) (10)   /**<  Audio Serial Data Interface
                                           *   Control C */
#define Aic31_P0_REG11     (UInt8) (11)   /**<  Audio Codec Overflow Flag  */
#define Aic31_P0_REG12     (UInt8) (12)   /**<  Audio Codec Digital Filter
                                           *   Control */
#define Aic31_P0_REG13     (UInt8) (13)   /**<  Headset / Button Press Detection
                                           *   A */
#define Aic31_P0_REG14     (UInt8) (14)   /**<  Headset / Button Press Detection
                                           *   B */
#define Aic31_P0_REG15     (UInt8) (15)   /**<  Left ADC PGA Gain Control */
#define Aic31_P0_REG16     (UInt8) (16)   /**<  Right ADC PGA Gain Control */
#define Aic31_P0_REG17     (UInt8) (17)   /**<  MIC3L/R to Left ADC Control */
#define Aic31_P0_REG18     (UInt8) (18)   /**<  MIC3L/R to Right ADC Control */
#define Aic31_P0_REG19     (UInt8) (19)   /**<  LINE1L to Left ADC Control */
#define Aic31_P0_REG20     (UInt8) (20)   /**<  LINE2L to Left ADC Control */
#define Aic31_P0_REG21     (UInt8) (21)   /**<  LINE1R to Left ADC Control */
#define Aic31_P0_REG22     (UInt8) (22)   /**<  LINE1R to Right ADC Control */
#define Aic31_P0_REG23     (UInt8) (23)   /**<  LINE2R to Right ADC Control */
#define Aic31_P0_REG24     (UInt8) (24)   /**<  LINE1L to Right ADC Control */
#define Aic31_P0_REG25     (UInt8) (25)   /**<  MICBIAS Control */
#define Aic31_P0_REG26     (UInt8) (26)   /**<  Left AGC Control A */
#define Aic31_P0_REG27     (UInt8) (27)   /**<  Left AGC Control B */
#define Aic31_P0_REG28     (UInt8) (28)   /**<  Left AGC Control C */
#define Aic31_P0_REG29     (UInt8) (29)   /**<  Right AGC Control A */
#define Aic31_P0_REG30     (UInt8) (30)   /**<  Right AGC Control B */
#define Aic31_P0_REG31     (UInt8) (31)   /**<  Right AGC Control C */
#define Aic31_P0_REG32     (UInt8) (32)   /**<  Left AGC Gain */
#define Aic31_P0_REG33     (UInt8) (33)   /**<  Right AGC Gain */
#define Aic31_P0_REG34     (UInt8) (34)   /**<  Left AGC Noise Gate Debounce */
#define Aic31_P0_REG35     (UInt8) (35)   /**<  Right AGC Noise Gate Debounce */
#define Aic31_P0_REG36     (UInt8) (36)   /**<  ADC Flag */
#define Aic31_P0_REG37     (UInt8) (37)   /**<  DAC Power and Output Driver
                                           *   Control */
#define Aic31_P0_REG38     (UInt8) (38)   /**<  High Power Output Driver Control
                                           */
#define Aic31_P0_REG40     (UInt8) (40)   /**<  High Power Output Stage Control
                                           */
#define Aic31_P0_REG41     (UInt8) (41)   /**<  DAC Output Switching Control */
#define Aic31_P0_REG42     (UInt8) (42)   /**<  Output Driver Pop Reduction */
#define Aic31_P0_REG43     (UInt8) (43)   /**<  Left DAC Digital Volume Control
                                           */
#define Aic31_P0_REG44     (UInt8) (44)   /**<  Right DAC Digital Volume Control
                                           */
#define Aic31_P0_REG45     (UInt8) (45)   /**<  LINE2L to HPLOUT Volume Control
                                           */
#define Aic31_P0_REG46     (UInt8) (46)   /**<  PGA_L to HPLOUT Volume Control
                                           */
#define Aic31_P0_REG47     (UInt8) (47)   /**<  DAC_L1 to HPLOUT Volume Control
                                           */
#define Aic31_P0_REG48     (UInt8) (48)   /**<  LINE2R to HPLOUT Volume Control
                                           */
#define Aic31_P0_REG49     (UInt8) (49)   /**<  PGA_R to HPLOUT Volume Control
                                           */
#define Aic31_P0_REG50     (UInt8) (50)   /**<  DAC_R1 to HPLOUT Volume Control
                                           */
#define Aic31_P0_REG51     (UInt8) (51)   /**<  HPLOUT Output Level Control
                                           */
#define Aic31_P0_REG52     (UInt8) (52)   /**<  LINE2L to HPLCOM Volume Control
                                           */
#define Aic31_P0_REG53     (UInt8) (53)   /**<  PGA_L to HPLCOM Volume Control
                                           */
#define Aic31_P0_REG54     (UInt8) (54)   /**<  DAC_L1 to HPLCOM Volume Control
                                           */
#define Aic31_P0_REG55     (UInt8) (55)   /**<  LINE2R to HPLCOM Volume Control
                                           */
#define Aic31_P0_REG56     (UInt8) (56)   /**<  PGA_R to HPLCOM Volume Control
                                           */
#define Aic31_P0_REG57     (UInt8) (57)   /**<  DAC_R1 to HPLCOM Volume Control
                                           */
#define Aic31_P0_REG58     (UInt8) (58)   /**<  HPLCOM Output Level Control */
#define Aic31_P0_REG59     (UInt8) (59)   /**<  LINE2L to HPROUT Volume Control
                                           */
#define Aic31_P0_REG60     (UInt8) (60)   /**<  PGA_L to HPROUT Volume Control
                                           */
#define Aic31_P0_REG61     (UInt8) (61)   /**<  DAC_L1 to HPROUT Volume Control
                                           */
#define Aic31_P0_REG62     (UInt8) (62)   /**<  LINE2R to HPROUT Volume Control
                                           */
#define Aic31_P0_REG63     (UInt8) (63)   /**<  PGA_R to HPROUT Volume Control
                                           */
#define Aic31_P0_REG64     (UInt8) (64)   /**<  DAC_R1 to HPROUT Volume Control
                                           */
#define Aic31_P0_REG65     (UInt8) (65)   /**<  HPROUT Output Level Control */
#define Aic31_P0_REG66     (UInt8) (66)   /**<  LINE2L to HPRCOM Volume Control
                                           */
#define Aic31_P0_REG67     (UInt8) (67)   /**<  PGA_L to HPRCOM Volume Control
                                           */
#define Aic31_P0_REG68     (UInt8) (68)   /**<  DAC_L1 to HPRCOM Volume Control
                                           */
#define Aic31_P0_REG69     (UInt8) (69)   /**<  LINE2R to HPRCOM Volume Control
                                           */
#define Aic31_P0_REG70     (UInt8) (70)   /**<  PGA_R to HPRCOM Volume Control
                                           */
#define Aic31_P0_REG71     (UInt8) (71)   /**<  DAC_R1 to HPRCOM Volume Control
                                           */
#define Aic31_P0_REG72     (UInt8) (72)   /**<  HPRCOM Output Level Control */
#define Aic31_P0_REG73     (UInt8) (73)   /**<  LINE2L to MONO_LOP/M Volume
                                           *   Control */
#define Aic31_P0_REG74     (UInt8) (74)   /**<  PGA_L to MONO_LOP/M Volume
                                           *   Control */
#define Aic31_P0_REG75     (UInt8) (75)   /**<  DAC_L1 to MONO_LOP/M Volume
                                           *   Control  */
#define Aic31_P0_REG76     (UInt8) (76)   /**<  LINE2R to MONO_LOP/M Volume
                                           *   Control  */
#define Aic31_P0_REG77     (UInt8) (77)   /**<  PGA_R to MONO_LOP/M Volume
                                           *   Control */
#define Aic31_P0_REG78     (UInt8) (78)   /**<  DAC_R1 to MONO_LOP/M Volume
                                           *   Control  */
#define Aic31_P0_REG79     (UInt8) (79)   /**<  MONO_LOP/M Output Level Control
                                           */
#define Aic31_P0_REG80     (UInt8) (80)   /**<  LINE2L to LEFT_LOP/M Volume
                                           *   Control */
#define Aic31_P0_REG81     (UInt8) (81)   /**<  PGA_L to LEFT_LOP/M Volume
                                           *   Control */
#define Aic31_P0_REG82     (UInt8) (82)   /**<  DAC_L1 to LEFT_LOP/M Volume
                                           *   Control */
#define Aic31_P0_REG83     (UInt8) (83)   /**<  LINE2R to LEFT_LOP/M Volume
                                           *   Control */
#define Aic31_P0_REG84     (UInt8) (84)   /**<  PGA_R to LEFT_LOP/M Volume
                                           *   Control */
#define Aic31_P0_REG85     (UInt8) (85)   /**<  DAC_R1 to LEFT_LOP/M Volume
                                           *   Control */
#define Aic31_P0_REG86     (UInt8) (86)   /**<  LEFT_LOP/M Output Level Control
                                           */
#define Aic31_P0_REG87     (UInt8) (87)   /**<  LINE2L to RIGHT_LOP/M Volume
                                           *   Control */
#define Aic31_P0_REG88     (UInt8) (88)   /**<  PGA_L to RIGHT_LOP/M Volume
                                           *   Control */
#define Aic31_P0_REG89     (UInt8) (89)   /**<  DAC_L1 to RIGHT_LOP/M Volume
                                           *   Control */
#define Aic31_P0_REG90     (UInt8) (90)   /**<  LINE2R to RIGHT_LOP/M Volume
                                           *   Control */
#define Aic31_P0_REG91     (UInt8) (91)   /**<  PGA_R to RIGHT_LOP/M Volume
                                           *   Control */
#define Aic31_P0_REG92     (UInt8) (92)   /**<  DAC_R1 to RIGHT_LOP/M Volume
                                           *   Control    */
#define Aic31_P0_REG93     (UInt8) (93)   /**<  RIGHT_LOP/M Output Level Control
                                           */
#define Aic31_P0_REG94     (UInt8) (94)   /**<  Module Power Status */
#define Aic31_P0_REG95     (UInt8) (95)   /**< O/P Driver Short Circuit
                                           *   Detection Status */
#define Aic31_P0_REG96     (UInt8) (96)   /**<  Sticky Interrupt Flags */
#define Aic31_P0_REG97     (UInt8) (97)   /**<  Real-time Interrupt Flags */
#define Aic31_P0_REG98     (UInt8) (98)   /**<  GPIO1 Control */
#define Aic31_P0_REG99     (UInt8) (99)   /**<  GPIO2 Control */
#define Aic31_P0_REG100    (UInt8) (100)  /**<  Additional GPIO Control A */
#define Aic31_P0_REG101    (UInt8) (101)  /**<  Additional GPIO Control B */
#define Aic31_P0_REG102    (UInt8) (102)  /**<  Clock Generation Control */
#define Aic31_P0_REG103    (UInt8) (103)  /**< Left AGC New Programmable Attack
                                           *   Time */
#define Aic31_P0_REG104    (UInt8) (104)  /**< Left AGC New Programmable Decay
                                           *   Time */
#define Aic31_P0_REG105    (UInt8) (105)  /**< Right AGC New Programmable Attack
                                           *  Time */
#define Aic31_P0_REG106    (UInt8) (106)  /**< Right AGC New Programmable Decay
                                           *  Time */
#define Aic31_P0_REG107    (UInt8) (107)  /**< New Programmable ADC Digital Path
                                           *  and I2C Bus Condition */
#define Aic31_P0_REG108    (UInt8) (108)  /**< Passive Analog Signal Bypass
                                           *  Selection During Powerdown */
#define Aic31_P0_REG109    (UInt8) (109)  /**< DAC Quiescent Current Adjustment
                                           */

#define Aic31_PAGE_SELECT_ADDR                      (UInt8) (0x0000)
#define Aic31_RESET_ADDR                            (UInt8) (0x0001)
#define Aic31_CODEC_SAMPLE_RATE_ADDR                (UInt8) (0x0002)
#define Aic31_PLLA_PROG_ADDR                        (UInt8) (0x0003)
#define Aic31_PLLB_PROG_ADDR                        (UInt8) (0x0004)
#define Aic31_PLLC_PROG_ADDR                        (UInt8) (0x0005)
#define Aic31_PLLD_PROG_ADDR                        (UInt8) (0x0006)
#define Aic31_CODEC_DATAPATH_SETUP_ADDR             (UInt8) (0x0007)
#define Aic31_SERIAL_INTERFACEA_ADDR                (UInt8) (0x0008)
#define Aic31_SERIAL_INTERFACEB_ADDR                (UInt8) (0x0009)
#define Aic31_SERIAL_INTERFACEC_ADDR                (UInt8) (0x000A)
#define Aic31_CODEC_OVERFLOW_FLAG_ADDR              (UInt8) (0x000B)
#define Aic31_CODEC_DIGIFILTER_CTRL_ADDR            (UInt8) (0x000C)
#define Aic31_CODEC_HEADSET_DETA_ADDR               (UInt8) (0x000D)
#define Aic31_CODEC_HEADSET_DETB_ADDR               (UInt8) (0x000E)
#define Aic31_LEFT_ADCPGA_GAIN_CTRL_ADDR            (UInt8) (0x000F)
#define Aic31_RIGHT_ADCPGA_GAIN_CTRL_ADDR           (UInt8) (0x0010)
#define Aic31_MIC3LR_TO_LEFTADC_CTRL_ADDR           (UInt8) (0x0011)
#define Aic31_MIC3LR_TO_RIGHTADC_CTRL_ADDR          (UInt8) (0x0012)
#define Aic31_LINE1L_TO_LEFT_ADC_CTRL_ADDR          (UInt8) (0x0013)
#define Aic31_LINE2L_TO_LEFT_ADC_CTRL_ADDR          (UInt8) (0x0014)
#define Aic31_LINE1R_TO_LEFT_ADC_CTRL_ADDR          (UInt8) (0x0015)
#define Aic31_LINE1R_TO_RIGHT_ADC_CTL_ADDR          (UInt8) (0x0016)
#define Aic31_LINE2R_TO_RIGTH_ADC_CTRL_ADDR         (UInt8) (0x0017)
#define Aic31_LINE1L_TO_RIGTH_ADC_CTRL_ADDR         (UInt8) (0x0018)
#define Aic31_MICBIAS_CTRL_ADDR                     (UInt8) (0x0019)
#define Aic31_LEFT_AGC_CTRLA_ADDR                   (UInt8) (0x001A)
#define Aic31_LEFT_AGC_CTRLB_ADDR                   (UInt8) (0x001B)
#define Aic31_LEFT_AGC_CTRLC_ADDR                   (UInt8) (0x001C)
#define Aic31_RIGHT_AGC_CTRLA_ADDR                  (UInt8) (0x001D)
#define Aic31_RIGHT_AGC_CTRLB_ADDR                  (UInt8) (0x001E)
#define Aic31_RIGHT_AGC_CTRLC_ADDR                  (UInt8) (0x001F)
#define Aic31_LEFT_AGC_GAIN_ADDR                    (UInt8) (0x0020)
#define Aic31_RIGHT_AGC_GAIN_ADDR                   (UInt8) (0x0021)
#define Aic31_LEFT_AGC_NOISE_GATE_DEBOUNCE_ADDR     (UInt8) (0x0022)
#define Aic31_RIGHT_AGC_NOISE_GATE_DEBOUNCE_ADDR    (UInt8) (0x0023)
#define Aic31_ADC_FLAG_ADDR                         (UInt8) (0x0024)
#define Aic31_DAC_POWER_OUTPUT_DRIVER_CTRL_ADDR     (UInt8) (0x0025)
#define Aic31_HP_OUTPUT_DRIVER_CTRL_ADDR            (UInt8) (0x0026)
#define Aic31_RESERVE                               (UInt8) (0x0027)
#define Aic31_HP_OUTPUT_STAGE_CTRL_ADDR             (UInt8) (0x0028)
#define Aic31_DAC_OUTPUT_SWITCH_CTRL_ADDR           (UInt8) (0x0029)
#define Aic31_OUTPUT_DRV_POP_REDUCTION_ADDR         (UInt8) (0x002A)
#define Aic31_LEFT_DAC_VOL_CTRL_ADDR                (UInt8) (0x002B)
#define Aic31_RIGHT_DAC_VOL_CTRL_ADDR               (UInt8) (0x002C)
#define Aic31_LINE2L_TO_HPLOUT_VOL_CTRL_ADDR        (UInt8) (0x002D)
#define Aic31_PGA_L_TO_HPLOUT_VOL_CTRL_ADDR         (UInt8) (0x002E)
#define Aic31_DAC_L1_TO_HPLOUT_VOL_CTRL_ADDR        (UInt8) (0x002F)
#define Aic31_LINE2R_TO_HPLOUT_VOL_CTRL_ADDR        (UInt8) (0x0030)
#define Aic31_PGA_R_TO_HPLOUT_VOL_CTRL_ADDR         (UInt8) (0x0031)
#define Aic31_DAC_R1_TO_HPLOUT_VOL_CTRL_ADDR        (UInt8) (0x0032)
#define Aic31_HPLOUT_OUTPUT_LEVEL_CTRL_ADDR         (UInt8) (0x0033)
#define Aic31_LIN2L_TO_HPLCOM_VOL_CTRL_ADDR         (UInt8) (0x0034)
#define Aic31_PGA_L_TO_HPLCOM_VOL_CTRL_ADDR         (UInt8) (0x0035)
#define Aic31_DAC_L1_TO_HPLCOM_VOL_CTRL_ADDR        (UInt8) (0x0036)
#define Aic31_LINE2R_TO_HPLCOM_VOL_CTRL_ADDR        (UInt8) (0x0037)
#define Aic31_PGA_R_TO_HPLCOM_VOL_CTRL_ADDR         (UInt8) (0x0038)
#define Aic31_DAC_R1_TO_HPLCOM_VOL_CTRL_ADDR        (UInt8) (0x0039)
#define Aic31_HPLCOM_OUTPUT_LEVEL_CTRL_ADDR         (UInt8) (0x003A)
#define Aic31_LINE2L_TO_HPROUT_VOL_CTRL_ADDR        (UInt8) (0x003B)
#define Aic31_PGA_L_TO_HPROUT_VOL_CTRL_ADDR         (UInt8) (0x003C)
#define Aic31_DAC_L1_TO_HPROUT_VOL_CTRL_ADDR        (UInt8) (0x003D)
#define Aic31_LINE2R_TO_HPROUT_VOL_CTRL_ADDR        (UInt8) (0x003E)
#define Aic31_PGA_R_TO_HPROUT_VOL_CTRL_ADDR         (UInt8) (0x003F)
#define Aic31_DAC_R1_TO_HPROUT_VOL_CTRL_ADDR        (UInt8) (0x0040)
#define Aic31_HPROUT_OUTPUT_LEVEL_CTRL_ADDR         (UInt8) (0x0041)
#define Aic31_LIN2L_TO_HPRCOM_VOL_CTRL_ADDR         (UInt8) (0x0042)
#define Aic31_PGA_L_TO_HPRCOM_VOL_CTRL_ADDR         (UInt8) (0x0043)
#define Aic31_DAC_L1_TO_HPRCOM_VOL_CTRL_ADDR        (UInt8) (0x0044)
#define Aic31_LINE2R_TO_HPRCOM_VOL_CTRL_ADDR        (UInt8) (0x0045)
#define Aic31_PGA_R_TO_HPRCOM_VOL_CTRL_ADDR         (UInt8) (0x0046)
#define Aic31_DAC_R1_TO_HPRCOM_VOL_CTRL_ADDR        (UInt8) (0x0047)
#define Aic31_HPRCOM_OUTPUT_LEVEL_CTRL_ADDR         (UInt8) (0x0048)
#define Aic31_LIN2L_TO_MONO_LOPM_VOL_CTRL_ADDR      (UInt8) (0x0049)
#define Aic31_PGA_L_TO_MONO_LOPM_VOL_CTRL_ADDR      (UInt8) (0x004A)
#define Aic31_DAC_L1_TO_MONO_LOPM_VOL_CTRL_ADDR     (UInt8) (0x004B)
#define Aic31_LINE2R_TO_MONO_LOPM_VOL_CTRL_ADDR     (UInt8) (0x004C)
#define Aic31_PGA_R_TO_MONO_LOPM_VOL_CTRL_ADDR      (UInt8) (0x004D)
#define Aic31_DAC_R1_TO_MONO_LOPM_VOL_CTRL_ADDR     (UInt8) (0x004E)
#define Aic31_MONO_LOPM_OUTPUT_LEVEL_CTRL_ADDR      (UInt8) (0x004F)
#define Aic31_LIN2L_TO_LEFT_LOPM_VOL_CTRL_ADDR      (UInt8) (0x0050)
#define Aic31_PGA_L_TO_LEFT_LOPM_VOL_CTRL_ADDR      (UInt8) (0x0051)
#define Aic31_DAC_L1_TO_LEFT_LOPM_VOL_CTRL_ADDR     (UInt8) (0x0052)
#define Aic31_LINE2R_TO_LEFT_LOPM_VOL_CTRL_ADDR     (UInt8) (0x0053)
#define Aic31_PGA_R_TO_LEFT_LOPM_VOL_CTRL_ADDR      (UInt8) (0x0054)
#define Aic31_DAC_R1_TO_LEFT_LOPM_VOL_CTRL_ADDR     (UInt8) (0x0055)
#define Aic31_LEFT_LOPM_OUTPUT_LEVEL_CTRL_ADDR      (UInt8) (0x0056)
#define Aic31_LIN2L_TO_RIGHT_LOPM_VOL_CTRL_ADDR     (UInt8) (0x0057)
#define Aic31_PGA_L_TO_RIGHT_LOPM_VOL_CTRL_ADDR     (UInt8) (0x0058)
#define Aic31_DAC_L1_TO_RIGHT_LOPM_VOL_CTRL_ADDR    (UInt8) (0x0059)
#define Aic31_LINE2R_TO_RIGHT_LOPM_VOL_CTRL_ADDR    (UInt8) (0x005A)
#define Aic31_PGA_R_TO_RIGHT_LOPM_VOL_CTRL_ADDR     (UInt8) (0x005B)
#define Aic31_DAC_R1_TO_RIGHT_LOPM_VOL_CTRL_ADDR    (UInt8) (0x005C)
#define Aic31_RIGHT_LOPM_OUTPUT_LEVEL_CTRL_ADDR     (UInt8) (0x005D)
#define Aic31_MODULE_POWER_STAT_ADDR                (UInt8) (0x005E)
#define Aic31_OUTPUT_DRV_SHORTCKT_DET_STAT_ADDR     (UInt8) (0x005F)
#define Aic31_STICKY_INTR_FLAGS_ADDR                (UInt8) (0x0060)
#define Aic31_REALTIME_INTR_FLAGS_ADDR              (UInt8) (0x0061)
#define Aic31_GPIO1_CTRL_ADDR                       (UInt8) (0x0062)
#define Aic31_GPIO2_CTRL_ADDR                       (UInt8) (0x0063)
#define Aic31_ADDITIONAL_GPIOCTRLA_ADDR             (UInt8) (0x0064)
#define Aic31_ADDITIONAL_GPIOCTRLB_ADDR             (UInt8) (0x0065)
#define Aic31_CLKGEN_CTRL_ADDR                      (UInt8) (0x0066)

/* Selct Aic31 page 0 registers                   */
#define Aic31_PAGE_0              (UInt8) (0x00)
#define Aic31_PAGE_1              (UInt8) (0x01)

/* Max value of gain to be programmed to the DAC  */
#define Aic31_MAX_DAC_GAIN_VALUE  (UInt8) (0x7F)

/* Max value of gain to be programmed to the AGC  */
#define Aic31_MAX_AGC_GAIN_VALUE  (UInt8) (0x77)

/* Max value of gain to be programmed to the PGA  */
#define Aic31_MAX_PGA_GAIN_VALUE  (UInt8) (0x77)

/* MAX percent of the gain allowed                */
#define Aic31_MAX_GAIN_PERCENT    (UInt8) (100U)

#define Aic31_REG_READ_PASS        (0U)

#define Aic31_REG_READ_FAIL        (1U)

#define Aic31_REG_WRITE_PASS       (0U)

#define Aic31_REG_WRITE_FAIL       (1U)

#define PLL_CLK_DIV_VAL_MAX        (17U)
#define PLL_CLK_DIV_VAL_MIN        (2U)

#if defined (TDA2XX_FAMILY_BUILD) || defined (TDA3XX_FAMILY_BUILD) || \
    defined (TI814X_BUILD) || defined (CHIP_C6A811x)
    #define AIC31_NUM_INSTANCES   (2U)
#ifdef TDA2EX_BUILD
    #define AIC31_INST0_ADDRESS   (0x19U)       /* Used for CPU board AIC31 */
#else
    #define AIC31_INST0_ADDRESS   (0x18U)
#endif
    #define AIC31_INST1_ADDRESS   (0x18U)       /* Used for JAMR3 AIC31 */
#endif

/* -------- structs -------- */

/**
 *  \brief Channel Object which stores the channel related information.
 *
 *  This structure defines the audio codec channel specific data.it defines
 *  the state of the channel and stores the information required by the
 *  channel.
 */
typedef struct
{
    ICodec_DriverState chanStatus;
    /**< The state of the channel. It could be opened or closed.              */

    ICodec_Channel     channelMode;
    /**< The channe mode. It could be transmit or recieve                     */

    Ptr                devHandle;
    /**< Pointer to the audio codec object                                    */

    UInt32             samplingRate;
    /**< Current sampling rate of the channel                                 */

    UInt32             chanGain;
    /**< The current gain of the channel in percentage                        */
}Aic31_Channel_Object;

/**
 *  \brief Hardware information structure
 *
 *  Aic31 structure containing the instance specific data.This data is
 *  loaded from the platform.xs file(this file contains the information
 *  specific to the platform).
 */
typedef struct {
    UInt32 deviceAddress;
}Aic31_HwInfo;

/* -------- module-wide state -------- */

/**
 *  \brief Moule state object
 */
typedef struct {
    Bool inUse[AIC31_NUM_INSTANCES];
} Aic31_Module_State;

/* -------- per-instance state -------- */

/**
 *  \brief Instance State object
 */
typedef struct
{
    UInt8                 instNum;
    /**< Instance number of the current codec type to be opened               */

    ICodec_DriverState    devState;
    /**< The state of the audio codec. It could created or deleted state      */

    ICodec_CodecType      acType;
    /**< Identifies the type of audio codec (AIC12 / AIC23 / TP)              */

    ICodec_ControlBusType acControlBusType;
    /**< Type of the control bus (SPI or I2C)                                 */

    String                acCtrlBusName;
    /**< Instance number of the control bus  (I2C or SPI)                     */

    DEV_Handle            acCtrlBusHandle;
    /* pointer to the driver object of the control bus                        */

    UInt32                acCodecId;
    /**< I2C slave address or SPI CS number                                   */

    ICodec_OpMode         acOpMode;
    /**< Audio Codec operating mode                                           */

    ICodec_DataType       acSerialDataType;
    /**< Audio Codec serial data type                                         */

    UInt32                acSlotWidth;
    /**< Slot width of each channel                                           */

    ICodec_DataPath       acDataPath;
    /**< Data paths (Tx / Rx / Both Tx and Rx )                               */

    Bool                  isRxTxClockIndependent;
    /**< Defines if the serial clock is common for both Tx and Rx data paths  */

    Bool                  isClkSrcMCLK;
    /**< Audio codec reference master clock source                        */

    Aic31_Channel_Object  ChanObj[ICodec_Channel_MAX];
    /**< The audio codec channel objects of transmit and receive channels     */

    Ptr                   hCtrlBus;
    /**< Handle of the control bus instance created and opened                */

    Semaphore_Handle      semObj;
    /**< Semaphore Handle used while doing I2C transfer                       */
    Semaphore_Struct      semStruct;
    /**< used for static allocation of semObj                                 */
} Aic31_Object;

#ifdef __cplusplus
}
#endif

#endif  /*AIC31LOCAL_H_ */
