/*
 *******************************************************************************
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \ingroup  ALGORITHM_LINK_PLUGIN
 * \defgroup ALGORITHM_LINK_OBJECTDRAW Algorithm Plugin: Object Draw Link API
 *
 * \brief  This file contains plug in functions for rectangle drawing over
 *         a object. This plugin does the following
 *         - Takes the composite buffer from the previous link. The composite \
 *            buffer has two channels, one containing the original video \
 *            and the other containing metadata (rectangles to be drawn).
 *         - Scales co-ordinates as per the requirement
 *         - Optionally copies the input video into an output buffer \
 *            using EDMA
 *         - Draws rectangles on the video and sends to the next link
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file algorithmLink_objectDraw.h
 *
 * \brief Plugin that draws rectangles over the objects
 *
 * \version 0.0 (Mar 2013) : [NN] First version
 *
 *******************************************************************************
 */

#ifndef ALGORITHM_LINK_OBJECTDRAW_H_
#define ALGORITHM_LINK_OBJECTDRAW_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/algorithmLink.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \ingroup LINK_API_CMD
 *   \addtogroup ALGORITHM_LINK_OBJECT_DRAW_CMD Algorithm Plugin:
 *                  Object Detect Draw Control Commands
 *   @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Alg Link Config CMD: Set ROI parameters
 *
 *   \param AlgorithmLink_ObjectDrawSetROIParams [IN]
 *
 *   \return SYSTEM_STATUS_SOK on success
 *
 *******************************************************************************
 */
#define ALGORITHM_LINK_OBJECT_DRAW_CMD_SET_ROI      (0x1000)

/* @} */

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */
/**
 *******************************************************************************
 *
 *  \brief  Enumerations for which object type the algorithm should draw.
 *
 *
 *******************************************************************************
*/
typedef enum
{
    ALGORITHM_LINK_OBJECT_DETECT_DRAW_PD_TSR = 0,
    /**< Draw PD and TSR both */
    ALGORITHM_LINK_OBJECT_DETECT_DRAW_PD = 1,
    /**< Draw PD only */
    ALGORITHM_LINK_OBJECT_DETECT_DRAW_TSR = 2,
    /**< Draw TSR only */
    ALGORITHM_LINK_OBJECT_DETECT_DRAW_FORCE32BITS = 0x7FFFFFFF
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */
} AlgorithmLink_ObjectDrawOption;

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Parameters to set specific ROI
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_ControlParams baseClassControl;
    /**< Base class control params */

    UInt32                   imgFrameStartX;
    /**< Start of actual video relative to start of input buffer */
    UInt32                   imgFrameStartY;
    /**< Start of actual video relative to start of input buffer */
    UInt32                   imgFrameWidth;
    /**< Width of the input frame */
    UInt32                   imgFrameHeight;
    /**< Height of the input frame */
} AlgorithmLink_ObjectDrawSetROIParams;

/**
 *******************************************************************************
 *
 *   \brief Structure containing create time parameters for algorithm
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_CreateParams baseClassCreate;
    /**< Base class create params. This structure should be first element */
    UInt32                   imgFrameStartX;
    /**< Start of actual input to algo relative to start of input buffer */
    UInt32                   imgFrameStartY;
    /**< Start of actual input to algo relative to start of input buffer */
    UInt32                   imgFrameWidth;
    /**< Width of frame given to the PD algo */
    UInt32                   imgFrameHeight;
    /**< Height of the frame given to the PD algo */
    UInt32                   numOutBuffers;
    /**< Number of output Buffers, optional if copy of input is not needed */

    UInt32                   pdRectThickness;
    /**< Thickness of Object Rectangle */
    AlgorithmLink_ObjectDrawOption drawOption;
    /**< Option of Object to Draw */

    System_LinkOutQueParams  outQueParams;
    /**< Output queue information */
    System_LinkInQueParams   inQueParams;
    /**< Input queue information */

} AlgorithmLink_ObjectDrawCreateParams;

/**
 *******************************************************************************
 *
 *   \brief Structure containing control parameters for Object Draw
 *          algorithm
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_ControlParams baseClassControl;
    /**< Base class control params */
} AlgorithmLink_ObjectDrawControlParams;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */
static inline void AlgorithmLink_ObjectDraw_Init(
                                AlgorithmLink_ObjectDrawCreateParams *pPrm);

/**
 *******************************************************************************
 *
 * \brief Set defaults for plugin create parameters
 *
 * \param pPrm  [OUT] plugin create parameters
 *
 *******************************************************************************
 */
static inline void AlgorithmLink_ObjectDraw_Init(
    AlgorithmLink_ObjectDrawCreateParams *pPrm)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */
    memset(pPrm, 0, sizeof(AlgorithmLink_ObjectDrawCreateParams));

    pPrm->baseClassCreate.size = (UInt32)
                                sizeof(AlgorithmLink_ObjectDrawCreateParams);
    pPrm->baseClassCreate.algId = ALGORITHM_LINK_IPU_ALG_PD_DRAW;

    pPrm->imgFrameStartX    = 0U;
    pPrm->imgFrameStartY    = 0U;
    pPrm->imgFrameWidth     = 640U;
    pPrm->imgFrameHeight    = 360U;
    pPrm->numOutBuffers  = 4U;
    pPrm->inQueParams.prevLinkId    = SYSTEM_LINK_ID_INVALID;
    pPrm->inQueParams.prevLinkQueId = 0U;
    pPrm->outQueParams.nextLink     = SYSTEM_LINK_ID_INVALID;
    pPrm->pdRectThickness = 3U;
    pPrm->drawOption = ALGORITHM_LINK_OBJECT_DETECT_DRAW_PD_TSR;
}


/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of object draw algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_objectDraw_initPlugin(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */

/* Nothing beyond this point */
