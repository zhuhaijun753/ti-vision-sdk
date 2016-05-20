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
 *   Description:    Profiler app to profile the data throughput of qspi driver
 *                   in dma & memcpy mode.
 *
 */

/****************************************************************
 *  INCLUDE FILES
 ****************************************************************/
#include "stdint.h"
#include "qspi.h"
#include "uartStdio.h"
#include "qspi_flash.h"
#include "edma.h"
#include "soc.h"
#include "cp15.h"

/* ============================================================================
 * GLOBAL VARIABLES DECLARATIONS
 * =============================================================================
 */
uint32_t gEdma_ch_num   = 2;
uint32_t edma_tcc_num  = 2;
uint32_t edma_evtq_num = 0;

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

int main(void) {
    qspi_DeviceType_e DeviceType     = DEVICE_TYPE_QSPI4;
    uint32_t          dstaddr_memcpy = 0x80700000;

    volatile uint32_t dstAddr = 0x80700000U, spi_offset;

    uint32_t          length = 0x100000;
    uint32_t          pmu_time_start, pmu_time_end;
    uint32_t          device_Id;

    /*PMU Clock counter reset*/
    ARM_CCNT_Enable();

    EDMA3Init(SOC_EDMA_TPCC_BASE, 0);
    EDMAsetRegion(0);
    EDMA3RequestChannel(SOC_EDMA_TPCC_BASE, EDMA3_CHANNEL_TYPE_DMA, gEdma_ch_num,
                        edma_tcc_num,
                        edma_evtq_num);

    UARTStdioInit();
    UARTPuts("\nQSPI Flash profiler", -1);

    QSPI_Initialize(DeviceType);

    device_Id = QSPI_GetDeviceId();

    UARTprintf("\nMID -%x", (device_Id & 0xFF));
    UARTprintf("\nDID - %x", (device_Id & 0xFF0000) >> 16);

    /*Measure the QSPI Baud Rate */

    /*Change to Memory mapped mode*/
    QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                      (uint8_t)QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT);
    QSPI_ConfMAddrSpace((uint8_t)QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT,
                                QSPI_CS0);

    /*Memcpy mode */
    /*
     *  1) Start time
     *  3) copy 1 MB data
     *  2) end time
     */

    spi_offset = 0x80000;

    pmu_time_start = ARM_CCNT_Read();

    QSPI_ReadSectors((void *) dstaddr_memcpy, spi_offset, length);

    pmu_time_end = ARM_CCNT_Read();

    UARTprintf("\n Number of bytes read from QSPI FLASH: %u", length);

    UARTprintf("\n QSPI data copy with memcpy - cpu cycles - %u\n",
               pmu_time_end - pmu_time_start);

    /*With EDMA*/
    spi_offset     = 0x80000;
    pmu_time_start = ARM_CCNT_Read();

    QSPI_ReadSectors_edma((void *) dstAddr, spi_offset, length,
                          gEdma_ch_num);
    pmu_time_end = ARM_CCNT_Read();

    UARTprintf("\n QSPI data copy in DMA MODE - cpu cycles - %u\n",
               pmu_time_end - pmu_time_start);

    UARTprintf(
        " \n PMCCNTR counts once every 64 clock cycles. To get actual CPU cycle multiple by 64\n");

    {volatile int spin = 1; while (spin) ; }

    return 0;
}

