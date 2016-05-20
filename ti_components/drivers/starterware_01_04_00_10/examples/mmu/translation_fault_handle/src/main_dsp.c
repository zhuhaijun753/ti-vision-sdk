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
 *  Filename       main_dsp
 *
 *  Description    Default code for testcase
 *                 Just returns RET_OK
 *
 * ========================================================================== */

#include "stdint.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mmu.h"
#include "soc.h"
#include "mailbox.h"
#include "hw_types.h"
#include "soc_defines.h"
#include "platform.h"
#include <common/stw_dataTypes.h>
#include <common/stw_types.h>

#if (defined (TDA2XX_FAMILY_BUILD) || defined (TDA3XX_FAMILY_BUILD))
#include "dsp_config.h"
#endif

/* External memory mappping as a super section of 16 MB*/
#define PHY_ADDR2    (0x80000000)
#define VIRT_ADDR2   (0x80000000)

#define PHY_ADDR3    (0x90000000)
#define VIRT_ADDR3   (0x48000000)

/* OCMCRAM region0 as 4KB section        */
#define PHY_ADDR4    (0x00800000)
#define VIRT_ADDR4   (0x00800000)

/* MMU Register memory region 4KB section        */
#define PHY_ADDR6    (SOC_DSP_MMU0CFG_BASE)
#define VIRT_ADDR6   (SOC_DSP_MMU0CFG_BASE)

/* External memory mappping as a super section of 16 MB*/
#define PHY_ADDR7    (0x85000000)
#define VIRT_ADDR7   (0x81000000)

/* External memory mappping as a super section of 16 MB*/
#define PHY_ADDR8    (0x82000000)
#define VIRT_ADDR8   (0x88000000)

#define PHY_ADDR9    (0x4031C000)
#define VIRT_ADDR9   (0x4031C000)

#define PHY_ADDR10    (0x8B000000)
#define VIRT_ADDR10   (0x8B000000)

#define PHY_ADDR11    (0x83000000)
#define VIRT_ADDR11   (0x83000000)

#define TTB_ADDRESS   (0x80500000)

volatile uint32_t mmu_intr_occurred = 0;

uint32_t MMU_Configure()
{
    MMU_TlbEntry_t mmu_entry;

    /* Configure MMU Tlb Entry for mapping reset vector of 4KB*/
    mmu_entry.phyAddr        = PHY_ADDR6;
    mmu_entry.virtAddr       = VIRT_ADDR6;
    mmu_entry.valid          = TRUE;
    mmu_entry.pageSize       = MMU_Large_Size;
    mmu_entry.endianness     = MMU_Little_Endian;
    mmu_entry.elementSize    = MMU_NoTranslation_ElementSize;
    mmu_entry.tlbElementSize = MMU_CPU_ElementSize;
    mmu_entry.preserve       = TRUE;
    MMUTlbEntrySet(SOC_DSP_MMU0CFG_BASE, 1, &mmu_entry);

    mmu_entry.phyAddr        = PHY_ADDR3;
    mmu_entry.virtAddr       = VIRT_ADDR3;
    mmu_entry.valid          = TRUE;
    mmu_entry.pageSize       = MMU_Section_Size;
    mmu_entry.endianness     = MMU_Little_Endian;
    mmu_entry.elementSize    = MMU_NoTranslation_ElementSize;
    mmu_entry.tlbElementSize = MMU_CPU_ElementSize;
    mmu_entry.preserve       = TRUE;
    MMUTlbEntrySet(SOC_DSP_MMU0CFG_BASE, 2, &mmu_entry);

    /* Configure MMU Tlb Entry for DDR Data  as 16 MB Supersection*/
    mmu_entry.phyAddr        = PHY_ADDR2;
    mmu_entry.virtAddr       = VIRT_ADDR2;
    mmu_entry.valid          = TRUE;
    mmu_entry.pageSize       = MMU_SuperSection_Size;
    mmu_entry.endianness     = MMU_Little_Endian;
    mmu_entry.elementSize    = MMU_NoTranslation_ElementSize;
    mmu_entry.tlbElementSize = MMU_CPU_ElementSize;
    mmu_entry.preserve       = TRUE;
    MMUTlbEntrySet(SOC_DSP_MMU0CFG_BASE, 3, &mmu_entry);

    /*ocmc ram initialization for MMU TLB Entry*/
    mmu_entry.phyAddr        = PHY_ADDR4;
    mmu_entry.virtAddr       = VIRT_ADDR4;
    mmu_entry.valid          = TRUE;
    mmu_entry.pageSize       = MMU_Large_Size;
    mmu_entry.endianness     = MMU_Little_Endian;
    mmu_entry.elementSize    = MMU_NoTranslation_ElementSize;
    mmu_entry.tlbElementSize = MMU_CPU_ElementSize;
    mmu_entry.preserve       = TRUE;
    MMUTlbEntrySet(SOC_DSP_MMU0CFG_BASE, 4, &mmu_entry);

    /* Configure MMU Tlb Entry for DDR Data  as 16 MB Supersection*/
    mmu_entry.phyAddr        = PHY_ADDR9;
    mmu_entry.virtAddr       = VIRT_ADDR9;
    mmu_entry.valid          = TRUE;
    mmu_entry.pageSize       = MMU_Large_Size;
    mmu_entry.endianness     = MMU_Little_Endian;
    mmu_entry.elementSize    = MMU_NoTranslation_ElementSize;
    mmu_entry.tlbElementSize = MMU_CPU_ElementSize;
    mmu_entry.preserve       = TRUE;
    MMUTlbEntrySet(SOC_DSP_MMU0CFG_BASE, 5, &mmu_entry);

    /* Configure MMU Tlb Entry for DDR Data  as 16 MB Supersection*/
    mmu_entry.phyAddr        = PHY_ADDR10;
    mmu_entry.virtAddr       = VIRT_ADDR10;
    mmu_entry.valid          = TRUE;
    mmu_entry.pageSize       = MMU_SuperSection_Size;
    mmu_entry.endianness     = MMU_Little_Endian;
    mmu_entry.elementSize    = MMU_NoTranslation_ElementSize;
    mmu_entry.tlbElementSize = MMU_CPU_ElementSize;
    mmu_entry.preserve       = TRUE;
    MMUTlbEntrySet(SOC_DSP_MMU0CFG_BASE, 6, &mmu_entry);

    memset((void *) TTB_ADDRESS, 0, 0x4000);

    /*Enable all mmu interrupts*/
    MMUIrqEnable(SOC_DSP_MMU0CFG_BASE, MMU_INT_All);

    /*Set TTB*/
    MMUTTBSet(SOC_DSP_MMU0CFG_BASE, TTB_ADDRESS);

    /*Enable TWL*/
    MMUWtlEnable(SOC_DSP_MMU0CFG_BASE);

    /* Enable MMU */
    MMUEnable(SOC_DSP_MMU0CFG_BASE);

    return 0;
}

int main(void)
{
    uint32_t          i, dspResetDone = 0;
    uint32_t          msgfromRx = 0;
    uint32_t          timeout   = 0xFFFFF;
    volatile uint32_t done      = 1;
    volatile uint32_t readValue;

    /* For first time it timeouts and after MMU fault is recovered mailbox
     *message is received from A15(Tda2xx) / M4(Tda3xx)*/
    while ((MESSAGE_INVALID ==
            (MailboxGetMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_0,
                               &msgfromRx))) && (--timeout)) ;

    if (!timeout)
    {
        /*Reset MMU*/
        MMUSoftReset(SOC_DSP_MMU0CFG_BASE);

        /*Set MMU to no idle mode*/
        MMUSetMode(SOC_DSP_MMU0CFG_BASE, MMU_NO_IDLE);

        /* Configure the MMU, enable MMU interrupt  */
        MMU_Configure();

#if (defined (TDA2XX_FAMILY_BUILD) || defined (TDA3XX_FAMILY_BUILD))
        /*Enable MMU in DSPSS */
        DSPSysMmuConfig(SOC_DSP_SYSTEM_BASE, DSP_SYS_MMU_INSTANCE0,
                        DSP_SYS_MMU_EN,
                        DSP_SYS_MMU_ABORT_DIS);
#endif

        /*Accessing memory regions which are not configured in MMU results in
         *translation fault */
        for (i = 0; i < 10; i++)
        {
            readValue = HW_RD_REG32(VIRT_ADDR7 + (i * 4));
        }

        for (i = 0; i < 10; i++)
        {
            readValue = HW_RD_REG32(VIRT_ADDR8 + (i * 4));
        }
    }
    else
    {
        dspResetDone = 1;
    }

    /* Disable MMU */
    MMUDisable(SOC_DSP_MMU0CFG_BASE);

    if (dspResetDone)
    {
        if ('A' == msgfromRx)
        {
            printf("From DSP\n");
            printf(
                "DSP Core successfully recoverd from MMU translation fault \n");
            printf("MMU translation fault test successfull\n");
        }
    }
    else
    {
        printf("MMU translation fault test Failed\n");
    }

    while (done) ;

    return 0;
}

