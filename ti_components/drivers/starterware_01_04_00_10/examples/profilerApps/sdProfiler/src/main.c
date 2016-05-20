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
 *   Component:      examples\profiler_apps
 *
 *   Filename:           main.c
 *
 *   Description:    Profiler app to profile the data throughput of SD driver.
 *
 */

/****************************************************************
 *  INCLUDE FILES
 ****************************************************************/
#include <stdint.h>
#include "hw_ctrl_core_pad.h"
#include "uartStdio.h"
#include "soc_defines.h"
#include "hsmmcsd_API.h"
#include "platform.h"
#include "soc.h"
#include "hw_types.h"
#include "edma.h"
#include "cp15.h"
#include <common/stw_dataTypes.h>
#include <osal/bsp_osal.h>

#define BUFFER_SIZE  (0x10000)
#define DEST_BUFF     (uint8_t *) (0x80600000)

/* ============================================================================
 * GLOBAL VARIABLES DECLARATIONS
 * =============================================================================
 */

/* ============================================================================
 * LOCAL VARIABLES DECLARATIONS
 * =============================================================================
 */

/* ============================================================================
 * LOCAL FUNCTIONS PROTOTYPES
 * =============================================================================
 */

/* ============================================================================
 * FUNCTIONS
 * =============================================================================
 */
int main(void)
{
    char    *filename = "TestFile";
    FIL      fp;
    FRESULT  fresult;
    uint32_t bytes_read = 0;
    uint32_t Max_read   = BUFFER_SIZE - 1;
    uint8_t *buffptr    = DEST_BUFF;
    uint32_t start_time, end_time;
    uint32_t fileSize = 0;

    BspOsal_cacheEnable(BSP_OSAL_CT_ALL);

    UARTStdioInit();
    UARTPuts("\n SD profiler..", -1);

    /*PMU Clock counter reset*/
    ARM_CCNT_Enable();

    /* EDMA3 Init */
    EDMAsetRegion(0);
    EDMA3Init(SOC_EDMA_TPCC_BASE, 0);

    HSMMCSDInit(MMC1_INST);

    UARTPuts("\n SD Card Init Done. \n", -1);

    fresult = f_open(&fp, filename, FA_READ);
    if (fresult != FR_OK)
    {
        UARTPuts("\n File open error \n", -1);
        while (1) ;
    }

    start_time = ARM_CCNT_Read();

    do
    {
        /*Read the bytes from the SD card*/
        fresult = f_read(&fp, buffptr, Max_read, (UINT *) &bytes_read);
        if (fresult != FR_OK)
        {
            UARTPuts("\t ERROR: File read failed.. Closing program.\r\n", -1);
            while (1) ;
        }
        fileSize += bytes_read;
        buffptr  += bytes_read;
    } while (bytes_read != 0);

    end_time = ARM_CCNT_Read();

    f_close(&fp);

    UARTprintf("\n Number of bytes read from sd card: %u", fileSize);
    UARTprintf("\n SD data copy - cpu cycles - %u\n", end_time - start_time);

    UARTprintf(
        " \n PMCCNTR counts once every 64 clock cycles. To get actual CPU cycle multiple by 64\n");

    {volatile int spin = 1; while (spin) ; }

    return 0;
}

/***************************** End Of File ***********************************/

