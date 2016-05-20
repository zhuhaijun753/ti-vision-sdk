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
#include "soc.h"
#include "spinlock.h"
#include "soc_defines.h"
#include "uartStdio.h"
#include "platform.h"

#define MAX_NUM_SPINLOCKS       (256U)

int main()
{
    uint32_t status = 0, lock_num = 0;

    #ifdef BUILD_A15
    char     coreName[10] = {"A15"};
    #elif defined (BUILD_M4)
    char     coreName[10] = {"M4"};
    #elif defined (BUILD_DSP)
    char     coreName[10] = {"DSP"};
    #endif

    PlatformUartConsoleSetPinMux();

    UARTStdioInit();
    UARTPuts("\nOn ", -1);
    UARTPuts(coreName, -1);

    for (lock_num = 0; lock_num < MAX_NUM_SPINLOCKS; lock_num++)
    {
        status = SPINLOCKLockStatusSet(SOC_SPINLOCK_BASE, lock_num);
        if (status == 0)
        {
            UARTPuts("\n", -1);
            UARTPuts(coreName, -1);
            UARTPuts(" acquired lock number:", -1);
            UARTPutNum(lock_num);
        }
        else if (status == 1)
        {
            UARTPuts("\n", -1);
            UARTPuts(coreName, -1);
            UARTPuts(" could not acquire lock number:", -1);
            UARTPutNum(lock_num);
            UARTPuts(", lock is not free", -1);
        }
    }
    return 0;
}

