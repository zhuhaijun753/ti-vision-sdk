/*****************************************************\
 *  Copyright 2004, Texas Instruments Incorporated.  *
 *  All rights reserved.                             *
 *  Restricted rights to use, duplicate or disclose  *
 *  this   code   are  granted   through  contract.  *
 *                                                   *
 * "@(#) PSP/CSL  3.0.0.0  (2003-09-30)              *
\*****************************************************/

/** @mainpage Vayu Starterware
*
* @section Introduction
*
* @subsection xxx Purpose and Scope
* The purpose of this document is to detail the APIs for the
* EDMA, Mailbox, MMU, EMIF, Program Cache & Interrupt Controller
* Modules.
*
* @subsection aaa Terms and Abbreviations
*   -# CSL:  Chip Support Library
*   -# API:  Application Programmer Interface
*   -# EDMA: Enhanced Direct Memory Access
*   -# MMU:  Memory Management Unit
*   -# MBOX: Mailbox
*   -# EMIF: External Memory Interface
*   -# PCACHE: Program Cache
*
* @subsection References
*    -# CSL 3.x Technical Requirements Specifications Version 0.5, dated
*       May 14th, 2003
*    -# EDMA Channel Controller Specification (Revision 0.25)
*    -# EDMA Transfer Controller Specification (Revision 0.14)
*    -# EVE Programmer's Guide, SPRUHC1A - April 2012
*
* @subsection Assumptions
*     The starterware API's include host side API's as well, for example
*     DSP host.
*
*/

/** @file csl_edma.h
 *
 *    @brief    Header file for functional layer CSL of EDMA
 *
 *  Description
 *    - The different enumerations, structure definitions
 *      and function declarations
 *  Last Modified : 29th June 2004
 */

#ifndef _CSL_EDMA_H_
#define _CSL_EDMA_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "cslr_edmacc.h"
#include "tistdtypes.h"
#include "edma_baseaddr.h"




#define CSL_EDMA_LINK_NULL                 0xFFFF
/**< Link to a Null Param entry */
#define CSL_EDMA_LINK_DEFAULT              0xFFFF
/**< Link to a Null Param entry */
#define CSL_EDMA_SYNC_A                    0
/**< A sycnhronized transfer  */
#define CSL_EDMA_SYNC_AB                   1
/**< AB sycnhronized transfer */
#define CSL_EDMA_SYNC_ARRAY                CSL_EDMA_SYNC_A
/**< Array/A sycnhronized transfer */
#define CSL_EDMA_SYNC_FRAME                CSL_EDMA_SYNC_AB
/**< Frame/AB sycnhronized transfer */
#define	CSL_EDMA_TCC_NORMAL  		           0
/**< Normal Completion */
#define	CSL_EDMA_TCC_EARLY                     1
/**< Early  Completion */
#define	CSL_EDMA_FIFOWIDTH_NONE                0
/**< Only for ease  */
#define	CSL_EDMA_FIFOWIDTH_8BIT                0
/**< 8 bit FIFO Width */
#define	CSL_EDMA_FIFOWIDTH_16BIT               1
/**< 16 bit FIFO Width */
#define	CSL_EDMA_FIFOWIDTH_32BIT               2
/**< 32 bit FIFO Width */
#define	CSL_EDMA_FIFOWIDTH_64BIT               3
/**< 64 bit FIFO Width */
#define	CSL_EDMA_FIFOWIDTH_128BIT              4
/**< 128 bit FIFO Width */
#define	CSL_EDMA_FIFOWIDTH_256BIT              5
/**< 256 bit FIFO Width */
#define	CSL_EDMA_ADDRMODE_INCR                 0
/**< Address Mode is incremental */
#define	CSL_EDMA_ADDRMODE_FIFO                 1
/**< Address Mode is such it wraps around after reaching FIFO width */


/* Bitwise OR of the below symbols are used for setting the Memory attributes
   These are defined only if the Memory Protection feature exists */
#if CSL_EDMA_MEMPROTECT

#define CSL_EDMA_MEMACCESS_UX              0x0001
/**< User Execute permission */
#define CSL_EDMA_MEMACCESS_UW              0x0002
/**< User Write permission */
#define CSL_EDMA_MEMACCESS_UR              0x0004
/**< User Read permission */
#define CSL_EDMA_MEMACCESS_SX              0x0008
/**< Supervisor Execute permission */
#define CSL_EDMA_MEMACCESS_SW              0x0010
/**< Supervisor Write permission */
#define CSL_EDMA_MEMACCESS_SR              0x0020
/**< Supervisor Read permission */
#define CSL_EDMA_MEMACCESS_EMU             0x0040
/**< Emulation security permission */
#define CSL_EDMA_MEMACCESS_NS              0x0080
/**< Non secure Access permission */
#define CSL_EDMA_MEMACCESS_EXT             0x0200

/**< External Allowed ID. VBus requests with PrivID >= '6' are permitted if access type is allowed*/

#define CSL_EDMA_MEMACCESS_AID0		   0x0400
/**< Allowed ID '0' */
#define CSL_EDMA_MEMACCESS_AID1		   0x0800
/**< Allowed ID '1' */
#define CSL_EDMA_MEMACCESS_AID2		   0x1000
/**< Allowed ID '2' */
#define CSL_EDMA_MEMACCESS_AID3		   0x2000
/**< Allowed ID '3' */
#define CSL_EDMA_MEMACCESS_AID4		   0x4000
/**< Allowed ID '4' */
#define CSL_EDMA_MEMACCESS_AID5		   0x8000
/**< Allowed ID '5' */

#endif
#define CSL_EDMA_TRIGWORD_NONE         7
/**< No trigger word. Useful while doing setup for EDMA channels */
#define CSL_EDMA_TRIGWORD_DEFAULT      7
/**< Last trigger word in a QDMA parameter entry */


/** Used for creating the options entry in the parameter ram */
#define CSL_EDMA_OPT_MAKE(itccEn,tccEn,itcintEn,tcintEn,tcc,tccMode,fwid,stat,syncDim,dam,sam) \
(uint32_t)(\
     CSL_FMKR(23U,23U,itccEn) \
    |CSL_FMKR(22U,22U,tccEn) \
    |CSL_FMKR(21U,21U,itcintEn) \
    |CSL_FMKR(20U,20U,tcintEn) \
    |CSL_FMKR(17U,12U,tcc) \
    |CSL_FMKR(11U,11U,tccMode) \
    |CSL_FMKR(10U,8U,fwid) \
    |CSL_FMKR(3U,3U,stat) \
    |CSL_FMKR(2U,2U,syncDim) \
    |CSL_FMKR(1U,1U,dam) \
    |CSL_FMKR(0U,0U,sam))

/** Used for creating the A,B Count entry in the parameter ram */
#define CSL_EDMA_CNT_MAKE(aCnt,bCnt) \
(uint32_t)(\
     CSL_FMK(EDMACC_A_B_CNT_ACNT,aCnt) \
    |CSL_FMK(EDMACC_A_B_CNT_BCNT,bCnt)\
    )

/** Used for creating the link and B count reload entry in the parameter ram */
#define CSL_EDMA_LINKBCNTRLD_MAKE(link,bCntRld) \
(uint32_t)(\
     CSL_FMK(EDMACC_LINK_BCNTRLD_LINK,link) \
    |CSL_FMK(EDMACC_LINK_BCNTRLD_BCNTRLD,bCntRld)\
    )

/** Used for creating the B index entry in the parameter ram */
#define CSL_EDMA_BIDX_MAKE(src,dst) \
(uint32_t)(\
     CSL_FMK(EDMACC_SRC_DST_BIDX_DSTBIDX,dst) \
    |CSL_FMK(EDMACC_SRC_DST_BIDX_SRCBIDX,src)\
    )

/** Used for creating the C index entry in the parameter ram */
#define CSL_EDMA_CIDX_MAKE(src,dst) \
(uint32_t)(\
     CSL_FMK(EDMACC_SRC_DST_CIDX_DSTCIDX,dst) \
    |CSL_FMK(EDMACC_SRC_DST_CIDX_SRCCIDX,src)\
    )

#ifdef __cplusplus
    }
#endif

#endif
