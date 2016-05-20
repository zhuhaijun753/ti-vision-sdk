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

/** \file   bsp_audio.c
 *
 *  \brief  audio interface implementation for the DSP BIOS operating system.
 *
 * This file implements the audio interface layer which is used as an interface
 * to the underlying audio devices(McASP/McBSP/voice codecs) and the various
 * audio codecs.This implementation is for the DSP BIOS operating system.
 *
 *  (C) Copyright 2009, Texas Instruments, Inc
 *
 *  \author     Platform Support Group
 *
 *  \version
 *
 *     0.1  Created for DM814x/C6A811x platform.
 *
 */

/* ========================================================================== */
/*                             Include files                                  */
/* ========================================================================== */

#include <assert.h>
#include <string.h>
#include <xdc/runtime/System.h>
#include <xdc/std.h>
#include <ti/sysbios/io/IOM.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Swi.h>
#include <ti/sysbios/hal/Hwi.h>
#include <mcasp/bsp_mcasp.h>

#include <audio/bsp_audio.h>
#include <devices/bsp_aic31.h>
#include <bsp_audioPriv.h>

/* -------- constants -------- */

const Audio_Params        Audio_PARAMS =
{
    AUDIO_DEVICETYPE_MCASP,     /* adDevType */
    "NONE",                     /* adDevName */
    (Uint8) 0x1,                /* acNumCodecs */
    {"", "", "", "", ""}        /* acDevName[5] */
};
/* ========================================================================== */
/*                       GLOBAL MODULE STATE                                  */
/* ========================================================================== */
/**
 *  \brief  Array which is part of Audio Module State
 */
static Bool               gAudioModInUse[AUDIO_NUMINSTANCES];
/**
 *  \brief  Audio Module State Object
 */
static Audio_Module_State Audio_module = {&gAudioModInUse[0]};
/**
 *  \brief  Array of Audio instance State objects array
 */
static Audio_Object       Audio_Instances[AUDIO_NUMINSTANCES];

/* ========================================================================== */
/*                        LOCAL FUNCTION PROTOTYPES                           */
/* ========================================================================== */
/**
 *  Below ifdef __cplusplus is added so that C++ build passes without
 *  typecasting. This is because the prototype is build as C type
 *  whereas this file is build as CPP file. Hence we get C++ build error.
 *  Also if tyecasting is used, then we get MisraC error Rule 11.1.
 */
#ifdef __cplusplus
extern "C"
{
#endif
static Int audioMdBindDev(Ptr *devp, Int devId, Ptr devParams);
static Int audioMdUnBindDev(Ptr devp);
static Int audioMdCreateChan(
    Ptr             *chanp,
    Ptr              devp,
    String           name,
    Int              mode,
    Ptr              chanParams,
    IOM_TiomCallback cbFxn,
    Ptr              cbArg
    );
static Int audioMdDeleteChan(Ptr chanp);
static Int audioMdSubmitChan(Ptr chanp, IOM_Packet *ioPacket);
static Int audioMdControlChan(Ptr chanp, Uns cmd, Ptr cmdArgs);
#ifdef __cplusplus
}
#endif
static Int audioSampleRateConfigure(Audio_Object *instHandle,
                                    Uint32        ioctlArg);

IOM_Fxns Audio_IOMFXNS =
{
    &audioMdBindDev,
    &audioMdUnBindDev,
    &audioMdControlChan,
    &audioMdCreateChan,
    &audioMdDeleteChan,
    &audioMdSubmitChan,
};
/* ========================================================================== */
/*                              Functions                                     */
/* ========================================================================== */

/*
 *  \brief  Function called by Bios during instance initialisation
 *
 *  \enter  Not implemented
 *
 *  \leave  Not implemented
 */
Void Audio_init(Void)
{
    Int         i;
    static Bool oneTimeAudioInit = (Bool) FALSE;

    if((Bool) FALSE == oneTimeAudioInit)
    {
        oneTimeAudioInit = (Bool) TRUE;

        for(i = (Int) 0; i < (Int) AUDIO_NUMINSTANCES; i++)
        {
            /* have to initialize statically                                      */
            /* MISRA PTR.ARITH */
            Audio_module.inUse[i] = (Bool) FALSE;
            memset((Void *) &Audio_Instances[i], 0x0, sizeof(Audio_Object));
        }
    }
}

/*
 *  \brief  Function called by Bios during instance initialisation.This
 *          function ensures that all the data structures are initialised
 *          and the user supplied parameters are updated.
 *
 *  \param  devp        [OUT] pointer to the audio driver object
 *  \param  devId       [IN]  must be less than Audio_NUMINSTANCES
 *  \param  devParams   [IN]  user supplied parameters
 *
 *  \return IOM_COMPLETED
 *                  in case of success
 *          IOM_EBADARGS
 *                  in case of bad arguments passed
 *          IOM_EBADMODE
 *                  in case that the module is already in use
 *
 *  \enter  devp        should be non NULL and valid pointer,
 *          devParams   if NULL Audio_PARAMS default will be used.
 *
 *  \leave  Not implemented
 *
 */
static Int audioMdBindDev(Ptr *devp, Int devId, Ptr devParams)
{
    Uint32 count  = 0;
    Uint32 loop   = 0;
    Int32  retVal = IOM_COMPLETED;
    Audio_Channel_Object *chanHandle = NULL;
    Audio_Params         *params     = NULL;
    Audio_Object         *instHandle = NULL;

    /* Begin parameter checking
     *                                                  */
#ifndef PSP_DISABLE_INPUT_PARAMETER_CHECK
    if((Int32)AUDIO_NUMINSTANCES <= devId)
    {
        retVal = IOM_EBADARGS;
    }
    else
    {
#endif
    /* get the Handle to the instance object                              */
    instHandle = &Audio_Instances[devId];

#ifndef PSP_DISABLE_INPUT_PARAMETER_CHECK
    if((NULL == instHandle) ||
       (NULL == devp) ||
       (TRUE == Audio_module.inUse[devId]))
    {
        retVal = IOM_EBADARGS;
    }
}

#endif  /* PSP_DISABLE_INPUT_PARAMETER_CHECK */
    /* End parameter checking
     *                                                    */

    if(IOM_COMPLETED == retVal)
    {
        if(NULL == devParams)
        {
            params = (Audio_Params *) &Audio_PARAMS;
        }
        else
        {
            params = (Audio_Params *) devParams;
        }

        Audio_module.inUse[devId] = (Bool) TRUE;

        instHandle->instNum   = (Uint8) devId;
        instHandle->adDevType = params->adDevType;
        instHandle->adDevName = params->adDevName;

        instHandle->adAudioDevData.isMaster = (Bool) FALSE;
        instHandle->acNumCodecs = params->acNumCodecs;
        instHandle->adDevHandle = NULL;

        for(count = 0; count < AUDIO_NUMCODECINSTANCES; count++)
        {
            instHandle->acDevName[count] = params->acDevName[count];
            instHandle->acDevHandle[count]          = NULL;
            instHandle->acCodecData[count].acOpMode = ICodec_OpMode_SLAVE;
        }

        for(count = 0; count < AUDIO_NUM_CHANS; count++)
        {
            chanHandle = &instHandle->ChanObj[count];

            /* channel state closed                                   */
            chanHandle->chanState = Audio_DriverState_CLOSED;

            /* update the audio device channel handle                 */
            chanHandle->aiAudioChanHandle = NULL;

            for(loop = 0; loop < AUDIO_NUMCODECINSTANCES; loop++)
            {
                chanHandle->aiAudioCodecHandle[loop]  = NULL;
                chanHandle->aiChannelConfig.chanParam = NULL;

                memset(
                    &chanHandle->aiChannelConfig.acChannelConfig[loop],
                    0x00,
                    sizeof(ICodec_ChannelConfig));
            }

            chanHandle->cbFxn = NULL;
            chanHandle->cbArg = NULL;
            chanHandle->aiChannelConfig.chanParam = NULL;
        }

        instHandle->devState = Audio_DriverState_CREATED;
        *devp = instHandle;
    }
#ifndef PSP_DISABLE_INPUT_PARAMETER_CHECK
    else
    {
        if(devp != NULL)
        {
            *devp = NULL;
        }
    }
#endif

    return ((Int) retVal);
}
/**
 *  \brief  This function creates the audio interface channel for TX or RX.
 *
 *          Creates a communication channel in specified mode to communicate
 *          data between the application and the audio interface instance.
 *          it returns configured channel handle to application which will be
 *          used for further transactions with the channel.
 *
 * \param   instHandle   [IN]     Driver object
 * \param   name         [IN]     Instance name of the device audioif0 etc
 * \param   mode         [IN]     channel  mode -> input or output
 * \param   chanParams   [IN]     channel parameters from user
 * \param   cbFxn        [IN]     callback function pointer
 * \param   cbArg        [IN]     callback function Arguments
 * \param   eb           [OUT]    error block given by application
 *
 * \return  Handle to the channel
 *                      if sucessful
 *          NULL
 *                      if not successful
 *
 *   \enter    chanp      must be a valid pointer and should not be null.
 *             devp       must be a valid pointer and should not be null.
 *             name       must be a valid name.
 *             mode       must be a valid mode, either input or output.
 *             chanParams must be a valid pointer and should not be null.
 *             cbFxn      must be a valid pointer and should not be null.
 *             cbArg      must be a valid pointer and should not be null.
 *
 *  \leave   Not implemented
 *
 */
static Int audioMdCreateChan(Ptr             *chanp,
                             Ptr              devp,
                             String           name,
                             Int              mode,
                             Ptr              chanParams,
                             IOM_TiomCallback cbFxn,
                             Ptr              cbArg)
{
    Audio_Object *instHandle = NULL;
    Audio_ChannelConfig      *audioDevParams = NULL;
    Audio_Channel_Object     *chanHandle     = NULL;
    Uint8         i       = 0;
    Uint32        hwiKey  = 0;
    Int32         retVal  = IOM_COMPLETED;
    String        remName = NULL;
    IOM_Fxns                *iomFxns;
    Ptr           devicepointer;
    Bool          breakLoop = (Bool) FALSE;

    /* Begin parameter checking
     *                                                  */
#ifndef PSP_DISABLE_INPUT_PARAMETER_CHECK
    if((NULL == cbFxn) ||
       (NULL == cbArg) ||
       (NULL == chanParams) ||
       (NULL == devp) ||
       ((IOM_INPUT != mode) && (IOM_OUTPUT != mode)))
    {
        retVal = IOM_EBADARGS;
    }
#endif  /* PSP_DISABLE_INPUT_PARAMETER_CHECK */
    /* End parameter checking
     *                                                    */

    instHandle = (Audio_Object *) devp;

    if(IOM_COMPLETED == retVal)
    {
        /* done to remove compiler warning */
        if(NULL != name)
        {
            name = name;
        }

        /* use the application provided parameters                            */
        audioDevParams = (Audio_ChannelConfig *) chanParams;

        /* update the parameters to the driver data structure                 */
        instHandle->ChanObj[mode - 1].aiChannelConfig = *audioDevParams;

        chanHandle = &instHandle->ChanObj[mode - 1];

        /* enter critical section                                             */
        hwiKey = (Uint32) Hwi_disable();

        if(Audio_DriverState_CLOSED == chanHandle->chanState)
        {
            /* update the channel status to opened                            */
            chanHandle->chanState = Audio_DriverState_OPENED;

            /* Leave critical section                                         */
            Hwi_restore(hwiKey);

            /* update the callback function details                           */
            chanHandle->cbFxn = cbFxn;
            chanHandle->cbArg = (Ptr) cbArg;

            chanHandle->devHandle = instHandle;

            /* open the codec devices here                                    */
            for(i = 0; i < instHandle->acNumCodecs; i++)
            {
                remName = DEV_match(
                    instHandle->acDevName[i],
                    &instHandle->acDevHandle[i]);

                if((NULL == instHandle->acDevHandle[i]) || (NULL == remName))
                {
                    retVal = IOM_EBADARGS;
                }
                else
                {
                    iomFxns = (IOM_Fxns *) DEV_getFxns(
                        instHandle->acDevHandle[i]);
                    devicepointer = DEV_getDevp(instHandle->acDevHandle[i]);

                    retVal = ((IOM_Fxns *) iomFxns)->mdCreateChan(
                        (Ptr *) &chanHandle->aiAudioCodecHandle[i],
                        devicepointer,
                        remName,
                        mode,
                        (Ptr) (&chanHandle->aiChannelConfig.acChannelConfig[i]),
                        cbFxn,
                        cbArg);

                    if((NULL == chanHandle->aiAudioCodecHandle[i]) &&
                       (IOM_COMPLETED != retVal))
                    {
                        retVal    = IOM_EBADARGS;
                        breakLoop = (Bool) TRUE;
                    }
                    else
                    {
                        /* query the codec information and store it in the    *
                         * driver object                                      */
                        retVal = ((IOM_Fxns *) iomFxns)->mdControlChan(
                            (Ptr) chanHandle->aiAudioCodecHandle[i],
                            IOCTL_AIC31_AC_GET_CODEC_INFO,
                            (Ptr) & instHandle->acCodecData[i]);

                        if(IOM_COMPLETED != retVal)
                        {
                            breakLoop = (Bool) TRUE;
                        }
                    }
                }
                if((Bool) TRUE == breakLoop)
                {
                    break;
                }
            }
            /* for */

            if(IOM_COMPLETED == retVal)
            {
                remName = DEV_match(instHandle->adDevName,
                                    &instHandle->adDevHandle);

                if((NULL == instHandle->adDevHandle) || (NULL == remName))
                {
                    retVal = IOM_EBADARGS;
                }
                else
                {
                    iomFxns = (IOM_Fxns *) DEV_getFxns(
                        instHandle->adDevHandle);
                    devicepointer = DEV_getDevp(instHandle->adDevHandle);
                    retVal        = ((IOM_Fxns *) iomFxns)->mdCreateChan(
                        &(chanHandle->aiAudioChanHandle),
                        devicepointer,
                        remName,
                        mode,
                        (Ptr) chanHandle->aiChannelConfig.chanParam,
                        cbFxn,
                        (Ptr) cbArg);

                    if(NULL == chanHandle->aiAudioChanHandle)
                    {
                        retVal = IOM_EBADARGS;
                    }
                    else
                    {
                        /* query the audio information and store it in the     *
                         * driver object
                         *                                      */
                        retVal = ((IOM_Fxns *) iomFxns)->mdControlChan(
                            chanHandle->aiAudioChanHandle,
                            IOCTL_MCASP_GET_DEVINFO,
                            (Ptr) & instHandle->adAudioDevData);
                    }
                }
            }

            if(IOM_COMPLETED != retVal)
            {
                /* one of the open calls has failed hence set error status    */
                audioMdDeleteChan(chanHandle);

                /* enter critical section                                     */
                hwiKey = (Uint32) Hwi_disable();

                /* channel open failed hence set status as closed             */
                chanHandle->chanState = Audio_DriverState_CLOSED;

                /* Leave critical section                                     */
                Hwi_restore(hwiKey);
            }
        }
        else
        {
            /* Leave critical section                                         */
            Hwi_restore(hwiKey);

            /* Channel is already open                                        */
            retVal = IOM_EBADMODE;
        }

        if(IOM_COMPLETED != retVal)
        {
            *chanp = NULL;
        }
        else
        {
            *chanp = (Ptr) chanHandle;
        }
    }
    return ((Int) retVal);
}

/**
 *  \brief   Submits a I/O packet to a channel for processing
 *
 *  The stream layer calls this function to cause the IDriver
 *  to process the IOM_Packet for read/write operations.
 *
 *  This function calls the submit function of the audio device to submit the
 *  data to the audio transport device.
 *
 *  \param   chanp         [IN]    Pointer to channel
 *  \param   ioPacket      [IN]    Pointer to packet to be submitted
 *
 *  \return  IOM_COMPLETED,
 *                       if packet is fully processed
 *           IOM_ERROR,
 *                       in case of error
 *
 * \entry    chanp should be a valid non NULL pointer
 *           ioPacket is a non NULL and valid pointer,
 *
 * \leave    Not implemented
 *
 */
static Int audioMdSubmitChan(Ptr chanp, IOM_Packet *ioPacket)
{
    Audio_Object         *instHandle = NULL;
    Audio_Channel_Object *chanHandle = NULL;
    Int32 retVal = IOM_COMPLETED;
    IOM_Fxns             *iomFxns;

    /* Begin parameter checking
     *                                                  */
#ifndef PSP_DISABLE_INPUT_PARAMETER_CHECK
    if((NULL == chanp) || (NULL == ioPacket))
    {
        retVal = IOM_EBADARGS;
    }
    else
    {
#endif

    chanHandle = (Audio_Channel_Object *) chanp;
    instHandle = (Audio_Object *) chanHandle->devHandle;

#ifndef PSP_DISABLE_INPUT_PARAMETER_CHECK
    if(NULL == instHandle)
    {
        retVal = IOM_EBADARGS;
    }
}

#endif /* PSP_DISABLE_INPUT_PARAMETER_CHECK */
       /* End parameter checking
        *                                                    */

    if(IOM_COMPLETED == retVal)
    {
        /* process the request */
        if((IOM_READ == ioPacket->cmd) ||
           (IOM_WRITE == ioPacket->cmd) ||
           (IOM_ABORT == ioPacket->cmd) ||
           (IOM_FLUSH == ioPacket->cmd))
        {
            iomFxns = (IOM_Fxns *) DEV_getFxns(instHandle->adDevHandle);
            /* call the function for the audio device submit                  */
            retVal = ((IOM_Fxns *) iomFxns)->mdSubmitChan(
                chanHandle->aiAudioChanHandle,
                ioPacket);
        }
    }

    return ((Int) retVal);
}
/**
 *  \brief  Implements the IOCTLS for Audio interface driver by calling
 *          the Ioctl functions of the audio device and codecs.
 *
 *          Audio_control() recieves IOCTL commands from the stream layer
 *          and then forwards the commands to the audio device Ioctl or audio
 *          codec ioctl by calling the respective functions provided by their
 *          drivers.
 *
 *  \param  chanp       [IN]    channel handle
 *  \param  cmd         [IN]    specific IOCTL command
 *  \param  cmdArg      [IN]    arguments required for specific commands
 *
 *  \return None
 *
 *  \enter  chanp is not NULL and is a valid pointer,
 *          cmd is a valid IOCTL command,
 *          cmdArgs are valid as appropriate for the command passed,
 *
 *  \leave  Not implemented
 *
 */
static Int audioMdControlChan(Ptr chanp, Uns cmd, Ptr cmdArgs)
{
    Audio_Object         *instHandle = NULL;
    Audio_Channel_Object *chanHandle = NULL;
    Audio_IoctlParam     *cmdArg     = NULL;
    Ptr hdevHandle = NULL;
    Int32 retVal   = IOM_COMPLETED;
    IOM_Fxns             *iomFxns;

    /* Begin parameter checking
     *                                                  */
#ifndef PSP_DISABLE_INPUT_PARAMETER_CHECK
    Uint32 hwiKey = 0;

    if((NULL == chanp) || (NULL == cmdArgs))
    {
        retVal = IOM_EBADARGS;
    }
    else
    {
#endif   /* PSP_DISABLE_INPUT_PARAMETER_CHECK */

    chanHandle = (Audio_Channel_Object *) chanp;
    instHandle = (Audio_Object *) chanHandle->devHandle;

#ifndef PSP_DISABLE_INPUT_PARAMETER_CHECK
    hwiKey = (Uint32) Hwi_disable();
    if((NULL == instHandle) ||
       (Audio_DriverState_OPENED != chanHandle->chanState))
    {
        Hwi_restore(hwiKey);
        retVal = IOM_EBADARGS;
    }
    else
    {
        Hwi_restore(hwiKey);
    }
}

#endif  /* PSP_DISABLE_INPUT_PARAMETER_CHECK */
    /* End parameter checking
     *                                                    */

    if(IOM_COMPLETED == retVal)
    {
        cmdArg = (Audio_IoctlParam *) cmdArgs;

        /* check the device to pass the command to and call the function      */
        if(AUDIO_IOCTL_SAMPLE_RATE == cmd)
        {
            retVal = (Int32) audioSampleRateConfigure(
                instHandle,
                ((Uint32) cmdArg->ioctlArg));
        }
        else
        {
            if(AUDIO_MODULESEL_AUDIO_DEVICE == cmdArg->aiModule)
            {
                /* if the command is to be passed to the audio dev            */
                hdevHandle = chanHandle->aiAudioChanHandle;

                if(NULL != hdevHandle)
                {
                    iomFxns = (IOM_Fxns *) DEV_getFxns(instHandle->adDevHandle);
                    /* call the function for the audio device Ioctl           */
                    retVal = (Int32) ((IOM_Fxns *) iomFxns)->mdControlChan(
                        hdevHandle,
                        cmd,
                        (Ptr) cmdArg->ioctlArg);
                }
                else
                {
                    retVal = IOM_EBADARGS;
                }
            }
            else if(AUDIO_MODULESEL_AUDIO_CODEC == cmdArg->aiModule)
            {
                /* if the command is to be passed to the audio codec          */
                hdevHandle =
                    (Ptr) chanHandle->aiAudioCodecHandle[cmdArg->codecId];

                if(NULL != hdevHandle)
                {
                    iomFxns =
                        (IOM_Fxns *) DEV_getFxns(
                            instHandle->acDevHandle[cmdArg->codecId]);

                    /* call the function for the audio codec Ioctl            */
                    retVal = (Int32) ((IOM_Fxns *) iomFxns)->mdControlChan(
                        hdevHandle,
                        cmd,
                        (Ptr) cmdArg->ioctlArg);
                }
                else
                {
                    retVal = IOM_EBADARGS;
                }
            }
            else
            {
                /* Error condition : usually this condition should not occur  *
                 * klokwork gives an error here but this is retained to handle*
                 * spurious errors                                            */
                retVal = IOM_EBADARGS;
            }
        }
    }

    return ((Int) retVal);
}

/**
 *  \brief  closes an open audio channel.
 *
 *          This function closes an open channel after which the channel is not
 *          available for further transactions. it deallocates all the assigned
 *          resources and marks the channel as closed.
 *
 *  \param  chanp      [IN]    channel handle
 *
 *  \return None
 *
 *  \enter  chanp is not NULL and is a valid pointer,
 *
 *  \leave  Not implemented
 */
static Int audioMdDeleteChan(Ptr chanp)
{
    Audio_Object *instHandle = NULL;
    Audio_Channel_Object     *chanHandle = NULL;
    Uint8         count  = 0;
    Uint32        hwiKey = 0;
    Int32         retVal = IOM_COMPLETED;
    IOM_Fxns     *iomFxns;

    /* Begin parameter checking
     *                                                  */
#ifndef PSP_DISABLE_INPUT_PARAMETER_CHECK
    if(NULL == chanp)
    {
        retVal = IOM_EBADARGS;
    }
    else
    {
#endif    /* PSP_DISABLE_INPUT_PARAMETER_CHECK */
    chanHandle = (Audio_Channel_Object *) chanp;
    instHandle = (Audio_Object *) chanHandle->devHandle;

#ifndef PSP_DISABLE_INPUT_PARAMETER_CHECK
    hwiKey = (Uint32) Hwi_disable();
    if((NULL == instHandle) ||
       (Audio_DriverState_OPENED != chanHandle->chanState))
    {
        Hwi_restore(hwiKey);
        retVal = IOM_EBADARGS;
    }
    else
    {
        Hwi_restore(hwiKey);
    }
}

#endif  /* PSP_DISABLE_INPUT_PARAMETER_CHECK */
    /* End parameter checking
     *                                                    */

    if(IOM_COMPLETED == retVal)
    {
        iomFxns = (IOM_Fxns *) DEV_getFxns(instHandle->adDevHandle);

        /* close the audio device and then close the codec devices            */
        /* match the driver name from the driver table                        */
        retVal = (Int32) ((IOM_Fxns *) iomFxns)->mdDeleteChan(
            (Ptr) chanHandle->aiAudioChanHandle);

        /* close the codec devices here                                       */
        for(count = 0; count < instHandle->acNumCodecs; count++)
        {
            iomFxns = (IOM_Fxns *) DEV_getFxns(instHandle->acDevHandle[count]);
            retVal  = ((IOM_Fxns *) iomFxns)->mdDeleteChan(
                (Ptr) chanHandle->aiAudioCodecHandle[count]);

            if(IOM_COMPLETED != retVal)
            {
                break;
            }
        }

        hwiKey = (Uint32) Hwi_disable();
        /* if the audio device and the codec have been deleted sucessfully    *
         * then we will set the status of the channel to deleted else the     *
         * error status will be returned to the caller                        */
        if(IOM_COMPLETED == retVal)
        {
            chanHandle->chanState = Audio_DriverState_CLOSED;
        }
        Hwi_restore(hwiKey);
    }

    return ((Int) retVal);
}
/**
 *  \brief  function called by bios during closing down of the instance.
 *
 *          This function closes the instance by deallocating all the resources
 *          allocated to it.This function marks the instance as not in use
 *          and free to be allocated. it also sets the state of the driver
 *          instance as deleted
 *
 *
 *  \param  instHandle [IN]    pointer to the Driver object
 *
 * \return  None
 *
 * \enter   instHandle is not NULL and is a valid pointer,
 *
 * \leave   Not implemented
 */
static Int audioMdUnBindDev(Ptr devp)
{
    Audio_Object *instHandle = NULL;
    Uint32        hwiKey     = 0;
    Int32         retVal     = IOM_COMPLETED;

    /* Begin parameter checking
     *                                                  */
#ifndef PSP_DISABLE_INPUT_PARAMETER_CHECK
    if(NULL == devp)
    {
        retVal = IOM_EBADARGS;
    }
#endif
    /* End parameter checking
     *                                                    */
    if(IOM_COMPLETED == retVal)
    {
        instHandle = (Audio_Object *) devp;

        if((Uint8)AUDIO_NUMINSTANCES <= instHandle->instNum)
        {
            retVal = IOM_EBADARGS;
        }

        if(IOM_COMPLETED == retVal)
        {
            hwiKey = (Uint32) Hwi_disable();

            if((Audio_DriverState_CREATED == instHandle->devState)
               && (Audio_DriverState_CLOSED == instHandle->ChanObj[0].chanState)
               && (Audio_DriverState_CLOSED == instHandle->ChanObj[1].chanState))
            {
                instHandle->devState = Audio_DriverState_DELETED;
                Audio_module.inUse[instHandle->instNum] = (Bool) FALSE;
            }

            Hwi_restore(hwiKey);
        }
    }
    return ((Int) retVal);
}

/* ========================================================================== */
/*                           LOCAL FUNCTIONS                                  */
/* ========================================================================== */

/**
 *
 * \brief  function used to configure the sample rate of the audio configuration
 *
 *         This function changes the sample rate for the audio configuration.it
 *         first stops the state machine of the codec and the audio device and
 *         then reconfigures the sample rate for the devices.it then
 *         restarts the required devices.please note that in case that the TX
 *         and RX sections are in sync,the sampling frequencies of both the
 *         sections are modified.
 *
 *
 * \param  instHandle [IN]  pointer to the Driver object
 * \param  sampleRate [IN]  sample rate to configure
 * \param  eb         [IN]  pointer to the error block
 *
 * \return IOM_COMPLETED - in case of sucess,
 *         IOM error code in case of error
 *
 * \enter  instHandle  is not NULL and is a valid pointer,
 *         sampleRate  is a valid sample rate
 *         eb          can be any value,in case the value is non null then the
 *                     application will receive updated error information block
 *                     in case of an error, if eb is NULL the program will
 *                     terminate the execution at the place where Error has
 *                     occured and an appropriate error message is logged.
 *
 * \leave  Not implemented
 */

static Int audioSampleRateConfigure(Audio_Object *instHandle,
                                    Uint32        ioctlArg)
{
    Uint32    acCount = 0;
    Int32     retVal  = IOM_COMPLETED;
    IOM_Fxns *iomFxns;

    assert(NULL != instHandle);

    /* To change the sample rate we need to first stop the audio device and   *
     * then check which device is master.We then need to send the command to  *
     * the master device to reconfigure the sample rate.Also we need to       *
     * restart the Audio device after that                                    */

    iomFxns = (IOM_Fxns *) DEV_getFxns(instHandle->adDevHandle);

    /* stop the Mcasp driver both channels                                   */
    retVal = (Int32) ((IOM_Fxns *) iomFxns)->mdControlChan(
        instHandle->ChanObj[0].aiAudioChanHandle,
        IOCTL_MCASP_STOP_PORT,
        NULL);

    if(IOM_COMPLETED == retVal)
    {
        retVal = ((IOM_Fxns *) iomFxns)->mdControlChan(
            instHandle->ChanObj[1].aiAudioChanHandle,
            IOCTL_MCASP_STOP_PORT,
            NULL);
    }

    if(IOM_COMPLETED == retVal)
    {
        /* send the command to Mcasp if it is the master                      */
        if(TRUE == instHandle->adAudioDevData.isMaster)
        {
            /* change the mcasp sample rate                                   */
            retVal = ((IOM_Fxns *) iomFxns)->mdControlChan(
                instHandle->ChanObj[0].aiAudioChanHandle,
                IOCTL_MCASP_SET_SAMPLE_RATE,
                (Ptr) ioctlArg);

            if(IOM_COMPLETED == retVal)
            {
                retVal = ((IOM_Fxns *) iomFxns)->mdControlChan(
                    instHandle->ChanObj[1].aiAudioChanHandle,
                    IOCTL_MCASP_SET_SAMPLE_RATE,
                    (Ptr) ioctlArg);
            }
        }
        else
        {
            /* codec is the master. search through the codecs and set the     *
             * sample rate for that codec                                     */

            for(acCount = 0; acCount < instHandle->acNumCodecs; acCount++)
            {
                iomFxns =
                    (IOM_Fxns *) DEV_getFxns(instHandle->acDevHandle[acCount]);

                if(ICodec_OpMode_MASTER
                   == instHandle->acCodecData[acCount].acOpMode)
                {
                    /* we found the master codec.Hence send the command for
                     *       *
                     * changing the sample rate
                     *                                  */
                    retVal = ((IOM_Fxns *) iomFxns)->mdControlChan(
                        (Ptr) instHandle->ChanObj[0].aiAudioCodecHandle[acCount
                        ],
                        IOCTL_AIC31_AC_SET_SAMPLERATE,
                        (Ptr) ioctlArg);

                    if(IOM_COMPLETED == retVal)
                    {
                        retVal = ((IOM_Fxns *) iomFxns)->mdControlChan(
                            (Ptr) instHandle->ChanObj[1].aiAudioCodecHandle[
                                acCount],
                            IOCTL_AIC31_AC_SET_SAMPLERATE,
                            (Ptr) ioctlArg);
                    }
                    /* only one master per configuration hence we will break now
                     * */
                    break;
                }
            }
        }

        if(IOM_COMPLETED == retVal)
        {
            iomFxns = (IOM_Fxns *) DEV_getFxns(instHandle->adDevHandle);

            /* start the Mcasp driver
             *                                            */
            retVal = ((IOM_Fxns *) iomFxns)->mdControlChan(
                instHandle->ChanObj[1].aiAudioChanHandle,
                IOCTL_MCASP_START_PORT,
                NULL);

            retVal = ((IOM_Fxns *) iomFxns)->mdControlChan(
                instHandle->ChanObj[0].aiAudioChanHandle,
                IOCTL_MCASP_START_PORT,
                NULL);
        }
    }

    return (Int) retVal;
}

/* ========================================================================== */
/*                             END OF FILE                                    */
/* ========================================================================== */
