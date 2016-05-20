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
 *  \file  mmu.h
 *
 *  \brief This file contains the device HAL APIs for MMU.
 */

/**
 *  @Component    SYSTEM_MMU
 *
 *  @Filename     mmu.h
 *
 *  @Description  SYSTEM MMU
 *
 *   Available Functions:
 *             MMUCurrentVictimSet    - Set Current Victim
 *             MMUCurrentVictimGet    - Get Current Victim
 *             MMUTlbLockSet          - Set Base Lock Value
 *             MMUTlbLockGet          - Get Base Lock Value
 *             MMUGlobalFlush         - MMU Global FLush
 *             MMUTlbEntryFlush       - MMU Tlb entry Flush
 *             MMUSoftReset           - Reset MMU
 *             MMUIrqGetStatus        - Get MMU Irq Status
 *             MMUIrqClearStatus      - Clear MMU Irq Status
 *             MMUIrqEnable           - Enable MMU Irq
 *             MMUIrqDisable          - Disable MMU Irq
 *             MMUWtlEnable           - Enable Walking Table Logic
 *             MMUWtlDisable          - Disable Walking Table Logic
 *             MMUEnable              - Enable MMU
 *             MMUDisable             - Disable MMU
 *             MMUTlbEntrySet         - Configure Selected TLB Entry
 *
 *  Domain:                 Ducati
 *
 **======================================================================== */

#ifndef MMU_H_
#define MMU_H_

/* =============================================================================
 * INCLUDE FILES (only if necessary)
 * =============================================================================
 */

#include "stdint.h"
#include "soc.h"
#include "hw_mmu.h"

#ifdef __cplusplus
extern "C" {
#endif

/* =============================================================================
 * EXPORTED DEFINITIONS
 * =============================================================================
 */

/*-------------------------------------------------------------------------***
 * @DEFINITION   <Identifier>
 *
 * @BRIEF        <Brief description of macro>
 *
 * @DESCRIPTION  <Detailed description of macro>
 *
 **------------------------------------------------------------------------ */

/* -----------------------------------------------------------------------***
 * @TYPE         MMU_IntType_t
 *
 * @BRIEF        Interrupt enable/status types
 *
 * @DESCRIPTION  Enumerated Type used to specify Interrupt enable/status for MMU
 *
 **----------------------------------------------------------------------- */
typedef enum MMU_IntType
{
    MMU_INT_TLBMiss          = MMU_IRQSTATUS_TLBMISS_MASK,
    MMU_INT_TranslationFault = MMU_IRQSTATUS_TRANSLATIONFAULT_MASK,
    MMU_INT_EMUMiss          = MMU_IRQSTATUS_EMUMISS_MASK,
    MMU_INT_TableWalkFault   = MMU_IRQSTATUS_TABLEWALKFAULT_MASK,
    MMU_INT_MultiHitFault    = MMU_IRQSTATUS_MULTIHITFAULT_MASK,
    MMU_INT_All              = 0x1F
} MMU_IntType_t;

/* -----------------------------------------------------------------------***
 * @TYPE         MMU_PageSize_t
 *
 * @BRIEF        Page Size
 *
 * @DESCRIPTION  Enumerated Type used to specify Page size
 *               MMU_CAM_PAGESIZE_SECTION -> 1MiB
 *               MMU_CAM_PAGESIZE_LARGE   -> 64kiB
 *               MMU_CAM_PAGESIZE_SMALL   -> 4kiB
 *               MMU_CAM_PAGESIZE_SUPER   -> 16MiB
 *
 **----------------------------------------------------------------------- */
typedef enum MMU_PageSize
{
    MMU_Section_Size      = MMU_CAM_PAGESIZE_SECTION,
    MMU_Large_Size        = MMU_CAM_PAGESIZE_LARGE,
    MMU_Small_Size        = MMU_CAM_PAGESIZE_SMALL,
    MMU_SuperSection_Size = MMU_CAM_PAGESIZE_SUPER,

    /* Additional enums to make them readable */
    MMU_PAGESIZE_1MB      = MMU_CAM_PAGESIZE_SECTION,
    MMU_PAGESIZE_64KB     = MMU_CAM_PAGESIZE_LARGE,
    MMU_PAGESIZE_4KB      = MMU_CAM_PAGESIZE_SMALL,
    MMU_PAGESIZE_16MB     = MMU_CAM_PAGESIZE_SUPER
} MMU_PageSize_t;

/* -----------------------------------------------------------------------***
 * @TYPE         MMU_Endianness_t
 *
 * @BRIEF        MMU Endianness translation
 *
 * @DESCRIPTION  Enumerated Type used to specify Endianness
 *
 **----------------------------------------------------------------------- */
typedef enum MMU_Endianness
{
    MMU_Little_Endian = 0x0,
    MMU_Big_Endian    = 0x1
} MMU_Endianness_t;

/* -----------------------------------------------------------------------***
 * @TYPE         MMU_ElementSize_t
 *
 * @BRIEF        Element Size
 *
 * @DESCRIPTION  Enumerated Type used to specify Element size
 *
 **----------------------------------------------------------------------- */
typedef enum MMU_ElementSize
{
    MMU_Byte_ElementSize          = 0x0,
    MMU_Short_ElementSize         = 0x1,
    MMU_Long_ElementSize          = 0x2,
    MMU_NoTranslation_ElementSize = 0x3
} MMU_ElementSize_t;

/* -----------------------------------------------------------------------***
 * @TYPE         MMU_MixedPageAttr_t
 *
 * @BRIEF        MMU Mixed Page Attribute
 *
 * @DESCRIPTION  Enumerated Type used to Mixed Page Attribute use
 *
 **----------------------------------------------------------------------- */
typedef enum MMU_MixedPageAttr
{
    MMU_TLB_ElementSize = 0x0,
    MMU_CPU_ElementSize = 0x1
} MMU_MixedPageAttr_t;

/* -----------------------------------------------------------------------***
 * @TYPE         MMU_Mode
 *
 * @BRIEF        MMU Modes of operation
 *
 * @DESCRIPTION  Enumerated Type used to set MMU mode of operation
 *
 **----------------------------------------------------------------------- */
typedef enum
{
    MMU_FORCE_IDLE = 0x0,
    MMU_NO_IDLE    = 0x1,
    MMU_SMART_IDLE = 0x2
} MMU_Mode;

/* -----------------------------------------------------------------------***
 * @TYPE         MMU_Return_t
 *
 * @BRIEF        MMU return value
 *
 * @DESCRIPTION  Status return from page table entry API's
 *
 **----------------------------------------------------------------------- */
typedef enum
{
    RET_OK,
    RET_FAIL
}MMU_Return_t;

/* =============================================================================
 * EXPORTED TYPES
 * =============================================================================
 */

/*-------------------------------------------------------------------------***
 * @TYPE         MMU_TlbEntry_t
 *
 * @BRIEF        MMU Table entry descriptor
 *
 * @DESCRIPTION  Structure holding all MMU Table Entry parameters
 *
 **------------------------------------------------------------------------ */
typedef struct MMU_TlbEntry
{
    uint32_t            phyAddr;
    uint32_t            virtAddr;
    uint32_t            valid;
    MMU_PageSize_t      pageSize;
    MMU_Endianness_t    endianness;
    MMU_ElementSize_t   elementSize;
    MMU_MixedPageAttr_t tlbElementSize;
    uint32_t            preserve;
} MMU_TlbEntry_t;

/* =============================================================================
 * EXPORTED VARIABLES
 * =============================================================================
 */

/*-------------------------------------------------------------------------***
 * @VARIABLE     <Identifier>
 *
 * @BRIEF        <type> <Identifier> - <Brief description of variable>
 *
 * @DESCRIPTION  <Detailed description of variable>
 *
 **------------------------------------------------------------------------ */

/* =============================================================================
 * EXPORTED FUNCTIONS
 * =============================================================================
 */

/* ------------------------------------------------------------------------***
 * @FUNCTION      MMUCurrentVictimSet
 *
 * @BRIEF         Set Tlb Entry in Lock register
 *
 * @param[in]     baseAddr    Base address of the instance
 * @param[in]     tlbEntry     uint32_t entry to be set in MMU
 *
 * @RETURNS       None
 *
 * @DESCRIPTION   Set Current Victim in Lock register.
 *
 * @METHOD        Fill Lock register current victim. Do not modify Locked
 *                entries.
 *
 *
 *
 **------------------------------------------------------------------------ */
void MMUCurrentVictimSet(uint32_t baseAddr, uint32_t tlbEntry);

/* ------------------------------------------------------------------------***
 * @FUNCTION      MMUCurrentVictimGet
 *
 * @BRIEF         Set Tlb Entry in Lock register
 *
 * @param[in]     baseAddr    Base address of the instance
 *
 * @RETURNS       Victim value
 *
 * @DESCRIPTION   Get Current Victim from Lock register.
 *
 * @METHOD        Return  Lock register current victim.
 *
 *
 *
 **------------------------------------------------------------------------ */
uint32_t MMUCurrentVictimGet(uint32_t baseAddr);

/* ------------------------------------------------------------------------***
 * @FUNCTION      MMUTlbLockSet
 *
 * @BRIEF         Set Tlb Lock entry in Lock register
 *
 * @param[in]     baseAddr    Base address of the instance
 * @param[in]     tlbEntry     uint32_t entry to be locked in MMU
 *
 * @RETURNS       None
 *
 * @DESCRIPTION   Set Tlb Lock in Lock register.
 *
 * @METHOD        Fill Lock register Base Value. Do not modify victim entries.
 *
 *
 *
 **------------------------------------------------------------------------ */
void MMUTlbLockSet(uint32_t baseAddr, uint32_t tlbEntry);

/* ------------------------------------------------------------------------***
 * @FUNCTION      MMUTlbLockGet
 *
 * @BRIEF         Set Tlb Lock entry in Lock register
 *
 * @param[in]     baseAddr    Base address of the instance
 *
 * @RETURNS       Lock base value
 *
 * @DESCRIPTION   Get Tlb Base Lock from Lock register.
 *
 * @METHOD        Get Lock register Base Value.
 *
 *
 *
 **------------------------------------------------------------------------ */
uint32_t MMUTlbLockGet(uint32_t baseAddr);

/* ------------------------------------------------------------------------***
 * @FUNCTION      MMUGlobalFlush
 *
 * @BRIEF         Flush all MMU entries
 *
 * @param[in]     baseAddr    Base address of the instance
 *
 * @RETURNS       void
 *
 * @DESCRIPTION   Flush all Tlb entrties in MMU.
 *
 * @METHOD        Write proper register.
 *
 *
 *
 **------------------------------------------------------------------------ */
void MMUGlobalFlush(uint32_t baseAddr);

/* ------------------------------------------------------------------------***
 * @FUNCTION      MMUTlbEntryFlush
 *
 * @BRIEF         Flush MMU entry for the virtual address passed
 *
 * @param[in]     baseAddr     Base address of the instance
 * @param[in]     virtAddress  uint32_t Virtual Address of entry to be flushed
 *
 * @RETURNS       void
 *
 * @DESCRIPTION   Flush Specific Tlb entrties in MMU pointed by specified Virt.
 *                Addr.
 *
 * @METHOD        Write proper registers.
 *
 *
 *
 *------------------------------------------------------------------------ */
void MMUTlbEntryFlush(uint32_t baseAddr, uint32_t virtAddress);

/* ------------------------------------------------------------------------***
 * @FUNCTION      MMUSoftReset
 *
 * @BRIEF         Reset MMU
 *
 * @param[in]     baseAddr    Base address of the instance
 *
 * @RETURNS       void
 *
 * @DESCRIPTION   Reset MMU and wait for reset done
 *
 * @METHOD        Set reset bit and wait for reset done.
 *
 *
 *
 **------------------------------------------------------------------------ */
void MMUSoftReset(uint32_t baseAddr);

/* ------------------------------------------------------------------------***
 * @FUNCTION      MMUSetMode
 *
 * @BRIEF         Set MMU operation mode
 *
 * @param[in]     baseAddr    Base address of the instance
 *
 * @param[in]     mode        Operation mode
 *
 * @RETURNS       void
 *
 * @DESCRIPTION   Set MMU operation mode
 *
 * @METHOD        Set MMU operation field bits
 *
 *
 *
 **------------------------------------------------------------------------ */
void MMUSetMode(uint32_t baseAddr, MMU_Mode mode);

/* ------------------------------------------------------------------------***
 * @FUNCTION      MMUIrqGetStatus
 *
 * @BRIEF         Get MMU Irq Status
 *
 * @param[in]     baseAddr    Base address of the instance
 *
 * @RETURNS       IRQ Status
 *
 * @DESCRIPTION   Get Current MMU.
 *
 * @METHOD        Read proper register.
 *
 *
 *
 **------------------------------------------------------------------------ */
uint32_t MMUIrqGetStatus(uint32_t baseAddr);

/* ------------------------------------------------------------------------***
 * @FUNCTION      MMUIrqClearStatus
 *
 * @BRIEF         Clear MMU Irq Status
 *
 * @param[in]     baseAddr    Base address of the instance
 * @param[in]     intType      MMU_IntType_t interrupt Type to Clear
 *
 * @RETURNS       void
 *
 * @DESCRIPTION   Clear Current MMU.
 *
 * @METHOD        Write proper register.
 *
 *
 *
 **------------------------------------------------------------------------ */
void MMUIrqClearStatus(uint32_t baseAddr, MMU_IntType_t intType);

/* ------------------------------------------------------------------------***
 * @FUNCTION      MMUIrqEnable
 *
 * @BRIEF         Get MMU Irq Status
 *
 * @param[in]     baseAddr    Base address of the instance
 * @param[in]     intType      MMU_IntType_t interrupt Type to enable
 *
 * @RETURNS       void
 *
 * @DESCRIPTION   Enable selected interrupt
 *
 * @METHOD        Write proper register.
 *
 *
 *
 **------------------------------------------------------------------------ */
void MMUIrqEnable(uint32_t baseAddr, MMU_IntType_t intType);

/* ------------------------------------------------------------------------***
 * @FUNCTION      MMUIrqDisable
 *
 * @BRIEF         Get MMU Irq Status
 *
 * @param[in]     baseAddr    Base address of the instance
 * @param[in]     intType      MMU_IntType_t interrupt Type to be disabled
 *
 * @RETURNS       void
 *
 * @DESCRIPTION   Disable selected interrupt
 *
 * @METHOD        Write proper register.
 *
 *
 *
 **------------------------------------------------------------------------ */
void MMUIrqDisable(uint32_t baseAddr, MMU_IntType_t intType);

/* ------------------------------------------------------------------------***
 * @FUNCTION      MMUWtlEnable
 *
 * @BRIEF         Enable MMU Walking table logic
 *
 * @param[in]     baseAddr    Base address of the instance
 *
 * @RETURNS       void
 *
 * @DESCRIPTION   Enable MMU Walking table logic.
 *
 * @METHOD        Write proper register.
 *
 *
 *
 **------------------------------------------------------------------------ */
void MMUWtlEnable(uint32_t baseAddr);

/* ------------------------------------------------------------------------***
 * @FUNCTION      MMUWtlDisable
 *
 * @BRIEF         Disable MMU Walking table logic
 *
 * @param[in]     baseAddr    Base address of the instance
 *
 * @RETURNS       void
 *
 * @DESCRIPTION   Disable MMU Walking table logic.
 *
 * @METHOD        Write proper register.
 *
 *
 *
 **------------------------------------------------------------------------ */
void MMUWtlDisable(uint32_t baseAddr);

/* ------------------------------------------------------------------------***
 * @FUNCTION      MMU_Enable
 *
 * @BRIEF         Enable MMU
 *
 * @param[in]     baseAddr    Base address of the instance
 *
 * @RETURNS       void
 *
 * @DESCRIPTION   Enable MMU.
 *
 * @METHOD        Write proper register.
 *
 *
 *
 **------------------------------------------------------------------------ */
void MMUEnable(uint32_t baseAddr);

/* ------------------------------------------------------------------------***
 * @FUNCTION      MMUDisable
 *
 * @BRIEF         Disable MMU
 *
 * @param[in]     baseAddr    Base address of the instance
 *
 * @RETURNS       void
 *
 * @DESCRIPTION   Disable MMU.
 *
 * @METHOD        Write proper register.
 *
 *
 *
 **------------------------------------------------------------------------ */
void MMUDisable(uint32_t baseAddr);

/* ------------------------------------------------------------------------***
 * @FUNCTION      MMULoadTLB
 *
 * @BRIEF         Load an entry into TLB
 *
 * @param[in]     baseAddr    Base address of the instance
 *
 * @RETURNS       void
 *
 * @DESCRIPTION   Load TLB.
 *
 * @METHOD        Write proper register.
 *
 *
 *
 **------------------------------------------------------------------------ */
void MMULoadTLB(uint32_t baseAddr);

/* ------------------------------------------------------------------------***
 * @FUNCTION      MMUWriteCAM
 *
 * @BRIEF         Write to CAM Register
 *
 * @param[in]     baseAddr    Base address of the instance
 * @param[in]     cam         CAM value to be entered
 *
 * @RETURNS       void
 *
 * @DESCRIPTION   Write to CAM Register.
 *
 * @METHOD        Write proper register.
 *
 *
 *
 **------------------------------------------------------------------------ */
void MMUWriteCAM(uint32_t baseAddr, uint32_t cam);

/* ------------------------------------------------------------------------***
 * @FUNCTION      MMUWriteRAM
 *
 * @BRIEF         Write to RAM Register
 *
 * @param[in]     baseAddr    Base address of the instance
 * @param[in]     ram         RAM value to be entered
 *
 * @RETURNS       void
 *
 * @DESCRIPTION   Write to RAM Register.
 *
 * @METHOD        Write proper register.
 *
 *
 *
 **------------------------------------------------------------------------ */
void MMUWriteRAM(uint32_t baseAddr, uint32_t ram);

/* ------------------------------------------------------------------------***
 * @FUNCTION      MMUReadCAM
 *
 * @BRIEF         Read CAM value
 *
 * @param[in]     baseAddr    Base address of the instance
 *
 * @RETURNS       CAM value
 *
 * @DESCRIPTION   Read CAM value
 *
 * @METHOD        Write proper register.
 *
 *
 *
 **------------------------------------------------------------------------ */
uint32_t MMUReadCAM(uint32_t baseAddr);

/* ------------------------------------------------------------------------***
 * @FUNCTION      MMUReadRAM
 *
 * @BRIEF         Read RAM value
 *
 * @param[in]     baseAddr    Base address of the instance
 *
 * @RETURNS       RAM value
 *
 * @DESCRIPTION   Read RAM value
 *
 * @METHOD        Write proper register.
 *
 *
 *
 **------------------------------------------------------------------------ */
uint32_t MMUReadRAM(uint32_t baseAddr);

/* ------------------------------------------------------------------------***
 * @FUNCTION      MMUFaultAddrGet
 *
 * @BRIEF         Read fault address
 *
 * @param[in]     baseAddr    Base address of the instance
 *
 * @RETURNS       fault address
 *
 * @DESCRIPTION   Read fault address
 *
 * @METHOD        Write proper register.
 *
 *
 *
 **------------------------------------------------------------------------ */
uint32_t MMUFaultAddrGet(uint32_t baseAddr);

/* ------------------------------------------------------------------------***
 * @FUNCTION      MMUTTBGet
 *
 * @BRIEF         Read TTB value
 *
 * @param[in]     baseAddr    Base address of the instance
 *
 * @RETURNS       TTB value
 *
 * @DESCRIPTION   Read TTB value
 *
 * @METHOD        Write proper register.
 *
 *
 *
 **------------------------------------------------------------------------ */
uint32_t MMUTTBGet(uint32_t baseAddr);

/* ------------------------------------------------------------------------***
 * @FUNCTION      MMUTTBSet
 *
 * @BRIEF         sets TTB value
 *
 * @param[in]     baseAddr    Base address of the instance
 * @param[in]     ttb         TTB value to be set
 *
 * @RETURNS       void
 *
 * @DESCRIPTION   sets TTB value
 *
 * @METHOD        Write proper register.
 *
 *
 *
 **------------------------------------------------------------------------ */
void MMUTTBSet(uint32_t baseAddr, uint32_t ttb);

/* ------------------------------------------------------------------------***
 * @FUNCTION      MMUTlbEntrySet
 *
 * @BRIEF         Fill MMU TLB Entry
 *
 * @param[in]     baseAddr    Base address of the instance
 * @param[in]     tlbEntry     uint32_t entry to be set in MMU
 * @param[in]     mmuTlbEntry  MMU_TlbEntry_t * pointer to MMU Table Entry
 *
 * @RETURNS       MMU_Return_t    RET_OK                   No errors occured
 *
 * @DESCRIPTION   Configure one MMU Table entry.
 *
 * @METHOD        Fill all necessary registers to properly configure one MMU
 *                Table entry.
 *
 *
 **------------------------------------------------------------------------ */
MMU_Return_t MMUTlbEntrySet(uint32_t              baseAddr,
                            uint32_t              tlbEntry,
                            const MMU_TlbEntry_t *mmuTlbEntry);
/* -----------------------------------------------------------------------***
 * @TYPE         MMUMixedSize_t
 *
 * @BRIEF        MMU element size
 *
 * @DESCRIPTION  Enumerated Type used to specify whther to follow CPU/TLB
 *               Element siz
 *
 **----------------------------------------------------------------------- */

typedef enum MMUMixedSize
{
    MMU_TLBES,
    MMU_CPUES
} MMUMixedSize_t;
/* -----------------------------------------------------------------------***
 * @TYPE         MMUFault_t
 *
 * @BRIEF        MMU fault type
 *
 * @DESCRIPTION  Enumerated Type used to specify the particular fault to be
 *               generated
 *
 **----------------------------------------------------------------------- */
typedef enum MMUfault
{
    MMU_NO_FAULT,
    MMU_FAULT_DESC1,
    MMU_FAULT_DESC2
} MMUFault_t;

/* ------------------------------------------------------------------------***
 * @FUNCTION      MMUSuperSection
 *
 * @BRIEF         Fill MMU page table supersection
 *
 * @param[in]     physicalAddr     physical address
 * @param[in]     virtualAddr      virtual address
 * @param[in]     TTB              translation table base addr
 * @param[in]     endianism        endianness
 * @param[in]     elementSize      element size of the page
 * @param[in]     mixedSize        mixed page attribute
 * @param[in]     faultType        fault type
 *
 *
 * @RETURNS       MMU_Return_t    RET_OK                   No errors occured
 *
 * @DESCRIPTION   Configure one MMU supersection  entry.
 *
 * @METHOD         Fill  necessary memory location to properly configure one MMU
 *                supersection entry.
 *
 *
 **------------------------------------------------------------------------ */
MMU_Return_t  MMUSuperSection(
    const uint32_t    physicalAddr,
    const uint32_t    virtualAddr,
    const uint32_t    TTB,
    MMU_Endianness_t  endianism,
    MMU_ElementSize_t elementSize,
    MMUMixedSize_t    mixedSize,
    MMUFault_t        faultType
    );

/* ------------------------------------------------------------------------***
 * @FUNCTION      MMUSection
 *
 * @BRIEF         Fill MMU page table section
 *
 * @param[in]     physicalAddr     physical address
 * @param[in]     virtualAddr      virtual address
 * @param[in]     TTB              translation table base addr
 * @param[in]     endianism        endianness
 * @param[in]     elementSize      element size of the page
 * @param[in]     mixedSize        mixed page attribute
 * @param[in]     faultType        fault type
 *
 *
 * @RETURNS       MMU_Return_t    RET_OK                   No errors occured
 *
 * @DESCRIPTION   Configure one MMU section  entry.
 *
 * @METHOD         Fill  necessary memory location to properly configure one MMU
 *                 section entry.
 *
 *
 **------------------------------------------------------------------------ */

MMU_Return_t MMUSection(
    const uint32_t    physicalAddr,
    const uint32_t    virtualAddr,
    const uint32_t    TTB,
    MMU_Endianness_t  endianism,
    MMU_ElementSize_t elementSize,
    MMUMixedSize_t    mixedSize,
    MMUFault_t        faultType
    );

/* ------------------------------------------------------------------------***
 * @FUNCTION      MMUCoarseLargePage
 *
 * @BRIEF         Fill MMU page table CoarseLargePage entry
 *
 * @param[in]     physicalAddr     physical address
 * @param[in]     virtualAddr      virtual address
 * @param[in]     TTB              translation table base addr
 * @param[in]     pageTableBase   page  table base addr
 * @param[in]     endianism        endianness
 * @param[in]     elementSize      element size of the page
 * @param[in]     mixedSize        mixed page attribute
 * @param[in]     faultType        fault type
 *
 *
 * @RETURNS       MMU_Return_t    RET_OK                   No errors occured
 *
 * @DESCRIPTION   Configure one MMU CoarseLargePage  entry.
 *
 * @METHOD         Fill  necessary memory location to properly configure one MMU
 *                 CoarseLargePage entry.
 *
 *
 **------------------------------------------------------------------------ */
MMU_Return_t MMUCoarseLargePage(
    const uint32_t    physicalAddr,
    const uint32_t    virtualAddr,
    const uint32_t    TTB,
    const uint32_t    pageTableBase,
    MMU_Endianness_t  endianism,
    MMU_ElementSize_t elementSize,
    MMUMixedSize_t    mixedSize,
    MMUFault_t        faultType
    );

/* ------------------------------------------------------------------------***
 * @FUNCTION      MMUCoarseSmallPage
 *
 * @BRIEF         Fill MMU page table CoarseSmallPage
 *
 * @param[in]     physicalAddr     physical address
 * @param[in]     virtualAddr      virtual address
 * @param[in]     TTB              translation table base addr
 * @param[in]     pageTableBase    page table base addr
 * @param[in]     endianism        endianness
 * @param[in]     elementSize      element size of the page
 * @param[in]     mixedSize        mixed page attribute
 * @param[in]     faultType        fault type
 *
 *
 * @RETURNS       MMU_Return_t    RET_OK                   No errors occured
 *
 * @DESCRIPTION   Configure one MMU CoarseSamllPage  entry.
 *
 * @METHOD         Fill  necessary memory location to properly configure one MMU
 *                 CoarseSmallPage entry.
 *
 *
 **------------------------------------------------------------------------ */
MMU_Return_t MMUCoarseSmallPage(
    const uint32_t    physicalAddr,
    const uint32_t    virtualAddr,
    const uint32_t    TTB,
    const uint32_t    pageTableBase,
    MMU_Endianness_t  endianism,
    MMU_ElementSize_t elementSize,
    MMUMixedSize_t    mixedSize,
    MMUFault_t        faultType
    );

#if 1

#endif

#ifdef __cplusplus
}
#endif
#endif  /* MMU_H_ */
/* EOF */

