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
 *   Component:      examples
 *
 *   Filename:           main.c
 *
 *   Description:    Test application for MMCSD & FAT Filesystem. Open an file
 *                   & read the content & send to UARTConsole
 *
 */

/****************************************************************
 *  INCLUDE FILES
 ****************************************************************/
#include <stdint.h>
#include "hw_ctrl_core_pad.h"
#include "soc_defines.h"
#include "uartConsole.h"
#include "hsmmcsd_API.h"
#include "uartStdio.h"
#include "platform.h"
#include "soc.h"
#include "hw_types.h"
#include  "hw_l3init_cm_core.h"
#include "hw_l4per_cm_core.h"
#include "edma.h"

#ifdef TDA2XX_FAMILY_BUILD
#include "pmhal_prcm.h"
#include "pm/pmhal/pmhal_mm.h"
#endif
#include <common/stw_types.h>
#include <common/stw_config.h>
#include <common/stw_utils.h>
#include "i2clib/lld_hsi2c.h"
#include "boards/stw_board.h"
#include "devices/stw_device.h"
#include "stwutils_app.h"
#include <common/stw_dataTypes.h>
#include <osal/bsp_osal.h>

/******************************************************************************
**                      INTERNAL MACRO DEFINITIONS
*******************************************************************************/
#define IO_EXPANDER_SA (0x21)

#define BASE_BOARD     ('1')
#define JAMR3_BOARD    ('2')
#define EXIT(opt)      (('x' == opt) || ('X' == opt))

/******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
*******************************************************************************/
signed char _srcBuffm[] =
    "Testing File read/write functions on SD CARD... ";

/******************************************************************************
**                      INTERNAL FUNCTION PROTOTYPES
*******************************************************************************/
#ifdef TDA2XX_FAMILY_BUILD
void MMCSD_LDO_PWR(void);
void mmc1PinMux(void);
void mmc3PinMux(void);
void mainMenu(char *option);
#endif

void delay(uint32_t delay);

void fileIoTest(void);
void mmc4PinMux(void);

/******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/
int main(void)
{
#ifdef TDA2XX_FAMILY_BUILD
    char                 mainMenuOption;
#endif
    volatile int8_t      appDone = 1U;
    stwAppInitParams_t   stwAppInitParams;
    int32_t              retVal;
    stwAppDeInitParams_t stwAppDeInitParams;

    BspOsal_cacheEnable(BSP_OSAL_CT_ALL);

    stwAppInitParams.isI2cInitReq  = TRUE;
    stwAppInitParams.isUartInitReq = TRUE;
    retVal = StwUtils_appDefaultInit(stwAppInitParams);
    if (retVal != STW_SOK)
    {
        console_print_string("\nSystem Init Failed ");
    }

    /* EDMA3 Init */
    EDMAsetRegion(0);
    EDMA3Init(SOC_EDMA_TPCC_BASE, 0);

#if (defined (TDA2XX_FAMILY_BUILD))
    mainMenu(&mainMenuOption);

    if (BASE_BOARD == mainMenuOption)
    {
        mmc1PinMux();

        HSMMCSDInit(MMC1_INST);

        UARTPuts("\n SD Card Init Done. \n", -1);

        fileIoTest();
    }
    else if (JAMR3_BOARD == mainMenuOption)
    {
        mmc3PinMux();

        HSMMCSDInit(MMC3_INST);

        UARTPuts("\n SD Card Init Done. \n", -1);

        fileIoTest();
    }
    else
    {
        UARTPuts("\nSD Card Init not done. Not a valid main menu option \n", -1);
    }
#elif (defined (TDA3XX_FAMILY_BUILD))
    mmc4PinMux();

    HSMMCSDInit(MMC4_INST);

    UARTPuts("\n SD Card Init Done. \n", -1);

    fileIoTest();
#endif

    UARTPuts("\nSD CARD FILE IO board diagnostic test exiting...", -1);

    /* System De init */
    stwAppDeInitParams.isI2cDeInitReq = TRUE;
    retVal = StwUtils_appDefaultDeInit(stwAppDeInitParams);
    if (retVal != STW_SOK)
    {
        console_print_string("\nSystem DeInit Failed ");
    }

    while (appDone) ;

    return 0;
}

void fileIoTest(void)
{
    char       *filename = "TestFile";
    FIL         fp;
    FRESULT     fresult;
    UINT        bytes_read = 0;
    uint32_t    Max_read   = sizeof (_srcBuffm);
    char        buffptr[sizeof (_srcBuffm)];
    uint32_t    loopcount = 1000U, cnt;

    fresult = f_open(&fp, filename, FA_WRITE);
    if (fresult != FR_OK)
    {
        /*If file does not exist. Create new one*/
        fresult = f_open(&fp, filename, FA_CREATE_NEW);
        if (fresult != FR_OK)
        {
            UARTPuts("\n File create error \n", -1);
            while (1) ;
        }
        else
        {
            f_close(&fp);
            /*Open handle to the newly created file*/
            fresult = f_open(&fp, filename, FA_WRITE);
        }
    }

    cnt = 0U;
    while (cnt < loopcount)
    {
        fresult = f_write(&fp, &_srcBuffm, sizeof (_srcBuffm), &bytes_read);
        if (fresult != FR_OK)
        {
            UARTPuts("\n File write error \n", -1);
            while (1) ;
        }
        cnt++;
    }
    f_close(&fp);

    fresult = f_open(&fp, filename, FA_READ);
    if (fresult != FR_OK)
    {
        UARTPuts("\n File open error \n", -1);
        while (1) ;
    }

    cnt = 0U;
    while (cnt < loopcount)
    {
        fresult = f_read(&fp, (void *) buffptr, Max_read, (UINT *) &bytes_read);
        if (fresult != FR_OK)
        {
            UARTPuts("\n File read error \n", -1);
            while (1) ;
        }
        if (memcmp(buffptr, _srcBuffm, bytes_read) != 0)
        {
            UARTPuts("\n Data mismatch!!\n", -1);
            while (1) ;
        }
        cnt++;
    }
    f_close(&fp);

    /*print the file content*/
    UARTPuts(buffptr, bytes_read);

    UARTPuts("\n FILEIO testapp completed successfully \n", -1);
}

#ifdef TDA2XX_FAMILY_BUILD
void mmc1PinMux()
{
    uint32_t tmpRegVal;
    /*MMC1- CM_L3INIT_MMC1_CLKCTRL */
    tmpRegVal  = HW_RD_REG32(SOC_L3INIT_CM_CORE_BASE + CM_L3INIT_MMC1_CLKCTRL);
    tmpRegVal |= 0x03000000;
    HW_WR_REG32(SOC_L3INIT_CM_CORE_BASE + CM_L3INIT_MMC1_CLKCTRL, tmpRegVal);

    /*Enable the module - mmc1  */
    PMHALModuleModeSet(PMHAL_PRCM_MOD_MMC1, PMHAL_PRCM_MODULE_MODE_ENABLED,
                       PM_TIMEOUT_INFINITE);
    MMCSD_LDO_PWR();

    /*MMC1 PAD Configuration*/
    PlatformMMCSD1SetPinMux();
}

void mmc3PinMux()
{
    uint32_t tmpRegVal;
    /*MMC3- CM_L4INIT_MMC3_CLKCTRL */
    tmpRegVal  = HW_RD_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_MMC3_CLKCTRL);
    tmpRegVal |= 0x02000000;
    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_MMC3_CLKCTRL, tmpRegVal);

    /*Enable the module - mmc3  */
    PMHALModuleModeSet(PMHAL_PRCM_MOD_MMC3, PMHAL_PRCM_MODULE_MODE_ENABLED,
                       PM_TIMEOUT_INFINITE);

    /*MMC3 PAD Configuration*/
    PlatformMMCSD3SetPinMux();

    HSMMCSDInit(MMC3_INST);
}

void mainMenu(char *option)
{
    while (1)
    {
        UARTPuts("\n\n**** SD CARD FILE IO TEST ****", -1);
        UARTPuts("\nMenu:", -1);
        UARTPuts("\n1. Base  board SD CARD", -1);
        UARTPuts("\n2. JAMR3 board SD CARD", -1);
        UARTPuts("\nx. Exit", -1);
        UARTPuts("\nSelect test board : ", -1);

        /* Get option */
        UARTGets(option, 1);

        if (BASE_BOARD == *option || JAMR3_BOARD == *option
            || EXIT(*option))
        {
            break;
        }
        else
        {
            UARTPuts("\nEnter Valid option\n", -1);
        }
    }
}

#endif

void delay(uint32_t delay)
{
    volatile uint32_t i;
    for (i = 0; i < (1000 * delay); ++i) ;
}

#ifdef TDA2XX_FAMILY_BUILD
void   MMCSD_LDO_PWR()
{
    /*CTRL_CORE_CONTROL_PBIAS*/

    uint32_t reg_val = 0;

    reg_val = HW_RD_REG32(
        SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE + CTRL_CORE_CONTROL_PBIAS);

    reg_val &= ~CTRL_CORE_CONTROL_PBIAS_SDCARD_IO_PWRDNZ_MASK;
    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                CTRL_CORE_CONTROL_PBIAS, reg_val);
    delay(10); /* wait 10 us */
    reg_val &= ~CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_PWRDNZ_MASK;
    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                CTRL_CORE_CONTROL_PBIAS, reg_val);

    /*Enable SDCARD_BIAS_VMODE*/
    reg_val |= CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_VMODE_MASK; /* 3v */
    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                CTRL_CORE_CONTROL_PBIAS, reg_val);

    reg_val = HW_RD_REG32(
        SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE + CTRL_CORE_CONTROL_PBIAS);
    reg_val |= CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_PWRDNZ_MASK;
    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                CTRL_CORE_CONTROL_PBIAS, reg_val);
    delay(150); /* wait 10 us */

    reg_val |= CTRL_CORE_CONTROL_PBIAS_SDCARD_IO_PWRDNZ_MASK;
    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                CTRL_CORE_CONTROL_PBIAS, reg_val);

    delay(150); /* wait 10 us */
}

#endif

#ifdef TDA3XX_FAMILY_BUILD

void mmc4PinMux()
{
    uint32_t tmpRegVal;
    /*MMC4- CM_L4INIT_MMC4_CLKCTRL */
    tmpRegVal  = HW_RD_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_MMC4_CLKCTRL);
    tmpRegVal |= 0x02000000;
    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_MMC4_CLKCTRL, tmpRegVal);

    /*MMC4 PRCM config*/
    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_MMC4_CLKCTRL, 0x2);

    /*MMC4 PAD Configuration*/
    PlatformMMCSD4SetPinMux();

    /*Todo IOExpander mux config : Mux F : MMC4*/
    BOARDSelectDevice(DEVICE_ID_MMC, DEVICE_MMC_INST_ID_4);
}

#endif
/***************************** End Of File ***********************************/

