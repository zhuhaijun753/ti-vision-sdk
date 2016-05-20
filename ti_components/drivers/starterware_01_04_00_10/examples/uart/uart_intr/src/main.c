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
 * main.c
 */

#include "stdint.h"
#include "stdio.h"
#include "soc_defines.h"
#include "uartConfig.h"
#include "soc.h"
#include "interrupt.h"
#include "irq_xbar.h"
#include "hw_types.h"
#include "platform.h"
#include <common/stw_dataTypes.h>
#include <common/stw_types.h>
#include "i2clib/lld_hsi2c.h"
#include "boards/stw_board.h"
#include "platforms/stw_platform.h"
#include "devices/stw_device.h"
#include "stw_boardPriv.h"
#include "pmhal_prcm.h"
#include "pm/pmhal/pmhal_mm.h"

/******************************************************************************
**              INTERNAL MACRO DEFINITIONS
******************************************************************************/
#if defined (TDA2XX_FAMILY_BUILD)
#define UART_INT_ID             (44U)
#elif defined (TDA3XX_FAMILY_BUILD)
#define UART_INT_ID             (45U)
#endif

/******************************************************************************
**              INTERNAL FUNCTION PROTOTYPES
******************************************************************************/
static void UartInterruptEnable(void);
static void UartINTCConfigure(void);
static void UartFIFOConfigure(void);
static void UartBaudRateSet(void);
static void UARTIsr(void *handle);

/******************************************************************************
**              GLOBAL VARIABLE DEFINITIONS
******************************************************************************/
unsigned char txArray[] = "StarterWare UART Interrupt application\n\r";
uint32_t      uartBaseAddr;

/******************************************************************************
**              FUNCTION DEFINITIONS
******************************************************************************/

int main()
{
    uint32_t uartInstId;
    pmhalPrcmModuleId_t pmModInstId;
    int32_t  retVal = STW_SOK;
    volatile uint32_t loopVar = 1U;

    uartInstId   = 1;
    uartBaseAddr = SOC_UART1_BASE;
    pmModInstId  = PMHAL_PRCM_MOD_UART1;

#if defined (TDA3XX_FAMILY_BUILD)
    uartInstId   = 3;
    uartBaseAddr = SOC_UART3_BASE;
    pmModInstId  = PMHAL_PRCM_MOD_UART3;
#endif

    /*Enable the module - uart*/
    retVal = PMHALModuleModeSet(pmModInstId,
                                PMHAL_PRCM_MODULE_MODE_ENABLED,
                                PM_TIMEOUT_INFINITE);
    if (retVal != PM_SUCCESS)
    {
        return STW_EFAIL;
    }
    else
    {
        retVal = STW_SOK;
    }

    /* PinMux Configuration for UART*/
    BOARDConfigConsolePinMux(uartInstId);

    /* Performing a module reset. */
    UARTModuleReset(uartBaseAddr);

    /* Performing FIFO configurations. */
    UartFIFOConfigure();

    /* Performing Baud Rate settings. */
    UartBaudRateSet();

    /* Switching to Configuration Mode B. */
    UARTRegConfigModeEnable(uartBaseAddr, UART_REG_CONFIG_MODE_B);

    /* Programming the Line Characteristics. */
    UARTLineCharacConfig(uartBaseAddr,
                         (UART_FRAME_WORD_LENGTH_8 | UART_FRAME_NUM_STB_1),
                         UART_PARITY_NONE);

    /* Disabling write access to Divisor Latches. */
    UARTDivisorLatchDisable(uartBaseAddr);

    /* Disabling Break Control. */
    UARTBreakCtl(uartBaseAddr, UART_BREAK_COND_DISABLE);

    /* Switching to UART16x operating mode. */
    UARTOperatingModeSelect(uartBaseAddr, UART16x_OPER_MODE);

    /* Performing Interrupt configurations. */
    UartInterruptEnable();

    while(loopVar == 1U);
    return retVal;
}

/*
** A wrapper function performing FIFO configurations.
*/

static void UartFIFOConfigure(void)
{
    uint32_t fifoConfig = 0;

    /* Setting the TX and RX FIFO Trigger levels as 1. No DMA enabled. */
    fifoConfig = UART_FIFO_CONFIG(UART_TRIG_LVL_GRANULARITY_1,
                                  UART_TRIG_LVL_GRANULARITY_1,
                                  1,
                                  1,
                                  1,
                                  1,
                                  UART_DMA_EN_PATH_SCR,
                                  UART_DMA_MODE_0_ENABLE);

    /* Configuring the FIFO settings. */
    UARTFIFOConfig(uartBaseAddr, fifoConfig);
}

/*
** A wrapper function performing Baud Rate settings.
*/

static void UartBaudRateSet(void)
{
    uint32_t divisorValue = 0;

    /* Computing the Divisor Value. */
    divisorValue = UARTDivisorValCompute(UART_MODULE_INPUT_CLK,
                                         BAUD_RATE_115200,
                                         UART16x_OPER_MODE,
                                         UART_MIR_OVERSAMPLING_RATE_42);

    /* Programming the Divisor Latches. */
    UARTDivisorLatchWrite(uartBaseAddr, divisorValue);
}

/*
** A wrapper function performing Interrupt configurations.
*/

static void UartInterruptEnable(void)
{
    /* Configuring INTC to receive UART interrupts. */
    UartINTCConfigure();

    /* Enabling the specified UART interrupts. */
    UARTIntEnable(uartBaseAddr, (UART_INT_LINE_STAT | UART_INT_THR |
                                 UART_INT_RHR_CTI));
}

/*
** Interrupt Service Routine for UART.
*/

static void UARTIsr(void *handle)
{
    static uint32_t txStrLength = sizeof (txArray);
    static uint32_t count       = 0;
    unsigned char   rxByte      = 0;
    uint32_t        intId       = 0;

    /* Checking ths source of UART interrupt. */
    intId = UARTIntIdentityGet(uartBaseAddr);

    switch (intId)
    {
        case UART_INTID_TX_THRES_REACH:

            if (0 != txStrLength)
            {
                UARTCharPut(uartBaseAddr, txArray[count]);
                txStrLength--;
                count++;
            }
            else
            {
                /* Disabling the THR interrupt. */
                UARTIntDisable(uartBaseAddr, UART_INT_THR);
            }

            break;

        case UART_INTID_RX_THRES_REACH:
            rxByte = UARTCharGetNonBlocking(uartBaseAddr);
            UARTCharPutNonBlocking(uartBaseAddr, rxByte);
            break;

        case UART_INTID_RX_LINE_STAT_ERROR:
        case UART_INTID_CHAR_TIMEOUT:
            UARTCharGetNonBlocking(uartBaseAddr);
            break;

        default:
            break;
    }
}

/*
** This function configures the INTC to receive UART interrupts.
*/

static void UartINTCConfigure(void)
{
    /* Unlock Pad Config Registers */
    PLATFORMUnLockRegion(PLATFORM_MMR_REG_2);
#if defined (TDA2XX_FAMILY_BUILD)
    /* Crossbar registers are already unlocked, so connect directly */
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_IPU1, 22,
                   UART1_IRQ);
#elif defined (TDA3XX_FAMILY_BUILD)
    /* Crossbar registers are already unlocked, so connect directly */
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_IPU1, 23,
                   UART3_IRQ);
#endif
    /* Lock Pad Config Registers */
    PLATFORMLockRegion(PLATFORM_MMR_REG_2);

    /* Initializing the Interrupt Controller. */
    Intc_Init();

    /* Enable the interrupt */
    Intc_IntEnable(0);

    /* Registering the Interrupt Service Routine(ISR). */
    Intc_IntRegister(UART_INT_ID, (IntrFuncPtr) UARTIsr, NULL);

    /* Setting the priority for the UART interrupt in INTC. */
    Intc_IntPrioritySet(UART_INT_ID, 1, 0);

    /* Enabling the UART interrupt in INTC. */
    Intc_SystemEnable(UART_INT_ID);
}

/******************************* End of file *********************************/
