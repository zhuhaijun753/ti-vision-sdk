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
 *  \file       trace.c
 *
 *  \brief      Trace implementation.
 *
 *              This abstracts and implements the definitions for
 *              user side traces statements and also details
 *              of variable traces supported in existing
 *              implementation.
 *
 *  \date       15 Apr, 2009
 *
 *  \internal   15 Apr, 2009, Mugdha Kamoolkar, Revision 0001:
 *              [1] Original version.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stdio.h>

#include <common/stw_dataTypes.h>
#include <common/stw_types.h>
#include <common/bsp_types.h>
#include <osal/bsp_osal.h>
#include <common/trace.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define REMOTE_DEBUG_SERVER_PRINT_BUF_LEN        (UInt32) (1024U * 2U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    UInt32 coreId;
    Char   printBuf[REMOTE_DEBUG_SERVER_PRINT_BUF_LEN];
} RemoteDebug_ServerObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

#ifdef PLATFORM_ZEBU
extern void uart1_write_formated(const Char *text, ...);
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
 #if !(defined (BUILD_A15)) && !(defined (BUILD_A8))
static RemoteDebug_ServerObj gRemoteDebug_serverObj = {0};
#endif
/** \brief Global trace flag. */
Int32 curTrace = 0;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 Bsp_printf(const Char *format, ...)
{
#if (defined (BUILD_A15)) || (defined (BUILD_A8))
    Int32   retVal = BSP_SOK;
#else
    va_list vaArgPtr;

    Int32   retVal = BSP_SOK;
    UInt32  cookie;
    Char   *buf = NULL;

    cookie = BspOsal_disableInterrupt();

    buf = &gRemoteDebug_serverObj.printBuf[0];

    va_start(vaArgPtr, format);
    vsnprintf(buf, REMOTE_DEBUG_SERVER_PRINT_BUF_LEN,
              (const Char *) format, vaArgPtr);
    va_end(vaArgPtr);

    BspOsal_restoreInterrupt(cookie);

    BspOsal_printf(buf);
#endif
    return (retVal);
}

Int32 Bsp_rprintf(const Char *format, ...)
{
#if (defined (BUILD_A15)) || (defined (BUILD_A8))
    Int32   retVal = BSP_SOK;
#else
    Int32   retVal = BSP_SOK;
    UInt32  cookie;
    Char   *buf = NULL;
    va_list vaArgPtr;

    cookie = BspOsal_disableInterrupt();

    buf = &gRemoteDebug_serverObj.printBuf[0];

    va_start(vaArgPtr, format);
    vsnprintf(buf, REMOTE_DEBUG_SERVER_PRINT_BUF_LEN,
              (const Char *) format, vaArgPtr);
    va_end(vaArgPtr);

    BspOsal_restoreInterrupt(cookie);
#endif
    return (retVal);
}

/**
 *  \brief      Function to log the trace with zero parameters and just
 *              information string.
 *  \param      mask type of traces.
 *  \param      classType One of three classes where this trace need
 *              to be enabed.
 *  \param      fileName    Where the condition has occured.
 *  \param      lineNum     Line number of the current file where this failure
 *                          has occured.
 *  \param      The debug string.
 */
void
GT_trace0(UInt32        maskType,
          GT_TraceClass classType,
          Char         *fileName,
          Int32         lineNum,
          const Char   *infoString)
{
    /* Check if trace is enabled. */
    if (((maskType & GT_TRACESTATE_MASK) >> GT_TRACESTATE_SHIFT)
        == GT_TraceState_Enable)
    {
        if ((classType == GT_ENTER) || (classType == GT_LEAVE))
        {
            if ((maskType & GT_TRACEENTER_MASK) == GT_TraceEnter_Enable)
            {
                Bsp_printf((const Char *) infoString);
            }
        }
        else
        {
            /* Check if specified class is enabled. */
            if ((maskType & GT_TRACECLASS_MASK) >= classType)
            {
                /* Print if specified class is greater than or equal to class
                 * for this specific print.
                 */
                if (!((classType == GT_INFO) || (classType == GT_INFO1)))
                {
                    Bsp_printf("%s @ Line %d: ", fileName, lineNum);
                }
                Bsp_printf((const Char *) infoString);
            }
        }
    }
}

/**
 *  \brief      Function to log the trace with one additional parameter
 *  \param      mask type of traces
 *  \param      classType One of three classes where this trace
 *              need to be enabed.
 *  \param      fileName    Where the condition has occured.
 *  \param      lineNum     Line number of the current file where this failure
 *                          has occured.
 *  \param      The debug string.
 *  \param      param The additional parameter which needs to be logged.
 */
void
GT_trace1(UInt32        maskType,
          GT_TraceClass classType,
          Char         *fileName,
          Int32         lineNum,
          const Char   *infoString,
          UInt32        param0)
{
    /* Check if trace is enabled. */
    if (((maskType & GT_TRACESTATE_MASK) >> GT_TRACESTATE_SHIFT)
        == GT_TraceState_Enable)
    {
        if ((classType == GT_ENTER) || (classType == GT_LEAVE))
        {
            if ((maskType & GT_TRACEENTER_MASK) == GT_TraceEnter_Enable)
            {
                Bsp_printf((const Char *) infoString, param0);
            }
        }
        else
        {
            /* Check if specified class is enabled. */
            if ((maskType & GT_TRACECLASS_MASK) >= classType)
            {
                /* Print if specified class is greater than or equal to class
                 * for this specific print.
                 */
                if (!((classType == GT_INFO) || (classType == GT_INFO1)))
                {
                    Bsp_printf("%s @ Line %d: ", fileName, lineNum);
                }
                Bsp_printf((const Char *) infoString, param0);
            }
        }
    }
}

/**
 *  \brief      Function to log the trace with two additional parameters
 *  \param      mask type of traces
 *  \param      classType One of three classes where this trace
 *              need to be enabed.
 *  \param      fileName    Where the condition has occured.
 *  \param      lineNum     Line number of the current file where this failure
 *                          has occured.
 *  \param      The debug string.
 *  \param      param0 The first parameter which needs to be logged.
 *  \param      param1 The second parameter which needs to be logged.
 */
void
GT_trace2(UInt32        maskType,
          GT_TraceClass classType,
          Char         *fileName,
          Int32         lineNum,
          const Char   *infoString,
          UInt32        param0,
          UInt32        param1)
{
    /* Check if trace is enabled. */
    if (((maskType & GT_TRACESTATE_MASK) >> GT_TRACESTATE_SHIFT)
        == GT_TraceState_Enable)
    {
        if ((classType == GT_ENTER) || (classType == GT_LEAVE))
        {
            if ((maskType & GT_TRACEENTER_MASK) == GT_TraceEnter_Enable)
            {
                Bsp_printf((const Char *) infoString, param0, param1);
            }
        }
        else
        {
            /* Check if specified class is enabled. */
            if ((maskType & GT_TRACECLASS_MASK) >= classType)
            {
                /* Print if specified class is greater than or equal to class
                 * for this specific print.
                 */
                if (!((classType == GT_INFO) || (classType == GT_INFO1)))
                {
                    Bsp_printf("%s @ Line %d: ", fileName, lineNum);
                }
                Bsp_printf((const Char *) infoString, param0, param1);
            }
        }
    }
}

/**
 *  \brief      Function to log the trace with three parameters.
 *  \param      mask type of traces
 *  \param      classType One of three classes where this trace
 *              need to be enabed.
 *  \param      fileName    Where the condition has occured.
 *  \param      lineNum     Line number of the current file where this failure
 *                          has occured.
 *  \param      The debug string.
 *  \param      param0 The first parameter which needs to be logged.
 *  \param      param1 The second parameter which needs to be logged.
 *  \param      param2 The third parameter which needs to be logged.
 */
void
GT_trace3(UInt32        maskType,
          GT_TraceClass classType,
          Char         *fileName,
          Int32         lineNum,
          const Char   *infoString,
          UInt32        param0,
          UInt32        param1,
          UInt32        param2)
{
    /* Check if trace is enabled. */
    if (((maskType & GT_TRACESTATE_MASK) >> GT_TRACESTATE_SHIFT)
        == GT_TraceState_Enable)
    {
        if ((classType == GT_ENTER) || (classType == GT_LEAVE))
        {
            if ((maskType & GT_TRACEENTER_MASK) == GT_TraceEnter_Enable)
            {
                Bsp_printf((const Char *) infoString, param0, param1, param2);
            }
        }
        else
        {
            /* Check if specified class is enabled. */
            if ((maskType & GT_TRACECLASS_MASK) >= classType)
            {
                /* Print if specified class is greater than or equal to class
                 * for this specific print.
                 */
                if (!((classType == GT_INFO) || (classType == GT_INFO1)))
                {
                    Bsp_printf("%s @ Line %d: ", fileName, lineNum);
                }
                Bsp_printf((const Char *) infoString, param0, param1, param2);
            }
        }
    }
}

/**
 *  \brief      Function to log the trace with four parameters.
 *  \param      mask type of traces
 *  \param      classType One of three classes where this trace
 *              need to be enabed.
 *  \param      fileName    Where the condition has occured.
 *  \param      lineNum     Line number of the current file where this failure
 *                          has occured.
 *  \param      The debug string.
 *  \param      param0 The first parameter which needs to be logged.
 *  \param      param1 The second parameter which needs to be logged.
 *  \param      param2 The third parameter which needs to be logged.
 *  \param      param3 The fourth parameter which needs to be logged.
 */
void
GT_trace4(UInt32        maskType,
          GT_TraceClass classType,
          Char         *fileName,
          Int32         lineNum,
          const Char   *infoString,
          UInt32        param0,
          UInt32        param1,
          UInt32        param2,
          UInt32        param3)
{
    /* Check if trace is enabled. */
    if (((maskType & GT_TRACESTATE_MASK) >> GT_TRACESTATE_SHIFT)
        == GT_TraceState_Enable)
    {
        if ((classType == GT_ENTER) || (classType == GT_LEAVE))
        {
            if ((maskType & GT_TRACEENTER_MASK) == GT_TraceEnter_Enable)
            {
                Bsp_printf((const Char *) infoString, param0, param1, param2,
                           param3);
            }
        }
        else
        {
            /* Check if specified class is enabled. */
            if ((maskType & GT_TRACECLASS_MASK) >= classType)
            {
                /* Print if specified class is greater than or equal to class
                 * for this specific print.
                 */
                if (!((classType == GT_INFO) || (classType == GT_INFO1)))
                {
                    Bsp_printf("%s @ Line %d: ", fileName, lineNum);
                }
                Bsp_printf((const Char *) infoString, param0, param1, param2,
                           param3);
            }
        }
    }
}

/**
 *  \brief      Function to log the trace with five parameters.
 *  \param      mask type of traces
 *  \param      classType One of three classes where this trace
 *              need to be enabed.
 *  \param      fileName    Where the condition has occured.
 *  \param      lineNum     Line number of the current file where this failure
 *                          has occured.
 *  \param      The debug string.
 *  \param      param0 The first parameter which needs to be logged.
 *  \param      param1 The second parameter which needs to be logged.
 *  \param      param2 The third parameter which needs to be logged.
 *  \param      param3 The fourth parameter which needs to be logged.
 *  \param      param4 The fifth parameter which needs to be logged.
 */
void
GT_trace5(UInt32        maskType,
          GT_TraceClass classType,
          Char         *fileName,
          Int32         lineNum,
          const Char   *infoString,
          UInt32        param0,
          UInt32        param1,
          UInt32        param2,
          UInt32        param3,
          UInt32        param4)
{
    /* Check if trace is enabled. */
    if (((maskType & GT_TRACESTATE_MASK) >> GT_TRACESTATE_SHIFT)
        == GT_TraceState_Enable)
    {
        if ((classType == GT_ENTER) || (classType == GT_LEAVE))
        {
            if ((maskType & GT_TRACEENTER_MASK) == GT_TraceEnter_Enable)
            {
                Bsp_printf((const Char *) infoString,
                           param0,
                           param1,
                           param2,
                           param3,
                           param4);
            }
        }
        else
        {
            /* Check if specified class is enabled. */
            if ((maskType & GT_TRACECLASS_MASK) >= classType)
            {
                /* Print if specified class is greater than or equal to class
                 * for this specific print.
                 */
                if (!((classType == GT_INFO) || (classType == GT_INFO1)))
                {
                    Bsp_printf("%s @ Line %d: ", fileName, lineNum);
                }
                Bsp_printf((const Char *) infoString,
                           param0,
                           param1,
                           param2,
                           param3,
                           param4);
            }
        }
    }
}

/**
 *  \brief      Function to log the trace with six parameters.
 *  \param      mask type of traces
 *  \param      classType One of three classes where this trace
 *              need to be enabed.
 *  \param      fileName    Where the condition has occured.
 *  \param      lineNum     Line number of the current file where this failure
 *                          has occured.
 *  \param      The debug string.
 *  \param      param0 The first parameter which needs to be logged.
 *  \param      param1 The second parameter which needs to be logged.
 *  \param      param2 The third parameter which needs to be logged.
 *  \param      param3 The fourth parameter which needs to be logged.
 *  \param      param4 The fifth parameter which needs to be logged.
 *  \param      param5 The sixth parameter which needs to be logged.
 */
void
GT_trace6(UInt32        maskType,
          GT_TraceClass classType,
          Char         *fileName,
          Int32         lineNum,
          const Char   *infoString,
          UInt32        param0,
          UInt32        param1,
          UInt32        param2,
          UInt32        param3,
          UInt32        param4,
          UInt32        param5)
{
    /* Check if trace is enabled. */
    if (((maskType & GT_TRACESTATE_MASK) >> GT_TRACESTATE_SHIFT)
        == GT_TraceState_Enable)
    {
        if ((classType == GT_ENTER) || (classType == GT_LEAVE))
        {
            if ((maskType & GT_TRACEENTER_MASK) == GT_TraceEnter_Enable)
            {
                Bsp_printf((const Char *) infoString,
                           param0,
                           param1,
                           param2,
                           param3,
                           param4,
                           param5);
            }
        }
        else
        {
            /* Check if specified class is enabled. */
            if ((maskType & GT_TRACECLASS_MASK) >= classType)
            {
                /* Print if specified class is greater than or equal to class
                 * for this specific print.
                 */
                if (!((classType == GT_INFO) || (classType == GT_INFO1)))
                {
                    Bsp_printf("%s @ Line %d: ", fileName, lineNum);
                }
                Bsp_printf((const Char *) infoString,
                           param0,
                           param1,
                           param2,
                           param3,
                           param4,
                           param5);
            }
        }
    }
}

/**
 *  \brief      Function to log the trace with seven parameters.
 *  \param      mask type of traces
 *  \param      classType One of three classes where this trace
 *              need to be enabed.
 *  \param      fileName    Where the condition has occured.
 *  \param      lineNum     Line number of the current file where this failure
 *                          has occured.
 *  \param      The debug string.
 *  \param      param0 The first parameter which needs to be logged.
 *  \param      param1 The second parameter which needs to be logged.
 *  \param      param2 The third parameter which needs to be logged.
 *  \param      param3 The fourth parameter which needs to be logged.
 *  \param      param4 The fifth parameter which needs to be logged.
 *  \param      param5 The sixth parameter which needs to be logged.
 *  \param      param6 The sixth parameter which needs to be logged.
 */
void
GT_trace7(UInt32        maskType,
          GT_TraceClass classType,
          Char         *fileName,
          Int32         lineNum,
          const Char   *infoString,
          UInt32        param0,
          UInt32        param1,
          UInt32        param2,
          UInt32        param3,
          UInt32        param4,
          UInt32        param5,
          UInt32        param6)
{
    /* Check if trace is enabled. */
    if (((maskType & GT_TRACESTATE_MASK) >> GT_TRACESTATE_SHIFT)
        == GT_TraceState_Enable)
    {
        if ((classType == GT_ENTER) || (classType == GT_LEAVE))
        {
            if ((maskType & GT_TRACEENTER_MASK) == GT_TraceEnter_Enable)
            {
                Bsp_printf((const Char *) infoString,
                           param0,
                           param1,
                           param2,
                           param3,
                           param4,
                           param5,
                           param6);
            }
        }
        else
        {
            /* Check if specified class is enabled. */
            if ((maskType & GT_TRACECLASS_MASK) >= classType)
            {
                /* Print if specified class is greater than or equal to class
                 * for this specific print.
                 */
                if (!((classType == GT_INFO) || (classType == GT_INFO1)))
                {
                    Bsp_printf("%s @ Line %d: ", fileName, lineNum);
                }
                Bsp_printf((const Char *) infoString,
                           param0,
                           param1,
                           param2,
                           param3,
                           param4,
                           param5,
                           param6);
            }
        }
    }
}

/**
 *  \brief      Function to report the vps failure and log the trace. This
 *              is mostly the fatal error and system can not recover without
 *              module restart.
 *  \param      mask        Indicates whether SetFailure is enabled.
 *  \param      func        Name of the function where this oc.cured
 *  \param      fileName    Where the condition has occured.
 *  \param      lineNum     Line number of the current file where this failure
 *                          has occured.
 *  \param      status      What was the code we got/set for this failure
 *  \param      msg         Any additional information which can be useful for
 *                          deciphering the error condition.
 */
void GT_failureReasonSet(Int32  enableMask,
                         Char  *func,
                         Char  *fileName,
                         Int32  lineNum,
                         UInt32 status,
                         Char  *msg)
{
    if ((((UInt32) enableMask &
          GT_TRACESETFAILURE_MASK) >> GT_TRACESETFAILURE_SHIFT)
        == GT_TraceState_Enable)
    {
        Bsp_printf("*** %s: %s\tError [0x%x] at Line no: %d in file %s\n",
                   func,
                   msg,
                   status,
                   lineNum,
                   fileName);
    }
}

