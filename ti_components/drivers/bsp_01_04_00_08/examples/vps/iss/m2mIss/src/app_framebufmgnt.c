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
#include <common/vpscore.h>
#include <app_framebufmgnt.h>

/** \brief Maximum number of buffers to be allocated
 */
#define MAX_NUM_BUFS            (6U)

/** \brief Maximum Buffer Size, Assuming input size is always greater
 */
#define MAX_BUF_SIZE            (1920u * 1080u * 2U)

/* Frame buffers must be aligned */
#pragma DATA_ALIGN(FrameBufArray, 32)
uint8_t         FrameBufArray[MAX_NUM_BUFS][MAX_BUF_SIZE];

typedef struct
{
    uint32_t      inpIdx;
    /* This is a counter which will provide MAX_NUM_BUFS_PER_PORT buffers
     * addresses to VIP in a cyclical manner */

    VpsCore_Frame frm[MAX_NUM_BUFS];
    /* This stores frame addresses in a format understood by VIP driver */
} App_FrameBufObj;

App_FrameBufObj gFrameBufObj;

Void App_FrameBufInit()
{
    uint32_t       i;
    VpsCore_Frame *frm;

    gFrameBufObj.inpIdx = 0;
    for(i = 0; i < MAX_NUM_BUFS; i++)
    {
        frm = &(gFrameBufObj.frm[i]);
        frm->drvData   = NULL;
        frm->streamId  = 0;                        /* Ignore for current
                                                    *use-case */
        frm->chId      = 0;                        /* Ignore for current
                                                    *use-case */
        frm->dropFrm   = 0;                        /* Ignore for current
                                                    *use-case */
        frm->coreStats = 0;                        /* Ignore for current
                                                    * use-case
                                                    * Used to provide error
                                                    * information
                                                    */

        frm->addr[0][0] = &FrameBufArray[i][0];    /*Important. Frame addr */
    }
}

Void App_FrameBufDeInit()
{
    // No book-keeping required since buffers are statically allocated
}

VpsCore_Frame *App_GetFrameBuf()
{
    VpsCore_Frame *frm;

    frm = &(gFrameBufObj.frm[gFrameBufObj.inpIdx]);

    /* This is to keep cycling between buffer allocated for the specified port*/
    gFrameBufObj.inpIdx++;
    if(gFrameBufObj.inpIdx >= MAX_NUM_BUFS)
    {
        gFrameBufObj.inpIdx = 0;
    }

    return frm;
}

Void App_ReleaseFrameBuf(VpsCore_Frame *frm)
{
    // No book-keeping required since buffers are statically allocated
}

