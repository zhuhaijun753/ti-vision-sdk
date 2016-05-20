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
 *  \file mcaspLocal.h
 *
 *  \brief Internal Driver header file
 *  @{
 */

#ifndef MCASPLOCAL_H_
#define MCASPLOCAL_H_

#include <xdc/std.h>
#include <ti/sysbios/io/IOM.h>
#include <mcasp/bsp_mcasp.h>
#include <ti/sysbios/knl/Swi.h>
#include <ti/sysbios/knl/Queue.h>

#include <soc.h>
#include <soc_defines.h>

/* Since SYS/BIOS does not support PWRM, presently this is commented out!!    */

/* #if ((defined(CHIP_DM8148)) && (!defined(BIOS_PWRM_ENABLE)))
 * #error "Use Bios PWRM module only for the SoC DM814x"
 * #else
 * #include <pwrm.h>
 * #endif
 *
 * #if ((defined(CHIP_C6A811x)) && defined(BIOS_PWRM_ENABLE))
 * #error "Do not use Bios PWRM module for this SoC C6A811x"
 #endif */

#ifdef __cplusplus
extern "C"
{
#endif

#include <ti/sdo/edma3/drv/edma3_drv.h>

/* -------- constants -------- */

#define Mcasp_MAX_NUM_CHANS       (0x02)
/**<  Maximum number of channels supported by the Mcasp instance              */

#define Mcasp_MAX_PACKET_SIZE     (32768U)
/**<  Maximum packet size in bytes                                            */

#define Mcasp_MAXLINKCNT          (UInt32) (2U)
/**<  Maximum number of EDMA jobs linked at a time (Must be 2).               */

#define Mcasp_TXEVENTQUE          (0U)
/**<  Transmit EDMA channel event queue number                                */

#define Mcasp_RXEVENTQUE          (1U)
/**<  Receive EDMA channel event queue number                                 */

#define MAX_FIFO_ALLOWED          (20U)
/*! The maximum FIFO depth that can be used                                   */

#define Mcasp_SM_RESET            (0U)
/**<  Reset value of xmt/rcv state m/c and frame sync                         */

#define Mcasp_TWO_PKTS_QUEUED     (2U)
/**<  When xmt is taken out of reset, it needs two words to                   *
 *  service it. This is used to keep tally of this requirement.               */

#define Mcasp_STATUS_INVALID      (0xFFFF)
/**<  Generic invalidate status                                               */

#define Mcasp_STATUS_VALID        (0x1)
/**<  Generic validate status                                                 */

#define Mcasp_DATA_RDY            (0x20U)
/**<  Interrupt due to: Data Ready                                            */

#define Mcasp_DMAERR              (UInt32) (0x80U)
/**<  Interrupt due to: DMA channel error                                     */

#define Mcasp_XMT_UNDERRUN        (UInt32) (0x1U)
/**<  Interrupt due to: Transmit Buffer Underrun                              */

#define Mcasp_RCV_OVERRUN         (UInt32) (0x1U)
/**<  Interrupt due to: Receive Buffer Overrun                                */

#define Mcasp_SYNCERR             (UInt32) (0x2U)
/**< Interrupt due to: Transmit/Receive Sync Error                            */

#define Mcasp_RSTAT_ERROR         (UInt32) (0x100U)
/**< Bit field to indicate if any receive error has occured                   */

#define Mcasp_XSTAT_ERROR         (UInt32) (0x100U)
/**< Bit field to indicate if any transmit error has occured                  */

#define Mcasp_TX_CLK_FAIL         (UInt32) (0x04U)
/**< Interrupt due to transmit clock failure                                  */

#define Mcasp_RX_CLK_FAIL         (UInt32) (0x04U)
/**< Interrupt due to receive clock failure                                   */

#define Mcasp_OPT_TCINTEN_SHIFT   (0x00000014U)
/**<  Interrupt enable bit in OPT register for edma                           */

#define Mcasp_OPT_SYNCDIM_SHIFT   (0x00000002U)
/**<  Sync Type AB set bit of OPT register for edma                           */

#define Mcasp_OPT_TCC_SHIFT       (UInt32) (0x0000000CU)
/**<  TCC set bit in OPT register for edma                                    */

#define Mcasp_OPT_TCC_MASK        (0x0003F000U)
/**<  Tcc mask in OPT register for edma                                       */

#define Mcasp_OPT_TCCMOD_SHIFT    (0x0000000BU)
/**< Transfer completion selection bit                                        */

#define Mcasp_CNT_MAX_VAL         (0xFFFFU)
/**<  Max possible value of aCnt, bCnt and cCnt                               */

#define Mcasp_SWI_PRIORITY         0x01
/**< Priority of the swi thread which handles the interrupts                  */

#define Mcasp_MAX_PWRM_EVENTS      (PWRM_INVALIDEVENT)
/**< Max number of PWRM events for which the mcasp will register              */

#define Mcasp_MAX_PWRM_CONSTRAINTS (PWRM_DISALLOWEDSLEEPSTATE_MASK)
/**< Max number of constraints for which a moudule can register               */

/**
 * \def    Mcasp_POLLED_RETRYCOUNT
 *         This macro specifies the default retry count to be used by the Mcasp
 *         driver when polling for any hardware bit to be set or reset.
 *
 * \note   This default value used by the driver can be changed by an IOCTL
 *         "Mcasp_Ioctl_SET_TIMEOUT".
 */
#define Mcasp_POLLED_RETRYCOUNT   (0xFFFFU)

/* -------- enums -------- */

/**
 *  \brief Enumeration for channel mode
 */
typedef enum
{
    Mcasp_ChanMode_FREE    = 0,       /**<  Channel not allocated             */
    Mcasp_ChanMode_XMT_DIT = 1U,      /**<  Transmit channel: DIT mode        */
    Mcasp_ChanMode_XMT_TDM = 2U,      /**<  Transmit channel: TDM mode        */
    Mcasp_ChanMode_RCV     = 3U       /**<  Receive channel                   */
}Mcasp_ChanMode;

/**
 *  \brief Enumeration for DIT channel index
 */
typedef enum {
    Mcasp_DITRegIndex_0 = 0,
    /**<  1st DIT (channel/user data), (left/right) Register                  */
    Mcasp_DITRegIndex_1 = 1,
    /**<  2nd DIT (channel/user data), (left/right) Register                  */
    Mcasp_DITRegIndex_2 = 2,
    /**<  3rd DIT (channel/user data), (left/right) Register                  */
    Mcasp_DITRegIndex_3 = 3,
    /**<  4th DIT (channel/user data), (left/right) Register                  */
    Mcasp_DITRegIndex_4 = 4,
    /**<  5th DIT (channel/user data), (left/right) Register                  */
    Mcasp_DITRegIndex_5 = 5
                          /**<  6th DIT (channel/user data), (left/right)
                           *Register                  */
}Mcasp_DITRegIndex;

/**
 *  \brief Mcasp driver state
 *
 *  Mcasp driver state enums used to track the driver state
 */
typedef enum {
    Mcasp_DriverState_DELETED,
    Mcasp_DriverState_CREATED,
    Mcasp_DriverState_INITIALIZED,
    Mcasp_DriverState_OPENED,
    Mcasp_DriverState_CLOSED,
    Mcasp_DriverState_DEINITIALIZED,
    Mcasp_DriverState_POWERED_DOWN,
    Mcasp_DriverState_PWRM_SUSPEND
}Mcasp_DriverState;

/**
 *  \brief Enumeration for the serializer mode
 */
typedef enum  {
    Mcasp_SerMode_INACTIVE = 0,                /**< Serializer is inactive    */
    Mcasp_SerMode_XMT      = 1,                /**< Serializer is transmitter */
    Mcasp_SerMode_RCV      = 2                 /**< Serializer is receiver    */
}Mcasp_SerMode;

/**
 *  \brief Enumeration for serializer status
 */
typedef enum  {
    Mcasp_SerializerStatus_FREE = (0), /**< Serializer not allocated          */
    Mcasp_SerializerStatus_XMT  = (1), /**< Serializer configured to transmit */
    Mcasp_SerializerStatus_RCV  = (2)  /**< Serializer configured to receive  */
}Mcasp_SerializerStatus;

/* -------- structs -------- */

/**
 *  \brief Enumeration for Hardware status commands
 */
typedef enum  {
    /**
     * @brief   Return current transmit slot being transmitted
     * @param   (UInt16 *)
     */
    Mcasp_HwStatusQuery_CURRENT_XSLOT = 1,
    /**
     * @brief   Return current receive slot being received
     * @param   (UInt16 *)
     */
    Mcasp_HwStatusQuery_CURRENT_RSLOT = 2,
    /**
     * @brief   Return transmit error status bit
     * @param   (Bool *)
     */
    Mcasp_HwStatusQuery_XSTAT_XERR = 3,
    /**
     * @brief   Return transmit clock failure flag status
     * @param   (Bool *)
     */
    Mcasp_HwStatusQuery_XSTAT_XCLKFAIL = 4,
    /**
     * @brief   Return unexpected transmit frame sync flag status
     * @param   (Bool *)
     */
    Mcasp_HwStatusQuery_XSTAT_XSYNCERR = 5,
    /**
     * @brief   Return transmit underrun flag status
     * @param   (Bool *)
     */
    Mcasp_HwStatusQuery_XSTAT_XUNDRN = 6,
    /**
     * @brief   Return transmit data ready flag status
     * @param   (Bool *)
     */
    Mcasp_HwStatusQuery_XSTAT_XDATA = 7,
    /**
     * @brief   Return receive error status bit
     * @param   (Bool *)
     */
    Mcasp_HwStatusQuery_RSTAT_RERR = 8,
    /**
     * @brief   Return receive clock failure flag status
     * @param   (Bool *)
     */
    Mcasp_HwStatusQuery_RSTAT_RCLKFAIL = 9,
    /**
     * @brief   Return unexpected receive frame sync flag status
     * @param   (Bool *)
     */
    Mcasp_HwStatusQuery_RSTAT_RSYNCERR = 10,
    /**
     * @brief   Return receive overrun flag status
     * @param   (Bool *)
     */
    Mcasp_HwStatusQuery_RSTAT_ROVRN = 11,
    /**
     * @brief   Return receive data ready flag status
     * @param   (Bool *)
     */
    Mcasp_HwStatusQuery_RSTAT_RDATA = 12,
    /**
     * @brief   Return whether the serializer is ready to receive or not
     * @param   (McaspSerQuery *)
     */
    Mcasp_HwStatusQuery_SRCTL_RRDY = 13,
    /**
     * @brief   Return status whether the serializer is ready to transmit
     *          or not
     * @param   (SerQuery *)
     */
    Mcasp_HwStatusQuery_SRCTL_XRDY = 14,
    /**
     * @brief   Return status whether serializer is configured to
     *          transmit/receive/inactive
     * @param   (SerQuery *)
     */
    Mcasp_HwStatusQuery_SRCTL_SRMOD = 15,
    /**
     * @brief   Return the value of transmitter status register.
     * @param   (UInt16 *)
     */
    Mcasp_HwStatusQuery_XSTAT = 16,
    /**
     * @brief   Return the value of receiver status register.
     * @param   (UInt16 *)
     */
    Mcasp_HwStatusQuery_RSTAT = 17,
    /**
     * @brief   Return the transmit state machine and transmit frame sync
     *          generator values in transmitter global control register
     * @param   (UInt8 *)
     * @li          0x00 - Both transmit frame generator sync and transmit
     *                     state machine are reset.
     * @li          0x1  - Only transmit state machine is active.
     * @li          0x10 - Only transmit frame sync generator is active.
     * @li          0x11 - Both transmit frame generator sync and transmit
     *                     state machine are active.
     */
    Mcasp_HwStatusQuery_SM_FS_XMT = 18,
    /**
     * @brief   Return the receive state machine and receive frame sync
     *          generator values in receiver global control register
     * @param   (UInt8 *)
     * @li          0x00 - Both receive frame generator sync and receive
     *                     state machine are reset.
     * @li          0x1  - Only receive state machine is active.
     * @li          0x10 - Only receive frame sync generator is active.
     * @li          0x11 - Both receive frame generator sync and receive
     *                     state machine are active.
     */
    Mcasp_HwStatusQuery_SM_FS_RCV = 19,
    /**
     * @brief   Queries whether DIT mode is set or not
     * @param   (Bool *)
     */
    Mcasp_HwStatusQuery_DIT_MODE = 20,
    /**
     * @brief   Queries and returns the value in AMUTE register
     * @param   (Bool *)
     */
    Mcasp_HwStatusQuery_AMUTE = 21,
    /**
     * @brief max number of queries
     */
    Mcasp_HwStatusQuery_MAX = 22
}Mcasp_HwStatusQuery;

/**
 *  \brief Channel Object
 *
 *  This structure maintains the current channel state. It also holds
 *  information on DMA channel being used and holds the application
 *  callback function to be called in case of an interrupt.
 *
 *  This structure is initialized by mdCreateChan and a pointer to this
 *  is passed down to all other channel related functions. Lifetime of
 *  the data structure is from its creation by mdCreateChan till it
 *  is invalidated by mdDeleteChan.
 */
typedef struct
{
    Mcasp_DriverState    chanState;
    /**<  Current state of the channel (opened or closed)                     */

    UInt32               mode;
    /**<  mode for channel (i.e IOM_INPUT or OUTPUT)                          */

    Ptr                  devHandle;
    /**<  Pointer to McASP device driver port structure                       */

    IOM_TiomCallback     cbFxn;
    /**<   IOM call back function to be called once a packet is processed     */

    UArg                 cbArg;
    /**<  Callback Function argument                                          */

    Queue_Struct         queueReqList;
    /**<  Queue containing the pending requests received from application.    */

    Queue_Struct         queueFloatingList;
    /**<  list to manage floating packets in DMA                              */

    UInt16               noOfSerAllocated;
    /**<  no of Serializer(s) allocated                                       */

    UInt32               indexOfSersRequested[MCASP_NUMSERIALIZERS];
    /**<  Multi Serializer numbers requested by channel                       */

    Mcasp_ChanMode       channelOpMode;
    /**<  Mode of operation: Transmit(DIT/TDM) or Receive                     */

    UInt16               dataQueuedOnReset;
    /* McASP needs to service each serializer with two words when it awakes
     *from reset */

    UInt32               intStatus;
    /**<  Holds id of McASP interrupt cause, if any
     *    used in interrupt mode                                              */

    Int32                currentPacketErrorStatus;
    /**< This member will hold the error status -normally updated from cpu
     *   interrupt thread and is used in EDMA completion thread for updating
     *   the error code in IOP
     */

    IOM_Packet          *dataPacket;
    /**<  Current data packet being serviced.                                 */

    IOM_Packet          *tempPacket;
    /**<  Temp IOP holder                                                     */

    volatile Bool        isTempPacketValid;
    /**<  Valid packet flag in EDMA callback                                  */

    UInt32               userDataBufferSize;
    /**<  Size of the data buffer per serialiser, hence the buffer given by   *
     * the application should really be userDataBufferSize * no. of           *
     * serialisers allocated for that channel                                 */

    Int32                submitCount;
    /**<  Number of submit calls pending                                      */

    UInt16               noOfSlots;
    /**< number of slots used by the mcasp                                    */

    Ptr                  edmaHandle;
    /**<  Edma Handle                                                         */

    Ptr                  loopJobBuffer;
    /**< Buffer to be transferred when the loop job is running                */

    UInt32               xferChan;
    /**<  EDMA  ChannelID                                                     */

    UInt32               tcc;
    /**<  EDMA  tcc                                                           */

    UInt32               pramTbl[2U];
    /**<  Logical channel numbers of EDMA, which are used for linking         */

    UInt32               pramTblAddr[2U];
    /**<  Physical address of logical channel numbers of EDMA, which          *
     * are used for linking                                               */

    UInt32               nextLinkParamSetToBeUpdated;
    /**<  Used to store the next index of link param to be updated            */

    Bool                 isDmaDriven;
    /**<  Determines whether data input is using DMA or not                   */

    volatile Bool        loopjobUpdatedinParamset;
    /**<  Used to prevent updating second paramset with loopjob for last      *
     * datapacket edma callback                                               */

    volatile Bool        xferinProgressIntmode;
    /**<  use to start int mode transfer from  0 packet status                */

    volatile Bool        bMuteON;
    /**<  True, if playback is muted                                          */

    volatile Bool        paused;
    /**<  TRUE, if pause Request is called                                    */

    volatile Bool        nextFlag;
    /**<  TRUE, if pause Request is called                                    */

    Bool                 enableHwFifo;
    /**< whether the FIFO has to be enabled for this channel                  */

    Bool                 isDataPacked;
    /**< flag to indicate if the buffer data needs to be packed               */

    UInt32               cpuEventNum;
    /**<  This hold the cpu event no. of this channel (TX/Rx) for this        *
     * instance                                                               */

    UInt16               loopJobLength;
    /**<  Length of userloop job for each serialiser                          */

    UInt16               userLoopJobLength;
    /**< Length of the user supplied loop job buffer                          */

    UInt16               roundedWordWidth;
    /**<  Word length bytes to be transferred for DMA transaction             */

    UInt16               currentDataSize;
    /**<  data packet size used for interrupt mode                            */

    EDMA3_RM_TccCallback edmaCallback;
    /**<  stores the edma call back function ptr - functions actual type is   *
     * EDMA3_RM_TccCallback                                                   */

    Mcasp_GblCallback    gblErrCbk;
    /**<  callback required when the loop job is running must be callable     *
     * directly from the IOM layer                                            */

    Mcasp_BufferFormat   dataFormat;
    /**< Application supplied buffer format                                   */

    UInt32               userIntValue;
    /**< User supplied mask for the interrupts to be enabled                  */

    Bool                 userLoopJob;
    /**< Option to indicate if the user loop job is used or driver loop job   */
}Mcasp_ChannelObj;

/**
 *  \brief Structure used to supply the information for the Mcasp setup
 */
typedef struct
{
    Bool           enablecache;
    /**< Submitted buffers are in cacheable memory                            */

    Bool           isDataBufferPayloadStructure;
    /**< Submitted buffers have payload information present or absent         */

    Mcasp_HwSetup *mcaspHwSetup;
    /**<  Initial setup for the McASP                                         */
}Mcasp_DevParams;

/**
 *  \brief HW info structure
 *
 *  Mcasp structure to hold the instance specific information.
 */
typedef struct
{
    UInt32 baseAddress;
    /**< base address of the mcasp instance        */

    UInt32 fifoAddress;
    /**< Fifo address of the mcasp instance        */

    UInt32 dataAddress;
    /**< Mcasp data registers address              */

    Bool   ditSupport;
    /**< Dit support enabled in hardware or not    */

    UInt16 numSerializers;
    /**<number of serializers supported by instance*/

    UInt32 txCpuEventNumber;
    /**< hardware interrupt of the mcasp instance  */

    UInt32 rxCpuEventNumber;
    /**< hardware interrupt of the mcasp instance  */

    UInt32 rxDmaEventNumber;
    /**< RX DMA event number                       */

    UInt32 txDmaEventNumber;
    /**< TX DMA event number                       */

    UInt32 pwrmPrcmId;
    /**< PRCM number for this instance             */

    UInt32 prcmInstance;
    /**< Instance of the PRCM which controls this module's instance           */

    /* CRED_index_t     component; */
    /**< McASP Component instance used                                        */
}Mcasp_HwInfo;

/**
 *  \brief Hardware specific information structure
 */
typedef struct
{
    Bool   ditStatus;
    /**< Support for DIT mode  in hardware                                    */

    UInt32 regs;
    /**< Pointer to the register overlay structure for the peripheral         */

    UInt32 fifoRegs;
    /**< pointer to the register overlay structure for the FIFO               */

    Int16  perNo;
    /**< Specifies a particular instance of McASP                             */

    UInt16 numOfSerializers;
    /**< Number of serializers                                                */

    UInt32 dataAddr;
    /**< Instance Data Address                                                */

    UInt32 edmaTxEventNum;
    /**< edma Transmit event number                                           */

    UInt32 edmaRxEventNum;
    /**< edma Receive event number                                            */

    UInt32 cpuTxEventNum;
    /**< This holds the CPU event no. of Rx                                   */

    UInt32 cpuRxEventNum;
    /**< This holds the CPU event no. of Tx                                   */

    UInt32 pwrmPrcmId;
    /**< Prcm number for this instance                                        */

    UInt32 prcmInstance;
    /**< Instance of the Prcm which controls this module's instance           */

    /*    CRED_index_t         component; */
    /**< McASP Component instance used                                        */
}Mcasp_HwObj;

/* -------- per-instance state -------- */
/**
 *  \brief per-instance state
 */
typedef struct
{
    UInt16                 instNum;
    /**< Preserve  instance number in port                                    */

    Mcasp_DriverState      devState;
    /**< stores the current state of the driver                               */

    Bool                   isDataBufferPayloadStructure;
    /**< Input request is a flat data buffer or a  payload                    *
     * structure                                                              */

    Mcasp_HwSetup          mcaspHwSetup;
    /**< Hw parmas to configure mcasp                                         */

    UInt16                 hwiNumber;
    /**< Hwi number if using interrupt mode                                   */

    Bool                   enablecache;
    /**< Submitted buffers are in cacheable memory                            */

    Bool                   stopSmFsXmt;
    /**< Status of stoping state m/c for XMT                                  */

    Bool                   stopSmFsRcv;
    /**< Status of stoping state m/c for RCV                                  */

    Mcasp_ChannelObj       XmtObj;
    /**< Holds transmit channel to the McASP.                                 */

    Mcasp_ChannelObj       RcvObj;
    /**< Holds receive channel to the McASP.                                  */

    Mcasp_HwObj            hwInfo;
    /**< McASP handle for initial port configuration                          */

    Mcasp_SerializerStatus serStatus[MCASP_NUMSERIALIZERS];
    /**< Holds status information for both the serializers.                   *
     *  - Valid values are FREE, XMT and RCV                                  */

    Swi_Struct             isrSwiObject;
    /**< SWI to handle the interrupts                                         */

    Swi_Struct             fifoSwiObject;
    /**< SWI object for the swi used to handle the FIFO not empty while the   *
     * last packet callback is in progress                                    */

    UInt32                 retryCount;
    /**< The retry count value to be used when waiting for the TX empty to be *
     * set                                                                    */

    Bool                   loopJobMode;
    /**< Variable to check if the loop job mode is enabled or not             */

    Bool                   prcmPwrmEnable;
    /**< Option to enable or disable the Prcm control in the driver           */

    Ptr                    prcmHandle;
    /**< Handle to the prcm instance to be used to switch on the instance     */

    Int                    prcmDevId;
    /* prcm device ID */

#ifdef BIOS_PWRM_ENABLE
    Mcasp_pwrmInfo         pwrmInfo;
#endif
    /**< structure to hold the PWMR related information                       */
} Mcasp_Object;

/**
 * \brief structure holding the information required for the ISR to service the
 *        appropriate instance.
 */
typedef struct
{
    Bool          isIsrRegistered[Mcasp_MAX_NUM_CHANS];
    /**< Hardware instance number of the device registering the interrupt   */

    Bool          chanEnabled[Mcasp_MAX_NUM_CHANS];
    /**< variable to indicate whether the channel has registered interrupts */

    Mcasp_Object *instHandle;
    /**< pointer to the driver instance object                              */

    Swi_Handle    isrSwiTaskHandle;
    /**< Handle to the SWI tasklet that will be handling all the interrupts */
}Mcasp_IsrObject;

/**
 *  \brief Module specific parameters. Present implementation doesn't have
 *  any module specific parameters.
 */
typedef struct
{
    UInt16 flags;
    /**<
     *  Bit mask to be used for module specific parameters.
     *  The below declaration is just a place-holder for future
     *  implementation.
     */
}Mcasp_HwParam;

/**
 *  \brief The following structure will be used in
 *  MCASP_HwStatusQuery_SRCTL_SRMOD
 */
typedef struct  {
    Mcasp_SerializerNum serNum;
    /**< Serializer number                                                    */
    Mcasp_SerMode       serMode;
    /**< Serializer mode                                                      */
}Mcasp_SerModeQuery;

/**
 *  \brief The following structure will be used in
 *  MCASP_HwStatusQuery_SRCTL_RRDY, and MCASP_HwStatusQuery_SRCTL_XRDY
 */
typedef struct  {
    Mcasp_SerializerNum serNum;
    /**< Serializer number                                                    */
    Bool                serStatus;
    /**< Return value of the query                                            */
}Mcasp_SerQuery;

/**
 *  \brief Loopjob buffers used in EDMA mode
 */
typedef struct
{
    UInt8   scratchBuf[((UInt32)(4U) + MCASP_CACHE_LENGTH)];
    /* This buffer will be aligned and also the same buffer will be used      *
     * for all serializers and also only 4 bytes are required because the     *
     * max wordwidth is 4 and the cache length is used for alignment          */
    UInt32 *scratchBuffer;
}Mcasp_TempBuffer;

#ifdef BIOS_PWRM_ENABLE
/**
 * \brief   Strcuture to hold the information related to the PWRM.
 */
typedef struct
{
    Mcasp_pllDomain       pllDomain;
    /**< Pll domain to be used for the device                                 */

    Bool                  ioSuspend;
    /**< whether the driver is in IO suspend mode (PWRM change is in progress)*/

    PWRM_Event            pwrmEvent;
    /**< Current pwrm event being processed                                   */

    UInt32                constraintMask;
    /**< Constraint mask (for information only)                               */

    UInt32                dependencyCount;
    /**< Current dependency count when the driver is going for sleep or
     * deepsleep                                                              */

    PWRM_NotifyHandle     notifyHandle[Mcasp_MAX_PWRM_EVENTS];
    /**< Handles required for unregistering of the events with PWRM           */

    Fxn                   delayedCompletionFxn[Mcasp_MAX_PWRM_EVENTS];
    /**< delayed completion callback function pointer                         */

    PWRM_ConstraintHandle constraintHandle[Mcasp_MAX_PWRM_CONSTRAINTS];
    /**< Handles required for unregistering of the constraints with PWRM      */
}Mcasp_pwrmInfo;
#endif

/* -------- module-wide state -------- */
/**
 *  \brief module-wide state
 *
 *  inUse in module state points to an array whose size is soc specific
 *  Pointer used to match IDriver codebase.
 */
typedef struct
{
    Bool            *inUse;

    Mcasp_IsrObject *isrObject;
} Mcasp_Module_State;

/* -------- typedefs -------- */

typedef Mcasp_ChannelObj *Mcasp_ChannelHandle;
typedef Mcasp_HwObj *     Mcasp_HwHandle;

extern Int32 Mcasp_localConfigRcvSection(Mcasp_Object            *instHandle,
                                         const Mcasp_HwSetupData *rcvData);

extern Int32 Mcasp_localConfigXmtSection(Mcasp_Object            *instHandle,
                                         const Mcasp_HwSetupData *xmtData);

extern Void Mcasp_localSmReset(Mcasp_ChannelHandle chanHandle);

extern Void Mcasp_localSmSet(Mcasp_ChannelHandle chanHandle);

extern Int32 Mcasp_localAbortReset(Mcasp_ChannelHandle chanHandle);

extern Void Mcasp_localCompleteCurrentIo(Mcasp_ChannelHandle chanHandle);

extern Int32 Mcasp_localResetXmt(Mcasp_HwHandle hMcasp);

extern Int32 Mcasp_localResetRcv(Mcasp_HwHandle hMcasp);

extern Int32 Mcasp_localEdmaProcessPkt(Ptr chanp, const IOM_Packet *ioPacket);

extern Int32 Mcasp_localCancelAndAbortAllIo(Mcasp_ChannelHandle chanHandle);

extern Void Mcasp_localSetupHwInfo(Mcasp_HwHandle       hMcasp,
                                   const Mcasp_HwSetup *myHwSetup);

extern Void Mcasp_localActivateSmFsForBoth(const Mcasp_Object *instHandle);

extern Void Mcasp_localActivateSmFsForXmt(const Mcasp_Object *instHandle);

extern Void Mcasp_localActivateSmFsForRcv(const Mcasp_Object *instHandle);

extern Void Mcasp_localDeactivateSmFsForXmt(const Mcasp_Object *instHandle);

extern Void Mcasp_localDeactivateSmFsForRcv(const Mcasp_Object *instHandle);

extern Int32 Mcasp_localUpdtDtPktToLnkPrms(Mcasp_ChannelHandle chanHandle,
                                           const IOM_Packet   *ioPacket);

extern Int32 Mcasp_localEdmaChanPaRAMsetup(Mcasp_ChannelHandle chanHandle);

extern Int32 Mcasp_localSubmitIoctl(Mcasp_ChannelHandle chanHandle,
                                    Uns                 cmd,
                                    Ptr                 arg,
                                    Ptr                 param);

extern Int32 Mcasp_localSetupEdmaDuringOpen(Mcasp_ChannelHandle chanHandle);

extern Void Mcasp_localEdmaCallback(UInt32             tcc,
                                    EDMA3_RM_TccStatus status,
                                    Ptr                data);

extern Int32 Mcasp_localGetIndicesSyncType(Mcasp_ChannelHandle chanHandle,
                                           volatile Int16     *bIndex,
                                           volatile Int16     *cIndex,
                                           volatile UInt16    *aCnt,
                                           volatile UInt16    *bCnt,
                                           volatile UInt16    *cCnt,
                                           EDMA3_DRV_SyncType *syncType,
                                           Bool                forLoopJobBuf);

extern Int32 Mcasp_localAbortRequests(Ptr handle, Ptr arg);

extern Void Mcasp_localGetNextIndex(UInt32 *index);

extern Int32 Mcasp_localPrcmOff(const Mcasp_Object *instHandle);

extern Int32 Mcasp_localPrcmOn(const Mcasp_Object *instHandle);

extern Int32 Mcasp_loadPendedIops(Mcasp_ChannelObj *chanHandle);

extern Void Mcasp_localLoadPktToEdma(Mcasp_ChannelObj *chanHandle,
                                     const IOM_Packet *ioPacket);

extern Void Mcasp_localHandlePwrmEvent(Mcasp_Object     *instHandle,
                                       Mcasp_ChannelObj *chanHandle);

#ifdef __cplusplus
}
#endif

#endif  /*MCASPLOCAL_H_ */

/*  @}  */
