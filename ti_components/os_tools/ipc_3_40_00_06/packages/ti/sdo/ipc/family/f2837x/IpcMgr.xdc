/*
 * Copyright (c) 2014, Texas Instruments Incorporated
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
 *  ======== IpcMgr.xdc ========
 */

import xdc.runtime.Assert;
import xdc.runtime.Error;

/*!
 *  ======== IpcMgr ========
 *  IPC Manager
 *
 *  This modules is used only for F2837x devices.  Users can statically
 *  configure which shared memory segments to enable, the owner processor
 *  and the owner's write access.  This module is used for specifying shared
 *  memory for IPC between the two C28 processors (CPU1 master and
 *  CPU2 slave).
 *
 *  There are no API's that need to be called.  The necessary drivers for
 *  IPC are all created within this module's startup function.  The shared
 *  memory is also programmed within this function.  There is handshaking
 *  between the processors.  CPU1 releases CPU2 from reset and both processors
 *  will synchronize at this point.
 *
 *  The {@link #readAddr} must point to shared memory which is writeable
 *  by the remote core while the {@link #writeAddr} must point to shared
 *  memory which is writeable by the local core.  The {@link #readAddr}
 *  and {@link #writeAddr} pointers must point to different shared memory
 *  blocks.  Memory addresses must be specified in the local core's
 *  memory space.
 *
 *  The {@link #cpu1} configuration parameter specifies whether or not
 *  the executable will be run on CPU1 or CPU2.
 *
 *  For example on CPU1:
 *  @p(code)
 *  var IpcMgr = xdc.useModule('ti.sdo.ipc.family.f2837x.IpcMgr');
 *  IpcMgr.readAddr  = 0x3F800;
 *  IpcMgr.writeAddr = 0x3FC00;
 *  @p
 *
 *  On the CPU2:
 *  @p(code)
 *  var IpcMgr = xdc.useModule('ti.sdo.ipc.family.f2837x.IpcMgr');
 *  IpcMgr.readAddr  = 0x3FC00;
 *  IpcMgr.writeAddr = 0x3F800;
 *  IpcMgr.cpu1 = false;
 *  @p
 */

@ModuleStartup

module IpcMgr
{
    /*
     *************************************************************************
     *                       Generic Errors/Asserts
     *************************************************************************
     */

    /*!
     *  ======== A_internal ========
     *  Assert raised when an internal error is encountered
     */
    config Assert.Id A_internal = {
        msg: "A_internal: An internal error has occurred"
    };

    /*!
     *  ======== A_invParam ========
     *  Assert raised when a parameter is invalid
     */
    config Assert.Id A_invParam  = {
        msg: "A_invParam: Invalid configuration parameter supplied"
    };

    /*!
     *  ======== A_notEnoughMemory ========
     *  Assert raised when there's not enough memory for creating instances.
     */
    config Assert.Id A_notEnoughMemory  = {
        msg: "A_notEnoughMemory: There is not enough memory for operation"
    };

    /*!
     *  ======== A_nullArgument ========
     *  Assert raised when a required argument is null
     */
    config Assert.Id A_nullArgument  = {
        msg: "A_nullArgument: Required argument is null"
    };

    /*!
     *  ======== E_internal ========
     *  Error raised when an internal error occured
     */
    config Error.Id E_internal  = {
        msg: "E_internal: An internal error occurred"
    };

    /*
     *************************************************************************
     *                       Module-wide Config Parameters
     *************************************************************************
     */

    /*!
     *  ======== genLinkerSections ========
     *  For generating or not generating the linker sections
     *
     *  By default this is set to 'true' so the following linker sections
     *  are generated for the amount of memory used for IPC. For the
     *  read address - "ti.sdo.ipc.family.f2837x.IpcMgr.readSect" and for
     *  the write address - "ti.sdo.ipc.family.f2837x.IpcMgr.writeSect".
     *  To disable generation, set this to 'false'.
     */
    metaonly config Bool genLinkerSections = true;

    /*!
     *  ======== cpu1 ========
     *  Set to false if this is CPU2.
     */
    config Bool cpu1 = true;

    /*!
     *  ======== ipcSetFlag ========
     *  The IPC set flag that is used for generating the IPC interrupt
     *
     *  Only a value of 0, 1, 2, or 3 are valid since only those flags
     *  have an interrupt associated with them. This value must be the
     *  same on both processors.
     */
    config UInt32 ipcSetFlag = 3;

    /*!
     *  ======== messageQSize ========
     *  The largest MessageQ size (in bytes) supported by the transport
     *
     *  This value must be large enough to handle the largest message.
     *  The size must be specified in bytes.
     */
    config UInt32 messageQSize = 128;

    /*!
     *  ======== messageQEventId ========
     *  Notify event ID for MessageQ transport.
     */
    config UInt16 messageQEventId = 2;

    /*!
     *  ======== nameServerEventId ========
     *  Notify event ID for NameServer.
     */
    config UInt16 nameServerEventId = 4;

    /*!
     *  ======== numNotifyMsgs ========
     *  The number of messages for the Notify driver's circular buffer
     *
     *  This is used to determine the size of the put and get buffers.
     *  This value must be a power of 2.  A value of 'N' allows 'N-1'
     *  outstanding notifications.
     */
    config UInt32 numNotifyMsgs = 32;

    /*!
     *  ======== numMessageQMsgs ========
     *  The number of messages for the MessageQ transport's circular buffer
     *
     *  This is used to determine the size of the put and get buffers.
     *  This value must be a power of 2.  A value of 'N' allows 'N-1'
     *  outstanding notifications.
     */
    config UInt32 numMessageQMsgs = 4;

    /*!
     *  ======== readAddr ========
     *  The base address of read-only shared memory.
     *
     *  The address must be specified in the local core's memory space.
     *  It must point to the same physical address as the writeAddr for
     *  the remote processor.
     */
    config Ptr readAddr;

    /*!
     *  ======== writeAddr ========
     *  The base address of read/write shared memory.
     *
     *  The address must be specified in the local core's memory space.
     *  It must point to the same physical address as the readAddr for
     *  the remote processor.
     */
    config Ptr writeAddr;

internal:

    /* the amount of shared memory used */
    config UInt32 sharedMemSizeUsed;

    /* function to create NotifyCirc driver instances */
    Int notifyCircAttach(UInt16 remoteProcId, Ptr writeAddr, Ptr readAddr);

    /* function to create NameServer remote instances */
    Int nameServerAttach(UInt16 remoteProcId, Ptr writeAddr, Ptr readAddr);

    /* function to create MessageQ transport instances */
    Int transportCircAttach(UInt16 remoteProcId, Ptr writeAddr, Ptr readAddr);
}
