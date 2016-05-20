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
 *  \file vpscore_DctrlDefaults.c
 *
 *  \brief Default NodeInfo and EdgeInfo structure for DCTRL
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <common/stw_dataTypes.h>
#include <common/stw_types.h>
#include <common/bsp_types.h>
#include <dispcore/src/vpscore_dctrlPriv.h>
#include <common/vps_graph.h>

/* {nodeNum,                        inType,     outType,    nodeType,
 *            corePtr, 0, 0, {     input   },  {     input   }},  */
const Vgraph_nodeInfo dctrlNodeInfoDefaults[GRAPH_DCTRL_DSS_NUM_NODES] =
{ \
    {GRAPH_DCTRL_DSS_INVALID,      EMPTY_IN,  EMPTY_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                            {NULL},
                                        {0}},
                                        {0,                            {NULL},
                                        {0}}}, \
    {GRAPH_DCTRL_DSS_VID1,         SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_DSSVID, NULL, 0, 0,
                                        {0,                            {NULL},
                                        {0}},
                                        {0,                            {NULL},
                                        {0}}}, \
    {GRAPH_DCTRL_DSS_VID2,         SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_DSSVID, NULL, 0, 0,
                                        {0,                            {NULL},
                                        {0}},
                                        {0,                            {NULL},
                                        {0}}}, \
    {GRAPH_DCTRL_DSS_VID3,         SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_DSSVID, NULL, 0, 0,
                                        {0,                            {NULL},
                                        {0}},
                                        {0,                            {NULL},
                                        {0}}}, \
    {GRAPH_DCTRL_DSS_GFX,          SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_DSSVID, NULL, 0, 0,
                                        {0,                            {NULL},
                                        {0}},
                                        {0,                            {NULL},
                                        {0}}}, \
    {GRAPH_DCTRL_DSS_WB,           SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_DSSVID, NULL, 0, 0,
                                        {0,                            {NULL},
                                        {0}},
                                        {0,                            {NULL},
                                        {0}}}, \
    {GRAPH_DCTRL_DSS_LCD1_BLENDER, MULTI_IN,  SINGLE_OUT,
                                        VGRAPH_NODETYPE_DSSMGR, NULL, 0, 0,
                                        {0,                            {NULL},
                                        {0}},
                                        {0,                            {NULL},
                                        {0}}}, \
    {GRAPH_DCTRL_DSS_LCD2_BLENDER, MULTI_IN,  MULTI_OUT,
                                        VGRAPH_NODETYPE_DSSMGR, NULL, 0, 0,
                                        {0,                            {NULL},
                                        {0}},
                                        {0,                            {NULL},
                                        {0}}}, \
    {GRAPH_DCTRL_DSS_LCD3_BLENDER, MULTI_IN,  MULTI_OUT,
                                        VGRAPH_NODETYPE_DSSMGR, NULL, 0, 0,
                                        {0,                            {NULL},
                                        {0}},
                                        {0,                            {NULL},
                                        {0}}}, \
    {GRAPH_DCTRL_DSS_HDMI_BLENDER, MULTI_IN,  MULTI_OUT,
                                        VGRAPH_NODETYPE_DSSMGR, NULL, 0, 0,
                                        {0,                            {NULL},
                                        {0}},
                                        {0,                            {NULL},
                                        {0}}}, \
    {GRAPH_DCTRL_DSS_DPI1_OUTPUT,  SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_DSSOUT, NULL, 0, 0,
                                        {0,                            {NULL},
                                        {0}},
                                        {0,                            {NULL},
                                        {0}}}, \
    {GRAPH_DCTRL_DSS_DPI2_OUTPUT,  SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_DSSOUT, NULL, 0, 0,
                                        {0,                            {NULL},
                                        {0}},
                                        {0,                            {NULL},
                                        {0}}}, \
    {GRAPH_DCTRL_DSS_DPI3_OUTPUT,  SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_DSSOUT, NULL, 0, 0,
                                        {0,                            {NULL},
                                        {0}},
                                        {0,                            {NULL},
                                        {0}}}, \
    {GRAPH_DCTRL_DSS_HDMI_OUTPUT,  SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_DSSOUT, NULL, 0, 0,
                                        {0,                            {NULL},
                                        {0}},
                                        {0,                            {NULL},
                                        {0}}},
};

/***
 * Defining EdgeList:
 * Muxes: Arrange in terms of mux values, if any entry is invalid, mark as
 * GRAPH_DSS_INVALID
 ***/
const Vgraph_edgeInfo dctrlEdgeInfoDefaults[GRAPH_DCTRL_DSS_NUM_EDGES] =
{                                                                 \
    {GRAPH_DCTRL_DSS_VID1,         GRAPH_DCTRL_DSS_LCD1_BLENDER}, \
    {GRAPH_DCTRL_DSS_VID1,         GRAPH_DCTRL_DSS_LCD2_BLENDER}, \
    {GRAPH_DCTRL_DSS_VID1,         GRAPH_DCTRL_DSS_LCD3_BLENDER}, \
    {GRAPH_DCTRL_DSS_VID1,         GRAPH_DCTRL_DSS_HDMI_BLENDER}, \
    {GRAPH_DCTRL_DSS_VID1,         GRAPH_DCTRL_DSS_WB          }, \
                                                                  \
    {GRAPH_DCTRL_DSS_VID2,         GRAPH_DCTRL_DSS_LCD1_BLENDER}, \
    {GRAPH_DCTRL_DSS_VID2,         GRAPH_DCTRL_DSS_LCD2_BLENDER}, \
    {GRAPH_DCTRL_DSS_VID2,         GRAPH_DCTRL_DSS_LCD3_BLENDER}, \
    {GRAPH_DCTRL_DSS_VID2,         GRAPH_DCTRL_DSS_HDMI_BLENDER}, \
    {GRAPH_DCTRL_DSS_VID1,         GRAPH_DCTRL_DSS_WB          }, \
                                                                  \
    {GRAPH_DCTRL_DSS_VID3,         GRAPH_DCTRL_DSS_LCD1_BLENDER}, \
    {GRAPH_DCTRL_DSS_VID3,         GRAPH_DCTRL_DSS_LCD2_BLENDER}, \
    {GRAPH_DCTRL_DSS_VID3,         GRAPH_DCTRL_DSS_LCD3_BLENDER}, \
    {GRAPH_DCTRL_DSS_VID3,         GRAPH_DCTRL_DSS_HDMI_BLENDER}, \
    {GRAPH_DCTRL_DSS_VID3,         GRAPH_DCTRL_DSS_WB          }, \

    {GRAPH_DCTRL_DSS_GFX,          GRAPH_DCTRL_DSS_LCD1_BLENDER}, \
    {GRAPH_DCTRL_DSS_GFX,          GRAPH_DCTRL_DSS_LCD2_BLENDER}, \
    {GRAPH_DCTRL_DSS_GFX,          GRAPH_DCTRL_DSS_LCD3_BLENDER}, \
    {GRAPH_DCTRL_DSS_GFX,          GRAPH_DCTRL_DSS_HDMI_BLENDER}, \
    {GRAPH_DCTRL_DSS_GFX,          GRAPH_DCTRL_DSS_WB          }, \
                                                                  \
    {GRAPH_DCTRL_DSS_LCD1_BLENDER, GRAPH_DCTRL_DSS_WB          }, \
    {GRAPH_DCTRL_DSS_LCD1_BLENDER, GRAPH_DCTRL_DSS_DPI1_OUTPUT }, \


    {GRAPH_DCTRL_DSS_LCD2_BLENDER, GRAPH_DCTRL_DSS_WB          }, \
    {GRAPH_DCTRL_DSS_LCD2_BLENDER, GRAPH_DCTRL_DSS_DPI1_OUTPUT }, \
    {GRAPH_DCTRL_DSS_LCD2_BLENDER, GRAPH_DCTRL_DSS_DPI2_OUTPUT }, \


    {GRAPH_DCTRL_DSS_LCD3_BLENDER, GRAPH_DCTRL_DSS_WB          }, \
    {GRAPH_DCTRL_DSS_LCD3_BLENDER, GRAPH_DCTRL_DSS_DPI1_OUTPUT }, \
    {GRAPH_DCTRL_DSS_LCD3_BLENDER, GRAPH_DCTRL_DSS_DPI3_OUTPUT }, \

    {GRAPH_DCTRL_DSS_HDMI_BLENDER, GRAPH_DCTRL_DSS_WB          }, \
    {GRAPH_DCTRL_DSS_HDMI_BLENDER, GRAPH_DCTRL_DSS_DPI1_OUTPUT }, \
    {GRAPH_DCTRL_DSS_HDMI_BLENDER, GRAPH_DCTRL_DSS_HDMI_OUTPUT }, \

};

