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
 *  ======== IpcMgr.xs ========
 */

var IpcMgr           = null;
var MultiProc        = null;
var NotifyDriverCirc = null;
var NameServerBlock  = null;
var TransportCirc    = null;
var Hwi              = null;
var Boot             = null;

/*
 *  ======== module$meta$init ========
 */
function module$meta$init()
{
    /* Only process during "cfg" phase */
    if (xdc.om.$name != "cfg") {
        return;
    }

    IpcMgr = this;

    var NameServer = xdc.useModule('ti.sdo.utils.NameServer');
    NameServer.SetupProxy = xdc.useModule('ti.sdo.ipc.family.f2837x.NameServerBlock');
}

/*
 *  ======== module$use ========
 */
function module$use()
{
    MultiProc = xdc.useModule("ti.sdo.utils.MultiProc");
    NotifyDriverCirc =
        xdc.useModule("ti.sdo.ipc.family.f2837x.NotifyDriverCirc");
    NameServerBlock =
        xdc.useModule("ti.sdo.ipc.family.f2837x.NameServerBlock");
    TransportCirc =
        xdc.useModule("ti.sdo.ipc.family.f2837x.TransportCirc");
    Hwi = xdc.useModule("ti.sysbios.hal.Hwi");

    if (IpcMgr.cpu1) {
        Boot = xdc.useModule("ti.catalog.c2800.initF2837x.Boot");
    }

    /* Init the number of messages for notify driver */
    NotifyDriverCirc.numMsgs = IpcMgr.numNotifyMsgs;

    /* Init the number of messages for messageQ transport */
    TransportCirc.numMsgs = IpcMgr.numMessageQMsgs;
    TransportCirc.maxMsgSizeInBytes = IpcMgr.messageQSize;
    TransportCirc.notifyEventId = IpcMgr.messageQEventId;
}

/*
 *  ======== module$static$init ========
 */
function module$static$init(mod, params)
{
    /* check to make sure readAddr and writeAddr have been set */
    if (params.readAddr == undefined) {
        IpcMgr.$logError("IpcMgr.readAddr is undefined", IpcMgr);
    }

    if (params.writeAddr == undefined) {
        IpcMgr.$logError("IpcMgr.writeAddr is undefined", IpcMgr);
    }

    /* init the interrupt ids */
    if ((params.ipcSetFlag < 0) || (params.ipcSetFlag > 3)) {
        IpcMgr.$logError("IpcMgr.ipcSetFlag must be 0, 1, 2, or 3 " +
            "because they are the only flags associated with an interrupt.",
            IpcMgr);
    }

    /* calculate the amount of shared memory used */
    IpcMgr.sharedMemSizeUsed = NotifyDriverCirc.sharedMemReqMeta(null) +
                               NameServerBlock.sharedMemReqMeta(null) +
                               TransportCirc.sharedMemReqMeta(null);

    /* validate sharedMemoryOwnerMask is correct for the readAddr/writeAddr */
    if (IpcMgr.cpu1) {
        /* TODO: This needs to be tested. */
        /*  From linker command file
         *  (ti/platforms/tms320x28/include/F28377D.cmd),
         *  these are the shared ram blocks:
         *  RAMGS0  : origin = 0x00C000, length = 0x001000
         *  RAMGS1  : origin = 0x00D000, length = 0x001000
         *  RAMGS2  : origin = 0x00E000, length = 0x001000
         *  RAMGS3  : origin = 0x00F000, length = 0x001000
         *  RAMGS4  : origin = 0x010000, length = 0x001000
         *  RAMGS5  : origin = 0x011000, length = 0x001000
         *  RAMGS6  : origin = 0x012000, length = 0x001000
         *  RAMGS7  : origin = 0x013000, length = 0x001000
         *  RAMGS8  : origin = 0x014000, length = 0x001000
         *  RAMGS9  : origin = 0x015000, length = 0x001000
         *  RAMGS10 : origin = 0x016000, length = 0x001000
         *  RAMGS11 : origin = 0x017000, length = 0x001000
         *  RAMGS12 : origin = 0x018000, length = 0x001000
         *  RAMGS13 : origin = 0x019000, length = 0x001000
         *  RAMGS14 : origin = 0x01A000, length = 0x001000
         *  RAMGS15 : origin = 0x01B000, length = 0x001000
         */

        var Boot = xdc.module('ti.catalog.c2800.initF2837x.Boot');
        if ((IpcMgr.writeAddr >= 0xC000) && (IpcMgr.writeAddr < 0x1C000)) {
            /*
             *  Determine segment being used for the writeAddr.
             *  The shared RAM base address starts 0xC000 to 0x1A000.
             *  Each segment with a length of 0x2000 (byte addressing).
             */
            var writeSeg = (IpcMgr.writeAddr - 0xC000) >> 13;

            /* This CPU must be owner of writeAddr shared memory segment */
            if (Boot.sharedMemoryOwnerMask & (1 << writeSeg)) {
                IpcMgr.$logError("IpcMgr.writeAddr is set to address: " +
                utils.toHex(IpcMgr.writeAddr) + "," +
                " but Boot.sharedMemoryOwnerMask bit: " + writeSeg +
                " must not be set. Unset this bit to make CPU1 the owner.",
                        IpcMgr);
            }
        }

        if ((IpcMgr.readAddr >= 0xC000) &&
            (IpcMgr.readAddr < 0x1C000)) {
            /*
             *  Determine segment being used for the CPU2 readAddr.
             *  The shared RAM base address starts 0xC000 to 0x1A000.
             *  Each segment with a length of 0x2000 (byte addressing).
             */
            var readSeg = (IpcMgr.readAddr - 0xC000) >> 13;

            /* CPU2 must be owner of readAddr shared memory segment */
            if (!(Boot.sharedMemoryOwnerMask & (1 << readSeg))) {
                IpcMgr.$logError("IpcMgr.readAddr is set to address: " +
                utils.toHex(IpcMgr.readAddr) + "," +
                " but IpcMgr.sharedMemoryOwnerMask bit: " + readSeg +
                " is not set. This bit must be set so CPU2 is the owner.",
                        IpcMgr);
            }
        }
    }
}

/*
 *  ======== module$validate ========
 */
function module$validate()
{
    if ((xdc.module('ti.sdo.ipc.Ipc').$used) ||
        (xdc.module('ti.sdo.ipc.GateMP').$used) ||
        (xdc.module('ti.sdo.ipc.SharedRegion').$used) ||
        (xdc.module('ti.sdo.ipc.ListMP').$used)) {
        IpcMgr.$logError("One or more of the following modules " +
            "[Ipc, GateMP, ListMP, SharedRegion] are being used " +
            "but are not supported on this device.", IpcMgr);
    }
}
