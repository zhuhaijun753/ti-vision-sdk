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
 *  ======== NotifyDriverCirc.xs ================
 */

var NotifyDriverCirc = null;
var IpcMgr           = null;
var MultiProc        = null;
var Notify           = null;
var Hwi              = null;

var IPC = [ 132, 133, 134, 135 ];

/*
 *  ======== module$use ========
 */
function module$use()
{
    NotifyDriverCirc = this;
    IpcMgr           = xdc.useModule("ti.sdo.ipc.family.f2837x.IpcMgr");
    MultiProc        = xdc.useModule("ti.sdo.utils.MultiProc");
    Notify           = xdc.useModule("ti.sdo.ipc.Notify");
    Hwi              = xdc.useModule("ti.sysbios.hal.Hwi");
}

/*
 *  ======== module$static$init ========
 */
function module$static$init(mod, params)
{
    NotifyDriverCirc.maxIndex = NotifyDriverCirc.numMsgs - 1;
    NotifyDriverCirc.modIndex = NotifyDriverCirc.numMsgs / 4;

    /* determine the local and remote interrupt id */
    NotifyDriverCirc.localIntId = IPC[IpcMgr.ipcSetFlag];
    NotifyDriverCirc.remoteIntId = IPC[IpcMgr.ipcSetFlag];
}

/*
 *  ======== sharedMemReqMeta ========
 */
function sharedMemReqMeta(params)
{
    /*
     *  Amount of shared memory:
     *  1 putBuffer with numMsgs +
     *  1 putWriteIndex ptr      +
     *  1 getReadIndex ptr
     */
    memReq =
        (NotifyDriverCirc.EventEntry.$sizeof() * NotifyDriverCirc.numMsgs) +
        (2 * Program.build.target.stdTypes['t_Int32'].size);

    return (memReq);
}

/*
 *************************************************************************
 *                       ROV View functions
 *************************************************************************
 */

/*
 *  ======== viewInitBasic ========
 */
function viewInitBasic(view, obj)
{
    var MultiProc = xdc.useModule('ti.sdo.utils.MultiProc');
    var modCfg =
        Program.getModuleConfig('ti.sdo.ipc.family.f2837x.NotifyDriverCirc');

    /* view.remoteProcName */
    try {
        view.remoteProcName = MultiProc.getName$view(obj.remoteProcId);
    }
    catch(e) {
        Program.displayError(view, 'remoteProcName',
                             "Problem retrieving proc name: " + e);
    }

    /* view obj information */
    view.bufSize      = modCfg.numMsgs;
}

/*
 *  ======== getEventData ========
 *  Helper function for use within viewInitData
 */
function getEventData(view, obj, bufferPtr, putIndex, getIndex)
{
    var NotifyDriverCirc =
        xdc.useModule('ti.sdo.ipc.family.f2837x.NotifyDriverCirc');
    var modCfg =
        Program.getModuleConfig('ti.sdo.ipc.family.f2837x.NotifyDriverCirc');

    if (bufferPtr == obj.putBuffer) {
        var bufferName = "put";
    }
    else {
        var bufferName = "get";
    }

    try {
        var putBuffer = Program.fetchArray(obj.putBuffer$fetchDesc,
                                           bufferPtr,
                                           modCfg.numMsgs);
    }
    catch(e) {
        throw (new Error("Error fetching putBuffer struct from shared memory"));
    }

    var i = getIndex;

    while (i != putIndex) {
        /* The event is registered */
        var elem = Program.newViewStruct(
                'ti.sdo.ipc.family.f2837x.NotifyDriverCirc',
                'Events');

        elem.index = i;
        elem.buffer = bufferName;
        elem.addr = utils.toHex(putBuffer[i].$addr);
        elem.eventId = putBuffer[i].eventid;
        elem.payload = utils.toHex(putBuffer[i].payload);

        /* Create a new row in the instance data view */
        view.elements.$add(elem);

        i++;
    }
}

/*
 *  ======== viewInitData ========
 *  Instance data view.
 */
function viewInitData(view, obj)
{
    var Program         = xdc.useModule('xdc.rov.Program');
    var ScalarStructs   = xdc.useModule('xdc.rov.support.ScalarStructs');
    var MultiProc = xdc.useModule('ti.sdo.utils.MultiProc');

    try {
        var notifyObj = Program.scanHandleView('ti.sdo.ipc.Notify',
            obj.notifyHandle, 'Basic');
    }
    catch (e) {
        throw (new Error("Error fetching Notify instance view"));
    }

    /* Display the instance label in the tree */
    view.label = "remoteProcId = " + obj.remoteProcId + " lineId = " +
        notifyObj.lineId;

    /* Fetch put/get index's */
    try {
        var putWriteIndex = Program.fetchStruct(ScalarStructs.S_Bits32$fetchDesc,
                                                obj.putWriteIndex);
    }
    catch(e) {
        throw (new Error("Error fetching putWriteIndex " +
                         "struct from shared memory"));
    }

    try {
        var putReadIndex = Program.fetchStruct(ScalarStructs.S_Bits32$fetchDesc,
                                               obj.putReadIndex);
    }
    catch(e) {
        throw (new Error("Error fetching putReadIndex " +
                         "struct from shared memory"));
    }

    try {
        var getWriteIndex = Program.fetchStruct(ScalarStructs.S_Bits32$fetchDesc,
                                                obj.getWriteIndex);
    }
    catch(e) {
        throw (new Error("Error fetching getWriteIndex " +
                         "struct from shared memory"));
    }

    try {
        var getReadIndex = Program.fetchStruct(ScalarStructs.S_Bits32$fetchDesc,
                                               obj.getReadIndex);
    }
    catch(e) {
        throw (new Error("Error fetching getReadIndex " +
                         "struct from shared memory"));
    }

    /* Get event data for the put buffer */
    getEventData(view, obj, obj.putBuffer, putWriteIndex.elem,
                 putReadIndex.elem);

    /* Get event data for the get buffer */
    getEventData(view, obj, obj.getBuffer, getWriteIndex.elem,
                 getReadIndex.elem);
}
