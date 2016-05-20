/**
 *  \file     dcan_evm_loopback_app_main.c
 *
 *  \brief    This file contains DCAN board to board loopback test for TX and RX
 *
 *  \details  DCAN board to board which tests the Tx from board 1 output to
 *            Rx input of board 2. Transmitted messages are treated as
 *            received messages and can be stored into message objects if they
 *            pass acceptance filtering.
 *
 *  \copyright Copyright (C) 2014 Texas Instruments Incorporated -
 *             http://www.ti.com/
 */

/* ======================================================================
 *   Copyright (C) 2014 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "stdint.h"
#include <string.h>
#include <common/stw_types.h>
#include <common/stw_utils.h>
#include <common/stw_dataTypes.h>
#include "hw_types.h"
#include "interrupt.h"
#include "irq_xbar_interrupt_ids.h"
#include "irq_xbar.h"
#include "soc.h"
#include "soc_defines.h"
#include "platform.h"
#include "uartStdio.h"
#include "hw_counter_32k.h"
#include "hw_ipu_unicache_cfg.h"
#include "pm/pm_types.h"

/* Application header files */
#include "dcan.h"

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

/** \brief 32K Timer Frequency */
#define TIMER_FREQUENCY_32KCOUNTER          (32 * 1024U)

/** \brief DCAN bit time calculation maximum error value. */
#define DCAN_APP_CALC_MAX_ERROR         (50U)
/** \brief Macro used to extract bit rate prescaler value. */
#define DCAN_APP_EXTRACT_BRPE_VAL       (0x3C0U)
/** \brief Shift value used for bit rate prescaler. */
#define DCAN_APP_BRPE_SHIFT             (6U)

/** \brief DCAN instance used */
#define DCAN_APP_INST                   (SOC_DCAN1_BASE)

/** \brief DCAN input clock - 20MHz */
#define DCAN_APP_INPUT_CLK              (20000000U)
/** \brief DCAN output bit rate - 1MHz */
#define DCAN_APP_BIT_RATE               (1000000U)

/** \brief DCAN TX interface register used */
#define DCAN_APP_TX_IF_REG              (DCAN_IF_REG_NUM_1)
/** \brief DCAN RX interface register used */
#define DCAN_APP_RX_IF_REG              (DCAN_IF_REG_NUM_2)

/** \brief Offset of DRM SUSPEND_CTRL1 register */
#define DRM_SUSPEND_CTRL1               (0x204)
/** \brief DRM_SUSPEND_CTRL1 is mapped to DCAN1 Suspend Output line */
#define DRM_SUSPEND_CTRL_DCAN1          (SOC_I_DRM_BASE + DRM_SUSPEND_CTRL1)

/** \brief DRM SUSPEND Source as A15 */
#define DRM_SUSPEND_SRC_MPU_C0          (0x5)
/** \brief DRM SUSPEND Source as M4 */
#define DRM_SUSPEND_SRC_IPU1_C0         (0x3)

#define DCAN_TX_TEST       ('1')
#define DCAN_RX_TEST       ('2')
#define EXIT(opt)      (('x' == opt) || ('X' == opt))

/** \brief DCAN message object identifier used */
#define DCAN_APP_MSG_IDENTIFIER            (0xC1)
/** \brief DCAN message object id used : 1=>Extended Frame, 0=>Standard Frame */
#define DCAN_APP_MSG_ID                    (DCAN_XID_29_BIT)
/** \brief DCAN FIFO Buffer depth used */
#define DCAN_APP_FIFO_BUF_DEPTH            (8U)
/** \brief DCAN TX FIFO Buffer start index used */
#define DCAN_APP_TX_FIFO_BUF_START_IDX        (1U)
/** \brief DCAN RX FIFO Buffer start index used */
#define DCAN_APP_RX_FIFO_BUF_START_IDX        (30U)

/** \brief DCAN Standard Frame Format Length excluding Data field used
 *   Start of Frame (SOF) : 1 bit field,
 *   Identifier : 11 bit field
 *   Remote transmission request  (RTR) : 1 bit field,
 *   Identifier extension bit (IDE) : 1 bit field
 *   Reserved bit (r0) : 1 bit field
 *   Data length code (DLC)  : 4 bit field
 *   Data field : (0 - 64 bit)
 *   CRC : 15 bit field
 *   CRC delimiter (r0) : 1 bit field
 *   ACK slot (r0) : 1 bit field
 *   ACK delimiter : 1 bit field
 *   End-of-frame (EOF) : 7 bit field
 */
#define DCAN_APP_STD_FIXED_FRAME_FMT_LENGTH        (44U)

/** \brief DCAN Extended Frame Format Length excluding Data field used
 *   Start of Frame (SOF) : 1 bit field,
 *   Identifier A : 11 bit field
 *   Substitute remote request  (SRR) : 1 bit field,
 *   Identifier extension bit (IDE) : 1 bit field
 *   Identifier B : 18 bit field
 *   Remote transmission request  (RTR) : 1 bit field,
 *   Reserved bit (r0) : 1 bit field
 *   Reserved bit (r1) : 1 bit field
 *   Data length code (DLC)  : 4 bit field
 *   Data field : (0 - 64 bit)
 *   CRC : 15 bit field
 *   CRC delimiter (r0) : 1 bit field
 *   ACK slot (r0) : 1 bit field
 *   ACK delimiter : 1 bit field
 *   End-of-frame (EOF) : 7 bit field
 */
#define DCAN_APP_EXT_FIXED_FRAME_FMT_LENGTH        (64U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 *  \brief    Enumerates the values used to represent the DCAN bit time
 *            calculation error values.
 */
typedef enum dcanBitTimeCalcErrType
{
    DCAN_BIT_RATE_ERR_MAX = 1,
    /**< Bitrate error maximum value */
    DCAN_BIT_RATE_ERR_WARN = 2,
    /**< Bitrate error warning value */
    DCAN_BIT_RATE_ERR_NONE = 3
                             /**< No bit rate error */
} dcanBitTimeCalcErrType_t;

/** \brief Structure holding Bit Time parameters for DCAN application. */
typedef struct dcanBitTimeParamsLocal
{
    uint32_t samplePnt;
    uint32_t timeQuanta;
    uint32_t propSeg;
    uint32_t phaseSeg1;
    uint32_t phaseSeg2;
    uint32_t syncJumpWidth;
    uint32_t bitRatePrescaler;
    uint32_t tseg1Min;
    uint32_t tseg1Max;
    uint32_t tseg2Min;
    uint32_t tseg2Max;
    uint32_t syncJumpWidthMax;
    uint32_t bitRatePrescalerMin;
    uint32_t bitRatePrescalerMax;
    uint32_t bitRatePrescalerInc;
    uint32_t bitRate;
} dcanBitTimeParamsLocal_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void DCANAppConfigIntr(char mainMenuOption);
static void DCANAppTxInt0Isr();
static void DCANAppRxInt0Isr();

static uint32_t DCANAppBitTimeCalculator(
    dcanBitTimeParamsLocal_t *pBitTimeParam,
    uint32_t                  clkFreq);

static int32_t DCANAppUpdateSamplePnt(dcanBitTimeParamsLocal_t *pBitTimeParam,
                                      int32_t                   samplePnt,
                                      int32_t                   tseg,
                                      int32_t                  *tseg1,
                                      int32_t                  *tseg2);

static void DCANAppInitCfgParams(dcanCfgParams_t *pDcanCfgPrms);

static void DCANAppInitTxParams(dcanMsgObjCfgParams_t *pDcanTxCfgPrms,
                                dcanTxParams_t        *pDcanTxPrms,
                                uint32_t               dataLength,
                                uint8_t               *dataBuffer);

static void DCANAppInitRxParams(dcanMsgObjCfgParams_t *pDcanRxCfgPrms);

static void DCANAppWaitForIfReg(uint32_t baseAddr, uint32_t ifRegNum);
/**
 * \brief   This function takes I/P Clk frequency, required bit-rate on the
 *          CAN bus and calculates the value to be programmed for DCAN BTR
 *          register. This API doesn't to the actual programming. This is
 *          intended to be used as a utility function. And the application
 *          should call the #DCANSetBitTime function to do the actual
 *          programming.
 *
 * \param   clkFreq        I/P clock frequency to DCAN controller in Hz.
 * \param   bitRate        Required bit-rate on the CAN bus in bits per second.
 * \param   pBitTimePrms   Pointer to params where the calculated register
 *                         fields are populated
 *
 * \return  errVal         Returns Bit Time calculation error of type enum
 *                         dcanBitTimeCalcErrType_t
 */
static uint32_t DCANCalculateBitTimeParams(uint32_t             clkFreq,
                                           uint32_t             bitRate,
                                           dcanBitTimeParams_t *pBitTimePrms);

volatile unsigned char gRxDoneFlag = 0;
volatile unsigned char gErrStatus  = 0;

volatile unsigned int  gMsgObj[20] = {0};
volatile unsigned char gIsrCnt   = 0;
volatile unsigned char gRxAppCnt = 0;

static void mainMenu(char *option);
static void mainSubMenu(char      mainMenuOption,
                        uint32_t *dataLength,
                        uint8_t  *dataBuffer,
                        uint32_t *numMsg);
static int32_t dcanTxTest(char mainMenuOption);
static int32_t dcanRxTest(char mainMenuOption);
static uint32_t read32KTimer(void);
static uint32_t dcanGetTheoriticalMax(uint32_t dataLength,
                                      uint32_t msgId,
                                      uint32_t bitRate);
#if defined (BUILD_M4)
static void enableIPU1Unicache(void);
static void disableIPU1Unicache(void);
#endif

int main(void)
{
    volatile uint32_t testDone = 1;
    char mainMenuOption;
    int32_t           retVal = STW_SOK;

    PlatformUartConsoleSetPinMux();

    UARTStdioInit();

    while (1)
    {
        mainMenu(&mainMenuOption);
        if (DCAN_TX_TEST == mainMenuOption)
        {
            retVal = dcanTxTest(mainMenuOption);
        }
        else if (DCAN_RX_TEST == mainMenuOption)
        {
            retVal = dcanRxTest(mainMenuOption);
        }
        else
        {
            UARTPuts("\nDCAN Evm Loopback test exiting...", -1);
            break;
        }
    }
    while (testDone) ;
    return retVal;
}

static int32_t dcanTxTest(char mainMenuOption)
{
    int32_t               retVal    = STW_SOK;
    int32_t               errStatus = STW_SOK;
    dcanCfgParams_t       appDcanCfgPrms;
    dcanMsgObjCfgParams_t appDcanTxCfgPrms;
    dcanTxParams_t        appDcanTxPrms;
    dcanBitTimeParams_t   appDcanBitTimePrms;
    uint32_t              timeOut       = 100U;
    uint32_t              msgCnt        = 0U;
    uint32_t              numMsg        = 0U;
    uint32_t              dataLength    = 0U;
    uint8_t               dataBuffer[8] = {0};
    uint32_t              fifoBufIdx;
    uint32_t              fifoBufCnt     = 1U;
    uint32_t              fifoFreeBufCnt = 1U;
    uint32_t              startTimeVal   = 0U;
    uint32_t              endTimeVal     = 0U;
    Float32               timeTaken;
    uint32_t              numMsgTxedPerSec;
    uint32_t              theoriticalMaxTBA;
    uint32_t              hwUtilizeStat;

    UARTPuts("\nDCAN Transmit Test App: DCAN1 MSG OBJ 1 (TX)", -1);

    /* Configure the Control module & Dcan Clock */
    retVal = PlatformDcanClkConfig(0);
    if (retVal != PM_SUCCESS)
    {
        UARTPuts("\nControl module & Dcan Clock Configure fails", -1);
    }

    mainSubMenu(mainMenuOption, &dataLength, dataBuffer, &numMsg);

#if defined (BUILD_M4)
    /* DRM_SUSPEND_CTRL_DCAN1 - SUSPEND_SEL(Suspend source selection) as IPU1_C0
     * & SENS_CTRL(Sensitivity control) as 1 means suspend signal must reach the
     * peripheral-IP  */
    HW_WR_REG32(DRM_SUSPEND_CTRL_DCAN1, ((DRM_SUSPEND_SRC_IPU1_C0 << 4) | 0x1));
#elif defined (BUILD_A15)
    /* DRM_SUSPEND_CTRL_DCAN1 - SUSPEND_SEL(Suspend source selection) as MPU_C0
     * & SENS_CTRL(Sensitivity control) as 1 means suspend signal must reach the
     * peripheral-IP  */
    HW_WR_REG32(DRM_SUSPEND_CTRL_DCAN1, ((DRM_SUSPEND_SRC_MPU_C0 << 4) | 0x1));
#endif

    DCANAppInitCfgParams(&appDcanCfgPrms);
    DCANAppInitTxParams(&appDcanTxCfgPrms, &appDcanTxPrms, dataLength,
                        dataBuffer);

    /*Unlock the Crossbar register */
    PlatformUnlockMMR();

    /* Clock Configuration. */
    PlatformDCAN1PrcmEnable();

    /* Initialize the DCAN message RAM. */
    PlatformDcanMessageRamInit(0);

    /* Perform the DCAN pinmux. */
    PlatformDCAN1SetPinMux();

    /* Register Crossbars and IRQ numbers */
    DCANAppConfigIntr(mainMenuOption);

    /* Reset the DCAN IP */
    retVal = DCANReset(DCAN_APP_INST, timeOut);
    if (retVal == STW_SOK)
    {
        /* Set the desired bit rate based on input clock */
        DCANSetMode(DCAN_APP_INST, DCAN_MODE_INIT);
        errStatus = DCANCalculateBitTimeParams(DCAN_APP_INPUT_CLK,
                                               DCAN_APP_BIT_RATE,
                                               &appDcanBitTimePrms);
        if (errStatus != DCAN_BIT_RATE_ERR_NONE)
        {
            return errStatus;
        }
        DCANSetBitTime(DCAN_APP_INST, &appDcanBitTimePrms);
        DCANSetMode(DCAN_APP_INST, DCAN_MODE_NORMAL);

        /* Configure DCAN controller */
        DCANConfig(DCAN_APP_INST, &appDcanCfgPrms);
    }

    /* Configuring FIFO Buffer of depth DCAN_APP_FIFO_BUF_DEPTH*/
    for (fifoBufIdx = DCAN_APP_TX_FIFO_BUF_START_IDX;
         fifoBufIdx < (DCAN_APP_TX_FIFO_BUF_START_IDX + DCAN_APP_FIFO_BUF_DEPTH);
         fifoBufIdx++)
    {
        /*
         * Enable message object interrupt to route interrupt line 1
         */
        DCANConfigIntrMux(DCAN_APP_INST, DCAN_INTR_LINE_NUM_0, fifoBufIdx);

        if (fifoBufIdx ==
            ((DCAN_APP_TX_FIFO_BUF_START_IDX + DCAN_APP_FIFO_BUF_DEPTH) - 1))
        {
            appDcanTxCfgPrms.fifoEOBFlag = TRUE;
        }
        else
        {
            appDcanTxCfgPrms.fifoEOBFlag = FALSE;
        }
        if (retVal == STW_SOK)
        {
            /* Wait for interface to become free */
            DCANAppWaitForIfReg(DCAN_APP_INST, DCAN_APP_TX_IF_REG);
            retVal = DCANConfigMsgObj(DCAN_APP_INST,
                                      fifoBufIdx,
                                      DCAN_APP_TX_IF_REG,
                                      &appDcanTxCfgPrms);
            /* Wait for config to be copied to internal message RAM */
            DCANAppWaitForIfReg(DCAN_APP_INST, DCAN_APP_TX_IF_REG);
        }
    }

#if defined (BUILD_M4)
    enableIPU1Unicache();
#endif
    startTimeVal = read32KTimer();

    for (msgCnt = 0; msgCnt < numMsg; msgCnt++)
    {
        gErrStatus = 0;

        if (retVal == STW_SOK)
        {
            /* Wait for interface to become free */
            DCANAppWaitForIfReg(DCAN_APP_INST, DCAN_APP_TX_IF_REG);
            retVal = DCANTransmitData(DCAN_APP_INST,
                                      fifoBufCnt,
                                      DCAN_APP_TX_IF_REG,
                                      &appDcanTxPrms,
                                      timeOut);
            /* Wait for config to be copied to internal message RAM */
            DCANAppWaitForIfReg(DCAN_APP_INST, DCAN_APP_TX_IF_REG);
            if (fifoBufCnt == DCAN_APP_FIFO_BUF_DEPTH)
                fifoBufCnt = 0;
            fifoBufCnt++;
        }
        if (retVal == STW_SOK)
        {
            /* check for Error is occured or not */
            if (gErrStatus != 0)
            {
                retVal = STW_EFAIL;
                break;
            }
            if (msgCnt >= (DCAN_APP_FIFO_BUF_DEPTH - 1))
            {
                while (DCANIsTxMsgPending(DCAN_APP_INST, fifoFreeBufCnt)) ;
                if (fifoFreeBufCnt == DCAN_APP_FIFO_BUF_DEPTH)
                    fifoFreeBufCnt = 0;
                fifoFreeBufCnt++;
            }
        }
        else
        {
            break;
        }
    }
    endTimeVal = read32KTimer();
#if defined (BUILD_M4)
    disableIPU1Unicache();
#endif

    if (retVal == STW_EFAIL)
    {
        UARTPuts("\nDCAN -- Board to Board Test (TX) Failed!! \n", -1);
    }
    else
    {
        UARTPuts("\nDCAN -- Board to Board Test (TX) Passed!! \n", -1);
    }

    timeTaken =
        ((Float32) (endTimeVal -
                    startTimeVal)) / ((Float32) TIMER_FREQUENCY_32KCOUNTER);
    numMsgTxedPerSec = (uint32_t) (((Float32) numMsg) / ((Float32) timeTaken));

    theoriticalMaxTBA = dcanGetTheoriticalMax(dataLength,
                                              DCAN_APP_MSG_ID,
                                              DCAN_APP_BIT_RATE);

    hwUtilizeStat =
        (uint32_t) ((((Float32) numMsgTxedPerSec) /
                     ((Float32) theoriticalMaxTBA)) * 100);

    UARTPuts("\n Messages transmitted per sec: ", -1);
    UARTPutNum(numMsgTxedPerSec);

    UARTPuts("\n Theoritical Max to be achieved :", -1);
    UARTPutNum(theoriticalMaxTBA);

    UARTPuts("\n DCAN HW utilization achieved : ", -1);
    UARTPutNum(hwUtilizeStat);
    UARTPuts("% ", -1);

    return retVal;
}

static int32_t dcanRxTest(char mainMenuOption)
{
    int32_t               retVal    = STW_SOK;
    int32_t               errStatus = STW_SOK;
    dcanCfgParams_t       appDcanCfgPrms;
    dcanMsgObjCfgParams_t appDcanRxCfgPrms;
    dcanBitTimeParams_t   appDcanBitTimePrms;
    dcanRxParams_t        appDcanRxPrms;
    uint32_t              timeOut    = 100U;
    uint32_t              dataLength = 0U;
    uint32_t              msgCnt, fifoBufIdx;
    uint32_t              rxMsgStatus           = FALSE;
    uint32_t              msgLstErrCnt          = 0U;
    uint32_t              dataMissMatchErrCnt   = 0U;
    uint32_t              expectedDataLength    = 0U;
    uint32_t              expectedNumMsg        = 0U;
    uint8_t               expectedDataBuffer[8] = {0};

    UARTPuts("\nDCAN Receive Test App: DCAN1 MSG OBJ (RX)", -1);

    retVal = PlatformDcanClkConfig(0);
    if (retVal != PM_SUCCESS)
    {
        UARTPuts("\nControl module & Dcan Clock Configure fails", -1);
    }

    mainSubMenu(mainMenuOption, &expectedDataLength, expectedDataBuffer,
                &expectedNumMsg);

#if defined (BUILD_M4)
    /* DRM_SUSPEND_CTRL_DCAN1 - SUSPEND_SEL(Suspend source selection) as IPU1_C0
     * & SENS_CTRL(Sensitivity control) as 1 means suspend signal must reach the
     * peripheral-IP  */
    HW_WR_REG32(DRM_SUSPEND_CTRL_DCAN1, ((DRM_SUSPEND_SRC_IPU1_C0 << 4) | 0x1));
#elif defined (BUILD_A15)
    /* DRM_SUSPEND_CTRL_DCAN1 - SUSPEND_SEL(Suspend source selection) as MPU_C0
     * & SENS_CTRL(Sensitivity control) as 1 means suspend signal must reach the
     * peripheral-IP  */
    HW_WR_REG32(DRM_SUSPEND_CTRL_DCAN1, ((DRM_SUSPEND_SRC_MPU_C0 << 4) | 0x1));
#endif

    DCANAppInitCfgParams(&appDcanCfgPrms);
    DCANAppInitRxParams(&appDcanRxCfgPrms);

    /*Unlock the Crossbar register */
    PlatformUnlockMMR();

    /* Clock Configuration. */
    PlatformDCAN1PrcmEnable();

    /* Perform the DCAN pinmux - RX pin as Driver OFF / GPIO pinmux. */
    PlatformDCAN1RXSetPinMux();

    /* Initialize the DCAN message RAM. */
    PlatformDcanMessageRamInit(0);

    /* Perform the DCAN pinmux. */
    PlatformDCAN1SetPinMux();

#if defined (BUILD_M4)
    enableIPU1Unicache();
#endif

    /* Register Crossbars and IRQ numbers */
    DCANAppConfigIntr(mainMenuOption);

    /* Reset the DCAN IP */
    retVal = DCANReset(DCAN_APP_INST, timeOut);
    if (retVal == STW_SOK)
    {
        /* Set the desired bit rate based on input clock */
        DCANSetMode(DCAN_APP_INST, DCAN_MODE_INIT);
        errStatus = DCANCalculateBitTimeParams(DCAN_APP_INPUT_CLK,
                                               DCAN_APP_BIT_RATE,
                                               &appDcanBitTimePrms);
        if (errStatus != DCAN_BIT_RATE_ERR_NONE)
        {
            return errStatus;
        }
        DCANSetBitTime(DCAN_APP_INST, &appDcanBitTimePrms);
        DCANSetMode(DCAN_APP_INST, DCAN_MODE_NORMAL);

        /* Configure DCAN controller */
        DCANConfig(DCAN_APP_INST, &appDcanCfgPrms);
    }

    /* Configuring FIFO Buffer of depth DCAN_APP_FIFO_BUF_DEPTH*/
    for (fifoBufIdx = DCAN_APP_RX_FIFO_BUF_START_IDX;
         fifoBufIdx < (DCAN_APP_RX_FIFO_BUF_START_IDX + DCAN_APP_FIFO_BUF_DEPTH);
         fifoBufIdx++)
    {
        /*
         * Enable message object interrupt to route interrupt line 1
         */
        DCANConfigIntrMux(DCAN_APP_INST, DCAN_INTR_LINE_NUM_0, fifoBufIdx);

        if (fifoBufIdx ==
            ((DCAN_APP_TX_FIFO_BUF_START_IDX + DCAN_APP_FIFO_BUF_DEPTH) - 1))
        {
            appDcanRxCfgPrms.fifoEOBFlag = TRUE;
        }
        else
        {
            appDcanRxCfgPrms.fifoEOBFlag = FALSE;
        }
        if (retVal == STW_SOK)
        {
            /* Wait for interface to become free */
            DCANAppWaitForIfReg(DCAN_APP_INST, DCAN_APP_RX_IF_REG);
            retVal = DCANConfigMsgObj(DCAN_APP_INST,
                                      fifoBufIdx,
                                      DCAN_APP_RX_IF_REG,
                                      &appDcanRxCfgPrms);
            /* Wait for config to be copied to internal message RAM */
            DCANAppWaitForIfReg(DCAN_APP_INST, DCAN_APP_RX_IF_REG);
        }
    }

    memset(&appDcanRxPrms, 0, sizeof (dcanRxParams_t));

    UARTPuts("\nWaiting for message from DCAN1 TX....\n", -1);

    for (msgCnt = 0; msgCnt < expectedNumMsg; msgCnt++)
    {
        rxMsgStatus = 0;
        gRxDoneFlag = 0;
        gErrStatus  = 0;

        if (msgCnt == 0)
        {
            if (retVal == STW_SOK)
            {
                /* Wait for Receive / Error interrupt */
                while ((gRxDoneFlag == 0) && (gErrStatus == 0)) ;
                /* Check for whether error is occured or not */
                if (gErrStatus != 0)
                {
                    retVal = STW_EFAIL;
                    break;
                }
            }
        }
        else
        {
            if (gErrStatus != 0)
            {
                retVal = STW_EFAIL;
                break;
            }
        }

        if (retVal == STW_SOK)
        {
            while (!rxMsgStatus)
            {
                /* check for msg is arrived or not */
                rxMsgStatus =
                    DCANHasRxMsgArrived(DCAN_APP_INST, gMsgObj[gRxAppCnt]);
            }
            if (rxMsgStatus == TRUE)
            {
                /* Wait for interface to become free */
                DCANAppWaitForIfReg(DCAN_APP_INST, DCAN_APP_RX_IF_REG);
                retVal = DCANGetData(DCAN_APP_INST,
                                     gMsgObj[gRxAppCnt++],
                                     DCAN_APP_RX_IF_REG,
                                     &appDcanRxPrms,
                                     timeOut);
                if (gRxAppCnt == 20)
                    gRxAppCnt = 0;
            }
        }
        if (retVal == STW_SOK)
        {
            /* Check if sent data is lost or not */
            if (appDcanRxPrms.msgLostFlag == TRUE)
            {
                msgLstErrCnt++;
            }

            /* Check if sent data has been received */
            if (retVal == STW_SOK)
            {
                /* Check if sent data has been received */
                if (appDcanRxPrms.dataLength == expectedDataLength)
                {
                    dataLength = 0U;
                    while (dataLength < appDcanRxPrms.dataLength)
                    {
                        if (appDcanRxPrms.msgData[dataLength] !=
                            expectedDataBuffer[dataLength])
                        {
                            retVal = STW_EFAIL;
                            dataMissMatchErrCnt++;
                        }
                        dataLength++;
                    }
                }
                else
                {
                    retVal = STW_EFAIL;
                    dataMissMatchErrCnt++;
                }
            }
        }
    }
#if defined (BUILD_M4)
    disableIPU1Unicache();
#endif

    if (((msgLstErrCnt == 0) &&
         (dataMissMatchErrCnt == 0)) && (retVal == STW_SOK))
    {
        UARTPuts("\nDCAN -- Board to Board Test (RX) Passed!! \n", -1);
    }
    else
    {
        UARTPuts("\nDCAN -- Board to Board Test (RX) Failed!! \n", -1);
    }

    return retVal;
}

static void DCANAppInitCfgParams(dcanCfgParams_t *pDcanCfgPrms)
{
    /*Intialize DCAN Config Params*/
    pDcanCfgPrms->parityEnable          = FALSE;
    pDcanCfgPrms->autoRetransmitDisable = TRUE;
    pDcanCfgPrms->autoBusOnEnable       = FALSE;
    pDcanCfgPrms->testModeEnable        = FALSE;
    pDcanCfgPrms->intrLine0Enable       = TRUE;
    pDcanCfgPrms->intrLine1Enable       = FALSE;
    pDcanCfgPrms->errIntrEnable         = TRUE;
    pDcanCfgPrms->stsChangeIntrEnable   = TRUE;
#ifdef TDA3XX_FAMILY_BUILD
    pDcanCfgPrms->eccModeEnable = FALSE;
#endif
    pDcanCfgPrms->autoBusOnTimerVal = FALSE;
    pDcanCfgPrms->testMode          = DCAN_TEST_MODE_EXT_LPBACK;
    pDcanCfgPrms->if1DmaEnable      = FALSE;
    pDcanCfgPrms->if2DmaEnable      = FALSE;
    pDcanCfgPrms->if3DmaEnable      = FALSE;
    pDcanCfgPrms->ramAccessEnable   = FALSE;
}

static void DCANAppInitTxParams(dcanMsgObjCfgParams_t *pDcanTxCfgPrms,
                                dcanTxParams_t        *pDcanTxPrms,
                                uint32_t               dataLength,
                                uint8_t               *dataBuffer)
{
    /*Intialize DCAN tx Config Params*/
    pDcanTxCfgPrms->xIdFlagMask       = 0x1;
    pDcanTxCfgPrms->dirMask           = 0x1;
    pDcanTxCfgPrms->msgIdentifierMask = 0x1FFFFFFF;

    pDcanTxCfgPrms->msgValid      = TRUE;
    pDcanTxCfgPrms->xIdFlag       = DCAN_APP_MSG_ID;
    pDcanTxCfgPrms->direction     = DCAN_DIR_TX;
    pDcanTxCfgPrms->msgIdentifier = DCAN_APP_MSG_IDENTIFIER;
    pDcanTxCfgPrms->uMaskUsed     = TRUE;
    pDcanTxCfgPrms->intEnable     = TRUE;
    pDcanTxCfgPrms->remoteEnable  = FALSE;

    /*Intialize DCAN Tx transfer Params */
    pDcanTxPrms->dataLength = dataLength;
    pDcanTxPrms->msgData[0] = dataBuffer[0];
    pDcanTxPrms->msgData[1] = dataBuffer[1];
    pDcanTxPrms->msgData[2] = dataBuffer[2];
    pDcanTxPrms->msgData[3] = dataBuffer[3];
    pDcanTxPrms->msgData[4] = dataBuffer[4];
    pDcanTxPrms->msgData[5] = dataBuffer[5];
    pDcanTxPrms->msgData[6] = dataBuffer[6];
    pDcanTxPrms->msgData[7] = dataBuffer[7];
}

static void DCANAppInitRxParams(dcanMsgObjCfgParams_t *pDcanRxCfgPrms)
{
    /*Intialize DCAN Rx Config Params*/
    pDcanRxCfgPrms->xIdFlagMask       = 0x1;
    pDcanRxCfgPrms->msgIdentifierMask = 0x1FFFFFFF;
    pDcanRxCfgPrms->dirMask           = 0x1;

    pDcanRxCfgPrms->msgValid      = TRUE;
    pDcanRxCfgPrms->xIdFlag       = DCAN_APP_MSG_ID;
    pDcanRxCfgPrms->direction     = DCAN_DIR_RX;
    pDcanRxCfgPrms->msgIdentifier = DCAN_APP_MSG_IDENTIFIER;

    pDcanRxCfgPrms->uMaskUsed    = TRUE;
    pDcanRxCfgPrms->intEnable    = TRUE;
    pDcanRxCfgPrms->remoteEnable = FALSE;
}

static uint32_t DCANCalculateBitTimeParams(uint32_t             clkFreq,
                                           uint32_t             bitRate,
                                           dcanBitTimeParams_t *pBitTimePrms)
{
    uint32_t errVal;
    dcanBitTimeParamsLocal_t bitTimePrms;

    bitTimePrms.samplePnt           = 0U;
    bitTimePrms.timeQuanta          = 0U;
    bitTimePrms.propSeg             = 0U;
    bitTimePrms.phaseSeg1           = 0U;
    bitTimePrms.phaseSeg2           = 0U;
    bitTimePrms.syncJumpWidth       = 0U;
    bitTimePrms.bitRatePrescaler    = 0U;
    bitTimePrms.tseg1Min            = 1U;
    bitTimePrms.tseg1Max            = 16U;
    bitTimePrms.tseg2Min            = 1U;
    bitTimePrms.tseg2Max            = 8U;
    bitTimePrms.syncJumpWidthMax    = 4U;
    bitTimePrms.bitRatePrescalerMin = 1U;
    bitTimePrms.bitRatePrescalerMax = 1024U;
    bitTimePrms.bitRatePrescalerInc = 1U;
    bitTimePrms.bitRate             = bitRate;

    errVal = DCANAppBitTimeCalculator(&bitTimePrms, clkFreq);

    pBitTimePrms->baudRatePrescaler =
        ((bitTimePrms.bitRatePrescaler - 1U) & DCAN_BTR_BRP_MASK);
    pBitTimePrms->syncJumpWidth = bitTimePrms.syncJumpWidth;
    pBitTimePrms->timeSegment1  =
        (bitTimePrms.phaseSeg1 + bitTimePrms.propSeg - 1U);
    pBitTimePrms->timeSegment2         = (bitTimePrms.phaseSeg2 - 1U);
    pBitTimePrms->baudRatePrescalerExt =
        (((bitTimePrms.bitRatePrescaler -
           1U) & DCAN_APP_EXTRACT_BRPE_VAL) >> DCAN_APP_BRPE_SHIFT);

    return (errVal);
}

static uint32_t DCANAppBitTimeCalculator(
    dcanBitTimeParamsLocal_t *pBitTimeParam,
    uint32_t                  clkFreq)
{
    int32_t  samplePnt = 0U, samplePntErr = 1000U, tsegAll = 0U;
    int32_t  tseg      = 0U, tseg1 = 0U, tseg2 = 0U;
    int32_t  brp       = 0U, samplePntNew = 0U, bestTseg = 0U, bestBrp = 0U;
    long     err       = 0U, bestErr = 1000000000U;
    uint32_t errVal    = DCAN_BIT_RATE_ERR_NONE;
    uint32_t rate      = 0U, timeQuanta = 0U;

    if (pBitTimeParam->bitRate > 800000U)
    {
        samplePnt = 750U;
    }
    else if (pBitTimeParam->bitRate > 500000U)
    {
        samplePnt = 800U;
    }
    else
    {
        samplePnt = 875U;
    }

    for (tseg = (pBitTimeParam->tseg1Max + pBitTimeParam->tseg2Max) * 2 + 1;
         tseg >= (pBitTimeParam->tseg1Min + pBitTimeParam->tseg2Min) * 2;
         tseg--)
    {
        tsegAll = 1 + tseg / 2;

        /* Compute all possible tseg choices (tseg = tseg1+tseg2) */
        brp = clkFreq / (tsegAll * pBitTimeParam->bitRate) + tseg % 2;

        /* chose brp step which is possible in system */
        brp = (brp / pBitTimeParam->bitRatePrescalerInc) *
              pBitTimeParam->bitRatePrescalerInc;

        if ((brp < pBitTimeParam->bitRatePrescalerMin) ||
            (brp > pBitTimeParam->bitRatePrescalerMax))
        {
            continue;
        }

        rate = clkFreq / (brp * tsegAll);
        err  = pBitTimeParam->bitRate - rate;

        /* tseg brp biterror */
        if (err < 0)
        {
            err = -err;
        }
        if (err > bestErr)
        {
            continue;
        }
        bestErr = err;
        if (err == 0)
        {
            samplePntNew = DCANAppUpdateSamplePnt(pBitTimeParam,
                                                  samplePnt,
                                                  tseg / 2,
                                                  &tseg1,
                                                  &tseg2);

            err = samplePnt - samplePntNew;
            if (err < 0)
            {
                err = -err;
            }
            if (err > samplePntErr)
            {
                continue;
            }
            samplePntErr = err;
        }
        bestTseg = tseg / 2;
        bestBrp  = brp;
        if (err == 0)
        {
            break;
        }
    }

    if (bestErr)
    {
        /* Error in one-tenth of a percent */
        err = (bestErr * 1000) / pBitTimeParam->bitRate;
        if (err > DCAN_APP_CALC_MAX_ERROR)
        {
            errVal = DCAN_BIT_RATE_ERR_MAX;
        }
        else
        {
            errVal = DCAN_BIT_RATE_ERR_WARN;
        }
    }

    /* real sample point */
    pBitTimeParam->samplePnt = DCANAppUpdateSamplePnt(pBitTimeParam,
                                                      samplePnt,
                                                      bestTseg,
                                                      &tseg1,
                                                      &tseg2);

    /* Calculate the time quanta value. */
    timeQuanta = bestBrp * 1000000000UL;

    pBitTimeParam->timeQuanta       = timeQuanta;
    pBitTimeParam->propSeg          = tseg1 / 2;
    pBitTimeParam->phaseSeg1        = tseg1 - pBitTimeParam->propSeg;
    pBitTimeParam->phaseSeg2        = tseg2;
    pBitTimeParam->syncJumpWidth    = 1;
    pBitTimeParam->bitRatePrescaler = bestBrp;

    /* Real bit-rate */
    pBitTimeParam->bitRate =
        clkFreq / (pBitTimeParam->bitRatePrescaler * (tseg1 + tseg2 + 1));

    return (errVal);
}

static int32_t DCANAppUpdateSamplePnt(dcanBitTimeParamsLocal_t *pBitTimeParam,
                                      int32_t                   samplePnt,
                                      int32_t                   tseg,
                                      int32_t                  *tseg1,
                                      int32_t                  *tseg2)
{
    *tseg2 = tseg + 1 - (samplePnt * (tseg + 1)) / 1000;

    if (*tseg2 < pBitTimeParam->tseg2Min)
    {
        *tseg2 = pBitTimeParam->tseg2Min;
    }

    if (*tseg2 > pBitTimeParam->tseg2Max)
    {
        *tseg2 = pBitTimeParam->tseg2Max;
    }

    *tseg1 = tseg - *tseg2;

    if (*tseg1 > pBitTimeParam->tseg1Max)
    {
        *tseg1 = pBitTimeParam->tseg1Max;
        *tseg2 = tseg - *tseg1;
    }
    return (1000 * (tseg + 1 - *tseg2) / (tseg + 1));
}

static void DCANAppConfigIntr(char mainMenuOption)
{
#if defined (BUILD_M4)
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_IPU1,
                   XBAR_INST_IPU1_IRQ_28, DCAN1_IRQ_INT0);

    Intc_Init();
    Intc_IntEnable(0);

    if (DCAN_TX_TEST == mainMenuOption)
    {
        Intc_IntRegister(28, (IntrFuncPtr) DCANAppTxInt0Isr, (void *) 0);
    }
    if (DCAN_RX_TEST == mainMenuOption)
    {
        Intc_IntRegister(28, (IntrFuncPtr) DCANAppRxInt0Isr, (void *) 0);
    }

    Intc_IntPrioritySet(28, 1, 0);

    Intc_SystemEnable(28);
#elif defined (BUILD_A15)
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_MPUSS,
                   XBAR_INST_MPU_IRQ_77, DCAN1_IRQ_INT0);

    Intc_Init();
    Intc_IntEnable(0);

    if (DCAN_TX_TEST == mainMenuOption)
    {
        Intc_IntRegister(77, (IntrFuncPtr) DCANAppTxInt0Isr, (void *) 0);
    }
    if (DCAN_RX_TEST == mainMenuOption)
    {
        Intc_IntRegister(77, (IntrFuncPtr) DCANAppRxInt0Isr, (void *) 0);
    }

    Intc_IntPrioritySet(77, 1, 0);

    Intc_SystemEnable(77);
#endif
}

static void DCANAppTxInt0Isr()
{
    uint32_t intrStatus, errStatus;
    uint32_t msgObj;

    DCANAppWaitForIfReg(DCAN_APP_INST, DCAN_APP_TX_IF_REG);
    intrStatus = DCANGetIntrStatus(DCAN_APP_INST, DCAN_INTR_LINE_NUM_0);
    if (intrStatus == DCAN_ERR_STS_UPDATED)
    {
        DCANAppWaitForIfReg(DCAN_APP_INST, DCAN_APP_TX_IF_REG);
        errStatus = DCANGetErrStatus(DCAN_APP_INST);
        if (errStatus != DCAN_ES_MASK_TX_OK)
        {
            gErrStatus = errStatus;
        }
        else
        {
            msgObj = DCANGetIntrStatus(DCAN_APP_INST, DCAN_INTR_LINE_NUM_0);
            if ((DCANIsMsgObjIntrPending(DCAN_APP_INST, msgObj)) == TRUE)
            {
                DCANAppWaitForIfReg(DCAN_APP_INST, DCAN_APP_TX_IF_REG);
                /* Clear the interrupts  of MSG_OBJ 1 for transmit */
                DCANIntrClearStatus(DCAN_APP_INST, msgObj, DCAN_APP_TX_IF_REG);
            }
        }
    }
}

static void DCANAppRxInt0Isr()
{
    uint32_t intrStatus, errStatus;
    uint32_t msgObj;

    DCANAppWaitForIfReg(DCAN_APP_INST, DCAN_APP_RX_IF_REG);
    intrStatus = DCANGetIntrStatus(DCAN_APP_INST, DCAN_INTR_LINE_NUM_0);
    if (intrStatus == DCAN_ERR_STS_UPDATED)
    {
        DCANAppWaitForIfReg(DCAN_APP_INST, DCAN_APP_RX_IF_REG);
        errStatus = DCANGetErrStatus(DCAN_APP_INST);
        if (errStatus != DCAN_ES_MASK_RX_OK)
        {
            gErrStatus = errStatus;
        }
        else
        {
            msgObj = DCANGetIntrStatus(DCAN_APP_INST, DCAN_INTR_LINE_NUM_0);
            gMsgObj[gIsrCnt++] = msgObj;
            if (gIsrCnt == 20)
                gIsrCnt = 0;
            if ((DCANIsMsgObjIntrPending(DCAN_APP_INST, msgObj)) == TRUE)
            {
                DCANAppWaitForIfReg(DCAN_APP_INST, DCAN_APP_RX_IF_REG);
                /* Clear the interrupts  of MSG_OBJ 2 for Receive */
                DCANIntrClearStatus(DCAN_APP_INST, msgObj, DCAN_APP_RX_IF_REG);
                gRxDoneFlag = 1;
            }
        }
    }
}

static void DCANAppWaitForIfReg(uint32_t baseAddr, uint32_t ifRegNum)
{
    do
    {
        if (TRUE != DCANIsIfRegBusy(baseAddr, ifRegNum))
        {
            break;
        }
    }
    while (1);
}

static void mainMenu(char *option)
{
    while (1)
    {
        UARTPuts("\n\n**** DCAN EVM LOOPBACK TEST ****", -1);
        UARTPuts("\nMenu:", -1);
        UARTPuts("\n1. DCAN Transmit test", -1);
        UARTPuts("\n2. DCAN Receive test", -1);
        UARTPuts("\nx. Exit", -1);
        UARTPuts("\nSelect DCAN EVM LOOPBACK TEST : ", -1);

        /* Get option */
        UARTGets(option, 1);

        if (DCAN_TX_TEST == *option || DCAN_RX_TEST == *option ||
            EXIT(*option))
        {
            break;
        }
        else
        {
            UARTPuts("\nEnter Valid option\n", -1);
        }
    }
}

static void mainSubMenu(char      mainMenuOption,
                        uint32_t *dataLength,
                        uint8_t  *dataBuffer,
                        uint32_t *numMsg)
{
    int32_t i;
    while (1)
    {
        if (mainMenuOption == DCAN_TX_TEST)
        {
            UARTPuts("\nEnter number of messages to be transmitted from:",
                     -1);
            *numMsg = UARTGetNum();

            UARTPuts("\nEnter the data length to be transmitted from 1 to 8:",
                     -1);
            *dataLength = UARTGetNum();

            UARTPuts("\nEnter the data sequence to be transmitted in Hex", -1);
            for (i = 0; i < *dataLength; i++)
            {
                UARTPuts("\ndataByte ", -1);
                UARTPutNum(i);
                UARTPuts("  :   ", -1);
                *dataBuffer = UARTGetHexNum();
                dataBuffer++;
            }
            break;
        }
        else if (mainMenuOption == DCAN_RX_TEST)
        {
            UARTPuts("\nEnter the expected number of messages to be received:",
                     -1);
            *numMsg = UARTGetNum();

            UARTPuts(
                "\nEnter the expected data length to be received from 1 to 8:",
                -1);
            *dataLength = UARTGetNum();
            UARTPuts(
                "\nEnter the expected data sequence to be received in Hex",
                -1);
            for (i = 0; i < *dataLength; i++)
            {
                UARTPuts("\ndataByte ", -1);
                UARTPutNum(i);
                UARTPuts("  :   ", -1);
                *dataBuffer = UARTGetHexNum();
                dataBuffer++;
            }
            break;
        }
        else
        {
            UARTPuts("\nEnter Valid option\n", -1);
        }
    }
}

static uint32_t read32KTimer(void)
{
    uint32_t timerVal = 0U;

    /* Read the counter value for 32 KHz SoC Synchronous Timer */
    timerVal = HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR);

    return timerVal;
}

#if defined (BUILD_M4)
static void enableIPU1Unicache(void)
{
    HW_WR_REG32(0x40000004, 0x0000001F);
}

static void disableIPU1Unicache(void)
{
    HW_WR_REG32(0x40000004, 0x0000001C);
}

#endif

static uint32_t dcanGetTheoriticalMax(uint32_t dataLength,
                                      uint32_t msgId,
                                      uint32_t bitRate)
{
    uint32_t theoriticalMax;
    uint32_t numBitsPerMsg;

    if (msgId == DCAN_XID_11_BIT)
    {
        /*Data field : (dataLength * 8) */
        numBitsPerMsg = DCAN_APP_STD_FIXED_FRAME_FMT_LENGTH + (dataLength * 8);
    }
    else
    {
        /*Data field : (dataLength * 8) */
        numBitsPerMsg = DCAN_APP_EXT_FIXED_FRAME_FMT_LENGTH + (dataLength * 8);
    }
    theoriticalMax = bitRate / numBitsPerMsg;

    return theoriticalMax;
}

