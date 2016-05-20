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
 *  \file bsp_utilsQue.h
 *
 *  \brief Utils layer - Array based queue.
 *
 */

#ifndef BSPUTILS_QUE_H_
#define BSPUTILS_QUE_H_

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

/**
 *  \ingroup BSP_DRV_UTIL_API
 *  \defgroup BSP_DRV_UTIL_AQUE_API Utils layer - Array based queue
 *
 *  Implementation of a array based queue with support for optional
 *  blocking on queue empty or queue full.
 *  Interally takes care of critical section locking so that it can be
 *  used from task, ISR context without any additional mutex logic.
 *
 *  @{
 */

/** Do not block on que get and que put,
 * returns error if que is empty or full respectively
 */
#define BSPUTILS_QUE_FLAG_NO_BLOCK_QUE    ((UInt32) 0x00000000U)

/** Block on que put if que is full */
#define BSPUTILS_QUE_FLAG_BLOCK_QUE_PUT   ((UInt32) 0x00000001U)

/** Block on que get if que is empty */
#define BSPUTILS_QUE_FLAG_BLOCK_QUE_GET   ((UInt32) 0x00000002U)

/** Block on que put if que is full, Block on que get if que is empty  */
#define BSPUTILS_QUE_FLAG_BLOCK_QUE       ((UInt32) 0x00000003U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 * \brief Queue Handle
 *
 * Typically user does not need to know internals of queue handle
 * data structure
 */
typedef struct
{
    UInt32            curRd;
    /**< Current read index */

    UInt32            curWr;
    /**< Current write index  */

    UInt32            count;
    /**< Count of element in queue  */

    UInt32            maxElements;
    /**< Max elements that be present in the queue  */

    Ptr              *queue;
    /**< Address of data area of the queue elements */

    BspOsal_SemHandle semRd;
    /**< Read semaphore */

    BspOsal_SemHandle semWr;
    /**< Write semaphore  */

    UInt32            flags;
    /**< Controls how APIs behave internally,
     * i.e blocking wait or non-blocking */
} BspUtils_QueHandle;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief Create a queue handle
 *
 * The size of queueMem llocate by the user should be maxElements*sizeof(Ptr)
 *
 * \param  handle        [ O] Initialized queue handle
 * \param  maxElements   [I ] Maximum elements that can reside in the queue
 *                        at any given point of time
 * \param  queueMem      [I ] Address of queue element data area
 * \param  flags         [I ] BSPUTILS_QUE_FLAG_xxxx
 *
 * \return 0 on success, else failure
 */
Int32 BspUtils_queCreate(BspUtils_QueHandle *handle,
                         UInt32 maxElements, Ptr queueMem, UInt32 flags);

/**
 * \brief Delete queue handle
 *
 * Releases all resources allocated during queue create
 *
 * \param  handle        [I ] Queue handle
 *
 * \return 0 on success, else failure
 */
Int32 BspUtils_queDelete(BspUtils_QueHandle *handle);

/**
 * \brief Add a element into the queue
 *
 * \param handle   [I ] Queue Handle
 * \param data     [I ] data element to insert
 * \param timeout  [I ] BIOS_NO_WAIT: non-blocking,
 *                      if queue is full error is returned \n
 *                     BIOS_WAIT_FOREVER: Blocking,
 *                      if queue is full function blocks until
 *                      atleast one element in the queue is free
 *                      for inserting new element
 *
 * \return 0 on success, else failure
 */
Int32 BspUtils_quePut(BspUtils_QueHandle *handle, Ptr data, UInt32 timeout);

/**
 * \brief Get a element from the queue
 *
 * \param handle   [I ] Queue Handle
 * \param data     [ O] extracted data element from the queue
 * \param minCount [I ] Data will be extracted only if
 *                      atleast 'minCount' elements are present in the queue
 * \param timeout  [I ] BIOS_NO_WAIT: non-blocking,
 *                     if queue is empty error is returned \n
 *                     BIOS_WAIT_FOREVER: Blocking, if queue is
 *                     empty function blocks until
 *                     atleast 'minCount' elemetns in the queue are available
 *
 * \return 0 on success, else failure
 */
Int32 BspUtils_queGet(BspUtils_QueHandle *handle,
                      Ptr *data, UInt32 minCount, UInt32 timeout);

/**
 * \brief Peek at the first element from the queue, but do not extract it
 *
 * \param handle   [I ] Queue Handle
 * \param data     [ O] "peeked" data element from the queue
 *
 * \return 0 on success, else failure
 */
Int32 BspUtils_quePeek(const BspUtils_QueHandle *handle, Ptr *data);

/**
 * \brief Returns TRUE is queue is empty else retunrs false
 *
 * \param handle   [I ] Queue Handle
 *
 * \return Returns TRUE is queue is empty else retunrs FALSE
 */
UInt32 BspUtils_queIsEmpty(const BspUtils_QueHandle *handle);

#ifdef __cplusplus
}
#endif

#endif  /* End of #ifndef BSPUTILS_QUE_H_ */

/* @} */
