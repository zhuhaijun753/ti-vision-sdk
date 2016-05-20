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
 *  ======== Mpu.c ========
 */

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Startup.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/hal/Hwi.h>

#if (defined xdc_target__isaCompatible_v7R)
#include <ti/sysbios/family/arm/v7r/Cache.h>
#else
#include <ti/sysbios/hal/CacheNull.h>
#endif

#include "package/internal/Mpu.xdc.h"

/*
 *  ======== Mpu_startup ========
 */
Void Mpu_startup()
{
    Mpu_disableBR();

    /*
     * Initialize all MPU regions
     */
    Mpu_initRegions();

    if (Mpu_enableMPU) {
        Mpu_enable();
    }

    if (Mpu_enableBackgroundRegion) {
        Mpu_enableBR();
    }
}

/*
 *  ======== Mpu_disable ========
 *  Function to disable the MPU.
 */
Void Mpu_disable()
{
    UInt16 type;
    UInt   key;

    if (!(Mpu_isEnabled())) {
        return;
    }

    key = Hwi_disable();

    /* get the current enabled bits */
    type = Cache_getEnabled();

    /* disable all enabled caches */
    Cache_disable(type);

    /* disables the MPU */
    Mpu_disableAsm();

    /* set cache back to initial settings */
    Cache_enable(type);

    Hwi_restore(key);
}

/*
 *  ======== Mpu_enable ========
 *  Function to enable the MPU.
 */
Void Mpu_enable()
{
    UInt16 type;
    UInt   key;

    /* if MPU is already enabled then just return */
    if (Mpu_isEnabled()) {
        return;
    }

    key = Hwi_disable();

    /* get the current enabled bits */
    type = Cache_getEnabled();

    if (type & Cache_Type_ALLP) {
        Cache_disable(Cache_Type_ALLP);
    }

    Mpu_enableAsm();

    /* set cache back to initial settings */
    Cache_enable(type);

    Hwi_restore(key);
}

/*
 *  ======== Mpu_initRegionAttrs ========
 */
Void Mpu_initRegionAttrs(Mpu_RegionAttrs *attrs)
{
    Assert_isTrue(attrs != NULL, Mpu_A_nullPointer);

    attrs->enable = Mpu_defaultAttrs.enable;
    attrs->bufferable = Mpu_defaultAttrs.bufferable;
    attrs->cacheable = Mpu_defaultAttrs.cacheable;
    attrs->shareable = Mpu_defaultAttrs.shareable;
    attrs->noExecute = Mpu_defaultAttrs.noExecute;
    attrs->accPerm = Mpu_defaultAttrs.accPerm;
    attrs->tex = Mpu_defaultAttrs.tex;
    attrs->subregionDisableMask = Mpu_defaultAttrs.subregionDisableMask;
}

/*
 *  ======== Mpu_setRegion ========
 */
Void setRegion(UInt8 regionId, Ptr regionBaseAddr,
    Mpu_RegionSize regionSize, Mpu_RegionAttrs *attrs)
{
    Bool   enabled;
    UInt32 baseAddressReg, sizeAndEnableReg, regionAttrsReg;
    // TODO Special handling when changing shareability attrs
    //      (see B5.3.3 of ARM ARM)

    Assert_isTrue(attrs != NULL, Mpu_A_nullPointer);
    Assert_isTrue(regionId < Mpu_numRegions, Mpu_A_invalidRegionId);

    enabled = Mpu_isEnabled();

    /* disable the MPU (if already disabled, does nothing) */
    Mpu_disable();

    /* Round down base address to a 4-byte aligned address */
    baseAddressReg = (UInt32)regionBaseAddr & 0xFFFFFFFC;

    sizeAndEnableReg = (attrs->subregionDisableMask << 8) | regionSize |
                       (attrs->enable);

    regionAttrsReg = (attrs->noExecute << 12) | (attrs->accPerm << 8) |
        (attrs->tex << 3) | (attrs->shareable << 2) | (attrs->cacheable << 1) |
        (attrs->bufferable);

    if (!Mpu_isMemoryMapped) {
        Mpu_setRegionAsm(regionId, baseAddressReg, sizeAndEnableReg,
            regionAttrsReg);
        /* Copy register values to module state for use by ROV */
        (Mpu_module->regionEntry[regionId]).baseAddress = baseAddressReg;
        (Mpu_module->regionEntry[regionId]).sizeAndEnable = sizeAndEnableReg;
        (Mpu_module->regionEntry[regionId]).regionAttrs = regionAttrsReg;
    }

    if (enabled) {
        Mpu_enable();
    }
}
