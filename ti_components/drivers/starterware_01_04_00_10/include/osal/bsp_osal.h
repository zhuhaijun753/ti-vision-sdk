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
 *  \file bsp_osal.h
 *
 *  \brief BSP OS abstraction layer header file.
 *
 */

#ifndef BSP_OSAL_H_
#define BSP_OSAL_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define BSP_OSAL_WAIT_FOREVER           (0xFFFFFFFFU)
#define BSP_OSAL_NO_WAIT                (0x00000000U)

/* Lists of bitmask cache types */
/** \brief Cache Type is L1I (or L1P) */
#define BSP_OSAL_CT_L1P                 (0x1U)
/** \brief Cache Type is L1D */
#define BSP_OSAL_CT_L1D                 (0x2U)
/** \brief Cache Type is L1 */
#define BSP_OSAL_CT_L1                  (BSP_OSAL_CT_L1P | BSP_OSAL_CT_L1D)
/** \brief Cache Type is L2I (or L2P) */
#define BSP_OSAL_CT_L2P                 (0x4U)
/** \brief Cache Type is L2D */
#define BSP_OSAL_CT_L2D                 (0x8U)
/** \brief Cache Type is L2 */
#define BSP_OSAL_CT_L2                  (BSP_OSAL_CT_L2P | BSP_OSAL_CT_L2D)
/** \brief Cache Type is ALLI (or ALLP) */
#define BSP_OSAL_CT_ALLP                (BSP_OSAL_CT_L1P | BSP_OSAL_CT_L2P)
/** \brief Cache Type is ALLD */
#define BSP_OSAL_CT_ALLD                (BSP_OSAL_CT_L1D | BSP_OSAL_CT_L2D)
/** \brief Cache Type is ALL */
#define BSP_OSAL_CT_ALL                 (0x7FFFU)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef void *BspOsal_SemHandle;
typedef void *BspOsal_TaskHandle;
typedef void *BspOsal_ClockHandle;
typedef void *BspOsal_IntrHandle;

typedef void (*BspOsal_TaskFuncPtr)(UInt32 arg0, UInt32 arg1);
typedef void (*BspOsal_ClockFuncPtr)(UInt32 arg0);
typedef void (*BspOsal_IntrFuncPtr)(UInt32 arg0);

typedef struct
{
    UInt32 peakSemObjs;
    UInt32 numMaxSemObjs;
    UInt32 numFreeSemObjs;

    UInt32 peakTaskObjs;
    UInt32 numMaxTaskObjs;
    UInt32 numFreeTaskObjs;

    UInt32 peakClockObjs;
    UInt32 numMaxClockObjs;
    UInt32 numFreeClockObjs;

    UInt32 peakHwiObjs;
    UInt32 numMaxHwiObjs;
    UInt32 numFreeHwiObjs;
} BspOsal_StaticMemStatus;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static inline void Empty_printf(void *buff);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

extern Int32 BspOsal_printf(const Char *format, ...);
extern Int32 BspOsal_scanf(const Char *format, ...);

extern BspOsal_TaskHandle BspOsal_taskCreate(
    BspOsal_TaskFuncPtr fxn,
    Int32               priority,
    void               *stack,
    UInt32              stackSize,
    const void         *arg0);
extern void BspOsal_taskDelete(BspOsal_TaskHandle *pTskHandle);
/**
 *  \brief Returns the stack used in bytes by the task represented by the
 *  handle passed. If the handle is NULL, it uses the current task context
 *  from which this function is called.
 *
 *  Note: This can't be called from HWI/SWI context.
 */
extern UInt32 BspOsal_getTaskStackUsage(BspOsal_TaskHandle tskHandle);
/**
 *  \brief Returns the system stack used in bytes by interrupts.
 *
 *  Note: This can't be called from HWI/SWI context.
 */
extern UInt32 BspOsal_getSystemStackUsage(void);

extern BspOsal_SemHandle BspOsal_semCreate(Int32 initValue, Bool isBinary);
extern void BspOsal_semDelete(BspOsal_SemHandle *pSemHandle);
extern Bool BspOsal_semWait(BspOsal_SemHandle semHandle, UInt32 timeOut);
extern void BspOsal_semPost(BspOsal_SemHandle semHandle);

extern BspOsal_ClockHandle BspOsal_clockCreate(
    BspOsal_ClockFuncPtr fxn,
    UInt32               period,
    Bool                 startFlag,
    const void          *arg0);
extern void BspOsal_clockDelete(BspOsal_ClockHandle *pClkHandle);
extern void BspOsal_clockStart(BspOsal_ClockHandle clkHandle);
extern void BspOsal_clockStop(BspOsal_ClockHandle clkHandle);
extern UInt32 BspOsal_getClockTicks(void);

extern BspOsal_IntrHandle BspOsal_registerIntr(
    UInt32              intNum,
    BspOsal_IntrFuncPtr fxn,
    void               *arg0);
extern void BspOsal_unRegisterIntr(const BspOsal_IntrHandle *pIntrHandle);
extern void BspOsal_clearIntr(UInt32 intNum);
extern UInt32 BspOsal_disableInterrupt(void);
extern void BspOsal_restoreInterrupt(UInt32 cookie);

extern void BspOsal_sleep(UInt32 delayMsec);

extern UInt64 BspOsal_getTimestamp64(void);
extern UInt64 BspOsal_getTimestampFreq(void);
extern UInt32 BspOsal_getCurTimeInMsec(void);
extern UInt64 BspOsal_getCurTimeInUsec(void);

Int32 BspOsal_getStaticMemStatus(BspOsal_StaticMemStatus *pMemStat);

static inline void Empty_printf(void *buff)
{
    return;
}

/*
 * Cache APIs
 */
void BspOsal_cacheDisable(UInt32 type);
void BspOsal_cacheEnable(UInt32 type);
void BspOsal_cacheInv(void *blockPtr, UInt32 byteCnt, UInt32 type, UInt32 timeOut);
void BspOsal_cacheWb(void *blockPtr, UInt32 byteCnt, UInt32 type, UInt32 timeOut);
void BspOsal_cacheWbAll(void);
void BspOsal_cacheWbInv(void *blockPtr, UInt32 byteCnt, UInt32 type, UInt32 timeOut);
void BspOsal_cacheWbInvAll(void);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BSP_OSAL_H_ */
