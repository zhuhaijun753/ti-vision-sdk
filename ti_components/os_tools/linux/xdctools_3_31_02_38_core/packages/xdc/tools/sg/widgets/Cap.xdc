/* 
 *Copyright (c) 2008 Texas Instruments and others.
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 * 
 *  Contributors:
 *      Texas Instruments - initial implementation
 *
 * */
metaonly interface Cap inherits Widget {
instance:
    create(Any parent, String capsuleName, Any params);
    void setCapsule(String capsuleName);
    readonly config Any capsule;
};
/*
 *  @(#) xdc.tools.sg.widgets; 1,0,0,269; 5-30-2015 10:02:16; /db/ztree/library/trees/xdctools/xdctools-f62x/src/
 */
