/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/


/**
*  @file       eve_edma_user_interface.h
*
*  @brief      This header defines all types and constants
*              shared by implementations of the BAM EDMA user interface.
*/

#ifndef EVE_EDMA_USER_INTERFACE_H
#define EVE_EDMA_USER_INTERFACE_H

#pragma CHECK_MISRA ("none")
#include "stdint.h"
#pragma RESET_MISRA ("required")

#define MAX_NODE_CHANNELS        10U    /**< Maximum allowed number of DMA channels per node */

#define BAM_SOURCE_NODE_PORT1   0U      /**< BAM input port index 0 */
#define BAM_SINK_NODE_PORT1     0U      /**< BAM output port index 0 */

#define BAM_SOURCE_NODE_PORT2   1U      /**< BAM input port index 1 */
#define BAM_SINK_NODE_PORT2     1U      /**< BAM output port index 1 */

#define BAM_SOURCE_NODE_PORT3   2U      /**< BAM input port index 2 */
#define BAM_SINK_NODE_PORT3     2U      /**< BAM output port index 2 */

#define BAM_SOURCE_NODE_PORT4   3U      /**< BAM input port index 3 */
#define BAM_SINK_NODE_PORT4     3U      /**< BAM output port index 3 */

#define BAM_SOURCE_NODE_PORT5   4U      /**< BAM input port index 4 */
#define BAM_SINK_NODE_PORT5     4U      /**< BAM output port index 4 */

#define BAM_SOURCE_NODE_PORT6   5U      /**< BAM input port index 5 */
#define BAM_SINK_NODE_PORT6     5U      /**< BAM output port index 5 */

#define BAM_SOURCE_NODE_PORT7   6U      /**< BAM input port index 6 */
#define BAM_SINK_NODE_PORT7     6U      /**< BAM output port index 6 */

#define BAM_SOURCE_NODE_PORT8   7U      /**< BAM input port index 7 */
#define BAM_SINK_NODE_PORT8     7U      /**< BAM output port index 7 */

#define BAM_SOURCE_NODE_PORT9   8U      /**< BAM input port index 8 */
#define BAM_SINK_NODE_PORT9     8U      /**< BAM output port index 8 */

#define BAM_SOURCE_NODE_PORT10   9U      /**< BAM input port index 9 */
#define BAM_SINK_NODE_PORT10     9U      /**< BAM output port index 9 */

/**
*  @brief      Constants for defining type of EDMA transfer channel.
*
*  @remarks    These constants determine the internal EDMA auto-increment
*              settings and trigger/wait controls of each channel.
*/
typedef enum args_type
{
    EDMA_SOURCE,    /**< To be used with channels for tranfering data from DDR to internal memory */
    EDMA_SINK       /**< To be used with channels for tranfering data from internal memory to DDR */
} DMANODE_EdmaArgsType;


#endif

