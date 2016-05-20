/* ======================================================================
 *   Copyright (C) 2013 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */
/**
 *  \file  interrupt.h
 *
 *  \brief This file contains the API prototypes for configuring INTC for
 *         ARM Cortex-A8
 */

#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "stdint.h"
#include "hw_intc.h"
#include "hw_types.h"

#ifdef __cplusplus
extern "C" {
#endif
/****************************************************************************
**                       MACRO DEFINITIONS
****************************************************************************/
/*
** Macros which can be passed to IntPrioritySet API as hostIntRoute.
*/
/* To route an interrupt to IRQ */
#define AINTC_HOSTINT_ROUTE_IRQ                (0)

/* To route an interrupt to FIQ */
#define AINTC_HOSTINT_ROUTE_FIQ                (INTC_ILR_FIQNIRQ)

/*
** Interrupt number list
*/
#define SYS_INT_EMUINT                         (0)
#define SYS_INT_COMMTX                         (1)
#define SYS_INT_COMMRX                         (2)
#define SYS_INT_BENCH                          (3)
#define SYS_INT_ELM_IRQ                        (4)
#define SYS_INT_SSM_WFI_IRQ                    (5)
#define SYS_INT_SSM_IRQ                        (6)
#define SYS_INT_NMI                            (7)
#define SYS_INT_SEC_EVNT                       (8)
#define SYS_INT_L3DEBUG                        (9)
#define SYS_INT_L3APPINT                       (10)
#define SYS_INT_PRCMINT                        (11)
#define SYS_INT_EDMACOMPINT                    (12)
#define SYS_INT_EDMAMPERR                      (13)
#define SYS_INT_EDMAERRINT                     (14)
#define SYS_INT_WDT0INT                        (15)
#define SYS_INT_ADC_TSC_GENINT                 (16)
#define SYS_INT_USBSSINT                       (17)
#define SYS_INT_USB0                           (18)
#define SYS_INT_USB1                           (19)
#define SYS_INT_PRUSS1_EVTOUT0                 (20)
#define SYS_INT_PRUSS1_EVTOUT1                 (21)
#define SYS_INT_PRUSS1_EVTOUT2                 (22)
#define SYS_INT_PRUSS1_EVTOUT3                 (23)
#define SYS_INT_PRUSS1_EVTOUT4                 (24)
#define SYS_INT_PRUSS1_EVTOUT5                 (25)
#define SYS_INT_PRUSS1_EVTOUT6                 (26)
#define SYS_INT_PRUSS1_EVTOUT7                 (27)
#define SYS_INT_MMCSD1INT                      (28)
#define SYS_INT_MMCSD2INT                      (29)
#define SYS_INT_I2C2INT                        (30)
#define SYS_INT_eCAP0INT                       (31)
#define SYS_INT_GPIOINT2A                      (32)
#define SYS_INT_GPIOINT2B                      (33)
#define SYS_INT_USBWAKEUP                      (34)
#define SYS_INT_LCDCINT                        (36)
#define SYS_INT_GFXINT                         (37)
#define SYS_INT_2DHWAINT                       (38)
#define SYS_INT_ePWM2INT                       (39)
#define SYS_INT_3PGSWRXTHR0                    (40)
#define SYS_INT_3PGSWRXINT0                    (41)
#define SYS_INT_3PGSWTXINT0                    (42)
#define SYS_INT_3PGSWMISC0                     (43)
#define SYS_INT_UART3INT                       (44)
#define SYS_INT_UART4INT                       (45)
#define SYS_INT_UART5INT                       (46)
#define SYS_INT_eCAP1INT                       (47)
#define SYS_INT_DCAN0_INT0                     (52)
#define SYS_INT_DCAN0_INT1                     (53)
#define SYS_INT_DCAN0_PARITY                   (54)
#define SYS_INT_DCAN1_INT0                     (55)
#define SYS_INT_DCAN1_INT1                     (56)
#define SYS_INT_DCAN1_PARITY                   (57)
#define SYS_INT_ePWM0_TZINT                    (58)
#define SYS_INT_ePWM1_TZINT                    (59)
#define SYS_INT_ePWM2_TZINT                    (60)
#define SYS_INT_eCAP2INT                       (61)
#define SYS_INT_GPIOINT3A                      (62)
#define SYS_INT_GPIOINT3B                      (63)
#define SYS_INT_MMCSD0INT                      (64)
#define SYS_INT_SPI0INT                        (65)
#define SYS_INT_TINT0                          (66)
#define SYS_INT_TINT1_1MS                      (67)
#define SYS_INT_TINT2                          (68)
#define SYS_INT_TINT3                          (69)
#define SYS_INT_I2C0INT                        (70)
#define SYS_INT_I2C1INT                        (71)
#define SYS_INT_UART0INT                       (72)
#define SYS_INT_UART1INT                       (73)
#define SYS_INT_UART2INT                       (74)
#define SYS_INT_RTCINT                         (75)
#define SYS_INT_RTCALARMINT                    (76)
#define SYS_INT_MBINT0                         (77)
#define SYS_INT_M3_TXEV                        (78)
#define SYS_INT_eQEP0INT                       (79)
#define SYS_INT_MCATXINT0                      (80)
#define SYS_INT_MCARXINT0                      (81)
#define SYS_INT_MCATXINT1                      (82)
#define SYS_INT_MCARXINT1                      (83)
#define SYS_INT_ePWM0INT                       (86)
#define SYS_INT_ePWM1INT                       (87)
#define SYS_INT_eQEP1INT                       (88)
#define SYS_INT_eQEP2INT                       (89)
#define SYS_INT_DMA_INTR_PIN2                  (90)
#define SYS_INT_WDT1INT                        (91)
#define SYS_INT_TINT4                          (92)
#define SYS_INT_TINT5                          (93)
#define SYS_INT_TINT6                          (94)
#define SYS_INT_TINT7                          (95)
#define SYS_INT_GPIOINT0A                      (96)
#define SYS_INT_GPIOINT0B                      (97)
#define SYS_INT_GPIOINT1A                      (98)
#define SYS_INT_GPIOINT1B                      (99)
#define SYS_INT_GPMCINT                        (100)
#define SYS_INT_DDRERR0                        (101)
#define SYS_INT_AES0_IRQ_S                     (102)
#define SYS_INT_AES0_IRQ_P                     (103)
#define SYS_INT_SHA_IRQ_S                      (108)
#define SYS_INT_SHA_IRQ_P                      (109)
#define SYS_INT_FPKA_SINTREQUEST_S             (110)
#define SYS_INT_RNG_IRQ                        (111)
#define SYS_INT_TCERRINT0                      (112)
#define SYS_INT_TCERRINT1                      (113)
#define SYS_INT_TCERRINT2                      (114)
#define SYS_INT_SMRFLX_Sabertooth              (120)
#define SYS_INT_SMRFLX_Core                    (121)
#define SYS_INT_DMA_INTR_PIN0                  (123)
#define SYS_INT_DMA_INTR_PIN1                  (124)
#define SYS_INT_SPI1INT                        (125)

/*****************************************************************************
**                     TYPEDEF DEFINITIONS
*****************************************************************************/
typedef void (*IntrFuncPtr)(void *handle);

/*****************************************************************************
**                     API FUNCTION PROTOTYPES
*****************************************************************************/
extern void Intc_Init(void);
extern void IntIfClkFreeRunSet(void);
extern void IntIfClkAutoGateSet(void);
extern void IntProtectionEnable(void);
extern void IntProtectionDisable(void);
extern void IntSyncClkFreeRunSet(void);
extern void IntSyncClkAutoGateSet(void);
extern void IntFuncClkFreeRunSet(void);
extern void IntFuncClkAutoGateSet(void);
extern void IntPriorityThresholdSet(uint32_t threshold);
extern void IntSoftwareIntSet(uint32_t intrNum);
extern void IntSoftwareIntClear(uint32_t intrNum);
extern void IntMasterIRQEnable(void);
extern void IntMasterIRQDisable(void);
extern void IntMasterFIQEnable(void);
extern void IntMasterFIQDisable(void);
extern void Intc_SystemEnable(uint16_t intrNum);
extern void Intc_SystemDisable(uint16_t intrNum);
extern void Intc_IntUnregister(uint16_t intrNum);
extern void Intc_IntEnable(uint8_t status);
extern void Intc_IntRegister(uint16_t intrNum, IntrFuncPtr fptr, void *fun_arg);
extern void Intc_IntPrioritySet(uint16_t intrNum, uint16_t priority,
                                uint8_t hostIntRoute);

extern uint8_t Intc_IntDisable(void);
extern uint32_t IntMasterStatusGet(void);
extern uint32_t IntActiveIrqNumGet(void);
extern uint32_t IntActiveFiqNumGet(void);
extern uint32_t IntSpurIrqFlagGet(void);
extern uint32_t IntSpurFiqFlagGet(void);
extern uint32_t IntCurrIrqPriorityGet(void);
extern uint32_t IntCurrFiqPriorityGet(void);
extern uint32_t IntPriorityThresholdGet(void);
extern uint32_t IntRawStatusGet(uint32_t intrNum);
extern uint32_t IntPendingIrqMaskedStatusGet(uint32_t intrNum);
extern uint32_t IntPendingFiqMaskedStatusGet(uint32_t intrNum);

#ifdef __cplusplus
}
#endif
#endif
