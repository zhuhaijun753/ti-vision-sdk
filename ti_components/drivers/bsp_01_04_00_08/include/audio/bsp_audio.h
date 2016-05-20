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
 *  \defgroup BSP_DRV_AUDIO_API Audio Driver API
 *
 *  @{
 */

/**
 *  \file bsp_audio.h
 *
 *  \section    Introduction
 *
 *  \subsection    xxx    Purpose and Scope
 *  The purpose of this document is to explain the Audio driver written for
 *  SYS/BIOS 6.x
 *
 *
 *  \subsection    bbb    Audio driver
 *
 *  Driver to stream data to/from a Application and audio transport streams.
 *
 *  The audio transport devices like mcasp,mcbsp are connected to the codecs
 *  which allow audio data to be received and transmitted.
 *
 *  The audio devices like Mcasp,Mcbsp have individual device drivers to control
 *  the data. Also the application needs to configure the proper audio codecs
 *  connected to the appropriate audio device.
 *
 *  The configuration of audio codecs is usually achieved through the use of
 *  a control bus like I2c or SPI.
 *
 *  Hence the application needs to configure the audio device driver,audio
 *  codec driver andd a control bus.
 *
 *  Instead an audio interface driver acts as a class driver which allows all
 *  the above mentioned devices to be controlled through a single interface.
 *  The audio driver is compliant with the IDriver interface specified by the
 *  DSP BIOS operating system.
 *
 *  The audio driver allows all the audio device and codecs to be configured
 *  by using a single interface thereby simplifying the application
 *  significantly.
 *
 *  The audio interface driver is  completly compliant with theIOM
 *  interface.
 *
 *  Note : since the audio codec does not handle any data transactions. The
 *  submit call of the audio interface will only be routed directly to the
 *  underlying audio device
 *
 *  \subsection    ccc    SYS/BIOS System
 *  SYS/BIOS is a real time kernel provided by TI to use with its
 *  DSP processors.
 *
 *  \subsection    ddd   Compiler defines to add/remove features.
 *
 *  Define to turn OFF parameter checking.
 *  Use -DPSP_DISABLE_INPUT_PARAMETER_CHECK when building library
 *
 *  Define to turn OFF asserts. Use -DNDEBUG when building library.
 *
 *  \subsection    References
 *    -# SYS/BIOS driver development <b>SPRU616.pdf</b>
 *
 *  \file   bsp_audio.h
 *
 *  \brief  Audio interface definition
 *
 *  This file contains the interfaces, data types and symbolic definitions
 *  that are needed by the application to utilize the serivces of the Audio
 *  device driver.
 */
#ifndef BSP_AUDIO_H_
#define BSP_AUDIO_H_

#include <devices/bsp_audioICodec.h>

#ifdef __cplusplus
extern "C" {
#endif

/* -------- constants -------- */
/**
 *  \brief Total number of Audio_NUMINSTANCES
 */
#define AUDIO_NUMINSTANCES      (2U)
/**
 *  \brief Total number of Audio_NUMCODECINSTANCES
 */
#define AUDIO_NUMCODECINSTANCES (5U)
/**
 *  \brief  Audio_NUM_CHANS
 *
 *  Number of channels per Audio instance
 */
#define AUDIO_NUM_CHANS         (0x02U)

/* -------- typedef enums -------- */

/**
 *  \brief Audio Interface Device Types.
 *
 *  This enum defines the audio device types supported in the Audio
 *  Framework.
 */
typedef enum
{
    AUDIO_DEVICETYPE_MCASP,         /**< Audio Device is McASP                */
    AUDIO_DEVICETYPE_MCBSP,         /**< Audio Device is McBSP                */
    AUDIO_DEVICETYPE_VOICE_CODEC,   /**< Audio device is voice codec          */
    AUDIO_DEVICETYPE_UNKNOWN        /**< Audio device is unknown              */
}Audio_DeviceType;

/**
 *  \brief Audio Interface channel mode.
 *
 *  This enum defines the audio interface channel mode.
 */
typedef enum
{
    AUDIO_IOMODE_RX,
    /**< Audio Interface channel mode is Rx                                   */
    AUDIO_IOMODE_TX,
    /**< Audio Interface channel mode is Tx                                   */
    AUDIO_IOMODE_MAX
    /**< Max channel count                                                    */
}Audio_IoMode;

/**
 *  \brief Audio Interface module selection.
 *
 *  This enum defines the audio interface module selection (used in IOCTL).
 */
typedef enum
{
    AUDIO_MODULESEL_AUDIO_DEVICE,
    /**< Audio Interface module is Audio Device                               */

    AUDIO_MODULESEL_AUDIO_CODEC
    /**< Audio Interface module is Audio Codec                                */
}Audio_ModuleSel;

/**
 *  \brief Audio Interface Ioctl commands
 *
 *  This enum defines the audio interface module supported IOCTLS.
 */

typedef enum
{
    AUDIO_IOCTL_SAMPLE_RATE
    /**< Audio interface ioctl to change the sample rate                      */
}Audio_Ioctl;

/* -------- typedef structs -------- */

/**
 *  \brief Audio Interface channel Parameters.
 *
 *  This structure defines the audio interface channel parameters.
 *  This parameter is supplied with the open call of the Audio Interface.
 */
typedef struct
{
    Ptr                  chanParam;
    /**< Pointer to Rx/Tx channel parameter structure                         */

    ICodec_ChannelConfig acChannelConfig[0x05U];
    /**< Audio codec channel configuration data structures                    */
}Audio_ChannelConfig;

/**
 *  \brief Audio Interface IOCTL Parameters.
 *
 *  This structure defines the audio interface IOCTL parameters.
 *  This parameter is supplied with the IOCTL call of the Audio Interface.
 */
typedef struct
{
    Audio_ModuleSel aiModule;
    /**< Device type specification(Audio device or codec)                     */
    Uint32          codecId;
    /**< I2C slave address or SPI CS number.Used only when
     * command is for Audio Codec                                             */
    Ptr             ioctlArg;
    /**< Command Specific data                                                */
}Audio_IoctlParam;

/* -------- per-instance configs -------- */

typedef struct
{
    Audio_DeviceType adDevType;
    /**< Audio device Type                                                    */
    String           adDevName;
    /**< Name of sudioDevice in DEV table                                     */
    Uint8            acNumCodecs;
    /**< Number of codecs present                                             */
    String           acDevName[AUDIO_NUMCODECINSTANCES];
    /**< Name od codec in DEV table                                           */
}Audio_Params;

/**
 *  \brief Audio IOM_Fxns table
 *
 *  Driver function table to be used by applications.
 */
extern IOM_Fxns           Audio_IOMFXNS;

/**
 *  \brief Default Audio_Params struct
 *
 *  const Audio_Params Audio_PARAMS__C = {
 *
 *      (Uint8)0x0,                    instNum
 *
 *       Audio_DeviceType_McASP,       adDevType
 *
 *       "NONE",                       adDevName
 *
 *       (Uint8)0x1,                   acNumCodecs
 *
 *       "",                           acDevName
 *
 *  };
 */
extern const Audio_Params Audio_PARAMS;

/**
 *  \brief    Initializes Audio instances which are statically allocated
 *
 *  This function needs to ve be called at part of BIOS initialization by
 *  setting initFxn for that particular UDEV instance or by calling this
 *  function as part of user specific initFxn.
 */
Void Audio_init(Void);

#ifdef __cplusplus
}
#endif

#endif /*BSP_AUDIO_H_ */

/*  @}  */

