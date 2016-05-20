/* 
 *  Copyright (c) 2015 Texas Instruments and others.
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 *
 *  Contributors:
 *      Texas Instruments - initial implementation
 *
 * */

/*!
 *  ======== IR5.xdc ========
 *  Cortex R5 little endian target
 */
metaonly interface IR5 inherits ti.targets.arm.elf.IArm {
    override readonly config string isa         = "v7R";

    override config string platform   = "ti.platforms.tms570xx";

    override readonly config xdc.bld.ITarget2.Command lnk = {
        cmd:  "armlnk",
        opts: "--abi=eabi -mv7R5 --strict_compatibility=on"
    };
}
/*
 *  @(#) ti.targets.arm.elf; 1, 0, 0,0; 7-10-2015 12:06:13; /db/ztree/library/trees/xdctargets/xdctargets-j04/src/ xlibrary

 */

