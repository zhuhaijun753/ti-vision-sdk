/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_prune_big_list_cn.h                                     */
/*                                                                          */
/*     @brief : This file contains declarations for the C reference         */
/*         function for pruning an input list based on sorted index array.  */
/*                                                                          */
/*     vcop_prune_big_list_cn                                               */
/*         This is the C-reference for the vcop_prune_big_list kernel.      */
/*         This routine accepts an input list and a sorted array of         */
/*         indices. The outputs is a pruned list of 'bestN' elements from   */
/*         input based on the ordering in the index list provided.          */
/*                                                                          */
/*     USAGE:                                                               */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_prune_big_list_cn                                          */
/*     (                                                                    */
/*         uint32_t *inList,                                                */
/*         uint16_t *inSortedIndexList,                                     */
/*         uint32_t *outList,                                               */
/*         uint16_t  bestN                                                  */
/*     )                                                                    */
/*                                                                          */
/*     inList            : Input list to be pruned                          */
/*     inSortedIndexList : List of sorted indexes. The index list is        */
/*                         expected to be a of 32-bit with the lower 16-bit */
/*                         representing the index.                          */
/*     outList           : Pruned and packed output list                    */
/*     bestN             : Number of elements expected to be available in   */
/*                         the output list.                                 */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     @version 1.0 (Nov 2013) : Base version.                              */
/*                                                                          */
/*==========================================================================*/

#ifndef _VCOP_PRUNE_BIG_LIST_CN
#define _VCOP_PRUNE_BIG_LIST_CN

void vcop_prune_big_list_cn
(
    uint32_t *inList,
    uint16_t *inSortedIndexList,
    uint32_t *inSortedIndexList32,
    uint32_t *outList,
    uint32_t *nonBestNSize,
    uint16_t  threshold,
    uint16_t  bestN
);

#endif /* _VCOP_PRUNE_BIG_LIST_CN */
