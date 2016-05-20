/*   ======================================================================
 *   Copyright (c) Texas Instruments Inc , 2012
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied
 *   provided
 *   ==========================================================================
*/
#ifndef EDMA_BASEADDR_H_
#define EDMA_BASEADDR_H_

#include "cslr_edmacc.h"

/*****************************************************************************/
 /** \FILENAME edma_baseaddr.h
 *
 * \BRIEF This file contains the base address from EDMA channel controller
 *
 *****************************************************************************/


/*****************************************************************************\
* Include files for all the modules in the device
\*****************************************************************************/

/*****************************************************************************\
* Peripheral Overlay Structures
\*****************************************************************************/

typedef volatile CSL_EdmaccRegs          *CSL_EdmaccRegsOvly;
typedef volatile CSL_EdmaccShadowRegs    *CSL_EdmaccShadowRegsOvly;

#ifndef _TMS320C6X
#define CGEM_MEM_OFFSET  (0x00000000)



/*****************************************************************************\
* Peripheral Base Address
\*****************************************************************************/


#define CSL_EDMACC_0_REGS                ((CSL_EdmaccRegsOvly) 0x400A0000)
#define CSL_EDMA3_TC0_BASE_ADDR                         ((void *)(0x40086000))
#define CSL_EDMA3_TC1_BASE_ADDR                         ((void *)(0x40087000))


#else
/* DSP PLATFORM */
#define CGEM_MEM_OFFSET  (0x00000000)



/*****************************************************************************\
* Peripheral Base Address
\*****************************************************************************/


#define CSL_EDMACC_0_REGS                ((CSL_EdmaccRegsOvly) 0x01D10000)
#define CSL_EDMA3_TC0_BASE_ADDR                    ((void *)(0x01D05000))
#define CSL_EDMA3_TC1_BASE_ADDR                    ((void *)(0x01D06000))


#endif

#endif /* EDMA_BASEADDR_H_ */


