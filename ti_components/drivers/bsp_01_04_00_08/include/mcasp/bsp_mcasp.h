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
 *  \defgroup BSP_DRV_MCASP_API MCASP Driver API
 *
 *  @{
 */

/**
 *  \file bsp_mcasp.h
 *
 *  \brief     Introduction
 *
 *  Purpose and Scope
 *  The purpose of this document is to explain the McASP driver on the PSP
 *  Framework architecture written in SYS/BIOS for platform.
 *
 *  McASP Controller
 *  The multichannel audio serial port (McASP) functions as a general-purpose
 *  audio serial port optimized for the needs of multichannel audio
 *  applications. The McASP is useful for time-division multiplexed (TDM)
 *  stream, Inter-Integrated Sound (I2S) protocols, and intercomponent digital
 *  audio interface transmission (DIT). The McASP consists of transmit and
 *  receive sections that may operate synchronized, or completely independently
 *  with separate master clocks, bit clocks, and frame syncs, and using
 *  different transmit modes with different bit-stream formats. The McASP
 *  module also includes up to 16 serializers that can be individually enabled
 *  to either transmit or receive. In addition, all of the McASP pins can be
 *  configured as general-purpose input/output (GPIO) pins.
 *
 *  SYS/BIOS System
 *  SYS/BIOS is a real time kernel provided by TI to use with its
 *  DSP processors.
 *
 *  Compiler defines to add/remove features
 *
 *  Define to turn OFF parameter checking.
 *  Use -DPSP_DISABLE_INPUT_PARAMETER_CHECK when building library
 *
 *  References
 *  -# SYS/BIOS driver development <b>SPRU616.pdf</b>
 *
 *  \file   bsp_mcasp.h
 *
 */

#ifndef BSP_MCASP_H_
#define BSP_MCASP_H_

#include <mcasp.h>

#ifdef __cplusplus
extern "C" {
#endif

/* -------- constants -------- */

#define MCASP_CACHE_LENGTH  (UInt32) (128U)
/**< cache line length                                                        */

#define MCASP_NUMSERIALIZERS (UInt32) (16U)
/**< Number of serializers on mcasp                                           */

#define MCASP_GBLCTL_TIMEOUT  (UInt32) (30000U)
/**< The time to try (in Msec) before the GBLCTL register setting timeouts    *
 *   if the setting/resetting is done in a context other than a task this will*
 *   be used as a retry count rather than the MSec timeout                    */

/* -------- enums -------- */
/**
 *  \brief enumerated constants for the Transfer modes supported by Mcasp
 */
typedef enum
{
    MCASP_OPMODE_TDM = 0,                /**< TDM Mode for channel operation  */
    MCASP_OPMODE_DIT = 1                 /**< DIT Mode for channel operation  */
}Mcasp_OpMode;

/**
 *  \brief Enumeration for the MCASP serializer numbers
 */
typedef enum
{
    MCASP_SERIALIZERNUM_0 = 0,           /**< Serializer 0                   */
    MCASP_SERIALIZERNUM_1 = 1,           /**< Serializer 1                   */
    MCASP_SERIALIZERNUM_2 = 2,           /**< Serializer 2                   */
    MCASP_SERIALIZERNUM_3 = 3,           /**< Serializer 3                   */
    MCASP_SERIALIZERNUM_4 = 4,           /**< Serializer 4                   */
    MCASP_SERIALIZERNUM_5 = 5            /**< Serializer 5                   */
}Mcasp_SerializerNum;

/**
 *  \brief Enumerated constant for wordlength supported by the MCASP device
 */
typedef enum
{
    MCASP_WORDLENGTH_8  = 8U,           /**< Word length of 8 bits            */
    MCASP_WORDLENGTH_16 = 16U,          /**< Word length of 16 bits           */
    MCASP_WORDLENGTH_24 = 24U,          /**< Word length of 24 bits           */
    MCASP_WORDLENGTH_32 = 32U           /**< Word length of 32 bits           */
}Mcasp_WordLength;

/**
 * \brief Enum to specify the supported buffer formats.
 *
 * Interleaved and non-interleaved is standard format, this enumeration
 * captures the standard and custom data formats.
 */
typedef enum
{
    /* This mode is used for buffer containing the data in continous      *
     * memory locations where each sample is  "wordWidth" long. This      *
     * format is supported for following configurations                   *
     *
     * Single serializer in DSP mode.DIT mode also can use this format    *
     *                                                                    *
     * Note : interleaved and non interleaved does not apply for this     *
     * buffer format                                                      */
    MCASP_BUFFERFORMAT_1SER_1SLOT,

    /* This is used for transfer of data on a single serializer with      *
     * multiple slots.please note that the slot data is not interleaved   *
     * in this format.                                                    *
     *                                                                    *
     * TDM with single serializer and slots > 1 uses this format.DIT can  *
     * also use this format                                               */
    MCASP_BUFFERFORMAT_1SER_MULTISLOT_NON_INTERLEAVED,
    /* This is used for transfer of data on a single serializer with      *
     * multiple slots.please note that the slot data is interleaved       *
     * in this format.                                                    *
     *                                                                    *
     * TDM with single serializer and slots > 1 uses this format. DIT     *
     * mode can also be supported here                                    */
    MCASP_BUFFERFORMAT_1SER_MULTISLOT_INTERLEAVED,

    /* This is used for transfer of data on a single slot with  multiple  *
     * serializers enabled.please note that the serializer data is        *
     * interleaved in this format.                                        *
     *                                                                    *
     * DSP and DIT mode with multiple serializer uses this format         */
    MCASP_BUFFERFORMAT_MULTISER_1SLOT_SER_INTERLEAVED,

    /* This is used for transfer of data on a single slot with  multiple  *
     * serializers enabled.please note that the serializer data is        *
     * interleaved in this format.                                        *
     *                                                                    *
     * DSP and DIT mode with multiple serializer uses this format         */
    MCASP_BUFFERFORMAT_MULTISER_1SLOT_SER_NON_INTERLEAVED,

    /* This is used for transfer of data with  multiple serializers and   *
     * also multiple slots enabled.please note that the serializer data is*
     * interleaved in this format. The slot data is also interleaved      *
     * Refer to the user guide to view the sample data format.            *
     *
     * TDM and DIT mode with multiple serializer and multiple slots uses  *
     * this format                                                        */
    MCASP_BUFFERFORMAT_MULTISER_MULTISLOT_SEMI_INTERLEAVED_1,

    /* This is used for transfer of data with  multiple serializers and   *
     * also multiple slots enabled.please note that the serializer data is*
     * NOT interleaved in this format. The slot data is interleaved       *
     * Refer to the user guide to view the sample data format.            *
     *
     * TDM and DIT mode with multiple serializer and multiple slots uses  *
     * this format                                                        */
    MCASP_BUFFERFORMAT_MULTISER_MULTISLOT_SEMI_INTERLEAVED_2

    /* we are unable to support this buffer format because the MCASP gives*
     * tx underrun error.
     * When 2 serializers are configured in 2 slot mode each. The MCASP   *
     * even though it receives two 16 bit samples it considers it as only *
     * one 32 bit sample because of which it will always give an underrun *
     * error. Hence this buffer format cannot be supported                *
     * This is used for transfer of data with  multiple serializers and   *
     * also multiple slots enabled.please note that the slot data is      *
     * NOT interleaved in this format. The serializer data is interleaved *
     * Refer to the user guide to view the sample data format.            *
     *
     * TDM and DIT mode with multiple serializer and multiple slots uses  *
     * this format                                                        *
     * BufferFormat_MULTISER_MULTISLOT_SEMI_INTERLEAVED_3,
     */
}Mcasp_BufferFormat;

/* -------- typedefs -------- */
/**
 *  \brief structure to hold the error condition and the status
 *
 *  This is the structure which holds the error condition and also the error
 *  status. Depending on the error status the application can take the decision
 *  to recover from the error
 */
typedef struct
{
    Bool  isDMAErr;
    /**< DMA Error           */
    Bool  isRcvOvrRunOrTxUndRunErr;
    /**< Receive OverRun on Transmir UnderRun Error           */
    Bool  isClkFailErr;
    /**< Clock Fail Error           */
    Bool  isSyncErr;
    /**< Sync Error           */
    Int32 retVal;
    /**< return value           */
}Mcasp_errCbStatus;

/**
 *  \brief Global error callback function protype
 *
 *  This is the global error callback function for the McASP driver.
 *  This function is called directly called from ISR context in
 *  case of error.
 */
typedef Void (*Mcasp_GblCallback)(Mcasp_errCbStatus errCbStat);

/**
 *  \brief Mcasp Interrupt service routine
 *
 *  This is Function pointer to the McASP ISR. Interrupt registration takes
 *  place by hooking the ISR to the interrrupt number.
 */
typedef Void (*Mcasp_Isr)(Ptr arg);

/* -------- structs -------- */

/**
 *  \brief Hardware setup data clock structure
 */
typedef struct
{
    UInt32 clkSetupClk;             /**< Clock details ACLK(R/X)CTL           */
    UInt32 clkSetupHiClk;           /**< High clock details AHCLK(R/X)CTL     */
    UInt32 clkChk;                  /**< Configures RX/TX CLK fail detect     */
}Mcasp_HwSetupDataClk;

/**
 *  \brief Hardware setup global structure
 */
typedef struct
{
    UInt32 pfunc;                          /**< Pin function register
                                            *            */
    UInt32 pdir;                           /**< Pin direction register
                                            *           */
    UInt32 ctl;                            /**< Global control register - GBLCTL
                                            * */
    UInt32 ditCtl;                         /**< whether McASP operates in DIT
                                            *mode*/
    UInt32 dlbMode;                        /**< Digital loopback mode setup
                                            *      */
    UInt32 amute;                          /**< Mute control register - AMUTE
                                            *    */
    UInt32 serSetup[MCASP_NUMSERIALIZERS]; /**< Setup serializer control
                                            *register */
}Mcasp_HwSetupGbl;

/**
 *  \brief Hardware setup data structure
 */
typedef struct
{
    UInt32               mask;       /**< To mask or not to mask - R/XMASK    */
    UInt32               fmt;        /**< Format details as per  - R/XFMT     */
    UInt32               frSyncCtl;  /**< Configure the rcv/xmt frame sync    */
    UInt32               tdm;        /**< Specifies which TDM slots are active*/
    UInt32               intCtl;     /**< Controls generation of interrupts   */
    UInt32               stat;       /**< Status register (controls writable  *
                                      * fields of STAT register)-R/XSTAT     */
    UInt32               evtCtl;     /**< Event control register - R/XEVTCTL  */
    Mcasp_HwSetupDataClk clk;        /**< Clock settings for rcv/xmt          */
}Mcasp_HwSetupData;

/**
 *  \brief Hardware setup structure
 */
typedef struct
{
    Mcasp_HwSetupGbl  glb;           /**< Value to be loaded in  (GLBCTL)     */
    Mcasp_HwSetupData rx;            /**< Receiver settings                   */
    Mcasp_HwSetupData tx;            /**< Transmitter settings                */
    UInt32            emu;           /**< Power down emulation mode params    */
}Mcasp_HwSetup;

/*!
 *  \brief structure to store the audio device related information            */
typedef struct
{
    Bool isMaster;
    /**< variable to store the current operation mode (Master/Slave).         */
}Mcasp_AudioDevData;

/*!
 *  \brief channel Parameters to initialize channel Object
 *
 *  This structure stores user supplied parameters
 */
typedef struct
{
    UInt16             noOfSerRequested;
    /**< Serializer requested by channel. Channel can ask for both.           */

    UInt32             indexOfSersRequested[MCASP_NUMSERIALIZERS];
    /**< Multi Serializer numbers requested by channel                        */

    Mcasp_HwSetupData *mcaspSetup;
    /**< Setup information for xmt/rcv sections of the McASP                  */

    Bool               isDmaDriven;
    /**< This parameters determines whether channel operates in DMA mode      *
     * All DMA parameters would be read only if this is TRUE                 */

    Mcasp_OpMode       channelMode;
    /**< channel operation mode TDM or DIT mode                               */

    UInt16             wordWidth;
    /**< The parameter informs the driver what is the width word              *
     * (not slot) and this help driver indirectly to decided no. of           *
     * bytes to be transfered into each serialer for each slot- This is       *
     * very important parameter - in case of invalid value default            *
     * value of 32 will be assumed by the driver                              */

    Ptr                userLoopJobBuffer;
    /**< Buffer to be transferred when the loop job is running.it should      *
     * be noted that this buffer size should be n*userLoopjobLength           *
     * where n is the no of serialisers configured in the direction of        *
     * the channel we are creating                                            */

    UInt16             userLoopJobLength;
    /**< Number of bytes of the userloopjob buffer for each serialiser        *
     * Please note that this is no. of bytes and this should be               *
     * pre-calcuated properly for word width of slot - Please refer the       *
     *  wordWidth of this structure                                           */

    Ptr                edmaHandle;
    /**< Handle to the EDMA Driver                                            */

    Mcasp_GblCallback  gblCbk;
    /**< callback required when global error occurs -                         *
     * must be callable  directly from the ISR context                        */

    UInt32             noOfChannels;
    /**< No of channels of data to be transmitted after the frame sync        *
     * This input is valid only for TDM in DSP mode mode of                   *
     * communication E.g.--For Stereo data the value is 2 and for 6           *
     * channel dac taking all channel data through one serialiser the         *
     * value of this member will be 6 Note: But for same 6ch dac taking       *
     * stereo data though 3 seperate serialiser value should be 2             */

    Mcasp_BufferFormat dataFormat;
    /**< Format of the application supplied buffer                            */

    Bool               enableHwFifo;
    /**< Option to enable the Hardware FIFO                                   */

    Bool               isDataPacked;
    /**< flag to indicate if the buffer data needs to be packed,i.e
     * the EDMA needs to be programmed for the exact slotwidth or a
     * rounded width of 32,16, or 8 Bit                                       */
    UInt16             hwiNumber;
    /**< Variable to specify the Hwi number to be used by the driver
     *  (default id is 0)                                              */
}Mcasp_ChanParams;

/**
 *  \brief DIT channel status register structure
 */
typedef struct
{
    UInt32 chStatusLeft[6];
    /**< Left channel status registers (DITCSRA0-5)                           */

    UInt32 chStatusRight[6];
    /**< Right channel status register (DITCSRB0-5)                           */
}Mcasp_ChStatusRam;

/**
 *  \brief DIT channel user data register structure
 */
typedef struct
{
    UInt32 userDataLeft[6];
    /**< Left channel user data registers (DITUDRA0-5)                        */

    UInt32 userDataRight[6];
    /**< Right channel user data registers (DITUDRB0-5)                       */
}Mcasp_UserDataRam;

/**
 *  \brief Structure passed through DriverTypes_Packet addr field
 *
 *  In order to pass data for the DIT Channel Status and
 *  User Data RAM registers, the addr field of the
 *  IOM_Packet is cast to Mcasp_PktAddrPayload. The
 *  addr field holds pointers to Mcasp_ChStatusRam and
 *  Mcasp_UserDataRam in addition to the DMA address to
 *  be programmed.
 *
 *  NOTE: The Mcasp_ChStatusRam and Mcasp_UserDataRam
 *  fields will be read only for a transmit channel
 *  operating in DIT mode.
 */
typedef struct
{
    Mcasp_ChStatusRam *chStat;
    /**< Channel Status RAM innfo                                             */

    Mcasp_UserDataRam *userData;
    /**< User Data RAM info                                                   */

    Bool               writeDitParams;
    /**< Determines whether Channel Status and User Data get                  *
     * written in case of interrupt mode                                      */

    UInt32            *addr;
    /**< Actual address to program DMA with                                   *
     * Address of data word if transactions are interrupt driven              */
}Mcasp_PktAddrPayload;

/**
 *  \brief  Mcasp Ioctl commands
 *
 *  Mcaspp Ioctl commands
 */
typedef enum
{
    /**< Reset Device, cmdArg = NONE                                          */
    IOCTL_MCASP_DEVICE_RESET = 128,

    /**< Enable/Disable mute, cmdArg = (Uint32 *) value for AMUTE register    */
    IOCTL_MCASP_CNTRL_AMUTE,

    /**< Start Mcasp port, cmdArg = NONE                                      */
    IOCTL_MCASP_START_PORT,

    /**< Stop Mcasp port, cmdArg = NONE                                       */
    IOCTL_MCASP_STOP_PORT,

    /**< Query AMUTE register, cmdArg = (Uint32 *) variable to store value    */
    IOCTL_MCASP_QUERY_MUTE,

    /**< Loop job modification, cmdArg = (Mcasp_ChanParams *)                 */
    IOCTL_MCASP_CTRL_MODIFY_LOOPJOB,

    /**< Mute on, cmdArg = NONE                                               */
    IOCTL_MCASP_CTRL_MUTE_ON,

    /**< Mute off, cmdArg = NONE                                              */
    IOCTL_MCASP_CTRL_MUTE_OFF,

    /**< Pause data transfer, cmdArg = NONE                                   */
    IOCTL_MCASP_PAUSE,

    /**< Resume data transfer, cmdArg = NONE                                  */
    IOCTL_MCASP_RESUME,

    /**< Set DIT mode, cmdArg = (Uint32 *) value for DITCTL register          */
    IOCTL_MCASP_SET_DIT_MODE,

    /**< Channel timeout, cmdArg = NONE                                       */
    IOCTL_MCASP_CHAN_TIMEDOUT,

    /**< Channel reset, cmdArg = NONE                                         */
    IOCTL_MCASP_CHAN_RESET,

    /**< Set channel format, cmdArg = (Mcasp_HwSetupData *)                   */
    IOCTL_MCASP_CNTRL_SET_FORMAT_CHAN,

    /**< Get format channel info, cmdArg = (Mcasp_HwSetupdata *)              */
    IOCTL_MCASP_CNTRL_GET_FORMAT_CHAN,

    /**< Set GBL register values, cmdArg = (Mcasp_HwSetup *)                  */
    IOCTL_MCASP_CNTRL_SET_GBL_REGS,

    /**< Set digital loop back mode, cmdArg = NONE                            */
    IOCTL_MCASP_SET_DLB_MODE,

    /**< Abort all queued requests, cmdArg = NONE                             */
    IOCTL_MCASP_ABORT,

    /**< IOCTL to Set the sample rate cmdArg = (Uint32 *)                     */
    IOCTL_MCASP_SET_SAMPLE_RATE,

    /**< Ioctl to query the Mcasp specific information.
     *   cmdArg = (Mcasp_AudioDevData *)                                      */
    IOCTL_MCASP_GET_DEVINFO,

    /**< Ioctl to flush the receive FIFO                                      */
    IOCTL_MCASP_FLUSH_RCV_FIFO,

    /**< Ioctl command to modify the timeout used by the driver for certain
     * wait operations. cmdArg = (Uint32 *)                                   */
    IOCTL_MCASP_SET_TIMEOUT,

    /**< Ioctl command to check if the driver is compiled in loop job mode or
     * Not. cmdArg = (Bool *) TRUE = loop job mode,FALSE = loop job disabled  */
    IOCTL_MCASP_QUERY_LOOPJOB_MODE
}Mcasp_ioctlCmd;

/* -------- per-instance configs -------- */

typedef struct
{
    Bool          enablecache;
    /**< Option to select whether to enable cache or not(default is TRUE)     */

    UInt16        hwiNumber;
    /**< Variable to specify the Hwi number to be used by the driver
     * (default id is 0)                                                      */

    Bool          prcmPwrmEnable;
    /**< This variable specify the option to enable or disable PWRM functions
     * (default is set to PWRM disabled)
     */

    Ptr           prcmHandle;
    /**< Handle to the prcm instance to be used to switch on the instance     */

    Bool          isDataBufferPayloadStructure;
    /**< This is useful during the operation of the Mcasp in DIT mode.This
     * parameter indicates if the data buffer has to be interpreted as a
     * payload structure,i.e whether the channel status and user data is also
     * included in the application buffer and hence has to be appropriately
     * interpreted.(Default is FALSE).                                        */

    Mcasp_HwSetup mcaspHwSetup;
    /**< Register information for initialising the Mcasp hardware.            */

    Bool          pwrmPowerEnable;
    /**< Option to enable or disable the PSC control in the driver            */

    Int           prcmDevId;
    /* prcm device ID */
}Mcasp_Params;

/**
 *  \brief -D's or compiler defines used to add/remove features
 */

/**
 *  \brief Define to enable debug prints from driver
 *
 *  Use -DMcasp_DEBUGPRINT_ENABLE when building library
 */

/**
 *  \brief Default Mcasp_Params struct
 *
 *  const Mcasp_Params Mcasp_PARAMS = {
 *
 *    1,                                enablecache
 *
 *    (Uint32)0x0,                      hwiNumber
 *
 *    0,                                isDataBufferPayloadStructure
 *
 *    {
 *        {
 *            (Uint32)0x0,              pfunc
 *
 *            (Uint32)0x1,              pdir
 *
 *            (Uint32)0x0,              ctl
 *
 *            (Uint32)0x0,              ditCtl
 *
 *            (Uint32)0x0,              dlbMode
 *
 *            (Uint32)0x0,              amute
 *
 *            {
 *                (Uint32)0x0,          [0]
 *
 *                (Uint32)0x0,          [1]
 *
 *                (Uint32)0x0,          [2]
 *
 *                (Uint32)0x0,          [3]
 *
 *                (Uint32)0x0,          [4]
 *
 *                (Uint32)0x0,          [5]
 *
 *            },                        serSetup
 *
 *        },                            glb
 *
 *        {
 *            (Uint32)0xffffffff,       mask
 *
 *            (Uint32)0x0,              fmt
 *
 *            (Uint32)0x0,              frSyncCtl
 *
 *            (Uint32)0x1,              tdm
 *
 *            (Uint32)0x0,              intCtl
 *
 *            (Uint32)0x1ff,            stat
 *
 *            (Uint32)0x0,              evtCtl
 *
 *            {
 *                (Uint32)0x0,          clkSrc
 *
 *                (Uint32)0x3,          clkSetupClk
 *
 *                (Uint32)0x8046,       clkSetupHiClk
 *
 *                (Uint32)0x0,          clkChk
 *
 *            },                        clk
 *
 *        },                            rx
 *
 *        {
 *            (Uint32)0xffffffff,       mask
 *
 *            (Uint32)0x0,              fmt
 *
 *            (Uint32)0x2,              frSyncCtl
 *
 *            (Uint32)0x1,              tdm
 *
 *            (Uint32)0x0,              intCtl
 *
 *            (Uint32)0x1ff,            stat
 *
 *            (Uint32)0x0,              evtCtl
 *
 *            {
 *                (Uint32)0x0,          clkSrc
 *
 *                (Uint32)0x23,         clkSetupClk
 *
 *                (Uint32)0x8046,       clkSetupHiClk
 *
 *                (Uint32)0x0,          clkChk
 *
 *            },                        clk
 *
 *        },                            tx
 *
 *        (Uint32)0x1,                  emu
 *
 *    },                                mcaspHwSetup
 *
 *  };
 */
extern const Mcasp_Params Mcasp_PARAMS;

/**
 *  \brief Mcasp IOM_Fxns table
 *
 *  Driver function table to be used by applications.
 */
extern IOM_Fxns           Mcasp_IOMFXNS;

/**
 * \brief    Initializes Mcasp instances which are statically allocated
 *
 *  This function needs to ve be called at part of BIOS initialization by
 *  setting initFxn for that particular UDEV instance or by calling this
 *  function as part of user specific initFxn.
 */
Void Mcasp_init(Void);

#ifdef __cplusplus
}
#endif
#endif /*BSP_MCASP_H_ */

/*  @}  */
