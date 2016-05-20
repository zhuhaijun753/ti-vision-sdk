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
#include <stdio.h>
#include "gpmc.h"
#include "soc.h"
#include "soc_defines.h"
#include "platform.h"
#include "util.h"
#include "hw_types.h"
#include "uartStdio.h"

#define BURST_MODE 0
#define MAX_DELAY   0x900

/* Simple wait loop */
void UTIL_waitLoop(uint32_t loopcnt)
{
    uint32_t i;
    for (i = 0; i < loopcnt; i++)
    {
        asm ("   NOP");
    }
}

uint32_t DEVICE_Delay(uint32_t delay)
{
    UTIL_waitLoop(delay * 0x100);
    return 0;
}

void GPMC_Init()
{
    uint32_t baseAddr = SOC_GPMC_CONF_BASE;
    uint32_t status;
    uint32_t TimeVar;

    status = GPMCRevisionGet(baseAddr);

    /* Set the clock for GPMC */
    GPMCAutoIdleConfig(baseAddr, GPMC_AUTOIDLE_AUTORUN);

    /* soft reset */
    GPMCModuleSoftReset(baseAddr);

    /* soft reset status get */
    status = GPMCModuleResetStatusGet(baseAddr);

    DEVICE_Delay(MAX_DELAY);

    /* FOLLOWING IS THE NOR MEMORY CONFIGURATION DEPENDING ON MODE */

#if BURST_MODE
    /* This configuration for NOR burst mode support has not been tested. */
    /* Set memory type */
    GPMCDevTypeSelect(baseAddr, GPMC_CHIP_SELECT_0, GPMC_DEVICETYPE_NORLIKE);

    /* Set a device size */
    GPMCDevSizeSelect(baseAddr, GPMC_CHIP_SELECT_0, GPMC_DEVICESIZE_16BITS);

    GPMCClkActivationTimeConfig(baseAddr, GPMC_CHIP_SELECT_0,
                                GPMC_CLKACTIVATIONTIME_ATSTART);

    /* Set the clock divided value */
    GPMCFclkDividerSelect(baseAddr, GPMC_CHIP_SELECT_0, GPMC_FCLK_DIV_BY_2);

    /* Select an address and data multiplexing protocol */
    GPMCAddrDataMuxProtocolSelect(baseAddr, GPMC_CHIP_SELECT_0,
                                  GPMC_MUXADDDATA_NOMUX);

    /* Set the attached device page length */
    GPMCDevPageLenSet(baseAddr, GPMC_CHIP_SELECT_0,
                      GPMC_DEV_PAGELENGTH_SIXTEEN);

    /* Set the wrapping burst capabilities */
    GPMCSyncWrapBurstConfig(baseAddr, GPMC_CHIP_SELECT_0,
                            GPMC_WRAPBURST_DISABLE);

    /* Select a timing signals latencies factor */
    GPMCTimeParaGranularitySelect(baseAddr, GPMC_CHIP_SELECT_0,
                                  GPMC_TIMEPARAGRANULARITY_X1);

    /* Select an output clock frequency, Choose an output clock activation time
     * and Set a single or multiple access
     * for read operations are not used because Applies only to synchronous
     * configurations
     * ( or nonmultiplexed asynchronous for multiple access one) */

    /* Set synchronous or asynchronous mode for read operations */
    GPMCReadTypeSelect(baseAddr, GPMC_CHIP_SELECT_0, GPMC_READTYPE_SYNC);

    /* Set a single or multiple access for write operations */
    GPMCAccessTypeSelect(baseAddr, GPMC_CHIP_SELECT_0,
                         GPMC_MODE_READ, GPMC_ACCESSTYPE_MULTIPLE);

    /* Set a synchronous or asynchronous mode for write */
    GPMCWriteTypeSelect(baseAddr, GPMC_CHIP_SELECT_0, GPMC_WRITETYPE_ASYNC);

    /* FOLLOWING IS NOR CHIP-SELECT CONFIGURATION */

    /* Select the chip-select base address, chip addr needs to be given */
    GPMCBaseAddrSet(baseAddr, GPMC_CHIP_SELECT_0, 0x00000001);

    /* Select the chip-select mask address */
    GPMCMaskAddrSet(baseAddr, GPMC_CHIP_SELECT_0, GPMC_CS_SIZE_16MB);

    DEVICE_Delay(MAX_DELAY);

    /* FOLLOWING IS THE NOR TIMINGS CONFIGURATION */

    /* Configure adequate timing parameters in various memory modes */
    TimeVar = GPMC_CS_TIMING_CONFIG(0x00, 0x0A, 0x00, 0x02);
    GPMCCSTimingConfig(baseAddr, GPMC_CHIP_SELECT_0, TimeVar);

    /* Configure the timing parameters for ADV# signal */
    TimeVar = GPMC_ADV_TIMING_CONFIG(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
    GPMCADVTimingConfig(baseAddr, GPMC_CHIP_SELECT_0, TimeVar);

    /* Configure the timing parameters for WE# and OE# signals */

    TimeVar = GPMC_WE_OE_TIMING_CONFIG(0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00,
                                       0x04);
    GPMCWEAndOETimingConfig(baseAddr, GPMC_CHIP_SELECT_0, TimeVar);

    TimeVar = GPMC_RDACCESS_CYCLETIME_TIMING_CONFIG(0x0A, 0x00, 0x06, 0x02);
    GPMCRdAccessAndCycleTimeTimingConfig(baseAddr, GPMC_CHIP_SELECT_0,
                                         TimeVar);

    TimeVar = GPMC_CYCLE2CYCLE_BUSTURNAROUND_TIMING_CONFIG(0x00, 0x00, 0x00,
                                                           0x00);
    GPMCycle2CycleAndTurnArndTimeTimingConfig(baseAddr, GPMC_CHIP_SELECT_0,
                                              TimeVar);
    GPMCWrAccessAndWrDataOnADMUXBusTimingConfig(baseAddr, GPMC_CHIP_SELECT_0,
                                                0x00, 0x00);

    /* WAIT PIN CONFIGURATION */

    /* Select the WAIT PIN for the device connected to csNum */
    GPMCWaitPinSelect(baseAddr, GPMC_CHIP_SELECT_0, GPMC_WAIT_PIN0);

    /* Configure/select the wait monitoring time for the device connected to
     *csNum */
    GPMCWaitMonitoringTimeSelect(baseAddr, GPMC_CHIP_SELECT_0,
                                 GPMC_WAITMONITORINGTIME_WITH_VALIDDATA);

    /* Configure the wait pin monitoring for read and write access */

    GPMCWaitPinMonitoringConfig(baseAddr, GPMC_CHIP_SELECT_0,
                                GPMC_MODE_WRITE, GPMC_WAITMONITORING_DISABLE);

    GPMCWaitPinMonitoringConfig(baseAddr, GPMC_CHIP_SELECT_0,
                                GPMC_MODE_READ, GPMC_WAITMONITORING_DISABLE);

    /* This function enables/disables the chip select. This function is called
     *during the chip select configuration */
    GPMCCSConfig(baseAddr, GPMC_CHIP_SELECT_0, GPMC_CS_ENABLE);
    DEVICE_Delay(MAX_DELAY);

#else

    /* Set memory type */
    GPMCDevTypeSelect(baseAddr, GPMC_CHIP_SELECT_0, GPMC_DEVICETYPE_NORLIKE);

    /* Set a device size */
    GPMCDevSizeSelect(baseAddr, GPMC_CHIP_SELECT_0, GPMC_DEVICESIZE_16BITS);

    GPMCClkActivationTimeConfig(baseAddr, GPMC_CHIP_SELECT_0,
                                GPMC_CLKACTIVATIONTIME_ONECLK_AFTR);

    /* Select an address and data multiplexing protocol */
    GPMCAddrDataMuxProtocolSelect(baseAddr, GPMC_CHIP_SELECT_0,
                                  GPMC_MUXADDDATA_NOMUX);

    /* Set the attached device page length */
    GPMCDevPageLenSet(baseAddr, GPMC_CHIP_SELECT_0,
                      GPMC_DEV_PAGELENGTH_FOUR);

    /* Set the wrapping burst capabilities */
    GPMCSyncWrapBurstConfig(baseAddr, GPMC_CHIP_SELECT_0,
                            GPMC_WRAPBURST_DISABLE);

    /* Select a timing signals latencies factor */
    GPMCTimeParaGranularitySelect(baseAddr, GPMC_CHIP_SELECT_0,
                                  GPMC_TIMEPARAGRANULARITY_X2);

    /* Select an output clock frequency, Choose an output clock activation time
     * and Set a single or multiple access
     * for read operations are not used because Applies only to synchronous
     * configurations
     * ( or nonmultiplexed asynchronous for multiple access one) */

    /* Set synchronous or asynchronous mode for read operations */
    GPMCReadTypeSelect(baseAddr, GPMC_CHIP_SELECT_0, GPMC_READTYPE_SYNC);

    /* Set a single or multiple access for write operations */
    GPMCAccessTypeSelect(baseAddr, GPMC_CHIP_SELECT_0,
                         GPMC_MODE_READ, GPMC_ACCESSTYPE_SINGLE);

    /* Set a synchronous or asynchronous mode for write */
    GPMCWriteTypeSelect(baseAddr, GPMC_CHIP_SELECT_0, GPMC_WRITETYPE_ASYNC);

    /* FOLLOWING IS NOR CHIP-SELECT CONFIGURATION */

    /* Select the chip-select base address, chip addr needs to be given */
    GPMCBaseAddrSet(baseAddr, GPMC_CHIP_SELECT_0, 0x00000008);

    /* Select the chip-select mask address */
    GPMCMaskAddrSet(baseAddr, GPMC_CHIP_SELECT_0, GPMC_CS_SIZE_64MB);

    DEVICE_Delay(MAX_DELAY);

    /* FOLLOWING IS THE NOR TIMINGS CONFIGURATION */

    /* Configure adequate timing parameters in various memory modes */
    TimeVar = GPMC_CS_TIMING_CONFIG(0x00, 0x0B, 0x00, 0x00);
    GPMCCSTimingConfig(baseAddr, GPMC_CHIP_SELECT_0, TimeVar);

    /* Configure the timing parameters for ADV# signal */
    TimeVar = GPMC_ADV_TIMING_CONFIG(0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00);
    GPMCADVTimingConfig(baseAddr, GPMC_CHIP_SELECT_0, TimeVar);

    /* Configure the timing parameters for WE# and OE# signals */

    TimeVar = GPMC_WE_OE_TIMING_CONFIG(0x00, 0x00, 0x00, 0x00, 0x0B, 0x00,
                                       0x00, 0x03);
    GPMCWEAndOETimingConfig(baseAddr, GPMC_CHIP_SELECT_0, TimeVar);

    TimeVar = GPMC_RDACCESS_CYCLETIME_TIMING_CONFIG(0x0B, 0x00, 0x0A, 0x01);
    GPMCRdAccessAndCycleTimeTimingConfig(baseAddr, GPMC_CHIP_SELECT_0,
                                         TimeVar);

    TimeVar = GPMC_CYCLE2CYCLE_BUSTURNAROUND_TIMING_CONFIG(0x00, 0x00, 0x00,
                                                           0x00);
    GPMCycle2CycleAndTurnArndTimeTimingConfig(baseAddr, GPMC_CHIP_SELECT_0,
                                              TimeVar);
    GPMCWrAccessAndWrDataOnADMUXBusTimingConfig(baseAddr, GPMC_CHIP_SELECT_0,
                                                0x00, 0x00);

    /* WAIT PIN CONFIGURATION */

    /* Select the WAIT PIN for the device connected to csNum */
    GPMCWaitPinSelect(baseAddr, GPMC_CHIP_SELECT_0, GPMC_WAIT_PIN0);

    /* Configure/select the wait monitoring time for the device connected to
     *csNum */
    GPMCWaitMonitoringTimeSelect(baseAddr, GPMC_CHIP_SELECT_0,
                                 GPMC_WAITMONITORINGTIME_WITH_VALIDDATA);

    /* Configure the wait pin monitoring for read and write access */

    GPMCWaitPinMonitoringConfig(baseAddr, GPMC_CHIP_SELECT_0,
                                GPMC_MODE_WRITE, GPMC_WAITMONITORING_DISABLE);

    GPMCWaitPinMonitoringConfig(baseAddr, GPMC_CHIP_SELECT_0,
                                GPMC_MODE_READ, GPMC_WAITMONITORING_DISABLE);

    /* This function enables/disables the chip select. This function is called
     *during the chip select configuration */
    GPMCCSConfig(baseAddr, GPMC_CHIP_SELECT_0, GPMC_CS_ENABLE);
    DEVICE_Delay(MAX_DELAY);

#endif

    UARTPuts("CS status is ", -1);
    UARTPutNum(status);
    UARTPuts("\n", -1);
}

