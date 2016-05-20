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
 */
/*
 *  @Component    UTILS : contains utility functions needed  by dsp
 *
 *  @Filename     dsp_utils.h
 *
 *
 *//*======================================================================== */
/**
*  @file       dsp_utils.h
*
*  @brief      Contains Interrupt (IRQ) handler functions allowing
*              the registering of interrupt handlers for specific vectors.
*              This file allso contains primary ARM11 irq handler.
*
*  This header defines all interrupt handler API's and events for the DSP host
*
*/
#ifndef __DSP_UTILS_H
#define __DSP_UTILS_H

/* ============================================================================
* INCLUDE FILES (only if necessary)
* =============================================================================
*/

#ifdef __cplusplus
extern "C"
{
#endif

/*-------------------------------------------------------------------------*//**
 * @DEFINITION WR_MEM_32_VOLATILE
 *
 * @BRIEF      Write memory volatile - 32bit; accessing the memory address
 *             This is ok for ARM cores and C64, not ok for C55
 *//*------------------------------------------------------------------------ */
#ifndef WR_MEM_32_VOLATILE
  #define WR_MEM_32_VOLATILE(addr, data) ( *((REG_UWORD32 *)(addr)) = (UWORD32)(data) )
#endif

/*-------------------------------------------------------------------------*//**
 * @DEFINITION RD_MEM_32_VOLATILE
 *
 * @BRIEF      Read memory volatile - 32bit; accessing the memory address
 *             This is ok for ARM cores and C64, not ok for C55
 *//*------------------------------------------------------------------------ */
#ifndef RD_MEM_32_VOLATILE
  #define RD_MEM_32_VOLATILE(addr)     ( (UWORD32)( *((REG_UWORD32 *)(addr)) ) )
#endif


#ifdef __cplusplus
}
#endif

#endif    /* __DSP_UTILS_H */

/* Nothing past this point */
