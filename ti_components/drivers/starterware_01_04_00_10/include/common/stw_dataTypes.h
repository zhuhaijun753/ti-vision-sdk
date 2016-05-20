/******************************************************************************
 *                                                                            *
 * Copyright (c) 2012 Texas Instruments Incorporated - http://www.ti.com/     *
 *                                                                            *
 * All rights reserved. Property of Texas Instruments Incorporated.           *
 * Restricted rights to use, duplicate or disclose this code are              *
 * granted through contract.                                                  *
 *                                                                            *
 * The program may not be used without the written permission                 *
 * of Texas Instruments Incorporated or against the terms and conditions      *
 * stipulated in the agreement under which this program has been              *
 * supplied.                                                                  *
 *                                                                            *
 *****************************************************************************/

/**
 *  \file stw_dataTypes.h
 *
 *  \brief Starterware header file containing standard data types.
 *
 */

#ifndef STW_DATATYPES_H_
#define STW_DATATYPES_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

typedef uint16_t      Bool; /* In sync with xdc/std.h */
typedef uint32_t      UInt32;
typedef int32_t       Int32;
typedef uint16_t      UInt16;
typedef int16_t       Int16;
typedef uint8_t       UInt8;
typedef int8_t        Int8;
typedef char          Char;
typedef void          Void;
typedef void *        Ptr;
typedef uint32_t      UArg;
typedef double        Double;
typedef uint64_t      UInt64;
typedef unsigned char tBoolean;
typedef float Float32;

/* To fix Misra-C errors */
#ifndef TRUE
#define TRUE  ((Bool) 1)
#endif
#ifndef FALSE
#define FALSE ((Bool) 0)
#endif

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef STW_DATATYPES_H_ */
