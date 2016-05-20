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

/*
 * \file     mailbox.h
 *
 * \brief    This file contains the function prototypes for Mail box access
 */

#ifndef      __TI814x_EVMDEF_H__
#define      __TI814x_EVMDEF_H__

#ifdef __cplusplus
extern "C" {
#endif

#define PADCTRL_BASE 0x48140000
/** @brief Base address of UART memory mapped registers                       */
#define SOC_UART_0_REGS                     (0x48020000U)
#define SOC_UART_1_REGS                     (0x48022000U)

#define UART_BASE                SOC_UART_0_REGS

#define BAUD_RATE_115200          (115200U)
#define UART_MODULE_INPUT_CLK     (48000000U)

#define UART_LCR_NB_STOP_1BIT   (0x0U)
#define UART_LCR_CHAR_LENGTH_8BIT   (0x3U)

/*UART 0*/
#define	PAD69_CNTRL (*(volatile uint32_t *)(PADCTRL_BASE +0x0910))
#define	PAD70_CNTRL (*(volatile uint32_t *)(PADCTRL_BASE +0x0914))  //PINCTRL_UART0_RXD
#define	PAD71_CNTRL (*(volatile uint32_t *)(PADCTRL_BASE +0x0918)) //PINCTRL_UART0_TXD
#define	PAD72_CNTRL (*(volatile uint32_t *)(PADCTRL_BASE +0x091C))  //PINCTRL_UART0_CTSn
#define PAD73_CNTRL (*(volatile uint32_t *)(PADCTRL_BASE +0x0920))  //PINCTRL_UART0_RTSn

#ifdef __cplusplus
}
#endif

#endif
