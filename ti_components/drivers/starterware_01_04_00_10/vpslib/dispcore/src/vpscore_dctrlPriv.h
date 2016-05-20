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
 *  \file vpscore_dssPriv.h
 *
 *  \brief Header file for DSS display core
 *  This file includes data-structures and function declarations for the
 *  the VPS display core interface for DSS.
 *
 */

#ifndef DCTRLLIB_PRIV_H_
#define DCTRLLIB_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <common/stw_config.h>
#include <common/bsp_utils.h>

#include <dispcore/vpscore_dctrl.h>
#include <common/vps_graph.h>
#include <vps/vps_displayCtrlDataTypes.h>
#include <dispcore/src/vpscore_dctrlIntr.h>

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

#define VPSCORE_DSS_DEF_ALIGN      ((uint32_t) 32U)
#define GRAPH_DCTRL_DSS_NUM_EDGES  ((uint32_t) 31U)

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

typedef enum
{
    VPS_DCTRL_PIPE_IDLE,
    /**< When Graph is created*/
    VPS_DCTRL_PIPE_OPENED,
    /**< When DSS core opens the pipe */
    VPS_DCTRL_PIPE_RUNNING
    /**< When DSS core starts pipe, DCTRL  need to send interrupts then*/
} VpsCore_DctrlPipeState;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/**
 *  struct VpsCore_DssObj
 *  \brief DSS Core Handle structure. This will be instantiated for each
 *  instance of DSS. (Currently there is only one instance of DSS)
 */

typedef struct
{
    UInt32              dispcIrqNumber;

    VpsHal_Handle       ovlHandle[VPSHAL_DSS_DISPC_OVLY_MAX_INST];

    void               *graph;
    Vgraph_Info         graphObj;
    Vgraph_nodeInfoList graphObjNodeList;
    Vgraph_edgeInfoList graphObjEdgeList;

    Vgraph_nodeInfoList dctrlNodeList;
    Vgraph_edgeInfoList dctrlEdgeList;
    Vgraph_nodeInfo     dctrlNodeObj[GRAPH_DCTRL_DSS_NUM_NODES];
    Vgraph_edgeInfo     dctrlEdgeObj[GRAPH_DCTRL_DSS_NUM_EDGES];

    Vgraph_nodeInfo     allDctrlNodes[GRAPH_DCTRL_DSS_NUM_NODES];
    Vgraph_edgeInfo     allEdgeInfo[GRAPH_DCTRL_DSS_NUM_EDGES];
} VpsCore_DctrlObj;

typedef struct
{
    UInt32                  pipeNodeNum;
    /**<Information of the pipe connected. */
    VpsCore_DctrlPipeState  state;
    /** <Dss core has opened the node. handle given. */
    UInt32                  ovlNodeNum;
    /**<Information of the Overlay connected. */
    UInt32                  VencNodeNum;
    /**<Information of the Display connected. */
    UInt32                  vencId;
    /**<ID of the display. */
    Int32                   shiftVidPosX;
    /**<Vid position in overlay to be shifted in Number of pixels. */
    Vpscore_dctrlClientInfo gClientInfo;
    /**< DSS core call back function */
} VpsCore_DctrlPipe;

typedef struct
{
    UInt32 gfxBufferUnderflow;
    /**<Graphics pipeline Buffer underflow count. */
    UInt32 wbBufferOverflow;
    /**<Wb pipeline Buffer overflow count. */
    UInt32 wbIncompleteError;
    /**<WB pipeline Incomplete Error count. */
    UInt32 vid1BufferUnderflow;
    /**<VID1 pipeline Buffer underflow count. */
    UInt32 vid2BufferUnderflow;
    /**<VID2 pipeline Buffer underflow count. */
    UInt32 vid3BufferUnderflow;
    /**<VID3 pipeline Buffer underflow count. */
    UInt32 syncLost1;
    /**<SyncLost Error Count for LCD1 Overlay. */
    UInt32 syncLost2;
    /**<SyncLost Error Count for LCD2 Overlay. */
    UInt32 syncLost3;
    /**<SyncLost Error Count for LCD3 Overlay. */
    UInt32 syncLostTV;
    /**<SyncLost Error Count for TV Overlay. */
    UInt32 ocpError;
    /**< Ocp Error Count. */
}VpsCore_DctrlErrorCount;

typedef struct
{
    UInt32 wbSyncRbEndWinTog;
    /**<Number of times wbSync and rbEndWindow interrupts occured together. */
    UInt32 wbSyncIrq;
    /**<Number of times wbSync interrupt occured. */
    UInt32 wbSyncOnlyNormal;
    /**<Number of times wbSync interrupt occured
     *  when regionbased bit is set previously. */
    UInt32 wbSyncOnlyFrameSkip;
    /**<Number of times wbSync interrupt occured
     *  when regionbased bit is not set previously.*/
    UInt32 rbEndWinOnly;
    /**<Number of times rb end window interrupt occured. */
} VpsCore_DctrlWbDebugInfo;

typedef struct
{
    UInt32                   numPipes;
    /**<Number of valid pipes in this struct. */
    VpsCore_DctrlPipe        VidInfo[VPSHAL_DSS_DISPC_PIPE_MAX_INST];
    /**<Information about the connected pipe. */
    UInt32                   numVencs;
    /**<Number of valid Vencs in this struct. */
    Vpscore_dctrlPathInfo    pathInfo[VPSHAL_DSS_DISPC_OVLY_MAX_INST];
    /**<Information about the LCD timing */
    UInt32                   isPushSafe[VPSHAL_DSS_DISPC_OVLY_MAX_INST];
    /**<Flag to indicate if buf push is safe - low latency display */
    UInt32                   dvoFmt[VPSHAL_DSS_DISPC_OVLY_MAX_INST];
    /**<Variable to Store the output format, vaild values #Vps_DctrlDigitalFmt.
    **/
    VpsCore_DctrlErrorCount  errorCnt;
    /**< all error stats are stored here. */
    VpsCore_DctrlWbDebugInfo wbDebugInfo;
    /**< Debug info for write back irq count. */
} VpsCore_DctrlInfo;

typedef struct
{
    UInt32 isStarted;
} VpsCore_DctrlPathObj;

extern const Vgraph_nodeInfo dctrlNodeInfoDefaults[GRAPH_DCTRL_DSS_NUM_NODES];
extern const Vgraph_edgeInfo dctrlEdgeInfoDefaults[GRAPH_DCTRL_DSS_NUM_EDGES];

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/*TODO - Add description*/
Int32 VpsCore_dctrlGetProperty(VpsCore_Inst      instObj,
                               VpsCore_Property *property);

VpsCore_Handle VpsCore_dctrlOpen(VpsCore_Inst            pDssHandle,
                                 const VpsCore_OpenPrms *openPrms,
                                 const void             *coreOpenPrms,
                                 void                   *coreReturnPrms);

Int32 VpsCore_dctrlControl(VpsCore_Handle handle,
                           UInt32         cmd,
                           Ptr            appArgs,
                           Ptr            drvArgs);
Int32 VpsCore_dctrlClose(VpsCore_Handle pathHandle);

VpsCore_Inst VpsCore_DctrlInit(VpsCore_DctrlObj *pNewObj);

Int32 VpsCore_DctrlDeInit(VpsCore_Inst pDssHandle);

Int32 VpsCore_dctrlCreateEdgeList(VpsCore_DctrlObj *pathObj,
                                  Vps_DctrlConfig  *pathCfg);

Void VpsCore_dctrlFreeEdgeList(VpsCore_DctrlObj *pathObj);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif
#endif /*DCTRLLIB_PRIV_H_*/
