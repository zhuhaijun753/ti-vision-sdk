/*
 * TI Booting and Flashing Utilities
 *
 * Provides device differentiation for the project files. This file MUST
 * be modified to match the device specifics.
 *
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

/* --------------------------------------------------------------------------
  AUTHOR      : Daniel Allred
 --------------------------------------------------------------------------- */

#ifndef DEVICE_H_
#define DEVICE_H_

#include "tistdtypes.h"

// Prevent C++ name mangling
#ifdef __cplusplus
extern far "c" {
#endif

/***********************************************************
* Global Macro Declarations                                *
***********************************************************/

#ifndef USE_DDR_HEAP
/* using ocmc0 for custom heap (and not ccs heap) */
#define SRAM_HEAP_START 0x40300000
#define SRAM_HEAP_SIZE	(200 * 1024)
#define DEVICE_DDR2_RAM_END	(SRAM_HEAP_START + SRAM_HEAP_SIZE)
#define DEVICE_DDR2_START_ADDR	(SRAM_HEAP_START)
#else
/* using DDR for custom heap */
#define DDR_HEAP_START 0x90000000
#define DDR_HEAP_SIZE	(64 * 1024 * 1024)
#define DEVICE_DDR2_RAM_END	(DDR_HEAP_START + DDR_HEAP_SIZE)
#define DEVICE_DDR2_START_ADDR	(DDR_HEAP_START)
#endif

/* Control Module MMR */
#define CM_BASE						0x48180000
#define CM_ALWON_MOD_OFF			0x1400  /* 1KB */
#define CM_ALWON_GPMC_CLKCTRL_OFF 	0x1D0
/* PRCM Bits */
#define MODULEMODE_SWCTRL			0x2


/* GPMC MMR
 */
#define GPMC_BASE				0x50000000
#define GPMC_SYSCONFIG_OFF		0x10
#define GPMC_IRQSTS_OFF			0x18
#define GPMC_IRQENABLE_OFF		0x1c
#define GPMC_TIMEOUTCTRL_OFF	0x40
#define GPMC_CONFIG_OFF			0x50
#define GPMC_CONFIG_CS0_BASE    (GPMC_BASE + 0x60)
#define GPMC_CS_CONFIG_SIZE		0x30
#define GPMC_MAX_CS				7

#define GPMC_CONFIG1_OFF		0x00
#define GPMC_CONFIG2_OFF		0x04
#define GPMC_CONFIG3_OFF		0x08
#define GPMC_CONFIG4_OFF		0x0C
#define GPMC_CONFIG5_OFF		0x10
#define GPMC_CONFIG6_OFF		0x14
#define GPMC_CONFIG7_OFF		0x18


/**** PAD CFG MMR */
#define CFG_MOD_BASE	0x48140000
#define TIM7_OUT_OFF    (0xb34)  /* a12 */
#define UART1_CTSN_OFF  (0xadc)  /* a13 */
#define UART1_RTSN_OFF  (0xad8)  /* a14 */
#define UART2_RTSN_OFF  (0xae8)  /* a15 */
#define SC1_RST_OFF     (0xb10)  /* a15 */
#define UART2_CTSN_OFF  (0xaec)  /* a16 */
#define UART0_RIN_OFF   (0xacc)  /* a17 */
#define UART0_DCDN_OFF  (0xac8)  /* a18 */
#define UART0_DSRN_OFF  (0xac4)  /* a19 */
#define UART0_DTRN_OFF  (0xac0)  /* a20 */
#define SPI_SCS3_OFF    (0xaa4)  /* a21 */
#define SPI_SC2_OFF     (0xaa0)  /* a22 */
#define GPO_IO6_OFF     (0xca0)  /* a23 */
#define TIM6_OUT_OFF    (0xb30)  /* a24 */
#define SC0_DATA_OFF    (0xafc)  /* a25 */
#define GPMC_A27_OFF    (0xba0)  /* a27 */

#define GPMC_PAD_DEF	(0x1)

#define GPIO0_PRCM		(0x4818155c)
#define GPIO1_PRCM		(0x48181560)
#define GPIO6_A			(0x4803213c)
#define GPIO6_B			(0x48032134)

/*** TI814X ****/
#define GPIO1_REG               (0x4804C000)

/****NOR PAD CONFIG *****/
#define GPMC_D0                 0x0960
#define GPMC_D1                 0x0964
#define GPMC_D2                 0x0968
#define GPMC_D3                 0x096C
#define GPMC_D4                 0x0970
#define GPMC_D5                 0x0974
#define GPMC_D6                 0x0978
#define GPMC_D7                 0x097C
#define GPMC_D8                 0x0980
#define GPMC_D9                 0x0984
#define GPMC_D10                0x0988
#define GPMC_D11                0x098C
#define GPMC_D12                0x0990
#define GPMC_D13                0x0994
#define GPMC_D14                0x0998
#define GPMC_D15                0x099C

#define GPMC_A1                 0x09D0
#define GPMC_A2                 0x09D4
#define GPMC_A3                 0x09D8
#define GPMC_A4                 0x09DC
#define GPMC_A5                 0x0A9C
#define GPMC_A6                 0x0AA0
#define GPMC_A7                 0x0AA4
#define GPMC_A8                 0x0AA8
#define GPMC_A9                 0x0AAC
#define GPMC_A10                0x0AB0
#define GPMC_A11                0x0AB4
#define GPMC_A12                0x0AB8
#define GPMC_A13                0x0B8C
#define GPMC_A14                0x0B90
#define GPMC_A15                0x0B94
#define GPMC_A16                0x09A0
#define GPMC_A17                0x09A4
#define GPMC_A18                0x09A8
#define GPMC_A19                0x09AC
#define GPMC_A20                0x09B0
#define GPMC_A21                0x09B4
#define GPMC_A22                0x09B8
#define GPMC_A23                0x09BC
#define GPMC_A24                0x09EC
#define GPMC_A25                0x09E8

#define GPMC_A27                0x09CC
#define GPMC_CS0_REG            0x09E4
#define GPMC_OEN                0x0A00
#define GPMC_WEN                0x0A04

/*------------------------------------------------------------------------------
 * @DEFINITION SET_FIELD
 *
 * @BRIEF      Shift and Mask the variable; takes the variable and bit-field
 *             as parameters; the whole input variable gets modified.
 *             This is size independent macro - use proper type for the variable
 *----------------------------------------------------------------------------*/
#define SET_FIELD(VAR, FIELD)    ((VAR << FIELD##__POS) & FIELD)

/* GPMC register base */

/* GPMC Chip Select configuration passed to gpmc_SetCSConfig */
typedef struct {
    Uint32 Config1;
    Uint32 Config2;
    Uint32 Config3;
    Uint32 Config4;
    Uint32 Config5;
    Uint32 Config6;
    Uint32 Config7;
} GPMC_CsConfig_t;

/* GPMC Configuration passed to GPMC_SetConfig in order to configure the GPMC
 * The structure is also used by the CHFLASH Configuration Header */
typedef struct
{
    Uint32 SysConfig;
    Uint32 IrqEnable;
    Uint32 TimeOutControl;
    Uint32 Config;
    Uint32 ChipSelectConfig[GPMC_MAX_CS];
    Uint32 PrefetchConfig1;
    Uint32 PrefetchConfig2;
    Uint32 PrefetchControl;
#ifdef NAND_SUPPORT
    Uint32 EccConfig;
    Uint32 EccControl;
    Uint32 EccSizeConfig;
#endif
}GPMC_Config_t;

void PAD_ConfigMux( Uint32 *addr, Uint32 val);
void GPMC_Init(GPMC_Config_t *cfg, Int8 cs);

#ifdef __cplusplus
}
#endif

#endif /* End DEVICE_H_ */

/***********************************************************
* End file                                                 *
***********************************************************/


/* --------------------------------------------------------------------------
    HISTORY
       v1.00  -  DJA  -  07-Nov-2007
         Initial Release
 ----------------------------------------------------------------------------- */


