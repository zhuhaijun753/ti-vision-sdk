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
 * \file bsp_utilsQue.c
 *
 * \brief Utils layer - Array based queue
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <xdc/std.h>
#include <common/bsp_types.h>
#include <common/trace.h>
#include <common/bsp_config.h>
#include <common/bsp_utils.h>
#include <osal/bsp_osal.h>
#include <common/bsp_utilsQue.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* See bsp_utilsQue.h for function documentation  */
Int32 BspUtils_queCreate(BspUtils_QueHandle *handle,
                         UInt32              maxElements,
                         Ptr                 queueMem,
                         UInt32              flags)
{
    /* init handle to 0's */
    BspUtils_memset(handle, 0, sizeof (*handle));

    /*
     * init handle with user parameters
     */
    handle->maxElements = maxElements;
    handle->flags       = flags;

    /*
     * queue data element memory cannot be NULL
     */
    GT_assert(BspUtilsTrace, (queueMem != NULL));

    handle->queue = (Ptr *) queueMem;
    if (handle->flags & BSPUTILS_QUE_FLAG_BLOCK_QUE_GET)
    {
        /*
         * user requested block on que get
         * create semaphore for it
         */
        handle->semRd = BspOsal_semCreate(0, FALSE);
        GT_assert(BspUtilsTrace, (handle->semRd != NULL));
    }

    if (handle->flags & BSPUTILS_QUE_FLAG_BLOCK_QUE_PUT)
    {
        /*
         * user requested block on que put
         * create semaphore for it
         */
        handle->semWr = BspOsal_semCreate(0, FALSE);
        GT_assert(BspUtilsTrace, (handle->semWr != NULL));
    }

    return (BSP_SOK);
}

Int32 BspUtils_queDelete(BspUtils_QueHandle *handle)
{
    if (handle->flags & BSPUTILS_QUE_FLAG_BLOCK_QUE_GET)
    {
        /*
         * user requested block on que get
         * delete associated semaphore
         */
        BspOsal_semDelete(&handle->semRd);
    }
    if (handle->flags & BSPUTILS_QUE_FLAG_BLOCK_QUE_PUT)
    {
        /*
         * user requested block on que put
         * delete associated semaphore
         */
        BspOsal_semDelete(&handle->semWr);
    }

    return (BSP_SOK);
}

Int32 BspUtils_quePut(BspUtils_QueHandle *handle, Ptr data, UInt32 timeout)
{
    Int32  status = BSP_EFAIL;               /* init status to error */
    UInt32 cookie;
    UInt32 loopBreak = FALSE;

    do
    {
        /* disable interrupts */
        cookie = BspOsal_disableInterrupt();
        if (handle->count < handle->maxElements)
        {
            /*
             * free space available in que
             */

            /* insert element */
            handle->queue[handle->curWr] = data;

            /* increment put pointer */
            handle->curWr = (handle->curWr + 1) % handle->maxElements;

            /* increment count of number element in que */
            handle->count++;

            /* restore interrupts */
            BspOsal_restoreInterrupt(cookie);

            /* mark status as success */
            status = BSP_SOK;
            if (handle->flags & BSPUTILS_QUE_FLAG_BLOCK_QUE_GET)
            {
                /*
                 * blocking on que get enabled
                 */

                /* post semaphore to unblock, blocked tasks */
                BspOsal_semPost(handle->semRd);
            }

            /* exit, with success */
            loopBreak = (UInt32) TRUE;
        }
        else
        {
            /*
             * que is full
             */

            /* restore interrupts */
            BspOsal_restoreInterrupt(cookie);

            if (BSP_OSAL_NO_WAIT == timeout)
            {
                loopBreak = (UInt32) TRUE;  /* non-blocking function call, exit
                                             * with error */
            }
            else
            {
                if (handle->flags & BSPUTILS_QUE_FLAG_BLOCK_QUE_PUT)
                {
                    /*
                     * blocking on que put enabled
                     */

                    /* take semaphore and block until timeout occurs or
                     * semaphore is posted */
                    if (!BspOsal_semWait(handle->semWr, timeout))
                    {
                        loopBreak = (UInt32) TRUE;  /* timeout happend, exit
                                                     * with error  */
                    }

                    /*
                     * received semaphore, recheck for available space in the
                     * que
                     */
                }
                else
                {
                    /*
                     * blocking on que put disabled
                     */

                    /* exit with error */
                    loopBreak = (UInt32) TRUE;
                }
            }
        }
    }
    while ((UInt32) FALSE == loopBreak);

    return (status);
}

Int32 BspUtils_queGet(BspUtils_QueHandle *handle,
                      Ptr                *data,
                      UInt32              minCount,
                      UInt32              timeout)
{
    Int32  status = BSP_EFAIL;               /* init status to error */
    UInt32 cookie;
    UInt32 loopBreak = FALSE;

    /*
     * adjust minCount between 1 and handle->maxElements
     */
    if (0U == minCount)
    {
        minCount = 1U;
    }
    if (minCount > handle->maxElements)
    {
        minCount = handle->maxElements;
    }

    do
    {
        /* disable interrupts */
        cookie = BspOsal_disableInterrupt();

        if (handle->count >= minCount)
        {
            /*
             * data elements available in que is >=
             * minimum data elements requested by user
             */

            /* extract the element */
            *data = handle->queue[handle->curRd];

            /* increment get pointer */
            handle->curRd = (handle->curRd + 1) % handle->maxElements;

            /* decrmeent number of elements in que */
            handle->count--;

            /* restore interrupts */
            BspOsal_restoreInterrupt(cookie);

            /* set status as success */
            status = BSP_SOK;

            if (handle->flags & BSPUTILS_QUE_FLAG_BLOCK_QUE_PUT)
            {
                /*
                 * blocking on que put enabled
                 */

                /* post semaphore to unblock, blocked tasks */
                BspOsal_semPost(handle->semWr);
            }

            /* exit with success */
            loopBreak = (UInt32) TRUE;
        }
        else
        {
            /*
             * no elements or not enough element (minCount) in que to extract
             */

            /* restore interrupts */
            BspOsal_restoreInterrupt(cookie);

            if (BSP_OSAL_NO_WAIT == timeout)
            {
                loopBreak = (UInt32) TRUE;  /* non-blocking function call, exit
                                             * with error  */
            }
            else
            {
                if (handle->flags & BSPUTILS_QUE_FLAG_BLOCK_QUE_GET)
                {
                    /*
                     * blocking on que get enabled
                     */

                    /* take semaphore and block until timeout occurs or
                     * semaphore is posted */
                    if (!BspOsal_semWait(handle->semRd, timeout))
                    {
                        loopBreak = (UInt32) TRUE;  /* timeout happened,
                                                     * exit with error */
                    }

                    /*
                     * received semaphore, check que again
                     */
                }
                else
                {
                    /*
                     * blocking on que get disabled
                     */

                    /* exit with error */
                    loopBreak = (UInt32) TRUE;
                }
            }
        }
    }
    while ((UInt32) FALSE == loopBreak);

    return (status);
}

UInt32 BspUtils_queIsEmpty(const BspUtils_QueHandle *handle)
{
    UInt32 isEmpty;
    UInt32 cookie;

    /* disable interrupts */
    cookie = BspOsal_disableInterrupt();

    /* check if que is empty */
    if (handle->count)
    {
        isEmpty = FALSE;    /* not empty  */
    }
    else
    {
        isEmpty = (UInt32) TRUE;     /* empty  */
    }

    /* restore interrupts */
    BspOsal_restoreInterrupt(cookie);

    return (isEmpty);
}

Int32 BspUtils_quePeek(const BspUtils_QueHandle *handle, Ptr *data)
{
    Int32  status = BSP_EFAIL;               /* init status as error  */
    UInt32 cookie;

    *data = NULL;

    /* disable interrupts */
    cookie = BspOsal_disableInterrupt();

    if (handle->count)
    {
        /*
         * que is not empty
         */

        /* get value of top element, but do not extract it from que */
        *data = handle->queue[handle->curRd];

        /* set status as success */
        status = BSP_SOK;
    }

    /* restore interrupts */
    BspOsal_restoreInterrupt(cookie);

    return (status);
}

