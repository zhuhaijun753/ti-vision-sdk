/* ============================================================================
*
*            TEXAS INSTRUMENTS INCORPORATED PROPRIETARY INFORMATION
*
*   Property of Texas Instruments
*   For Unrestricted Internal Use Only
*   Unauthorized reproduction and/or distribution is strictly prohibited.
*   This product is protected under copyright law and trade secret law as an unpublished work.
*   Created 2003, (C) Copyright 2003 Texas Instruments.  All rights reserved.
*
*   Component:     Utill functions
*
*   Filename:      utils.h
*
*   Description: Contains some utility functions needed by starterware
*
* =============================================================================
*/

#ifndef UTILS_H
#define UTILS_H
/**
* @brief   RD_MEM_8, WR_MEM_8
*
* @brief        8 bit memory access macros
*
*
*/
#define RD_MEM_8(addr)	((UWORD8)(*((UWORD8 *)(addr))))                      /**< 8 bit read memory */
#define WR_MEM_8(addr, data)	(*((UWORD8 *)(addr)) = (UWORD8)(data))       /**< 8 bit write memory */

/**
* @brief   RD_MEM_16, WR_MEM_16
*
* @brief        16 bit memory access macros
*
*
*/
#define RD_MEM_16(addr)	((UWORD16)(*((UWORD16 *)(addr))))                        /**< 16 bit read memory */
#define WR_MEM_16(addr, data)	(*((UWORD16 *)(addr)) = (UWORD16)(data))         /**< 16 bit write memory */

/**
* @brief   RD_MEM_32, WR_MEM_32
*
* @brief        32 bit memory access macros
*
*
*/
#define RD_MEM_32(addr)	((UWORD32)(*((UWORD32 *)(addr))))                        /**< 32 bit read memory */
#define WR_MEM_32(addr, data)	(*((UWORD32 *)(addr)) = (UWORD32)(data))         /**< 32 bit write memory */

/**
* @brief   RD_MEM_64, WR_MEM_64
*
* @brief        64 bit memory access macros
*
*
*/
#define RD_MEM_64(addr)	((UWORD64)(*((UWORD64 *)(addr))))                          /**< 64 bit read memory */
#define WR_MEM_64(addr, data)	(*((UWORD64 *)(addr)) = (UWORD64)(data))           /**< 64 bit write memory */

#endif /*UTILS_H*/

