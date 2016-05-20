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

#include "baseaddress.h"
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


} /* EVE_MMU_CurrentVictimSet() */



/* ======================== Function Separator ============================= */
UWORD32 EVE_MMU_CurrentVictimGet ( CRED_index_t component )
{

    UWORD32 rdVal=0;


    return rdVal;

} /* EVE_MMU_CurrentVictimGet() */



/* ======================== Function Separator ============================= */
void EVE_MMU_TlbLockSet ( CRED_index_t component, UWORD32 tlbEntry )
{

 return;
} /* EVE_MMU_TlbLockSet() */



/* ======================== Function Separator ============================= */
UWORD32 EVE_MMU_TlbLockGet ( CRED_index_t component )
{

    UWORD32 rdVal=0;

    return rdVal;

} /* EVE_MMU_TlbLockGet() */



/* ======================== Function Separator ============================= */
void EVE_MMU_GlobalFlush( CRED_index_t component )
{

	return;
} /* EVE_MMU_GlobalFlush() */


/* ======================== Function Separator ============================= */
void EVE_MMU_TlbEntryFlush( CRED_index_t component, UWORD32 virtAddress )
{

	return;
} /* EVE_MMU_GlobalFlush() */



/* ======================== Function Separator ============================= */
void EVE_MMU_SoftReset( CRED_index_t component )
{

	return;
} /* EVE_MMU_SoftReset() */



/* ======================== Function Separator ============================= */
UWORD32 EVE_MMU_IrqGetStatus ( CRED_index_t component )
{

    UWORD32 rdVal=0;

    return rdVal;

} /* EVE_MMU_IrqGetStatus() */


/* ======================== Function Separator ============================= */
void EVE_MMU_IrqClearStatus ( CRED_index_t component, MMU_IntType_t intType  )
{

	return;

} /* EVE_MMU_IrqGetStatus() */



/* ======================== Function Separator ============================= */
void EVE_MMU_IrqEnable ( CRED_index_t component, MMU_IntType_t intType )
{
	return;
} /* EVE_MMU_IrqEnable() */



/* ======================== Function Separator ============================= */
void EVE_MMU_IrqDisable ( CRED_index_t component, MMU_IntType_t intType )
{
	return;
} /* EVE_MMU_IrqDisable() */



/* ======================== Function Separator ============================= */
void EVE_MMU_WtlEnable ( CRED_index_t component )
{
	return;
} /* EVE_MMU_WtlEnable() */



/* ======================== Function Separator ============================= */
void EVE_MMU_WtlDisable ( CRED_index_t component )
{
	return;
} /* EVE_MMU_WtlDisable() */



/* ======================== Function Separator ============================= */
void EVE_MMU_Enable ( CRED_index_t component )
{
	return;
} /* EVE_MMU_Enable() */



/* ======================== Function Separator ============================= */
void EVE_MMU_Disable ( CRED_index_t component )
{
	return;
} /* EVE_MMU_Enable() */


/* ======================== Function Separator ============================= */
#ifdef VAYU_PLATFORM
ReturnCode_t EVE_MMU_TlbEntrySet_Coherency ( CRED_index_t component,
                                         UWORD32      tlbEntry,
                                         const MMU_TlbEntry_t *mmuTlbEntry,
                                         UWORD32 Coherency )

{

    ReturnCode_t returnCode = RET_OK;

    return returnCode;

} /* MMU_WriteTLBEntry() */

#endif



/* ======================== Function Separator ============================= */
ReturnCode_t EVE_MMU_TlbEntrySet ( CRED_index_t component,
                               UWORD32 tlbEntry,
                               const MMU_TlbEntry_t *mmuTlbEntry )

{

    ReturnCode_t returnCode = RET_OK;

    return returnCode;

} /* MMU_WriteTLBEntry() */


/* ======================== Function Separator ============================= */
#ifdef VAYU_PLATFORM
ReturnCode_t EVE_MMU_TlbEntrySet_Extended ( CRED_index_t component,
                                        UWORD32 tlbEntry,
                                        const MMU_TlbEntry_extended_t *mmuTlbEntry_extended )

{

    ReturnCode_t returnCode = RET_OK;


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

   return returnCode;
}



/* =============================================================================
 * LOCAL FUNCTIONS
 * =============================================================================
 */


/* EOF */

