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

/*
 *  ======== ti/psp/platforms/evmOMAPL137/audio/Audio.h ========
 */
#ifndef AUDIOLOCAL_H_
#define AUDIOLOCAL_H_

#include <xdc/std.h>
#include <ti/sysbios/io/GIO.h>
#include <ti/sysbios/io/DEV.h>

#ifdef __cplusplus
extern "C" {
#endif

/* -------- typedef enums -------- */

/**
 *   \brief Audio driver state
 *
 *  Audio driver state enums used to track the driver state.
 */
typedef enum
{
    Audio_DriverState_DELETED,
    Audio_DriverState_CREATED,
    Audio_DriverState_INITIALIZED,
    Audio_DriverState_OPENED,
    Audio_DriverState_CLOSED,
    Audio_DriverState_DEINITIALIZED,
    Audio_DriverState_POWERED_DOWN
}Audio_DriverState;

/* -------- typedef structs -------- */

/**
 *  \brief Audio inteface channel object structure
 */
typedef struct
{
    Audio_DriverState   chanState;
    /**< status of the channel (open /closed)                                 */

    Ptr                 aiAudioChanHandle;
    /**< The handle to the audio device (RX/TX mode)                          */

    Uint32              aiAudioCodecHandle[AUDIO_NUMCODECINSTANCES];
    /**< The handles to all the audio codecs                                  */

    IOM_TiomCallback    cbFxn;
    /**< call back function                                                   */

    Ptr                 cbArg;
    /**< Callback Function argument                                           */

    Audio_ChannelConfig aiChannelConfig;
    /**< The audio interface channel configuration params                     */

    Ptr                 devHandle;
    /**< instance handle                                                      */
}Audio_Channel_Object;

/* -------- module-wide state -------- */

/**
 *  \brief Audio module object structure
 */
typedef struct {
    Bool *inUse;
} Audio_Module_State;

/* -------- per-instance state -------- */

/**
 *  \brief Audio Interface instance local data structure.
 *
 *  This structure contains the audio interface driver local data. it
 *  stores all the information related to the initialisation parameters.
 *  it also stores the channel parameters required during the opening of
 *  all the audio devices and the audio codecs. it stores within it the
 *  various handles required for communication with the audio devices
 *  and codecs(which are returned during the open call of respective
 *  drivers).
 */
typedef struct
{
    Uint8                instNum;
    /**< instance number of the audio interface                               */

    Audio_DriverState    devState;
    /**<  The current status of the instance (created/deleted)                */

    Audio_DeviceType     adDevType;
    /**< Identifies the type of audio device (McASP/McBSP)                    */

    String               adDevName;
    /**< Name of the audio device used during the creation and  addition of
     * the driver to the driver table.
     *                                           */

    DEV_Handle           adDevHandle;
    /**< Handle to the Audio device IDriver                                   */

    Mcasp_AudioDevData   adAudioDevData;
    /**< Information related to the audio device                              */

    Uint8                acNumCodecs;
    /**< Number of audio codec instance                                       */

    String               acDevName[AUDIO_NUMCODECINSTANCES];
    /**< handle to the audio codec returned during bind function              */

    DEV_Handle           acDevHandle[AUDIO_NUMCODECINSTANCES];
    /**< Handle to the Audio codec IDriver                                    */

    ICodec_CodecData     acCodecData[AUDIO_NUMCODECINSTANCES];
    /**< Information related to the codec                                     */

    Audio_Channel_Object ChanObj[AUDIO_NUM_CHANS];
    /**<  AI channel configuration information object                         */
} Audio_Object;

#ifdef __cplusplus
}
#endif

#endif  /*AUDIOLOCAL_H_ */

