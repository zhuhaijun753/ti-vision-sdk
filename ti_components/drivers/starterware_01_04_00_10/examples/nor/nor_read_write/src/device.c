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

#include "stdint.h"
#include "device.h"

#define MAX_DELAY   0x900

void UTIL_waitLoop(uint32_t loopcnt)
{
    uint32_t i;
    for (i = 0; i < loopcnt; i++)
    {
        asm ("   NOP");
    }
}

void GPMC_Write(uint32_t offset, uint32_t val)
{
    *(volatile uint32_t *) (GPMC_BASE + offset) = val;
}

void GPMC_CSWrite(uint8_t cs, uint32_t offset, uint32_t val)
{
    *(volatile uint32_t *) (GPMC_CONFIG_CS0_BASE +
                            (GPMC_CS_CONFIG_SIZE * cs) + offset) = val;
}

uint32_t GPMC_Read(uint32_t offset)
{
    return (*(volatile uint32_t *) (GPMC_BASE + offset));
}

/* make sure compiler doesnt optimize this function */
uint32_t DEVICE_Delay(uint32_t delay)
{
    UTIL_waitLoop(delay * 0x100);
    return 0;
}

/*********************************************************************
 *
 * GPMC_Init - Initialize GPMC based on CS and config values
 *
 *********************************************************************/
void GPMC_Init(GPMC_Config_t *cfg, uint8_t cs)
{
    uint8_t i;

    /* program global GPMC regs */
    GPMC_Write(GPMC_SYSCONFIG_OFF, cfg->SysConfig);
    GPMC_Write(GPMC_IRQENABLE_OFF, cfg->IrqEnable);
    GPMC_Write(GPMC_TIMEOUTCTRL_OFF, cfg->TimeOutControl);
    GPMC_Write(GPMC_CONFIG_OFF, cfg->Config);

    /* program GPMC CS specific registers */
    /* disable cs */
    GPMC_CSWrite(cs, GPMC_CONFIG7_OFF, 0x00000000);
    DEVICE_Delay(MAX_DELAY);

    /* program new set of config values (1 to 7) */
    for (i = 0; i < GPMC_MAX_CS; i++) {
        GPMC_CSWrite(cs, (i * 4), cfg->ChipSelectConfig[i]);
    }

    /* enable cs */
    GPMC_CSWrite(cs, GPMC_CONFIG7_OFF, (cfg->ChipSelectConfig[6] | 0x40));
    DEVICE_Delay(MAX_DELAY);
}

