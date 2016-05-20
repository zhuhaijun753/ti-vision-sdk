/* =============================================================================
 *
 *            TEXAS INSTRUMENTS INCORPORATED PROPRIETARY INFORMATION
 *
 *  Property of Texas Instruments
 *  For Unrestricted Internal Use Only
 *  Unauthorized reproduction and/or distribution is strictly
 *  prohibited.
 *  This product is protected under copyright law and trade secret law
 *  as an unpublished work.
 *  Created 2008, (C) Copyright 2008 Texas Instruments.  All rights
 *  reserved.
 *
 *
 *  @Component    TESLASS_MMU
 *
 *  @Filename     mmu.h
 *
 *  @Description  TeslaSS/Ducati L3 MMU
 *
 *   Available Functions:
 *             EVE_MMU_CurrentVictimSet    - Set Current Victim
 *             EVE_MMU_CurrentVictimGet    - Get Current Victim
 *             EVE_MMU_TlbLockSet          - Set Base Lock Value
 *             EVE_MMU_TlbLockGet          - Get Base Lock Value
 *             EVE_MMU_GlobalFlush         - MMU Global FLush
 *             EVE_MMU_TlbEntryFlush       - MMU Tlb entry Flush
 *             EVE_EVE_MMU_SoftReset           - Reset MMU
 *             EVE_MMU_IrqGetStatus        - Get MMU Irq Status
 *             EVE_MMU_IrqClearStatus      - Clear MMU Irq Status
 *             EVE_EVE_MMU_IrqEnable           - Enable MMU Irq
 *             EVE_EVE_MMU_IrqDisable          - Disable MMU Irq
 *             EVE_EVE_MMU_WtlEnable           - Enable Walking Table Logic
 *             EVE_EVE_MMU_WtlDisable          - Disable Walking Table Logic
 *             EVE_EVE_MMU_Enable              - Enable MMU
 *             EVE_EVE_MMU_Disable             - Disable MMU
 *             EVE_MMU_TlbEntrySet         - Configure Selected TLB Entry
 *
 *  Domain:                 Tesla SS, Ducati
 *
 *//*======================================================================== */
/**
*  @file       mbox.h
*
*  @brief      The mailbox library component offers basic mailbox
*              functionality that can be used to transmit 32-bit messages
*              between CPUs using the OMAP4.0 Mailbox
*
*  This header provides all mailbox APIs supported by EVE
*
*/

/**
*  @brief    UWORD64
*
*  @brief      unsigned long word
*
*/
#ifndef MMU_H
#define MMU_H

typedef unsigned long long  UWORD64;

/* =============================================================================
 * INCLUDE FILES (only if necessary)
 * =============================================================================
 */

#ifdef __cplusplus
extern "C"
{
#endif

/* =============================================================================
 * EXPORTED DEFINITIONS
 * =============================================================================
 */

/*-------------------------------------------------------------------------*//*
 * @DEFINITION   <Identifier>
 *
 * @BRIEF        <Brief description of macro>
 *
 * @DESCRIPTION  <Detailed description of macro>
 *
 *//*------------------------------------------------------------------------ */

/* -----------------------------------------------------------------------*//**
 * @brief         MMU_IntType_t
 *
 * @brief        Interrupt enable/status types
 *
 * @details      Enumerated Type used to specify Interrupt enable/status for MMU
 *
 *//*----------------------------------------------------------------------- */
typedef enum MMU_IntType
{
    MMU_INT_TLBMiss          = 0x01U,          /**< TLBMiss          */
    MMU_INT_TranslationFault = 0x02U,          /**< TranslationFault */
    MMU_INT_EMUMiss          = 0x04U,          /**< EMUMiss          */
    MMU_INT_TableWalkFault   = 0x08U,          /**< TableWalkFault   */
    MMU_INT_MultiHitFault    = 0x10U,          /**< MultiHitFault    */
    MMU_INT_All              = 0x1FU           /**< All              */

} MMU_IntType_t;



/* -----------------------------------------------------------------------*//**
 * @brief         MMU_PageSize_t
 *
 * @brief        Page Size
 *
 * @details      Enumerated Type used to specify Page size
 *
 *//*----------------------------------------------------------------------- */
typedef enum MMU_PageSize
{
  MMU_Section_Size       = 0x0, /**< 1MB */
  MMU_Large_Size         = 0x1, /**< 64KB */
  MMU_Small_Size         = 0x2, /**< 4KB */
  MMU_SuperSection_Size  = 0x3  /**< 16 MB */
} MMU_PageSize_t;


/* -----------------------------------------------------------------------*//**
 * @brief         MMU_Endianness_t
 *
 * @brief        MMU Endianness translation
 *
 * @details      Enumerated Type used to specify Endianness
 *
 *//*----------------------------------------------------------------------- */
typedef enum MMU_Endianness
{
    MMU_Little_Endian       = 0x0,      /**< little endian */
    MMU_Big_Endian          = 0x1       /**< big endian */
} MMU_Endianness_t;


/* -----------------------------------------------------------------------*//**
 * @brief         MMU_ElementSize_t
 *
 * @brief        Element Size
 *
 * @details      Enumerated Type used to specify Element size
 *
 *//*----------------------------------------------------------------------- */
typedef enum MMU_ElementSize
{
    MMU_Byte_ElementSize           = 0x0,       /**< Byte */
    MMU_Short_ElementSize          = 0x1,       /**< Short */
    MMU_Long_ElementSize           = 0x2,       /**< Long */
    MMU_NoTranslation_ElementSize  = 0x3        /**< No translation */
} MMU_ElementSize_t;


/* -----------------------------------------------------------------------*//**
 * @brief         MMU_MixedPageAttr_t
 *
 * @brief        MMU Mixed Page Attribute
 *
 * @details      Enumerated Type used to Mixed Page Attribute use
 *
 *//*----------------------------------------------------------------------- */
typedef enum MMU_MixedPageAttr
{
    MMU_TLB_ElementSize       = 0x0,           /**< tlb element size */
    MMU_CPU_ElementSize       = 0x1            /**< cpu element size */
} MMU_MixedPageAttr_t;

/* =============================================================================
 * EXPORTED TYPES
 * =============================================================================
 */

/*-------------------------------------------------------------------------*//**
 * @brief         MMU_TlbEntry_t
 *
 * @brief        MMU Table entry descriptor
 *
 * @details      Structure holding all MMU Table Entry parameters
 *
 *//*------------------------------------------------------------------------ */
typedef struct MMU_TlbEntry
{
    UWORD32              phyAddr;                  /**< physical address */
    UWORD32              virtAddr;                 /**< virtual address */
    UWORD32              valid;                    /**< valid entry */
    MMU_PageSize_t       pageSize;                 /**< page size */
    MMU_Endianness_t     endianness;               /**< endian format */
    MMU_ElementSize_t    elementSize;              /**< element size */
    MMU_MixedPageAttr_t  tlbElementSize;           /**< tlb element size */
    UWORD32              preserve;                 /**< reserved field */

} MMU_TlbEntry_t;

/*-------------------------------------------------------------------------*//**
 * @brief         MMU_TlbEntry_extended
 *
 * @brief        MMU Table entry descriptor
 *
 * @details      Structure holding all MMU Table Entry parameters
 *
 *//*------------------------------------------------------------------------ */
typedef struct MMU_TlbEntry_extended
{
    UWORD64              phyAddr;           /**< physical address */
    UWORD32              virtAddr;          /**< virtual address */
    UWORD32              valid;             /**< valid entry */
    MMU_PageSize_t       pageSize;          /**< page size */
    UWORD32              preserve;          /**< reserved field */

} MMU_TlbEntry_extended_t;



/* =============================================================================
 * EXPORTED VARIABLES
 * =============================================================================
 */

/*-------------------------------------------------------------------------*//*
 * @VARIABLE     <Identifier>
 *
 * @BRIEF        <type> <Identifier> - <Brief description of variable>
 *
 * @DESCRIPTION  <Detailed description of variable>
 *
 *//*------------------------------------------------------------------------ */


/* =============================================================================
 * EXPORTED FUNCTIONS
 * =============================================================================
 */

/* ------------------------------------------------------------------------*//**
 * @brief            EVE_MMU_CurrentVictimSet
 *
 * @brief         Set Tlb Entry in Lock register
 *
 * @param[in]     component    CRED_index_t Name of the instance
 * @param[in]     tlbEntry     UWORD32 entry to be set in MMU
 *
 * @return        None
 *
 * @details       Set Current Victim in Lock register.
 *
 * @remarks        Fill Lock register current victim. Do not modify Locked entries.
 *
 *
 *
 *//*------------------------------------------------------------------------ */
extern void EVE_MMU_CurrentVictimSet ( CRED_index_t component, UWORD32 tlbEntry );


/* ------------------------------------------------------------------------*//**
 * @brief            EVE_MMU_CurrentVictimGet
 *
 * @brief         Set Tlb Entry in Lock register
 *
 * @param[in]     component    CRED_index_t Name of the instance
 *
 * @return        UWORD32 Value from Lock register
 *
 * @details       Get Current Victim from Lock register.
 *
 * @remarks        Return  Lock register current victim.
 *
 *
 *
 *//*------------------------------------------------------------------------ */
extern UWORD32 EVE_MMU_CurrentVictimGet ( CRED_index_t component );


/* ------------------------------------------------------------------------*//**
 * @brief            EVE_MMU_TlbLockSet
 *
 * @brief         Set Tlb Lock entry in Lock register
 *
 * @param[in]     component    CRED_index_t Name of the instance
 * @param[in]     tlbEntry     UWORD32 entry to be locked in MMU
 *
 * @return        None
 *
 * @details       Set Tlb Lock in Lock register.
 *
 * @remarks        Fill Lock register Base Value. Do not modify victim entries.
 *
 *
 *
 *//*------------------------------------------------------------------------ */
extern void EVE_MMU_TlbLockSet ( CRED_index_t component, UWORD32 tlbEntry );


/* ------------------------------------------------------------------------*//**
 * @brief            EVE_MMU_TlbLockGet
 *
 * @brief         Set Tlb Lock entry in Lock register
 *
 * @param[in]     component    CRED_index_t Name of the instance
 *
 * @return        UWORD32
 *
 * @details       Get Tlb Base Lock from Lock register.
 *
 * @remarks        Get Lock register Base Value.
 *
 *
 *
 *//*------------------------------------------------------------------------ */
extern UWORD32 EVE_MMU_TlbLockGet ( CRED_index_t component );


/* ------------------------------------------------------------------------*//**
 * @brief            EVE_MMU_GlobalFlush
 *
 * @brief         Flush all MMU entries
 *
 * @param[in]     component    CRED_index_t Name of the instance
 *
 * @return        void
 *
 * @details       Flush all Tlb entrties in MMU.
 *
 * @remarks        Write proper register.
 *
 *
 *
 *//*------------------------------------------------------------------------ */
extern void EVE_MMU_GlobalFlush( CRED_index_t component );


/* ------------------------------------------------------------------------*//**
 * @brief            EVE_MMU_TlbEntryFlush
 *
 * @brief         Flush all MMU entries
 *
 * @param[in]     component    CRED_index_t Name of the instance
 * @param[in]     virtAddress  UWORD32 Virtual Address of entry to be flushed
 *
 * @return        void
 *
 * @details       Flush Specific Tlb entrties in MMU pointed by specified Virt. Addr.
 *
 * @remarks        Write proper registers.
 *
 *
 *
 *//*------------------------------------------------------------------------ */
extern void EVE_MMU_TlbEntryFlush( CRED_index_t component, UWORD32 virtAddress );



/* ------------------------------------------------------------------------*//**
 * @brief            EVE_EVE_MMU_SoftReset
 *
 * @brief         Reset MMU
 *
 * @param[in]     component    CRED_index_t Name of the instance
 *
 * @return        void
 *
 * @details       Reset MMU and wait for reset done
 *
 * @remarks        Set reset bit and wait for reset done.
 *
 *
 *
 *//*------------------------------------------------------------------------ */
extern void EVE_MMU_SoftReset( CRED_index_t component );



/* ------------------------------------------------------------------------*//**
 * @brief            EVE_MMU_IrqGetStatus
 *
 * @brief         Get MMU Irq Status
 *
 * @param[in]     component    CRED_index_t Name of the instance
 *
 * @return        void
 *
 * @details       Get Current MMU.
 *
 * @remarks        Read proper register.
 *
 *
 *
 *//*------------------------------------------------------------------------ */
UWORD32 EVE_MMU_IrqGetStatus ( CRED_index_t component );


/* ------------------------------------------------------------------------*//**
 * @brief            EVE_MMU_IrqClearStatus
 *
 * @brief         Clear MMU Irq Status
 *
 * @param[in]     component    CRED_index_t Name of the instance
 * @param[in]     intType      MMU_IntType_t interrupt Type to Clear
 *
 * @return        void
 *
 * @details       Clear Current MMU.
 *
 * @remarks        Write proper register.
 *
 *
 *
 *//*------------------------------------------------------------------------ */
void EVE_MMU_IrqClearStatus ( CRED_index_t component, MMU_IntType_t intType );




/* ------------------------------------------------------------------------*//**
 * @brief            EVE_EVE_MMU_IrqEnable
 *
 * @brief         Get MMU Irq Status
 *
 * @param[in]     component    CRED_index_t Name of the instance
 * @param[in]     intType      MMU_IntType_t interrupt Type to enable
 *
 * @return        void
 *
 * @details       Enable selected interrupt
 *
 * @remarks        Write proper register.
 *
 *
 *
 *//*------------------------------------------------------------------------ */
void EVE_MMU_IrqEnable ( CRED_index_t component, MMU_IntType_t intType );



/* ------------------------------------------------------------------------*//**
 * @brief            EVE_EVE_MMU_IrqDisable
 *
 * @brief         Get MMU Irq Status
 *
 * @param[in]     component    CRED_index_t Name of the instance
 * @param[in]     intType      MMU_IntType_t interrupt Type to be disabled
 *
 * @return        void
 *
 * @details       Disable selected interrupt
 *
 * @remarks        Write proper register.
 *
 *
 *
 *//*------------------------------------------------------------------------ */
void EVE_MMU_IrqDisable ( CRED_index_t component, MMU_IntType_t intType );



/* ------------------------------------------------------------------------*//**
 * @brief            EVE_EVE_MMU_WtlEnable
 *
 * @brief         Enable MMU Walking table logic
 *
 * @param[in]     component    CRED_index_t Name of the instance
 *
 * @return        void
 *
 * @details       Enable MMU Walking table logic.
 *
 * @remarks        Write proper register.
 *
 *
 *
 *//*------------------------------------------------------------------------ */
extern void EVE_MMU_WtlEnable ( CRED_index_t component );



/* ------------------------------------------------------------------------*//**
 * @brief            EVE_EVE_MMU_WtlDisable
 *
 * @brief         Disable MMU Walking table logic
 *
 * @param[in]     component    CRED_index_t Name of the instance
 *
 * @return        void
 *
 * @details       Disable MMU Walking table logic.
 *
 * @remarks        Write proper register.
 *
 *
 *
 *//*------------------------------------------------------------------------ */
extern void EVE_MMU_WtlDisable ( CRED_index_t component );



/* ------------------------------------------------------------------------*//**
 * @brief            EVE_EVE_MMU_Enable
 *
 * @brief         Enable MMU
 *
 * @param[in]     component    CRED_index_t Name of the instance
 *
 * @return        void
 *
 * @details       Enable MMU.
 *
 * @remarks        Write proper register.
 *
 *
 *
 *//*------------------------------------------------------------------------ */
extern void EVE_MMU_Enable ( CRED_index_t component );



/* ------------------------------------------------------------------------*//**
 * @brief            EVE_MMU_Disable
 *
 * @brief         Disable MMU
 *
 * @param[in]     component    CRED_index_t Name of the instance
 *
 * @return        void
 *
 * @details       Disable MMU.
 *
 * @remarks        Write proper register.
 *
 *
 *
 *//*------------------------------------------------------------------------ */
extern void EVE_MMU_Disable ( CRED_index_t component );


/* ------------------------------------------------------------------------*//**
 * @brief            EVE_MMU_TlbEntrySet_Coherency
 *
 * @brief         Set Coherency
 *
 * @param[in]     component    CRED_index_t Name of the instance
 * @param[in]     tlbEntry    UWORD32 Table entry
 * @param[in]     mmuTlbEntry    MMU_TlbEntry_t MMU entry
 * @param[in]     Coherency    UWORD32 Name of the instance
 *
 * @return        ReturnCode_t
 *
 * @details        Set Coherency
 *
 * @remarks        Write proper register.
 *
 *
 *
 *//*------------------------------------------------------------------------ */
extern ReturnCode_t EVE_MMU_TlbEntrySet_Coherency ( CRED_index_t component,
                                         UWORD32      tlbEntry,
                                         const MMU_TlbEntry_t *mmuTlbEntry,
                                         UWORD32 Coherency );


/* ------------------------------------------------------------------------*//**
 * @brief            EVE_MMU_TlbEntrySet
 *
 * @brief         Fill MMU TLB Entry
 *
 * @param[in]     component    CRED_index_t Name of the instance
 * @param[in]     tlbEntry     UWORD32 entry to be set in MMU
 * @param[in]     mmuTlbEntry  MMU_TlbEntry_t * pointer to MMU Table Entry
 *
 * @return        ReturnCode_t    RET_OK                   No errors occured
 *
 * @details       Configure one MMU Table entry.
 *
 * @remarks        Fill all necessary registers to properly configure one MMU
 *                Table entry.
 *
 *
 *//*------------------------------------------------------------------------ */
extern ReturnCode_t EVE_MMU_TlbEntrySet ( CRED_index_t component,
                                      UWORD32 tlbEntry,
                                      const MMU_TlbEntry_t *mmuTlbEntry );
/* -----------------------------------------------------------------------*//**
 * @brief         MMUMixedSize_t
 *
 * @brief        MMU element size
 *
 * @details      Enumerated Type used to specify whther to follow CPU/TLB Element siz
 *
 *//*----------------------------------------------------------------------- */


/* ------------------------------------------------------------------------*//**
 * @brief            EVE_MMU_TlbEntrySet_Extended
 *
 * @brief         Fill MMU TLB Entry
 *
 * @param[in]     component    CRED_index_t Name of the instance
 * @param[in]     tlbEntry     UWORD32 entry to be set in MMU
 * @param[in]     mmuTlbEntry_extended  MMU_TlbEntry_t * pointer to MMU Table Entry
 *
 * @return        ReturnCode_t    RET_OK                   No errors occured
 *
 * @details       Configure one MMU Table entry.
 *
 * @remarks        Fill all necessary registers to properly configure one MMU
 *                Table entry.
 *
 *
 *//*------------------------------------------------------------------------ */
ReturnCode_t EVE_MMU_TlbEntrySet_Extended ( CRED_index_t component,
                                        UWORD32 tlbEntry,
                                        const MMU_TlbEntry_extended_t *mmuTlbEntry_extended );

typedef enum MMUMixedSize
{
    MMU_TLBES,
    MMU_CPUES

} MMUMixedSize_t;
/* -----------------------------------------------------------------------*//**
 * @brief         MMUFault_t
 *
 * @brief        MMU fault type
 *
 * @details      Enumerated Type used to specify the particular fault to be generated
 *
 *//*----------------------------------------------------------------------- */
typedef enum MMUfault
{
    MMU_NO_FAULT,
    MMU_FAULT_DESC1,
    MMU_FAULT_DESC2

} MMUFault_t;

/* ------------------------------------------------------------------------*//**
 * @brief            EVE_MMU_SuperSection
 *
 * @brief         Fill MMU page table supersection
 *
 * @param[in]     physicalAddr     physical address
 * @param[in]     virtualAddr      virtual address
 * @param[in]     TTB              translation table base addr
 * @param[in]     endianism        endianness
 * @param[in]     elementSize1      element size of the page
 * @param[in]     mixedSize        mixed page attribute
 * @param[in]     faultType        fault type


 * @return        ReturnCode_t    RET_OK                   No errors occured
 *
 * @details       Configure one MMU supersection  entry.
 *
 * @remarks         Fill  necessary memory location to properly configure one MMU
 *                supersection entry.
 *
 *
 *//*------------------------------------------------------------------------ */
extern ReturnCode_t  EVE_MMU_SuperSection(
                             const UWORD32      physicalAddr,
                             const UWORD32      virtualAddr,
                             const UWORD32      TTB ,
                             MMU_Endianness_t     endianism,
                             MMU_ElementSize_t   elementSizeA,
                             MMUMixedSize_t     mixedSize,
                             MMUFault_t         faultType
                             );

/* ------------------------------------------------------------------------*//**
 * @brief            EVE_MMU_Section
 *
 * @brief         Fill MMU page table section
 *
 * @param[in]     physicalAddr     physical address
 * @param[in]     virtualAddr      virtual address
 * @param[in]     TTB              translation table base addr
 * @param[in]     endianism        endianness
 * @param[in]     elementSize2      element size of the page
 * @param[in]     mixedSize        mixed page attribute
 * @param[in]     faultType        fault type


 * @return        ReturnCode_t    RET_OK                   No errors occured
 *
 * @details       Configure one MMU section  entry.
 *
 * @remarks         Fill  necessary memory location to properly configure one MMU
 *                 section entry.
 *
 *
 *//*------------------------------------------------------------------------ */

extern ReturnCode_t EVE_MMU_Section(
                        const UWORD32      physicalAddr,
                        const UWORD32      virtualAddr,
                        const UWORD32      TTB ,
                        MMU_Endianness_t     endianism,
                        MMU_ElementSize_t   elementSizeB,
                        MMUMixedSize_t     mixedSize,
                        MMUFault_t         faultType
                        );

/* ------------------------------------------------------------------------*//**
 * @brief            EVE_MMU_CoarseLargePage
 *
 * @brief         Fill MMU page table CoarseLargePage entry
 *
 * @param[in]     physicalAddr     physical address
 * @param[in]     virtualAddr      virtual address
 * @param[in]     TTB              translation table base addr
 * @param[in]     pageTableBase   page  table base addr
 * @param[in]     endianism        endianness
 * @param[in]     elementSize3      element size of the page
 * @param[in]     mixedSize        mixed page attribute
 * @param[in]     faultType        fault type


 * @return        ReturnCode_t    RET_OK                   No errors occured
 *
 * @details       Configure one MMU CoarseLargePage  entry.
 *
 * @remarks         Fill  necessary memory location to properly configure one MMU
 *                 CoarseLargePage entry.
 *
 *
 *//*------------------------------------------------------------------------ */
extern ReturnCode_t EVE_MMU_CoarseLargePage(
                                const UWORD32      physicalAddr,
                                const UWORD32      virtualAddr,
                                const UWORD32      TTB,
                                const UWORD32      pageTableBase,
                                MMU_Endianness_t     endianism,
                                MMU_ElementSize_t   elementSize__,
                                MMUMixedSize_t     mixedSize,
                                MMUFault_t         faultType
                                );

/* ------------------------------------------------------------------------*//**
 * @brief            EVE_MMU_CoarseSmallPage
 *
 * @brief         Fill MMU page table CoarseSmallPage
 *
 * @param[in]     physicalAddr     physical address
 * @param[in]     virtualAddr      virtual address
 * @param[in]     TTB              translation table base addr
 * @param[in]     pageTableBase    page table base addr
 * @param[in]     endianism        endianness
 * @param[in]     elementSize      element size of the page
 * @param[in]     mixedSize        mixed page attribute
 * @param[in]     faultType        fault type


 * @return        ReturnCode_t    RET_OK                   No errors occured
 *
 * @details       Configure one MMU CoarseSamllPage  entry.
 *
 * @remarks         Fill  necessary memory location to properly configure one MMU
 *                 CoarseSmallPage entry.
 *
 *
 *//*------------------------------------------------------------------------ */
extern ReturnCode_t EVE_MMU_CoarseSmallPage(
                                const UWORD32      physicalAddr,
                                const UWORD32      virtualAddr,
                                const UWORD32      TTB,
                                const UWORD32      pageTableBase,
                                MMU_Endianness_t     endianism,
                                MMU_ElementSize_t   elementSize_,
                                MMUMixedSize_t     mixedSize,
                                MMUFault_t         faultType
                                );

#ifdef __cplusplus
}
#endif
#endif	/* MMU_H */
/* EOF */

