/* $Header: <fileName>.c	<lastVersionNumber>    	<lastEditionDate>
 * =============================================================================
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
 */
/**
 *  @Component    TESLASS_MMU
 *
 *  @Filename     mmu.c
 *
 *  @Description  TeslaSS/Ducati L3 MMU
 *
 *//*======================================================================== */


/* =============================================================================
 * STANDARD INCLUDE FILES
 * =============================================================================
 */
#include "GlobalTypes.h"
#include "cram.h"

#pragma CHECK_MISRA ("none")
#include "baseaddress.h"
#include "teslass_mmu_cred.h"
#pragma RESET_MISRA ("required")

#include "mmu.h"

/* =============================================================================
 * PROJECT SPECIFIC INCLUDE FILES
 * =============================================================================
 */

/* =============================================================================
 * GLOBAL VARIABLES DECLARATIONS
 * =============================================================================
 */

/*-------------------------------------------------------------------------*//**
 * @VARIABLE     <Identifier>
 *
 * @BRIEF        <type> <Identifier> - <Brief description of variable>
 *
 * @DESCRIPTION  <Detailed description of variable>
 *
 *//*------------------------------------------------------------------------ */

/* =============================================================================
 * LOCAL TYPES AND DEFINITIONS
 * =============================================================================
 */

/*-------------------------------------------------------------------------*//**
 * @TYPE         <Identifier>
 *
 * @BRIEF        <Brief description of type>
 *
 * @DESCRIPTION  <Detailed description of type>
 *
 *//*------------------------------------------------------------------------ */
/* =============================================================================
 * LOCAL VARIABLES DECLARATIONS
 * =============================================================================
 */
#define MMU_TTB_MASK             0xFFFFC000U
#define MMU_SECTION_ADDR_MASK    0xFFF00000U
#define MMU_SSECTION_ADDR_MASK   0xFF000000U
#define MMU_PAGE_TABLE_MASK      0xFFFFFC00U
#define MMU_LARGE_PAGE_MASK      0xFFFF0000U
#define MMU_SMALL_PAGE_MASK      0xFFFFF000U
#define MMU_ELEMENTSIZE_MAX      3
#define LOWER_32_MASK            0x00000000FFFFFFFFU
#define SHIFT_32                 32

/**
* @brief   CHECK_INPUT_RANGE_MIN0
*
* @brief        Checks an input value and returns a specified value if not in
*               specified range. The minimum value is 0.
*
* @note         Can be disabled to save HW cycles.
*
*
*/
#define CHECK_INPUT_RANGE_MIN0(actualValue, maxValidValue, returnCodeIfMismatch, spyCodeIfMisMatch)

/*-------------------------------------------------------------------------*//**
 * @VARIABLE     <Identifier>
 *
 * @BRIEF        <type> <Identifier> - <Brief description of variable>
 *
 * @DESCRIPTION  <Detailed description of variable>
 *
 *//*------------------------------------------------------------------------ */

/* =============================================================================
 * LOCAL FUNCTIONS PROTOTYPES
 * =============================================================================
 */

/*-------------------------------------------------------------------------*//**
 * @FUNCTION     Function Name
 *
 * @BRIEF        Brief description of function purpose
 *
 * @DESCRIPTION  Detailed description of function purpose
 *
 * @RETURNS      Description of return value
 *
 * @NOTES        This section is optional, delete if unused. Should contain
 *               anything else important about the function, e.g correct usage
 *
 *//*------------------------------------------------------------------------ */


/* =============================================================================
 * FUNCTIONS
 * =============================================================================
 */

/* ======================== Function Separator ============================= */
void EVE_MMU_CurrentVictimSet ( CRED_index_t component, UWORD32 tlbEntry )
{

    WR_FIELD_32(component,
                TESLASS_MMU__MMU_LOCK,
                TESLASS_MMU__MMU_LOCK__CURRENTVICTIM,
                tlbEntry,
                (UWORD32)TESLASS_MMU__MMU_LOCK__CURRENTVICTIM__POS);

} /* EVE_MMU_CurrentVictimSet() */



/* ======================== Function Separator ============================= */
UWORD32 EVE_MMU_CurrentVictimGet ( CRED_index_t component )
{

    UWORD32 rdVal;

    rdVal = RD_FIELD_32(component,
                        TESLASS_MMU__MMU_LOCK,
                        TESLASS_MMU__MMU_LOCK__CURRENTVICTIM,
                        (UWORD32)TESLASS_MMU__MMU_LOCK__CURRENTVICTIM__POS);

    return rdVal;

} /* EVE_MMU_CurrentVictimGet() */



/* ======================== Function Separator ============================= */
void EVE_MMU_TlbLockSet ( CRED_index_t component, UWORD32 tlbEntry )
{

    WR_FIELD_32(component,
                TESLASS_MMU__MMU_LOCK,
                TESLASS_MMU__MMU_LOCK__BASEVALUE,
                tlbEntry,
                TESLASS_MMU__MMU_LOCK__BASEVALUE__POS);

} /* EVE_MMU_TlbLockSet() */



/* ======================== Function Separator ============================= */
UWORD32 EVE_MMU_TlbLockGet ( CRED_index_t component )
{

    UWORD32 rdVal;

    rdVal = RD_FIELD_32(component,
                        TESLASS_MMU__MMU_LOCK,
                        TESLASS_MMU__MMU_LOCK__BASEVALUE,
                        (UWORD32)TESLASS_MMU__MMU_LOCK__BASEVALUE__POS);

    return rdVal;

} /* EVE_MMU_TlbLockGet() */



/* ======================== Function Separator ============================= */
void EVE_MMU_GlobalFlush( CRED_index_t component )
{

    WR_REG_32( component,
               TESLASS_MMU__MMU_GFLUSH,
               TESLASS_MMU__MMU_GFLUSH__GLOBALFLUSH__FLUSH_W );

} /* EVE_MMU_GlobalFlush() */


/* ======================== Function Separator ============================= */
void EVE_MMU_TlbEntryFlush( CRED_index_t component, UWORD32 virtAddress )
{

    WR_FIELD_32( component,
                 TESLASS_MMU__MMU_CAM,
                 TESLASS_MMU__MMU_CAM__VATAG,
                 virtAddress ,
                 (UWORD32)TESLASS_MMU__MMU_CAM__VATAG__POS);

    WR_REG_32 ( component,
                TESLASS_MMU__MMU_FLUSH_ENTRY,
                TESLASS_MMU__MMU_FLUSH_ENTRY__FLUSHENTRY__FLUSHTLB_W );

} /* EVE_MMU_GlobalFlush() */



/* ======================== Function Separator ============================= */
void EVE_MMU_SoftReset( CRED_index_t component )
{

    UWORD32 resetDone;

    WR_REG_32 ( component,
                TESLASS_MMU__MMU_SYSCONFIG,
                TESLASS_MMU__MMU_SYSCONFIG__SOFTRESET__RSTMODE_W );

    resetDone = 0;
    while ( resetDone==0 )
    {
        resetDone = RD_FIELD_32 ( component,
                                  TESLASS_MMU__MMU_SYSSTATUS,
                                  TESLASS_MMU__MMU_SYSSTATUS__RESETDONE,
                                   TESLASS_MMU__MMU_SYSSTATUS__RESETDONE__POS);
    }


} /* EVE_MMU_SoftReset() */



/* ======================== Function Separator ============================= */
UWORD32 EVE_MMU_IrqGetStatus ( CRED_index_t component )
{

    UWORD32 rdVal;

    rdVal = RD_REG_32 ( component, TESLASS_MMU__MMU_IRQSTATUS );

    rdVal &= (UWORD32)MMU_INT_All;

    return rdVal;

} /* EVE_MMU_IrqGetStatus() */


/* ======================== Function Separator ============================= */
void EVE_MMU_IrqClearStatus ( CRED_index_t component, MMU_IntType_t intType  )
{

    UWORD32 lVal;

    lVal = (UWORD32)intType & (UWORD32)MMU_INT_All;

    WR_REG_32 ( component, TESLASS_MMU__MMU_IRQSTATUS, lVal );

} /* EVE_MMU_IrqGetStatus() */



/* ======================== Function Separator ============================= */
void EVE_MMU_IrqEnable ( CRED_index_t component, MMU_IntType_t intType )
{

    UWORD32 lVal;

    lVal = RD_REG_32 ( component, TESLASS_MMU__MMU_IRQENABLE );
    lVal = (lVal | (UWORD32)intType) & (UWORD32)MMU_INT_All;
    WR_REG_32 ( component, TESLASS_MMU__MMU_IRQENABLE, lVal );

} /* EVE_MMU_IrqEnable() */



/* ======================== Function Separator ============================= */
void EVE_MMU_IrqDisable ( CRED_index_t component, MMU_IntType_t intType )
{

    UWORD32 lVal;

    lVal = RD_REG_32 ( component, TESLASS_MMU__MMU_IRQENABLE );
    lVal = (lVal & ~((UWORD32)intType)) & (UWORD32)MMU_INT_All;
    WR_REG_32 ( component, TESLASS_MMU__MMU_IRQENABLE, lVal );

} /* EVE_MMU_IrqDisable() */



/* ======================== Function Separator ============================= */
void EVE_MMU_WtlEnable ( CRED_index_t component )
{

    WR_FIELD_32 ( component,
                  TESLASS_MMU__MMU_CNTL,
                  TESLASS_MMU__MMU_CNTL__TWLENABLE,
                  (UWORD32)TESLASS_MMU__MMU_CNTL__TWLENABLE__TWLEN,
                   TESLASS_MMU__MMU_CNTL__TWLENABLE__POS                  );

} /* EVE_MMU_WtlEnable() */



/* ======================== Function Separator ============================= */
void EVE_MMU_WtlDisable ( CRED_index_t component )
{

    WR_FIELD_32 ( component,
                  TESLASS_MMU__MMU_CNTL,
                  TESLASS_MMU__MMU_CNTL__TWLENABLE,
                  (UWORD32)TESLASS_MMU__MMU_CNTL__TWLENABLE__TWLDIS,
                   TESLASS_MMU__MMU_CNTL__TWLENABLE__POS);

} /* EVE_MMU_WtlDisable() */



/* ======================== Function Separator ============================= */
void EVE_MMU_Enable ( CRED_index_t component )
{

    WR_FIELD_32 ( component,
                  TESLASS_MMU__MMU_CNTL,
                  TESLASS_MMU__MMU_CNTL__MMUENABLE,
                  (UWORD32)TESLASS_MMU__MMU_CNTL__MMUENABLE__MMUEN,
                    TESLASS_MMU__MMU_CNTL__MMUENABLE__POS);

} /* EVE_MMU_Enable() */



/* ======================== Function Separator ============================= */
void EVE_MMU_Disable ( CRED_index_t component )
{

    WR_FIELD_32 ( component,
                  TESLASS_MMU__MMU_CNTL,
                  TESLASS_MMU__MMU_CNTL__MMUENABLE,
                  (UWORD32)TESLASS_MMU__MMU_CNTL__MMUENABLE__MMUDIS,
                    TESLASS_MMU__MMU_CNTL__MMUENABLE__POS);

} /* EVE_MMU_Enable() */


/* ======================== Function Separator ============================= */
#ifdef VAYU_PLATFORM
ReturnCode_t EVE_MMU_TlbEntrySet_Coherency ( CRED_index_t component,
                                         UWORD32      tlbEntry,
                                         const MMU_TlbEntry_t *mmuTlbEntry,
                                         UWORD32 Coherency )

{

    ReturnCode_t returnCode = RET_OK;
    UWORD32 lVal;
    UWORD32 rd_val;

    /* Check parameters */
    /* Add */

    /* Prepare CAM register Value */
    lVal = mmuTlbEntry->virtAddr & TESLASS_MMU__MMU_CAM__VATAG;
    MASKSET_FIELD(lVal, TESLASS_MMU__MMU_CAM__P, mmuTlbEntry->preserve, TESLASS_MMU__MMU_CAM__P__POS);
    MASKSET_FIELD(lVal, TESLASS_MMU__MMU_CAM__V, mmuTlbEntry->valid, TESLASS_MMU__MMU_CAM__V__POS);
    MASKSET_FIELD(lVal, TESLASS_MMU__MMU_CAM__PAGESIZE, (UWORD32)mmuTlbEntry->pageSize, (UWORD32)TESLASS_MMU__MMU_CAM__PAGESIZE__POS);
    /* Write CAM Register */
    WR_REG_32( component, TESLASS_MMU__MMU_CAM, lVal );

    /* Prepare RAM register Value */
    lVal = mmuTlbEntry->phyAddr & TESLASS_MMU__MMU_RAM__PHYSICALADDRESS;
    /*MASKSET_FIELD(lVal, TESLASS_MMU__MMU_RAM__ENDIANNESS, mmuTlbEntry->endianness);
    MASKSET_FIELD(lVal, TESLASS_MMU__MMU_RAM__ELEMENTSIZE, mmuTlbEntry->elementSize);
    MASKSET_FIELD(lVal, TESLASS_MMU__MMU_RAM__MIXED, mmuTlbEntry->tlbElementSize); */
    /* Write RAM Register */
    WR_REG_32( component, TESLASS_MMU__MMU_RAM, lVal );

    /*Coherency bit */
    rd_val = RD_REG_32( component,TESLASS_MMU__MMU_TTB_MSB);
    lVal = rd_val | Coherency;
    WR_REG_32( component,TESLASS_MMU__MMU_TTB_MSB,lVal);

    /* Set Desired TLB Entry */
    EVE_MMU_CurrentVictimSet ( component, tlbEntry );

    /* Load Tlb */
    WR_REG_32( component, TESLASS_MMU__MMU_LD_TLB,
                          TESLASS_MMU__MMU_LD_TLB__LDTLBITEM__LDTLB_W );


    return returnCode;

} /* MMU_WriteTLBEntry() */

#endif



/* ======================== Function Separator ============================= */
ReturnCode_t EVE_MMU_TlbEntrySet ( CRED_index_t component,
                               UWORD32 tlbEntry,
                               const MMU_TlbEntry_t *mmuTlbEntry )

{

    ReturnCode_t returnCode = RET_OK;
    UWORD32 lVal;

    /* Check parameters */
    /* Add */

    /* Prepare CAM register Value */
    lVal = mmuTlbEntry->virtAddr & TESLASS_MMU__MMU_CAM__VATAG;
    MASKSET_FIELD(lVal, TESLASS_MMU__MMU_CAM__P, mmuTlbEntry->preserve, TESLASS_MMU__MMU_CAM__P__POS);
    MASKSET_FIELD(lVal, TESLASS_MMU__MMU_CAM__V, mmuTlbEntry->valid, TESLASS_MMU__MMU_CAM__V__POS);
    MASKSET_FIELD(lVal, TESLASS_MMU__MMU_CAM__PAGESIZE, (UWORD32)mmuTlbEntry->pageSize, (UWORD32)TESLASS_MMU__MMU_CAM__PAGESIZE__POS);
    /* Write CAM Register */
    WR_REG_32( component, TESLASS_MMU__MMU_CAM, lVal );

    /* Prepare RAM register Value */
    lVal = mmuTlbEntry->phyAddr & TESLASS_MMU__MMU_RAM__PHYSICALADDRESS;
/*  MASKSET_FIELD(lVal, TESLASS_MMU__MMU_RAM__ENDIANNESS, mmuTlbEntry->endianness);
    MASKSET_FIELD(lVal, TESLASS_MMU__MMU_RAM__ELEMENTSIZE, mmuTlbEntry->elementSize);
    MASKSET_FIELD(lVal, TESLASS_MMU__MMU_RAM__MIXED, mmuTlbEntry->tlbElementSize);*/
    /* Write RAM Register */
    WR_REG_32( component, TESLASS_MMU__MMU_RAM, lVal );

    /* Set Desired TLB Entry */
    EVE_MMU_CurrentVictimSet ( component, tlbEntry );

    /* Load Tlb */
    WR_REG_32( component, TESLASS_MMU__MMU_LD_TLB,
                          TESLASS_MMU__MMU_LD_TLB__LDTLBITEM__LDTLB_W );


    return returnCode;

} /* MMU_WriteTLBEntry() */


/* ======================== Function Separator ============================= */
#ifdef VAYU_PLATFORM
ReturnCode_t EVE_MMU_TlbEntrySet_Extended ( CRED_index_t component,
                                        UWORD32 tlbEntry,
                                        const MMU_TlbEntry_extended_t *mmuTlbEntry_extended )

{

    ReturnCode_t returnCode = RET_OK;
    UWORD32 lVal;
    /* Check parameters */
    /* Add */

    /* Prepare CAM register Value */
    lVal = mmuTlbEntry_extended->virtAddr & TESLASS_MMU__MMU_CAM__VATAG;
    MASKSET_FIELD(lVal, TESLASS_MMU__MMU_CAM__P, mmuTlbEntry_extended->preserve, TESLASS_MMU__MMU_CAM__P__POS);
    MASKSET_FIELD(lVal, TESLASS_MMU__MMU_CAM__V, mmuTlbEntry_extended->valid, TESLASS_MMU__MMU_CAM__V__POS);
    MASKSET_FIELD(lVal, TESLASS_MMU__MMU_CAM__PAGESIZE, (UWORD32)mmuTlbEntry_extended->pageSize, (UWORD32)TESLASS_MMU__MMU_CAM__PAGESIZE__POS);
    /* Write CAM Register */
    WR_REG_32( component, TESLASS_MMU__MMU_CAM, lVal );

    /* Prepare RAM register Value */
    lVal = ((UWORD32)((UWORD64)(mmuTlbEntry_extended->phyAddr) & LOWER_32_MASK)) & TESLASS_MMU__MMU_RAM__PHYSICALADDRESS;
    /* Write RAM Register */
    WR_REG_32( component, TESLASS_MMU__MMU_RAM, lVal );
    /* Prepare 32-35 MSB bits of RAM register Value */
    lVal = (((UWORD32)((UWORD64)(mmuTlbEntry_extended->phyAddr)>>SHIFT_32)) & LOWER_32_MASK) & TESLASS_MMU__MMU_RAM_MSB__PA_MSB;
    /* Write RAM-MSB Register */
    WR_REG_32( component, TESLASS_MMU__MMU_RAM_MSB, lVal );

    /* Set Desired TLB Entry */
    EVE_MMU_CurrentVictimSet ( component, tlbEntry );

    /* Load Tlb */
    WR_REG_32( component, TESLASS_MMU__MMU_LD_TLB,
                          TESLASS_MMU__MMU_LD_TLB__LDTLBITEM__LDTLB_W );


    return returnCode;

} /* MMU_WriteTLBEntry_Extended() */
#endif
/* ============================================================================*/
/*              MMU_SuperSection                                               */
/* ============================================================================*/
ReturnCode_t EVE_MMU_SuperSection(
                             const UWORD32      physicalAddr,
                             const UWORD32      virtualAddr,
                             const UWORD32      TTB ,
                             MMU_Endianness_t     endianism,
                             MMU_ElementSize_t   elementSizeA,
                             MMUMixedSize_t     mixedSize,
                             MMUFault_t         faultType
                             )
{
   ReturnCode_t returnCode = RET_OK;
   UWORD32 addrOfL1Desc, l1DescSSection, TTB_13_to_7, VA_31_to_25, desc_13_to_7;

   /*Check the input Parameters*/
   CHECK_INPUT_RANGE_MIN0(elementSizeA,MMU_ELEMENTSIZE_MAX,RET_PARAM_OUT_OF_RANGE,RES_MMU_BASE + RES_INVALID_INPUT_PARAM);

   /* Generate the ADDRESS of First Level Descriptor for a Super section address */
   TTB_13_to_7  =  (TTB >> 7U) & 0x0000007FU ;
   VA_31_to_25  =  (virtualAddr >> 25U) & 0x0000007FU ;
   desc_13_to_7 =  ( (TTB_13_to_7 + VA_31_to_25) & 0x0000007FU ) << 7U ;

   addrOfL1Desc =  (TTB & MMU_TTB_MASK) | desc_13_to_7 |  ( (virtualAddr >> 18U) & 0x0000007CU)  ;

   /* Generate the First Level Descriptor for a Super section address */
   if(faultType == MMU_FAULT_DESC1)
   {
             l1DescSSection = ( (physicalAddr & MMU_SSECTION_ADDR_MASK) |
                                  ((UWORD32)endianism << 15U) |
                                  ((UWORD32)elementSizeA << 10U) |
                                  ((UWORD32)mixedSize << 17U)
                                ) | 0x40000U;
   }
   else
   {
             l1DescSSection = ( (physicalAddr & MMU_SSECTION_ADDR_MASK) |
                                  ((UWORD32)endianism << 15U) |
                                  ((UWORD32)elementSizeA << 10U) | 2U |
                                  ((UWORD32)mixedSize << 17U)
                                ) | 0x40000U;
   }

   *(UWORD32*)addrOfL1Desc = l1DescSSection;

   return returnCode;
}

/* ============================================================================*/
/*               MMU_Section                                                   */
/* ============================================================================*/
ReturnCode_t EVE_MMU_Section(
                        const UWORD32      physicalAddr,
                        const UWORD32      virtualAddr,
                        const UWORD32      TTB ,
                        MMU_Endianness_t     endianism,
                        MMU_ElementSize_t   elementSizeB,
                        MMUMixedSize_t     mixedSize,
                        MMUFault_t         faultType
                        )
{
   ReturnCode_t returnCode = RET_OK;
   UWORD32 addrOfL1Desc, l1DescSection, TTB_13_to_7, VA_31_to_25, desc_13_to_7;

   /*Check the input Parameters*/
/*   CHECK_INPUT_RANGE_MIN0(elementSize,MMU_ELEMENTSIZE_MAX,RET_PARAM_OUT_OF_RANGE,RES_MMU_BASE + RES_INVALID_INPUT_PARAM); */

   /* Generate the ADDRESS of First Level Descriptor for a section address */
   TTB_13_to_7  = (TTB >> 7U) & 0x0000007FU ;
   VA_31_to_25  =  (virtualAddr >> 25U) & 0x0000007FU ;
   desc_13_to_7 =  ( (TTB_13_to_7 + VA_31_to_25) & 0x0000007FU ) << 7U;


   addrOfL1Desc =  (TTB & MMU_TTB_MASK) | desc_13_to_7 |  ( (virtualAddr >> 18U) & 0x0000007CU)  ;

   /* Generate the first Level Descriptor for a section address */
   if(faultType == MMU_FAULT_DESC1)
   {
             l1DescSection =  ((physicalAddr & MMU_SECTION_ADDR_MASK) |
                                 ((UWORD32)endianism << 15U) |
                                 ((UWORD32)elementSizeB << 10U) |
                                 ((UWORD32)mixedSize << 17U)
                                ) & 0xFFFBFFFFU
                             ;
   }
   else
   {
             l1DescSection =  ( (physicalAddr & MMU_SECTION_ADDR_MASK) |
                                 ((UWORD32)endianism << 15U) |
                                 ((UWORD32)elementSizeB << 10U) |
                                 ((UWORD32)mixedSize << 17U) |
                                  2U
                               ) & 0xFFFBFFFFU
                             ;
   }

   *(UWORD32*)addrOfL1Desc = l1DescSection;

   return returnCode;
}


/* ============================================================================*/
/*                MMU_CoarseLargePage                                          */
/* ============================================================================*/
ReturnCode_t EVE_MMU_CoarseLargePage(
                                const UWORD32      physicalAddr,
                                const UWORD32      virtualAddr,
                                const UWORD32      TTB,
                                const UWORD32      pageTableBase,
                                MMU_Endianness_t     endianism,
                                MMU_ElementSize_t   elementSize__,
                                MMUMixedSize_t     mixedSize,
                                MMUFault_t         faultType
                                )
{
   ReturnCode_t returnCode = RET_OK;
   UWORD32 addrOfL1Desc, l1DescCoarseLP, addrOfL2Desc, l2DescCoarseLP, i;
   UWORD32 TTB_13_to_7, VA_31_to_25, desc_13_to_7;

   /*Check the input Parameters*/
   CHECK_INPUT_RANGE_MIN0(elementSize__,MMU_ELEMENTSIZE_MAX,RET_PARAM_OUT_OF_RANGE,RES_MMU_BASE + RES_INVALID_INPUT_PARAM);

   /* Generate the ADDRESS of First Level Descriptor for a Coarse Large Page */
   TTB_13_to_7  = (TTB >> 7U) & 0x0000007FU ;
   VA_31_to_25  = (virtualAddr >> 25U) & 0x0000007FU ;
   desc_13_to_7 = ( (TTB_13_to_7 + VA_31_to_25) & 0x0000007FU ) << 7U ;
   addrOfL1Desc = (TTB & MMU_TTB_MASK) | desc_13_to_7 |  ( (virtualAddr >> 18U) & 0x0000007CU) ;

   /* Generate the First Level Descriptor for a Coarse Large Page */
   if(faultType == MMU_FAULT_DESC1)
   {
             l1DescCoarseLP = pageTableBase & MMU_PAGE_TABLE_MASK;

   }
   else
   {
             l1DescCoarseLP = (pageTableBase & MMU_PAGE_TABLE_MASK) | 1U;
   }

   /* Generate the ADDRESS of Second Level Descriptor for a Coarse Large Page */
   addrOfL2Desc   = (pageTableBase & MMU_PAGE_TABLE_MASK) |
                      ( ( (virtualAddr & 0x000FF000U) >> 10U) & 0x000003FCU )
                    ;

   /* Generate the Second Level Descriptor for a Coarse Large Page */
   if(faultType == MMU_FAULT_DESC2)
   {
             l2DescCoarseLP = (physicalAddr & MMU_LARGE_PAGE_MASK) |
                                ((UWORD32)endianism << 9U) |
                                ((UWORD32)elementSize__ << 4U) |
                                ((UWORD32)mixedSize << 11U);
   }
   else
   {
             l2DescCoarseLP = (physicalAddr & MMU_LARGE_PAGE_MASK) |
                                ((UWORD32)endianism << 9U) |
                                ((UWORD32)elementSize__ << 4U) |
                                ((UWORD32)mixedSize << 11U) | 1U;
   }

   *(UWORD32*)addrOfL1Desc = l1DescCoarseLP;

   for (i = 0; i < 16U; i++)
   {
      *(UWORD32*)(addrOfL2Desc + (4U * i) ) = l2DescCoarseLP;
   }

   return returnCode;
}


/* ============================================================================*/
/*                  MMU_CoarseSmallPage                                        */
/* ============================================================================*/
ReturnCode_t EVE_MMU_CoarseSmallPage(
                                const UWORD32      physicalAddr,
                                const UWORD32      virtualAddr,
                                const UWORD32      TTB,
                                const UWORD32      pageTableBase,
                                MMU_Endianness_t     endianism,
                                MMU_ElementSize_t   elementSize_,
                                MMUMixedSize_t     mixedSize,
                                MMUFault_t         faultType
                                )
{
   ReturnCode_t returnCode = RET_OK;
   UWORD32 addrOfL1Desc, l1DescCoarseSP, addrOfL2Desc, l2DescCoarseSP;
   UWORD32 TTB_13_to_7, VA_31_to_25, desc_13_to_7;

   /*Check the input Parameters*/
   CHECK_INPUT_RANGE_MIN0(elementSize_,MMU_ELEMENTSIZE_MAX,RET_PARAM_OUT_OF_RANGE,RES_MMU_BASE + RES_INVALID_INPUT_PARAM);

   /* Generate the ADDRESS of First Level Descriptor for a Coarse Small Page */
   TTB_13_to_7  =  (TTB >> 7U) & 0x0000007FU;
   VA_31_to_25  =  (virtualAddr >> 25U) & 0x0000007FU;
   desc_13_to_7 =  ( (TTB_13_to_7 + VA_31_to_25) & 0x0000007FU ) << 7U ;
   addrOfL1Desc =  (TTB & MMU_TTB_MASK) | desc_13_to_7 |  ( (virtualAddr >> 18U) & 0x0000007CU)  ;

   /* Generate the First Level Descriptor for a Coarse Small Page */
   if(faultType == MMU_FAULT_DESC1)
   {
             l1DescCoarseSP = pageTableBase & MMU_PAGE_TABLE_MASK;
   }
   else
   {
             l1DescCoarseSP = (pageTableBase & MMU_PAGE_TABLE_MASK) | 1U;
   }

   /* Generate the ADDRESS of Second Level Descriptor for a Coarse Small Page */
   addrOfL2Desc =  (pageTableBase & MMU_PAGE_TABLE_MASK) |
                    ( ( (virtualAddr & 0x000FF000U) >> 10U) & 0x000003FCU);

   /* Generate the Second Level Descriptor for a Coarse Small Page */
   if(faultType == MMU_FAULT_DESC2)
   {
             l2DescCoarseSP = (physicalAddr & MMU_SMALL_PAGE_MASK) |
                                ((UWORD32)endianism << 9U) |
                                ((UWORD32)elementSize_ << 4U) |
                                ((UWORD32)mixedSize << 11U);
   }
   else
   {
             l2DescCoarseSP = (physicalAddr & MMU_SMALL_PAGE_MASK) |
                                ((UWORD32)endianism << 9U) |
                                ((UWORD32)elementSize_ << 4U) |
                                ((UWORD32)mixedSize << 11U)  |
                                 2U;
   }

   *(UWORD32*)addrOfL1Desc = l1DescCoarseSP;
   *(UWORD32*)addrOfL2Desc = l2DescCoarseSP;

   return returnCode;
}



/* =============================================================================
 * LOCAL FUNCTIONS
 * =============================================================================
 */


/* EOF */

