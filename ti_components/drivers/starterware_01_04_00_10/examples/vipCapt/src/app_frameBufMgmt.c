/* ======================================================================
 *   Copyright (C) 2013 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */
#include <stdint.h>
#include <stddef.h>
#include <common/stw_dataTypes.h>
#include <common/stw_types.h>

#include <app_frameBufMgmt.h>
#include <common/bsp_utils.h>

/* Frame buffers must be aligned */
#ifdef __cplusplus
#pragma DATA_ALIGN(32)
#else
#pragma DATA_ALIGN(FrameBufArray, 32)
#endif  /* #ifdef __cplusplus */
UInt8 FrameBufArray[MAX_NUM_PORTS][MAX_NUM_BUFS_PER_PORT][MAX_BUF_SIZE];

typedef struct
{
    UInt32        inpIdx[MAX_NUM_PORTS];
    /* This is a counter which will provide MAX_NUM_BUFS_PER_PORT buffers
     * addresses to VIP in a cyclical manner */

    VpsCore_Frame frm[MAX_NUM_PORTS][MAX_NUM_BUFS_PER_PORT];
    /* This stores frame addresses in a format understood by VIP driver */
} App_FrameBufObj;

App_FrameBufObj gFrameBufObj;

Void App_FrameBufInit()
{
    /* This function initilizes a pool of
     * VpsCore_Frame[MAX_NUM_PORTS][MAX_NUM_BUFS_PER_PORT]
     * with static addresses from
     * FrameBufArray[MAX_NUM_PORTS][MAX_NUM_BUFS_PER_PORT][MAX_BUF_SIZE]
     */
    UInt32         i, j;
    VpsCore_Frame *frm;

    for (i = 0; i < MAX_NUM_PORTS; i++)
    {
        gFrameBufObj.inpIdx[i] = 0;
        for (j = 0; j < MAX_NUM_BUFS_PER_PORT; j++)
        {
            frm            = &(gFrameBufObj.frm[i][j]);
            frm->drvData   = NULL;
            frm->streamId  = 0;    /* Ignore for current use-case */
            frm->chId      = 0;    /* Ignore for current use-case */
            frm->dropFrm   = 0;    /* Ignore for current use-case */
            frm->coreStats = 0;
            frm->rtParams  = NULL; /* No Runtime params for this use-case */
            /* Ignore for current use-case Used to provide error information */
            frm->addr[0][0] = &FrameBufArray[i][j][0];
            /* Important. Frame addr */
        }
    }
}

Void App_FrameBufDeInit()
{
    // No book-keeping required since buffers are statically allocated
}

VpsCore_Frame *App_GetFrameBuf(UInt32 portId)
{
    VpsCore_Frame *frm;

    frm = &(gFrameBufObj.frm[portId]
            [gFrameBufObj.inpIdx[portId]]
            );

    /* This is to keep cycling between buffer allocated for the specified port*/
    gFrameBufObj.inpIdx[portId]++;
    if (gFrameBufObj.inpIdx[portId] >= MAX_NUM_BUFS_PER_PORT)
    {
        gFrameBufObj.inpIdx[portId] = 0;
    }

    return frm;
}

Void App_ReleaseFrameBuf(VpsCore_Frame *frm)
{
    // No book-keeping required since buffers are statically allocated
}

