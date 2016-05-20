/*==========================================================================*/
/*      Copyright (C) 2009-2015 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       iobjdet_ti.h
 *
 *  @brief      This file defines ivision interface for Object Detection
 *              Algorithms
 *
 *  @version 1.0 (July 2014) : Base version.
 */

/** @ingroup    ti_ivision_TI_OD*/
/*@{*/
#ifndef IOBJDET_TI_H
#define IOBJDET_TI_H

#include <ivision.h>
#include <ti/xdais/ires.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Maximum number of output string messages per detection.
 */
#define MAX_NUM_OUTPUT_STRINGS           (10)

/**
 * Maximum size of string message
 */
#define MAX_STRING_SIZE                 (50)

/**
 * Maximum number of detections per object.
 * This number includes total detections per PD, TSR, etc..
 * As this version of OD has just PD and TSR there could
 * be max object detections of 32 each. Hence 32 PD and
 * 32 TSR is supported.
 */
#define TI_OD_MAX_DETECTIONS_PER_OBJECT (32)

/**
 * @brief The unique const funtion table for object detection
 */
extern const IVISION_Fxns TI_OD_VISION_FXNS;

/**
* @brief IRES interface of the object detection app
*/
extern const IRES_Fxns TI_OD_IRES_FXNS;

/**
  @enum   TI_OD_ObjectType
  @brief  Enum to indicate type of object detected.
          This is used to populate objType in
          TI_OD_output structure

          If 0, TI_OD_PEDESTRIAN
          If 1, TI_OD_TRAFFIC_SIGN
          If 2, TI_OD_MAX_OBJECTS
*/
typedef enum
{
    TI_OD_PEDESTRIAN = 0,
    TI_OD_TRAFFIC_SIGN,
    TI_OD_MAX_OBJECTS

} TI_OD_ObjectType;

/**
  @enum  TI_OD_InBufOrder
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of buffer
         There is 1 input buffer descriptor

         If 0, TI_OD_IN_BUFDESC_FEATURE_PLANES: This buffer descriptor provides the
               feature planes representing the image. The feature planes are
               assumed to be 16 bit data.
         If 1, TI_OD_IN_BUFDESC_TOTAL

*/
typedef enum
{
  TI_OD_IN_BUFDESC_FEATURE_PLANES = 0,
  TI_OD_IN_BUFDESC_TOTAL

} TI_OD_InBufOrder;


/**
  @enum  TI_OD_OutBufOrder
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of out buffer

         If 0, TI_OD_OUT_BUFDESC_LIST - This  buffer is filled up by algorithm
               with a list of detected objects.
         If 1, TI_OD_OUT_BUFDESC_TOTAL
  */

typedef enum
{
  TI_OD_OUT_BUFDESC_LIST = 0,
  TI_OD_OUT_BUFDESC_TOTAL

} TI_OD_OutBufOrder;

/**
  @enum  TI_OD_ROIPreset
  @brief ROI processing presets supported by OD.
         If 0, TI_OD_ROI_FULL_FRAME
               This preset will enable search at every point in the provided
               feature data

         If 1, TI_OD_ROI_DYNAMIC
               This preset will enable search only a small region around a detected
               object in the previous frame. The previous frame could have been
               fully processed or processed based on detections.
  */

typedef enum {
    TI_OD_ROI_FULL_FRAME = 0,
    TI_OD_ROI_DYNAMIC

}TI_OD_ROIPreset;


/**
 * Maximum number of scales supported
 */
#define TI_OD_MAX_TOTAL_SCALES  (32)

/**
 * Maximum number of German traffic signs supported.
 */
#define TI_OD_NUM_TSR_TEMPLATES (43)

/**
  @enum  TI_OD_TSRClassTemplates
  @brief Enumeration of German Traffic signs. The current verion of OD
         supports only the below listed 43 clases.
*/
typedef enum
{
   /*0*/  TI_OD_TSR_SPEED_LIMIT_20 = 0,
   /*1*/  TI_OD_TSR_SPEED_LIMIT_30,
   /*2*/  TI_OD_TSR_SPEED_LIMIT_50,
   /*3*/  TI_OD_TSR_SPEED_LIMIT_60,
   /*4*/  TI_OD_TSR_SPEED_LIMIT_70,
   /*5*/  TI_OD_TSR_SPEED_LIMIT_80,
   /*6*/  TI_OD_TSR_RESTRICTION_ENDS_80,
   /*7*/  TI_OD_TSR_SPEED_LIMIT_100,
   /*8*/  TI_OD_TSR_SPEED_LIMIT_120,
   /*9*/  TI_OD_TSR_NO_OVERTAKING,
   /*10*/ TI_OD_TSR_NO_OVERTAKING_TRUCKS,
   /*11*/ TI_OD_TSR_PRIORITY_AT_NEXT_INTERSECTION,
   /*12*/ TI_OD_TSR_PRIORITY_ROAD,
   /*13*/ TI_OD_TSR_GIVE_WAY,
   /*14*/ TI_OD_TSR_STOP,
   /*15*/ TI_OD_TSR_NO_VEHICLES,
   /*16*/ TI_OD_TSR_NO_TRUCKS,
   /*17*/ TI_OD_TSR_NO_ENTRY,
   /*18*/ TI_OD_TSR_DANGER_AHEAD,
   /*19*/ TI_OD_TSR_BEND_TO_LEFT,
   /*20*/ TI_OD_TSR_BEND_TO_RIGHT,
   /*21*/ TI_OD_TSR_DOUBLE_BEND_FIRST_TO_LEFT,
   /*22*/ TI_OD_TSR_UNEVEN_ROAD,
   /*23*/ TI_OD_TSR_SLIPPERY_ROAD,
   /*24*/ TI_OD_TSR_ROAD_NARROWS,
   /*25*/ TI_OD_TSR_CONSTRUCTION,
   /*26*/ TI_OD_TSR_TRAFFIC_SIGNAL,
   /*27*/ TI_OD_TSR_PEDESTRIAN_CROSSING,
   /*28*/ TI_OD_TSR_SCHOOL_CROSSING,
   /*29*/ TI_OD_TSR_CYCLES_CROSSING,
   /*30*/ TI_OD_TSR_SNOW,
   /*31*/ TI_OD_TSR_ANIMALS,
   /*32*/ TI_OD_TSR_RESTRICTION_ENDS,
   /*33*/ TI_OD_TSR_GO_RIGHT,
   /*34*/ TI_OD_TSR_GO_LEFT,
   /*35*/ TI_OD_TSR_GO_STRAIGHT,
   /*36*/ TI_OD_TSR_GO_RIGHT_OR_STRAIGHT,
   /*37*/ TI_OD_TSR_GO_LEFT_OR_STRAIGHT,
   /*38*/ TI_OD_TSR_KEEP_RIGHT,
   /*39*/ TI_OD_TSR_KEEP_LEFT,
   /*40*/ TI_OD_TSR_ROUNDABOUT,
   /*41*/ TI_OD_TSR_RESTRICTION_ENDS_OVERTAKING,
   /*42*/ TI_OD_TSR_RESTRICTION_ENDS_OVERTAKING_FOR_TRUCKS,
   /*43*/ TI_OD_TSR_NOT_A_TRAFFIC_SIGN

} TI_OD_TSRClassTemplates;

/**
  @enum  TI_OD_ErrorCodes
  @brief Enumeration of error codes returned by OD algorithm
*/
typedef enum
{
  TI_OD_UNSUPPORTED_IMAGE_WIDTH = 16,
  TI_OD_UNSUPPORTED_IMAGE_HEIGHT = 17,
  TI_OD_UNSUPPORTED_NUM_SCALES = 18,
  TI_OD_UNSUPPORTED_DETECTION_MODE = 19,
  TI_OD_UNSUPPORTED_ROI_PRESET = 20,
  TI_OD_UNSUPPORTED_REFRESH_INTERVAL = 21,
  TI_OD_UNSUPPORTED_CLASSIFIER_TYPE = 22,
  TI_OD_UNSUPPORTED_TRACKING_METHOD = 23,
  TI_OD_UNSUPPORTED_RECOGNITION_METHOD = 24,
  TI_OD_UNSUPPORTED_SOFT_CASCADE_THRESHOLD = 25,
  TI_OD_UNSUPPORTED_STRONG_CASCADE_THRESHOLD = 26,
  TI_OD_UNSUPPORTED_META_DATA = 27,
  TI_OD_EDMA_MEMCPY_ERROR = 28,
  TI_OD_EDMA_SCATTER_GATHER_ERROR = 29,
  TI_OD_RESERVED_PARAMS_NOT_ZERO = 20,
  TI_OD_UNSUPPORTED_PARAMETER = 31
} TI_OD_ErrorCodes;

/**
  @struct TI_OBJECT_FEATURES_scaleMetaData

  @brief  This structure contains all the meta data containing
          informtion about the each scale feature

  @param  scaleOffset
          Offset from the base output pointer

  @param  orgImCols
          Original image width in pixels

  @param  orgImRows
          Original image height in pixels

  @param  imCols
          ROI Image width in pixels, can be same as orgImCols for
          full image processing.

  @param  imRows
          ROI Image height in pixels, can be same as orgImRows for
          full image processing

  @param  startX
          ROI starting location in pixels along X direction

  @param  startY
          ROI starting location in pixels along Y direction

  @param  featCols
          number of valid features in each row of a feture plane

  @param  featRows
          number of features row per feture plane

  @param  featPitch
          Offset between each line of a feture plane (in Bytes)

  @param  planeOffset
          Offset between each feture plane (in Bytes)
*/
typedef struct
{
  uint32_t          scaleOffset;
  uint16_t          orgImCols;
  uint16_t          orgImRows;
  uint16_t          imCols;
  uint16_t          imRows;
  uint16_t          startX;
  uint16_t          startY;
  uint16_t          featCols;
  uint16_t          featRows;
  uint16_t          featPitch;
  uint32_t          planeOffset;

} TI_OBJECT_FEATURES_scaleMetaData;

/**
  @struct TI_OBJECT_FEATURES_outputMetaData

  @brief  This structure contains all the meta data containing
          informtion about the feature data set.

  @param  size
          Size of this stucture in bytes

  @param  featBufSize
          Total output buffer size in bytes

  @param  numScales
          Total number of (pyramid levles) fearture scales

  @param  numPlanes
          Number of feature planes/channels.

  @param  outFormat
          Feature data layout information.

  @param  leftPadPels
          Left padding of input image in pixels. Equal amount of
          padding will be applied on the right edge of the image.

  @param  topPadPels
          Top padding of input image in pixels. Equal amount of
          padding will be applied on the bottom edge of the image.

  @param  computeCellSum
          Flag to indicate of 2x2 cell sum is to be computed by OD
          algorithm or not
          0 - 2x2 cell sum computed outside OD.
          1 - 2x2 cell sum to be computed by OD.
*/

typedef struct
{
  uint32_t          size;
  uint32_t          featBufSize;
  uint8_t           numScales;
  uint8_t           numPlanes;
  uint8_t           outFormat;
  uint16_t          leftPadPels;
  uint16_t          topPadPels;
  uint8_t           computeCellSum;
  TI_OBJECT_FEATURES_scaleMetaData scaleInfo[TI_OD_MAX_TOTAL_SCALES];
} TI_OBJECT_FEATURES_outputMetaData;

/**
  @struct TI_OD_CreateParams
  @brief  This structure contains all the parameters which controls
          OD algorithm at create time

  @param  edma3RmLldHandle
          Handle to EDMA3 resource manager.

  @param  maxImageWidth
          Max input width of image

  @param  maxImageHeight
          Max input height of image

  @param  maxScales
          Max number of supported scales
*/
typedef struct
{
  IVISION_Params visionParams;
  void    *edma3RmLldHandle;

  uint16_t maxImageWidth;
  uint16_t maxImageHeight;
  uint16_t maxScales;

} TI_OD_CreateParams;

/**
  @struct TI_OD_PDConfig
  @brief  This structure contains the PD specific
          config parameters.

  @param  enablePD
          Flag to enable or disable pedestrian detection
          0 - disable
          1 - enable (default)

  @param  classifierTypePD
          Flag to indicate type of classifier to be used.
          0 - Two level Adaboost (default)

  @param  trackingMethodPD
          Flag to enable / disable pedestrian tracking
          0 - disable tracking
          1 - enable  tracking (default)

  @param  softCascadeThPD
          32-bit signed threshold value for AdaBoost.
          -1 (recommended)

  @param  strongCascadeThPD
          32-bit signed threshold value for AdaBoost
          -1 (recommended)

*/
typedef struct
{
  uint8_t enablePD;
  uint8_t classifierTypePD;
  uint8_t trackingMethodPD;
  int32_t softCascadeThPD;
  int32_t strongCascadeThPD;

} TI_OD_PDConfig;

/**
  @struct TI_OD_TSRConfig
  @brief  This structure contains the TSR specific
          config parameters.

  @param  enableTSR
          Flag to enable or disable traffic sign detection
          0 - disable
          1 - enable (default)

  @param  classifierTypeTSR
          Flag to indicate type of classifier to be used.
          0 - Two level Adaboost (default)

  @param  trackingMethodTSR
          Flag to enable / disable traffic sign recognition.
          0 - disable tracking
          1 - enable  tracking (default)

  @param  recognitionMethodTSR
          Flag to enable / disable traffic sign recognition.
          0 - disable
          1 - enable LDA (default)

  @param  softCascadeThTSR
          32-bit signed threshold value for AdaBoost
          -1 (recommended)

  @param  strongCascadeThTSR
          32-bit signed threshold value for AdaBoost
          7 (recommended)

*/
typedef struct
{
  uint8_t enableTSR;
  uint8_t classifierTypeTSR;
  uint8_t trackingMethodTSR;
  uint8_t recognitionMethodTSR;
  int32_t softCascadeThTSR;
  int32_t strongCascadeThTSR;

} TI_OD_TSRConfig;


/**
  @struct TI_OD_InArgs
  @brief  This structure contains all the parameters which are given as an
          input to OD algorithm at frame level

  @param  iVisionInArgs
          Common InArgs  for all ivison based modules

  @param  pdConfig
          Structure of type TI_OD_PDConfig

  @param  tsrConfig
          Structure of type TI_OD_TSRConfig

  @param  roiPreset
          Flag to enable or disable ROI processing on DSP
          0 - Searches each point in the feature vector every frame
          1 - Searches only regions around detected object in previous
              frames
          See enum TI_OD_ROIPreset

  @param  refreshInterval
          Specifies frame refresh rate when roiPreset is 1.
          Eg. A value of 2 will process every even frames fully and every
          odd frames only around detected object regions.
          Not applicable when roiPreset is 0.

  @param  detectionMode
          This is to control search points in feature plane.
          When,

          detectionMode = 0 => Search all points. HIGH_QUALITY mode. (default)
          detectionMode = 1 => Skip odd points in the horizontal direction

  @param  reserved0
           Reserved 32-bit field. Must be set to 0 for normal operation.

  @param  reserved1
           Reserved 32-bit field. Must be set to 0 for normal operation.

  @param  reserved2
           Reserved 32-bit field. Must be set to 0 for normal operation.

  @param  reserved3
           Reserved 32-bit field. Must be set to 0 for normal operation.

*/
typedef struct
{
  IVISION_InArgs   iVisionInArgs;
  TI_OD_PDConfig   pdConfig;
  TI_OD_TSRConfig  tsrConfig;
  uint8_t          detectionMode;
  uint8_t          roiPreset;
  uint8_t          refreshInterval;

  uint32_t         reserved0;
  uint32_t         reserved1;
  uint32_t         reserved2;
  uint32_t         reserved3;

} TI_OD_InArgs;

/**
  @struct TI_OD_PDStats
  @brief  This structure reports statistics of running PD.
          To be used only for debug purpose.

  @param  numCyclesPD
          Number of cycles taken by classifier.

  @param  numTreesPD
          Total number of trees traversed by AdaBoost classifier.
          NA when classifierType is not AdaBoost.

*/

typedef struct
{
  uint32_t numCyclesPD;
  uint32_t numTreesPD;

} TI_OD_PDStats;

/**
  @struct TI_OD_TSRStats
  @brief  This structure reports statistics of running TSR
          To be used only for debug purpose.

  @param  numCyclesTSR
          Number of cycles taken by classifier.

  @param  numTreesTSR
          Total number of trees traversed by AdaBoost classifier.
          NA when classifierType is not AdaBoost.

*/

typedef struct
{
  uint32_t numCyclesTSR;
  uint32_t numTreesTSR;

} TI_OD_TSRStats;

/**
  @struct TI_OD_OutArgs
  @brief  This structure contains all the parameters
          which are given as output.

  @param  iVisionOutArgs
          Common outArgs for all ivison based modules

  @param  pdStats
          Stats structure of type TI_OD_PDStats for PD

  @param  tsrStats
          Stats structure of type TI_OD_TSRStats for TSR

  @param  errorCode
          Type of error detected by the module see TI_OD_ErrorCodes
*/
typedef struct
{
  IVISION_OutArgs iVisionOutArgs;
  TI_OD_PDStats   pdStats;
  TI_OD_TSRStats  tsrStats;
  uint32_t errorCode;
} TI_OD_OutArgs;

/**
  @struct TI_OD_objectDescriptor
  @brief  This structure contains the detected object properties
          such as location-(x, y), size-(height, width), confidence (score)
          string messages etc.

  @param  objType
          Indicates the type of object detected. See enum TI_OD_ObjectType
          for supported object types.

  @param  xPos
          Location of the detected object in pixels along X direction.

  @param  yPos
          Location of the detected object in pixels along Y direction.

  @param  objWidth
          Width of the located object in pixels. Does not indicate actual
          width of the object.

  @param  objHeight
          Width of the located object in pixels. Does not indicate actual
          height of the object.

  @param  objTag
          Value or index to indicate, color in case of pedestrian tracking
          or traffic sign type. See enum TI_OD_TSRClassTemplates for
          supported traffic signs. Current version of OD fills 0 for pedestrian
          detection and one out of 43 enumerations for traffic sign recognition

  @param  objScore
          Adaboost classifier score for the detected object.

  @param  objScale
          Scale at which the object was detected. A lower number indicates that
          an object far from the camera was detected. A higher number indicates
          that the object close to the camera was detected. This number may not
          correspond to original image pyramid scale ratio. The numbers may come
          out interpolated between scales.
          IEEE 32-bit single precision floating point format.

  @param  numMsg
          Number of auxiliary string messages passed by algorithm back to
          the application. Max is defined by MAX_NUM_OUTPUT_STRINGS

  @param  objMsg[MAX_NUM_OUTPUT_STRINGS][MAX_STRING_SIZE]
          Auxiliary string message describing the object by the algorithm.
          Only for display purpose.

*/
typedef struct
{
  uint8_t  objType;

  uint16_t xPos;
  uint16_t yPos;

  uint16_t objWidth;
  uint16_t objHeight;

  uint32_t objTag;
  int32_t  objScore;
  float    objScale;

  uint16_t numMsg;
  uint8_t  objMsg[MAX_NUM_OUTPUT_STRINGS][MAX_STRING_SIZE];
} TI_OD_objectDescriptor;

/**
  @struct TI_OD_output
  @brief  This is the output structure given out by object detection
          module. It contains the number of objects detected and
          TI_OD_MAX_DETECTIONS_PER_OBJECT instances of TI_OD_objectDescriptor
          structure. The number of valid descriptors is governed by
          numObjects variable.

  @param  numObjects
          Number of objects detected by the module.

  @param  errorCode
          Error Code returned for one process call. A value of 0
          indicates no error. Refer TI_OD_errorCodes enumeration
          for a list of errorCodes thrown by OD.

  @param  objDesc
          List of detected object descriptor.
          Max size TI_OD_MAX_DETECTIONS_PER_OBJECT

*/
typedef struct
{
  int32_t numObjects;
  int32_t errorCode;
  TI_OD_objectDescriptor objDesc[TI_OD_MAX_DETECTIONS_PER_OBJECT];
} TI_OD_output;

/*
 * Total size of the output buffer to be allocated by the application.
 */
#define TI_OD_OUT_BUFDESC_LIST_SIZE (sizeof(TI_OD_output))

/*@}*/
/* ti_ivision_TI_OD */

#ifdef __cplusplus
}
#endif

#endif /*IOBJDET_TI_H */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/


