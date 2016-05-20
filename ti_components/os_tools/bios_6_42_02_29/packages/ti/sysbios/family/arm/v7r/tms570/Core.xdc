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
 *  ======== Core.xdc ========
 */

import xdc.runtime.Error;

/*!
 *  ======== Core ========
 *  Core Identification Module.
 *
 *  The Core module is used to define which core within a dual core
 *  "R5" subsystem an application is being built for.
 *
 *  At runtime, a comparison is made between the configured Core.id
 *  and the value of MPIDR (bits 7:0). If they do not agree, an Error
 *  is raised.
 *
 *  Core 0's vector table is placed at 0x100 and Core 1's vector table
 *  is placed at 0x20000.
 *
 *  @a(Bootup sequence)
 *  When each Cortex-R5 core comes out of reset, it runs a routine that
 *  determines the source of reset and depending on the source either
 *  continues executing the bootup sequence or calls a reset callback
 *  function corresponding to the detected reset source.
 *
 *  In case the reset source is a PowerOn/Debug/External reset signal,
 *  the normal bootup sequence is continued (i.e. data section init
 *  and execution of various kernel module startup functions before
 *  calling main() function).
 *
 *  For other reset sources, the callback functions corresponding to
 *  the reset source are called. Here's an example showing how to register
 *  a software reset callback function:
 *
 *  @p(code)
 *  var Core = xdc.useModule('ti.sysbios.family.arm.v7r.tms570.Core');
 *  Core.swResetFunc = '&myfunc';
 *  @p
 */

@ModuleStartup          /* to configure static timers */
@Template ("./Core.xdt")

module Core inherits ti.sysbios.interfaces.ICore
{
    /*! Reset function type definition. */
    typedef Void (*ResetFuncPtr)(void);

    /*!
     *  @_nodoc
     *  Reset sources
     */
    enum ResetSource
    {
        ResetSource_POWERON       =   0x8000U,
        ResetSource_OSC_FAILURE   =   0x4000U,
        ResetSource_WATCHDOG      =   0x2000U,
        ResetSource_WATCHDOG2     =   0x1000U,
        ResetSource_DEBUG         =   0x0800U,
        ResetSource_INTERCONNECT  =   0x0080U,
        ResetSource_CPU1          =   0x0040U,
        ResetSource_CPU0          =   0x0020U,
        ResetSource_SW            =   0x0010U,
        ResetSource_EXT           =   0x0008U,
        ResetSource_NO_RESET      =   0x0000U
    };

    /*!
     *  Error raised if Core.id does not match the contents
     *  of MPIDR [7:0] register.
     */
    config Error.Id E_mismatchedIds = {
        msg: "E_mismatchedIds: Core_Id: %d does not match hardware core Id: %d"
    };

    override config UInt numCores;

    /*!
     *  R5 Core ID, default is Core 0
     *
     *  Used for making static decisions based on Core ID
     */
    config UInt id = 0;

    /*!
     *  ======== cpu0ResetFunc ========
     *  CPU0 reset function pointer
     */
    metaonly config ResetFuncPtr cpu0ResetFunc = null;

    /*!
     *  ======== cpu1ResetFunc ========
     *  CPU1 reset function pointer
     */
    metaonly config ResetFuncPtr cpu1ResetFunc = null;

    /*!
     *  ======== interconnectResetFunc ========
     *  Interconnect reset function pointer
     */
    metaonly config ResetFuncPtr interconnectResetFunc = null;

    /*!
     *  ======== oscFailureResetFunc ========
     *  Oscillator failure reset function pointer
     */
    metaonly config ResetFuncPtr oscFailureResetFunc = null;

    /*!
     *  ======== swResetFunc ========
     *  Software reset function pointer
     */
    metaonly config ResetFuncPtr swResetFunc = null;

    /*!
     *  ======== watchdogResetFunc ========
     *  Watchdog reset function pointer
     */
    metaonly config ResetFuncPtr watchdogResetFunc = null;

    /*!
     *  ======== watchdog2ResetFunc ========
     *  Watchdog2 reset function pointer
     */
    metaonly config ResetFuncPtr watchdog2ResetFunc = null;

    @Macro
    override UInt hwiDisable();

    @Macro
    override UInt hwiEnable();

    @Macro
    override Void hwiRestore(UInt key);

internal:

    /*
     *  ======== syncStartup ========
     *  Sync Core0 and Core1 during startup.
     */
    Void syncStartup();

    /*
     *  ======== getResetSource ========
     */
    ResetSource getResetSource();

    /*
     *  ======== resetC ========
     */
    Void resetC();
}
