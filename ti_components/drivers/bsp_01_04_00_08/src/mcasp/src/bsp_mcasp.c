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
 * \file      Mcasp.c
 *
 * \brief     Generic McASP Driver for SYS/BIOS Platform.It uses the EDMA for
 *            data transfer.
 *
 *            This file implements the McASP IOM driver to be used with
 *            SYS-BIOS operating system.
 *
 * \author    Platform Support Group
 *
 * \version   0.1 Created for DM814x/C6A811x platform.
 *
 */

/* ========================================================================== */
/*                          INCLUDE FILES                                     */
/* ========================================================================== */

#include <xdc/std.h>
#include <string.h>
#include <assert.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/io/IOM.h>
#include <ti/sysbios/knl/Swi.h>
#include <ti/sysbios/hal/Cache.h>
#include <ti/sysbios/knl/Queue.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sdo/edma3/drv/edma3_drv.h>
#include <bsp_mcaspPriv.h>

#ifdef BUILD_DSP
#include <ti/sysbios/family/c64p/Hwi.h>
#include <ti/sysbios/family/c64p/EventCombiner.h>
#else
#include <osal/bsp_osal.h>
#include <ti/sysbios/hal/Hwi.h>
#endif

#include <soc.h>
#include <soc_defines.h>

#if defined (TDA2XX_FAMILY_BUILD)

/* These are not yet defined in soc.h files, hence defining in local files */

/** @brief Base address of McASP memory mapped registers                      */
#define SOC_MCASP0_CTRL_REGS               (UInt32) (SOC_MCASP1_CFG_BASE)
#define SOC_MCASP0_FIFO_REGS                ((UInt32)              \
                                             SOC_MCASP1_CFG_BASE + \
                                             (UInt32) 0x1000U)
#define SOC_MCASP0_DATA_REGS               (UInt32) (SOC_MCASP1_BASE)

#define SOC_MCASP1_CTRL_REGS               (UInt32) (SOC_MCASP2_CFG_BASE)
#define SOC_MCASP1_FIFO_REGS                ((UInt32)              \
                                             SOC_MCASP2_CFG_BASE + \
                                             (UInt32) 0x1000U)
#define SOC_MCASP1_DATA_REGS               (UInt32) (SOC_MCASP2_BASE)

#define SOC_MCASP2_CTRL_REGS               (UInt32) (SOC_MCASP3_CFG_BASE)
#define SOC_MCASP2_FIFO_REGS                ((UInt32)              \
                                             SOC_MCASP3_CFG_BASE + \
                                             (UInt32) 0x1000U)
#define SOC_MCASP2_DATA_REGS               (UInt32) (SOC_MCASP3_BASE)

#define SOC_MCASP3_CTRL_REGS              (UInt32) (SOC_MCASP4_CFG_BASE)
#define SOC_MCASP3_FIFO_REGS              ((UInt32)              \
                                           SOC_MCASP4_CFG_BASE + \
                                           (UInt32) 0x1000U)
#define SOC_MCASP3_DATA_REGS               (UInt32) (SOC_MCASP4_DAT_BASE)

#define SOC_MCASP4_CTRL_REGS               (UInt32) (SOC_MCASP5_CFG_BASE)
#define SOC_MCASP4_FIFO_REGS              ((UInt32)              \
                                           SOC_MCASP5_CFG_BASE + \
                                           (UInt32) 0x1000U)
#define SOC_MCASP4_DATA_REGS               (UInt32) (SOC_MCASP5_DAT_BASE)

#define SOC_MCASP5_CTRL_REGS               (UInt32) (SOC_MCASP6_CFG_BASE)
#define SOC_MCASP5_FIFO_REGS               ((UInt32)              \
                                            SOC_MCASP6_CFG_BASE + \
                                            (UInt32) 0x1000U)
#define SOC_MCASP5_DATA_REGS               (UInt32) (SOC_MCASP6_DAT_BASE)

#define SOC_MCASP6_CTRL_REGS               (UInt32) (SOC_MCASP7_CFG_BASE)
#define SOC_MCASP6_FIFO_REGS               ((UInt32)              \
                                            SOC_MCASP7_CFG_BASE + \
                                            (UInt32) 0x1000U)
#define SOC_MCASP6_DATA_REGS               (UInt32) (SOC_MCASP7_DAT_BASE)

#define SOC_MCASP7_CTRL_REGS               (UInt32) (SOC_MCASP8_CFG_BASE)
#define SOC_MCASP7_FIFO_REGS               ((UInt32)              \
                                            SOC_MCASP8_CFG_BASE + \
                                            (UInt32) 0x1000U)
#define SOC_MCASP7_DATA_REGS               (UInt32) (SOC_MCASP8_DAT_BASE)

#endif

#if defined (TDA3XX_FAMILY_BUILD)

/** @brief Base address of McASP memory mapped registers                      */
#define SOC_MCASP0_CTRL_REGS               (UInt32) (SOC_MCASP1_CFG_BASE)
#define SOC_MCASP0_FIFO_REGS                ((UInt32)              \
                                             SOC_MCASP1_CFG_BASE + \
                                             (UInt32) 0x1000U)
#define SOC_MCASP0_DATA_REGS               (UInt32) (SOC_MCASP1_BASE)

#endif

/* -------- constants -------- */

const Mcasp_Params        Mcasp_PARAMS =
{
    TRUE,   /* enablecache */
    0x0,    /* hwiNumber */
    FALSE,  /* prcmPwrmEnable*/
    NULL,   /* prcmHandle   */
    FALSE,  /* isDataBufferPayloadStructure */
    {
        {
            (UInt32) 0x0,         /* pfunc   */
            (UInt32) 0x1,         /* pdir    */
            (UInt32) 0x0,         /* ctl     */
            (UInt32) 0x0,         /* ditCtl  */
            (UInt32) 0x0,         /* dlbMode */
            (UInt32) 0x0,         /* amute   */
            {
                (UInt32) 0x0,     /* [0] */
                (UInt32) 0x0,     /* [1] */
                (UInt32) 0x0,     /* [2] */
                (UInt32) 0x0,     /* [3] */
                (UInt32) 0x0,     /* [4] */
                (UInt32) 0x0,     /* [5] */
                (UInt32) 0x0,     /* [6] */
                (UInt32) 0x0,     /* [7] */
                (UInt32) 0x0,     /* [8] */
                (UInt32) 0x0,     /* [9] */
                (UInt32) 0x0,     /* [10] */
                (UInt32) 0x0,     /* [11] */
                (UInt32) 0x0,     /* [12] */
                (UInt32) 0x0,     /* [13] */
                (UInt32) 0x0,     /* [14] */
                (UInt32) 0x0,     /* [15] */
            }
            ,                     /* serSetup */
        }
        ,                         /* glb */
        {
            (UInt32) 0xffffffffU, /* mask    */
            (UInt32) 0x0,         /* fmt         */
            (UInt32) 0x0,         /* frSyncCtl*/
            (UInt32) 0x1,         /* tdm         */
            (UInt32) 0x0,         /* intCtl  */
            (UInt32) 0x1ff,       /* stat    */
            (UInt32) 0x0,         /* evtCtl  */
            {
                (UInt32) 0x3,     /* clkSetupClk  */
                (UInt32) 0x8046,  /* clkSetupHiClk*/
                (UInt32) 0x0,     /* clkChk      */
            }
            ,                     /* clk */
        }
        ,                         /* rx */
        {
            (UInt32) 0xffffffffU, /* mask    */
            (UInt32) 0x0,         /* fmt         */
            (UInt32) 0x2,         /* frSyncCtl*/
            (UInt32) 0x1,         /* tdm         */
            (UInt32) 0x0,         /* intCtl  */
            (UInt32) 0x1ff,       /* stat    */
            (UInt32) 0x0,         /* evtCtl  */
            {
                (UInt32) 0x23,    /* clkSetupClk  */
                (UInt32) 0x8046,  /* clkSetupHiClk*/
                (UInt32) 0x0,     /* clkChk      */
            }
            ,                     /* clk */
        }
        ,                         /* tx */
        (UInt32) 0x1,             /* emu*/
    }
    ,                             /* mcaspHwSetup */
    FALSE,                        /* prcmPwrmEnable  */
    0                             /* prcmDevId */
};
/* ========================================================================== */
/*                       GLOBAL MODULE STATE                                  */
/* ========================================================================== */
/**
 *  \brief  Array which is part of Mcasp Module State
 *
 */
static Bool               gMcaspModInUse[CSL_MCASP_PER_CNT];

/*
 * \brief  Array to contain the Isr related information for all instances.
 */
static Mcasp_IsrObject    isrInstanceObject[CSL_MCASP_PER_CNT];

/**
 *  \brief  Mcasp Module State Object
 */
static Mcasp_Module_State Mcasp_module =
{&gMcaspModInUse[0], &isrInstanceObject[0]};

/**
 *  \brief  Array of Mcasp instance State objects array
 */
static Mcasp_Object       Mcasp_Instances[CSL_MCASP_PER_CNT];

#if (defined (TDA2XX_FAMILY_BUILD) || defined (TDA3XX_FAMILY_BUILD)) && \
    defined (BUILD_M4)
/**
 * \brief  Global array of Hwi handles;
 */
static BspOsal_IntrHandle gHwiHandle[CSL_MCASP_PER_CNT][2];
#endif

/**
 *  \brief  Array for device information per instance
 */
Mcasp_HwInfo              Mcasp_deviceInstInfo[CSL_MCASP_PER_CNT];

#ifdef Mcasp_LOOPJOB_ENABLED
/**
 *  \brief  Destination loop buffer per instance
 *
 * \note   Buffer used during the loop job mode for the Transmit section
 */
Mcasp_TempBuffer          Mcasp_loopDstBuf[CSL_MCASP_PER_CNT];
/**
 * \brief  Receive loop buffer per instance
 *
 * \note   Buffer used during the loop job mode for the Receive section
 */
Mcasp_TempBuffer          Mcasp_loopSrcBuf[CSL_MCASP_PER_CNT];
#endif /* Mcasp_LOOPJOB_ENABLED */
/**
 *  \brief  Mute buffer per instance
 */
Mcasp_TempBuffer          Mcasp_muteBuf[CSL_MCASP_PER_CNT];

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
static Int mcaspMdBindDev(Ptr *devp, Int devId, Ptr devParams);
static Int mcaspMdUnBindDev(Ptr devp);
static Int mcaspMdCreateChan(
    Ptr             *chanp,
    Ptr              devp,
    String           name,
    Int              mode,
    Ptr              chanParams,
    IOM_TiomCallback cbFxn,
    Ptr              cbArg
    );
static Int mcaspMdDeleteChan(Ptr chanp);
static Int mcaspMdSubmitChan(Ptr chanp, IOM_Packet *ioPacket);
static Int mcaspMdControlChan(Ptr chanp, Uns cmd, Ptr cmdArgs);
#ifdef __cplusplus
}
#endif
IOM_Fxns Mcasp_IOMFXNS =
{
    &mcaspMdBindDev,
    &mcaspMdUnBindDev,
    &mcaspMdControlChan,
    &mcaspMdCreateChan,
    &mcaspMdDeleteChan,
    &mcaspMdSubmitChan,
};
static Void mcaspInit(UInt32 instNum);

Void mcaspIsr(UArg arg);

Void mcaspIsrInput(UArg chanp);

Void mcaspIsrOutput(UArg chanp);

static Void mcaspUnRegisterInt(UInt16 devid, UInt16 evt, Int mode);

static Void mcaspBitSetGblCtl(const Mcasp_Object *instHandle,
                              UInt32              bitMaskVal);

static Void mcaspBitSetGblXCtl(const Mcasp_Object *instHandle,
                               UInt32              bitMaskVal);

static Void mcaspBitRemoveGblRCtl(const Mcasp_Object *instHandle,
                                  UInt32              bitMaskVal);

static Void mcaspBitRemoveGblXCtl(const Mcasp_Object *instHandle,
                                  UInt32              bitMaskVal);

static Void mcaspMultiSerGlobalRestore(Ptr chanp);

static Void mcaspBitSetGblRCtl(const Mcasp_Object *instHandle,
                               UInt32              bitMaskVal);

static Int32 mcaspSubmitReq(Mcasp_ChannelHandle chanHandle,
                            IOM_Packet         *ioPacket);

static Void mcaspRegisterInt(Ptr    chanp,
                             UInt32 instNum,
                             UInt16 evt,
                             Ptr    intIsr);

static Void mcaspSetSerXmt(Mcasp_HwHandle      hMcasp,
                           Mcasp_SerializerNum serNum);

static Void mcaspSetSerRcv(Mcasp_HwHandle      hMcasp,
                           Mcasp_SerializerNum serNum);

static Int32 mcaspSetDitMode(Mcasp_HwHandle hMcasp,
                             Bool           ditFlag);

static Bool mcaspIsRequestedSerzsFree(const Mcasp_Object *instHandle,
                                      Ptr                 params);

static Int32 mcaspSetDitMode(Mcasp_HwHandle hMcasp,
                             Bool           ditFlag);

static Void mcaspMultiSerInitializationRcv(Mcasp_Object *instHandle,
                                           Ptr           params);

static Void mcaspMultiSerInitializationXmt(Mcasp_Object *instHandle,
                                           Ptr           params);

static Int32 mcaspConfigureXmtChannel(Mcasp_Object *instHandle,
                                      Ptr           params);

static Int32 mcaspConfigureRcvChannel(Mcasp_Object *instHandle,
                                      Ptr           params);

static Int32 mcaspWriteChanStatRam(Mcasp_HwHandle           hMcasp,
                                   const Mcasp_ChStatusRam *chanStatRam);

static Int32 mcaspWriteUserDataRam(Mcasp_HwHandle           hMcasp,
                                   const Mcasp_UserDataRam *userDataRam);

static Void mcaspConfigureFifo(const Mcasp_HwObj      *hMcasp,
                               const Mcasp_ChannelObj *chanHandle,
                               Bool                    enableHwFifo);

static Int32  mcaspValidateBufferConfig(Mcasp_ChannelHandle     chanHandle,
                                        const Mcasp_ChanParams *params);

static Void Mcasp_localIsrSwiFxn(UArg arg0, UArg arg1);

#if defined (BIOS_PWRM_ENABLE) && !defined (Mcasp_LOOPJOB_ENABLED)
static Int32 McaspRegisterNotification(Mcasp_Object *instHandle);

static Int32 McaspUnregisterNotification(Mcasp_Object *instHandle);

static Int32 McaspUnregisterConstraints(Mcasp_Object *instHandle);

static PWRM_NotifyResponse McaspNotifyCallback(PWRM_Event eventType,
                                               UArg       eventArg1,
                                               UArg       eventArg2,
                                               UArg       clientArg);

static PWRM_NotifyResponse McaspSuspendCurrentIops(Mcasp_Object *instHandle,
                                                   PWRM_Event    eventType);

static Int32 McaspUnregisterConstraints(Mcasp_Object *instHandle);

#endif

#ifndef Mcasp_LOOPJOB_ENABLED
static Void Mcasp_swiTxFifo(UArg arg0, UArg arg1);
#endif

static Void Mcasp_enableInterrupt(UInt32 cpuEventNum);
static Void Mcasp_disableInterrupt(UInt32 cpuEventNum);

/* ========================================================================== */
/*                            GLOBAL VARIABLES                                */
/* ========================================================================== */

/* ========================================================================== */
/*                          FUNCTION DEFINTIONS                               */
/* ========================================================================== */

/* ========================================================================== */
/*                           MODULE FUNCTIONS                                 */
/* ========================================================================== */

/*
 * \brief   Initializes McASP IOM driver's data structures
 *
 *          This function initializes the McASP IOM driver's data structures
 *          including instance objects and channel objects.This function needs
 *          to be called at part of BIOS initialization by setting initFxn for
 *          that particular UDEV instance or by calling this function as part of
 *          user specific initFxn.
 *
 * \param   [IN]  none
 *
 * \return  None
 */
Void Mcasp_init(Void)
{
    Int         i;
    static Bool oneTimeMcaspInit = (Bool) FALSE;

    if ((Bool) FALSE == oneTimeMcaspInit)
    {
        oneTimeMcaspInit = (Bool) TRUE;

        for (i = (Int) 0; i < (Int) CSL_MCASP_PER_CNT; i++)
        {
            /* have to initialize statically */
            Mcasp_module.inUse[i] = (Bool) FALSE;
            memset((Void *) &Mcasp_Instances[i], 0x0, sizeof (Mcasp_Object));

            Mcasp_module.isrObject[i].isIsrRegistered[0] = (Bool) FALSE;
            Mcasp_module.isrObject[i].isIsrRegistered[1] = (Bool) FALSE;
            Mcasp_module.isrObject[i].chanEnabled[0]     = (Bool) FALSE;
            Mcasp_module.isrObject[i].chanEnabled[1]     = (Bool) FALSE;
            Mcasp_module.isrObject[i].instHandle         = NULL;
            Mcasp_module.isrObject[i].isrSwiTaskHandle   = NULL;

            if (i == 0)
            {
                Mcasp_deviceInstInfo[i].ditSupport  = (Bool) FALSE;
                Mcasp_deviceInstInfo[i].baseAddress =
                    SOC_MCASP0_CTRL_REGS;
                Mcasp_deviceInstInfo[i].fifoAddress =
                    SOC_MCASP0_FIFO_REGS;
                Mcasp_deviceInstInfo[i].dataAddress =
                    SOC_MCASP0_DATA_REGS;
                Mcasp_deviceInstInfo[i].numSerializers =
                    CSL_MCASP_0_NumSerializers;
                Mcasp_deviceInstInfo[i].txCpuEventNumber =
                    (UInt32) CSL_INTC_EVENTID_MCASP0_TXINT;
                Mcasp_deviceInstInfo[i].rxCpuEventNumber =
                    (UInt32) CSL_INTC_EVENTID_MCASP0_RXINT;
                Mcasp_deviceInstInfo[i].rxDmaEventNumber =
                    (UInt32) CSL_EDMA3_CHA_MCASP0_RX;
                Mcasp_deviceInstInfo[i].txDmaEventNumber =
                    (UInt32) CSL_EDMA3_CHA_MCASP0_TX;
#ifndef BIOS_PWRM_ENABLE
                /*              Mcasp_deviceInstInfo[i].pwrmPrcmId =
                 *                            (UInt32)CSL_PRCM_NUMBER_MCASP_0;*/
#else
                /*              Mcasp_deviceInstInfo[i].pwrmPrcmId =
                 *                            (UInt32)CSL_PRCM_NUMBER_MCASP_0;*/
#endif
                /*              Mcasp_deviceInstInfo[i].prcmInstance =
                 *                                (UInt32)CSL_PRCM_INST_MCASP_0;
                 * */
                /* Component is always instnum+1 for Tda2xx */
                /*              Mcasp_deviceInstInfo[i].component =
                 *                                         (CRED_index_t)MCASP1;
                 **/
            }
#if !defined (TDA3XX_FAMILY_BUILD)
            else if (i == 1)
            {
                Mcasp_deviceInstInfo[i].ditSupport  = (Bool) FALSE;
                Mcasp_deviceInstInfo[i].baseAddress =
                    (UInt32) SOC_MCASP1_CTRL_REGS;
                Mcasp_deviceInstInfo[i].fifoAddress =
                    (UInt32) SOC_MCASP1_FIFO_REGS;
                Mcasp_deviceInstInfo[i].dataAddress =
                    (UInt32) SOC_MCASP1_DATA_REGS;

                Mcasp_deviceInstInfo[i].numSerializers =
                    CSL_MCASP_1_NumSerializers;

                Mcasp_deviceInstInfo[i].txCpuEventNumber =
                    (UInt32) CSL_INTC_EVENTID_MCASP1_TXINT;
                Mcasp_deviceInstInfo[i].rxCpuEventNumber =
                    (UInt32) CSL_INTC_EVENTID_MCASP1_RXINT;

                Mcasp_deviceInstInfo[i].rxDmaEventNumber =
                    (UInt32) CSL_EDMA3_CHA_MCASP1_RX;
                Mcasp_deviceInstInfo[i].txDmaEventNumber =
                    (UInt32) CSL_EDMA3_CHA_MCASP1_TX;
#ifndef BIOS_PWRM_ENABLE
                /*              Mcasp_deviceInstInfo[i].pwrmPrcmId =
                 *                   (UInt32)CSL_PRCM_NUMBER_MCASP_1;
                 * */
#else
                /*              Mcasp_deviceInstInfo[i].pwrmPrcmId =
                 *                      (UInt32)CSL_PRCM_NUMBER_MCASP_1;*/
#endif
                /*              Mcasp_deviceInstInfo[i].prcmInstance =
                 *                              (UInt32)CSL_PRCM_INST_MCASP_1;*/

                /*              Mcasp_deviceInstInfo[i].component =
                 *                                       (CRED_index_t)MCASP2;*/
            }
            else if (i == 2)
            {
                Mcasp_deviceInstInfo[i].ditSupport  = (Bool) FALSE;
                Mcasp_deviceInstInfo[i].baseAddress =
                    (UInt32) SOC_MCASP2_CTRL_REGS;
                Mcasp_deviceInstInfo[i].fifoAddress =
                    (UInt32) SOC_MCASP2_FIFO_REGS;
                Mcasp_deviceInstInfo[i].dataAddress =
                    (UInt32) SOC_MCASP2_DATA_REGS;

                Mcasp_deviceInstInfo[i].numSerializers =
                    CSL_MCASP_2_NumSerializers;

                Mcasp_deviceInstInfo[i].txCpuEventNumber =
                    (UInt32) CSL_INTC_EVENTID_MCASP2_TXINT;
                Mcasp_deviceInstInfo[i].rxCpuEventNumber =
                    (UInt32) CSL_INTC_EVENTID_MCASP2_RXINT;

                Mcasp_deviceInstInfo[i].rxDmaEventNumber =
                    (UInt32) CSL_EDMA3_CHA_MCASP2_RX;
                Mcasp_deviceInstInfo[i].txDmaEventNumber =
                    (UInt32) CSL_EDMA3_CHA_MCASP2_TX;
                /*
                 * #ifndef BIOS_PWRM_ENABLE
                 *              Mcasp_deviceInstInfo[i].pwrmPrcmId =
                 *                    (UInt32)CSL_PRCM_NUMBER_MCASP_2;
                 * #else
                 *              Mcasp_deviceInstInfo[i].pwrmPrcmId =
                 *                       (UInt32)CSL_PRCM_NUMBER_MCASP_2;
                 * #endif
                 *              Mcasp_deviceInstInfo[i].prcmInstance =
                 *                                (UInt32)CSL_PRCM_INST_MCASP_2;
                 */
                /*              Mcasp_deviceInstInfo[i].component =
                 *                                       (CRED_index_t)MCASP3;*/
            }
            else if (i == 3)
            {
                Mcasp_deviceInstInfo[i].ditSupport  = (Bool) FALSE;
                Mcasp_deviceInstInfo[i].baseAddress =
                    (UInt32) SOC_MCASP3_CTRL_REGS;
                Mcasp_deviceInstInfo[i].fifoAddress =
                    (UInt32) SOC_MCASP3_FIFO_REGS;
                Mcasp_deviceInstInfo[i].dataAddress =
                    (UInt32) SOC_MCASP3_DATA_REGS;

                Mcasp_deviceInstInfo[i].numSerializers =
                    CSL_MCASP_3_NumSerializers;

                Mcasp_deviceInstInfo[i].txCpuEventNumber =
                    (UInt32) CSL_INTC_EVENTID_MCASP3_TXINT;
                Mcasp_deviceInstInfo[i].rxCpuEventNumber =
                    (UInt32) CSL_INTC_EVENTID_MCASP3_RXINT;

                Mcasp_deviceInstInfo[i].rxDmaEventNumber =
                    (UInt32) CSL_EDMA3_CHA_MCASP3_RX;
                Mcasp_deviceInstInfo[i].txDmaEventNumber =
                    (UInt32) CSL_EDMA3_CHA_MCASP3_TX;
                /*
                 * #ifndef BIOS_PWRM_ENABLE
                 *              Mcasp_deviceInstInfo[i].pwrmPrcmId =
                 *                              (UInt32)CSL_PRCM_NUMBER_MCASP_3;
                 * #else
                 *              Mcasp_deviceInstInfo[i].pwrmPrcmId =
                 *                              (UInt32)CSL_PRCM_NUMBER_MCASP_3;
                 * #endif
                 *              Mcasp_deviceInstInfo[i].prcmInstance =
                 *                                (UInt32)CSL_PRCM_INST_MCASP_3;
                 */
                /*              Mcasp_deviceInstInfo[i].component =
                 *                                         (CRED_index_t)MCASP4;
                 **/
                /* Commented out since only 3 instances supported on Tda2xx */
            }
            else if (i == 4)
            {
                Mcasp_deviceInstInfo[i].ditSupport  = (Bool) FALSE;
                Mcasp_deviceInstInfo[i].baseAddress =
                    (UInt32) SOC_MCASP4_CTRL_REGS;
                Mcasp_deviceInstInfo[i].fifoAddress =
                    (UInt32) SOC_MCASP4_FIFO_REGS;
                Mcasp_deviceInstInfo[i].dataAddress =
                    (UInt32) SOC_MCASP4_DATA_REGS;

                Mcasp_deviceInstInfo[i].numSerializers =
                    CSL_MCASP_4_NumSerializers;

                Mcasp_deviceInstInfo[i].txCpuEventNumber =
                    (UInt32) CSL_INTC_EVENTID_MCASP4_TXINT;
                Mcasp_deviceInstInfo[i].rxCpuEventNumber =
                    (UInt32) CSL_INTC_EVENTID_MCASP4_RXINT;

                Mcasp_deviceInstInfo[i].rxDmaEventNumber =
                    (UInt32) CSL_EDMA3_CHA_MCASP4_RX;
                Mcasp_deviceInstInfo[i].txDmaEventNumber =
                    (UInt32) CSL_EDMA3_CHA_MCASP4_TX;
                /*
                 * #ifndef BIOS_PWRM_ENABLE
                 *              Mcasp_deviceInstInfo[i].pwrmPrcmId =
                 *                              (UInt32)CSL_PRCM_NUMBER_MCASP_4;
                 * #else
                 *              Mcasp_deviceInstInfo[i].pwrmPrcmId =
                 *                              (UInt32)CSL_PRCM_NUMBER_MCASP_4;
                 * #endif
                 *              Mcasp_deviceInstInfo[i].prcmInstance =
                 *
                 *                                (UInt32)CSL_PRCM_INST_MCASP_4;
                 */
                /*              Mcasp_deviceInstInfo[i].component =
                 *
                 *                                       (CRED_index_t)MCASP5;*/
            }
            else if (i == 5)
            {
                Mcasp_deviceInstInfo[i].ditSupport  = (Bool) FALSE;
                Mcasp_deviceInstInfo[i].baseAddress =
                    (UInt32) SOC_MCASP5_CTRL_REGS;
                Mcasp_deviceInstInfo[i].fifoAddress =
                    (UInt32) SOC_MCASP5_FIFO_REGS;
                Mcasp_deviceInstInfo[i].dataAddress =
                    (UInt32) SOC_MCASP5_DATA_REGS;

                Mcasp_deviceInstInfo[i].numSerializers =
                    CSL_MCASP_5_NumSerializers;

                Mcasp_deviceInstInfo[i].txCpuEventNumber =
                    (UInt32) CSL_INTC_EVENTID_MCASP5_TXINT;
                Mcasp_deviceInstInfo[i].rxCpuEventNumber =
                    (UInt32) CSL_INTC_EVENTID_MCASP5_RXINT;

                Mcasp_deviceInstInfo[i].rxDmaEventNumber =
                    (UInt32) CSL_EDMA3_CHA_MCASP5_RX;
                Mcasp_deviceInstInfo[i].txDmaEventNumber =
                    (UInt32) CSL_EDMA3_CHA_MCASP5_TX;
                /*
                 * #ifndef BIOS_PWRM_ENABLE
                 *              Mcasp_deviceInstInfo[i].pwrmPrcmId =
                 *                              (UInt32)CSL_PRCM_NUMBER_MCASP_5;
                 * #else
                 *              Mcasp_deviceInstInfo[i].pwrmPrcmId =
                 *                              (UInt32)CSL_PRCM_NUMBER_MCASP_5;
                 * #endif
                 *              Mcasp_deviceInstInfo[i].prcmInstance =
                 *
                 *                                (UInt32)CSL_PRCM_INST_MCASP_5;
                 */
                /*              Mcasp_deviceInstInfo[i].component =
                 *                                       (CRED_index_t)MCASP1;*/
            }
#if (defined (TDA2XX_FAMILY_BUILD))
            else if (i == 6)
            {
                Mcasp_deviceInstInfo[i].ditSupport  = (Bool) FALSE;
                Mcasp_deviceInstInfo[i].baseAddress =
                    (UInt32) SOC_MCASP6_CTRL_REGS;
                Mcasp_deviceInstInfo[i].fifoAddress =
                    (UInt32) SOC_MCASP6_FIFO_REGS;
                Mcasp_deviceInstInfo[i].dataAddress =
                    (UInt32) SOC_MCASP6_DATA_REGS;

                Mcasp_deviceInstInfo[i].numSerializers =
                    CSL_MCASP_6_NumSerializers;

                Mcasp_deviceInstInfo[i].txCpuEventNumber =
                    (UInt32) CSL_INTC_EVENTID_MCASP6_TXINT;
                Mcasp_deviceInstInfo[i].rxCpuEventNumber =
                    (UInt32) CSL_INTC_EVENTID_MCASP6_RXINT;

                Mcasp_deviceInstInfo[i].rxDmaEventNumber =
                    (UInt32) CSL_EDMA3_CHA_MCASP6_RX;
                Mcasp_deviceInstInfo[i].txDmaEventNumber =
                    (UInt32) CSL_EDMA3_CHA_MCASP6_TX;
            }
            else if (i == 7)
            {
                Mcasp_deviceInstInfo[i].ditSupport  = (Bool) FALSE;
                Mcasp_deviceInstInfo[i].baseAddress =
                    (UInt32) SOC_MCASP7_CTRL_REGS;
                Mcasp_deviceInstInfo[i].fifoAddress =
                    (UInt32) SOC_MCASP7_FIFO_REGS;
                Mcasp_deviceInstInfo[i].dataAddress =
                    (UInt32) SOC_MCASP7_DATA_REGS;

                Mcasp_deviceInstInfo[i].numSerializers =
                    CSL_MCASP_7_NumSerializers;

                Mcasp_deviceInstInfo[i].txCpuEventNumber =
                    (UInt32) CSL_INTC_EVENTID_MCASP7_TXINT;
                Mcasp_deviceInstInfo[i].rxCpuEventNumber =
                    (UInt32) CSL_INTC_EVENTID_MCASP7_RXINT;

                Mcasp_deviceInstInfo[i].rxDmaEventNumber =
                    (UInt32) CSL_EDMA3_CHA_MCASP7_RX;
                Mcasp_deviceInstInfo[i].txDmaEventNumber =
                    (UInt32) CSL_EDMA3_CHA_MCASP7_TX;
            }
#endif
            else
            {
                /* do nothing
                 *                                                    */
            }
#endif
        }
        /* intialise the loop job buffers and the mute buffers for all instances
         * */
#ifdef Mcasp_LOOPJOB_ENABLED
        memset((Void *) Mcasp_loopDstBuf, 0x0,
               sizeof (Mcasp_TempBuffer) * CSL_MCASP_PER_CNT);
        memset((Void *) Mcasp_loopSrcBuf, 0x0,
               sizeof (Mcasp_TempBuffer) * CSL_MCASP_PER_CNT);
#endif  /* Mcasp_LOOPJOB_ENABLED */
        memset((Void *) Mcasp_muteBuf, 0x0,
               sizeof (Mcasp_TempBuffer) * CSL_MCASP_PER_CNT);
    }
}

/*
 *  \brief  Function called by Bios during instance initialisation
 *
 *  \param  devp        [OUT] pointer to hold the device Handle
 *  \param  devId       [IN]  Instance number of the Mcasp to create
 *  \param  devParams   [IN]  Pointer to the user supplied device parameters
 *
 *  \return IOM_COMPLETED    if success
 *          Error ID         in case of error
 *
 *
 *  \enter  devp        should be non NULL and valid pointer,
 *          devId       should be < CSL_MCASP_PER_CNT
 *          devParams   should be non NULL and valid pointer,
 *
 *  \leave  Not implemented
 */
static Int mcaspMdBindDev(Ptr *devp, Int devId, Ptr devParams)
{
    Mcasp_Object *instHandle = NULL;
    Mcasp_Params *params     = NULL;
    Int32         status     = IOM_COMPLETED;
    UInt32        count      = 0;
    UInt32        key        = 0;
    Swi_Params    swiParams  = {0};

    if (NULL == devParams)
    {
        params = (Mcasp_Params *) &Mcasp_PARAMS;
    }
    else
    {
        params = (Mcasp_Params *) devParams;
    }

    if ((Int) CSL_MCASP_PER_CNT <= devId)
    {
        status = IOM_EBADARGS;
    }

    if (IOM_COMPLETED == status)
    {
        instHandle = &Mcasp_Instances[devId];

        if ((Bool) TRUE == Mcasp_module.inUse[devId])
        {
            status = IOM_EBADARGS;
        }
    }

    /* End parameter checking
     *                                                    */

    if (IOM_COMPLETED == status)
    {
        /* critical section starts                                            */
        key = (UInt32) Hwi_disable();

        Mcasp_module.inUse[devId] = (Bool) TRUE;
        instHandle->devState      = Mcasp_DriverState_CREATED;

        /* critical section ends                                              */
        Hwi_restore(key);

        /* initialise the data structures                                     */
        instHandle->instNum        = (UInt16) devId;
        instHandle->enablecache    = params->enablecache;
        instHandle->hwiNumber      = params->hwiNumber;
        instHandle->prcmPwrmEnable = params->prcmPwrmEnable;
        instHandle->prcmHandle     = params->prcmHandle;

        /* stop the state machine of RX and TX                                */
        instHandle->stopSmFsXmt = (Bool) TRUE;
        instHandle->stopSmFsRcv = (Bool) TRUE;

        instHandle->retryCount = Mcasp_POLLED_RETRYCOUNT;

        instHandle->isDataBufferPayloadStructure =
            params->isDataBufferPayloadStructure;

        /* configure the mcasp hardware info                                  */
        instHandle->mcaspHwSetup = params->mcaspHwSetup;

        /* copy the soc related information                                   */
        instHandle->hwInfo.regs     = Mcasp_deviceInstInfo[devId].baseAddress;
        instHandle->hwInfo.fifoRegs = Mcasp_deviceInstInfo[devId].fifoAddress;
        instHandle->hwInfo.dataAddr = Mcasp_deviceInstInfo[devId].dataAddress;

        instHandle->hwInfo.numOfSerializers =
            Mcasp_deviceInstInfo[devId].numSerializers;
        instHandle->hwInfo.edmaTxEventNum =
            Mcasp_deviceInstInfo[devId].txDmaEventNumber;
        instHandle->hwInfo.edmaRxEventNum =
            Mcasp_deviceInstInfo[devId].rxDmaEventNumber;
        instHandle->hwInfo.cpuTxEventNum =
            Mcasp_deviceInstInfo[devId].txCpuEventNumber;
        instHandle->hwInfo.cpuRxEventNum =
            Mcasp_deviceInstInfo[devId].rxCpuEventNumber;
        instHandle->hwInfo.ditStatus =
            Mcasp_deviceInstInfo[devId].ditSupport;
        instHandle->hwInfo.prcmInstance =
            Mcasp_deviceInstInfo[devId].prcmInstance;
        instHandle->hwInfo.pwrmPrcmId = Mcasp_deviceInstInfo[devId].pwrmPrcmId;
        /*        instHandle->hwInfo.regs =
         *Mcasp_deviceInstInfo[devId].component; */

        instHandle->hwInfo.perNo = (Int16) instHandle->instNum;
        instHandle->prcmDevId    = params->prcmDevId;

        /* configure the default values for the transmit channel              */
        instHandle->XmtObj.chanState = Mcasp_DriverState_CLOSED;
        instHandle->XmtObj.mode      = (UInt32) IOM_OUTPUT;
        instHandle->XmtObj.devHandle = NULL;
        instHandle->XmtObj.cbFxn     = NULL;
        instHandle->XmtObj.cbArg     = NULL;

        Queue_construct(&(instHandle->XmtObj.queueReqList), NULL);
        Queue_construct(&(instHandle->XmtObj.queueFloatingList), NULL);

        instHandle->XmtObj.noOfSerAllocated   = 0;
        instHandle->XmtObj.channelOpMode      = Mcasp_ChanMode_XMT_DIT;
        instHandle->XmtObj.isDmaDriven        = (Bool) TRUE;
        instHandle->XmtObj.dataQueuedOnReset  = 0;
        instHandle->XmtObj.intStatus          = 0;
        instHandle->XmtObj.dataPacket         = NULL;
        instHandle->XmtObj.tempPacket         = NULL;
        instHandle->XmtObj.isTempPacketValid  = (Bool) FALSE;
        instHandle->XmtObj.userDataBufferSize = 0;
        instHandle->XmtObj.submitCount        = -1;
        instHandle->XmtObj.edmaHandle         = NULL;
        instHandle->XmtObj.xferChan           = 0;
        instHandle->XmtObj.tcc            = 0;
        instHandle->XmtObj.pramTbl[0]     = 0;
        instHandle->XmtObj.pramTbl[1]     = 0;
        instHandle->XmtObj.pramTblAddr[0] = 0;
        instHandle->XmtObj.pramTblAddr[1] = 0;
        instHandle->XmtObj.nextLinkParamSetToBeUpdated = 0;
        instHandle->XmtObj.loopjobUpdatedinParamset    = (Bool) FALSE;
        instHandle->XmtObj.cpuEventNum           = 0;
        instHandle->XmtObj.xferinProgressIntmode = (Bool) FALSE;
        instHandle->XmtObj.loopJobBuffer         = NULL;
        instHandle->XmtObj.loopJobLength         = 0;
        instHandle->XmtObj.roundedWordWidth      = 0;
        instHandle->XmtObj.currentDataSize       = 0;
        instHandle->XmtObj.bMuteON      = (Bool) FALSE;
        instHandle->XmtObj.paused       = (Bool) FALSE;
        instHandle->XmtObj.edmaCallback = NULL;
        instHandle->XmtObj.gblErrCbk    = NULL;
        instHandle->XmtObj.enableHwFifo = (Bool) TRUE;
        instHandle->XmtObj.nextFlag     = (Bool) FALSE;
        instHandle->XmtObj.currentPacketErrorStatus = IOM_COMPLETED;
        instHandle->XmtObj.noOfSlots    = 0;
        instHandle->XmtObj.isDataPacked = (Bool) FALSE;

        instHandle->XmtObj.dataFormat   = MCASP_BUFFERFORMAT_1SER_1SLOT;
        instHandle->XmtObj.userLoopJob  = (Bool) FALSE;
        instHandle->XmtObj.userIntValue = 0x00000003;

        instHandle->RcvObj.chanState = Mcasp_DriverState_CLOSED;
        instHandle->RcvObj.mode      = (UInt32) IOM_INPUT;
        instHandle->RcvObj.devHandle = NULL;
        instHandle->RcvObj.cbFxn     = NULL;
        instHandle->RcvObj.cbArg     = NULL;

        Queue_construct(&(instHandle->RcvObj.queueReqList), NULL);
        Queue_construct(&(instHandle->RcvObj.queueFloatingList), NULL);

        instHandle->RcvObj.noOfSerAllocated   = 0;
        instHandle->RcvObj.channelOpMode      = Mcasp_ChanMode_RCV;
        instHandle->RcvObj.isDmaDriven        = (Bool) TRUE;
        instHandle->RcvObj.dataQueuedOnReset  = 0;
        instHandle->RcvObj.intStatus          = 0;
        instHandle->RcvObj.dataPacket         = NULL;
        instHandle->RcvObj.tempPacket         = NULL;
        instHandle->RcvObj.isTempPacketValid  = (Bool) FALSE;
        instHandle->RcvObj.userDataBufferSize = 0;
        instHandle->RcvObj.submitCount        = -1;
        instHandle->RcvObj.edmaHandle         = NULL;
        instHandle->RcvObj.xferChan           = 0;
        instHandle->RcvObj.tcc            = 0;
        instHandle->RcvObj.pramTbl[0]     = 0;
        instHandle->RcvObj.pramTbl[1]     = 0;
        instHandle->RcvObj.pramTblAddr[0] = 0;
        instHandle->RcvObj.pramTblAddr[1] = 0;
        instHandle->RcvObj.nextLinkParamSetToBeUpdated = 0;
        instHandle->RcvObj.loopjobUpdatedinParamset    = (Bool) FALSE;
        instHandle->RcvObj.cpuEventNum           = 0;
        instHandle->RcvObj.xferinProgressIntmode = (Bool) FALSE;
        instHandle->RcvObj.loopJobBuffer         = NULL;
        instHandle->RcvObj.loopJobLength         = 0;
        instHandle->RcvObj.roundedWordWidth      = 0;
        instHandle->RcvObj.currentDataSize       = 0;
        instHandle->RcvObj.bMuteON      = (Bool) FALSE;
        instHandle->RcvObj.paused       = (Bool) FALSE;
        instHandle->RcvObj.edmaCallback = NULL;
        instHandle->RcvObj.gblErrCbk    = NULL;
        instHandle->RcvObj.enableHwFifo = (Bool) TRUE;
        instHandle->RcvObj.nextFlag     = (Bool) FALSE;
        instHandle->RcvObj.noOfSlots    = 0;
        instHandle->RcvObj.isDataPacked = (Bool) FALSE;

        instHandle->RcvObj.dataFormat =
            MCASP_BUFFERFORMAT_1SER_1SLOT;
        instHandle->RcvObj.currentPacketErrorStatus = IOM_COMPLETED;
        instHandle->RcvObj.userLoopJob       = (Bool) FALSE;
        instHandle->RcvObj.userLoopJobLength = 0;
        instHandle->RcvObj.userIntValue      = 0x00000003;

        for (count = 0; count < MCASP_NUMSERIALIZERS; count++)
        {
            instHandle->serStatus[count] = Mcasp_SerializerStatus_FREE;
            instHandle->XmtObj.indexOfSersRequested[count] = 0;
            instHandle->RcvObj.indexOfSersRequested[count] = 0;
        }

#ifdef Mcasp_LOOPJOB_ENABLED
        /* driver is compiled in loop Job mode                                */
        instHandle->loopJobMode = (Bool) TRUE;

        if ((Bool) TRUE == instHandle->prcmPwrmEnable)
        {
            /* power management not supported for loop job mode               */
            status = IOM_EBADMODE;
        }
#else
        instHandle->loopJobMode = (Bool) FALSE;
#endif
        if ((IOM_COMPLETED == status) &&
            ((Bool) FALSE == instHandle->prcmPwrmEnable))
        {
#ifdef BIOS_PWRM_ENABLE
            /* power on using bios PWRM API
             */
            /*            status = (Int32)PWRM_setDependency(
             *                  (PWRM_Resource)instHandle->hwInfo.pwrmPrcmId);*/
#else
            /* power on using PRCM API
             */
            /*
             *              Prcm_ModuleClkCtrl(
             *                (Int)instHandle->prcmDevId,
             *                  (UInt32)instHandle->hwInfo.pwrmPrcmId,
             *                  Prcm_moduleClkCtrl_ENABLE,
             *                  NULL);
             */
#endif
        }

#if defined (BIOS_PWRM_ENABLE) && !defined (Mcasp_LOOPJOB_ENABLED)
        if ((IOM_COMPLETED == status) &&
            ((Bool) TRUE == instHandle->prcmPwrmEnable))
        {
            memset(&instHandle->pwrmInfo, 0x00, sizeof (Mcasp_pwrmInfo));

            /* register the notify function for the PWRM events               */
            status = McaspRegisterNotification(instHandle);
        }
#endif

        if (IOM_COMPLETED == status)
        {
            /* power on the module                                            */
            status = Mcasp_localPrcmOn(instHandle);

            if (IOM_COMPLETED == status)
            {
                Mcasp_localSetupHwInfo(
                    &instHandle->hwInfo,
                    &instHandle->mcaspHwSetup);

                status = Mcasp_localPrcmOff(instHandle);
            }
        }

        /* we need to check if any one of the instance has the Swi created    *
         * else we will create the swi here                                   */
        for (count = 0; count < CSL_MCASP_PER_CNT; count++)
        {
            if (NULL != Mcasp_module.isrObject[count].isrSwiTaskHandle)
            {
                break;
            }
        }

        if (count == CSL_MCASP_PER_CNT)
        {
            Swi_Params_init(&swiParams);

            /* modify the default parameters with the required params         */
            swiParams.priority = Mcasp_SWI_PRIORITY;

            /* create the swi that will be used for ISR handling              */
            Swi_construct(&(instHandle->isrSwiObject),
                          &Mcasp_localIsrSwiFxn, &swiParams,
                          NULL);

            /* copy the swi Handle information to all the module objects      */
            for (count = 0; count < CSL_MCASP_PER_CNT; count++)
            {
                Mcasp_module.isrObject[count].isrSwiTaskHandle = \
                    Swi_handle(&instHandle->isrSwiObject);
            }
        }

        if (IOM_COMPLETED == status)
        {
#ifndef Mcasp_LOOPJOB_ENABLED
            instHandle->loopJobMode = (Bool) FALSE;

            Swi_Params_init(&swiParams);

            /* create the swi to handle the TX FIFO empty case handling       */
            swiParams.priority = Mcasp_SWI_PRIORITY;
            swiParams.arg0     = (UArg) & instHandle->XmtObj;
            swiParams.arg1     = (UArg) instHandle;

            Swi_construct(&(instHandle->fifoSwiObject),
                          (Swi_FuncPtr) & Mcasp_swiTxFifo, &swiParams, NULL);

#endif
        }

        if (IOM_COMPLETED == status)
        {
            instHandle->devState = Mcasp_DriverState_CREATED;
            *devp = (Ptr) instHandle;
        }
        else
        {
            *devp = NULL;
        }
    }
    return ((Int) status);
}

/**
 *  \brief  Closes the McASP device from use.
 *
 *  This function is called when an previously opened channel is to be closed.
 *  it unallocates all the resources allocated during the instance creation
 *  and marks the instance as free for allocation
 *
 *  \param  devp  [IN]  Device handle (returned during device creation)
 *
 *  \return IOM_COMPLETED   if successful
 *          IOM error       if not successful
 *
 *  \enter  instHandle    is not NULL and is a valid pointer,
 *          status        is a valid value.
 *
 *  \leave  Not Implemented
 */
static Int mcaspMdUnBindDev(Ptr devp)
{
    Mcasp_Object *instHandle  = NULL;
    Int32         retVal      = IOM_COMPLETED;
    UInt32        key         = 0;
    UInt32        devId       = 0;
    Bool          destructSwi = (Bool) TRUE;

    /* Begin parameter checking
     *                                                  */
#ifndef PSP_DISABLE_INPUT_PARAMETER_CHECK
    if (NULL == devp)
    {
        retVal = IOM_EBADARGS;
    }
    else
    {
#endif  /* PSP_DISABLE_INPUT_PARAMETER_CHECK */
    instHandle = (Mcasp_Object *) devp;
#ifndef PSP_DISABLE_INPUT_PARAMETER_CHECK
    if (((UInt16) CSL_MCASP_PER_CNT <= instHandle->instNum) ||
        (Mcasp_DriverState_CLOSED != instHandle->XmtObj.chanState) ||
        (Mcasp_DriverState_CLOSED != instHandle->RcvObj.chanState))
    {
        retVal = IOM_EBADARGS;
    }
}

#endif  /* PSP_DISABLE_INPUT_PARAMETER_CHECK */
    /* End parameter checking
     *                                                    */

    if (IOM_COMPLETED == retVal)
    {
        /* Close and free mcasp port handle                                   */
        if (NULL != &(instHandle->hwInfo))
        {
            instHandle->hwInfo.regs  = 0x00;
            instHandle->hwInfo.perNo = (Int16) - 1;
            instHandle->hwInfo.numOfSerializers = 0;
            instHandle->hwInfo.ditStatus        = (Bool) FALSE;
        }

        /* critical section starts                                            */
        key = (UInt32) Hwi_disable();

        /* Mark driver state as deleted and module as not in use              */
        instHandle->devState = Mcasp_DriverState_DELETED;
        Mcasp_module.inUse[instHandle->instNum] = (Bool) FALSE;

        /* Check across all instances to see if any interrupts are still
         *registered */
        for (devId = (UInt32) 0; devId < CSL_MCASP_PER_CNT; devId++)
        {
            if (((Bool) TRUE ==
                 Mcasp_module.isrObject[devId].isIsrRegistered[0])
                && ((Bool) TRUE ==
                    Mcasp_module.isrObject[devId].isIsrRegistered[1]))
            {
                destructSwi = (Bool) FALSE;
                break;
            }
        }

        /* Destruct Swi only if all interrupts are properly unregistered */
        if ((Bool) TRUE == destructSwi)
        {
            Swi_destruct(&(instHandle->fifoSwiObject));
        }

        /* critical section ends                                              */
        Hwi_restore(key);

        if ((Bool) FALSE == instHandle->prcmPwrmEnable)
        {
            /* #ifdef BIOS_PWRM_ENABLE */
            /* power on using bios PWRM API
             */
            /*           retVal = (Int32)PWRM_releaseDependency(
             *                    (PWRM_Resource)instHandle->hwInfo.pwrmLpscId);
             #else */
            /* power on using PRCM API
             */
            /*
             *              Prcm_ModuleClkCtrl(
             *                (Int)instHandle->prcmDevId,
             *                  (UInt32)instHandle->hwInfo.pwrmPrcmId,
             *                  Prcm_moduleClkCtrl_DISABLE,
             *                  NULL);
             #endif */
        }

#if defined (BIOS_PWRM_ENABLE) && !defined (Mcasp_LOOPJOB_ENABLED)
        if ((IOM_COMPLETED == retVal) &&
            ((Bool) TRUE == instHandle->prcmPwrmEnable))
        {
            /* register the notify function for the PWRM events               */
            retVal = McaspUnregisterNotification(instHandle);
        }
#endif
    }
    return ((Int) retVal);
}

/* ========================================================================== */
/*                             IOM FUNCTIONS                                  */
/* ========================================================================== */

/**
 *  \brief  Creates a communication channel in specified mode to communicate
 *          data between the application and the McASP device instance. This
 *          function sets the required hardware configurations for the data
 *          transactions.it returns configured channel handle to application.
 *          which will be used in all further transactions with the channel.
 *
 *          This function is called in response to a Stream_create call.
 *
 *          Pre-requisites:
 *          1.  Valid chanParams structure
 *              This takes much information pertaining to mcasp channel
 *              configuration such as how many serialisers are used for this
 *              channel what are they communication parameters,clock setting etc
 *          2.  Valid device pointer
 *
 *  \param  instHandle   [IN]   Mcasp driver object
 *  \param  name         [IN]   Mcasp Instance name like MCASP0
 *  \param  mode         [IN]   channel  mode -> input or output
 *  \param  chanParams   [IN]   channel parameters from user
 *  \param  cbFxn        [IN]   callback function pointer
 *  \param  cbArg        [IN]   callback function Arguments
 *
 *  \return channel handle in case of success
 *          NULL   in case of failure
 *
 *  \enter  instHandle   is not NULL and is a valid pointer,
 *          chanp        is not NULL and is a valid pointer,
 *          cmd          is a valid IOCTL command,
 *          cmdArgs      are valid and appropriate for the command passed,
 *
 *  \leave  Not implemented
 */
static Int mcaspMdCreateChan(Ptr             *chanp,
                             Ptr              devp,
                             String           name,
                             Int              mode,
                             Ptr              chanParams,
                             IOM_TiomCallback cbFxn,
                             Ptr              cbArg)
{
    Mcasp_Object       *instHandle = NULL;
    Mcasp_ChannelHandle chanHandle = NULL;
    Mcasp_ChanParams   *chanparam  = NULL;
    UInt32 key      = 0;
    UInt16 count    = 0;
    UInt16 mask     = 0;
    UInt32 mod      = 0;
    Bool falsewhile = (Bool) TRUE;
    Bool pscPwrOn   = (Bool) FALSE;
    Int32 retVal    = IOM_COMPLETED;
    UInt32 tempFuncPtr;
#ifdef Mcasp_LOOPJOB_ENABLED
    UInt32 dlbMode = 0;
    EDMA3_DRV_TrigMode  trigMode = EDMA3_DRV_TRIG_MODE_EVENT;
#endif
    Int status = IOM_COMPLETED;

    /* Done to remove compiler warning of unused param                        */
    if (NULL != name)
    {
        name = name;
    }

    /* Begin parameter checking
     *                                                  */
#ifndef PSP_DISABLE_INPUT_PARAMETER_CHECK
    if (((NULL == chanParams)
         || (NULL == cbFxn)
         || (NULL == cbArg)
         || (NULL == devp))
        || ((IOM_INPUT != mode) && (IOM_OUTPUT != mode)))
    {
        status = IOM_EBADARGS;
    }
    else
    {
#endif  /* PSP_DISABLE_INPUT_PARAMETER_CHECK */
    chanparam = (Mcasp_ChanParams *) chanParams;
#ifndef PSP_DISABLE_INPUT_PARAMETER_CHECK
    if ((NULL == chanparam->edmaHandle) &&
        ((Bool) TRUE == chanparam->isDmaDriven))
    {
        status = IOM_EBADARGS;
    }
}

#endif  /* PSP_DISABLE_INPUT_PARAMETER_CHECK */
    /* End parameter checking
     *                                                    */

    if (IOM_COMPLETED == status)
    {
        instHandle = (Mcasp_Object *) devp;
        do
        {
            falsewhile = (Bool) FALSE;

            /* power on the module                                            */
            status = (Int) Mcasp_localPrcmOn(instHandle);

            if (IOM_COMPLETED == status)
            {
                pscPwrOn = (Bool) TRUE;

                /* initialise buffers required by the mcasp for mute and loop
                 * job */
                mcaspInit((UInt32) instHandle->instNum);

                /* check the current mode of operation and assign suitable
                 * handle */
                if (IOM_INPUT == mode)
                {
                    chanHandle = (Mcasp_ChannelHandle) & instHandle->RcvObj;
                }
                else
                {
                    chanHandle = (Mcasp_ChannelHandle) & instHandle->XmtObj;
                }

                /* enter critical section and update the status of driver
                 * */
                key = (UInt32) Hwi_disable();
            }
            /* check if the handle to the channel is valid                    */
            if (((NULL == chanHandle) ||
                 (Mcasp_DriverState_OPENED == chanHandle->chanState)) &&
                (IOM_COMPLETED == status))
            {
                status = IOM_EBADARGS;

                /* Leave critical section                                     */
                Hwi_restore(key);
            }
            if (IOM_COMPLETED == status)
            {
                /* update the driver status as being opened in case of failure
                 * status needs to be reverted back
                 *                              */
                chanHandle->chanState = Mcasp_DriverState_OPENED;

                /*
                 * Leave critical section
                 */
                Hwi_restore(key);

                /*
                 * update the channel operational mode  (i.e TX or RX)
                 */
                chanHandle->mode = (UInt32) mode;

                /*
                 * update the device handle in the channel object structure
                 */
                chanHandle->devHandle = (Ptr) instHandle;

                /* update the IOM callback function in channel structure
                 *         */
                chanHandle->cbFxn = cbFxn;
                chanHandle->cbArg = (UArg) cbArg;
            }
            /* check if requested serialisers are more than device supports.  *
             * This is a first level check, later we check what serialisers   *
             * are remaining and if they match the requested serialisers number
             **/
            if (((chanparam->noOfSerRequested) >
                 (instHandle->hwInfo.numOfSerializers)) &&
                (IOM_COMPLETED == status))
            {
                status = IOM_EBADARGS;
            }

            /* check if  mode (transmit or receive mode) is DIT or TDM        */
            if ((MCASP_OPMODE_TDM != chanparam->channelMode)
                && (MCASP_OPMODE_DIT != chanparam->channelMode)
                && (IOM_COMPLETED == status))
            {
                status = IOM_EBADARGS;
            }

            /* validate params for the DIT mode and set an error if incorrect */
            if ((MCASP_OPMODE_DIT == chanparam->channelMode)
                && ((IOM_OUTPUT != mode)
                    || (MCASP_WORDLENGTH_32 != chanparam->wordWidth))
                && (IOM_COMPLETED == status))
            {
                status = IOM_EBADARGS;
            }

            if ((MCASP_OPMODE_DIT == chanparam->channelMode)
                && ((Bool) FALSE == instHandle->isDataBufferPayloadStructure)
                && (IOM_COMPLETED == status))
            {
                status = IOM_EBADARGS;
            }

            /* if this instance is not supporting DIT mode then return error  */
            if ((MCASP_OPMODE_DIT == chanparam->channelMode)
                && ((Bool) FALSE == instHandle->hwInfo.ditStatus)
                && (IOM_COMPLETED == status))
            {
                status = IOM_EBADARGS;
            }

            /* check if the cache is to be supported and flush the cache      *
             * if the cache support is enabled                                */
            if (((Bool) TRUE == instHandle->enablecache) &&
                (IOM_COMPLETED == status))
            {
                Cache_wb(Mcasp_muteBuf[instHandle->instNum].scratchBuffer,
                         MCASP_CACHE_LENGTH,
                         Cache_Type_ALL, (Bool) TRUE);

#ifdef Mcasp_LOOPJOB_ENABLED
                Cache_wb(Mcasp_loopDstBuf[instHandle->instNum].scratchBuffer,
                         MCASP_CACHE_LENGTH,
                         Cache_Type_ALL, (Bool) TRUE);

                Cache_wb(Mcasp_loopSrcBuf[instHandle->instNum].scratchBuffer,
                         MCASP_CACHE_LENGTH,
                         Cache_Type_ALL, (Bool) TRUE);

#endif          /* Mcasp_LOOPJOB_ENABLED */
            }
            if (IOM_COMPLETED == status)
            {
                /* This is used in EDMA mode to populate paramsets in PING PONG
                 *  */
                chanHandle->nextLinkParamSetToBeUpdated = 0;

                chanHandle->dataPacket = NULL;
                chanHandle->currentPacketErrorStatus = IOM_COMPLETED;

                /* Initialize Mute parameter
                 *                                     */
                chanHandle->bMuteON = (Bool) FALSE;

                /* Initialize Pause parameter
                 *                                    */
                chanHandle->paused = (Bool) FALSE;
            }

            /* Check requested serializers are free or not                    */
            if (((Bool) FALSE ==
                 mcaspIsRequestedSerzsFree(instHandle,
                                           chanparam)) &&
                (IOM_COMPLETED == status))
            {
                /* since serializers cannot be allocated, return error        */
                chanHandle->channelOpMode = Mcasp_ChanMode_FREE;
                status = IOM_EBADARGS;
            }

            if (IOM_COMPLETED == status)
            {
                /* Since we have request serialisers as free, we allocate them
                 * to this channel as requested
                 */
                for (count = 0; count < chanparam->noOfSerRequested; count++)
                {
                    chanHandle->indexOfSersRequested[count] =
                        chanparam->indexOfSersRequested[count];
                }

                /* update the number of serializers allocated to channel
                 *         */
                chanHandle->noOfSerAllocated = chanparam->noOfSerRequested;

                /* Counter that counts outstanding requests of this channel
                 *      */
                chanHandle->submitCount = 0;

                /* Global error callback registered to channel
                 *                   */
                chanHandle->gblErrCbk = chanparam->gblCbk;

                /* We need to have infomation on what application intends to do.
                 * for e.g. if application is sending 12bit data and formats it
                 * in such a way the it in stream it occupies 2 bytes,this
                 * members value should be 16 (MCASP_WORDLENGTH_16).
                 * By defaut we assume that app has formated the
                 * data byte stream for 4 bytes for each serialser
                 * for each sync event/int from mcasp. Please note
                 * that for burst mode we have 1 sync event/int from mcasp for
                 * both L and R (in general all slots) where as we have each
                 * sync event /Int from mcasp for L and R (in general all slots)
                 * seperately
                 *                                                    */
                chanHandle->roundedWordWidth = (UInt16) MCASP_WORDLENGTH_32;
            }
            /* we have 3 options for chanHandle->roundedWordWidth variable    *
             * 32,16 & 8 so we start from 32 (bit 5) and check if bit5 , 4,   *
             * or 3 is set if  param->wordWidth is invalid - we assume the    *
             * default of 32bit width.The following logic translates the      *
             * intermediate bit widths to what this driver wants. It assumes  *
             * that always the data streams is aligned to 8 ,16, 32 bits      *
             * ( rounded to ceil)
             *                                              */

            if ((MCASP_WORDLENGTH_32 > chanparam->wordWidth) &&
                (IOM_COMPLETED == status))
            {
                mask = 0x20U;

                for (count = 0; count < (3U); count++)
                {
                    if (mask == (mask & chanparam->wordWidth))
                    {
                        chanHandle->roundedWordWidth = (UInt16) mask;

                        if (chanparam->wordWidth > chanHandle->roundedWordWidth)
                        {
                            chanHandle->roundedWordWidth =
                                (UInt16) (chanHandle->roundedWordWidth << 1);
                        }
                        break;
                    }
                    mask = (UInt16) (mask >> 1);
                }
            }

            /* we will overide the above setting if application has enabled   *
             * the packed mode support                                        */
            if (((Bool) TRUE == chanparam->isDataPacked) &&
                (IOM_COMPLETED == status))
            {
                switch (chanparam->wordWidth)
                {
                    case MCASP_WORDLENGTH_32:
                    case MCASP_WORDLENGTH_24:
                    case MCASP_WORDLENGTH_16:
                    case MCASP_WORDLENGTH_8:
                        chanHandle->roundedWordWidth = chanparam->wordWidth;
                        break;

                    default:
                        status = IOM_EBADARGS;
                        break;
                }
            }

            if (((UInt32) 0U ==
                 ((UInt32) (0x0000FF80U) &
                  chanparam->mcaspSetup->frSyncCtl)) &&
                (IOM_COMPLETED == status))
            {
                /*the driver has been configured for DSP (BURST mode)         */
                if (0 == chanparam->noOfChannels)
                {
                    status = IOM_EBADARGS;
                }
                if (IOM_COMPLETED == status)
                {
                    chanHandle->roundedWordWidth = (UInt16) \
                                                   (chanparam->noOfChannels *
                                                    chanHandle->
                                                    roundedWordWidth);
                }
                /* rounded wordwidth can not go beyond 32 bits. In burst mode *
                 * multiplication of no of channels and wordwidth can be max. *
                 * 32 bits. Beyond that it is not supported                   */
                if ((MCASP_WORDLENGTH_32 < chanHandle->roundedWordWidth) &&
                    (IOM_COMPLETED == status))
                {
                    status = IOM_EBADARGS;
                }
            }

            if ((IOM_COMPLETED
                 != mcaspValidateBufferConfig(chanHandle,
                                              chanparam)) &&
                (IOM_COMPLETED == status))
            {
                status = IOM_EBADARGS;
            }
            if (IOM_COMPLETED == status)
            {
                /* Converting word width from bits to bytes
                 *                      */
                chanHandle->roundedWordWidth = \
                    (UInt16) (chanHandle->roundedWordWidth >> 3);
            }
            /* Approaches part ways.For interrupt and DMA modes               */
            if (((Bool) TRUE == chanparam->isDmaDriven) &&
                (IOM_COMPLETED == status))
            {
                /* Store this info in the channel handle too                  */
                chanHandle->isDmaDriven = (Bool) TRUE;

                /* store the EDMA3 module handle                              */
                chanHandle->edmaHandle = chanparam->edmaHandle;

                if (IOM_INPUT == chanHandle->mode)
                {
                    /* Receive mode */

                    /* Assign the Channel ID and TCC                          */
                    chanHandle->xferChan =
                        instHandle->hwInfo.edmaRxEventNum;
                    chanHandle->tcc =
                        instHandle->hwInfo.edmaRxEventNum;
                    chanHandle->edmaCallback = \
                        &Mcasp_localEdmaCallback;
                    chanHandle->cpuEventNum = instHandle->hwInfo.cpuRxEventNum;
                }
                else
                {
                    /* Transmit mode */

                    /* Assign the Channel ID and TCC                          */
                    chanHandle->xferChan =
                        instHandle->hwInfo.edmaTxEventNum;
                    chanHandle->tcc =
                        instHandle->hwInfo.edmaTxEventNum;
                    chanHandle->edmaCallback = \
                        &Mcasp_localEdmaCallback;
                    chanHandle->cpuEventNum = instHandle->hwInfo.cpuTxEventNum;
                }
#ifdef Mcasp_LOOPJOB_ENABLED
                /* Configure loop job for the user specified buffer if given  */
                if (NULL == chanparam->userLoopJobBuffer)
                {
                    if (IOM_INPUT == chanHandle->mode)
                    {
                        chanHandle->loopJobBuffer = \
                            Mcasp_loopDstBuf[(instHandle->instNum)].
                            scratchBuffer;
                    }
                    else
                    {
                        chanHandle->loopJobBuffer = \
                            Mcasp_loopSrcBuf[(instHandle->instNum)].
                            scratchBuffer;
                    }

                    /* Length of UInt32 per serialiser-this is what we have   *
                     * allocated                                              */
                    if (MCASP_OPMODE_DIT == chanparam->channelMode)
                    {
                        /* we need 2 * 24 bit data per subframe. Hence we will*
                         * program the loop job length as 6 bytes             */
                        chanHandle->loopJobLength = 6U;
                    }
                    else
                    {
                        chanHandle->loopJobLength =
                            (chanHandle->roundedWordWidth
                             * chanHandle->noOfSlots
                             * chanHandle->noOfSerAllocated);
                    }
                    /* user loopJob is not being used                         */
                    chanHandle->userLoopJob = (Bool) FALSE;
                }
                else
                {
                    /* Apps has preference on the loopjob buffer & lets use it*/
                    chanHandle->loopJobBuffer =
                        chanparam->userLoopJobBuffer;
                    chanHandle->userLoopJobLength =
                        chanparam->userLoopJobLength;

                    /* user loopJob is being used                             */
                    chanHandle->userLoopJob = (Bool) TRUE;
                    if (chanHandle->roundedWordWidth >
                        chanparam->userLoopJobLength)
                    {
                        /* not enough loopjob buffer has been provided  we    *
                         * should have aleast loopbuffer for 1 sync event     */
                        status = IOM_EBADARGS;
                    }
                }
#endif          /* Mcasp_LOOPJOB_ENABLED */
                /* configure EDMA for this driver                             */
                if ((IOM_COMPLETED !=
                     Mcasp_localSetupEdmaDuringOpen(chanHandle)) &&
                    (IOM_COMPLETED == status))
                {
                    status = IOM_EBADARGS;
                }
            }
            /* if DMA driven*/
            else if (IOM_COMPLETED == status)
            {
                /* Interrupt driven operation */
                /* Store this info too in the channel handle.                 */
                chanHandle->isDmaDriven = (Bool) FALSE;
                if (IOM_INPUT == chanHandle->mode)
                {
                    chanHandle->cpuEventNum = instHandle->hwInfo.cpuRxEventNum;
                }
                else
                {
                    chanHandle->cpuEventNum = instHandle->hwInfo.cpuTxEventNum;
                }

                /* On being released from reset, the McASP xmt section will   *
                 * trigger two interrupts to fill it's buffers (this has been *
                 * handled in submitreq function.Keep count of packets to     *
                 * service this.                                              */
                chanHandle->dataQueuedOnReset     = 0;
                chanHandle->xferinProgressIntmode = (Bool) FALSE;
            }
            else
            {
                /* Misra Compliance */
                status = status;
            }
            if (IOM_COMPLETED == status)  /* configure the FIFO control
                                           * registers
                                           *(only if requested)       */
            {
                chanHandle->enableHwFifo = chanparam->enableHwFifo;
                mcaspConfigureFifo(&(instHandle->hwInfo),
                                   (Mcasp_ChannelHandle) chanHandle,
                                   chanHandle->enableHwFifo);

                if (IOM_INPUT == mode)
                {
                    /* receive channel */
                    /* Reconfigure the RCV section
                     *                               */
                    if (IOM_COMPLETED !=
                        mcaspConfigureRcvChannel(instHandle, chanparam))
                    {
                        status = IOM_EBADARGS;
                    }
                    if (IOM_COMPLETED == status)
                    {
                        /* Mark REQUESTED serializers as RECEIVE mode.This also
                         * configures PDIR pins as INPUT pin
                         *                         */
                        mcaspMultiSerInitializationRcv(instHandle, chanparam);

                        /* Set channel operational mode
                         *                              */
                        chanHandle->channelOpMode = Mcasp_ChanMode_RCV;
                    }
                }
                else
                {
                    /* transmit channel */
                    /* Re-configure the XMT section
                     *                              */
                    if (IOM_COMPLETED !=
                        mcaspConfigureXmtChannel(instHandle, chanparam))
                    {
                        status = IOM_EBADARGS;
                    }
                    if (IOM_COMPLETED == status)
                    {
                        /* Mark REQUESTED serializers as RECEIVE mode. Also
                         * configures PDIR pins as INPUT pin
                         * */
                        mcaspMultiSerInitializationXmt(instHandle, chanparam);

                        /* Set channel mode
                         *                                          */
                        if (MCASP_OPMODE_DIT == chanparam->channelMode)
                        {
                            /* Channel is to operate in DIT mode
                             *                     */
                            chanHandle->channelOpMode = Mcasp_ChanMode_XMT_DIT;
                        }
                        else
                        {
                            /* Channel is to operate in normal TDM mode
                             *              */
                            chanHandle->channelOpMode = Mcasp_ChanMode_XMT_TDM;
                        }
                    }
                }

                /* For burtsmode of operation frame sync error has to be ignored
                 * hence, we do the following
                 *                                    */
                if (IOM_INPUT == chanHandle->mode)
                {
                    /* Clear the framsync error flag from EVTCTLR
                     *                */
                    mod = McASPTxRxFrameSyncRead
                              (instHandle->hwInfo.regs, (UInt8) RX);
                    mod &= (UInt32) MCASP_RXFMCTL_RMOD_MASK;
                    if (0U == mod)
                    {
                        McASPRxIntDisable(instHandle->hwInfo.regs,
                                          (UInt32) MCASP_RX_SYNCERROR);
                    }
                }
                else
                {
                    /* Clear the framsync error flag from EVTCTLX
                     *                */
                    mod = McASPTxRxFrameSyncRead
                              (instHandle->hwInfo.regs, (UInt8) TX);
                    mod &= MCASP_TXFMCTL_XMOD_MASK;
                    if (0U == mod)
                    {
                        McASPTxIntDisable(instHandle->hwInfo.regs,
                                          (UInt32) MCASP_TX_SYNCERROR);
                    }
                }
                tempFuncPtr = (UInt32) & mcaspIsr;
                /* Register the interrupts for events for both  DMA/Interrupt
                 * modes  because in DMA mode also we will get interrupts for
                 * errors
                 *                                                        */
                mcaspRegisterInt(
                    chanHandle,
                    (UInt32) instHandle->instNum,
                    (UInt16) chanHandle->cpuEventNum,
                    (Ptr) tempFuncPtr);

#ifdef Mcasp_LOOPJOB_ENABLED
                /*Starting DMA after starting clocks and before Serialiser SM FS
                 * */
                if ((Bool) TRUE == chanHandle->isDmaDriven)
                {
                    /* When we get first packet let us start from linkparam set
                     *0 */
                    chanHandle->nextLinkParamSetToBeUpdated = 0;
                    /* enable the DMA */
                    EDMA3_DRV_enableTransfer(
                        chanHandle->edmaHandle,
                        chanHandle->xferChan,
                        trigMode);

                    /* if DLB mode is set then Enable both state m/c else rcv
                     * or xmt  state machine only needs to be enabled
                     */
                    dlbMode = McASPDlbRegRead(instHandle->hwInfo.regs);

                    if (MCASP_LBCTL_DLBEN_DISABLE == dlbMode)
                    {
                        if (IOM_INPUT == mode)
                        {
                            /* Receive channel */
                            /* activate RX and TX state machine and frame sync
                             */
                            Mcasp_enableInterrupt(chanHandle->cpuEventNum);
                            Mcasp_localActivateSmFsForRcv(instHandle);
                        }
                        else
                        {
                            /* Transmit channel */
                            /* activate RX and TX state machine and frame sync
                             */
                            Mcasp_enableInterrupt(chanHandle->cpuEventNum);
                            Mcasp_localActivateSmFsForXmt(instHandle);
                        }
                    }
                    else
                    {
                        /***        DLB Mode      ****/
                        /* activate RX and TX state machine and frame sync
                         */
                        Mcasp_enableInterrupt(
                            instHandle->hwInfo.cpuRxEventNum);
                        Mcasp_enableInterrupt(
                            instHandle->hwInfo.cpuTxEventNum);

                        Mcasp_localActivateSmFsForBoth(instHandle);
                    }
                }
                /* dma driven */

                /* For interrupt mode actual start of mcasp starts in Submit
                 * function and only when enough data packets are available.
                 * Also note that we have not implemented loopjobbuffer for
                 * this mode
                 * */
                /*  update the State m/c stop status
                 */
                instHandle->stopSmFsXmt = (Bool) FALSE;
                instHandle->stopSmFsRcv = (Bool) FALSE;
#endif          /* Mcasp_LOOPJOB_ENABLED */
            }
        }
        while (falsewhile);

        if ((Bool) TRUE == pscPwrOn)
        {
            /* power off the module                                           */
            retVal = Mcasp_localPrcmOff(instHandle);

            if (IOM_COMPLETED == status)
            {
                status = retVal;
            }
        }
    }

    if (IOM_COMPLETED != status)
    {
        /* enter critical section                                             */
        key = (UInt32) Hwi_disable();

        /* in case of an error we may not have the reference to channel handle*
         * hence we will explicitly assign it here                            */
        if (NULL != chanHandle)
        {
            /* call the delete function to free all the assigned resources    */
            mcaspMdDeleteChan(chanHandle);
        }

        /* Leave critical section                                             */
        Hwi_restore(key);

        /* channel opening for transaction has failed                         */
        chanHandle = NULL;
    }
    else
    {
        *chanp = chanHandle;
    }
    return (Int) status;
}

/**
 *  \brief   Submit a I/O packet to a channel for processing
 *
 *  The stream layer calls this function to cause the IDriver
 *  to process the IOM_Packet for read/write operations.
 *  This function calls mcaspSubmitReq  function to execute the request.
 *
 *  \param   instHandle [IN]  pointer to mcasp instance object
 *  \param   chanp      [IN]  Handle to the channel
 *  \param   ioPacket   [IN]  Pointer to the packet to be submitted
 *  \Param   eb         [OUT] error block
 *
 *  \return  IOM_COMPLETED, if packet is fully processed
 *           IOM_PENDING,   if packet is not fully processed
 *           IOM_ERROR      if error in processing
 *
 *  \enter  instHandle    is not NULL and is a valid pointer,
 *          chanp         is not NULL and is a valid pointer,
 *          ioPacket      is not NULL and is a valid pointer,
 *
 *  \leave  Not implemented
 */
static Int mcaspMdSubmitChan(Ptr chanp, IOM_Packet *ioPacket)
{
    Mcasp_ChannelHandle chanHandle = NULL;
    Mcasp_Object       *instHandle = NULL;
    Int32 status = IOM_COMPLETED;

    /* Begin parameter checking
     *                                                  */
#ifndef PSP_DISABLE_INPUT_PARAMETER_CHECK
    if ((NULL == chanp) || (NULL == ioPacket))
    {
        status = IOM_EBADARGS;
    }
    else
    {
#endif  /* PSP_DISABLE_INPUT_PARAMETER_CHECK */

    chanHandle = (Mcasp_ChannelHandle) chanp;

#ifndef PSP_DISABLE_INPUT_PARAMETER_CHECK
    if ((NULL == chanHandle) ||
        (Mcasp_DriverState_OPENED != chanHandle->chanState) ||
        (((IOM_READ == ioPacket->cmd) || (IOM_WRITE == ioPacket->cmd)) &&
         ((0 == ioPacket->size) || (NULL == ioPacket->addr))))
    {
        status = IOM_EBADARGS;
    }
}

#endif  /* PSP_DISABLE_INPUT_PARAMETER_CHECK */
    /* End parameter checking
     */

    /* validate all the input parameters and set error if not OK              */
    if (IOM_COMPLETED == status)
    {
        /* if the command is for the ABORT or FLUSH                           */
        if ((IOM_ABORT == ioPacket->cmd) || (IOM_FLUSH == ioPacket->cmd))
        {
            status = Mcasp_localAbortRequests(chanHandle, NULL);
        }
        else if ((IOM_WRITE == ioPacket->cmd) || (IOM_READ == ioPacket->cmd))
        {
            instHandle = (Mcasp_Object *) chanHandle->devHandle;
            assert(NULL != instHandle);

            /* switch on the device in the PSC                                */
            status = Mcasp_localPrcmOn(instHandle);

            if (IOM_COMPLETED == status)
            {
                /* submit the IO request to the driver                        */
                status = mcaspSubmitReq((Mcasp_ChannelHandle) chanHandle,
                                        ioPacket);

                if (IOM_PENDING != status)
                {
                    status = Mcasp_localPrcmOff(instHandle);
                }
            }
        }
        else
        {
            /* error: command not found                                       */
            status = IOM_EBADARGS;
        }
    }
    return (Int) status;
}

/**
 *  \brief   This function is called by the application to close a previously
 *           opened channel.it deletes the channel so that it is not available
 *           for further transactions. All the allocated resources are freed
 *           and the channel will be ready for the "open" operation once again.
 *
 *  \param   chanp      [IN]   Handle to the channel.
 *
 *  \return  None
 *
 *  \enter   instHandle    is not NULL and is a valid pointer,
 *           chanp         is not NULL and is a valid pointer,
 *
 *  \leave   Not implemented
 */
static Int mcaspMdDeleteChan(Ptr chanp)
{
    Mcasp_Object       *instHandle = NULL;
    Mcasp_ChannelHandle chanHandle = NULL;
    Int32  status   = IOM_COMPLETED;
    UInt8  linkCnt  = 0;
    UInt32 hwiKey   = 0;
    Bool   pscPwrOn = (Bool) FALSE;
    Int32  retVal   = IOM_COMPLETED;

    /* Begin parameter checking
     */
#ifndef PSP_DISABLE_INPUT_PARAMETER_CHECK
    if (NULL == chanp)
    {
        status = IOM_EBADARGS;
    }
    else
    {
#endif  /* PSP_DISABLE_INPUT_PARAMETER_CHECK */
    chanHandle = (Mcasp_ChannelHandle) chanp;
#ifndef PSP_DISABLE_INPUT_PARAMETER_CHECK
    if (NULL == chanHandle->devHandle)
    {
        status = IOM_EBADARGS;
    }
}

#endif  /* PSP_DISABLE_INPUT_PARAMETER_CHECK */
    /* End parameter checking
     */

    /* check if the input parameters are valid                                */
    if (IOM_COMPLETED == status)
    {
        instHandle = (Mcasp_Object *) chanHandle->devHandle;
        assert(NULL != instHandle);

#if defined (BIOS_PWRM_ENABLE) && !defined (Mcasp_LOOPJOB_ENABLED)
        if ((Bool) TRUE == instHandle->prcmPwrmEnable)
        {
            status = McaspUnregisterConstraints(instHandle);
        }
#endif

        /* before touching McASP registers, place transmit and receive section
         * in reset    */
        if (IOM_OUTPUT == chanHandle->mode)
        {
            McASPTxReset(instHandle->hwInfo.regs);
        }
        else
        {
            McASPRxReset(instHandle->hwInfo.regs);
        }

        /* DMA driven transaction channel                                     */
        if ((Bool) TRUE == chanHandle->isDmaDriven)
        {
            /* Unregister the interrupts registered                           */
            mcaspUnRegisterInt(
                instHandle->instNum,
                (UInt16) chanHandle->cpuEventNum,
                (Int) chanHandle->mode);

            status = Mcasp_localPrcmOn(instHandle);

            if (IOM_COMPLETED == status)
            {
                pscPwrOn = (Bool) TRUE;
            }

            if (IOM_COMPLETED == status)
            {
                /* Stop the xmt/rcv state machine.                            */
                if (Mcasp_ChanMode_RCV == chanHandle->channelOpMode)
                {
                    /* Reset state m/c and frame sync of receive section      */
                    Mcasp_localDeactivateSmFsForRcv(instHandle);
                }
                else
                {
                    /* Reset state m/c and frame sync of transmit section     */
                    Mcasp_localDeactivateSmFsForXmt(instHandle);
                }
            }

            /* Disable the current transfer to make sure that there is        *
             * no running EDMA transfer taking place                          */
            if (IOM_COMPLETED == status)
            {
                status = EDMA3_DRV_disableTransfer(
                    chanHandle->edmaHandle,
                    chanHandle->xferChan,
                    EDMA3_DRV_TRIG_MODE_EVENT);
            }

            if (IOM_COMPLETED != status)
            {
                status = IOM_EBADMODE;
                /* we will continue inspite of the error here                 */
            }

            status = EDMA3_DRV_freeChannel(
                chanHandle->edmaHandle,
                chanHandle->xferChan);

            /* Free the allocated Edma channels                               */
            if (IOM_COMPLETED != status)
            {
                status = IOM_EBADMODE;
                /* we will continue inspite of the error here                 */
            }

            /* free the EDMA PaRAM entries used for Pingpong buffering        */
            for (linkCnt = (UInt8) 0U; linkCnt < (UInt8) Mcasp_MAXLINKCNT;
                 linkCnt++)
            {
                EDMA3_DRV_freeChannel(
                    chanHandle->edmaHandle,
                    chanHandle->pramTbl[linkCnt]);
            }
        }
        /* DMA Driven flag is TRUE if loop */

        /* restore global serializer state.                                   */
        mcaspMultiSerGlobalRestore(chanHandle);

        /* Set the Muted state to FALSE                                       */
        chanHandle->bMuteON = (Bool) FALSE;

        /* Set the Pause state to FALSE                                       */
        chanHandle->paused = (Bool) FALSE;

        /* start of critical section                                          */
        hwiKey = (UInt32) Hwi_disable();

        /* Mark channel as ready to be allocated again.                       */
        chanHandle->chanState = Mcasp_DriverState_CLOSED;

        /* Leave critical section                                             */
        Hwi_restore(hwiKey);

        chanHandle->noOfSerAllocated = 0;
        chanHandle->channelOpMode    = Mcasp_ChanMode_FREE;

        if ((Bool) TRUE == pscPwrOn)
        {
            retVal = Mcasp_localPrcmOff(instHandle);

            if (IOM_COMPLETED == status)
            {
                status = retVal;
            }
        }
    }
    return ((Int) status);
}

/**
 *  \brief    This function allows the control commands to be sent to the Mcasp
 *            driver. it internally calls the mcaspSubmitIoctl Function to
 *            perform the desired operation.
 *
 *  \param    instHandle [IN]    pointer to the Mcasp instance object
 *  \param    chanp      [IN]    Channel handle
 *  \param    cmd        [IN]    control command given by the application
 *  \param    cmdArgs    [IN]    Optional arguments required for the command
 *  \param    eb         [OUT]   error block
 *
 *  \return   None
 *
 *  \enter   instHandle   is not NULL and is a valid pointer,
 *           chanp        is not NULL and is a valid pointer,
 *           cmd          is a valid IOCTL command,
 *           cmdArgs      are valid and appropriate for the command passed,
 *
 *  \leave   Not implemented
 *
 */
static Int mcaspMdControlChan(Ptr chanp, Uns cmd, Ptr cmdArgs)
{
    Mcasp_ChannelHandle chanHandle = NULL;
    Mcasp_Object       *instHandle = NULL;
    Int32 status = IOM_COMPLETED;
    Int32 retVal = IOM_COMPLETED;

    /* Begin parameter checking
     *                                                  */
#ifndef PSP_DISABLE_INPUT_PARAMETER_CHECK
    if (NULL != chanp)
    {
#endif  /* PSP_DISABLE_INPUT_PARAMETER_CHECK */
    chanHandle = (Mcasp_ChannelHandle) chanp;
#ifndef PSP_DISABLE_INPUT_PARAMETER_CHECK
    if (Mcasp_DriverState_OPENED != chanHandle->chanState)
    {
        status = IOM_EBADARGS;
    }
    else if (NULL == chanHandle->devHandle)
    {
        status = IOM_EBADARGS;
    }
    else
    {
        /* Nothing to be done here */
    }
}

else
{
    status = IOM_EBADARGS;
}
#endif  /* PSP_DISABLE_INPUT_PARAMETER_CHECK */
    /* End parameter checking
     */

    /* check if the channel handle passed is valid                            */
    if (IOM_COMPLETED == status)
    {
        instHandle = (Mcasp_Object *) chanHandle->devHandle;

        status = Mcasp_localPrcmOn(instHandle);

        if (IOM_COMPLETED == status)
        {
            /* channel status is OK Hence the IOCTL can be executed           */
            status = Mcasp_localSubmitIoctl(chanHandle, cmd, (Ptr) cmdArgs,
                                            NULL);

            retVal = Mcasp_localPrcmOff(instHandle);

            if (IOM_COMPLETED == status)
            {
                status = retVal;
            }
        }
    }

    return ((Int) status);
}

/* ========================================================================== */
/*                              LOCAL FUNCTIONS                               */
/* ========================================================================== */

/**
 *  \brief  This function configures the  McASP instance registers as per the
 *          values passed in the hardware setup structure.
 *
 *  \param   hMcasp     [IN]    Handle to the McASP instance
 *  \param   myHwSetup  [IN]    Pointer to hardware setup structure
 *                             the query passed
 *
 *  \return  None
 *
 *  \enter   hMcasp      is a valid non null pointer
 *          myHwSetup   is a valid non null pointer
 *
 *  \leave   Not implemented
 *
 */
Void Mcasp_localSetupHwInfo(Mcasp_HwHandle       hMcasp,
                            const Mcasp_HwSetup *myHwSetup)
{
    UInt16 serNum = 0;

    assert(NULL != hMcasp);
    assert(NULL != myHwSetup);
    assert(NULL != hMcasp->regs);
    /* Reset McASP to default values by setting GBLCTL = 0                    */
    McASPGlobalCtlReset(hMcasp->regs);

    /* Changing the reset Power ON State of McASP to NO IDLE Configuration.
     * WakeUp Schema for McASP does not work,since we dont have any Power
     ****************Framework
     * default Power Status of McASP is changed to NOIDLE  indorder to prevent
     ****************any issues
     * which affect McASP wakeup in HW_AUTO Mode and cause
     * McASP Application Crash. Hence As per TRM recommended
     * Value, it is set to NOIDLE Mode.
     * But there will be huge impact on Power as McASP will always be ON.
     */
    McASPSetPowerIdleConfig(hMcasp->regs, MCASP_IDLEMODE_NOIDLE);

    /* Configure the RMASK register                                           */
    McASPRxFmtMaskSet(hMcasp->regs, (UInt32) myHwSetup->rx.mask);

    /* Configure RFMT                                                         */
    McASPRxFmtSet(hMcasp->regs, (UInt32) myHwSetup->rx.fmt);

    /* Configure AFSRCTL                                                      */
    McASPRxFrameSyncCfg(
        hMcasp->regs,
        (myHwSetup->rx.frSyncCtl &
         (UInt32) MCASP_RXFMCTL_RMOD_MASK) >> MCASP_RXFMCTL_RMOD_SHIFT,
        (myHwSetup->rx.frSyncCtl &
         (UInt32) MCASP_RXFMCTL_FRWID_MASK) >> MCASP_RXFMCTL_FRWID_SHIFT,
        (myHwSetup->rx.frSyncCtl &
         ((UInt32) MCASP_RXFMCTL_FSRP_MASK |
          (UInt32) MCASP_RXFMCTL_FSRM_MASK)) >> MCASP_RXFMCTL_FSRP_SHIFT);

    /* Configure ACLKRCTL                                                     */
    /* Configure AHCLKRCTL                                                    */
    McASPRxClkPolaritySet(hMcasp->regs,
                          (myHwSetup->rx.clk.clkSetupClk &
                           (UInt32) MCASP_ACLKRCTL_CLKRP_MASK));

    McASPRxHFClkPolaritySet(hMcasp->regs,
                            ((myHwSetup->rx.clk.clkSetupHiClk &
                              (UInt32) MCASP_AHCLKRCTL_HCLKRP_MASK) <<
                             MCASP_AHCLKRCTL_HCLKRP_SHIFT));

    McASPRxClkCfg(hMcasp->regs,
                  ((myHwSetup->rx.clk.clkSetupClk &
                    (UInt32) MCASP_ACLKRCTL_CLKRM_MASK) |
                   (myHwSetup->rx.clk.clkSetupHiClk &
                    (UInt32) MCASP_AHCLKRCTL_HCLKRM_MASK)),
                  ((myHwSetup->rx.clk.clkSetupClk &
                    (UInt32) MCASP_ACLKRCTL_CLKRDIV_MASK) >>
                   MCASP_ACLKRCTL_CLKRDIV_SHIFT),
                  ((myHwSetup->rx.clk.clkSetupHiClk &
                    (UInt32) MCASP_AHCLKRCTL_HCLKRDIV_MASK) >>
                   MCASP_AHCLKRCTL_HCLKRDIV_SHIFT));

    /* Configure RTDM                                                         */
    McASPRxTimeSlotSet(hMcasp->regs, myHwSetup->rx.tdm);

    /* Configure RINTCTL                                                      */
    McASPRxIntEnable(hMcasp->regs, myHwSetup->rx.intCtl);

    /* Configure RCLKCHK                                                      */
    McASPRxClkCheckRegWrite(hMcasp->regs, myHwSetup->rx.clk.clkChk);

    /* Configure XMASK                                                        */
    McASPTxFmtMaskSet(hMcasp->regs, myHwSetup->tx.mask);

    /* Configure XFMT                                                         */
    McASPTxFmtSet(hMcasp->regs, myHwSetup->tx.fmt);

    /* Configure AFSXCTL                                                      */
    McASPTxFrameSyncCfg(
        hMcasp->regs,
        (myHwSetup->tx.frSyncCtl &
         (UInt32) MCASP_TXFMCTL_XMOD_MASK) >> MCASP_TXFMCTL_XMOD_SHIFT,
        (myHwSetup->tx.frSyncCtl &
         (UInt32) MCASP_TXFMCTL_FXWID_MASK) >> MCASP_TXFMCTL_FXWID_SHIFT,
        (myHwSetup->tx.frSyncCtl &
         ((UInt32) MCASP_TXFMCTL_FSXP_MASK |
          (UInt32) MCASP_TXFMCTL_FSXM_MASK)) >> MCASP_TXFMCTL_FSXP_SHIFT);

    /* Configure ACLKXCTL                                                     */
    McASPTxClkPolaritySet(hMcasp->regs,
                          (myHwSetup->tx.clk.clkSetupClk &
                           (UInt32) MCASP_ACLKXCTL_CLKXP_MASK));

    McASPTxHFClkPolaritySet(hMcasp->regs,
                            ((myHwSetup->tx.clk.clkSetupHiClk &
                              (UInt32) MCASP_AHCLKXCTL_HCLKXP_MASK) <<
                             MCASP_AHCLKXCTL_HCLKXP_SHIFT));

    if ((myHwSetup->tx.clk.clkSetupClk &
         (UInt32) MCASP_ACLKXCTL_ASYNC_MASK) ==
        (UInt32) MCASP_ACLKXCTL_ASYNC_MASK)
    {
        McASPTxRxClkSyncDisable(hMcasp->regs);
    }
    else
    {
        McASPTxRxClkSyncEnable(hMcasp->regs);
    }

    McASPTxClkCfg(hMcasp->regs,
                  ((myHwSetup->tx.clk.clkSetupClk &
                    (UInt32) MCASP_ACLKXCTL_CLKXM_MASK) |
                   (myHwSetup->tx.clk.clkSetupHiClk &
                    (UInt32) MCASP_AHCLKXCTL_HCLKXM_MASK)),
                  ((myHwSetup->tx.clk.clkSetupClk &
                    (UInt32) MCASP_ACLKXCTL_CLKXDIV_MASK) >>
                   MCASP_ACLKXCTL_CLKXDIV_SHIFT),
                  ((myHwSetup->tx.clk.clkSetupHiClk &
                    (UInt32) MCASP_AHCLKXCTL_HCLKXDIV_MASK) >>
                   MCASP_AHCLKXCTL_HCLKXDIV_SHIFT));

    /* Configure XTDM                                                         */
    McASPTxTimeSlotSet(hMcasp->regs, myHwSetup->tx.tdm);

    /* Configure XINTCTL                                                      */
    McASPTxIntEnable(hMcasp->regs, myHwSetup->tx.intCtl);

    /* Configure XCLKCHK                                                      */
    McASPTxClkCheckRegWrite(hMcasp->regs, myHwSetup->tx.clk.clkChk);

    assert(hMcasp->numOfSerializers <= MCASP_NUMSERIALIZERS);

    while (serNum < hMcasp->numOfSerializers)
    {
        McASPSerializerSet(hMcasp->regs, (UInt32) serNum,
                           myHwSetup->glb.serSetup[serNum]);
        serNum++;
    }

    /* Configure pin function register                                        */
    McASPPinGPIOSet(hMcasp->regs, myHwSetup->glb.pfunc);

    /* Configure pin direction register                                       */
    McASPPinDirOutputSet(hMcasp->regs, myHwSetup->glb.pdir);

    /* Configure DITCTL                                                       */
    if ((Bool) TRUE == hMcasp->ditStatus)
    {
        McASPDITModeCtlWrite(hMcasp->regs, myHwSetup->glb.ditCtl);
    }

    /* Configure DLBCTL                                                       */
    McASPDlbRegWrite(hMcasp->regs, myHwSetup->glb.dlbMode);

    /* Configure AMUTE                                                        */
    /* hal_mcasp_aMuteEnable(hMcasp->regs, 0x00,
     *                    myHwSetup->glb.amute); */

    /* Configure RSTAT and XSTAT                                              */
    McASPRxStatusSet(hMcasp->regs, myHwSetup->rx.stat);
    McASPTxStatusSet(hMcasp->regs, myHwSetup->tx.stat);

    /* Configure REVTCTL and XEVTCTL                                          */
    McASPTxRxDMAEvtCntrlWrite(hMcasp->regs, (UInt8) RX, myHwSetup->rx.evtCtl);
    McASPTxRxDMAEvtCntrlWrite(hMcasp->regs, (UInt8) TX, myHwSetup->rx.evtCtl);

    /* Initialize the global control register                                 */
    McASPGlobalCtlSet(hMcasp->regs, myHwSetup->glb.ctl);
}

/**
 *  \brief   Aborts all the request queued up with the current channel
 *
 *  \param   chanHandle   [IN]   Handle to the mcasp channel
 *
 *  \return  None
 *
 *  \enter   chanHandle  is a valid non null pointer
 *
 *  \leave   Not implemented
 *
 */
Int32 Mcasp_localAbortReset(Mcasp_ChannelHandle chanHandle)
{
    Mcasp_Object *instHandle = NULL;
    IOM_Packet   *ioPacket   = NULL;
    UInt32        hwiKey     = 0;
    Bool          falsewhile = FALSE;
    UInt32        localcCnt  = 0;
    UInt32        localbCnt  = 0;
    Bool          firstReq   = (Bool) TRUE;
    Int32         status     = IOM_COMPLETED;

    assert(NULL != chanHandle);
    assert(NULL != chanHandle->devHandle);

    do
    {
        falsewhile = (Bool) FALSE;

        instHandle = (Mcasp_Object *) chanHandle->devHandle;

        assert(NULL != instHandle);

        /* This function services both transmit and receive channels. Define  *
         * critical section to avoid corruption of local variables.           *
         * CRITICAL SECTION: begins!                                          */
        hwiKey = (UInt32) Hwi_disable();

        /* stop the xmt/rcv state machine.                                    */
        if (Mcasp_ChanMode_RCV == chanHandle->channelOpMode)
        {
            /* Reset state m/c and frame sync of receive section              */
            Mcasp_localDeactivateSmFsForRcv(instHandle);
        }
        else
        {
            /* Reset state m/c and frame sync of transmit section             */
            Mcasp_localDeactivateSmFsForXmt(instHandle);
        }

        /* Disable EDMA  transfer                                             */
        EDMA3_DRV_disableTransfer(
            chanHandle->edmaHandle,
            chanHandle->xferChan,
            EDMA3_DRV_TRIG_MODE_EVENT);

        /* Clear the error bits of McASP due to stopping of peripheral.       */
        if (IOM_INPUT == chanHandle->mode)
        {
            McASPRxStatusSet(instHandle->hwInfo.regs,
                             (UInt32) MCASP_RXSTAT_RDMAERR_MASK);

            McASPRxStatusSet(instHandle->hwInfo.regs,
                             (UInt32) MCASP_RXSTAT_ROVRN_MASK);

            McASPRxStatusSet(instHandle->hwInfo.regs,
                             (UInt32) MCASP_RXSTAT_RSYNCERR_MASK);
        }
        else
        {
            McASPTxStatusSet(instHandle->hwInfo.regs,
                             (UInt32) MCASP_TXSTAT_XDMAERR_MASK);
            McASPTxStatusSet(instHandle->hwInfo.regs,
                             (UInt32) MCASP_TXSTAT_XUNDRN_MASK);
            McASPTxStatusSet(instHandle->hwInfo.regs,
                             (UInt32) MCASP_TXSTAT_XSYNCERR_MASK);
        }

        /* Get the current value of cCnt for the actual data transfered       */
        EDMA3_DRV_getPaRAMField(
            (EDMA3_DRV_Handle) chanHandle->edmaHandle,
            chanHandle->xferChan,
            EDMA3_DRV_PARAM_FIELD_CCNT,
            &localcCnt);

        EDMA3_DRV_getPaRAMField(
            (EDMA3_DRV_Handle) chanHandle->edmaHandle,
            chanHandle->xferChan,
            EDMA3_DRV_PARAM_FIELD_BCNT,
            &localbCnt);

        firstReq = (Bool) TRUE;

        if ((Bool) TRUE == chanHandle->isDmaDriven)
        {
            /* Empty the floating queue.                                      */
            while ((Bool) TRUE !=
                   Queue_empty(Queue_handle(&(chanHandle->queueFloatingList))))
            {
                ioPacket = (IOM_Packet *) \
                           Queue_get(Queue_handle(&(chanHandle->
                                                    queueFloatingList)));

                if (NULL == ioPacket)
                {
                    status = IOM_EBADIO;
                    /* Ideally control should not come here                   */
                    break;
                }

                /* set packet status equal to IOM_ABORTED                     */
                ioPacket->status = IOM_ABORTED;

                ioPacket->size = 0;

                /* Actual data transfer will be equal to size provided by     *
                 * application i.e.userDataBufferSize reduced by current      *
                 * value of cCnt * aCnt * bCnt                                */
                if ((Bool) TRUE == firstReq)
                {
                    ioPacket->size =
                        (UInt32) (ioPacket->size -
                                  (localcCnt * chanHandle->roundedWordWidth *
                                   localbCnt));
                    firstReq = (Bool) FALSE;
                }

                if (NULL != ioPacket)
                {
                    if (NULL != chanHandle->cbFxn)
                    {
                        /*  Application callback                              */
                        (*chanHandle->cbFxn)((Ptr) chanHandle->cbArg, ioPacket);
                    }
                }
                /* decrement the submit count as request is aborted           */
                chanHandle->submitCount--;
            }
        }
        else
        {
            ioPacket = chanHandle->dataPacket;

            if (NULL != ioPacket)
            {
                /* set packet status equal to Mcasp_E_aborted                 */
                ioPacket->status = IOM_ABORTED; /* Mcasp_E_aborted; */

                if (NULL != ioPacket)
                {
                    if (NULL != chanHandle->cbFxn)
                    {
                        /*  Application callback                              */
                        (*chanHandle->cbFxn)((Ptr) chanHandle->cbArg, ioPacket);
                    }
                }
            }
        }
        /* Empty the pendQUE queue.                                           */
        while ((Bool) TRUE !=
               Queue_empty(Queue_handle(&(chanHandle->queueReqList))))
        {
            ioPacket =
                (IOM_Packet *) Queue_get(Queue_handle(&(chanHandle->
                                                        queueReqList)));

            if (NULL != ioPacket)
            {
                /* set packet status equal to IOM_ABORTED                     */
                ioPacket->status = IOM_ABORTED;
                ioPacket->size   = 0;

                if (NULL != chanHandle->cbFxn)
                {
                    /*  Application callback                                  */
                    (*chanHandle->cbFxn)((Ptr) chanHandle->cbArg, ioPacket);
                }
            }
            /* decrement the submit count as request is aborted */
            chanHandle->submitCount--;
        }

        /* As EDMA is disabled it might have thrown an error and set error    *
         * bit. Clear the error bit to enable the transfer again              */
        EDMA3_DRV_clearErrorBits(
            chanHandle->edmaHandle,
            chanHandle->xferChan);

        /* Configure the EDMA channel and EDMA param tables with intialization*
         * configuration as they are configured at the create time.           */
        chanHandle->nextLinkParamSetToBeUpdated = 0;
        chanHandle->loopjobUpdatedinParamset    = (Bool) TRUE;

        Mcasp_localEdmaChanPaRAMsetup(chanHandle);

#ifdef Mcasp_LOOPJOB_ENABLED
        /* Enable EDMA transfer, state machine and fram sync                  */
        EDMA3_DRV_enableTransfer(
            chanHandle->edmaHandle,
            chanHandle->xferChan,
            EDMA3_DRV_TRIG_MODE_EVENT);

        if (Mcasp_ChanMode_RCV == chanHandle->channelOpMode)
        {
            /* Reset state m/c and frame sync of receive section              */
            Mcasp_localActivateSmFsForRcv(instHandle);
        }
        else
        {
            /* Reset state m/c and frame sync of transmit section             */
            Mcasp_localActivateSmFsForXmt(instHandle);
        }
#endif
        /* CRITICAL SECTION: ends!                                            */
        Hwi_restore(hwiKey);
    }
    while (falsewhile);

    return (status);
}

/**
 *  \brief   This function activates the receive section state machine and
 *           the corresponding frame sync.
 *
 *  \param   instHandle  [IN]   Handle to the Mcasp instance object
 *
 *  \return  None
 *
 *  \enter   instHandle  is a valid non null pointer
 *
 *  \leave   Not implemented
 *
 */
Void Mcasp_localActivateSmFsForRcv(const Mcasp_Object *instHandle)
{
    assert(NULL != instHandle);

    McASPRxStatusSet(instHandle->hwInfo.regs,
                     ((UInt32) MCASP_RXSTAT_RERR_MASK |
                      (UInt32) MCASP_RXSTAT_RDMAERR_MASK |
                      (UInt32) MCASP_RXSTAT_RSTAFRM_MASK |
                      (UInt32) MCASP_RXSTAT_RDATA_MASK |
                      (UInt32) MCASP_RXSTAT_RLAST_MASK |
                      (UInt32) MCASP_RXSTAT_RCKFAIL_MASK |
                      (UInt32) MCASP_RXSTAT_RSYNCERR_MASK |
                      (UInt32) MCASP_RXSTAT_ROVRN_MASK));
    /*serializer*/
    mcaspBitSetGblRCtl((Mcasp_Object *) instHandle,
                       (UInt32) MCASP_GBLCTLR_RSRCLR_MASK);
    /*state m/c*/
    mcaspBitSetGblRCtl((Mcasp_Object *) instHandle,
                       (UInt32) MCASP_GBLCTLR_RSMRST_MASK);
    /*frame sync*/
    mcaspBitSetGblRCtl((Mcasp_Object *) instHandle,
                       (UInt32) MCASP_GBLCTLR_RFRST_MASK);
}

/**
 *  \brief   This function activates the transmit section state machine and
 *           the corresponding frame sync.
 *
 *  \param   instHandle [IN]  pointer to the Mcasp instance object
 *
 *  \return  None
 *
 *  \enter   instHandle  is a valid non null pointer
 *
 *  \leave   Not implemented
 *
 */
Void Mcasp_localActivateSmFsForXmt(const Mcasp_Object *instHandle)
{
    assert(NULL != instHandle);

    McASPTxStatusSet(instHandle->hwInfo.regs,
                     ((UInt32) MCASP_TXSTAT_XERR_MASK |
                      (UInt32) MCASP_TXSTAT_XDMAERR_MASK |
                      (UInt32) MCASP_TXSTAT_XSTAFRM_MASK |
                      (UInt32) MCASP_TXSTAT_XDATA_MASK |
                      (UInt32) MCASP_TXSTAT_XLAST_MASK |
                      (UInt32) MCASP_TXSTAT_XCKFAIL_MASK |
                      (UInt32) MCASP_TXSTAT_XSYNCERR_MASK |
                      (UInt32) MCASP_TXSTAT_XUNDRN_MASK));

    /*Start the Serializer, State M/C and Frame Sync Generator                */
    mcaspBitSetGblXCtl((Mcasp_Object *) instHandle,
                       (UInt32) MCASP_GBLCTLX_XSRCLR_MASK);
    mcaspBitSetGblXCtl((Mcasp_Object *) instHandle,
                       (UInt32) MCASP_GBLCTLX_XSMRST_MASK);
    mcaspBitSetGblXCtl((Mcasp_Object *) instHandle,
                       (UInt32) MCASP_GBLCTLX_XFRST_MASK);
}

/**
 *  \brief   This function activates the state machine and the corresponding
 *           frame sync for both receive and transmit sections.
 *
 *  \param   instHandle [IN]  pointer to the Mcasp Instance object
 *
 *  \return  None
 *
 *  \enter   instHandle  is a valid non null pointer
 *
 *  \leave   Not implemented
 *
 */
Void Mcasp_localActivateSmFsForBoth(const Mcasp_Object *instHandle)
{
    assert((NULL != instHandle));

    /* Clear the interrupts                                                   */

    McASPTxStatusSet(instHandle->hwInfo.regs,
                     ((UInt32) MCASP_TX_STAT_ERR |
                      (UInt32) MCASP_TX_STAT_DMAERR |
                      (UInt32) MCASP_TX_STAT_STARTOFFRAME |
                      (UInt32) MCASP_TX_STAT_DATAREADY |
                      (UInt32) MCASP_TX_STAT_LASTSLOT |
                      (UInt32) MCASP_TXSTAT_XCKFAIL_MASK |
                      (UInt32) MCASP_TX_STAT_SYNCERR |
                      (UInt32) MCASP_TX_STAT_UNDERRUN));

    McASPRxStatusSet(instHandle->hwInfo.regs,
                     ((UInt32) MCASP_RXSTAT_RERR_MASK |
                      (UInt32) MCASP_RXSTAT_RDMAERR_MASK |
                      (UInt32) MCASP_RXSTAT_RSTAFRM_MASK |
                      (UInt32) MCASP_RXSTAT_RDATA_MASK |
                      (UInt32) MCASP_RXSTAT_RLAST_MASK |
                      (UInt32) MCASP_RXSTAT_RCKFAIL_MASK |
                      (UInt32) MCASP_RXSTAT_RSYNCERR_MASK |
                      (UInt32) MCASP_RXSTAT_ROVRN_MASK));

    /*Start the Serializer, State M/C and Frame Sync Generator*/
    mcaspBitSetGblCtl(instHandle,
                      (UInt32) (MCASP_GBLCTLX_XSRCLR_MASK |
                                MCASP_GBLCTLR_RSRCLR_MASK));
    mcaspBitSetGblCtl(instHandle,
                      (UInt32) (MCASP_GBLCTLX_XSMRST_MASK |
                                MCASP_GBLCTLR_RSMRST_MASK));
    mcaspBitSetGblCtl(instHandle,
                      (UInt32) (MCASP_GBLCTLX_XFRST_MASK |
                                MCASP_GBLCTLR_RFRST_MASK));
}

/**
 *  \brief  Resets the state m/c of the McASP xmt/rcv unit. In case of interrupt
 *          driven transactions, this also resets data queued for servicing the
 *          MCASP xmt/rcv unit when it is taken out of reset.
 *
 *  \param  chanHandle  [IN]  Handle to the mcasp channel to reset
 *  \param  eb          [OUT] pointer to the error information block
 *
 *  \return  Nothing
 *
 *  \enter   chanHandle  is a valid non null pointer
 *
 *  \leave   Not implemented
 */
Void Mcasp_localSmReset(Mcasp_ChannelHandle chanHandle)
{
    Mcasp_Object *instHandle = NULL;

    assert(NULL != chanHandle);
    assert(NULL != chanHandle->devHandle);

    instHandle = (Mcasp_Object *) chanHandle->devHandle;

    if (Mcasp_ChanMode_RCV == chanHandle->channelOpMode)
    {
        /* Reset state m/c and frame sync of receive section                  */
        Mcasp_localDeactivateSmFsForRcv(instHandle);
    }
    else
    {
        /* Reset state m/c and frame sync of transmit section                 */
        Mcasp_localDeactivateSmFsForXmt(instHandle);
    }

    if ((Bool) FALSE == chanHandle->isDmaDriven)
    {
        /* Interrupt driven transactions */

        /* When iohandle state m/c is reactivated, it will require two        *
         * requests to service it. Reset count to ensure this.                */
        chanHandle->dataQueuedOnReset     = 0;
        chanHandle->xferinProgressIntmode = (Bool) FALSE;
    }
    else
    {
        EDMA3_DRV_disableTransfer(
            (EDMA3_DRV_Handle) chanHandle->edmaHandle,
            (UInt32) chanHandle->xferChan,
            EDMA3_DRV_TRIG_MODE_EVENT);
    }
}

/**
 *  \brief  This function activates the state machine of the Mcasp transmit and
 *          receive sections and enables the edma transfer.
 *
 *  \param  chanHandle  [IN]  Handle to the Mcasp Channel
 *  \param  eb          [OUT] pointer to the error information block
 *
 *  \return  None
 *
 *  \enter   hanHandle  is a valid non null pointer
 *
 *  \leave   Not implemented
 */
Void Mcasp_localSmSet(Mcasp_ChannelHandle chanHandle)
{
    Mcasp_Object *instHandle = NULL;

    assert(NULL != chanHandle);
    assert(NULL != chanHandle->devHandle);

    instHandle = (Mcasp_Object *) chanHandle->devHandle;

    if ((Bool) FALSE == chanHandle->isDmaDriven)
    {
        /* Interrupt driven transactions */

        /* When channel state m/c is reactivated, it will require two         *
         * requests to service it. Reset count to ensure this.                */
        chanHandle->dataQueuedOnReset     = 0;
        chanHandle->xferinProgressIntmode = (Bool) FALSE;
    }
    else
    {
        /* Start the DMA chanHandle operation.                                */
        EDMA3_DRV_enableTransfer(
            (EDMA3_DRV_Handle) chanHandle->edmaHandle,
            (UInt32) chanHandle->xferChan,
            EDMA3_DRV_TRIG_MODE_EVENT);
    }

    if (Mcasp_ChanMode_RCV == chanHandle->channelOpMode)
    {
        /* Reset state m/c and frame sync of receive section                  */
        Mcasp_localActivateSmFsForRcv(instHandle);
    }
    else
    {
        /* Reset state m/c and frame sync of transmit section                 */
        Mcasp_localActivateSmFsForXmt(instHandle);
    }
}

/**
 *  \brief   This function configures format, frame sync, and other parameters
 *           related to the xmt section. Also configures the xmt clk section.
 *
 *  \param   instHandle  [IN]  Pointer to the Mcasp driver object
 *  \param   xmtData     [IN]  data for configuring the TX section
 *  \param   eb          [OUT] pointer to the error information block.
 *
 *  \return  IOM_COMPLETED  - Successful completion of read
 *          IOM_EBADARGS   - Invalid parameters
 *
 *
 *  \enter   instHandle  is a valid non null pointer
 *          xmtData     is a valid non null pointer
 *
 *  \leave   Not implemented
 */
Int32 Mcasp_localConfigXmtSection(Mcasp_Object            *instHandle,
                                  const Mcasp_HwSetupData *xmtData)
{
    Int32  status     = IOM_COMPLETED;
    UInt8  xCnt       = 0x00;
    UInt32 xMin       = 0x00;
    UInt32 xMax       = 0x00;
    UInt32 retryCount = 5U;
    UInt32 tempVal    = 0x00;
    UInt32 xCntTemp   = 0x00;
    UInt8  xMinTemp   = 0x00;
    UInt8  xMaxTemp   = 0x00;
    assert(NULL != instHandle);
    assert(NULL != xmtData);
    assert(NULL != (instHandle->hwInfo.regs));

    /* Configure TXMASK register                                              */
    McASPTxFmtMaskSet(instHandle->hwInfo.regs, xmtData->mask);

    /* Reset the XSMRST bit in GBLCTL register                                */
    mcaspBitRemoveGblXCtl(instHandle, (UInt32) ~(MCASP_GBLCTLX_XSMRST_MASK));

    /* Configure TXFMT register                                               */
    McASPTxFmtSet(instHandle->hwInfo.regs, xmtData->fmt);

    /* Reset the XFRST register in GBLCTL                                     */
    mcaspBitRemoveGblXCtl(instHandle, ~(MCASP_GBLCTLX_XFRST_MASK));

    /* Configure TXFMCTL register                                             */
    McASPTxFrameSyncCfg(
        instHandle->hwInfo.regs,
        (xmtData->frSyncCtl &
         (UInt32) MCASP_RXFMCTL_RMOD_MASK) >> MCASP_RXFMCTL_RMOD_SHIFT,
        (xmtData->frSyncCtl &
         (UInt32) MCASP_RXFMCTL_FRWID_MASK) >> MCASP_RXFMCTL_FRWID_SHIFT,
        (xmtData->frSyncCtl &
         ((UInt32) MCASP_RXFMCTL_FSRP_MASK |
          (UInt32) MCASP_RXFMCTL_FSRM_MASK)) >> MCASP_RXFMCTL_FSRP_SHIFT);

    if ((UInt32) MCASP_TXFMCTL_FSXM_INTERNAL ==
        (((UInt32) MCASP_TXFMCTL_FSXM_MASK & xmtData->frSyncCtl)
         >> MCASP_TXFMCTL_FSXM_SHIFT))
    {
        McASPPinDirOutputSet(instHandle->hwInfo.regs, (UInt32) MCASP_PIN_AFSX);
    }

    mcaspBitRemoveGblXCtl(
        instHandle,
        ~((UInt32) MCASP_GBLCTLX_XHCLKRST_MASK
          | (UInt32) MCASP_GBLCTLX_XCLKRST_MASK
          | (UInt32) MCASP_GBLCTLX_XSRCLR_MASK));

    /* Configure XTDM register                                                */
    McASPTxTimeSlotSet(instHandle->hwInfo.regs, xmtData->tdm);

    /* Configure XCLKCHK register                                             */
    McASPTxClkCheckRegWrite(instHandle->hwInfo.regs, xmtData->clk.clkChk);

    McASPTxClkPolaritySet(instHandle->hwInfo.regs,
                          (xmtData->clk.clkSetupClk &
                           (UInt32) MCASP_ACLKXCTL_CLKXP_MASK));

    McASPTxHFClkPolaritySet(instHandle->hwInfo.regs,
                            ((xmtData->clk.clkSetupHiClk &
                              (UInt32) MCASP_AHCLKXCTL_HCLKXP_MASK) <<
                             MCASP_AHCLKXCTL_HCLKXP_SHIFT));

    if ((xmtData->clk.clkSetupClk &
         (UInt32) MCASP_ACLKXCTL_ASYNC_MASK) ==
        (UInt32) MCASP_ACLKXCTL_ASYNC_MASK)
    {
        McASPTxRxClkSyncDisable(instHandle->hwInfo.regs);
    }
    else
    {
        McASPTxRxClkSyncEnable(instHandle->hwInfo.regs);
    }

    McASPTxClkCfg(instHandle->hwInfo.regs,
                  ((xmtData->clk.clkSetupClk &
                    (UInt32) MCASP_ACLKXCTL_CLKXM_MASK) |
                   (xmtData->clk.clkSetupHiClk &
                    (UInt32) MCASP_AHCLKXCTL_HCLKXM_MASK)),
                  ((xmtData->clk.clkSetupClk &
                    (UInt32) MCASP_ACLKXCTL_CLKXDIV_MASK) >>
                   MCASP_ACLKXCTL_CLKXDIV_SHIFT),
                  ((xmtData->clk.clkSetupHiClk &
                    (UInt32) MCASP_AHCLKXCTL_HCLKXDIV_MASK) >>
                   MCASP_AHCLKXCTL_HCLKXDIV_SHIFT));

    /* Sequence of start: starting hclk first                                 */
    mcaspBitSetGblXCtl(instHandle, (UInt32) MCASP_GBLCTLX_XHCLKRST_MASK);

    /* start ACLKX only if internal clock is used                             */
    if ((UInt32) MCASP_ACLKXCTL_CLKXM_INTERNAL ==
        ((xmtData->clk.clkSetupClk & (UInt32) MCASP_ACLKXCTL_CLKXM_MASK) >>
         MCASP_ACLKXCTL_CLKXM_SHIFT))
    {
        mcaspBitSetGblXCtl(instHandle, (UInt32) MCASP_GBLCTLX_XCLKRST_MASK);
        McASPPinDirOutputSet(instHandle->hwInfo.regs, (UInt32) MCASP_PIN_ACLKX);
    }

    /* Configure ACLKXCTL register                                            */

    /* Configure AHCLKXCTL register                                           */

    if ((UInt32) MCASP_AHCLKXCTL_HCLKXM_INTERNAL ==
        ((xmtData->clk.clkSetupHiClk & (UInt32) MCASP_AHCLKXCTL_HCLKXM_MASK) >>
         MCASP_AHCLKXCTL_HCLKXM_SHIFT))
    {
        McASPPinDirOutputSet(instHandle->hwInfo.regs, (UInt32) MCASP_PIN_AHCLKX);
    }

    /*
     *  McASPTxClkPolaritySet(instHandle->hwInfo.regs,
     *                             (xmtData->clk.clkSetupClk &
     *                             MCASP_ACLKXCTL_CLKXP_MASK));
     *
     *  McASPTxHFClkPolaritySet(instHandle->hwInfo.regs,
     *                               ((xmtData->clk.clkSetupHiClk &
     *                               MCASP_AHCLKXCTL_HCLKXP_MASK) <<
     *                               MCASP_AHCLKXCTL_HCLKXP_SHIFT));
     *
     *  McASPTxClkCfg(instHandle->hwInfo.regs,
     *                     ((xmtData->clk.clkSetupClk &
     *                     MCASP_ACLKXCTL_CLKXM_MASK) |
     *                     (xmtData->clk.clkSetupHiClk &
     *                     MCASP_AHCLKXCTL_HCLKXM_MASK)),
     *                     ((xmtData->clk.clkSetupClk &
     *                     MCASP_ACLKXCTL_CLKXDIV_MASK) >>
     *                     MCASP_ACLKXCTL_CLKXDIV_SHIFT),
     *                     ((xmtData->clk.clkSetupHiClk &
     *                     MCASP_AHCLKXCTL_HCLKXDIV_MASK) >>
     *                     MCASP_AHCLKXCTL_HCLKXDIV_SHIFT));
     */

    /* Configure XEVTCTL register                                             */
    if (Mcasp_TX_CLK_FAIL == (Mcasp_TX_CLK_FAIL & xmtData->intCtl))
    {
        UInt32 tempValue = 0x00;
        tempValue = McASPTxClkCheckRegRead(instHandle->hwInfo.regs);
        /* now read the counter value and set val +1 as max and val -1 as min */
        xCntTemp = ((tempValue & (UInt32) MCASP_TXCLKCHK_XCNT_MASK) >>
                    MCASP_TXCLKCHK_XCNT_SHIFT);
        xCnt     = (UInt8) xCntTemp;
        xMaxTemp = (xCnt + (UInt8) 3U);
        xMinTemp = (xCnt - (UInt8) 3U);
        xMin     = (UInt32) xMinTemp;
        xMax     = (UInt32) xMaxTemp;

        if (xCnt >= (UInt8) 0xFD)
        {
            xMax = 255U;
        }

        if (xCnt <= (UInt8) 3U)
        {
            xMin = 0U;
        }

        /* now write the value to the register                                */
        tempValue &= ~(MCASP_TXCLKCHK_XMAX_MASK |
                       MCASP_TXCLKCHK_XMIN_MASK);
        McASPTxClkCheckRegWrite(instHandle->hwInfo.regs, tempValue);

        McASPTxClkCheckConfig(instHandle->hwInfo.regs,
                              (xmtData->clk.clkChk &
                               (UInt32) MCASP_TXCLKCHK_XPS_MASK),
                              (UInt8) xMin, (UInt8) xMax);

        /* check if the clock has stablised without any errors                */
        while (retryCount > 0)
        {
            retryCount--;
            /* write to the XCLK FAIL register to clear the failure bit       */
            tempVal = McASPTxStatusGet(instHandle->hwInfo.regs);

            McASPTxStatusSet(instHandle->hwInfo.regs,
                             (tempVal | (UInt32) MCASP_TXSTAT_XCKFAIL_MASK));

            Task_sleep((UInt32) 10);

            tempVal = McASPTxStatusGet(instHandle->hwInfo.regs);

            /* verify if the clock failure is detected. if not detected then  *
             * we can retry else we can continue with the intialisation       */
            if (Mcasp_TX_CLK_FAIL != (tempVal & (UInt32) Mcasp_TX_CLK_FAIL))
            {
                break;
            }
        }

        if (0x00U == retryCount)
        {
            /* setting the clock failure interrupt failed                     */
            status = IOM_EBADARGS;
        }

        McASPTxIntEnable(instHandle->hwInfo.regs, Mcasp_TX_CLK_FAIL);

        /* set the AMUTE register XCLK bit                                    */
        /* hal_mcasp_aMuteEnable(instHandle->hwInfo.regs,
         *                    MCASP_AMUTE_TX_CLKFAIL,
         *                    MCASP_AMUTE_PIN_HIGH);*/
    }

    /* Configure XINTCTL register                                             */
    McASPTxIntEnable(instHandle->hwInfo.regs, xmtData->intCtl);

#ifndef Mcasp_LOOPJOB_ENABLED
    /* copy the user supplied interrupt enable mask                           */
    instHandle->XmtObj.userIntValue = xmtData->intCtl;
#else
    /* Non Const variable assignment, fix for Misra C                         */
    instHandle->XmtObj.userIntValue = instHandle->XmtObj.userIntValue;
#endif /* Mcasp_LOOPJOB_ENABLED  */

    /* Configure XEVTCTL register                                             */
    McASPTxRxDMAEvtCntrlWrite(instHandle->hwInfo.regs, (UInt8) TX,
                              xmtData->evtCtl);

    return (status);
}

/**
 *  \brief   This function configures the format, frame sync, and other params
 *           related to the rcv section. Also configures the rcv clk section.
 *
 *  \param   hMcasp      [IN]     Handle to the McASP instance
 *  \param   rcvData     [IN]     Receive related parameters
 *  \return
 *           IOM_COMPLETED   - Successful completion of read
 *           IOM_EBADARGS    - Invalid parameters or Invalid handle
 *
 *  \enter   instHandle  is a valid non null pointer
 *           rcvData     is a valid non null pointer
 *
 *  \leave   Not implemented
 */

Int32 Mcasp_localConfigRcvSection(Mcasp_Object            *instHandle,
                                  const Mcasp_HwSetupData *rcvData)
{
    Int32  status     = IOM_COMPLETED;
    UInt8  rCnt       = 0x00;
    UInt32 rMin       = 0x00;
    UInt32 rMax       = 0x00;
    UInt32 retryCount = 5U;
    UInt32 tempVal    = 0x00;
    UInt32 rCntTemp   = 0x00;
    UInt8  rMinTemp   = 0x00;
    UInt8  rMaxTemp   = 0x00;

    assert(NULL != instHandle);
    assert(NULL != rcvData);
    assert(NULL != instHandle->hwInfo.regs);

    /* Configure RMASK register                                               */
    McASPRxFmtMaskSet(instHandle->hwInfo.regs, rcvData->mask);

    /* Reset the RSMRST bit in GBLCTL register                                */
    mcaspBitRemoveGblRCtl(instHandle, ~(MCASP_GBLCTLR_RSMRST_MASK));

    /* Configure RFMT register                                                */
    McASPRxFmtSet(instHandle->hwInfo.regs, rcvData->fmt);

    mcaspBitRemoveGblRCtl(instHandle, ~(MCASP_GBLCTLR_RFRST_MASK));

    /* Configure RXFMCTL register                                             */
    McASPRxFrameSyncCfg(
        instHandle->hwInfo.regs,
        (rcvData->frSyncCtl &
         (UInt32) MCASP_RXFMCTL_RMOD_MASK) >> MCASP_RXFMCTL_RMOD_SHIFT,
        (rcvData->frSyncCtl &
         (UInt32) MCASP_RXFMCTL_FRWID_MASK) >> MCASP_RXFMCTL_FRWID_SHIFT,
        (rcvData->frSyncCtl &
         ((UInt32) MCASP_RXFMCTL_FSRP_MASK |
          (UInt32) MCASP_RXFMCTL_FSRM_MASK)) >> MCASP_RXFMCTL_FSRP_SHIFT);

    if ((UInt32) MCASP_RXFMCTL_FSRM_INTERNAL ==
        (((UInt32) MCASP_RXFMCTL_FSRM_MASK & rcvData->frSyncCtl) >>
         MCASP_RXFMCTL_FSRM_SHIFT))
    {
        McASPPinDirOutputSet(instHandle->hwInfo.regs, (UInt32) MCASP_PIN_AFSR);
    }

    /* Reset RHCLKRST, RCLKRST, RSRCLR in GBLCTL                              */
    mcaspBitRemoveGblRCtl(
        instHandle,
        ~((UInt32) MCASP_GBLCTLR_RHCLKRST_MASK
          | (UInt32) MCASP_GBLCTLR_RCLKRST_MASK
          | (UInt32) MCASP_GBLCTLR_RSRCLR_MASK));

    /* Configure it completely before starting the clocks                     */
    /* Configure RTDM register                                                */
    McASPRxTimeSlotSet(instHandle->hwInfo.regs, rcvData->tdm);

    /* Configure RXCLKCHK register                                            */
    McASPRxClkCheckRegWrite(instHandle->hwInfo.regs,
                            rcvData->clk.clkChk);

    McASPRxClkPolaritySet(instHandle->hwInfo.regs,
                          (rcvData->clk.clkSetupClk &
                           (UInt32) MCASP_ACLKRCTL_CLKRP_MASK));

    McASPRxHFClkPolaritySet(instHandle->hwInfo.regs,
                            ((rcvData->clk.clkSetupHiClk &
                              (UInt32) MCASP_AHCLKRCTL_HCLKRP_MASK) <<
                             MCASP_AHCLKRCTL_HCLKRP_SHIFT));

    McASPRxClkCfg(instHandle->hwInfo.regs,
                  ((rcvData->clk.clkSetupClk &
                    (UInt32) MCASP_ACLKRCTL_CLKRM_MASK) |
                   (rcvData->clk.clkSetupHiClk &
                    (UInt32) MCASP_AHCLKRCTL_HCLKRM_MASK)),
                  ((rcvData->clk.clkSetupClk &
                    (UInt32) MCASP_ACLKRCTL_CLKRDIV_MASK) >>
                   MCASP_ACLKRCTL_CLKRDIV_SHIFT),
                  ((rcvData->clk.clkSetupHiClk &
                    (UInt32) MCASP_AHCLKRCTL_HCLKRDIV_MASK) >>
                   MCASP_AHCLKRCTL_HCLKRDIV_SHIFT));

    /* Sequence of start: starting hclk first                                 */
    /* start AHCLKR                                                           */
    mcaspBitSetGblRCtl(instHandle, (UInt32) MCASP_GBLCTLR_RHCLKRST_MASK);

    /* start ACLKR only if internal clock is used*/
    if ((UInt32) MCASP_ACLKRCTL_CLKRM_INTERNAL ==
        ((rcvData->clk.clkSetupClk & (UInt32) MCASP_ACLKRCTL_CLKRM_MASK) >>
         MCASP_ACLKRCTL_CLKRM_SHIFT))
    {
        mcaspBitSetGblRCtl(instHandle, (UInt32) MCASP_GBLCTLR_RCLKRST_MASK);
        McASPPinDirOutputSet(instHandle->hwInfo.regs, (UInt32) MCASP_PIN_ACLKR);
    }

    /* Configure ACLKRCTL register                                            */
    /* Configure AHCLKRCTL register */
    if ((UInt32) MCASP_AHCLKRCTL_HCLKRM_INTERNAL ==
        ((rcvData->clk.clkSetupHiClk & (UInt32) MCASP_AHCLKRCTL_HCLKRM_MASK) >>
         MCASP_AHCLKRCTL_HCLKRM_SHIFT))
    {
        McASPPinDirOutputSet(instHandle->hwInfo.regs, 0x40000000U);
    }
    /*
     *  McASPRxClkPolaritySet(instHandle->hwInfo.regs,
     *                             (rcvData->clk.clkSetupClk &
     *                             MCASP_ACLKRCTL_CLKRP_MASK));
     *
     *  McASPRxHFClkPolaritySet(instHandle->hwInfo.regs,
     *                               ((rcvData->clk.clkSetupHiClk &
     *                               MCASP_AHCLKRCTL_HCLKRP_MASK) <<
     *                               MCASP_AHCLKRCTL_HCLKRP_SHIFT));
     *
     *  McASPRxClkCfg(instHandle->hwInfo.regs,
     *                     ((rcvData->clk.clkSetupClk &
     *                      MCASP_ACLKRCTL_CLKRM_MASK) |
     *                      (rcvData->clk.clkSetupHiClk &
     *                      MCASP_AHCLKRCTL_HCLKRM_MASK)),
     *                      ((rcvData->clk.clkSetupClk &
     *                      MCASP_ACLKRCTL_CLKRDIV_MASK) >>
     *                      MCASP_ACLKRCTL_CLKRDIV_SHIFT),
     *                      ((rcvData->clk.clkSetupHiClk &
     *                      MCASP_AHCLKRCTL_HCLKRDIV_MASK) >>
     *                      MCASP_AHCLKRCTL_HCLKRDIV_SHIFT));
     */

    /* Configure REVTCTL register                                             */
    if (Mcasp_RX_CLK_FAIL == (Mcasp_RX_CLK_FAIL & rcvData->intCtl))
    {
        UInt32 tempValue = 0x00;
        tempValue = McASPRxClkCheckRegRead(instHandle->hwInfo.regs);
        /* now read the counter value and set val +1 as max and val -1 as min */
        rCntTemp = ((tempValue & (UInt32) MCASP_RXCLKCHK_RCNT_MASK) >>
                    MCASP_RXCLKCHK_RCNT_SHIFT);
        rCnt     = (UInt8) rCntTemp;
        rMaxTemp = rCnt + (UInt8) 3U;
        rMinTemp = rCnt - (UInt8) 3U;

        rMax = (UInt32) rMaxTemp;
        rMin = (UInt32) rMinTemp;

        if (rCnt >= (UInt8) 0xFD)
        {
            rMax = 255U;
        }

        if (rCnt <= (UInt8) 3U)
        {
            rMin = 0U;
        }

        /* now write the value to the register                                */
        tempValue &= ~((UInt32) MCASP_RXCLKCHK_RMAX_MASK |
                       (UInt32) MCASP_RXCLKCHK_RMIN_MASK);
        McASPRxClkCheckRegWrite(instHandle->hwInfo.regs, tempValue);
        McASPRxClkCheckConfig(instHandle->hwInfo.regs,
                              (rcvData->clk.clkChk &
                               (UInt32) MCASP_RXCLKCHK_RPS_MASK),
                              (UInt8) rMin,
                              (UInt8) rMax);

        /* check if the clock has stablised without any errors                */
        while (retryCount > 0U)
        {
            retryCount--;

            /* write to the RCLK FAIL register to clear the failure bit       */
            tempVal = McASPRxStatusGet(instHandle->hwInfo.regs);

            McASPRxStatusSet(instHandle->hwInfo.regs,
                             (tempVal | (UInt32) MCASP_RXSTAT_RCKFAIL_MASK));

            /* wait for the reading to be taken                               */
            Task_sleep((UInt32) 10);

            tempVal = McASPRxStatusGet(instHandle->hwInfo.regs);

            /* verify if the clock failure is detected. if detected then      *
             * we can retry else we can continue with the intialisation       */
            if ((UInt32) MCASP_RXSTAT_RCKFAIL_MASK !=
                (tempVal & (UInt32) MCASP_RXSTAT_RCKFAIL_MASK))
            {
                break;
            }
        }

        if (0x00U == retryCount)
        {
            /* setting the clock failure interrupt failed                     */
            status = IOM_EBADARGS;
        }
        McASPRxIntEnable(instHandle->hwInfo.regs, Mcasp_RX_CLK_FAIL);

        /* set the AMUTE register RCLK bit                                    */
        /* hal_mcasp_aMuteEnable(instHandle->hwInfo.regs,
         *                    MCASP_AMUTE_RX_CLKFAIL,
         *                    MCASP_AMUTE_PIN_HIGH); */
    }
    McASPRxIntEnable(instHandle->hwInfo.regs, rcvData->intCtl);

#ifndef Mcasp_LOOPJOB_ENABLED
    /* copy the user supplied interrupt enable mask                           */
    instHandle->RcvObj.userIntValue = rcvData->intCtl;
#else
    /* Non Const variable assignment fix for Misra C Fixes
     *                    */
    instHandle->RcvObj.userIntValue = instHandle->RcvObj.userIntValue;
#endif /* Mcasp_LOOPJOB_ENABLED  */

    McASPTxRxDMAEvtCntrlWrite(instHandle->hwInfo.regs, (UInt8) RX,
                              rcvData->evtCtl);
    return (status);
}

/**
 *  \brief  This function resets the bits related to transmit in XGBLCTL.
 *
 *  \param  hMcasp  [IN] Pointer to the Mcasp Hardware info structure
 *
 *  \return
 *          IOM_COMPLETED   - Successful completion
 *          IOM_EBADARGS    - Invalid parameters or Invalid handle
 *
 *  \enter  hMcasp      is a valid non null pointer
 *
 *  \leave  Not implemented
 */
Int32 Mcasp_localResetXmt(Mcasp_HwHandle hMcasp)
{
    Int32 status = IOM_COMPLETED;

    assert(NULL != hMcasp);
    assert(NULL != hMcasp->regs);

    McASPTxReset(hMcasp->regs);

    return (status);
}

/**
 *  \brief   This function resets the bits related to receive in RGBLCTL.
 *
 *  \param   hMcasp  [IN] Pointer to the Mcasp Hardware info structure
 *
 *  \return
 *           IOM_COMPLETED   - Successful completion
 *           IOM_EBADARGS    - Invalid parameters or Invalid handle
 *
 *  \enter   hMcasp      is a valid non null pointer
 *
 *  \leave   Not implemented
 */
Int32 Mcasp_localResetRcv(Mcasp_HwHandle hMcasp)
{
    Int32 status = IOM_COMPLETED;

    assert(NULL != hMcasp);
    assert(NULL != hMcasp->regs);

    McASPRxReset(hMcasp->regs);

    return (status);
}

/**
 *  \brief  For the transmit operation, the eDMA channel's destination
 *          port is tied to the MCASP DAT port. In case of receive, the eDMA
 *          channel's source port is tied to the MCASP DAT port. The source
 *          address for transmit eDMA channel and the destination address for
 *          the receive eDMA channel are set here.
 *
 *  \param  chanp      [IN]    Pointer to channel
 *  \param  ioPacket   [IN]    Pointer to request to be processed
 *
 *  \return IOM_COMPLETED, if the address is set correctly
 *          ERROR ID otherwise
 *
 *  \enter  chanp       is a valid non null pointer
 *          ioPacket    is a valid non null pointer
 *
 *  \leave  Not implemented
 */
Int32 Mcasp_localEdmaProcessPkt(Ptr chanp, const IOM_Packet *ioPacket)
{
    Mcasp_Object         *instHandle = NULL;
    Mcasp_ChannelHandle   chanHandle = NULL;
    Mcasp_PktAddrPayload *payLoad    = NULL;
    Int32 status     = IOM_COMPLETED;
    Bool  falsewhile = (Bool) TRUE;

    /* Validate pointers and parameters                                       */
    assert(NULL != chanp);
    assert(NULL != ioPacket);

    chanHandle = (Mcasp_ChannelHandle) chanp;

    assert(NULL != chanHandle->devHandle);

    do
    {
        falsewhile = (Bool) FALSE;

        instHandle = (Mcasp_Object *) chanHandle->devHandle;

        if ((Mcasp_ChanMode_RCV != chanHandle->channelOpMode)
            && (Mcasp_ChanMode_XMT_DIT == chanHandle->channelOpMode))
        {
            /* The data should be a payload structure                         */
            payLoad = (Mcasp_PktAddrPayload *) ioPacket->addr;
            assert(NULL != payLoad);

            if ((Bool) TRUE == payLoad->writeDitParams)
            {
                /* DIT Mode: for DIT mode as of now each packet (IOP)         *
                 * carries/should carry 1 super frame = 192 frames = 384 sub  *
                 * frames of data max                                         */
                status = mcaspWriteChanStatRam(
                    &(instHandle->hwInfo),
                    (Mcasp_ChStatusRam *) payLoad->chStat);

                if (IOM_COMPLETED != status)
                {
                    status = IOM_ABORTED;
                }
                if (IOM_COMPLETED == status)
                {
                    status = mcaspWriteUserDataRam(
                        &(instHandle->hwInfo),
                        (Mcasp_UserDataRam *) payLoad->userData);
                }
                if (IOM_COMPLETED != status)
                {
                    status = IOM_ABORTED;
                }
            }
        }

        /* we are going to update the paramset from EDMA callback context.    *
         * That means the one of the param sets are having audio data         *
         * just completed data request and one having currently loaded (active*
         * ) data request Current index is pointing only latest paramset      *
         * (that is active)  so move the index                                */
        if (IOM_COMPLETED == status)
        {
            Mcasp_localGetNextIndex(&chanHandle->nextLinkParamSetToBeUpdated);

            /* Link the packet
             *                                                   */
            status = Mcasp_localUpdtDtPktToLnkPrms(chanHandle, ioPacket);
        }
    }
    while (falsewhile);

    return (status);
}

/**
 *  \brief   This function completes the current pending request and then
 *           invokes the application registered callback.
 *
 *  \param   chanHandle   [IN]  Handle to the channel
 *  \param   eb           [IN]  pointer to the error block
 *
 *  \return  None
 *
 *  \enter   chanHandle  is a valid non null pointer
 *
 *  \leave   Not implemented
 */
Void Mcasp_localCompleteCurrentIo(Mcasp_ChannelHandle chanHandle)
{
    IOM_Packet   *ioPacket = NULL;
#ifndef Mcasp_LOOPJOB_ENABLED
    Mcasp_Object *instHandle = NULL;
#endif

    assert(NULL != chanHandle);

#ifndef Mcasp_LOOPJOB_ENABLED
    assert(NULL != chanHandle->devHandle);
    instHandle = (Mcasp_Object *) chanHandle->devHandle;
#endif

    if ((Bool) TRUE == chanHandle->isTempPacketValid)
    {
        ioPacket = chanHandle->tempPacket;
        chanHandle->isTempPacketValid = (Bool) FALSE;
    }
    else
    {
        ioPacket = chanHandle->dataPacket;
    }

#ifndef Mcasp_LOOPJOB_ENABLED
    /* reduce the dependency count                                            */
    Mcasp_localPrcmOff(instHandle);
#endif

    if (NULL != ioPacket)
    {
        /* call the completion callback function registered with us           *
         * during channel creation                                            */
        if ((NULL != chanHandle->cbFxn) && (NULL != chanHandle->cbArg))
        {
            /*  Application callback                                          */
            (*chanHandle->cbFxn)((Ptr) chanHandle->cbArg, ioPacket);
        }
    }
    chanHandle->dataPacket         = NULL;
    chanHandle->userDataBufferSize = 0;
}

/**
 *  \brief   This function aborts all the pending requests in the queue
 *
 *  \param   chanHandle   [IN]  Handle to the channel
 *  \param   eb           [IN]  pointer to the error block
 *
 *  \return  None
 *
 *  \enter   chanHandle  is a valid non null pointer
 *
 *  \leave   Not implemented
 */
Int32 Mcasp_localCancelAndAbortAllIo(Mcasp_ChannelHandle chanHandle)
{
    UInt32 dlbMode = 0U;
    Mcasp_Object        *instHandle = NULL;
    Int32  status = IOM_COMPLETED;

    assert(NULL != chanHandle);
    assert(NULL != chanHandle->devHandle);

    chanHandle->submitCount--;

    chanHandle->dataPacket->status = IOM_ABORTED;

    Mcasp_localCompleteCurrentIo((Mcasp_ChannelHandle) chanHandle);

    instHandle = (Mcasp_Object *) chanHandle->devHandle;
    assert(NULL != instHandle);

    /* While aborting care should be taken about DLB mode otherwise           *
     * aborting packets in only one direction will make the packet in         *
     * other direction not to return                                          */
    dlbMode = McASPDlbRegRead(instHandle->hwInfo.regs);

    if (MCASP_LBCTL_DLBEN_ENABLE == dlbMode)
    {
        status =
            Mcasp_localAbortReset((Mcasp_ChannelHandle) & (instHandle->RcvObj));
        if (IOM_COMPLETED == status)
        {
            status =
                Mcasp_localAbortReset((Mcasp_ChannelHandle) &
                                      (instHandle->XmtObj));
        }
    }
    else
    {
        status = Mcasp_localAbortReset(chanHandle);
    }

    return (status);
}

/**
 *  \brief   This function sets the GBLCTL bit and wait and checks that bit is
 *           set or not
 *
 *  \param   instHandle  [IN]  pointer to the mcasp instance object
 *  \param   bitMaskVal  [IN]  mask bit value
 *
 *  \return  None
 *
 *  \enter   instHandle  is a valid non null pointer
 *           bitMaskVal  is a valid value
 *
 *  \leave   Not implemented
 */
static Void mcaspBitSetGblCtl(const Mcasp_Object *instHandle, UInt32 bitMaskVal)
{
    UInt32 timeout = MCASP_GBLCTL_TIMEOUT;
    Bool   isTask  = (Bool) FALSE;
    UInt32 tempVal = 0x00;

    assert(NULL != instHandle);

    tempVal = McASPGlobalCtlGet(instHandle->hwInfo.regs);

    /* If already this bit is set then don't set again                        */
    if ((tempVal & bitMaskVal) != bitMaskVal)
    {
        tempVal |= bitMaskVal;

        McASPGlobalCtlSet(instHandle->hwInfo.regs, tempVal);

        tempVal = McASPGlobalCtlGet(instHandle->hwInfo.regs);

        while (((tempVal & bitMaskVal) != bitMaskVal) && (timeout > 0))
        {
            /* reduce the timout count value                                  */
            timeout--;

            isTask = (Bool) (BIOS_getThreadType() == BIOS_ThreadType_Task);

            /* wait for 1 tick only if called from a task context             */
            if ((Bool) TRUE == isTask)
            {
                Task_sleep((UInt32) 1);
            }
            tempVal = McASPGlobalCtlGet(instHandle->hwInfo.regs);
        }
        assert(0U != timeout);
    }
}

/*
 *  \brief Initializes McASP driver's data structures
 *
 *  This function initializes the McASP driver's internal data structures
 *  used by the driver for the mute and loop job. These data structures are
 *  aligned to the proper cache line boundary here.
 *
 *  \param  instNum [IN]  instance num of the data structure to initialise
 *
 *  \return Nothing
 *
 *  \enter   instNUm     is a valid value
 *
 *  \leave   Not implemented
 */
static Void mcaspInit(UInt32 instNum)
{
    UInt32 tempVal;
    if (instNum < CSL_MCASP_PER_CNT)
    {
#ifdef Mcasp_LOOPJOB_ENABLED
        /* initialise the mcasp device driver internal buffers                */
        memset((Void *) &Mcasp_loopDstBuf[instNum], 0x00,
               sizeof (Mcasp_TempBuffer));
        memset((Void *) &Mcasp_loopSrcBuf[instNum], 0x00,
               sizeof (Mcasp_TempBuffer));

        /* align the buffers to the cache line size                           */
        tempVal = ((UInt32) & Mcasp_loopSrcBuf[instNum].scratchBuf
                   + (UInt32) 0x7FU) & ~(UInt32) 0x7FU;
        Mcasp_loopSrcBuf[instNum].scratchBuffer =
            (UInt32 *) tempVal;

        tempVal = ((UInt32) & Mcasp_loopDstBuf[instNum].scratchBuf
                   + (UInt32) 0x7FU) & ~(UInt32) 0x7FU;
        Mcasp_loopDstBuf[instNum].scratchBuffer =
            (UInt32 *) tempVal;
#endif  /* Mcasp_LOOPJOB_ENABLED */
        tempVal = ((UInt32) & Mcasp_muteBuf[instNum].scratchBuf
                   + (UInt32) 0x7FU) & ~(UInt32) 0x7FU;

        Mcasp_muteBuf[instNum].scratchBuffer =
            (UInt32 *) tempVal;
    }
    /* initialisation of driver data structures is completed                  */
    return;
}

/**
 *  \brief   Writes a packet of data to the output channel of the driver
 *           This function is called by the IDriver submit function. This
 *           function is called with handle to the o/p channel and the pointer
 *           to ioRequest structure which takes a set of information need for
 *           the IO.
 *
 *  \param   chanHandle  [IN]   Handle to the McASP channel
 *  \param   ioPacket    [IN]   io request information structure
 *
 *  \return IOM_COMPLETED or Error code
 *
 *  \enter   chanHandle  is a valid non null pointer
 *           ioPacket    is a valid non null pointer
 *
 *  \leave   Not implemented
 */
static Int32 mcaspSubmitReq(Mcasp_ChannelHandle chanHandle,
                            IOM_Packet         *ioPacket)
{
    Mcasp_Object         *instHandle = NULL;
    Mcasp_PktAddrPayload *payLoad    = NULL;
    Int32  status     = IOM_COMPLETED;
    UInt32 hwiKey     = 0;
    Bool   falsewhile = (Bool) TRUE;
    Ptr    pktAddr    = NULL;
#ifdef Mcasp_LOOPJOB_ENABLED
    Bool   chanStopped = (Bool) FALSE;
#endif
    Void  *ioPacketVoidTempPtr;

    assert(NULL != chanHandle);
    assert(NULL != ioPacket);
    assert(NULL != chanHandle->devHandle);

    /* check for the valid packet size                                        */
    assert((0 != ioPacket->size)
           && (Mcasp_MAX_PACKET_SIZE >=
               (ioPacket->size / chanHandle->noOfSerAllocated)));

    do
    {
        falsewhile = (Bool) FALSE;
        instHandle = (Mcasp_Object *) chanHandle->devHandle;
        assert(NULL != instHandle);

        if ((Bool) TRUE == instHandle->isDataBufferPayloadStructure)
        {
            payLoad = (Mcasp_PktAddrPayload *) ioPacket->addr;
            assert(NULL != payLoad);

            pktAddr = payLoad->addr;
        }
        else
        {
            pktAddr = ioPacket->addr;
        }

        assert(NULL != pktAddr);

        /* maintain cache coherency                                           */
        if (IOM_INPUT == chanHandle->mode)
        {
            /* Cleans and invalidate the D Cache in MVA way                   */
            if ((Bool) TRUE == instHandle->enablecache)
            {
                Cache_wbInv(pktAddr, ioPacket->size, Cache_Type_ALL,
                            (Bool) TRUE);
            }
#ifdef Mcasp_LOOPJOB_ENABLED
            /* check if the state machine is stopped. if the state machine is *
             * stopped then we will load the packets in to the pending queue  */
            if ((Bool) TRUE == instHandle->stopSmFsRcv)
            {
                chanStopped = (Bool) TRUE;
            }
#endif
        }
        else
        {
            /* clean the D Cache in MVA way                                   */
            if ((Bool) TRUE == instHandle->enablecache)
            {
                Cache_wb(pktAddr, ioPacket->size, Cache_Type_ALL, (Bool) TRUE);
            }
#ifdef Mcasp_LOOPJOB_ENABLED
            /* check if the state machine is stopped. if the state machine is *
             * stopped then we will load the packets in to the pending queue  */
            if ((Bool) TRUE == instHandle->stopSmFsXmt)
            {
                chanStopped = (Bool) TRUE;
            }
#endif
        }

        /*  Enter critical section to protect the submit count                */
        hwiKey = (UInt32) Hwi_disable();

#ifdef Mcasp_LOOPJOB_ENABLED
        if (((Int32) Mcasp_MAXLINKCNT <= chanHandle->submitCount) ||
            ((Bool) TRUE == chanStopped) ||
#else
        /* We now have 3 packets loaded in the EDMA                           */
        if ((((Int32) Mcasp_MAXLINKCNT + 1) <= chanHandle->submitCount) ||
#endif
            ((Bool) TRUE == chanHandle->paused) ||
            (Mcasp_DriverState_PWRM_SUSPEND == instHandle->devState))
        {
            /* Already enough requests are in active queue.Hence load in to   *
             * the pending queue                                              */
            chanHandle->submitCount++;
            ioPacketVoidTempPtr = (Void *) ioPacket;
            Queue_put(Queue_handle(
                          &(chanHandle->queueReqList)),
                      (Queue_Elem *) ioPacketVoidTempPtr);

            /* restore the interrupts                                         */
            Hwi_restore(hwiKey);
        }
        else
        {
            /* Process this packet immediately as active queue is empty       */
            chanHandle->submitCount++;
            ioPacketVoidTempPtr = (Void *) ioPacket;
            Queue_put(Queue_handle(
                          &(chanHandle->queueFloatingList)),
                      (Queue_Elem *) ioPacketVoidTempPtr);

            /* restore the interrupts                                         */
            Hwi_restore(hwiKey);

            /* load this request in to the EDMA paramsets                     */
            Mcasp_localLoadPktToEdma(chanHandle, ioPacket);
        }
        /* return the status as pending as the packet will complete later     */
        status = IOM_PENDING;
    }
    while (falsewhile);
    return status;
}

/**
 * \fn      static Void mcaspIsrSwiFxn()
 *
 * \brief   Swi thread which handles the Mcasp module interrupts
 *
 * \param   arg0  [IN]  The pointer to the ISR object holds instance pointer.
 * \param   arg1  [IN]  unused argument
 *
 * \return  None
 *
 * \enter   arg0    is a valid non NULL pointer.
 *
 * \leave   Not implemented
 */
static Void Mcasp_localIsrSwiFxn(UArg arg0, UArg arg1)
{
    UInt32        count      = 0;
    Mcasp_Object *instHandle = NULL;

    /* To remove the compiler warning                                         */
    arg0 = arg0;
    arg1 = arg1;

    /* An interrupt has occured and it could be because of any one of the     *
     * mcasp instances and also either a TX or RX section interrupt.Hence we  *
     * will check all the instances to find which interrupt has occured. Also *
     * note that here we are only intrested in logging the interrupts for the *
     * error conditions only                                                  */

    /* we are only checking the instances which are currently active          */
    for (count = (UInt32) 0; count < CSL_MCASP_PER_CNT; count++)
    {
        /* check if the instance has registered for interrupts                */
        if (((Bool) TRUE == Mcasp_module.isrObject[count].isIsrRegistered[0])
            && ((Bool) TRUE == Mcasp_module.isrObject[count].isIsrRegistered[1])
            && (NULL != Mcasp_module.isrObject[count].instHandle))
        {
            instHandle = Mcasp_module.isrObject[count].instHandle;
            assert(NULL != instHandle);

            /* check if the RX channel has registered the interrupts          */
            if ((Bool) TRUE == Mcasp_module.isrObject[count].chanEnabled[0])
            {
                /* check if atleast one error has occured                     */
                if (Mcasp_RSTAT_ERROR ==
                    ((UInt32) Mcasp_RSTAT_ERROR &
                     (McASPRxStatusGet(instHandle->hwInfo.regs))))
                {
                    mcaspIsrInput((UArg) & (instHandle->RcvObj));
                }
            }

            /* check if the TX channel has registered the interrupts          */
            if ((Bool) TRUE == Mcasp_module.isrObject[count].chanEnabled[1])
            {
                if (Mcasp_XSTAT_ERROR ==
                    ((UInt32) Mcasp_XSTAT_ERROR &
                     (McASPTxStatusGet(instHandle->hwInfo.regs))))
                {
                    mcaspIsrOutput((UArg) & (instHandle->XmtObj));
                }
            }
        }
    }
}

/**
 * \fn      static Void mcaspIsr()
 *
 * \brief   This function is the interrupt service routine for the mcasp driver.
 *
 * \param   arg  [IN]  The instance number of the first instance to register
 *                     the ISR.
 *
 * \return  None
 *
 * \enter   arg     is a valid non null pointer
 *
 * \leave   Not implemented
 */
Void mcaspIsr(UArg arg)
{
    /* we have got the interrupt for the Mcasp. we need to check which        *
     * instance has generated this interrupt and which section TX or RX. We   *
     * defer the procesing to the Swi thread for the mcasp driver             */

    /* Trigger the SWI thread to handle the interrupts                        *
     * Note : The "arg" here is the instance number of the instance which has *
     * first registered the isr. please note that any valid instance is OK as *
     * all the instances have the same SWI task handle.                       */
    Swi_post((Swi_Handle) arg);
}

/**
 *  \brief   This function is a ISR function.it will be called when Mcasp
 *           receive interrupt is triggered.
 *
 *  \param   chanp   [IN]  Handle to the mcasp channel
 *
 *  \return  None
 *
 *  \enter   chanp       is a valid non null pointer
 *
 *  \leave   Not implemented
 */
Void mcaspIsrInput(UArg chanp)
{
    Mcasp_Object       *instHandle = NULL;
    Mcasp_ChannelHandle chanHandle = NULL;
    Bool falsewhile = (Bool) TRUE;
    Int32 status    = IOM_COMPLETED;
    /*    UInt32                rmod       = 0; */
    UInt32 dlbMode = 0;
    EDMA3_DRV_PaRAMRegs pramTbl    = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    Mcasp_errCbStatus   errStatuts =
    {FALSE, FALSE, FALSE, FALSE, IOM_COMPLETED};

    do
    {
        assert((UArg) NULL != chanp);

        falsewhile = (Bool) FALSE;

        chanHandle = (Mcasp_ChannelHandle) chanp;
        assert(NULL != chanHandle);
        assert(NULL != chanHandle->devHandle);
        instHandle = (Mcasp_Object *) chanHandle->devHandle;
        assert(NULL != instHandle);

        /* Interrupt handling starts                                          */

        /* The driver is in DMA mode and it is enough if we handle errors     */

        /* Read interrupt-status register.                                    */
        chanHandle->intStatus = (UInt32) McASPRxStatusGet(
            instHandle->hwInfo.regs);

        /*Interrupt status word to be written back to reset status bits       */
        McASPRxStatusSet(instHandle->hwInfo.regs,
                         chanHandle->intStatus);

        /* for bursmode of operation frame sync error has to ignored to       *
         * indentify that we do the following                                 */
        /* rmod = (UInt32)((McASPTxRxFrameSyncRead(
         *               instHandle->hwInfo.regs, RX)) &
         *               MCASP_RXFMCTL_RMOD_MASK); */
        /* The above is checked using fsMode. Check line - 1565 similar coding
         * is done */

        do
        {
            falsewhile = (Bool) FALSE;

            if ((Mcasp_DMAERR == (Mcasp_DMAERR & chanHandle->intStatus)))
            {
                status = IOM_EBADIO;
                errStatuts.isDMAErr = (Bool) TRUE;
            }

            if ((Mcasp_RCV_OVERRUN ==
                 (Mcasp_RCV_OVERRUN & chanHandle->intStatus)) &&
                (IOM_COMPLETED == status))
            {
                status = IOM_EBADIO;
                errStatuts.isRcvOvrRunOrTxUndRunErr = (Bool) TRUE;
            }

            if ((Mcasp_RX_CLK_FAIL ==
                 (Mcasp_RX_CLK_FAIL & McASPRxIntrStatusGet(
                      instHandle->hwInfo.regs))) && (IOM_COMPLETED == status))
            {
                if (Mcasp_RX_CLK_FAIL ==
                    (Mcasp_RX_CLK_FAIL & chanHandle->intStatus))
                {
                    status = IOM_EBADIO;
                    errStatuts.isClkFailErr = (Bool) TRUE;
                }
            }
            /* no sync error check for burst mode                             */

            if (((UInt32) 0 !=
                 ((instHandle->mcaspHwSetup.rx.frSyncCtl &
                   (UInt32) MCASP_RXFMCTL_RMOD_MASK) >>
                  MCASP_RXFMCTL_RMOD_SHIFT)) && (IOM_COMPLETED == status))
            {
                if ((Mcasp_SYNCERR ==
                     (Mcasp_SYNCERR & chanHandle->intStatus)))
                {
                    status = IOM_ETIMEOUT;
                    errStatuts.isClkFailErr = (Bool) TRUE;
                }
            }
        }
        while (falsewhile);

        /* Update the error code which will be used by the application to
         * recover from the error
         */
        errStatuts.retVal = (Int32) status;

        if (IOM_COMPLETED != status)
        {
            /* call the application registered callback if any                */
            if (NULL != (chanHandle->gblErrCbk))
            {
                (chanHandle->gblErrCbk)(errStatuts);
            }

            /* For sync error we call the application callback and we         *
             * abort all other pending IOPs also                              */
            if (IOM_ETIMEOUT == status)
            {
                /* While aborting care should be taken about DLB mode         *
                 * otherwise aborting packets in only one direction will      *
                 * make the packet in other direction not to return           */
                dlbMode = McASPDlbRegRead(instHandle->hwInfo.regs);

                if ((UInt32) MCASP_LBCTL_DLBEN_ENABLE == dlbMode)
                {
                    status = Mcasp_localAbortReset(&(instHandle->RcvObj));

                    if (IOM_COMPLETED == status)
                    {
                        status = Mcasp_localAbortReset(&(instHandle->XmtObj));
                    }
                }
                else
                {
                    status = Mcasp_localAbortReset(chanHandle);
                }
                break;
            }

            /* if the error is a non- framesync error - we just send error    *
             * status for the current packet in the callback function and     *
             * continue with other packets for xfer                           */
            if (IOM_ETIMEOUT != status)
            {
                /* Disable Serializer, State machine and Frame sync of RCV    *
                 * Section. Also Disable EDMA Transfer.                       */
                Mcasp_localSmReset(chanHandle);

                /* Initiate dummy transfer (or reduce the c-count to 1) in    *
                 * EDMA-current transfer channel param This would load the    *
                 * next link paramset and give a edma callback where we       *
                 * do futher steps needed to close the current packet and     *
                 * load next pending packet etc                               */

                /* get the param table information of transfer channel        */
                EDMA3_DRV_getPaRAM(
                    (EDMA3_DRV_Handle) chanHandle->edmaHandle,
                    chanHandle->xferChan,
                    &pramTbl);

                if (0 != pramTbl.cCnt)
                {
                    pramTbl.cCnt = 0;

                    EDMA3_DRV_setPaRAM(
                        (EDMA3_DRV_Handle) chanHandle->edmaHandle,
                        chanHandle->xferChan,
                        &pramTbl);
                }

                chanHandle->currentPacketErrorStatus = status;

                /* Enable Serializer, State machine and Frame sync of RCV     *
                 * Section.Also Enable EDMA Transfer.                         */
                Mcasp_localSmSet(chanHandle);
            }
            /*for errors except sync errors*/
        }
        /*dma transfer for all errors*/
    }
    while (falsewhile);
}

/**
 *  \brief   This function is the ISR function. This is called when Mcasp0 XMT
 *           interrupt is triggered
 *
 *  \param   chanp  [IN]  pointer.The pointer to the channel handle.
 *
 *  \return  None
 *
 *  \enter   chanp       is a valid non null pointer
 *
 *  \leave   Not implemented
 */
Void mcaspIsrOutput(UArg chanp)
{
    Mcasp_Object       *instHandle = NULL;
    Mcasp_ChannelHandle chanHandle = NULL;
    Bool falsewhile = (Bool) TRUE;
    Int32 status    = IOM_COMPLETED;
    /*    UInt32                  xmod       = 0; */
    UInt32 dlbMode = 0;
    EDMA3_DRV_PaRAMRegs pramTbl    = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    Mcasp_errCbStatus   errStatuts = {FALSE, FALSE, FALSE, FALSE, 0};

    assert((UArg) NULL != chanp);

    do
    {
        falsewhile = (Bool) FALSE;

        chanHandle = (Mcasp_ChannelHandle) chanp;
        assert(NULL != chanHandle);
        assert(NULL != chanHandle->devHandle);
        instHandle = (Mcasp_Object *) chanHandle->devHandle;
        assert(NULL != instHandle);

        /* Interrupt handling starts                                          */

        /*The driver is in DMA mode and we will handle only errors here       */
        status = IOM_COMPLETED;

        /* Read interrupt-status register.                                    */
        chanHandle->intStatus = (UInt32) McASPTxStatusGet(
            instHandle->hwInfo.regs);

        /*Interrupt status word to be written back to reset status bits       */
        McASPTxStatusSet(instHandle->hwInfo.regs,
                         chanHandle->intStatus);

        /* For burst mode of operation frame sync error has to ignored        *
         * to indentify that we do the following                              */
        /* xmod = (UInt32)((McASPTxRxFrameSyncRead(
         *               instHandle->hwInfo.regs, TX)) &
         *               MCASP_TXFMCTL_XMOD_MASK);*/
        /* The above is checked using fsMode. Check line - 1565 similar coding
         * is done */

        do
        {
            falsewhile = (Bool) FALSE;

            if (((Mcasp_DMAERR) == (Mcasp_DMAERR & chanHandle->intStatus)))
            {
                status = IOM_EBADIO;
                errStatuts.isDMAErr = (Bool) TRUE;
            }

            if (((Mcasp_XMT_UNDERRUN) ==
                 (Mcasp_XMT_UNDERRUN & chanHandle->intStatus)) &&
                (IOM_COMPLETED == status))
            {
                status = IOM_EBADIO;
                errStatuts.isRcvOvrRunOrTxUndRunErr = (Bool) TRUE;
            }

            /* check the mcasp clock failure interrupt only if it is enabled  *
             * in interrupt control register                                  */
            if ((Mcasp_TX_CLK_FAIL ==
                 (Mcasp_TX_CLK_FAIL & McASPTxIntrStatusGet(
                      instHandle->hwInfo.regs))) && (IOM_COMPLETED == status))
            {
                if (Mcasp_TX_CLK_FAIL ==
                    (Mcasp_TX_CLK_FAIL & chanHandle->intStatus))
                {
                    status = IOM_EBADIO;
                    errStatuts.isClkFailErr = (Bool) TRUE;
                }
            }

            /* no sync error check for burst mode                             */

            if (((UInt32) 0 !=
                 ((instHandle->mcaspHwSetup.tx.frSyncCtl &
                   (UInt32) MCASP_TXFMCTL_XMOD_MASK) >>
                  MCASP_TXFMCTL_XMOD_SHIFT)) && (IOM_COMPLETED == status))
            {
                if ((Mcasp_SYNCERR ==
                     (Mcasp_SYNCERR & chanHandle->intStatus)))
                {
                    status = IOM_ETIMEOUT;
                    errStatuts.isSyncErr = (Bool) TRUE;
                }
            }
        }
        while (falsewhile);

        /* Update the error code which will be used by the application to
         * recover from the error
         */
        errStatuts.retVal = (Int32) status;

        if (IOM_COMPLETED != status)
        {
            /* call the application registered callback if any                */
            if (NULL != (chanHandle->gblErrCbk))
            {
                (chanHandle->gblErrCbk)(errStatuts);
            }

            /* at this point we will decide whether to continue other         *
             * pending IOPs  or abort - it depends on error                   */
            /* For sync error we call the application callback and we         *
             * abort all other pending IOPs also                              */
            if (IOM_ETIMEOUT == status)
            {
                /* While aborting care should be taken about DLB mode         *
                 * otherwise aborting packets in only one direction will      *
                 * make the packet in other direction not to return           */
                dlbMode = McASPDlbRegRead(instHandle->hwInfo.regs);

                if (MCASP_LBCTL_DLBEN_ENABLE == dlbMode)
                {
                    status = Mcasp_localAbortReset(&(instHandle->RcvObj));
                    if (IOM_COMPLETED == status)
                    {
                        Mcasp_localAbortReset(&(instHandle->XmtObj));
                    }
                }
                else
                {
                    status = Mcasp_localAbortReset(chanHandle);
                }
                break;
            }

            /* if the error is a non- framesync error - we just send error    *
             * status for the current packet in the callback function and     *
             * continue with other packets for xfer                           */
            if (IOM_ETIMEOUT != status)
            {
                /* Disable Serializer, State machine and Frame sync of RCV    *
                 * Section.Also Disable EDMA Transfer.                        */
                Mcasp_localSmReset(chanHandle);

                /* Initiate dummy transfer (or reduce the c-count to 1) in    *
                 * EDMA-current transfer channel param This would load the    *
                 * next link paramset and give a edma callback where we       *
                 * do futher steps needed to close the current packet and     *
                 * load next pending packet etc                               */

                /* get the param table information of transfer channel        */
                EDMA3_DRV_getPaRAM(
                    (EDMA3_DRV_Handle) chanHandle->edmaHandle,
                    chanHandle->xferChan,
                    &pramTbl);

                if (1 != pramTbl.cCnt)
                {
                    pramTbl.cCnt = 1;

                    EDMA3_DRV_setPaRAM(
                        (EDMA3_DRV_Handle) chanHandle->edmaHandle,
                        chanHandle->xferChan,
                        &pramTbl);
                }

                /* When an underrun occurs we reset the MCASP and restart the
                 * the transfers. In case FIFO is used, MCASP expects the FIFO
                 * to be at threshold level before starting it. So we do a manul
                 * trigger to fill the FIFO and avoid next underrun, if this is
                 * not done we will never be able to come out of underrun
                 * scenario. */
                EDMA3_DRV_enableTransfer(
                    (EDMA3_DRV_Handle) chanHandle->edmaHandle,
                    (UInt32) chanHandle->xferChan,
                    EDMA3_DRV_TRIG_MODE_MANUAL);

                chanHandle->currentPacketErrorStatus = status;

                /* Enable Serializer, State machine and Frame sync of RCV     *
                 * Section. Also Enable EDMA Transfer.                        */
                Mcasp_localSmSet(chanHandle);
            }
            /*for errors except sync errors*/
        }
        /*dma transfer for all errors*/
    }
    while (falsewhile);
}

/**
 *  \brief    This function sets the GBLCTLR bit and wait and check that bit is
 *            set or not
 *
 *  \param    instHandle  [IN]  pointer to the mcasp instance object
 *  \param    bitMaskVal  [IN]  mask bit value
 *
 *  \return   None
 *
 *  \enter   hMcasp      is a valid non null pointer
 *           bitMaskVal  is a valid value
 *
 *  \leave   Not implemented
 */
static Void mcaspBitSetGblRCtl(const Mcasp_Object *instHandle,
                               UInt32              bitMaskVal)
{
    UInt32 timeout  = MCASP_GBLCTL_TIMEOUT;
    Bool   isTask   = (Bool) FALSE;
    UInt32 tempVal1 = 0x00;
    UInt32 tempVal2 = 0x00;

    assert(NULL != instHandle);

    tempVal1 = McASPGlobalCtlGet(instHandle->hwInfo.regs);
    tempVal2 = McASPRxGlobalCtlGet(instHandle->hwInfo.regs);

    /* If already this bit is set then don't set again                        */
    if ((tempVal1 & bitMaskVal) != bitMaskVal)
    {
        if (FALSE == instHandle->RcvObj.isDmaDriven)
        {
            Mcasp_disableInterrupt(instHandle->RcvObj.cpuEventNum);
        }

        tempVal2 |= bitMaskVal;
        McASPRxGlobalCtlSet(instHandle->hwInfo.regs, tempVal2);
        tempVal1 = McASPGlobalCtlGet(instHandle->hwInfo.regs);

        while (((tempVal1 & bitMaskVal) !=
                bitMaskVal) && (timeout > 0U))
        {
            /* decrement the timeout count                                    */
            timeout--;

            isTask = (Bool) (BIOS_getThreadType() == BIOS_ThreadType_Task);

            /* wait for 1 tick only if called from a task context             */
            if ((Bool) TRUE == isTask)
            {
                Task_sleep((UInt32) 1);
            }
            tempVal1 = McASPGlobalCtlGet(instHandle->hwInfo.regs);
        }

        assert(0U != timeout);

        if ((Bool) FALSE == instHandle->RcvObj.isDmaDriven)
        {
            /* Leave critical section */
            Mcasp_enableInterrupt(instHandle->RcvObj.cpuEventNum);
        }
    }
}

/**
 *  \brief   This function removes the GBLCTLR bit and wait and checks that
 *           bit is set or not
 *
 *  \param   instHandle  [IN]  pointer to the mcasp instance object
 *  \param   bitMaskVal  [IN]  mask bit value
 *
 *  \return  None
 *
 *  \enter   hMcasp      is a valid non null pointer
 *           bitMaskVal  is a valid value
 *
 *  \leave   Not implemented
 */
static Void mcaspBitRemoveGblRCtl(const Mcasp_Object *instHandle,
                                  UInt32              bitMaskVal)
{
    UInt32 temp_bitMaskVal = 0U;
    UInt32 timeout         = MCASP_GBLCTL_TIMEOUT;
    Bool   isTask          = (Bool) FALSE;
    UInt32 tempVal1        = 0U;
    UInt32 tempVal2        = 0U;

    temp_bitMaskVal = (0xFFFFFFFFU & (UInt32) bitMaskVal);

    assert(NULL != instHandle);

    tempVal1 = McASPGlobalCtlGet(instHandle->hwInfo.regs);
    tempVal2 = McASPRxGlobalCtlGet(instHandle->hwInfo.regs);

    /* If already this bit is set then don't set again                        */
    if ((tempVal1 & ~temp_bitMaskVal)
        == ((UInt32) 0x0000FFFFU & ~temp_bitMaskVal))
    {
        tempVal2 &= (0xFFFF0000U | temp_bitMaskVal);
        McASPRxGlobalCtlSet(instHandle->hwInfo.regs, tempVal2);
        tempVal1 = McASPGlobalCtlGet(instHandle->hwInfo.regs);

        while (((tempVal1 & ~temp_bitMaskVal) ==
                ((UInt32) 0x0000FFFFU & ~temp_bitMaskVal)) &&
               (timeout > (UInt32) 0U))
        {
            /* decrement the timeout count                                    */
            timeout--;

            isTask = (Bool) (BIOS_getThreadType() == BIOS_ThreadType_Task);

            /* wait for 1 tick only if called from a task context             */
            if ((Bool) TRUE == isTask)
            {
                Task_sleep((UInt32) 1);
            }
            tempVal1 = McASPGlobalCtlGet(instHandle->hwInfo.regs);
        }
        assert(0U != timeout);
    }
}

/**
 *  \brief   This function sets the GBLCTLX bit and wait and check that bit is
 *           set or not
 *
 *  \param   instHandle  [IN]  pointer to the mcasp instance object
 *  \param   bitMaskVal  [IN]  mask bit value
 *
 *  \return  None
 *
 *  \enter   hMcasp      is a valid non null pointer
 *           bitMaskVal  is a valid value
 *
 *  \leave   Not implemented
 */
static Void mcaspBitSetGblXCtl(const Mcasp_Object *instHandle,
                               UInt32              bitMaskVal)
{
    UInt32 timeout  = (UInt32) 3000U;
    Bool   isTask   = (Bool) FALSE;
    UInt32 tempVal1 = (UInt32) 0x00U;
    UInt32 tempVal2 = (UInt32) 0x00U;

    tempVal1 = McASPGlobalCtlGet(instHandle->hwInfo.regs);
    tempVal2 = McASPTxGlobalCtlGet(instHandle->hwInfo.regs);

    assert(NULL != instHandle);

    if ((tempVal1 & bitMaskVal) != bitMaskVal)
    {
        if ((Bool) FALSE == instHandle->XmtObj.isDmaDriven)
        {
            Mcasp_disableInterrupt(instHandle->XmtObj.cpuEventNum);
        }
        tempVal2 |= bitMaskVal;

        McASPTxGlobalCtlSet(instHandle->hwInfo.regs, tempVal2);

        tempVal1 = McASPGlobalCtlGet(instHandle->hwInfo.regs);

        while (((tempVal1 & bitMaskVal) !=
                bitMaskVal) && (timeout > 0))
        {
            timeout--;
            isTask = (Bool) (BIOS_getThreadType() == BIOS_ThreadType_Task);
            if ((Bool) TRUE == isTask)
            {
                Task_sleep((UInt32) 1);
            }
            tempVal1 = McASPGlobalCtlGet(instHandle->hwInfo.regs);
        }
        assert(0U != timeout);
        if ((Bool) FALSE == instHandle->XmtObj.isDmaDriven)
        {
            Mcasp_enableInterrupt(instHandle->XmtObj.cpuEventNum);
        }
    }
}

/**
 *  \brief  This function removes the GBLCTLX bit and wait and checks that bit
 *          is set or not.
 *
 *  \param  instHandle  [IN]  pointer to the mcasp instance object
 *  \param  bitMaskVal  [IN]  mask bit value
 *
 *  \return None
 *
 *  \enter   hMcasp      is a valid non null pointer
 *           bitMaskVal  is a valid value
 *
 *  \leave   Not implemented
 */
static Void mcaspBitRemoveGblXCtl(const Mcasp_Object *instHandle,
                                  UInt32              bitMaskVal)
{
    volatile UInt32 temp_bitMaskVal  = 0U;
    volatile UInt32 temp_bitMaskVal2 = 0U;
    UInt32          timeout          = MCASP_GBLCTL_TIMEOUT;
    Bool isTask = (Bool) FALSE;
    UInt32          tempVal1 = 0U;
    UInt32          tempVal2 = 0U;

    tempVal1 = McASPGlobalCtlGet(instHandle->hwInfo.regs);
    tempVal2 = McASPTxGlobalCtlGet(instHandle->hwInfo.regs);

    temp_bitMaskVal = (0xFFFFFFFFU & (UInt32) bitMaskVal);

    assert(NULL != instHandle);
    temp_bitMaskVal2 = (UInt32) 0x0000FFFFU & ~temp_bitMaskVal;
    if ((tempVal1 & ~temp_bitMaskVal) == temp_bitMaskVal2)
    {
        tempVal2  = McASPTxGlobalCtlGet(instHandle->hwInfo.regs);
        tempVal2 &= (UInt32) (0xFFFF0000U | temp_bitMaskVal);
        McASPTxGlobalCtlSet(instHandle->hwInfo.regs, tempVal2);

        tempVal1 = McASPGlobalCtlGet(instHandle->hwInfo.regs);

        while (((tempVal1 & ~temp_bitMaskVal) == temp_bitMaskVal2)
               && (timeout > 0))
        {
            timeout--;
            isTask = (Bool) (BIOS_getThreadType() == BIOS_ThreadType_Task);
            if ((Bool) TRUE == isTask)
            {
                Task_sleep((UInt32) 1);
            }
            tempVal1 = McASPGlobalCtlGet(instHandle->hwInfo.regs);
        }
        assert(0U != timeout);
    }
}

/*
 *  This function configures the required serializer to transmit mode.
 *
 * \param    hMcasp   [IN]  pointer to the Mcasp Hardware information structure
 * \param    serNum   [IN]  serializer number to configure
 * \param    eb       [OUT] pointer to error block
 *
 * \return
 *           IOM_COMPLETED   - Successful completion
 *           IOM_EBADARGS    - Invalid parameters or Invalid handle
 * \enter   hMcasp      is a valid non null pointer
 *          serNum      is a valid value
 * \leave   Not implemented
 */
static Void mcaspSetSerXmt(Mcasp_HwHandle      hMcasp,
                           Mcasp_SerializerNum serNum)
{
    assert(NULL != hMcasp);
    assert((UInt16) serNum < hMcasp->numOfSerializers);

    McASPSerializerTxSet(hMcasp->regs, serNum);

    McASPPinDirOutputSet(hMcasp->regs, ((UInt32) 1U << serNum));
}

/*
 *  This function configures the required serializer to receive mode.
 *
 * \param    hMcasp   [IN]  pointer to the Mcasp Hardware information structure
 * \param    serNum   [IN]  serializer number to configure
 * \param    eb       [OUT] pointer to error block
 *
 * \return  None
 *
 * \enter   hMcasp      is a valid non null pointer
 *          ditFlag     is a valid value
 * \leave   Not implemented
 */

static Void mcaspSetSerRcv(Mcasp_HwHandle      hMcasp,
                           Mcasp_SerializerNum serNum)
{
    assert(NULL != hMcasp);
    assert((UInt16) serNum < hMcasp->numOfSerializers);

    McASPSerializerRxSet(hMcasp->regs, serNum);

    McASPPinDirInputSet(hMcasp->regs, ((UInt32) 1U << serNum));
}

/**
 *  \brief    This function enables/disables the DIT mode.
 *
 *  \param    hMcasp      [IN]     Handle to the McASP hardware info structure
 *  \param    ditFlag     [IN]     Value to loaded into the DITCTL register
 *  \param    eb          [OUT] Pointer to the error block
 *
 *  \return
 *           IOM_COMPLETED   - Successful completion
 *           IOM_EBADARGS    - Invalid parameters or Invalid handle
 *
 *  \enter   hMcasp      is a valid non null pointer
 *           ditFlag     is a valid value
 *  \leave   Not implemented
 */

static Int32 mcaspSetDitMode(Mcasp_HwHandle hMcasp,
                             Bool           ditFlag)
{
    Int32  status  = IOM_COMPLETED;
    UInt32 tempVal = 0x0;

    assert(NULL != hMcasp);

    if ((Bool) TRUE == hMcasp->ditStatus)
    {
        tempVal = McASPGlobalCtlGet(hMcasp->regs);

        /* Reset XSMRST and XFRST in GBLCTL */
        tempVal &= ~MCASP_GBLCTL_XSMRST_MASK;
        McASPGlobalCtlSet(hMcasp->regs, tempVal);

        tempVal &= ~MCASP_GBLCTL_XFRST_MASK;
        McASPGlobalCtlSet(hMcasp->regs,
                          (UInt32) MCASP_GBLCTL_XFRST_RESET);

        /* Configure DITEN bit of DITCTL    */
        McASPDITModeCtlWrite(hMcasp->regs,
                             ((UInt32) ditFlag << MCASP_TXDITCTL_DITEN_SHIFT));
    }
    return (status);
}

/**
 *  \brief    This function registers the interrupt handler for the given
 *            channel.
 *
 *  \param    chanp        [IN]    Pointer to channel object
 *  \param    instNum      [IN]    instance number
 *  \param    evt          [IN]    event number
 *  \param    intIsr       [IN]    function pointer
 *  \param    eb           [OUT]   pointer to error block
 *
 *  \return   If success return IOM_COMPLETED else error code is
 *            returned
 *
 *  \enter   chanp       is a valid non null pointer
 *           instNum     is a valid value
 *           evt         is a valid value
 *           intIsr      is a valid non null pointer
 *
 *  \leave   Not implemented
 *
 */
static Void mcaspRegisterInt(Ptr    chanp,
                             UInt32 instNum,
                             UInt16 evt,
                             Ptr    intIsr)
{
    Mcasp_ChannelHandle chanHandle = NULL;
    Uns hwiKey = 0;
    Mcasp_Object       *instHandle = NULL;
    UArg   arg;
    UInt32 tempCastFuncPtr;
    Int32  retVal = IOM_COMPLETED;

    assert(NULL != chanp);
    assert(NULL != intIsr);
    /* get the handle to the channel to register the interrupt                */
    chanHandle = (Mcasp_ChannelHandle) chanp;

    assert(NULL != chanHandle);
    assert(NULL != chanHandle->devHandle);
    instHandle = (Mcasp_Object *) chanHandle->devHandle;
    assert(NULL != instHandle);
    if ((IOM_INPUT != chanHandle->mode) && (IOM_OUTPUT != chanHandle->mode))
    {
        retVal = IOM_EBADARGS;
    }
    if (CSL_MCASP_PER_CNT <= instNum)
    {
        retVal = IOM_EBADARGS;
    }
    if (IOM_COMPLETED == retVal)
    {
        hwiKey = (UInt32) Hwi_disable();

        /* set the variable to indicate that this channel has registered
         *          *
         * interrupts
         *                                                            */
        Mcasp_module.isrObject[instNum].chanEnabled[chanHandle->mode -
                                                    1] = (Bool) TRUE;

        /* update the information of the instance which is registering the ISR
         *   */
        if ((Bool) FALSE ==
            Mcasp_module.isrObject[instNum].isIsrRegistered[chanHandle->mode -
                                                            1])
        {
            Mcasp_module.isrObject[instNum].isIsrRegistered[chanHandle->mode -
                                                            1] = (Bool) TRUE;
            Mcasp_module.isrObject[instNum].instHandle         = instHandle;
        }
        else
        {
            /* interrupt handler is already plugged in for this instance
             *         */
        }

        arg = (UArg) Mcasp_module.isrObject[instNum].isrSwiTaskHandle;

        /* Enabling the the interrupt
         *                                        */
        tempCastFuncPtr = (UInt32) intIsr;

#ifdef BUILD_DSP
        EventCombiner_dispatchPlug((UInt32) evt,
                                   (EventCombiner_FuncPtr) tempCastFuncPtr,
                                   arg,
                                   (Bool) TRUE);

        Hwi_enableIER((Bits16) ((Bits16) 1 << instHandle->hwiNumber));
#else       /* BUILD_M4 */
        gHwiHandle[instNum][chanHandle->mode - 1] =
            BspOsal_registerIntr((UInt32) evt,
                                 (BspOsal_IntrFuncPtr) tempCastFuncPtr,
                                 (void *) arg);

#endif

        /* Enabling the interrupts
         *                                               */
        Hwi_restore(hwiKey);
    }
    else
    {
        assert(FALSE);
    }
}

/**
 *  \brief    unregister interrupt handler for the given channel.
 *
 *  \param    devid        [IN]    instance number
 *  \param    evt          [IN]    interrupt number
 *  \param    mode         [IN]    input or output
 *
 *  \return   Nothing
 *
 *  \enter   Not implemented
 *
 *  \leave   Not implemented
 */
static Void mcaspUnRegisterInt(UInt16 devid, UInt16 evt, Int mode)
{
    UInt32 hwiKey = 0;
    Int32  retVal = IOM_COMPLETED;

    if ((IOM_INPUT != mode) && (IOM_OUTPUT != mode))
    {
        retVal = IOM_EBADARGS;
    }
    if ((UInt16) CSL_MCASP_PER_CNT <= devid)
    {
        retVal = IOM_EBADARGS;
    }
    if (IOM_COMPLETED == retVal)
    {
        /* disable the interrupts before unregistering the interrupts
         *            */
        hwiKey = (UInt32) Hwi_disable();

        /* indicate that the channel has unregisterd the interrupts and is
         * disabled
         *              */
        Mcasp_module.isrObject[devid].chanEnabled[mode - 1]     = (Bool) FALSE;
        Mcasp_module.isrObject[devid].isIsrRegistered[mode - 1] = (Bool) FALSE;
        Mcasp_module.isrObject[devid].instHandle = NULL;

        /* Disable the event now.
         *                                              */
        Mcasp_disableInterrupt((UInt32) evt);

#ifdef BUILD_DSP
        /* Remove EventCombiner function registration */
        EventCombiner_dispatchPlug(evt, EventCombiner_unused, NULL, FALSE);
#else
        /* Delete Hwi handle for the corresponding instance and mode */
        BspOsal_unRegisterIntr(&gHwiHandle[devid][mode - 1]);
#endif

        /* Enabling the interrupts
         *                                               */
        Hwi_restore(hwiKey);
    }
    else
    {
        assert(FALSE);
    }
}

/**
 *  \brief   This function Deactivates the receive section state machine and
 *           the corresponding frame sync.
 *
 *  \param   instHandle  [IN]  pointer to the Mcasp instance object
 *
 *  \return  None
 *
 *  \enter   instHandle  is a valid non null pointer
 *
 *  \leave   Not implemented
 */
Void Mcasp_localDeactivateSmFsForRcv(const Mcasp_Object *instHandle)
{
    assert(NULL != instHandle);

    /*frame sync*/
    mcaspBitRemoveGblRCtl(instHandle, ~MCASP_GBLCTLR_RFRST_MASK);

    /*state m/c*/
    mcaspBitRemoveGblRCtl(instHandle, ~MCASP_GBLCTLR_RSMRST_MASK);

    /*serializer*/
    mcaspBitRemoveGblRCtl(instHandle, ~MCASP_GBLCTLR_RSRCLR_MASK);

    /* Clear interrupts, if any */
    /* Its important to clear the interrupt status register after stopping
     * serializer, Frame Sync generator etc... as an error could be
     * generated. There could error due to the reason that, we have stopped
     * the serializer and at that point, the frame syncs is being generated
     * (in case of a master) */
    McASPRxStatusSet(instHandle->hwInfo.regs,
                     ((UInt32) MCASP_RXSTAT_RERR_MASK |
                      (UInt32) MCASP_RXSTAT_RDMAERR_MASK |
                      (UInt32) MCASP_RXSTAT_RSTAFRM_MASK |
                      (UInt32) MCASP_RXSTAT_RDATA_MASK |
                      (UInt32) MCASP_RXSTAT_RLAST_MASK |
                      (UInt32) MCASP_RX_STAT_CURRSLOT_EVEN |
                      (UInt32) MCASP_RX_STAT_CURRSLOT_ODD |
                      (UInt32) MCASP_RXSTAT_RCKFAIL_MASK |
                      (UInt32) MCASP_RXSTAT_RSYNCERR_MASK |
                      (UInt32) MCASP_RXSTAT_ROVRN_MASK));
}

/**
 *  \brief   This function deactivates the transmit section state machine and
 *           the corresponding frame sync.
 *
 *  \param   instHandle [IN]  Pointer to the mcasp instance object
 *
 *  \return  None
 *
 *  \enter   instHandle  is a valid non null pointer
 *
 *  \leave   Not implemented
 */
Void Mcasp_localDeactivateSmFsForXmt(const Mcasp_Object *instHandle)
{
    assert(NULL != instHandle);

    /*Start the Serializer, State M/C and Frame Sync Generator*/
    mcaspBitRemoveGblXCtl(instHandle, ~MCASP_GBLCTLX_XFRST_MASK);
    mcaspBitRemoveGblXCtl(instHandle, ~MCASP_GBLCTLX_XSMRST_MASK);
    mcaspBitRemoveGblXCtl(instHandle, ~MCASP_GBLCTLX_XSRCLR_MASK);

    /* Clear interrupts if any */
    /* Its important to clear the interrupt status register after stopping
     * serializer, Frame Sync generator etc... as an error could be
     * generated. There could error due to the reason that, we have stopped
     * the serializer and at that point, the frame syncs is being generated
     * (in case of a master) */
    McASPTxStatusSet(instHandle->hwInfo.regs,
                     ((UInt32) MCASP_TX_STAT_ERR |
                      (UInt32) MCASP_TX_STAT_DMAERR |
                      (UInt32) MCASP_TX_STAT_STARTOFFRAME |
                      (UInt32) MCASP_TX_STAT_DATAREADY |
                      (UInt32) MCASP_TX_STAT_LASTSLOT |
                      (UInt32) MCASP_TX_STAT_CURRSLOT_EVEN |
                      (UInt32) MCASP_TX_STAT_CURRSLOT_ODD |
                      (UInt32) MCASP_TXSTAT_XCKFAIL_MASK |
                      (UInt32) MCASP_TX_STAT_SYNCERR |
                      (UInt32) MCASP_TX_STAT_UNDERRUN));
}

/**
 *  \brief  This function checks if the requested serialisers are free or not
 *
 *  \param   instHandle  [IN]  pointer to the Mcasp instance object
 *  \param   chanParams  [IN]  Device parameter structure that supplies
 *                            data to initialize the McASP
 *  \param  eb           [OUT] pointer to the error information block
 *
 *  \return TRUE if all serializers are free (Mcasp_SerializerStatus_FREE)
 *          FALSE if any one of the requested serializer is not free
 *
 *  \enter   instHandle  is a valid non null pointer
 *           params      is a valid non null pointer
 *
 *  \leave   Not implemented
 */
static Bool mcaspIsRequestedSerzsFree(const Mcasp_Object *instHandle,
                                      Ptr                 params)
{
    Mcasp_ChanParams *chanParams = NULL;
    UInt16 count    = 0;
    Bool status     = (Bool) TRUE;
    Bool falsewhile = (Bool) TRUE;

    assert(NULL != instHandle);
    assert(NULL != params);
    do
    {
        falsewhile = (Bool) FALSE;

        chanParams = (Mcasp_ChanParams *) params;

        for (count = 0; count < chanParams->noOfSerRequested; count++)
        {
            /* Get serializer number requested by user                        */
            if (Mcasp_SerializerStatus_FREE !=
                (instHandle->serStatus[chanParams->indexOfSersRequested[count]]))
            {
                status = (Bool) FALSE;
                break;
            }
        }
    }
    while (falsewhile);
    return (status);
}

/**
 *  \brief   This function is used to configure the requested serializers in the
 *           receive mode.
 *
 *  \param    instHandle  [IN]   pointer to the Mcasp instance object
 *  \param    params      [IN]   channel parameters given by user
 *  \param    eb          [OUT]  pointer to the Error infromation block
 *
 *  \return   None
 *
 *  \enter   instHandle  is a valid non null pointer
 *           params      is a valid non null pointer
 *
 *  \leave   Not implemented
 */
static Void mcaspMultiSerInitializationRcv(Mcasp_Object *instHandle,
                                           Ptr           params)
{
    Mcasp_ChanParams   *chanParams = NULL;
    UInt16 count  = 0;
    UInt32 serNum = 0;
    Mcasp_SerializerNum serializerToConfigure = (Mcasp_SerializerNum) 0;

    assert(NULL != instHandle);
    assert(NULL != params);
    chanParams = (Mcasp_ChanParams *) params;

    for (count = (UInt16) 0; count < chanParams->noOfSerRequested; count++)
    {
        /* Get serializer number requested by user                            */
        serNum = (UInt32) chanParams->indexOfSersRequested[count];

        if (Mcasp_SerializerStatus_FREE == instHandle->serStatus[serNum])
        {
            /* Configure requested serialzer as receive mode                  */
            instHandle->serStatus[serNum] = Mcasp_SerializerStatus_RCV;
            serializerToConfigure         = (Mcasp_SerializerNum) serNum;

            mcaspSetSerRcv(&(instHandle->hwInfo), serializerToConfigure);
        }
    }
}

/**
 *  \brief   This function configures the requested serializers in the transmit
 *           mode
 *
 *  \param    instHandle  [IN]   pointer to the Mcasp instance object
 *  \param    params      [IN]   channel parameters given by user
 *  \param    eb          [OUT]  pointer to the Error infromation block
 *
 *  \return   None
 *
 *  \enter   instHandle  is a valid non null pointer
 *          params      is a valid non null pointer
 *
 *  \leave   Not implemented
 */

static Void mcaspMultiSerInitializationXmt(Mcasp_Object *instHandle,
                                           Ptr           params)
{
    Mcasp_ChanParams   *chanParams = NULL;
    UInt32 count  = 0;
    UInt32 serNum = 0;
    Mcasp_SerializerNum serializerToConfigure = (Mcasp_SerializerNum) 0;

    assert(NULL != instHandle);
    assert(NULL != params);
    chanParams = (Mcasp_ChanParams *) params;

    for (count = (UInt32) 0; count < chanParams->noOfSerRequested; count++)
    {
        /* Get serializer number requested by user                            */
        serNum = (UInt32) chanParams->indexOfSersRequested[count];

        if (Mcasp_SerializerStatus_FREE == instHandle->serStatus[serNum])
        {
            /* Configure requested serialzer as transmit mode                 */
            instHandle->serStatus[serNum] = Mcasp_SerializerStatus_XMT;

            serializerToConfigure = (Mcasp_SerializerNum) serNum;

            mcaspSetSerXmt(&(instHandle->hwInfo), serializerToConfigure);
        }
    }
}

/**
 *  \brief   This function restore global serializer state as available
 *           for further use.
 *
 *  \param   chanp  [IN]   Channel handle
 *
 *  \return  None
 *
 *  \enter   chanp       is a valid non null pointer
 *
 *  \leave   Not implemented
 */
static Void mcaspMultiSerGlobalRestore(Ptr chanp)
{
    Mcasp_ChannelHandle chanHandle = NULL;
    Mcasp_Object       *instHandle = NULL;
    UInt16 serNum = 0;

    assert(NULL != chanp);

    chanHandle = (Mcasp_ChannelHandle) chanp;

    assert(NULL != chanHandle->devHandle);

    instHandle = (Mcasp_Object *) chanHandle->devHandle;
    assert(NULL != instHandle);

    for (serNum = 0; serNum < chanHandle->noOfSerAllocated; serNum++)
    {
        instHandle->serStatus[chanHandle->indexOfSersRequested[serNum]] =
            Mcasp_SerializerStatus_FREE;
    }
}

/**
 *  \brief   This function configures the Mcasp transmit sections
 *
 *  \param   instHandle  [IN]   pointer to the Mcasp instance object
 *  \param   params      [IN]   transmit channel parameters
 *  \param   eb          [OUT]  pointer to error block
 *
 *  \return  IOM_COMPLETED If configuration is success
 *           Error code in case of failure.
 *
 *  \enter   instHandle  is a valid non null pointer
 *          params      is a valid non null pointer
 *
 *  \leave   Not implemented
 */
static Int32 mcaspConfigureXmtChannel(Mcasp_Object *instHandle,
                                      Ptr           params)
{
    Mcasp_ChanParams *chanParams = NULL;
    Int32 status     = IOM_COMPLETED;
    Bool  falsewhile = (Bool) TRUE;

    assert(NULL != instHandle);
    assert(NULL != params);
    do
    {
        falsewhile = (Bool) FALSE;

        chanParams = (Mcasp_ChanParams *) params;

        /* before touching McASP registers, place transmit section in reset   */
        status = Mcasp_localResetXmt(&(instHandle->hwInfo));

        if (IOM_COMPLETED == status)
        {
            /* Configure the transmit section of the device: Start transmit high
             *  *
             * clock and clock
             *                                                   */
            status = Mcasp_localConfigXmtSection(
                instHandle,
                chanParams->mcaspSetup);
        }

        /* Set DITEN bit if DIT mode else set to I2S mode.                    */
        if ((MCASP_OPMODE_DIT == chanParams->channelMode) &&
            (IOM_COMPLETED == status))
        {
            /* check hardware supports dit mode or not                        */
            if ((Bool) TRUE == instHandle->hwInfo.ditStatus)
            {
                status = mcaspSetDitMode(
                    &(instHandle->hwInfo),
                    (Bool) chanParams->channelMode);
            }
        }
    }
    while (falsewhile);
    return (status);
}

/**
 *  \brief   This function configures the receive section of the mcasp device.
 *
 *  \param   instHandle  [IN]  pointer to the Mcasp instance object
 *  \param   params      [IN]  receive channel parameters
 *  \param   eb          [OUT] pointer to error block
 *
 *  \return  IOM_COMPLETED in case of success
 *           Error code in case of failure
 *
 *  \enter   instHandle  is a valid non null pointer
 *          params      is a valid non null pointer
 *
 *  \leave   Not implemented
 *
 */

static Int32 mcaspConfigureRcvChannel(Mcasp_Object *instHandle,
                                      Ptr           params)
{
    Mcasp_ChanParams *chanParams = NULL;
    Int32 status    = IOM_COMPLETED;
    Bool falsewhile = (Bool) TRUE;

    assert(NULL != instHandle);
    assert(NULL != params);
    do
    {
        falsewhile = (Bool) FALSE;

        chanParams = (Mcasp_ChanParams *) params;

        /* before touching McASP registers, place receive section in reset    */
        status = Mcasp_localResetRcv(&(instHandle->hwInfo));

        if (IOM_COMPLETED == status)
        {
            /* Configure the receive section of the device: start Receive high
             *    *
             * clock and clock
             *                                                   */
            status = Mcasp_localConfigRcvSection(
                instHandle,
                chanParams->mcaspSetup);
        }
    }
    while (falsewhile);

    return (status);
}

/**
 *  \brief   This function writes to the Channel status RAM (DITCSRA/B0-5)
 *
 *  \param   hMcasp      [IN]     Handle to the McASP instance
 *  \param   chanStatRam [IN]     status to be written
 *  \param   eb          [OUT]    pointer to the error information block
 *
 *  \return
 *           IOM_COMPLETED   - Successful completion of read
 *           IOM_EBADARGS    - Invalid parameters or Invalid handle
 *  \enter   hMcasp      is a valid non null pointer
 *          chanStatRam is a valid non null pointer
 *
 *  \leave   Not implemented
 */

static Int32 mcaspWriteChanStatRam(Mcasp_HwHandle           hMcasp,
                                   const Mcasp_ChStatusRam *chanStatRam)
{
    Int32 status = IOM_COMPLETED;

    assert(NULL != hMcasp);
    assert(NULL != chanStatRam);
    if ((Bool) TRUE == hMcasp->ditStatus)
    {
        /* Configure the DIT left channel status registers                    */

        McASPDITLeftChanStatusSet(
            hMcasp->regs, (UInt32) 0,
            chanStatRam->chStatusLeft[Mcasp_DITRegIndex_0]);

        McASPDITLeftChanStatusSet(
            hMcasp->regs, (UInt32) 1,
            chanStatRam->chStatusLeft[Mcasp_DITRegIndex_1]);

        McASPDITLeftChanStatusSet(
            hMcasp->regs, (UInt32) 2,
            chanStatRam->chStatusLeft[Mcasp_DITRegIndex_2]);

        McASPDITLeftChanStatusSet(
            hMcasp->regs, (UInt32) 3,
            chanStatRam->chStatusLeft[Mcasp_DITRegIndex_3]);

        McASPDITLeftChanStatusSet(
            hMcasp->regs, (UInt32) 4,
            chanStatRam->chStatusLeft[Mcasp_DITRegIndex_4]);

        McASPDITLeftChanStatusSet(
            hMcasp->regs, (UInt32) 5,
            chanStatRam->chStatusLeft[Mcasp_DITRegIndex_5]);

        /* Configure the DIT right channel status registers                   */

        McASPDITRightChanStatusSet(hMcasp->regs, (UInt32) 0,
                                   chanStatRam->chStatusRight[
                                       Mcasp_DITRegIndex_0]);

        McASPDITRightChanStatusSet(hMcasp->regs, (UInt32) 1,
                                   chanStatRam->chStatusRight[
                                       Mcasp_DITRegIndex_1]);

        McASPDITRightChanStatusSet(hMcasp->regs, (UInt32) 2,
                                   chanStatRam->chStatusRight[
                                       Mcasp_DITRegIndex_2]);

        McASPDITRightChanStatusSet(hMcasp->regs, (UInt32) 3,
                                   chanStatRam->chStatusRight[
                                       Mcasp_DITRegIndex_3]);

        McASPDITRightChanStatusSet(hMcasp->regs, (UInt32) 4,
                                   chanStatRam->chStatusRight[
                                       Mcasp_DITRegIndex_4]);

        McASPDITRightChanStatusSet(hMcasp->regs, (UInt32) 5,
                                   chanStatRam->chStatusRight[
                                       Mcasp_DITRegIndex_5]);
    }
    else
    {
        status = IOM_EBADARGS;
    }
    return (status);
}

/**
 *  \brief   This function writes to the User Data RAM (DITUDRA/B0-5)
 *
 *  \param   hMcasp      [IN] pointer to the Mcasp H/W information structure
 *  \param   userDataRam [IN] data to be written
 *
 *  \return
 *           IOM_COMPLETED   - Successful completion of write
 *           IOM_EBADARGS    - Invalid parameters or Invalid handle
 *
 *  \enter   hMcasp      is a valid non null pointer
 *          userDataRam is a valid non null pointer
 *
 *  \leave   Not implemented
 *
 */
static Int32 mcaspWriteUserDataRam(Mcasp_HwHandle           hMcasp,
                                   const Mcasp_UserDataRam *userDataRam)
{
    Int32 status = IOM_COMPLETED;

    assert(NULL != hMcasp);
    assert(NULL != userDataRam);
    if ((Bool) TRUE == hMcasp->ditStatus)
    {
        /* Configure the DIT left user data registers                         */

        McASPDITLeftUserDataRamSet(hMcasp->regs, (UInt32) 0,
                                   userDataRam->userDataLeft[
                                       Mcasp_DITRegIndex_0]);

        McASPDITLeftUserDataRamSet(hMcasp->regs, (UInt32) 1,
                                   userDataRam->userDataLeft[
                                       Mcasp_DITRegIndex_1]);

        McASPDITLeftUserDataRamSet(hMcasp->regs, (UInt32) 2,
                                   userDataRam->userDataLeft[
                                       Mcasp_DITRegIndex_2]);

        McASPDITLeftUserDataRamSet(hMcasp->regs, (UInt32) 3,
                                   userDataRam->userDataLeft[
                                       Mcasp_DITRegIndex_3]);

        McASPDITLeftUserDataRamSet(hMcasp->regs, (UInt32) 4,
                                   userDataRam->userDataLeft[
                                       Mcasp_DITRegIndex_4]);

        McASPDITLeftUserDataRamSet(hMcasp->regs, (UInt32) 5,
                                   userDataRam->userDataLeft[
                                       Mcasp_DITRegIndex_5]);

        /* Configure the DIT right user data registers                        */

        McASPDITRightUserDataRamSet(hMcasp->regs, (UInt32) 0,
                                    userDataRam->userDataRight[
                                        Mcasp_DITRegIndex_0]);

        McASPDITRightUserDataRamSet(hMcasp->regs, (UInt32) 1,
                                    userDataRam->userDataRight[
                                        Mcasp_DITRegIndex_1]);

        McASPDITRightUserDataRamSet(hMcasp->regs, (UInt32) 2,
                                    userDataRam->userDataRight[
                                        Mcasp_DITRegIndex_2]);

        McASPDITRightUserDataRamSet(hMcasp->regs, (UInt32) 3,
                                    userDataRam->userDataRight[
                                        Mcasp_DITRegIndex_3]);

        McASPDITRightUserDataRamSet(hMcasp->regs, (UInt32) 4,
                                    userDataRam->userDataRight[
                                        Mcasp_DITRegIndex_4]);

        McASPDITRightUserDataRamSet(hMcasp->regs, (UInt32) 5,
                                    userDataRam->userDataRight[
                                        Mcasp_DITRegIndex_5]);
    }
    else
    {
        status = IOM_EBADARGS;
    }
    return (status);
}

/**
 *
 * \brief   This function configures the Hardware FIFO
 *
 * \param   hMcasp       [IN] pointer to the Mcasp Hardware information struct
 * \param   chanHandle   [IN] handle to the channel
 * \param   enableHwFifo [IN] hardware FIFO to be enabled or disabled
 *
 * \return  None
 *
 * \enter   hMcasp      is a valid non null pointer
 *          chanHandle  is a valid non null pointer
 *
 * \leave   Not implemented
 *
 */
static Void mcaspConfigureFifo(const Mcasp_HwObj      *hMcasp,
                               const Mcasp_ChannelObj *chanHandle,
                               Bool                    enableHwFifo)

{
    /* validate the input parameters                                          */
    assert(NULL != hMcasp);
    assert(NULL != hMcasp->fifoRegs);
    assert(NULL != chanHandle);
    /* check if the HW FIFO usage is requested by the user for this channel   */
    if ((Bool) TRUE == enableHwFifo)
    {
        if (IOM_INPUT == chanHandle->mode)
        {
            /* configure the receive channel                                  */
            /* Step 1 : configure the "WNUMDMA" and "WNUMEVT" bits before     *
             * enabling the FIFO                                              */
            McASPReadFifoEnable(hMcasp->regs,
                                chanHandle->noOfSerAllocated,
                                chanHandle->noOfSerAllocated);
        }
        else
        {
            /* configure the transmit channel                                 */
            /* Step 1 : configure the "WNUMDMA" and "WNUMEVT" bits before     *
             * enabling the FIFO                                              */
            McASPWriteFifoEnable(hMcasp->regs,
                                 chanHandle->noOfSerAllocated,
                                 chanHandle->noOfSerAllocated);
        }
    }
    else
    {
        /* FIFO needs to be disabled                                          */
        if (IOM_INPUT == chanHandle->mode)
        {
            /* disable the FIFO now by resetting the "WENA" bit               */
            McASPReadFifoDisable(hMcasp->regs);
        }
        else
        {
            /* disable the FIFO now by resetting the "WENA" bit               */
            McASPWriteFifoDisable(hMcasp->regs);
        }
    }
}

/**
 *
 * \brief This function validates the application specified buffer formats and
 *          updates the channel handle with the choosen buffer format.
 *
 * Side effect: This function also update the channel environment variable
 *              "noOfSlots" that would be used to compute the EDMA 3 indices.
 *
 * \param   chanHandle    [IN]    Pointer to channel handle
 * \param   params        [IN]    user supplied channel configurations.
 *
 * \return  DriverTypes_COMPLETED on sucess else an error code is returned
 *
 * \enter   chanHandle     is a valid non null pointer
 *          params         is a valid non null pointer
 *
 * \leave   Not implemented
 */

static Int32  mcaspValidateBufferConfig(Mcasp_ChannelHandle     chanHandle,
                                        const Mcasp_ChanParams *params)
{
    UInt32 tempVar = 0x0;
    Int32  status  = IOM_COMPLETED;

    assert(NULL != params);
    assert(NULL != chanHandle);

    /* get the number of slots to be configured                               */
    tempVar = (((UInt32) 0x0000FF80U) & params->mcaspSetup->frSyncCtl);
    tempVar = tempVar >> 7;

    if (0x01 < params->noOfSerRequested)
    {
        /* multi serializer configuration                                     */
        if (0x01U < tempVar)
        {
            /* multi serialiser multi slot configuration                      */
            if ((MCASP_BUFFERFORMAT_MULTISER_MULTISLOT_SEMI_INTERLEAVED_1
                 != params->dataFormat) &&
                (MCASP_BUFFERFORMAT_MULTISER_MULTISLOT_SEMI_INTERLEAVED_2
                 != params->dataFormat))
            {
                status = IOM_EBADARGS;
            }
        }
        else
        {
            /* Multi serialiser single slot configuration                     */
            if ((MCASP_BUFFERFORMAT_MULTISER_1SLOT_SER_INTERLEAVED
                 != params->dataFormat) &&
                (MCASP_BUFFERFORMAT_MULTISER_1SLOT_SER_NON_INTERLEAVED
                 != params->dataFormat))
            {
                status = IOM_EBADARGS;
            }
        }
    }
    else
    {
        /* single serialiser configuration                                    */
        if (0x01U < tempVar)
        {
            /* single serializer multi slot configuration                     */
            if ((MCASP_BUFFERFORMAT_1SER_MULTISLOT_INTERLEAVED
                 != params->dataFormat) &&
                (MCASP_BUFFERFORMAT_1SER_MULTISLOT_NON_INTERLEAVED
                 != params->dataFormat))
            {
                status = IOM_EBADARGS;
            }
        }
        else
        {
            /* single slot configuration                                      */
            if (MCASP_BUFFERFORMAT_1SER_1SLOT != params->dataFormat)
            {
                status = IOM_EBADARGS;
            }
        }
    }

    /* update the number of slots in to the channel structure                 */
    chanHandle->noOfSlots = (UInt16) params->noOfChannels;

    if (IOM_COMPLETED == status)
    {
        /* copy the data format to the channel structure                      */
        chanHandle->dataFormat = params->dataFormat;
    }
    return status;
}

/*
 *  \brief  This function toggles the index of the edma params
 *
 *  \param  index [IN]  pointer to current index
 *
 *  \return None
 *
 *  \enter  Not implemented
 *
 *  \leave  Not implemented
 */
Void Mcasp_localGetNextIndex(UInt32 *index)
{
    assert(NULL != index);
    *index = (((*index) + 1U) & 0x01U);
}

/**
 *  \brief  This function loads the packets to the actual EDMA paramset.
 *
 *  \param  chanHandle [IN]  Handle to channel.
 *  \param  ioPacket   [IN]  pointer to the ioPacket
 *
 *  \return None
 *
 *  \enter  Not implemented
 *
 *  \leave  Not implemented
 */

Void Mcasp_localLoadPktToEdma(Mcasp_ChannelObj *chanHandle,
                              const IOM_Packet *ioPacket)
{
    Mcasp_Object         *instHandle = NULL;
    Mcasp_PktAddrPayload *payLoad    = NULL;
    Int32 status    = IOM_COMPLETED;
    Bool falseWhile = (Bool) TRUE;
    UInt32 hwiKey   = 0;
#ifndef Mcasp_LOOPJOB_ENABLED
    UInt32 dlbMode = 0;
    EDMA3_DRV_TrigMode    trigMode = EDMA3_DRV_TRIG_MODE_EVENT;
#endif

    assert(NULL != chanHandle);
    assert(NULL != ioPacket);

    instHandle = (Mcasp_Object *) chanHandle->devHandle;
    assert(NULL != instHandle);

    do
    {
        falseWhile = (Bool) FALSE;

        if ((Bool) TRUE == instHandle->isDataBufferPayloadStructure)
        {
            payLoad = (Mcasp_PktAddrPayload *) ioPacket->addr;
            assert(NULL != payLoad);
        }

        /* For a DIT  request,  channel has to be programmed with its contents*
         * (DIT RAM registers also if this is an xmt channel in DIT mode).    */
        if (Mcasp_ChanMode_RCV != chanHandle->channelOpMode)
        {
            if ((Mcasp_ChanMode_XMT_DIT == chanHandle->channelOpMode)
                && ((Bool) TRUE == instHandle->isDataBufferPayloadStructure)
                && ((Bool) TRUE == payLoad->writeDitParams))
            {
                /* DIT Mode: Write to the Channel Status RAM and User Data RAM*/
                status = mcaspWriteChanStatRam(
                    &(instHandle->hwInfo),
                    payLoad->chStat);
                if (IOM_COMPLETED != status)
                {
                    status = IOM_ABORTED;
                }
                else
                {
                    status = mcaspWriteUserDataRam(
                        &(instHandle->hwInfo),
                        payLoad->userData);
                }
                if (IOM_COMPLETED != status)
                {
                    status = IOM_ABORTED;
                }
            }
        }
        if (IOM_COMPLETED == status)
        {
            chanHandle->currentDataSize    = (UInt16) ioPacket->size;
            chanHandle->userDataBufferSize = (UInt32) ioPacket->size;

            /* for DMA mode we will not use chanHandle->dataPacket to hold
             *        *
             * current packet - we use floatingqueue
             *                             */
            chanHandle->dataPacket = NULL;

            /*  Enter critical section to protect the submit count
             *               */
            hwiKey = (UInt32) Hwi_disable();

#ifdef Mcasp_LOOPJOB_ENABLED
            if (2U == chanHandle->submitCount)
#else
            /* The second and the third packet will go the link paramsets
             *        */
            if (2U <= chanHandle->submitCount)
#endif
            {
                chanHandle->loopjobUpdatedinParamset = (Bool) FALSE;
                Mcasp_localGetNextIndex(
                    &chanHandle->nextLinkParamSetToBeUpdated);
            }

            status = Mcasp_localUpdtDtPktToLnkPrms(chanHandle, ioPacket);
        }
        if (IOM_COMPLETED != status)
        {
            status = IOM_EBADIO;

            /*  Enter critical section to protect the submit count            */
            Hwi_restore(hwiKey);
        }

        if ((1U == chanHandle->submitCount) && (IOM_COMPLETED == status))
        {
            /* First packet is being submitted in case of loop job        *
             * mode this will ne loaded in to the link paramset else      *
             * in case of the non loop job this will go in to the main    *
             * channel                                                    */
#ifdef Mcasp_LOOPJOB_ENABLED
            /* if at all this is the very first packet, then one param    *
             * set has loop job loaded , self linked and active with      *
             * the main xfer channel param. other param set is ready      *
             * loaded (just now and has link paramater set as the one     *
             * having loopjob (this is to ensure that if at all we are    *
             * not getting any more packets loopjob be will taken         *
             * over). Now we have to link the floating / newly loaded     *
             * param set to xfer channel.                                 */
            status = EDMA3_DRV_linkChannel(
                chanHandle->edmaHandle,
                chanHandle->xferChan,
                chanHandle->pramTbl \
                [chanHandle->nextLinkParamSetToBeUpdated]);

            if (IOM_COMPLETED != status)
            {
                status = IOM_EBADIO;
                /*  exit critical section to protect the submit count     */
                Hwi_restore(hwiKey);
            }
#endif
            if (IOM_COMPLETED == status)
            {
                Hwi_restore(hwiKey);

#ifndef Mcasp_LOOPJOB_ENABLED
                chanHandle->nextLinkParamSetToBeUpdated = 0;

                /* configure the FIFO for the specific channel
                 *                   */
                if ((Bool) TRUE == chanHandle->enableHwFifo)
                {
                    /* disable and enable the FIFO to clear any data in the FIFO
                     * */
                    mcaspConfigureFifo(&instHandle->hwInfo, chanHandle, FALSE);
                    mcaspConfigureFifo(&instHandle->hwInfo, chanHandle,
                                       (Bool) TRUE);
                }

                /* This is the first packet. we would have update the main
                 * params with the ioPacket. we will now just start the
                 * transfer so that the packet is transferred
                 */
                EDMA3_DRV_enableTransfer(
                    chanHandle->edmaHandle,
                    chanHandle->xferChan,
                    trigMode);

                /*  update the State m/c stop status
                 */
                instHandle->stopSmFsXmt = FALSE;
                instHandle->stopSmFsRcv = (Bool) FALSE;

                /* if DLB mode is set then Enable both state m/c else rcv or xmt
                 * state machine only needs to be enabled
                 */
                dlbMode = McASPDlbRegRead(instHandle->hwInfo.regs);

                if (MCASP_LBCTL_DLBEN_DISABLE == dlbMode)
                {
                    if (IOM_INPUT == chanHandle->mode)
                    {
                        /* Receive channel */
                        /* activate RX and TX state machine and frame sync*/
                        Mcasp_enableInterrupt(chanHandle->cpuEventNum);
                        Mcasp_localActivateSmFsForRcv(instHandle);
                    }
                    else
                    {
                        /* Transmit channel */
                        /* activate RX and TX state machine and frame sync*/
                        Mcasp_enableInterrupt(chanHandle->cpuEventNum);
                        Mcasp_localActivateSmFsForXmt(instHandle);
                    }
                }
                else
                {
                    /***        DLB Mode      ****/
                    /* activate RX and TX state machine and frame sync    */
                    Mcasp_enableInterrupt(instHandle->hwInfo.cpuRxEventNum);
                    Mcasp_enableInterrupt(instHandle->hwInfo.cpuTxEventNum);
                    Mcasp_localActivateSmFsForBoth(instHandle);
                }

#endif
            }
        }
    }
    while (falseWhile);
}

#ifndef Mcasp_LOOPJOB_ENABLED
/*
 *  \brief  This function waits for the FIFO to be emptied so that the Framesync
 *          can be stopped.here after the FIFO is empty.
 *
 *  \param  arg0   [IN]  Handle to the TX channel
 *  \param  arg1   [IN]  unused
 *
 *  \return None
 *
 *  \enter  Not implemented
 *
 *  \leave  Not implemented
 */
Void Mcasp_swiTxFifo(UArg arg0, UArg arg1)
{
    Mcasp_ChannelObj *chanHandle = NULL;
    Mcasp_Object     *instHandle = NULL;
    UInt32 timeOut = 0x00;
    UInt32 dlbMode = 0x00;
    UInt32 tempVal = 0x0;

    chanHandle = (Mcasp_ChannelObj *) arg0;
    instHandle = (Mcasp_Object *) arg1;

    assert(NULL != chanHandle);
    assert(NULL != instHandle);

    /* update the timeout value from the instance handle                      */
    timeOut = instHandle->retryCount;

    dlbMode = McASPDlbRegRead(instHandle->hwInfo.regs);

    /* we have come here means that the Mcasp has got an callback but it      *
     * did have any more packet to load Hence here we will wait for the       *
     * FIFO to become empty (if FIFO is enabled) else wait for the TX to      *
     * become empty.then we will disable the TX section                       */
    if ((Bool) TRUE == chanHandle->enableHwFifo)
    {
        tempVal = McASPTxFifoStatusGet(instHandle->hwInfo.regs);

        while ((0 != (tempVal & 0xFF))  /* Checking for 0-7 bits of the reg */
               && (0 != timeOut))
        {
            /* reduce the timeout count and check if the FIFO is empty        */
            timeOut--;
            tempVal = McASPTxFifoStatusGet(instHandle->hwInfo.regs);
        }
    }

    /* reinitialize the retry count                                           */
    timeOut = instHandle->retryCount;
    tempVal = 0x0;
    tempVal = McASPTxStatusGet(instHandle->hwInfo.regs);

    while ((MCASP_TX_STAT_UNDERRUN !=
            (tempVal & MCASP_TX_STAT_UNDERRUN))
           && (0 != timeOut))
    {
        /* reduce the retry count and check if the TX has completed           *
         * transmitting all the bytes                                         */
        timeOut--;
        tempVal = McASPTxStatusGet(instHandle->hwInfo.regs);
    }

    /* Now we can disable the frame sync                                      */
    if (MCASP_LBCTL_DLBEN_ENABLE == dlbMode)
    {
        Mcasp_localDeactivateSmFsForRcv(instHandle);
        Mcasp_localDeactivateSmFsForXmt(instHandle);
    }
    else
    {
        /* Reset state m/c & frame sync of TX section                         */
        Mcasp_localDeactivateSmFsForXmt(instHandle);
    }

    if (MCASP_TX_UNDERRUN ==
        (MCASP_TX_UNDERRUN & chanHandle->userIntValue))
    {
        /* clear the underrun error                                           */
        tempVal  = McASPTxStatusGet(instHandle->hwInfo.regs);
        tempVal |= MCASP_TX_STAT_UNDERRUN;
        McASPTxStatusSet(instHandle->hwInfo.regs, tempVal);

        /* enable the underrun error                                          */
        McASPTxIntEnable(instHandle->hwInfo.regs,
                         MCASP_TX_UNDERRUN);
    }

    /* clear the error bits in the EDMA(as this is the last packet)           */
    EDMA3_DRV_clearErrorBits(
        chanHandle->edmaHandle,
        chanHandle->xferChan);

    /* complete the IOP now and call the callback to the stream               */
    chanHandle->tempPacket =
        (IOM_Packet *) Queue_get(Queue_handle(&(chanHandle->queueFloatingList)));

    /* Decrement the submit count for the IOpackets                           */
    chanHandle->submitCount--;

    chanHandle->isTempPacketValid  = (Bool) TRUE;
    chanHandle->tempPacket->status = chanHandle->currentPacketErrorStatus;

    Mcasp_localCompleteCurrentIo(chanHandle);

#if defined (BIOS_PWRM_ENABLE) && !defined (Mcasp_LOOPJOB_ENABLED)
    /* check if the driver is waiting to go to sleep or process DVFS event    *
     * (only if the application has requested PWRM support)                   */
    if ((Bool) TRUE == instHandle->prcmPwrmEnable)
    {
        Mcasp_localHandlePwrmEvent(instHandle, chanHandle);
    }
#endif /* #ifdef BIOS_PWRM_ENABLE  */
}

/**
 * \brief     This function restores the driver to the original state that is it
 *            resumes the normal operation of the driver by picking the IOPs
 *            from the pending queue and putting it to the active IOP.
 *
 * \param     instHandle [IN] Handle to the device instance object
 *
 * \enter     instHandle is a valid non NULL pointer
 *
 * \leave     Not impplemented
 */
Int32 Mcasp_loadPendedIops(Mcasp_ChannelObj *chanHandle)
{
    IOM_Packet *ioPacket        = NULL;
    Int32       status          = IOM_COMPLETED;
    UInt32      count           = 0x00;
    UInt32      hwiKey          = 0x00;
    UInt32      tempSubmitCount = 0x00;

    assert(NULL != chanHandle);

    /* reset the submit count to indicate we are loading the first packet     */
    tempSubmitCount         = (UInt32) chanHandle->submitCount;
    chanHandle->submitCount = 0x00;

    for (count = 0; count < (Mcasp_MAXLINKCNT + 1); count++)
    {
        /* start the critical section                                         */
        hwiKey = (UInt32) Hwi_disable();

        if ((Bool) TRUE == Queue_empty(Queue_handle(&chanHandle->queueReqList)))
        {
            break;
        }
        else
        {
            chanHandle->submitCount++;

            /* get the packet out of the pending queue and load it to the     *
             * active Queue                                                   */
            ioPacket =
                (IOM_Packet *) Queue_get(Queue_handle(&(chanHandle->
                                                        queueReqList)));

            /* put the packet in to the active queue                          */
            Queue_put(Queue_handle(
                          &(chanHandle->queueFloatingList)),
                      (Queue_Elem *) ioPacket);

            /* load the packet to the edma                                    */
            Mcasp_localLoadPktToEdma(chanHandle, ioPacket);
        }
    }

    /* restore the submit count                                               */
    chanHandle->submitCount = (Int32) tempSubmitCount;
    Hwi_restore(hwiKey);

    return status;
}

#endif /* Mcasp_LOOPJOB_ENABLED */

/*============================================================================*/
/*                             PWRM FUNCTIONS                                 */
/*============================================================================*/

/**
 *  \brief    Mcasp_localPrcmOn
 *
 *            This function is invoked to power on the Mcasp peripheral and
 *            configure it according to the operating mode. Note that this
 *            function uses different functions to power ON the module,
 *            depending on whether PWRM is enabled in this driver or NOT
 *
 *  \param    instHandle  [IN] Handle to the device instance
 *
 *  \return   IOM_COMPLETED in case of success, an ERROR code in case of error.
 *
 *  \enter    instHandle    must be a valid pointer
 *
 *  \leave    Not Implemented.
 */
Int32 Mcasp_localPrcmOn(const Mcasp_Object *instHandle)
{
    Int32 status = IOM_COMPLETED;

    assert(NULL != instHandle);
    if ((Bool) TRUE == instHandle->prcmPwrmEnable)
    {
/* #ifdef BIOS_PWRM_ENABLE */
        /* power on using bios PWRM API
         */
        /*
         *      status = (Int32)PWRM_setDependency(
         *                  (PWRM_Resource)instHandle->hwInfo.pwrmLpscId);
         #else */
        /* power on using the PRCM API
         */
        /*
         *          Prcm_ModuleClkCtrl(
         *            (Int)instHandle->prcmDevId,
         *              (UInt32)instHandle->hwInfo.pwrmPrcmId,
         *              Prcm_moduleClkCtrl_ENABLE,
         *              NULL);
         *
         #endif */
    }
    return (status);
}

/**
 * \brief    Mcasp_localPrcmOff
 *
 *           This function is invoked to power off the module.
 *
 * \param    instHandle  [IN] Handle to the device instance
 *
 * \return   IOM_COMPLETED in case of success, an ERROR code in case of error.
 *
 * \enter    instHandle must be a valid channel object
 *           No pending IO
 *
 * \leave    Not Implemented.
 */
Int32 Mcasp_localPrcmOff(const Mcasp_Object *instHandle)
{
    Int32 status = IOM_COMPLETED;

    assert(NULL != instHandle);

    if ((Bool) TRUE == instHandle->prcmPwrmEnable)
    {
/* #ifdef BIOS_PWRM_ENABLE*/
        /* power off  using PWRM API
         */
        /*        status = (Int32)PWRM_releaseDependency(
         *
         *
         *                        (PWRM_Resource)instHandle->hwInfo.pwrmLpscId);
         #else */
        /* power off using PRCM API only if it is an instance other than "0"
         */
        /*
         *          Prcm_ModuleClkCtrl(
         *            (Int)instHandle->prcmDevId,
         *              (UInt32)instHandle->hwInfo.pwrmPrcmId,
         *              Prcm_moduleClkCtrl_DISABLE,
         *              NULL);
         *
         #endif*/
    }
    return (status);
}

#if defined (BIOS_PWRM_ENABLE) && !defined (Mcasp_LOOPJOB_ENABLED)
/**
 * \brief     This function registers with the BIOS PWRM module for all the
 *            possible power management events.
 *
 * \param     instHandle [IN] Handle to the driver instance object
 *
 * \return    None
 *
 * \enter     instHandle is a NON null valid pointer
 *
 * \leave     Not implemented
 */
static Int32 McaspRegisterNotification(Mcasp_Object *instHandle)
{
    UInt32      eventCnt = 0x00;
    PWRM_Status retVal   = PWRM_SOK;
    Int32       status   = IOM_COMPLETED;

    assert(NULL != instHandle);

    /* register for the events to be notified by the driver                   */
    for (eventCnt = 0; eventCnt < Mcasp_MAX_PWRM_EVENTS; eventCnt++)
    {
        /* register the notify function for the PWRM event                    */
        retVal = PWRM_registerNotify(
            (PWRM_Event) eventCnt,
            NULL,
            &McaspNotifyCallback,
            (UArg) instHandle,
            &(instHandle->pwrmInfo.notifyHandle[eventCnt]),
            &(instHandle->pwrmInfo.delayedCompletionFxn[eventCnt]));

        if (PWRM_SOK != retVal)
        {
            status = IOM_EBADARGS;
            break;
        }
    }
    return (status);
}

/**
 * \brief     This function is the notify function called by the BIOS whenever
 *            a power event occurs in the system.This function handles the
 *            power events and calls the appropriate functions to process the
 *            same.
 *
 * \param     eventType [IN] power event type
 * \param     eventArg1 [IN] event-specific argument
 * \param     eventArg2 [IN] event-specific argument
 * \param     clientArg [IN] argument passed by the PWRM module(usually
 *                          (supplied during the registration of the notifyFxn)
 *
 * \return    None
 *
 * \enter     eventType is a valid event
 *
 * \leave     Not implemented
 */
static PWRM_NotifyResponse McaspNotifyCallback(PWRM_Event eventType,
                                               UArg       eventArg1,
                                               UArg       eventArg2,
                                               UArg       clientArg)
{
    Mcasp_Object       *instHandle = NULL;
    PWRM_NotifyResponse pwrmStatus = PWRM_NOTIFYDONE;
    PWRM_Status         status     = PWRM_SOK;

    assert(NULL != clientArg);

    eventArg1 = eventArg1;
    eventArg2 = eventArg2;

    instHandle = (Mcasp_Object *) clientArg;
    assert(NULL != instHandle);

    /* check the event notified by the PWRM module and process accordingly    */
    switch (eventType)
    {
        case PWRM_GOINGTOSLEEP:
        case PWRM_GOINGTOSTANDBY:
        case PWRM_GOINGTODEEPSLEEP:
            pwrmStatus = McaspSuspendCurrentIops(instHandle, eventType);
            break;
        case PWRM_PENDING_CPU_SETPOINTCHANGE:
        case PWRM_PENDING_PER_SETPOINTCHANGE:
            /* No DVFS changes required hence return done                     */
            pwrmStatus = PWRM_NOTIFYDONE;
            break;
        case PWRM_DONE_CPU_SETPOINTCHANGE:
        case PWRM_DONE_PER_SETPOINTCHANGE:
            /* No DVFS changes required hence return done                     */
            pwrmStatus = PWRM_NOTIFYDONE;
            break;
        case PWRM_AWAKEFROMSLEEP:
        case PWRM_AWAKEFROMDEEPSLEEP:
            /* restore the dependency count                                   */
            while (instHandle->pwrmInfo.dependencyCount > 0)
            {
                status = PWRM_setDependency(
                    (PWRM_Resource) instHandle->hwInfo.pwrmLpscId);

                if (PWRM_SOK != status)
                {
                    break;
                }
                instHandle->pwrmInfo.dependencyCount--;
            }

            if (PWRM_SOK == status)
            {
                Mcasp_loadPendedIops(&instHandle->XmtObj);
                Mcasp_loadPendedIops(&instHandle->RcvObj);
                instHandle->devState = Mcasp_DriverState_CREATED;
            }
            else
            {
                pwrmStatus = PWRM_NOTIFYNOTDONE;
            }
            break;
        case PWRM_AWAKEFROMSTANDBY:
            Mcasp_loadPendedIops(&instHandle->XmtObj);
            Mcasp_loadPendedIops(&instHandle->RcvObj);

            instHandle->devState = Mcasp_DriverState_CREATED;
            break;
        default:
            break;
    }
    return (pwrmStatus);
}

/**
 * \brief    This function configures the driver so that the current IOP can be
 *           completed and then supends all the remaining IOPs.
 *
 * \param    instHandle [IN] Handle to the device instance object
 * \param    eventType  [IN] event which has caused this notification call to
 *                           driver
 *
 * \return   PWRM_NOTIFYDONE    if no IOPs are pending
 *           PWRM_NOTIFYNOTDONE if IOPs are pending in the driver.
 */
static PWRM_NotifyResponse McaspSuspendCurrentIops(Mcasp_Object *instHandle,
                                                   PWRM_Event    eventType)
{
    UInt32 hwiKey = 0x00;
    PWRM_NotifyResponse status = PWRM_NOTIFYDONE;

    assert(NULL != instHandle);

    hwiKey = (UInt32) Hwi_disable();

    if (((Bool) TRUE ==
         Queue_empty(Queue_handle(&instHandle->XmtObj.queueFloatingList))) &&
        ((Bool) TRUE ==
         Queue_empty(Queue_handle(&instHandle->RcvObj.queueFloatingList))))
    {
        /* No IOP is pending currently. we can return the status of the       *
         * notify call as sucess                                              */
        instHandle->devState = Mcasp_DriverState_PWRM_SUSPEND;
        status = PWRM_NOTIFYDONE;
    }
    else
    {
        /* There are some IOPs pending,hence we will complete processing      *
         * of this request in the ISR context(task in case of polled mode)    *
         * by calling the delayed completion function                         */
        status = PWRM_NOTIFYNOTDONE;
        instHandle->pwrmInfo.ioSuspend = (Bool) TRUE;
        instHandle->pwrmInfo.pwrmEvent = eventType;
    }

    Hwi_restore(hwiKey);
    return (status);
}

/**
 * \brief     This function unregisters all the power management events
 *            which were previously registered by the driver instance.
 *
 * \param     instHandle [IN] Handle to the driver instance object
 *
 * \return    IOM_COMPLETED in case of success
 *            IOM_EBADARGS  in case of error
 *
 * \enter     instHandle is a NON null valid pointer
 *
 * \leave     Not implemented
 */
static Int32 McaspUnregisterNotification(Mcasp_Object *instHandle)
{
    UInt32      eventCnt = 0x00;
    PWRM_Status retVal   = PWRM_SOK;
    Int32       status   = IOM_COMPLETED;

    assert(NULL != instHandle);

    for (eventCnt = 0; eventCnt < Mcasp_MAX_PWRM_EVENTS; eventCnt++)
    {
        /* register the notify function for the PWRM event                    */
        if (NULL != (instHandle->pwrmInfo.notifyHandle[eventCnt]))
        {
            retVal = PWRM_unregisterNotify(
                (instHandle->pwrmInfo.notifyHandle[eventCnt]));

            if (PWRM_SOK != retVal)
            {
                status = IOM_EBADARGS;
                break;
            }
            else
            {
                instHandle->pwrmInfo.notifyHandle[eventCnt] = 0x00;
            }
        }
    }
    return (status);
}

/**
 * \brief     This function unregisters all the constraints for the device
 *            instance.
 *
 * \param     instHandle [IN]  Handle to the driver instance object
 *
 * \return    IOM_COMPLETED in case of success
 *            IOM_EBADMODE in case of failure
 *
 * \enter     instHandle is a valid non null pointer
 *
 * \leave     Not implemented
 */
static Int32 McaspUnregisterConstraints(Mcasp_Object *instHandle)
{
    Int32       status = IOM_COMPLETED;
    PWRM_Status retVal = PWRM_SOK;
    UInt32      count  = 0x00;

    assert(NULL != instHandle);

    for (count = 0; count < Mcasp_MAX_PWRM_CONSTRAINTS; count++)
    {
        if (NULL != instHandle->pwrmInfo.constraintHandle[count])
        {
            retVal = PWRM_unregisterConstraint(
                instHandle->pwrmInfo.constraintHandle[count]);

            if (PWRM_SOK != retVal)
            {
                status = IOM_EBADMODE;
                break;
            }
            else
            {
                instHandle->pwrmInfo.constraintHandle[count] = 0x00;
            }
        }
    }
    return (status);
}

#endif

static Void Mcasp_enableInterrupt(UInt32 cpuEventNum)
{
#ifdef BUILD_DSP
    EventCombiner_enableEvent(cpuEventNum);
#else
    Hwi_enableInterrupt(cpuEventNum);
#endif
}

static Void Mcasp_disableInterrupt(UInt32 cpuEventNum)
{
#ifdef BUILD_DSP
    EventCombiner_disableEvent(cpuEventNum);
#else
    Hwi_disableInterrupt(cpuEventNum);
#endif
}

/* ========================================================================== */
/*                             END OF FILE                                    */
/* ========================================================================== */

