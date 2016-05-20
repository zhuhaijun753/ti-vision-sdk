/*
 *******************************************************************************
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file tlb_config_eve1.c
 *
 * \brief  This file implements the MMU configuration of EVE1
 *
 * \version 0.0 (Jul 2013) : [SS] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Error.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/ipc/Ipc.h>
#include <mmu.h>

/*******************************************************************************
 *  DEFINES
 ***************************************************************************** */
void eve1MmuConfig(void);
void eveCommonMmuConfig(UInt32 baseAddr);

/* There are only 32 TLB entries in EVE */
#define EVE_TLB_NUM_ENTRIES (32U)

/* To allow skipping of configuration for some TLB entries */
#define INVALID_PG          (0xFFFFFFFFU)

#ifdef TDA3XX_64MB_DDR
const UInt32 tlbMapping[EVE_TLB_NUM_ENTRIES*2U] =
{
    /* PHYS   ,  VIRT   */
    INVALID_PG, INVALID_PG, /* 00 */
    INVALID_PG, INVALID_PG, /* 01 */
    INVALID_PG, INVALID_PG, /* 02 */
    0x40000000, 0x40000000, /* 03 */
    0x41000000, 0x41000000, /* 04 */
    0x42000000, 0x42000000, /* 05 */
    0x48000000, 0x48000000, /* 06 */
    0x49000000, 0x49000000, /* 07 */
    0x4A000000, 0x4A000000, /* 08 */
    0x81000000, 0x81000000, /* 09 */
    0x82000000, 0x82000000, /* 10 */
    0x83000000, 0x83000000, /* 11 */
    INVALID_PG, INVALID_PG, /* 12 */
    INVALID_PG, INVALID_PG, /* 13 */
    INVALID_PG, INVALID_PG, /* 14 */
    INVALID_PG, INVALID_PG, /* 15 */
    INVALID_PG, INVALID_PG, /* 16 */
    INVALID_PG, INVALID_PG, /* 17 */
    INVALID_PG, INVALID_PG, /* 18 */
    INVALID_PG, INVALID_PG, /* 19 */
    INVALID_PG, INVALID_PG, /* 20 */
    INVALID_PG, INVALID_PG, /* 21 */
    INVALID_PG, INVALID_PG, /* 22 */
    INVALID_PG, INVALID_PG, /* 23 */
    INVALID_PG, INVALID_PG, /* 24 */
    INVALID_PG, INVALID_PG, /* 25 */
    INVALID_PG, INVALID_PG, /* 26 */
    INVALID_PG, INVALID_PG, /* 27 */
    INVALID_PG, INVALID_PG, /* 28 */
    INVALID_PG, INVALID_PG, /* 29 */
    INVALID_PG, INVALID_PG, /* 30 */
    0x54000000, 0x54000000  /* 31 */
};
#else
const UInt32 tlbMapping[EVE_TLB_NUM_ENTRIES*2U] =
{
    /* PHYS   ,  VIRT   */
    INVALID_PG, INVALID_PG, /* 00 */
    INVALID_PG, INVALID_PG, /* 01 */
    INVALID_PG, INVALID_PG, /* 02 */
    0x40000000, 0x40000000, /* 03 */
    0x41000000, 0x41000000, /* 04 */
    0x42000000, 0x42000000, /* 05 */
    0x48000000, 0x48000000, /* 06 */
    0x49000000, 0x49000000, /* 07 */
    0x4A000000, 0x4A000000, /* 08 */
    0x85000000, 0x85000000, /* 09 */
    0x86000000, 0x86000000, /* 10 */
    0x87000000, 0x87000000, /* 11 */
    0x88000000, 0x88000000, /* 12 */
    0x89000000, 0x89000000, /* 13 */
    0x8A000000, 0x8A000000, /* 14 */
    0x8B000000, 0x8B000000, /* 15 */
    0x8C000000, 0x8C000000, /* 16 */
    0x8D000000, 0x8D000000, /* 17 */
    0x8E000000, 0x8E000000, /* 18 */
    0x8F000000, 0x8F000000, /* 19 */
    0x90000000, 0x90000000, /* 20 */
    0x91000000, 0x91000000, /* 21 */
    0x92000000, 0x92000000, /* 22 */
    0x93000000, 0x93000000, /* 23 */
    0x94000000, 0x94000000, /* 24 */
    0x95000000, 0x95000000, /* 25 */
    0x96000000, 0x96000000, /* 26 */
    0x97000000, 0x97000000, /* 27 */
    0x98000000, 0x98000000, /* 28 */
    0x99000000, 0x99000000, /* 29 */
    /* SR0, REMOTE_LOG_SIZE mapping */
    0x9F000000, 0x9F000000, /* 30 */
    0x54000000, 0x54000000  /* 31 */
};
#endif

/**
 *******************************************************************************
 *
 * \brief This function implements the MMU configuration of EVE
 *
 * \return  void
 *
 *******************************************************************************
 */
void eveCommonMmuConfig(UInt32 baseAddr)
{
    UInt32 i;
    MMU_TlbEntry_t  tlbEntry;

    tlbEntry.valid          = 1U;
    tlbEntry.pageSize       = MMU_PAGESIZE_16MB;
    tlbEntry.endianness     = MMU_Little_Endian;
    tlbEntry.elementSize    = MMU_Byte_ElementSize; /* Unsupported - keep 0 */
    tlbEntry.tlbElementSize = MMU_TLB_ElementSize;  /* Unsupported - keep 0 */
    tlbEntry.preserve       = 0U; /* 0 => No protection against flush */

    for ( i = 0; i < EVE_TLB_NUM_ENTRIES; i++)
    {
        if(INVALID_PG == tlbMapping[i*2U])
        {
            continue;
        }
        tlbEntry.phyAddr        = tlbMapping[i*2U];
        tlbEntry.virtAddr       = tlbMapping[i*2U + 1U];
        MMUTlbEntrySet(baseAddr,
                       i,
                       (const MMU_TlbEntry_t *) &tlbEntry);
    }
    /*Enable MMU*/
    MMUEnable(baseAddr);
}

/**
 *******************************************************************************
 *
 * \brief This function implements the MMU configuration of EVE1
 *
 * \return  void
 *
 *******************************************************************************
 */
void eve1MmuConfig(void)
{
    eveCommonMmuConfig(SOC_EVE_MMU0_BASE);
}
