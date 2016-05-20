/** ===========================================================================
* @file   xdais_types.h
*
* @desc   This header is a suppliment to need of XDAIS. XDAIS needs these
*         data type defention from external module hence this file is created
*         This file should not be used as data types for EVE software modules
* =====================================================================
* Copyright (c) Texas Instruments Inc 2013
*
* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied
* ===========================================================================*/


#ifndef XDAIS_TYPES
#define XDAIS_TYPES

typedef void            Void  ;        
typedef signed char     Int8   ;    /**< Actual size chip dependent. */
typedef unsigned char   Uint8  ;    /**< Actual size chip dependent. */
typedef signed short    Int16  ;    /**< Actual size of type is 16 bits. */
typedef unsigned short  Uint16 ;    /**< Actual size of type is 16 bits. */
typedef signed int      Int32  ;    /**< Actual size of type is 32 bits. */
typedef unsigned int    Uint32 ;    /**< Actual size of type is 32 bits. */

typedef signed int      Int  ;    /**< Actual size of type is 32 bits. */
typedef unsigned int    Uns  ;    /**< Actual size of type is 32 bits. */

typedef signed char *    String   ;    /**< Actual size chip dependent. */

#endif /* XDAIS_TYPES */

