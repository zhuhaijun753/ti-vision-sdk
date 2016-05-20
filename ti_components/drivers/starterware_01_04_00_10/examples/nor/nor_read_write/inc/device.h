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

#ifndef DEVICE_H_
#define DEVICE_H_

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************
 * Global Macro Declarations                                *
 ***********************************************************/
/* GPMC MMR */
#define GPMC_BASE                     0x50000000
#define GPMC_SYSCONFIG_OFF            0x10
#define GPMC_IRQSTS_OFF               0x18
#define GPMC_IRQENABLE_OFF            0x1c
#define GPMC_TIMEOUTCTRL_OFF          0x40
#define GPMC_CONFIG_OFF               0x50
#define GPMC_CONFIG_CS0_BASE          (GPMC_BASE + 0x60)
#define GPMC_CS_CONFIG_SIZE           0x30
#define GPMC_MAX_CS                   7

#define GPMC_CONFIG1_OFF              0x00
#define GPMC_CONFIG2_OFF              0x04
#define GPMC_CONFIG3_OFF              0x08
#define GPMC_CONFIG4_OFF              0x0C
#define GPMC_CONFIG5_OFF              0x10
#define GPMC_CONFIG6_OFF              0x14
#define GPMC_CONFIG7_OFF              0x18

/* NOR Base address */
#define NOR_BASE                      0x08000000

/* GPMC Chip Select configuration passed to gpmc_SetCSConfig */
typedef struct {
    uint32_t Config1;
    uint32_t Config2;
    uint32_t Config3;
    uint32_t Config4;
    uint32_t Config5;
    uint32_t Config6;
    uint32_t Config7;
} GPMC_CsConfig_t;

/* GPMC Configuration passed to GPMC_SetConfig in order to configure the GPMC
 * The structure is also used by the CHFLASH Configuration Header */
typedef struct
{
    uint32_t SysConfig;
    uint32_t IrqEnable;
    uint32_t TimeOutControl;
    uint32_t Config;
    uint32_t ChipSelectConfig[GPMC_MAX_CS];
    uint32_t PrefetchConfig1;
    uint32_t PrefetchConfig2;
    uint32_t PrefetchControl;
}GPMC_Config_t;

void GPMC_Init(GPMC_Config_t *cfg, uint8_t cs);

#ifdef __cplusplus
}
#endif

#endif
