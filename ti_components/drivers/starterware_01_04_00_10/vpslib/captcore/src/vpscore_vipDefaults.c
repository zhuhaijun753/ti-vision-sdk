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
 *  \file vpscore_vipDefaults.c
 *
 *  \brief Default NodeInfo and EdgeInfo structure for VIP
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <common/stw_dataTypes.h>
#include <common/stw_types.h>
#include <common/vps_graph.h>
#include <captcore/vpscore_vip.h>
#include <captcore/src/vpscore_vipPriv.h>

/* {nodeNum,                        inType,     outType,    nodeType,
 *            corePtr, 0, 0, {     input   },  {     input   }},  */
const Vgraph_nodeInfo vipNodeInfoDefaults[GRAPH_VIP_NUM_NODES] =
{ \
    {GRAPH_VIP_INVALID,               EMPTY_IN,  EMPTY_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_PARSER_PORTA,       EMPTY_IN,  MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPPORT, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_PARSER_PORTB,       EMPTY_IN,  MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPPORT, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_PARSER_PORTA_INTF,  SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_PARSER_PORTB_INTF,  SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_PARSER_PORTA_08,    SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_PARSER_PORTA_16,    SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_PARSER_PORTA_24,    SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_PARSER_PORTB_08,    SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_PARSER_PORTA_08_16, SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_SEC0,               SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPPORT, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_COMP0,              SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPPORT, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_CSC_SRC,            SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_SC_SRC,             SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_CSC,                SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_CSC, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_SC,                 SINGLE_IN, MULTI_OUT, VGRAPH_NODETYPE_SC,
                                        NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_CHRDS0_ON,          SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_CHRDS1_ON,          SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_CHRDS0_OFF,         SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_CHRDS1_OFF,         SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_CHRDS0,             SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_CHRDS1,             SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_RGB_HI,             SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_Y_UP,               SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_UV_UP,              SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_Y_LO,               SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_UV_LO,              SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_PARSER_PORTA_ANC,   EMPTY_IN,  MULTI_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_PARSER_PORTB_ANC,   EMPTY_IN,  MULTI_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_PORTA_LUMA,         SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_PORTA_CHROMA,       SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_PORTB_LUMA,         SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_PORTB_CHROMA,       SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_PORTA_RGB,          MULTI_IN,  SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_PORTB_RGB,          MULTI_IN,  SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_MULT_ACTA_SRC0,     SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_MULT_ACTB_SRC0,     SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_MULT_ANCA_SRC0,     SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_MULT_ANCB_SRC0,     SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
                                               \
                                               \
    {GRAPH_VIP_S1_PARSER_PORTA,       EMPTY_IN,  MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPPORT, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_PARSER_PORTB,       EMPTY_IN,  MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPPORT, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_PARSER_PORTA_INTF,  SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_PARSER_PORTB_INTF,  SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_PARSER_PORTA_08,    SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_PARSER_PORTA_16,    SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_PARSER_PORTA_24,    SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_PARSER_PORTB_08,    SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_PARSER_PORTA_08_16, SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_SEC0,               SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPPORT, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_COMP0,              SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPPORT, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_CSC_SRC,            SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_SC_SRC,             SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_CSC,                SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_CSC, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_SC,                 SINGLE_IN, MULTI_OUT, VGRAPH_NODETYPE_SC,
                                        NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_CHRDS0_ON,          SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_CHRDS1_ON,          SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_CHRDS0_OFF,         SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_CHRDS1_OFF,         SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_CHRDS0,             SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_CHRDS1,             SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_RGB_HI,             SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_Y_UP,               SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_UV_UP,              SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_Y_LO,               SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_UV_LO,              SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_PARSER_PORTA_ANC,   EMPTY_IN,  MULTI_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_PARSER_PORTB_ANC,   EMPTY_IN,  MULTI_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_PORTA_LUMA,         SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_PORTA_CHROMA,       SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_PORTB_LUMA,         SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_PORTB_CHROMA,       SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_PORTA_RGB,          MULTI_IN,  SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_PORTB_RGB,          MULTI_IN,  SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_MULT_ACTA_SRC0,     SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_MULT_ACTB_SRC0,     SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_MULT_ANCA_SRC0,     SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_MULT_ANCB_SRC0,     SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
};

/***
 * Defining EdgeList:
 * Muxes: Arrange in terms of mux values, if any entry is invalid, mark as
 * GRAPH_VIP_INVALID
 ***/
const Vgraph_edgeInfo vipEdgeInfoDefaults[GRAPH_VIP_NUM_EDGES] =
{                                                                       \
    {GRAPH_VIP_S0_PARSER_PORTA,       GRAPH_VIP_S0_PARSER_PORTA_ANC  }, \
    {GRAPH_VIP_S0_PARSER_PORTA,       GRAPH_VIP_S0_PARSER_PORTA_INTF }, \
                                                                        \
    {GRAPH_VIP_S0_PARSER_PORTB,       GRAPH_VIP_S0_PARSER_PORTB_ANC  }, \
    {GRAPH_VIP_S0_PARSER_PORTB,       GRAPH_VIP_S0_PARSER_PORTB_INTF }, \
                                                                        \
    {GRAPH_VIP_S0_PARSER_PORTA_INTF,  GRAPH_VIP_S0_PARSER_PORTA_08   }, \
    {GRAPH_VIP_S0_PARSER_PORTA_INTF,  GRAPH_VIP_S0_PARSER_PORTA_16   }, \
    {GRAPH_VIP_S0_PARSER_PORTA_INTF,  GRAPH_VIP_S0_PARSER_PORTA_24   }, \
    {GRAPH_VIP_S0_PARSER_PORTB_INTF,  GRAPH_VIP_S0_PARSER_PORTB_08   }, \
                                                                        \
    {GRAPH_VIP_S0_PARSER_PORTA_08,    GRAPH_VIP_S0_PARSER_PORTA_08_16}, \
    {GRAPH_VIP_S0_PARSER_PORTA_16,    GRAPH_VIP_S0_PARSER_PORTA_08_16}, \
                                                                        \
    {GRAPH_VIP_INVALID,               GRAPH_VIP_S0_CSC_SRC           }, \
    {GRAPH_VIP_S0_PARSER_PORTA_08_16, GRAPH_VIP_S0_CSC_SRC           }, \
    {GRAPH_VIP_S0_PARSER_PORTB_08,    GRAPH_VIP_S0_CSC_SRC           }, \
    {GRAPH_VIP_S0_SEC0,               GRAPH_VIP_S0_CSC_SRC           }, \
    {GRAPH_VIP_S0_PARSER_PORTA_24,    GRAPH_VIP_S0_CSC_SRC           }, \
    {GRAPH_VIP_S0_COMP0,              GRAPH_VIP_S0_CSC_SRC           }, \
                                                                        \
    {GRAPH_VIP_INVALID,               GRAPH_VIP_S0_SC_SRC            }, \
    {GRAPH_VIP_S0_CSC,                GRAPH_VIP_S0_SC_SRC            }, \
    {GRAPH_VIP_S0_PARSER_PORTA_08_16, GRAPH_VIP_S0_SC_SRC            }, \
    {GRAPH_VIP_S0_PARSER_PORTB_08,    GRAPH_VIP_S0_SC_SRC            }, \
    {GRAPH_VIP_S0_SEC0,               GRAPH_VIP_S0_SC_SRC            }, \
                                                                        \
    {GRAPH_VIP_S0_CSC_SRC,            GRAPH_VIP_S0_CSC               }, \
    {GRAPH_VIP_S0_SC_SRC,             GRAPH_VIP_S0_SC                }, \
                                                                        \
    {GRAPH_VIP_INVALID,               GRAPH_VIP_S0_CHRDS0_ON         }, \
    {GRAPH_VIP_S0_SC,                 GRAPH_VIP_S0_CHRDS0_ON         }, \
    {GRAPH_VIP_S0_CSC,                GRAPH_VIP_S0_CHRDS0_ON         }, \
    {GRAPH_VIP_S0_PARSER_PORTA_08_16, GRAPH_VIP_S0_CHRDS0_ON         }, \
    {GRAPH_VIP_S0_PARSER_PORTB_08,    GRAPH_VIP_S0_CHRDS0_ON         }, \
    {GRAPH_VIP_S0_SEC0,               GRAPH_VIP_S0_CHRDS0_ON         }, \
                                                                        \
    {GRAPH_VIP_INVALID,               GRAPH_VIP_S0_CHRDS1_ON         }, \
    {GRAPH_VIP_S0_SC,                 GRAPH_VIP_S0_CHRDS1_ON         }, \
    {GRAPH_VIP_S0_CSC,                GRAPH_VIP_S0_CHRDS1_ON         }, \
    {GRAPH_VIP_S0_PARSER_PORTA_08_16, GRAPH_VIP_S0_CHRDS1_ON         }, \
    {GRAPH_VIP_S0_PARSER_PORTB_08,    GRAPH_VIP_S0_CHRDS1_ON         }, \
    {GRAPH_VIP_S0_SEC0,               GRAPH_VIP_S0_CHRDS1_ON         }, \
                                                                        \
    {GRAPH_VIP_INVALID,               GRAPH_VIP_S0_CHRDS0_OFF        }, \
    {GRAPH_VIP_S0_SC,                 GRAPH_VIP_S0_CHRDS0_OFF        }, \
    {GRAPH_VIP_S0_CSC,                GRAPH_VIP_S0_CHRDS0_OFF        }, \
    {GRAPH_VIP_S0_PARSER_PORTA_08_16, GRAPH_VIP_S0_CHRDS0_OFF        }, \
    {GRAPH_VIP_S0_PARSER_PORTB_08,    GRAPH_VIP_S0_CHRDS0_OFF        }, \
    {GRAPH_VIP_S0_SEC0,               GRAPH_VIP_S0_CHRDS0_OFF        }, \
                                                                        \
    {GRAPH_VIP_INVALID,               GRAPH_VIP_S0_CHRDS1_OFF        }, \
    {GRAPH_VIP_S0_SC,                 GRAPH_VIP_S0_CHRDS1_OFF        }, \
    {GRAPH_VIP_S0_CSC,                GRAPH_VIP_S0_CHRDS1_OFF        }, \
    {GRAPH_VIP_S0_PARSER_PORTA_08_16, GRAPH_VIP_S0_CHRDS1_OFF        }, \
    {GRAPH_VIP_S0_PARSER_PORTB_08,    GRAPH_VIP_S0_CHRDS1_OFF        }, \
    {GRAPH_VIP_S0_SEC0,               GRAPH_VIP_S0_CHRDS1_OFF        }, \
                                                                        \
    {GRAPH_VIP_S0_CHRDS0_ON,          GRAPH_VIP_S0_CHRDS0            }, \
    {GRAPH_VIP_S0_CHRDS0_OFF,         GRAPH_VIP_S0_CHRDS0            }, \
    {GRAPH_VIP_S0_CHRDS1_ON,          GRAPH_VIP_S0_CHRDS1            }, \
    {GRAPH_VIP_S0_CHRDS1_OFF,         GRAPH_VIP_S0_CHRDS1            }, \
                                                                        \
    {GRAPH_VIP_INVALID,               GRAPH_VIP_S0_RGB_HI            }, \
    {GRAPH_VIP_INVALID,               GRAPH_VIP_S0_RGB_HI            }, \
    {GRAPH_VIP_S0_COMP0,              GRAPH_VIP_S0_RGB_HI            }, \
    {GRAPH_VIP_S0_CSC,                GRAPH_VIP_S0_RGB_HI            }, \
                                                                        \
    {GRAPH_VIP_S0_CHRDS1,             GRAPH_VIP_S0_Y_LO              }, \
    {GRAPH_VIP_S0_PARSER_PORTA_08_16, GRAPH_VIP_S0_Y_LO              }, \
    {GRAPH_VIP_S0_CSC,                GRAPH_VIP_S0_Y_LO              }, \
    {GRAPH_VIP_S0_PARSER_PORTA_24,    GRAPH_VIP_S0_Y_LO              }, \
                                                                        \
    {GRAPH_VIP_S0_CHRDS1,             GRAPH_VIP_S0_UV_LO             }, \
    {GRAPH_VIP_S0_PARSER_PORTB_08,    GRAPH_VIP_S0_UV_LO             }, \
    {GRAPH_VIP_S0_CSC,                GRAPH_VIP_S0_UV_LO             }, \
    {GRAPH_VIP_S0_PARSER_PORTA_24,    GRAPH_VIP_S0_UV_LO             }, \
                                                                        \
    {GRAPH_VIP_S0_CHRDS0,             GRAPH_VIP_S0_Y_UP              }, \
    {GRAPH_VIP_S0_RGB_HI,             GRAPH_VIP_S0_Y_UP              }, \
                                                                        \
    {GRAPH_VIP_S0_CHRDS0,             GRAPH_VIP_S0_UV_UP             }, \
    {GRAPH_VIP_S0_CHRDS0,             GRAPH_VIP_S0_UV_UP             }, \
    {GRAPH_VIP_INVALID,               GRAPH_VIP_S0_UV_UP             }, \
    {GRAPH_VIP_S0_CHRDS1,             GRAPH_VIP_S0_UV_UP             }, \
    {GRAPH_VIP_S0_RGB_HI,             GRAPH_VIP_S0_UV_UP             }, \
                                                                        \
    {GRAPH_VIP_S0_Y_UP,               GRAPH_VIP_S0_PORTA_LUMA        }, \
    {GRAPH_VIP_S0_UV_UP,              GRAPH_VIP_S0_PORTA_CHROMA      }, \
                                                                        \
    {GRAPH_VIP_S0_Y_LO,               GRAPH_VIP_S0_PORTB_LUMA        }, \
    {GRAPH_VIP_S0_UV_LO,              GRAPH_VIP_S0_PORTB_CHROMA      }, \
                                                                        \
    {GRAPH_VIP_S0_Y_UP,               GRAPH_VIP_S0_PORTA_RGB         }, \
    {GRAPH_VIP_S0_UV_UP,              GRAPH_VIP_S0_PORTA_RGB         }, \
    {GRAPH_VIP_S0_Y_LO,               GRAPH_VIP_S0_PORTB_RGB         }, \
    {GRAPH_VIP_S0_UV_LO,              GRAPH_VIP_S0_PORTB_RGB         }, \
                                                                        \
    {GRAPH_VIP_S0_Y_LO,               GRAPH_VIP_S0_MULT_ACTA_SRC0    }, \
    {GRAPH_VIP_S0_PARSER_PORTA_ANC,   GRAPH_VIP_S0_MULT_ANCA_SRC0    }, \
    {GRAPH_VIP_S0_UV_LO,              GRAPH_VIP_S0_MULT_ACTB_SRC0    }, \
    {GRAPH_VIP_S0_PARSER_PORTB_ANC,   GRAPH_VIP_S0_MULT_ANCB_SRC0    }, \
                                                                        \
                                                                        \
                                                                        \
                                                                        \
    {GRAPH_VIP_S1_PARSER_PORTA,       GRAPH_VIP_S1_PARSER_PORTA_ANC  }, \
    {GRAPH_VIP_S1_PARSER_PORTA,       GRAPH_VIP_S1_PARSER_PORTA_INTF }, \
                                                                        \
    {GRAPH_VIP_S1_PARSER_PORTB,       GRAPH_VIP_S1_PARSER_PORTB_ANC  }, \
    {GRAPH_VIP_S1_PARSER_PORTB,       GRAPH_VIP_S1_PARSER_PORTB_INTF }, \
                                                                        \
    {GRAPH_VIP_S1_PARSER_PORTA_INTF,  GRAPH_VIP_S1_PARSER_PORTA_08   }, \
    {GRAPH_VIP_S1_PARSER_PORTA_INTF,  GRAPH_VIP_S1_PARSER_PORTA_16   }, \
    {GRAPH_VIP_S1_PARSER_PORTA_INTF,  GRAPH_VIP_S1_PARSER_PORTA_24   }, \
    {GRAPH_VIP_S1_PARSER_PORTB_INTF,  GRAPH_VIP_S1_PARSER_PORTB_08   }, \
                                                                        \
    {GRAPH_VIP_S1_PARSER_PORTA_08,    GRAPH_VIP_S1_PARSER_PORTA_08_16}, \
    {GRAPH_VIP_S1_PARSER_PORTA_16,    GRAPH_VIP_S1_PARSER_PORTA_08_16}, \
                                                                        \
    {GRAPH_VIP_INVALID,               GRAPH_VIP_S1_CSC_SRC           }, \
    {GRAPH_VIP_S1_PARSER_PORTA_08_16, GRAPH_VIP_S1_CSC_SRC           }, \
    {GRAPH_VIP_S1_PARSER_PORTB_08,    GRAPH_VIP_S1_CSC_SRC           }, \
    {GRAPH_VIP_S1_SEC0,               GRAPH_VIP_S1_CSC_SRC           }, \
    {GRAPH_VIP_S1_PARSER_PORTA_24,    GRAPH_VIP_S1_CSC_SRC           }, \
    {GRAPH_VIP_S1_COMP0,              GRAPH_VIP_S1_CSC_SRC           }, \
                                                                        \
    {GRAPH_VIP_INVALID,               GRAPH_VIP_S1_SC_SRC            }, \
    {GRAPH_VIP_S1_CSC,                GRAPH_VIP_S1_SC_SRC            }, \
    {GRAPH_VIP_S1_PARSER_PORTA_08_16, GRAPH_VIP_S1_SC_SRC            }, \
    {GRAPH_VIP_S1_PARSER_PORTB_08,    GRAPH_VIP_S1_SC_SRC            }, \
    {GRAPH_VIP_S1_SEC0,               GRAPH_VIP_S1_SC_SRC            }, \
                                                                        \
    {GRAPH_VIP_S1_CSC_SRC,            GRAPH_VIP_S1_CSC               }, \
    {GRAPH_VIP_S1_SC_SRC,             GRAPH_VIP_S1_SC                }, \
                                                                        \
    {GRAPH_VIP_INVALID,               GRAPH_VIP_S1_CHRDS0_ON         }, \
    {GRAPH_VIP_S1_SC,                 GRAPH_VIP_S1_CHRDS0_ON         }, \
    {GRAPH_VIP_S1_CSC,                GRAPH_VIP_S1_CHRDS0_ON         }, \
    {GRAPH_VIP_S1_PARSER_PORTA_08_16, GRAPH_VIP_S1_CHRDS0_ON         }, \
    {GRAPH_VIP_S1_PARSER_PORTB_08,    GRAPH_VIP_S1_CHRDS0_ON         }, \
    {GRAPH_VIP_S1_SEC0,               GRAPH_VIP_S1_CHRDS0_ON         }, \
                                                                        \
    {GRAPH_VIP_INVALID,               GRAPH_VIP_S1_CHRDS1_ON         }, \
    {GRAPH_VIP_S1_SC,                 GRAPH_VIP_S1_CHRDS1_ON         }, \
    {GRAPH_VIP_S1_CSC,                GRAPH_VIP_S1_CHRDS1_ON         }, \
    {GRAPH_VIP_S1_PARSER_PORTA_08_16, GRAPH_VIP_S1_CHRDS1_ON         }, \
    {GRAPH_VIP_S1_PARSER_PORTB_08,    GRAPH_VIP_S1_CHRDS1_ON         }, \
    {GRAPH_VIP_S1_SEC0,               GRAPH_VIP_S1_CHRDS1_ON         }, \
                                                                        \
    {GRAPH_VIP_INVALID,               GRAPH_VIP_S1_CHRDS0_OFF        }, \
    {GRAPH_VIP_S1_SC,                 GRAPH_VIP_S1_CHRDS0_OFF        }, \
    {GRAPH_VIP_S1_CSC,                GRAPH_VIP_S1_CHRDS0_OFF        }, \
    {GRAPH_VIP_S1_PARSER_PORTA_08_16, GRAPH_VIP_S1_CHRDS0_OFF        }, \
    {GRAPH_VIP_S1_PARSER_PORTB_08,    GRAPH_VIP_S1_CHRDS0_OFF        }, \
    {GRAPH_VIP_S1_SEC0,               GRAPH_VIP_S1_CHRDS0_OFF        }, \
                                                                        \
    {GRAPH_VIP_INVALID,               GRAPH_VIP_S1_CHRDS1_OFF        }, \
    {GRAPH_VIP_S1_SC,                 GRAPH_VIP_S1_CHRDS1_OFF        }, \
    {GRAPH_VIP_S1_CSC,                GRAPH_VIP_S1_CHRDS1_OFF        }, \
    {GRAPH_VIP_S1_PARSER_PORTA_08_16, GRAPH_VIP_S1_CHRDS1_OFF        }, \
    {GRAPH_VIP_S1_PARSER_PORTB_08,    GRAPH_VIP_S1_CHRDS1_OFF        }, \
    {GRAPH_VIP_S1_SEC0,               GRAPH_VIP_S1_CHRDS1_OFF        }, \
                                                                        \
    {GRAPH_VIP_S1_CHRDS0_ON,          GRAPH_VIP_S1_CHRDS0            }, \
    {GRAPH_VIP_S1_CHRDS0_OFF,         GRAPH_VIP_S1_CHRDS0            }, \
    {GRAPH_VIP_S1_CHRDS1_ON,          GRAPH_VIP_S1_CHRDS1            }, \
    {GRAPH_VIP_S1_CHRDS1_OFF,         GRAPH_VIP_S1_CHRDS1            }, \
                                                                        \
    {GRAPH_VIP_INVALID,               GRAPH_VIP_S1_RGB_HI            }, \
    {GRAPH_VIP_INVALID,               GRAPH_VIP_S1_RGB_HI            }, \
    {GRAPH_VIP_S1_COMP0,              GRAPH_VIP_S1_RGB_HI            }, \
    {GRAPH_VIP_S1_CSC,                GRAPH_VIP_S1_RGB_HI            }, \
                                                                        \
    {GRAPH_VIP_S1_CHRDS1,             GRAPH_VIP_S1_Y_LO              }, \
    {GRAPH_VIP_S1_PARSER_PORTA_08_16, GRAPH_VIP_S1_Y_LO              }, \
    {GRAPH_VIP_S1_CSC,                GRAPH_VIP_S1_Y_LO              }, \
    {GRAPH_VIP_S1_PARSER_PORTA_24,    GRAPH_VIP_S1_Y_LO              }, \
                                                                        \
    {GRAPH_VIP_S1_CHRDS1,             GRAPH_VIP_S1_UV_LO             }, \
    {GRAPH_VIP_S1_PARSER_PORTB_08,    GRAPH_VIP_S1_UV_LO             }, \
    {GRAPH_VIP_S1_CSC,                GRAPH_VIP_S1_UV_LO             }, \
    {GRAPH_VIP_S1_PARSER_PORTA_24,    GRAPH_VIP_S1_UV_LO             }, \
                                                                        \
    {GRAPH_VIP_S1_CHRDS0,             GRAPH_VIP_S1_Y_UP              }, \
    {GRAPH_VIP_S1_RGB_HI,             GRAPH_VIP_S1_Y_UP              }, \
                                                                        \
    {GRAPH_VIP_S1_CHRDS0,             GRAPH_VIP_S1_UV_UP             }, \
    {GRAPH_VIP_S1_CHRDS0,             GRAPH_VIP_S1_UV_UP             }, \
    {GRAPH_VIP_INVALID,               GRAPH_VIP_S1_UV_UP             }, \
    {GRAPH_VIP_S1_CHRDS1,             GRAPH_VIP_S1_UV_UP             }, \
    {GRAPH_VIP_S1_RGB_HI,             GRAPH_VIP_S1_UV_UP             }, \
                                                                        \
    {GRAPH_VIP_S1_Y_UP,               GRAPH_VIP_S1_PORTA_LUMA        }, \
    {GRAPH_VIP_S1_UV_UP,              GRAPH_VIP_S1_PORTA_CHROMA      }, \
                                                                        \
    {GRAPH_VIP_S1_Y_LO,               GRAPH_VIP_S1_PORTB_LUMA        }, \
    {GRAPH_VIP_S1_UV_LO,              GRAPH_VIP_S1_PORTB_CHROMA      }, \
                                                                        \
    {GRAPH_VIP_S1_Y_UP,               GRAPH_VIP_S1_PORTA_RGB         }, \
    {GRAPH_VIP_S1_UV_UP,              GRAPH_VIP_S1_PORTA_RGB         }, \
    {GRAPH_VIP_S1_Y_LO,               GRAPH_VIP_S1_PORTB_RGB         }, \
    {GRAPH_VIP_S1_UV_LO,              GRAPH_VIP_S1_PORTB_RGB         }, \
                                                                        \
    {GRAPH_VIP_S1_Y_LO,               GRAPH_VIP_S1_MULT_ACTA_SRC0    }, \
    {GRAPH_VIP_S1_PARSER_PORTA_ANC,   GRAPH_VIP_S1_MULT_ANCA_SRC0    }, \
    {GRAPH_VIP_S1_UV_LO,              GRAPH_VIP_S1_MULT_ACTB_SRC0    }, \
    {GRAPH_VIP_S1_PARSER_PORTB_ANC,   GRAPH_VIP_S1_MULT_ANCB_SRC0    }, \
};
