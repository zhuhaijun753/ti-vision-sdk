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
 *  \file fvid2_drvMgr.h
 *
 *  \brief FVID2 driver manager header file.
 *
 *  This file exposes internal functions of driver management functionality.
 *  This is not used by application and is used by video drivers to register
 *  itself to the FVID2.
 *
 */

#ifndef FVID2_DRVMGR_H_
#define FVID2_DRVMGR_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <fvid2/fvid2.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief FVID2 driver handle returned by individual drivers. */
typedef Ptr Fdrv_Handle;

/** \brief Typedef for callback function parameters. */
typedef struct Fvid2_DrvCbParams_t Fvid2_DrvCbParams;

/**
 *  \brief Typedef for FVID2 driver callback function prototype. This will be
 *  called by the driver and then the FVID2 driver manager will route the
 *  callback to the application.
 *
 *  fdmData: FVID2 driver manager internal data passed to driver during create
 *  call.
 *
 *  reserved: For future use. Not used currently. This will be set to NULL.
 */
typedef Int32 (*Fdm_CbFxn)(Ptr fdmData, Ptr reserved);

/**
 *  \brief Typedef for FVID2 driver error callback function prototype.
 *  This will be called by the driver and then the FVID2 driver manager
 *  will route the error callback to the application.
 *
 *  fdmData: FVID2 driver manager internal data passed to driver during create
 *  call.
 *
 *  errList: Error data passed to the application.
 *
 *  reserved: For future use. Not used currently. This will be set to NULL.
 */
typedef Int32 (*Fdm_ErrCbFxn)(Ptr fdmData, void *errList, Ptr reserved);

/** \brief Typedef for FVID2 create function pointer. */
typedef Fdrv_Handle (*Fvid2_DrvCreate)(UInt32                   drvId,
                                       UInt32                   instanceId,
                                       Ptr                      createArgs,
                                       Ptr
                                       createStatusArgs,
                                       const Fvid2_DrvCbParams *fdmCbParams);

/** \brief Typedef for FVID2 delete function pointer. */
typedef Int32 (*Fvid2_DrvDelete)(Fdrv_Handle handle, Ptr deleteArgs);

/** \brief Typedef for FVID2 control function pointer. */
typedef Int32 (*Fvid2_DrvControl)(Fdrv_Handle handle,
                                  UInt32      cmd,
                                  Ptr         cmdArgs,
                                  Ptr         cmdStatusArgs);

/** \brief Typedef for FVID2 queue function pointer. */
typedef Int32 (*Fvid2_DrvQueue)(Fdrv_Handle      handle,
                                Fvid2_FrameList *frameList,
                                UInt32           streamId);

/** \brief Typedef for FVID2 dequeue function pointer. */
typedef Int32 (*Fvid2_DrvDequeue)(Fdrv_Handle      handle,
                                  Fvid2_FrameList *frameList,
                                  UInt32           streamId,
                                  UInt32           timeout);

/** \brief Typedef for FVID2 process frames function pointer. */
typedef Int32 (*Fvid2_DrvProcessFrames)(Fdrv_Handle        handle,
                                        Fvid2_ProcessList *processList);

/** \brief Typedef for FVID2 get processed frames function pointer. */
typedef Int32 (*Fvid2_DrvGetProcessedFrames)(Fdrv_Handle        handle,
                                             Fvid2_ProcessList *processList,
                                             UInt32             timeout);

/** \brief Typedef for FVID2 process frames function pointer. */
typedef Int32 (*Fvid2_DrvProcessRequest)(Fdrv_Handle        handle,
                                         Fvid2_FrameList   *inProcessList,
                                         Fvid2_FrameList   *outProcessList);

/** \brief Typedef for FVID2 get processed frames function pointer. */
typedef Int32 (*Fvid2_DrvGetProcessedRequest)(Fdrv_Handle        handle,
                                              Fvid2_FrameList   *inProcessList,
                                              Fvid2_FrameList   *outProcessList,
                                              UInt32             timeout);


/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct Fvid2_DrvCbParams_t
 *  \brief Structure for setting callback function parameters.
 */
struct Fvid2_DrvCbParams_t
{
    Fdm_CbFxn    fdmCbFxn;
    /**< FDM callback function used by the driver to initimate any
     *   operation has completed or not. */
    Fdm_ErrCbFxn fdmErrCbFxn;
    /**< FDM error callback function used by the driver to initimate
     *   any error occuring at the time of streaming. */
    Fvid2_Handle handle;
    /**< FDM layer FVID2 handle. This can be used by the actual driver to call
     *   application callback with proper FVID2 handle instead of routining
     *   the call through FDM layer. */
    void        *errList;
    /**< Pointer to a valid framelist or processlist where the driver
     *   copies the aborted/error packet. */
    Ptr          fdmData;
    /**< FDM specific data which is returned in the callback function
     *   as it is. */
    Ptr          reserved;
    /**< For future use. Not used currently. Set this to NULL. */
};

/**
 *  struct Fvid2_DrvOps
 *  \brief Structure to store driver function pointers.
 */
typedef struct
{
    UInt32                      drvId;
    /**< Unique driver Id. */
    Fvid2_DrvCreate             createFxn;
    /**< FVID2 create function pointer. */
    Fvid2_DrvDelete             deleteFxn;
    /**< FVID2 delete function pointer. */
    Fvid2_DrvControl            controlFxn;
    /**< FVID2 control function pointer. */
    Fvid2_DrvQueue              queueFxn;
    /**< FVID2 queue function pointer. */
    Fvid2_DrvDequeue            dequeueFxn;
    /**< FVID2 dequeue function pointer. */
    Fvid2_DrvProcessFrames      processFramesFxn;
    /**< FVID2 process frames function pointer. */
    Fvid2_DrvGetProcessedFrames getProcessedFramesFxn;
    /**< FVID2 get processed frames function pointer. */
    Fvid2_DrvProcessRequest     processRequestFxn;
    /**< FVID2 process request function pointer. */
    Fvid2_DrvGetProcessedRequest getProcessedRequestFxn;
    /**< FVID2 get processed request function pointer. */
} Fvid2_DrvOps;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  Fvid2_registerDriver
 *  \brief FVID2 register driver function.
 *
 *  This function registers a driver with the FVID2 driver manager.
 *
 *  \param drvOps       Driver function table pointer containing driver
 *                      function pointers and driver name. The driver name
 *                      should be unique - two or more drivers can't have the
 *                      same driver name.
 *
 *  \return             Returns 0 on success else returns error value.
 */
Int32 Fvid2_registerDriver(const Fvid2_DrvOps *drvOps);

/**
 *  Fvid2_unRegisterDriver
 *  \brief FVID2 unregister driver function.
 *
 *  This function unregisters a driver from the FVID2 driver manager.
 *
 *  \param drvOps       Driver function table pointer containing driver
 *                      function pointers and driver name.
 *
 *  \return             Returns 0 on success else returns error value.
 */
Int32 Fvid2_unRegisterDriver(const Fvid2_DrvOps *drvOps);

/**
 *  Fvid2_checkFrameList
 *  \brief Checks the FVID2 frame list for error and returns appropriate error.
 *
 *  This is used by the drivers and not by the application.
 *
 *  \param frameList    Pointer to frame list to check for errors.
 *  \param maxFrames    Max frames to be checked against numFrames member
 *                      in frame list.
 *
 *  \return             Returns 0 on success else returns error value.
 */
Int32 Fvid2_checkFrameList(const Fvid2_FrameList *frameList, UInt32 maxFrames);

/**
 *  Fvid2_checkDqFrameList
 *  \brief Checks the FVID2 frame list of dequeue call for error and returns
 *  appropriate error. For dequeue operation, the frame pointers in the frames
 *  should not be checked as this will be filled by the driver.
 *
 *  This is used by the drivers and not by the application.
 *
 *  \param frameList    Pointer to frame list to check for errors.
 *  \param maxFrames    Max frames to be checked against numFrames member
 *                      in frame list.
 *
 *  \return             Returns 0 on success else returns error value.
 */
Int32 Fvid2_checkDqFrameList(const Fvid2_FrameList *frameList,
                             UInt32                 maxFrames);

/**
 *  Fvid2_checkProcessList
 *  \brief Checks the FVID2 process list for error and returns appropriate
 *  error.
 *
 *  This is used by the drivers and not by the application.
 *
 *  \param processList  Pointer to process list to check for errors.
 *  \param inLists      Expected number of in frame list to check for errors.
 *  \param outLists     Expected number of out frame list to check for errors.
 *  \param maxFrames    Max frames to be checked against numFrames member
 *                      in frame list.
 *  \param isMosaicMode TRUE for mosaic mode as the number of frames can be
 *                      different across input and output frame lists if
 *                      isMosaicMode is TRUE. Hence numFrames equality in out
 *                      frame list and in frame list is not checked.
 *
 *  \return             Returns 0 on success else returns error value.
 */
Int32 Fvid2_checkProcessList(const Fvid2_ProcessList *processList,
                             UInt32                   inLists,
                             UInt32                   outLists,
                             UInt32                   maxFrames,
                             Bool                     isMosaicMode);

/**
 *  Fvid2_copyFrameList
 *  \brief Copies the source frame list to the destination frame list.
 *  This also resets the frame pointers from the source frame list.
 *
 *  This is used by the drivers and not by the application.
 *
 *  \param dest         Pointer to destination frame list.
 *  \param src          Pointer to source frame list.
 *
 *  \return             Returns 0 on success else returns error value.
 */
void Fvid2_copyFrameList(Fvid2_FrameList *dest, Fvid2_FrameList *src);

/**
 *  Fvid2_duplicateFrameList
 *  \brief Duplicate the source frame list to the destination frame list.
 *  This does not reset the frame pointers from the source frame list.
 *
 *  This is used by the drivers and not by the application.
 *
 *  \param dest         Pointer to destination frame list.
 *  \param src          Pointer to source frame list.
 *
 *  \return             Returns 0 on success else returns error value.
 */
void Fvid2_duplicateFrameList(Fvid2_FrameList       *dest,
                              const Fvid2_FrameList *src);

/**
 *  Fvid2_copyProcessList
 *  \brief Copies the source process list to the destination process list.
 *  This also resets the frame list pointers from the source process list.
 *
 *  This is used by the drivers and not by the application.
 *
 *  \param dest         Pointer to destination process list.
 *  \param src          Pointer to source process list.
 *
 *  \return             Returns 0 on success else returns error value.
 */
void Fvid2_copyProcessList(Fvid2_ProcessList *dest, Fvid2_ProcessList *src);


/**
 *  \brief Fvid2_DrvOps structure init function.
 *
 *  \param drvOps   [IN] Pointer to #Fvid2_DrvOps structure.
 *
 */
static inline void Fvid2DrvOps_init(Fvid2_DrvOps *drvOps);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void Fvid2DrvOps_init(Fvid2_DrvOps *drvOps)
{
    if (NULL != drvOps)
    {
        drvOps->drvId                   = 0U;
        drvOps->createFxn               = NULL;
        drvOps->deleteFxn               = NULL;
        drvOps->controlFxn              = NULL;
        drvOps->queueFxn                = NULL;
        drvOps->dequeueFxn              = NULL;
        drvOps->processFramesFxn        = NULL;
        drvOps->getProcessedFramesFxn   = NULL;
        drvOps->processRequestFxn       = NULL;
        drvOps->getProcessedRequestFxn  = NULL;
    }

    return;
}


#ifdef __cplusplus
}
#endif

#endif /* #ifndef FVID2_DRVMGR_H_ */
