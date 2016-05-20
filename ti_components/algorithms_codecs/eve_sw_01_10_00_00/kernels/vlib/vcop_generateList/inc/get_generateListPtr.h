/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_generateList                                                    */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2013 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#include <stdint.h>

int32_t get_generateListPtr(
        const uint16_t* pblock,
        uint16_t    paramCount,
        uint32_t    pListX,
        uint32_t    pListY,
        uint16_t    *listXoffset,
        uint16_t    *listYoffset
);

int32_t reset_generateListPtr(
        const uint16_t* pblock,
        uint32_t    pListX,
        uint32_t    pListY,
        uint16_t    listXoffset,
        uint16_t    listYoffset
);
