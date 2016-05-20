/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_extract_bit_field_u32_cn.h                              */
/*                                                                          */
/*     @brief : This file contains declarations for the C reference         */
/*         function for extracting a bit-field from a given integer array.  */
/*                                                                          */
/*     vcop_extract_bit_field_u32_cn                                        */
/*         This is the C-reference for the vcop_extract_bit_field_u32       */
/*         kernel. This routine accepts an array of 32-bit values. The      */
/*         outputs is a list of extracted 8-bit bit-fields.                 */
/*                                                                          */
/*     USAGE:                                                               */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_extract_bit_field_u32_cn                                   */
/*     (                                                                    */
/*         uint32_t *inArray,                                               */
/*         uint16_t  length,                                                */
/*         uint32_t  bit_mask,                                              */
/*         uint8_t   shift,                                                 */
/*         uint8_t  *outList                                                */
/*     )                                                                    */
/*                                                                          */
/*     inArray      : Input list to be pruned                               */
/*     length       : Length of the input array                             */
/*     bit_mask     : Bit mask indicating the bits to be selected.          */
/*     shift        : Shift required to align LSB                           */
/*     outList      : List of extracted bit-fields                          */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     @version 1.0 (Dec 2013) : Base version.                              */
/*                                                                          */
/*==========================================================================*/

#ifndef _VCOP_EXTRACT_BIT_FIELD_U32_CN
#define _VCOP_EXTRACT_BIT_FIELD_U32_CN

void vcop_extract_bit_field_u32_cn
(
    uint32_t *inArray,
    uint16_t  length,
    uint32_t  bit_mask,
    uint8_t   shift,
    uint8_t  *outList
);

#endif /* _VCOP_EXTRACT_BIT_FIELD_U32_CN */
