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
){
    uint16_t i;
    const uint32_t *p;
    int32_t status= 0;
    uint16_t listXFound= 0, listYFound= 0;

    p= (const uint32_t*)pblock;
    /* Search for location of waveletPtr1 */
    for (i=0;i<paramCount/2;i++) {
        if (p[i]== pListX && (!listXFound)) {
            *listXoffset= i;
            listXFound=1;
        }
        if (p[i]== pListY && (!listYFound)) {
            *listYoffset= i;
            listYFound=1;
        }
    }

    if ((!listXFound) || (!listYFound)) {
        status= -1;
    }

    return status;
}

int32_t reset_generateListPtr(
        uint16_t* const pblock,
        uint32_t    pListX,
        uint32_t    pListY,
        uint16_t    listXoffset,
        uint16_t    listYoffset
){
    int32_t status= 0;
    uint32_t *p;

    p= (uint32_t*)pblock;
    p[listXoffset]= pListX;
    p[listYoffset]= pListY;

    return status;
}
