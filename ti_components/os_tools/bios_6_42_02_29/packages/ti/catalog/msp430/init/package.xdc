/*
 *  Copyright (c) 2015 by Texas Instruments and others.
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 *
 *  Contributors:
 *      Texas Instruments - initial implementation
 *
 * */

requires xdc.runtime;

/*!
 *  ======== ti.catalog.msp430.init ========
 *  MSP430 boot time initialization support
 *
 *  This package contains a `{@link Boot}` module that supplies minimal
 *  boot time initialization code.  This code optionally disables the
 *  watchdog timer (to ensure normal C initialization can complete before
 *  the watchdog resets the device) and configures the CPU clock.
 */
package ti.catalog.msp430.init[1,0,0] {
    module Boot;
}
/*
 *  @(#) ti.catalog.msp430.init; 1, 0, 0,; 8-14-2015 13:38:36; /db/ztree/library/trees/platform/platform-q07/src/
 */

