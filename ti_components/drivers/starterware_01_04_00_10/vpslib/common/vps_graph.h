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
#ifndef VPS_GRAPH_H_
#define VPS_GRAPH_H_

#include <common/bsp_types.h>

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

#define VGRAPH_DEF_ALIGN       ((UInt32) 16U)
#define GRAPH_INVALID_NODE_ID  ((UInt32) 0U)
#define GRAPH_MAX_NODES        ((UInt32) 80U)
#define GRAPH_MAX_NUM_PATHS    ((UInt32) 20U)

typedef enum
{
    VGRAPH_NODE_DISABLE = 0,
    VGRAPH_NODE_ENABLE  = 1,
    VGRAPH_NODE_CHECK   = 2
} Vgraph_mode;

typedef enum
{
    VGRAPH_NODETYPE_DUMMY,
    VGRAPH_NODETYPE_VPDMA,   /* VPDMA channels */
    VGRAPH_NODETYPE_VIPPORT, /* VIP Inputs */
    VGRAPH_NODETYPE_VIPMUX,  /* VIP Muxes */
    VGRAPH_NODETYPE_SC,      /* VIP Muxes */
    VGRAPH_NODETYPE_CSC,     /* VIP Muxes */
    VGRAPH_NODETYPE_DSSVID,  /* DSS Pipelines */
    VGRAPH_NODETYPE_DSSMGR,  /* DSS overlay manager */
    VGRAPH_NODETYPE_DSSOUT,  /* DSS output */
    VGRAPH_NODETYPE_MAX_NODETYPE
} Vgraph_NodeTypes;

typedef struct Vgraph_nodeInfo_t Vgraph_nodeInfo;
typedef struct Vgraph_nodeSet_t
{
    UInt32           numNodes;
    /**< Number of input/output nodes */
    Vgraph_nodeInfo *node[GRAPH_MAX_NUM_PATHS];
    /**< Pointer to the input/output node */
    UInt32           isEnabled[GRAPH_MAX_NUM_PATHS];
    /**< Flag to indicate whether input/output is enabled or not. */
} Vgraph_nodeSet;

typedef enum
{
    SINGLE_IN,
    MULTI_IN,
    EMPTY_IN
} Vgraph_NodeInputType;

typedef enum
{
    SINGLE_OUT,
    MULTI_OUT,
    EMPTY_OUT
} Vgraph_NodeOutputType;

struct Vgraph_nodeInfo_t
{
    /* Will be used to select config structure from the handleCreateParams */
    UInt32                nodeNum;

    /* Tree-connections */
    Vgraph_NodeInputType  inType;
    Vgraph_NodeOutputType outType;

    /* SI/SO/MI/MO */
    UInt32                nodeType;

    /* For multiple handles */
    /* UInt32          isMH; */
    /* UInt32          openCount; */

    /* List of HAL functions required while configuring */
    /* FuncPtrList*    halPtr; */
    void                 *corePtr;

    UInt32                isDummy;
    UInt32                inUse;

    /* Need to check how to track state when in multi-handle mode */
    /* void*           fnPtr_isAvailable;  */
    /* required when sharing an IP across two handles */
    /* void*           fnPtr_isRunning;    */
    /* required when sharing an IP across two handles */
    /* and using different list for different handles */
    Vgraph_nodeSet        input;
    Vgraph_nodeSet        output;

    /* TODO: Need to check how to track state when in multi-handle mode */
};

typedef struct
{
    UInt32           numNodes;
    Vgraph_nodeInfo *list;
} Vgraph_nodeInfoList;

/**
 * \brief Structure containing edge information. Edge is a connection
 *  between two nodes i.e. two modules (like CIG and Blend) in VPS.
 *  VPS can be represented by a graph, where each
 *  module is node and edge is present between two nodes if they are connected.
 *  All VPS paths can be configured in one shot by IOCTL
 *  IOCTL_VPSCORE_DCTRL_SET_CONFIG.
 *  This IOCTL takes the array of edges connected between nodes. This structure
 *  is used to specify individual edge information.
 */
typedef struct
{
    UInt32 startNode;
    /**< Starting node (VPS Module) of the edge */
    UInt32 endNode;
    /**< End node (VPS Module) of the edge */
} Vgraph_edgeInfo;

typedef struct
{
    UInt32           numEdges;
    /**< End node (VPS Module) of the edge */

    Vgraph_edgeInfo *list;
    /**< Starting node (VPS Module) of the edge */
} Vgraph_edgeInfoList;

typedef struct
{
    Vgraph_nodeInfoList *nodeList;
    Vgraph_edgeInfoList *edgeList;
} Vgraph_Info;

Vgraph_Info *Vgraph_Init(const Vgraph_nodeInfoList *inNodeList,
                         const Vgraph_edgeInfoList *inEdgeList,
                         Vgraph_Info               *graphHandle);

Int32 Vgraph_DeInit(Vgraph_Info *graphHandle);

Vgraph_nodeInfo *Vgraph_getNodeInfo(const Vgraph_nodeInfoList *nodeList,
                                    UInt32                     cnt);

Int32 Vgraph_allocNodes(const Vgraph_nodeInfoList *nodeList,
                        const Vgraph_edgeInfoList *edgeList,
                        Vgraph_mode                mode);

Int32 Vgraph_getPath(const Vgraph_nodeInfoList *inNodeList,
                     const Vgraph_edgeInfoList *inEdgeList,
                     Vgraph_nodeInfoList       *outNodeList,
                     Vgraph_edgeInfoList       *outEdgeList,
                     UInt32                     maxOutNodeCnt,
                     UInt32                     maxOutEdgeCnt);

Int32 Vgraph_freePath(Vgraph_nodeInfoList *nodeList,
                      Vgraph_edgeInfoList *edgeList);

static Void Vgraph_stackReset(void);

static Void Vgraph_stackPush(Vgraph_nodeInfo *node);

static Void Vgraph_stackPop(void);

static UInt32 Vgraph_stackIsVisited(const Vgraph_nodeInfo *node);

Int32 Vgraph_stackIsLastNode(const Vgraph_nodeInfo *currNode, UInt32 isForward);

Void Vgraph_stackInitTraverser(Vgraph_nodeInfo *node);

Vgraph_nodeInfo *Vgraph_getNextNodeToTraverse(UInt32 isForward);

Bool Vgraph_isNodeInputAvailable(const Vgraph_nodeInfoList *nodeList,
                                 UInt32                     nodeNum);

Bool Vgraph_isNodeOutputAvailable(const Vgraph_nodeInfoList *nodeList,
                                  UInt32                     nodeNum);

Void Vgraph_initTraverser(Vgraph_nodeInfo *node);

Vgraph_nodeInfo *Vgraph_getNextChildNode(const Vgraph_nodeInfo *currNode,
                                         UInt32                 isForward);

Vgraph_nodeInfo *Vgraph_stackPeak(UInt32 *stNum);

Int32 Vgraph_getEnabledIndex(const UInt32 *array, UInt32 size);

Void Vgraph_AddEdge(Vgraph_edgeInfo *edge, UInt32 startNode, UInt32 endNode);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif /* VPS_GRAPH_H_ */

