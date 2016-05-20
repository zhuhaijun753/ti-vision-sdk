/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2014
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 *  \file       pmhal_clocktree.h
 *
 *  \brief      This file contains Acyclic Graph Abstract Data Type,
 *              it has the graph node API for tree traversal
 */

#ifndef PMHAL_CLOCKTREE_H_
#define PMHAL_CLOCKTREE_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "stdint.h"
#include <limits.h>
#include "pmhal_prcm.h"
#include "pm_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 * \brief Clock-tree node types
 */
typedef enum pmhalNodeType
{
    PMHAL_MOD = 0U,
    PMHAL_MIN = PMHAL_MOD,
    /**< Lower bound (inclusive) */
    PMHAL_DPLL = 1U,
    /**< Node Type for DPLL */
    PMHAL_MUX = 2U,
    /**< Node Type for Multiplexer */
    PMHAL_DIV = 3U,
    /**< Node Type for Divider */
    PMHAL_ROOT_CLK = 4U,
    /**< Node Type for Root Clocks */
    PMHAL_MAX = PMHAL_ROOT_CLK,
    /**< Enum Upper bound */
    PMHAL_COUNT = PMHAL_MAX + 1U,
    /**< Enum Count */
    PMHAL_UNDEF = -1
                  /**< Undefined value */
} pmhalNodeType_t;

/**
 * \brief  Graph Node-ID type
 */
typedef uint32_t pmhalClockTreeNodeId;

/**
 * \brief  Graph Node-ID type
 */
typedef pmhalClockTreeNodeId *pmhalClockTreeNodeIdVec;

/**
 * \brief  Graph Node-ID const vector type
 */
typedef const pmhalClockTreeNodeId *pmhalClockTreeNodeIdCvec;

/**
 * \brief  Graph Node Vertex type
 */
typedef uint32_t pmhalClockTreePropType;

/**
 * \brief  Graph Node Vertex type
 */
typedef uint32_t pmhalClockTreeProperty;

/**
 * \brief  Graph Node Property type
 */
typedef uint8_t clockTreeVertex;

/**
 * \brief  Graph size type
 */
typedef uint16_t pmhalClockTreeSize_t;

/**
 * \brief   Graph container to hold arbitary data-type
 */
typedef struct
{
    pmhalClockTreePropType ptype;
    /**< Property type used to interpret pvalue*/
    const void            *pvalue;
    /**< Property value*/
} pmhalClockTreeProp, *pmhalClockTreePropPtr;
typedef const pmhalClockTreeProp *pmhalClockTreePropCptr;

/**
 * \brief   Graph container to hold arbitary data-type
 */
typedef struct
{
    pmhalClockTreePropType ptype;
    /**< Property type used to interpret pvalue*/
    const void            *pvalue;
    /**< Property value*/
    clockTreeVertex        vType;
    /**< Vertex of value*/
} pmhalClockTreeEdgeProp, *pmhalClockTreeEdgePropPtr;
typedef const pmhalClockTreeEdgeProp *pmhalClockTreeEdgePropCptr;

/**
 * \brief   Edge stuct that encapsulates a property
 */
typedef struct
{
    pmhalClockTreeProperty     toProp;
    /**< Property of the connected node*/
    pmhalClockTreeEdgePropCptr prop;
    /**< Edge property specific to this edge*/
} pmhalClockTreeEdge, *pmhalClockTreeEdgePtr;
typedef const pmhalClockTreeEdge *pmhalClockTreeEdgeCptr;
typedef const pmhalClockTreeEdge *pmhalClockTreeEdgeCvec;

/**
 *  \brief   List of edges originating from a node
 */
typedef struct
{
    pmhalClockTreeNodeId   from;
    /**< Source of edge*/
    pmhalClockTreeEdgeCvec toNodes;
    /**< Target(s) of edge*/
    pmhalClockTreeSize_t   toNodesMax;
    /**< Number of elements in toNodes vector*/
} pmhalClockTreeEdges, *pmhalClockTreeEdgesPtr;
typedef const pmhalClockTreeEdges *pmhalClockTreeEdgesCvec;

/**
 *  \brief  Graph node optimized for PM
 */
typedef struct
{
    pmhalClockTreePropCptr   prop;
    /**< Node Property*/
    pmhalClockTreeNodeIdCvec edgeIn;
    /**< List of edges incident on this node (Parent node-ids)*/
    pmhalClockTreeSize_t     edgeInMax;
    /**< Number of edges incident on this node*/
} pmhalClockTreeNode, *pmhalClockTree_node_ptr;
typedef const pmhalClockTreeNode *pmhalClockTreeNodeCptr;
typedef const pmhalClockTreeNode *pmhalClockTreeNodeCvec;

/**
 *  \brief  Graph data structure
 */
typedef struct
{
    pmhalClockTreeSize_t    nodesMax;
    /**< Max number of edges incident on this node*/
    pmhalClockTreeNodeCvec  nodes;
    pmhalClockTreeSize_t    edgesMax;
    /**< Max number of edges incident on this node*/
    pmhalClockTreeEdgesCvec edges;
    /**< Number of edges incident on this node*/
} pmhalClockTree, *pmhalClockTreePtr;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   Is the given node-id valid?
 *
 * \param   pmhalClockTreeNodeId      graph node Id
 *
 * \return  errorStatus     Status of API call. Can be any of the following,
 *          PM_SUCCESS      Indicates the operation is success
 *          PM_FAIL         Indicates the nodeId is not valid
 */
pmErrCode_t PMHALClockTreeValidNode(pmhalClockTreeNodeId id);

/**
 * \brief   gives the type of the given node
 *
 * \param   pmhalClockTreeNodeId      graph node Id
 *
 * \return  nodeType     Refer #pmhalNodeType_t name for details
 *
 */
pmhalNodeType_t PMHALClockTreeGetNodeType(pmhalClockTreeNodeId id);

/**
 * \brief  Get the node_ptr corresponding to the node_id
 *
 * \param  pmhalClockTreeNodeId         graph node Id
 * \param  pmhalClockTreeNodeCptr       nodePointer
 *
 * \return errorStatus     Status of API call. Can be any of the following,
 *          PM_SUCCESS      Indicates the operation is success
 *          PM_FAIL         Indicates node is not found
 */
pmErrCode_t PMHALClockTreeGetNode(pmhalClockTreeNodeId    id,
                                  pmhalClockTreeNodeCptr *nodePtr);

/**
 * \brief  Get the property corresponding to the node_id
 *
 * \param  pmhalClockTreeNodeCptr  node_ptr corresponding to the node_id
 * \param  pmhalClockTreePropCptr  propPtr corresponding to nodePointer
 *
 * \return errorStatus     Status of API call. Can be any of the following,
 *          PM_SUCCESS      Indicates the operation is success
 *          PM_FAIL         Indicates node is not found or property is undefined
 */
pmErrCode_t PMHALClockTreeGetNodeProp(pmhalClockTreeNodeCptr  np,
                                      pmhalClockTreePropCptr *propPtr);

/**
 * \brief     Get the the list of predecessor nodes
 *
 * \param  pmhalClockTreeNodeId      graph node Id
 * \param  pmhalClockTreeNodeIdCvec  Graph Node-ID const vector type
 * \param  pmhalClockTreeSize_t           no of innodes to the given node
 *
 * \return errorStatus     Status of API call. Can be any of the following,
 *          PM_SUCCESS     Indicates the operation is success
 *          PM_FAIL        Indicates the nodeId is not valid
 */
pmErrCode_t PMHALClockTreeGetPredecessors(pmhalClockTreeNodeId      id,
                                          pmhalClockTreeNodeIdCvec *pred,
                                          pmhalClockTreeSize_t     *npred);

/**
 * \brief   Get the edge_ptr associated with a clock for a Module.
 *
 * \param   sourceNode      module for which edge property is valid.
 * \param   property        edge property that we are interested
 * \param   edgePtr         pointer that defines the edge attributes
 *
 * \return  errorStatus     Status of API call. Can be any of the following,
 *          PM_SUCCESS      Indicates the operation is success
 *          PM_FAIL         Indicates edge is undefined for the source Node
 *                          or the related Node is not connected
 */
pmErrCode_t PMHALClockTreeGetModuleEdge(pmhalClockTreeNodeId    sourceNode,
                                        pmhalClockTreeProperty  property,
                                        pmhalClockTreeEdgeCptr *edgePtr);

/**
 * \brief   Get the edge_ptr connecting Dpll and a Node.
 *
 * \param   sourceNode      module for which edge property is valid.
 * \param   toNode          node that is connected to source node
 * \param   property        edge property that we are interested
 * \param   edgePtr         pointer that defines the edge attributes
 *
 * \return  errorStatus     Status of API call. Can be any of the following,
 *          PM_SUCCESS      Indicates the operation is success
 *          PM_FAIL         Indicates edge is undefined for the source
 *                          Node or the related Node is not connected
 */
pmErrCode_t PMHALClockTreeGetDpllEdge(pmhalClockTreeNodeId    sourceNode,
                                      pmhalClockTreeNodeId    toNode,
                                      pmhalClockTreeProperty  property,
                                      pmhalClockTreeEdgeCptr *edgePtr);

/**
 * \brief  Get the property corresponding to the edge
 *
 * \param  pmhalClockTreeEdgeCptr      graph edge const pointer
 * \param  pmhalClockTreeEdgePropCptr  edge property pointer
 *
 * \return errorStatus     Status of API call. Can be any of the following,
 *          PM_SUCCESS      Indicates the operation is success
 *          PM_FAIL         Indicates edge is not found or property is undefined
 */
pmErrCode_t PMHALClockTreeGetEdgeProp(pmhalClockTreeEdgeCptr      ep,
                                      pmhalClockTreeEdgePropCptr *edgePropPtr);

/**
 * \brief   Get the edge_ptr associated with a clock for a dpll.
 *
 * \param   sourceNode      dpll for which edge property is valid.
 * \param   property        edge property that we are interested
 * \param   edgePtr         pointer that defines the edge attributes
 *
 * \return  errorStatus     Status of API call. Can be any of the following,
 *          PM_SUCCESS      Indicates the operation is success
 *          PM_FAIL         Indicates edge is undefined for the source Node
 *                          or the related Node is not connected
 */
pmErrCode_t PMHALClockTreeGetDpllInEdge(pmhalClockTreeNodeId    sourceNode,
                                        pmhalClockTreeProperty  property,
                                        pmhalClockTreeEdgeCptr *edgePtr);

#ifdef __cplusplus
}
#endif

#endif /* PMHAL_CLOCKTREE_H_ */

