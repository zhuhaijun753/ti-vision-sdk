/**
 *  \file     sbl_tda2ex_main.c
 *
 *  \brief    This file contains the SBL main function which calls the SOC Init
 *            and slave core boot up functions in sequence.
 *
 *  \copyright Copyright (C) 2015 Texas Instruments Incorporated -
 *             http://www.ti.com/
 */

/* ======================================================================
 *   Copyright (C) 2015 Texas Instruments Incorporated
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include "hw_types.h"
#include "soc.h"
#include "soc_defines.h"
#include "sbl_tda2xx_soc_init.h"
#include "sbl_tda2xx_image_copy.h"
#include "sbl_tda2xx_platform.h"
#include "sbl_tda2xx_slavecore_boot.h"
#include "sbl_tda2xx_pmic.h"
#include "sbl_tda2xx_wd_timer.h"
#include "soc_defines.h"
#include "cp15.h"
#include "interrupt.h"
#include "edma.h"
#include "uartConsole.h"
#include "pmlib_cpuidle.h"
#include "pmhal_mpu_lprm.h"
#include "mpu_wugen.h"
#include "platform.h"
#include "uartStdio.h"
#include "pmhal_pdm.h"
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
typedef void (*EntryFunPtr_t)(void);

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
void SBL_PRINTF_Init(UART_INST_t num);
int32_t enable_modules(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
uint32_t entryPoint_MPU_CPU0  = 0;
uint32_t entryPoint_IPU1_CPU0 = 0, entryPoint_IPU1_CPU1 = 0;
uint32_t entryPoint_DSP1      = 0;

/**< \brief This global variable is used to store the status of the Voltage
 *          setting operation of the voltage rails.
 *          Success - if value is 0
 *          Failure - if value is non zero.
 */
int32_t  gSetVoltRailsStatus;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    int32_t  retval = 0;
    void     (*func_ptr)(void);
    uint32_t edma_ch_num   = 1U;
    uint32_t edma_tcc_num  = 1U;
    uint32_t edma_evtq_num = 0;
    uint32_t sblBuildMode;

    /*SBL Instrumentation*/
    uint32_t soc_prcm_time_start, soc_prcm_time_end;
    uint32_t ddr_time_start, ddr_time_end;
    uint32_t image_load_time_start, image_load_time_end;
    uint32_t slavecore_boot_time_start, slavecore_boot_time_end;
    uint32_t sbl_time_start, sbl_time_end;

#ifdef SBL_DEV_BUILD
    sblBuildMode = SBL_BUILD_MODE_DEV;
#else
    sblBuildMode = SBL_BUILD_MODE_PROD;
#endif

    /*PMU Clock counter reset*/
    ARM_CCNT_Enable();

    sbl_time_start = ARM_CCNT_Read();

    /* Enable Neon FPU  */
    CP15FPUEnable();

    /* AVS-0 has already been done in NOR bootmode */
#if (defined (QSPI) || defined (MMCSD))

    /*
     * Initialize the value of gSetVoltRailsStatus before configuring the
     * voltage rails.
     */
    gSetVoltRailsStatus = 0;

    /*Setting AVS Class-0 and the ABB for supported voltage rails*/
    retval = SBLConfigAllVotageRails();
    if (retval != PM_SUCCESS)
    {
        gSetVoltRailsStatus = -1;
    }
#endif

    retval = ConfigPowerDomains();
    if (retval != 0)
    {
        BootAbort();
    }

    /*Unlock MMR registers*/
    PlatformUnlockMMR();

    /* Initializing the ARM Interrupt Controller. */
    Intc_Init();

    /* Enable the interrupt */
    Intc_IntEnable(0);

    /*Refresh the WD_TIMER to 3mins & enable DLY interrupt*/
    SBLWdtimerBegin();

    /*UART initialization*/

    SBL_PRINTF_Init(UART1_INST);

    SBL_PRINTF(0, "\n J6 ECO SBL Boot \n");

    /* gSetVoltRailsStatus would be set to 0 if the voltages are set correctly
     * and the ABB configuration has gone through fine. If not,
     * gSetVoltRailsStatus would have a value -1.
     */
    if (gSetVoltRailsStatus != 0)
    {
        SBL_PRINTF(TRACE_HIGH,
                   "\n AVS class 0 Configure Error \n");
    }
    else
    {
        SBL_PRINTF(TRACE_HIGH, "\n AVS class-0 has been completed already \n");
    }

    soc_prcm_time_start = ARM_CCNT_Read();

    /*Initialized the DPLL*/
    retval = configure_dpll();

    if (retval != 0)
    {
        SBL_PRINTF(TRACE_HIGH, "\n Configure DPLL Error- Error \n");
        BootAbort();
    }

    SBL_PRINTF(TRACE_HIGH, "\n DPLL configuration completed \n");

    /*Configure the clock domain*/
    retval = configure_clock_domains();

    if (retval != 0)
    {
        SBL_PRINTF(TRACE_HIGH, "\n Clockdomain wakeup - Error \n");
    }
    else
    {
        SBL_PRINTF(TRACE_HIGH,
                   "\n PRCM clock domain force wake-up completed \n");
    }

    /*Module enable - IO peripherals, video subsystem, mem*/
    retval = enable_modules();

    if (retval != 0)
    {
        SBL_PRINTF(TRACE_HIGH, "\n Enable modules - Error \n");
    }
    else
    {
        SBL_PRINTF(TRACE_HIGH, "\n PRCM module enable completed \n");
    }

    /*Program the video1, video2 & HDMI PLL*/
    retval = program_dss_video_pll();

    if (retval != 0)
    {
        SBL_PRINTF(TRACE_HIGH, "\n dss video pll programming - Error \n");
    }
    else
    {
        SBL_PRINTF(TRACE_HIGH, "\n dss video pll programming completed \n");
    }

    ti_tda2xx_evm_configure_pad();

    SBL_PRINTF(TRACE_HIGH, "\n TI TDA2EX EVM pad configuration completed \n");

    retval = SBLConfigStaticDependency();

    if (retval != 0)
    {
        SBL_PRINTF(TRACE_HIGH, "\n Static Dependency Program Error \n");
    }

    soc_prcm_time_end = ARM_CCNT_Read();

    ddr_time_start = ARM_CCNT_Read();

    /*Configure EMIF DDR3*/
    sbl_ddr3_config();

    SBL_PRINTF(TRACE_HIGH, "\n DDR3 configuration completed \n");

    ddr_time_end = ARM_CCNT_Read();

    /* EDMA3 Init & request channel 1 */
    EDMAsetRegion(0);
    EDMA3Init(SOC_EDMA_TPCC_BASE, 0);

    EDMA3RequestChannel(SOC_EDMA_TPCC_BASE, EDMA3_CHANNEL_TYPE_DMA, edma_ch_num,
                        edma_tcc_num,
                        edma_evtq_num);

    /*slavecore prcm init & system reset*/
    slavecore_prcm_enable();

    SBL_PRINTF(TRACE_HIGH, "\n AppImage download begins \n");

    image_load_time_start = ARM_CCNT_Read();

    /*Copy the Multicore Image file & entry point*/
    if (ImageCopy() != 0)
    {
        SBL_PRINTF(TRACE_HIGH, "\n No valid App Image is available \n");
    }
    image_load_time_end = ARM_CCNT_Read();

    slavecore_boot_time_start = ARM_CCNT_Read();

    /*Refresh the WD_TIMER to 3mins & disable DLY interrupt*/
    SBLWdtimerEnd();

    /*Deinit the AINTC & Disable ARM IRQ*/
    Intc_IntDisable();

    /* Release the slave cores out of reset */
    SBLIPUBringUp((uint32_t) 0, entryPoint_IPU1_CPU0, entryPoint_IPU1_CPU1,
                  sblBuildMode);

    DSP1_BringUp(entryPoint_DSP1, sblBuildMode);

    slavecore_boot_time_end = ARM_CCNT_Read();

    SBL_PRINTF(TRACE_HIGH, "\n SBL boot completed successfully  \n");

    /*EDMA3 Deinit*/
    EDMA3Deinit(SOC_EDMA_TPCC_BASE, 0);

    sbl_time_end = ARM_CCNT_Read();

    UARTprintf(
        "\n **************SBL Boot-up clock cycles*******************\n ");
    UARTprintf(
        " \n PMCCNTR counts once every 64 clock cycles. To get actual CPU cycle multiple by 64\n");
    UARTprintf("\n VM init clock cycles - %u\n",
               soc_prcm_time_start - sbl_time_start);
    UARTprintf("\n soc prcm init clock cycles - %u\n",
               soc_prcm_time_end - soc_prcm_time_start);
    UARTprintf("\n ddr3 init clock cycles - %u\n",
               ddr_time_end - ddr_time_start);
    UARTprintf("\n appImage load clock cycles - %u\n",
               image_load_time_end - image_load_time_start);
    UARTprintf("\n slavecore bring-up clock cycles - %u\n",
               slavecore_boot_time_end - slavecore_boot_time_start);
    UARTprintf("\n sbl total boot-up clock cycles - %u\n",
               sbl_time_end - sbl_time_start);
    UARTprintf(
        "\n *****************************************************************\n ");

    /*Jump to MPU APP*/
    if (entryPoint_MPU_CPU0 != 0)
    {
        SBL_PRINTF(TRACE_HIGH, "Jumping to MPU CPU0 Application...\r\n\n");
        UARTWaitUntilTransmitComplete();
        func_ptr = (EntryFunPtr_t) entryPoint_MPU_CPU0;
        func_ptr();
    }
    else
    {
#ifndef SBL_DEV_BUILD
        SBL_PRINTF(TRACE_HIGH, "Putting MPU in Retention...\r\n\n");

        MPU_WUGEN_0_DisableAll();

        PMHALPdmSetPDState(PMHAL_PRCM_PD_MPU,
                           PMHAL_PRCM_PD_STATE_RETENTION,
                           PM_TIMEOUT_NOWAIT);
        PMHALPdmSetLogicRetState(PMHAL_PRCM_PD_MPU,
                                 PMHAL_PRCM_PD_RET_STATUS_CSWR);

        PMHALPdmSetMemRetState(PMHAL_PRCM_PD_MPU,
                               PMHAL_PRCM_PHY_MEM_MPU_L2,
                               PMHAL_BANK_RET_ON);
        HW_WR_REG32(SOC_MPU_CM_CORE_AON_BASE, 0x3);

        PMLIBCpuIdle(PMHAL_PRCM_PD_STATE_RETENTION);
#else
        volatile int spin = 1;
        while (spin) ;
#endif
    }

    return 0;
}

/**
 * \brief  enable modules function sequence IO peripherials, mem subsystem,
 *          video subsytem, interconnect & timer modules PRCM enable
 *
 *
 *
 * \param   None.
 *
 * \return   error status.If error has occured it returns a non zero value.
 *             If no error has occured then return status will be zero. .
 *
 **/
int32_t enable_modules(void)
{
    int32_t retval = 0;

    SBL_PRINTF(TRACE_LOW, __func__);

#ifdef TDA2EX_BUILD
    retval = enable_i2c1();

    if (retval != 0)
    {
        SBL_PRINTF(TRACE_HIGH, "\n i2c module enable - Error \n");
    }
#endif

    retval = enable_vip_dss();

    if (retval != 0)
    {
        SBL_PRINTF(TRACE_HIGH, "\n vip & dss module enable - Error \n");
    }

    retval = enable_ocmc();

    if (retval != 0)
    {
        SBL_PRINTF(TRACE_HIGH, "\n ocmc module enable - Error \n");
    }

    retval = enable_serial_per();

    if (retval != 0)
    {
        SBL_PRINTF(TRACE_HIGH, "\n serial peripherals module enable - Error \n");
    }

    retval = enable_mem();

    if (retval != 0)
    {
        SBL_PRINTF(TRACE_HIGH, "\n mem enable - Error \n");
    }

    retval = enable_interconnect();

    if (retval != 0)
    {
        SBL_PRINTF(TRACE_HIGH, "\n interconnect module enable - Error \n");
    }

    retval = enable_ipc();

    if (retval != 0)
    {
        SBL_PRINTF(TRACE_HIGH, "\n ipc module enable - Error \n");
    }

    retval = enable_timer();

    if (retval != 0)
    {
        SBL_PRINTF(TRACE_HIGH, "\n timer module enable - Error \n");
    }

    retval = enable_per();

    if (retval != 0)
    {
        SBL_PRINTF(TRACE_HIGH, "\n peripherals module enable - Error \n");
    }

    retval = enable_cpgmac();

    if (retval != 0)
    {
        SBL_PRINTF(TRACE_HIGH, "\n cpgmac module enable - Error \n");
    }

    return retval;
}

/*
 * \brief This function Aborts execution.
 *
 * \param  none
 *
 * \return none
 */

void BootAbort(void)
{
    /* Go into an infinite loop.*/
    volatile uint32_t loop = 1U;
    while (1U == loop)
    {
        /* Infinite loop */
    }
}

/**
 * \brief  Function to read the device ID
 *
 *
 * \param   None.
 *
 * \return   Return the device id
 *
 **/

int32_t GetDeviceId(void)
{
    int32_t deviceId = 66;
    return (deviceId);
}

void  SBL_PRINTF(traceLevel_t level, const char *ptr)
{
    switch (level)
    {
#if (DEBUG_TRACE_LEVEL >= 0)
        case TRACE_REG:
            UARTPuts(ptr, -1);
            break;
#endif

#if (DEBUG_TRACE_LEVEL >= 1)
        case TRACE_HIGH:
            UARTPuts(ptr, -1);
            break;
#endif

#if (DEBUG_TRACE_LEVEL >= 2)
        case TRACE_MEDIUM:
            UARTPuts(ptr, -1);
            break;
#endif

#if DEBUG_TRACE_LEVEL >= 3
        case TRACE_LOW:
            UARTPuts(ptr, -1);
            break;
#endif
        default:
            /* Nothing to be done here */
            break;
    }
}

/**
 * \brief  static function to initialize the uart peripheral & associated
 *          DLL_PER, clock domain & PRCM module enable
 *
 *
 *
 * \param   None.
 *
 * \return   None.
 *
 **/

void SBL_PRINTF_Init(UART_INST_t num)
{
    int32_t retval = 0;

    retval = SBL_UART_PRCM(num);

    PlatformUARTSetPinMux(num);

    if (retval != 0)
    {
        BootAbort();
    }

    UART_Init(num);
}

