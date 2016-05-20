/*
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== Core.c ========
 */

#include <xdc/std.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/Startup.h>

#include "package/internal/Core.xdc.h"

#define REG16(A)                    (*(volatile UInt16 *) (A))
#define REG32(A)                    (*(volatile UInt32 *) (A))

#define SYSESR                      0xFFFFFFE4
#define IMMGCTRL                    0xFFF7AC00
#define IMMFLAG                     0xFFF7AC18
#define IMMWORD0                    0xFFF7AC80
#define IMMWORD1                    0xFFF7AC84

/* Bit masks for different reset sources */
#define MPMODE                      0x00000001

#define IMM_ERROR_INTERRUPT_DISABLE 0x0500U
#define IMM_ERROR_OVERWRITE_DISABLE 0x0000U
#define IMM_MESSAGE_WORD1           0x0002U
#define IMM_RESET_VALUE             0x0555U

extern Void _c_int00();

/*
 *  ======== Core_Module_startup ========
 */
Int Core_Module_startup(Int status)
{
    UInt8 coreId = Core_getId();

    if (Core_id != coreId) {
        Error_raise(NULL, Core_E_mismatchedIds, Core_id, coreId);
    }

    return (Startup_DONE);
}

/*
 *  ======== Core_interruptCore ========
 */
Void Core_interruptCore(UInt coreId)
{
}

/*
 *  ======== Core_lock ========
 */
IArg Core_lock()
{
    return (Core_hwiDisable());
}

/*
 *  ======== Core_unlock ========
 */
Void Core_unlock()
{
}
/*
 *  ======== Core_syncStartup ========
 */
Void Core_syncStartup()
{
    volatile UInt32 dummy;
    UInt8 coreId = Core_getId();

    if (coreId != 0) {
        /* Write to word1 to signal init complete */
        REG32(IMMWORD1) = 0xAAAAAAAA;
        /* Perform a dummy read to ensure register write completed */
        dummy = REG32(IMMWORD1);
    }
    else {
        /* Enable IMM (keep error handling disabled) */
        REG32(IMMGCTRL) = IMM_ERROR_INTERRUPT_DISABLE |
                          IMM_ERROR_OVERWRITE_DISABLE;
        /* Write to word0 to signal init complete */
        REG32(IMMWORD0) = 0x55555555;
        /* Wait for Core1 to signal initialization complete */
        while (!(REG32(IMMFLAG) & IMM_MESSAGE_WORD1));
        /* Clear the flag for word1 */
        REG32(IMMFLAG) = 0x2;
        /* Disable IMM */
        REG32(IMMGCTRL) = IMM_RESET_VALUE;
        /* Perform a dummy read to ensure register write completed */
        dummy = REG32(IMMGCTRL);
    }
}

/*
 *  ======== Core_getResetSource ========
 */
Core_ResetSource Core_getResetSource()
{
    UInt sysesr = REG32(SYSESR);
    Core_ResetSource resetSource;

    if (sysesr & Core_ResetSource_POWERON) {
        resetSource = Core_ResetSource_POWERON;
        REG32(SYSESR) = 0x0000FFFF;
    }
    else if (sysesr & Core_ResetSource_OSC_FAILURE) {
        resetSource = Core_ResetSource_OSC_FAILURE;
        REG32(SYSESR) = Core_ResetSource_OSC_FAILURE;
    }
    else if (sysesr & Core_ResetSource_WATCHDOG) {
        resetSource = Core_ResetSource_WATCHDOG;
        REG32(SYSESR) = Core_ResetSource_WATCHDOG;
    }
    else if (sysesr & Core_ResetSource_WATCHDOG2) {
        resetSource = Core_ResetSource_WATCHDOG2;
        REG32(SYSESR) = Core_ResetSource_WATCHDOG2;
    }
    else if (sysesr & Core_ResetSource_DEBUG) {
        resetSource = Core_ResetSource_DEBUG;
        REG32(SYSESR) = Core_ResetSource_DEBUG;
    }
    else if (sysesr & Core_ResetSource_INTERCONNECT) {
        resetSource = Core_ResetSource_INTERCONNECT;
        REG32(SYSESR) = Core_ResetSource_INTERCONNECT;
    }
    else if (sysesr & Core_ResetSource_CPU1) {
        resetSource = Core_ResetSource_CPU1;
        REG32(SYSESR) = Core_ResetSource_CPU1;
    }
    else if (sysesr & Core_ResetSource_CPU0) {
        resetSource = Core_ResetSource_CPU0;
        REG32(SYSESR) = Core_ResetSource_CPU0;
    }
    else if (sysesr & Core_ResetSource_SW) {
        resetSource = Core_ResetSource_SW;
        REG32(SYSESR) = Core_ResetSource_SW;
    }
    else if (sysesr & Core_ResetSource_EXT) {
        resetSource = Core_ResetSource_EXT;
        REG32(SYSESR) = Core_ResetSource_EXT;
    }
    else {
        resetSource = Core_ResetSource_NO_RESET;
    }

    return (resetSource);
}
