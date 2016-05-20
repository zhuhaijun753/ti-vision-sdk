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
*   Component:     Global Types
*
*   Filename:      GlobalTypes.h
*
*   Description:
*
* =============================================================================
*/
/**
*  @file       globaltypes.h
*
*  @brief      Error types and some data types needed by starterware
*
*
*/
#ifndef GLOBALTYPES_H
#define GLOBALTYPES_H

/* ============================================================================
* INCLUDE FILES (only if necessary)
* =============================================================================
*/
#pragma CHECK_MISRA ("none")
#include <stddef.h>
#include <stdint.h>

#ifndef HOST_EMULATION
#include <stdbool.h>
#endif

#include <string.h>
#pragma RESET_MISRA ("required")
#ifdef __cplusplus
extern "C"
{
#endif


/**
*
* @brief        ReturnCode_t, *pReturnCode_t : Return codes to be returned by all library functions
*
*
*/
typedef enum ReturnCode_label {
    RET_OK = 0,                 /**< pass */
    RET_FAIL,                   /**< fail */
    RET_BAD_NULL_PARAM,         /**< bad null parameter */
    RET_PARAM_OUT_OF_RANGE,     /**< parameter is out of range */
    RET_INVALID_ID,             /**< invalid id */
    RET_EMPTY,                  /**< empty */
    RET_FULL,                   /**< full */
    RET_TIMEOUT,                /**< timed out */
    RET_INVALID_OPERATION,      /**< invalid operation */

    /* Beach register tests return codes */
    RET_POR_FAIL,               /* Power on reset fail */
    RET_READ_INTEG_FAIL,        /* Read Integrity fail  */
    RET_READ_ONLY_FAIL,         /* Read only fail */
    RET_WRTIE_ONLY_FAIL,        /* Write only fail */
    RET_RE_UP_FAIL,             /* Read exclusivity Up fail */
    RET_RE_DOWN_FAIL,           /* Read exclusivity Down fail */
    RET_BUSY,

    /* Add new error codes at end of above list */

    RET_NUM_RET_CODES     /* this should ALWAYS be LAST entry */
} ReturnCode_t, *pReturnCode_t;                    /**< ReturnCode_t, *pReturnCode_t */


/* Boolean  Definition */
/**
*
* @brief        Boolean Type True, False
*
*
*/
#ifndef BOOL_FLAG
    #define BOOL_FLAG
#ifndef HOST_EMULATION
    typedef  _Bool BOOL;
#else
    typedef  unsigned char BOOL;
#endif
#endif

/*-------------------------------------------------------------------------*//**
 * @TYPE  UWORD8
 *
 * @BRIEF unsigned byte type
 *//*------------------------------------------------------------------------ */
#ifndef UWORD8_FLAG
  #define UWORD8_FLAG
  typedef     uint8_t   UWORD8;
  #endif

#ifndef WORD8_FLAG
  #define WORD8_FLAG
typedef     int8_t    WORD8;
#endif

#ifndef UWORD16_FLAG
  #define UWORD16_FLAG
typedef    uint16_t  UWORD16 ;
#endif

#ifndef WORD16_FLAG
  #define WORD16_FLAG
typedef    int16_t    WORD16;
#endif

#ifndef UWORD32_FLAG
  #define UWORD32_FLAG
typedef   uint32_t  UWORD32;
#endif

#ifndef WORD32_FLAG
  #define WORD32_FLAG
typedef   int32_t    WORD32;
#endif

#ifndef UCHAR_FLAG
  #define UCHAR_FLAG
typedef   uint8_t    UCHAR;
#endif

/**
  * @brief REG_UWORD8, REG_WORD8
  *
  * @brief       8 bit register types.
  *
  *
  */
#ifndef REG_UWORD8_FLAG
  #define REG_UWORD8_FLAG                             /**< REG_UWORD8 flag */
  typedef volatile uint8_t REG_UWORD8;          /**< REG_UWORD8 */
#endif

  typedef volatile int8_t  REG_WORD8;          /**< REG_WORD8 */

  /**
  * @brief REG_UWORD16, REG_WORD16
  *
  * @brief       16 bit register types.
  *
  *
  */
#ifndef REG_UWORD16_FLAG
  #define REG_UWORD16_FLAG                             /**< REG_UWORD16 flag */
  typedef volatile uint16_t REG_UWORD16;         /**< REG_UWORD16 */
#endif

  typedef volatile    uint16_t REG_WORD16;          /**< REG_WORD16 */

  /**
  * @brief REG_UWORD32, REG_WORD32
  *
  * @brief       32 bit register types.
  *
  *
  */
#ifndef REG_UWORD32_FLAG
  #define REG_UWORD32_FLAG                             /**< REG_UWORD32 flag */
  typedef volatile uint32_t  REG_UWORD32;          /**< REG_UWORD32 */
#endif

#ifndef REG_WORD32_FLAG
  #define REG_WORD32_FLAG                               /**< REG_WORD32 flag*/
  typedef volatile          int32_t  REG_WORD32;            /**< REG_WORD32 */
#endif



#ifdef __cplusplus
}
#endif
#endif  /* GLOBALTYPES_H */
