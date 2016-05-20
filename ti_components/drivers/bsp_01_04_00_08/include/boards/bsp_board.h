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
 *  \defgroup BSP_DRV_BOARD_API Board API
 *
 *  This module defines APIs for board specific features.
 *
 *  @{
 */

/**
 *  \file bsp_board.h
 *
 *  \brief Board related API.
 */

#ifndef BSP_BOARD_H_
#define BSP_BOARD_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <fvid2/fvid2_dataTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Invalid instance ID. */
#define BSP_BOARD_INVALID_INST_ID   (0xFFU)

/** \brief Driver ID for drivers other than video. */
/* Caution: These Ids should not clash with fvid2 driver ids */
#define BSP_DRV_ID_MISC_BASE        ((UInt32) 0x00002000)

/** \brief Driver ID for UART Driver. */
#define BSP_DRV_ID_UART             (BSP_DRV_ID_MISC_BASE + (UInt32) 0x00U)

/** \brief Driver ID for I2C Driver. */
#define BSP_DRV_ID_I2C              (BSP_DRV_ID_MISC_BASE + (UInt32) 0x10U)

/** \brief Driver ID for MCSPI Driver. */
#define BSP_DRV_ID_MCSPI            (BSP_DRV_ID_MISC_BASE + (UInt32) 0x20U)

/** \brief Driver ID for MCASP Driver. */
#define BSP_DRV_ID_MCASP            (BSP_DRV_ID_MISC_BASE + (UInt32) 0x30U)

/** \brief Driver ID for Ethernet Driver. */
#define BSP_DRV_ID_ENET             (BSP_DRV_ID_MISC_BASE + (UInt32) 0x40U)

/** \brief Driver ID for Ethernet Phy DP83865 driver. */
#define BSP_DRV_ID_ENET_PHY_DP83865 (BSP_DRV_ID_MISC_BASE + (UInt32) 0x50U)

/** \brief Driver ID for MMC Driver. */
#define BSP_DRV_ID_MMC              (BSP_DRV_ID_MISC_BASE + (UInt32) 0x60U)

/**
 *  \brief EVM Board ID.
 */
typedef enum
{
    BSP_BOARD_UNKNOWN = 0x0001U,
    /**< Unknown board. */
    BSP_BOARD_VS = 0x0002U,
    /**< Video survillance based board. */
    BSP_BOARD_VC = 0x0004U,
    /**< Video conferencing based board. */
    BSP_BOARD_VISION = 0x0008U,
    /**< Vision board of TDA2XX family. */
    BSP_BOARD_VISION_TI81XX = 0x0010U,
    /**< Vision board of TI81XX family. */
    BSP_BOARD_CATALOG = 0x0020U,
    /**< TVP7002/SIL1161A. */
    BSP_BOARD_CUSTOM = 0x0040U,
    /**< Any other custom board. */
    BSP_BOARD_JAMR3 = 0x0080U,
    /**< JAMR3 board of TDA2XX family. */
    BSP_BOARD_MULTIDES = 0x0100U,
    /**< Multi Deserializer board of TDA2XX family. */
    BSP_BOARD_BASE_TDA2XX = 0x0200U,
    /**< TDA2XX Base Board. */
    BSP_BOARD_BASE_TDA3XX = 0x0400U,
    /**< TDA3XX Base Board. */
    BSP_BOARD_BASE_TI81XX = 0x0800U,
    /**< TI81XX Base Board. */
    BSP_BOARD_BASE_TDA2EX = 0x1000U,
    /**< TDA2EX Base Board. */
    BSP_BOARD_MONSTERCAM = 0x2000U,
    /**< Monster-Camera Base Board. */
    BSP_BOARD_MAX = 0xFFFFU
                    /**< Max board ID. */
} Bsp_BoardId;

/**
 *  \brief Board revision ID.
 */
typedef enum
{
    BSP_BOARD_REV_UNKNOWN,
    /**< Unknown/unsupported board revision. */
    BSP_BOARD_REV_A,
    /**< Board revision A. */
    BSP_BOARD_REV_B,
    /**< Board revision B. */
    BSP_BOARD_REV_C,
    /**< Board revision C. */
    BSP_BOARD_REV_D,
    /**< Board revision D. */
    BSP_BOARD_REV_E,
    /**< Board revision E. */
    BSP_BOARD_REV_MAX
    /**< Max board revision. */
} Bsp_BoardRev;

/**
 *  \brief Device specific modes
 */
typedef enum
{
    BSP_BOARD_MODE_DEFAULT,
    /**< This enum could be passed if the mode is a don't care and the
     *   mode select function returns success after selecting the default
     *   mode (if applicable). */
    BSP_BOARD_MODE_VIDEO_24BIT,
    /**< 24-bit video mode. */
    BSP_BOARD_MODE_VIDEO_16BIT,
    /**< 16-bit video mode. */
    BSP_BOARD_MODE_VIDEO_14BIT,
    /**< 14-bit video mode. */
    BSP_BOARD_MODE_VIDEO_12BIT,
    /**< 12-bit video mode. */
    BSP_BOARD_MODE_VIDEO_10BIT,
    /**< 10-bit video mode. */
    BSP_BOARD_MODE_VIDEO_8BIT,
    /**< 8-bit video mode. */
    BSP_BOARD_MODE_VIDEO_8BIT_TDM,
    /**< 8-bit TDM (RGB interleaved) video mode. */
    BSP_BOARD_MODE_VIDEO_BT656,
    /**< 8-bit BT656 video mode. */
    BSP_BOARD_MODE_VIDEO_BT1120,
    /**< 16-bit BT1120 video mode. */
    BSP_BOARD_MODE_MAX
    /**< Max board modes. */
} Bsp_BoardMode;

/**
 *  \brief Function pointer typedef for custom board initialization
 */
typedef Int32 (*Bsp_BoardCustomInitFxn)(void);

/**
 *  \brief Function pointer typedef for custom board set pin mux
 */
typedef Int32 (*Bsp_BoardSetPinMuxFxn)(UInt32 drvId,
                                       UInt32 instId,
                                       Bsp_BoardMode boardMode);

/**
 *  \brief Function pointer typedef for device select function per board.
 */
typedef Int32 (*Bsp_BoardSelectDeviceFxn)(UInt32 devDrvId, UInt32 instId);

/**
 *  \brief Function pointer typedef for custom board select mode
 */
typedef Int32 (*Bsp_BoardSelectModeFxn)(UInt32 devDrvId,
                                        UInt32 instId,
                                        Bsp_BoardMode boardMode);

/**
 *  \brief Function pointer typedef for device reset function per board.
 */
typedef Int32 (*Bsp_BoardResetDeviceFxn)(UInt32 devDrvId, UInt32 instId);

/**
 *  \brief Function pointer typedef for device power on function per board.
 */
typedef Int32 (*Bsp_BoardPowerOnDeviceFxn)(UInt32 devDrvId,
                                           UInt32 instId,
                                           UInt32 powerOn);

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Board specific per instance I2C related data.
 */
typedef struct
{
    UInt32 instId;
    /**< I2C controller number. */
    UInt32 baseAddr;
    /**< I2C peripheral base address. */
    UInt32 intNum;
    /**< I2C Interrupt number. */
    UInt32 busClkKHz;
    /**< I2C bus clock in KHz. */
} Bsp_BoardI2cInstData;

/**
 *  \brief Board specific data.
 */
typedef struct
{
    UInt32                numInst;
    /**< Number of I2C instance to initialize. */
    Bsp_BoardI2cInstData *instData;
    /**< Pointer to #numInst number of I2C board data. */
    UInt32                probeInstId;
    /**< I2C instance to use for board detect. */
} Bsp_BoardI2cData;

/**
 *  \brief Board specific per instance device related data.
 */
typedef struct
{
    UInt32                    devDrvId;
    /**< Device driver ID. */
    UInt32                    instId;
    /**< Instance ID - 0 to max-1 in a board. */
    UInt32                    i2cInstId;
    /**< I2C instance the device is connected to. */
    UInt32                    i2cAddr;
    /**< I2C address of the device. */
    UInt32                    drvId;
    /**< Capture/display driver ID to which the device is connected to. */
    UInt32                    drvInstId;
    /**< Capture/display driver instance to which the device is connected to. */
    Bsp_BoardSelectDeviceFxn  selectDev;
    /**< Select device function pointer. This function will power on the
     *   device, do the device reset sequence and also enable any board level
     *   mux for the provided device. */
    Bsp_BoardResetDeviceFxn   resetDev;
    /**< Reset device function pointer. This function will do the device reset
     *   sequence as per the board information. */
    Bsp_BoardPowerOnDeviceFxn powerOnDev;
    /**< Power On device function pointer. This function will do the Powering on
     *   the device as per the board information. */
} Bsp_BoardDeviceData;

/**
 *  \brief Board specific data.
 */
typedef struct
{
    UInt32                     numDev;
    /**< Number of deviced connected to the board. */
    const Bsp_BoardDeviceData *devData;
    /**< Pointer to #numDev number of device data. */
} Bsp_BoardData;

/**
 *  \brief Custom board parameters
 */
typedef struct
{
    const Char *boardIdString;
    /**< Custom board ID string. Note: This can't be NULL */
    const Char *boardRevString;
    /**< Custom board revision string. Note: This can't be NULL */
    const Bsp_BoardI2cData *i2cData;
    /**< Custom board I2C data. Note: This can't be NULL */
    const Bsp_BoardData *boardData;
    /**< Custom board device data. Note: This can't be NULL */
    Bsp_BoardCustomInitFxn initFxn;
    /**< Custom board initialization function. This can be NULL is no init is
     *   required for custom board */
    Bsp_BoardSetPinMuxFxn setPinMuxFxn;
    /**< Custom board set pin mux function. This can be NULL is no pin mux is
     *   required for custom board */
    Bsp_BoardSelectModeFxn selectModeFxn;
    /**< Custom board select mode function. This can be NULL is no mode select
     *   is required for custom board */
} Bsp_BoardCustomData;

/**
 *  \brief Board initialization parameters.
 */
typedef struct
{
    Bsp_BoardId  boardId;
    /**< Override board ID detection. Set this to #BSP_BOARD_MAX to allow
     *   auto detection of the board connected. Setting any other value will
     *   override the auto detect and force the board ID to the supplied
     *   value. */
    Bsp_BoardRev baseBoardRev;
    /**< Override base board revision detection. Set this to #BSP_BOARD_REV_MAX
     *   to allow auto detection of base board revision. Setting any other
     *   value will override the auto detect and force the revision to the
     *   supplied value. */
    Bsp_BoardRev dcBoardRev;
    /**< Override daughter card board revision detection. Set this to
     *   #BSP_BOARD_REV_MAX to allow auto detection of DC board revision.
     *   Setting any other value will override the auto detect and force
     *   the revision to the supplied value. */
    Bsp_BoardCustomData *customData;
    /**< Override auto-detection and calling of built in board support functions
     *   and data with custom board implementation. Set to NULL if not used.
     *   Note: When this param is set, boardId, baseBoardRev and dcBoardRev
     *   should be set valid values other than BSP_BOARD_MAX/BSP_BOARD_REV_MAX
     *   so that the board module doesn't do auto-detect. */
} Bsp_BoardInitParams;

/* ========================================================================== */
/*                         Functions                                          */
/* ========================================================================== */

/**
 *  \brief Init the underlying board.
 *
 *  \param initPrms     [IN] Board Initialization parameters.
 *
 *  \return BSP_SOK on success, else appropriate error code on failure.
 */
Int32 Bsp_boardInit(const Bsp_BoardInitParams *initPrms);

/**
 *  \brief De-init the underlying platform.
 *
 *  \param args         [IN] Not used currently. Set to NULL.
 *
 *  \return BSP_SOK on success, else appropriate error code on failure.
 */
Int32 Bsp_boardDeInit(Ptr args);

/**
 *  \brief Probes for video device and return board ID
 *
 *  \return Board ID on success
 */
Bsp_BoardId Bsp_boardGetId(void);

/**
 *  \brief Returns the base board revision.
 *
 *  \return Base board revision information on success.
 */
Bsp_BoardRev Bsp_boardGetBaseBoardRev(void);

/**
 *  \brief Returns the add-on or daughter card board revision.
 *
 *  \return Add-on or daughter card board revision information on success.
 */
Bsp_BoardRev Bsp_boardGetDcRev(void);

/**
 *  \brief Returns I2C data.
 */
const Bsp_BoardI2cData *Bsp_boardGetI2cData(void);

/**
 *  \brief Returns board specific data.
 */
const Bsp_BoardData *Bsp_boardGetData(void);

/**
 *  \brief Returns the device instance to which the video device is connected
 *  corresponding capture/display driver and instance.
 *
 *  \param devDrvId     [IN] Video device driver ID to get the info for.
 *  \param drvId        [IN] Driver ID to which the device is connected.
 *  \param drvInstId    [IN] Driver instance to which the device is connected.
 *
 *  \return Device instance if found else returns BSP_BOARD_INVALID_INST_ID.
 */
UInt32 Bsp_boardGetVideoDeviceInstId(UInt32 devDrvId,
                                     UInt32 drvId,
                                     UInt32 drvInstId);

/**
 *  \brief Returns the I2C instance to which the video device is connected
 *  corresponding capture/display driver and instance.
 *
 *  \param devDrvId     [IN] Video device driver ID to get the info for.
 *  \param drvId        [IN] Driver ID to which the device is connected.
 *  \param drvInstId    [IN] Driver instance to which the device is connected.
 *
 *  \return I2C instance if found else returns BSP_DEVICE_I2C_INST_ID_MAX.
 */
UInt32 Bsp_boardGetVideoDeviceI2cInstId(UInt32 devDrvId,
                                        UInt32 drvId,
                                        UInt32 drvInstId);

/**
 *  \brief Returns the video device I2C address connected to the corresponding
 *  capture/display driver and instance.
 *
 *  \param devDrvId     [IN] Video device driver ID to get the info for.
 *  \param drvId        [IN] Driver ID to which the device is connected.
 *  \param drvInstId    [IN] Driver instance to which the device is connected.
 *
 *  \return I2C address of the device if found else returns 0.
 */
UInt32 Bsp_boardGetVideoDeviceI2cAddr(UInt32 devDrvId,
                                      UInt32 drvId,
                                      UInt32 drvInstId);

/**
 *  \brief Perform Power On for the provided device through GPIO or I2C IO
 *  expander. If Power On is not needed this function returns success
 *  without reporting error.
 *
 *  \param devDrvId     [IN] Video device driver ID to power-on.
 *  \param instId       [IN] Instance ID. Used when multiple devices are
 *                           present in a board.
 *  \param powerOn      [IN] TRUE - power on, FALSE - power down
 *
 *  \return BSP_SOK on success, else appropriate error code on failure.
 */
Int32 Bsp_boardPowerOnDevice(UInt32 devDrvId, UInt32 instId, UInt32 powerOn);

/**
 *  \brief Enable board level mux for the provided device.
 *  If no muxing is needed this function returns success without reporting
 *  error.
 *
 *  \param devDrvId     [IN] Video device driver ID to select.
 *  \param instId       [IN] Instance ID. Used when multiple devices are
 *                           present in a board.
 *
 *  \return BSP_SOK on success, else appropriate error code on failure.
 */
Int32 Bsp_boardSelectDevice(UInt32 devDrvId, UInt32 instId);

/**
 *  \brief Perform reset for the provided device through GPIO or I2C IO
 *  expander. If reset is not needed this function returns success
 *  without reporting error.
 *
 *  \param devDrvId     [IN] Video device driver ID to reset.
 *  \param instId       [IN] Instance ID. Used when multiple devices are
 *                           present in a board.
 *
 *  \return BSP_SOK on success, else appropriate error code on failure.
 */
Int32 Bsp_boardResetDevice(UInt32 devDrvId, UInt32 instId);

/**
 *  \brief Sets particular mode specific to the device.
 *
 *  Note: This API should be called only after calling power on and select
 *  device functions as calling the device select function after this could
 *  set the mode to default.
 *
 *  \param devDrvId     [IN] Video device driver ID to set the mode.
 *  \param instId       [IN] Instance ID. Used when multiple devices are
 *                           present in a board.
 *  \param boardMode    [IN] Mode param.
 *
 *  \return BSP_SOK on success, else appropriate error code on failure.
 *          Note: This function returns BSP_SOK even if no mux programming
 *                is required for a particular mode of operation.
 */
Int32 Bsp_boardSelectMode(UInt32        devDrvId,
                          UInt32        instId,
                          Bsp_BoardMode boardMode);

/**
 *  \brief Enable the TVP7002 input filter.
 *
 *  \param instId       [IN] Instance ID. Used when multiple TVP7002 are
 *                           present in a board.
 *  \param standard     [IN] Input standard to the filter.
 *
 *  \return BSP_SOK on success, else appropriate error code on failure.
 */
Int32 Bsp_boardEnableTvp7002Filter(UInt32 instId, Fvid2_Standard standard);

/**
 *  \brief Function to get the name of the board in printable string.
 *
 *  \return Returns a const pointer to the string. If the board is not
 *  known, then it return the string as "UNKNOWN".
 */
const Char *Bsp_boardGetBoardString(void);

/**
 *  \brief Function to get the name of the base board revision in printable
 *  string.
 *
 *  \return Returns a const pointer to the string. If the base board revision is
 *  not known, then it return the string as "UNKNOWN".
 */
const Char *Bsp_boardGetBaseBoardRevString(void);

/**
 *  \brief Function to get the name of the daughter card revision in printable
 *  string.
 *
 *  \return Returns a const pointer to the string. If the daughter card revision
 *  is not known, then it return the string as "UNKNOWN".
 */
const Char *Bsp_boardGetDcRevString(void);

/**
 *  \brief Function to print all the board information like board type,
 *  board revision etc...
 */
void Bsp_boardPrintInfo(void);

/**
 *  \brief Bsp_BoardInitParams structure init function.
 *
 *  \param initPrms     [IN] Pointer to #Bsp_BoardInitParams structure.
 *
 */
static inline void BspBoardInitParams_init(Bsp_BoardInitParams *initPrms);

/**
 *  \brief This API is used for setting up the pinmux for the give interface
 *  and for the given instance of the driver.
 *
 *  \param drvId        [IN] Driver Id. Used to identify the driver
 *  \param instId       [IN] Instance ID. Used when multiple
 *                           instances of the same device are present.
 *  \param boardMode    [IN] Board Mode. Based on this board mode, pinmux
 *                           will be set, for example, for 8bit board mode,
 *                           pinmuxe will be selected 8 data pins.
 *
 *  \return BSP_SOK on success, else appropriate error code on failure.
 *          Note: This function returns BSP_SOK even if no mux programming
 *                is required for a particular mode of operation.
 */
Int32 Bsp_boardSetPinMux(UInt32 drvId,
                         UInt32 instId,
                         Bsp_BoardMode boardMode);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void BspBoardInitParams_init(Bsp_BoardInitParams *initPrms)
{
    if (NULL != initPrms)
    {
        initPrms->boardId      = BSP_BOARD_MAX;
        initPrms->baseBoardRev = BSP_BOARD_REV_MAX;
        initPrms->dcBoardRev   = BSP_BOARD_REV_MAX;
        initPrms->customData   = NULL;
    }

    return;
}

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef BSP_BOARD_H_ */

/* @} */
