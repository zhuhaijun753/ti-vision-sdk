/**
 *  \file     dcan_loopback_app_main.c
 *
 *  \brief    This file contains DCAN external loopback test mode
 *
 *  \details  DCAN external loopback which tests the internal feedback
 *            from Tx output to Rx input. Transmitted messages are treated as
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
#include "pm/pm_types.h"

/* Application header files */
#include "dcan.h"

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

/** \brief DCAN bit time calculation maximum error value. */
#define DCAN_APP_CALC_MAX_ERROR         (50U)

/** \brief Macro used to extract bit rate prescaler value. */
#define DCAN_APP_EXTRACT_BRPE_VAL       (0x3C0U)

/** \brief Shift value used for bit rate prescaler. */
#define DCAN_APP_BRPE_SHIFT             (6U)

/** \brief DCAN instance used */
#define DCAN1_APP_INST                   (SOC_DCAN1_BASE)
#define DCAN2_APP_INST                   (SOC_DCAN2_BASE)

/** \brief DCAN input clock - 20MHz */
#define DCAN_APP_INPUT_CLK              (20000000U)
/** \brief DCAN output bit rate - 1MHz */
#define DCAN_APP_BIT_RATE               (1000000U)

/** \brief DCAN TX message object used */
#define DCAN_TX_MSG_OBJ                 (0x1U)
/** \brief DCAN RX message object used */
#define DCAN_RX_MSG_OBJ                 (0x2U)

/** \brief DCAN TX interface register used */
#define DCAN_APP_TX_IF_REG              (DCAN_IF_REG_NUM_1)
/** \brief DCAN RX interface register used */
#define DCAN_APP_RX_IF_REG              (DCAN_IF_REG_NUM_2)

/** \brief Offset of DRM SUSPEND_CTRL1 register */
#define DRM_SUSPEND_CTRL1               (0x204)
/** \brief DRM_SUSPEND_CTRL1 is mapped to DCAN1 Suspend Output line */
#define DRM_SUSPEND_CTRL_DCAN1          (SOC_I_DRM_BASE + DRM_SUSPEND_CTRL1)

/** \brief Offset of DRM SUSPEND_CTRL2 register */
#define DRM_SUSPEND_CTRL2               (0x208)
/** \brief DRM_SUSPEND_CTRL2 is mapped to DCAN2 Suspend Output line */
#define DRM_SUSPEND_CTRL_DCAN2          (SOC_I_DRM_BASE + DRM_SUSPEND_CTRL2)

/** \brief DRM SUSPEND Source as A15 */
#define DRM_SUSPEND_SRC_MPU_C0          (0x5)
/** \brief DRM SUSPEND Source as M4 */
#define DRM_SUSPEND_SRC_IPU1_C0         (0x3)

/** \brief DCAN Message Object */
#define DCAN_MSG_OBJ                    (0x1)

/** \brief DCAN Message Object RAM Address */
#define DCAN_MSG_OBJ_RAM_ADDR           ((SOC_DCAN1_MESSAGERAM_BASE) + \
                                         (DCAN_MSG_OBJ * DCAN_MSG_OBJ_SIZE))

#define DCAN_EXT_LOOPBACK_TEST      ('1')
#define DCAN_INT_LOOPBACK_TEST      ('2')
#define DCAN_ECC_TEST               ('3')
#define EXIT(opt)                   (('x' == opt) || ('X' == opt))

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

static void DCANAppConfigIntr(void);
static void DCANAppInt0Isr();

static uint32_t DCANAppBitTimeCalculator(
    dcanBitTimeParamsLocal_t *pBitTimeParam,
    uint32_t                  clkFreq);

static int32_t DCANAppUpdateSamplePnt(dcanBitTimeParamsLocal_t *pBitTimeParam,
                                      int32_t                   samplePnt,
                                      int32_t                   tseg,
                                      int32_t                  *tseg1,
                                      int32_t                  *tseg2);

static void DCANAppInitParams(dcanCfgParams_t       *pDcanCfgPrms,
                              dcanMsgObjCfgParams_t *pDcanTxCfgPrms,
                              dcanMsgObjCfgParams_t *pDcanRxCfgPrms,
                              dcanTxParams_t        *pDcanTxPrms);

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

static void mainMenu(char *option);
#ifdef TDA3XX_FAMILY_BUILD
static int32_t dcanEccTest(void);
#endif
static int32_t dcanLoopbackTest(void);

volatile unsigned char gTxDoneFlag = 0, gRxDoneFlag = 0;
char     gMainMenuOption;
uint32_t gDcanAppInstance;

int main(void)
{
    volatile uint32_t testDone = 1;
    int32_t           retVal   = STW_SOK;

    PlatformUartConsoleSetPinMux();
    UARTStdioInit();

    while (1)
    {
        mainMenu(&gMainMenuOption);
        if ((DCAN_EXT_LOOPBACK_TEST == gMainMenuOption) ||
            (DCAN_INT_LOOPBACK_TEST == gMainMenuOption))
        {
            if (DCAN_EXT_LOOPBACK_TEST == gMainMenuOption)
            {
                gDcanAppInstance = DCAN1_APP_INST;
            }
            else
            {
                gDcanAppInstance = DCAN2_APP_INST;
            }
            retVal = dcanLoopbackTest();
        }
#ifdef TDA3XX_FAMILY_BUILD
        else if (DCAN_ECC_TEST == gMainMenuOption)
        {
            gDcanAppInstance = DCAN1_APP_INST;
            retVal           = dcanEccTest();
        }
#endif
        else
        {
            UARTPuts("\nDCAN Application Test exiting...", -1);
            break;
        }
    }
    while (testDone) ;
    return retVal;
}

#ifdef TDA3XX_FAMILY_BUILD
static int32_t dcanEccTest(void)
{
    int32_t               retVal    = STW_SOK;
    int32_t               errStatus = STW_SOK;
    dcanCfgParams_t       appDcanCfgPrms;
    dcanMsgObjCfgParams_t appDcanTxCfgPrms;
    dcanMsgObjCfgParams_t appDcanRxCfgPrms;
    dcanTxParams_t        appDcanTxPrms;
    dcanBitTimeParams_t   appDcanBitTimePrms;
    uint32_t              timeOut = 100U;
    int32_t              *pMsgObj;
    uint32_t              msgObj;
    dcanRxParams_t        appDcanRxPrms;

    UARTPuts("\nDCAN ECC Test App\n", -1);

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
    DCANAppInitParams(&appDcanCfgPrms,
                      &appDcanTxCfgPrms,
                      &appDcanRxCfgPrms,
                      &appDcanTxPrms);

    /*Unlock the Crossbar register */
    PlatformUnlockMMR();

    /* Clock Configuration. */
    PlatformDCAN1PrcmEnable();

    /* Perform the DCAN pinmux. */
    PlatformDCAN1SetPinMux();

    /* Initialize the DCAN message RAM. */
    PlatformDcanMessageRamInit(0);

    /* Reset the DCAN IP */
    retVal = DCANReset(gDcanAppInstance, timeOut);
    if (retVal == STW_SOK)
    {
        /* Set the desired bit rate based on input clock */
        DCANSetMode(gDcanAppInstance, DCAN_MODE_INIT);
        errStatus = DCANCalculateBitTimeParams(DCAN_APP_INPUT_CLK,
                                               DCAN_APP_BIT_RATE,
                                               &appDcanBitTimePrms);
        if (errStatus != DCAN_BIT_RATE_ERR_NONE)
        {
            return errStatus;
        }
        DCANSetBitTime(gDcanAppInstance, &appDcanBitTimePrms);
        DCANSetMode(gDcanAppInstance, DCAN_MODE_NORMAL);

        /* Configure DCAN controller */
        DCANConfig(gDcanAppInstance, &appDcanCfgPrms);
    }
    if (retVal == STW_SOK)
    {
        /* Wait for interface to become free */
        DCANAppWaitForIfReg(gDcanAppInstance, DCAN_APP_TX_IF_REG);
        retVal = DCANConfigMsgObj(gDcanAppInstance,
                                  DCAN_TX_MSG_OBJ,
                                  DCAN_APP_TX_IF_REG,
                                  &appDcanTxCfgPrms);
        /* Wait for config to be copied to internal message RAM */
        DCANAppWaitForIfReg(gDcanAppInstance, DCAN_APP_TX_IF_REG);
    }

    if (retVal == STW_SOK)
    {
        /* Wait for interface to become free */
        DCANAppWaitForIfReg(gDcanAppInstance, DCAN_APP_TX_IF_REG);
        retVal = DCANTransmitData(gDcanAppInstance,
                                  DCAN_TX_MSG_OBJ,
                                  DCAN_APP_TX_IF_REG,
                                  &appDcanTxPrms,
                                  timeOut);
        /* Wait for config to be copied to internal message RAM */
        DCANAppWaitForIfReg(gDcanAppInstance, DCAN_APP_TX_IF_REG);
    }

    /* Disable SECDED to corrupt the RAM */
    DCANParityEnable(gDcanAppInstance, FALSE);
    pMsgObj = (int32_t *) (DCAN_MSG_OBJ_RAM_ADDR);

    /* Enable ECCDIAG mode */
    DCANEccDiagModeEnable(gDcanAppInstance, TRUE);
    /* RDA mode is enabled to ACCESS the MessageRAM */
    DCANTestModeEnable(gDcanAppInstance, TRUE, DCAN_TEST_RDA_MASK);
    /* Corrupting the data in Message RAM in RDA Mode :
     * as 0xFFFF5AA4 instead of 0xFFFF5AA5 which introduces single bit error.
     */
    *pMsgObj = (*pMsgObj & 0xFFFFFFFE);
    /* RDA mode is disabled to ACCESS the MessageRAM */
    DCANTestModeEnable(gDcanAppInstance, FALSE, DCAN_TEST_RDA_MASK);
    /* Enable SECDED */
    DCANParityEnable(gDcanAppInstance, TRUE);

    /* Wait for interface to become free */
    DCANAppWaitForIfReg(gDcanAppInstance, DCAN_APP_TX_IF_REG);

    retVal = DCANGetData(gDcanAppInstance,
                         DCAN_TX_MSG_OBJ,
                         DCAN_APP_RX_IF_REG,
                         &appDcanRxPrms,
                         timeOut);
    /* Wait for interface to become free */
    DCANAppWaitForIfReg(gDcanAppInstance, DCAN_APP_TX_IF_REG);

    /* Check for whether single bit error is detected */
    msgObj = DCANGetMsgObjBitErrDetected(gDcanAppInstance);

    DCANEccDiagModeEnable(gDcanAppInstance, FALSE);
    DCANParityEnable(gDcanAppInstance, FALSE);

    if (msgObj != DCAN_TX_MSG_OBJ)
    {
        UARTPuts("\nDCAN -- ECC test Failed!! \n", -1);
    }
    else
    {
        UARTPuts("\nDCAN -- ECC test Passed!! \n", -1);
    }

    return retVal;
}

#endif

static int32_t dcanLoopbackTest(void)
{
    int32_t               retVal    = STW_SOK;
    int32_t               errStatus = STW_SOK;
    dcanCfgParams_t       appDcanCfgPrms;
    dcanMsgObjCfgParams_t appDcanTxCfgPrms;
    dcanMsgObjCfgParams_t appDcanRxCfgPrms;
    dcanTxParams_t        appDcanTxPrms;
    dcanBitTimeParams_t   appDcanBitTimePrms;
    dcanRxParams_t        appDcanRxPrms;
    uint32_t              timeOut             = 100U;
    uint32_t              dataLength          = 0U;
    uint32_t              msgLstErrCnt        = 0U;
    uint32_t              dataMissMatchErrCnt = 0U;

    gTxDoneFlag = 0;
    gRxDoneFlag = 0;

    if (gDcanAppInstance == DCAN1_APP_INST)
    {
        UARTPuts(
            "\nDCAN External Loopback Test App: DCAN1 MSG OBJ 1 (TX) to DCAN1 MSG OBJ 2 (RX)\n",
            -1);

        retVal = PlatformDcanClkConfig(0);
        if (retVal != PM_SUCCESS)
        {
            UARTPuts("\nControl module & Dcan Clock Configure fails", -1);
        }

#if defined (BUILD_M4)
        /* DRM_SUSPEND_CTRL_DCAN1 - SUSPEND_SEL(Suspend source selection) as
         * IPU1_C0
         * & SENS_CTRL(Sensitivity control) as 1 means suspend signal must reach
         * the peripheral-IP  */
        HW_WR_REG32(DRM_SUSPEND_CTRL_DCAN1,
                    ((DRM_SUSPEND_SRC_IPU1_C0 << 4) | 0x1));
#elif defined (BUILD_A15)
        /* DRM_SUSPEND_CTRL_DCAN1 - SUSPEND_SEL(Suspend source selection) as
         * MPU_C0
         * & SENS_CTRL(Sensitivity control) as 1 means suspend signal must reach
         * the peripheral-IP  */
        HW_WR_REG32(DRM_SUSPEND_CTRL_DCAN1,
                    ((DRM_SUSPEND_SRC_MPU_C0 << 4) | 0x1));
#endif
    }
    else
    {
        UARTPuts(
            "\nDCAN Internal Loopback Test App: DCAN2 MSG OBJ 1 (TX) to DCAN2 MSG OBJ 2 (RX)\n",
            -1);

        retVal = PlatformDcanClkConfig(1);
        if (retVal != PM_SUCCESS)
        {
            UARTPuts("\nControl module & Dcan Clock Configure fails", -1);
        }

#if defined (BUILD_M4)
        /* DRM_SUSPEND_CTRL_DCAN2 - SUSPEND_SEL(Suspend source selection) as
         * IPU1_C0 & SENS_CTRL(Sensitivity control) as 1 means suspend signal
         *  must reach the peripheral-IP  */
        HW_WR_REG32(DRM_SUSPEND_CTRL_DCAN2,
                    ((DRM_SUSPEND_SRC_IPU1_C0 << 4) | 0x1));
#elif defined (BUILD_A15)
        /* DRM_SUSPEND_CTRL_DCAN2 - SUSPEND_SEL(Suspend source selection) as
         * MPU_C0 & SENS_CTRL(Sensitivity control) as 1 means suspend signal
         * must reach the peripheral-IP  */
        HW_WR_REG32(DRM_SUSPEND_CTRL_DCAN2,
                    ((DRM_SUSPEND_SRC_MPU_C0 << 4) | 0x1));
#endif
    }
    DCANAppInitParams(&appDcanCfgPrms,
                      &appDcanTxCfgPrms,
                      &appDcanRxCfgPrms,
                      &appDcanTxPrms);

    /*Unlock the Crossbar register */
    PlatformUnlockMMR();

    if (gDcanAppInstance == DCAN1_APP_INST)
    {
        /* Clock Configuration. */
        PlatformDCAN1PrcmEnable();

        /* Perform the DCAN pinmux - RX pin as Driver OFF / GPIO pinmux. */
        PlatformDCAN1RXSetPinMux();

        /* Initialize the DCAN message RAM. */
        PlatformDcanMessageRamInit(0);

        /* Perform the DCAN pinmux. */
        PlatformDCAN1SetPinMux();
    }
    else
    {
        /* Clock Configuration. */
        PlatformDCAN2PrcmEnable();

        /* Perform the DCAN pinmux - RX pin as Driver OFF / GPIO pinmux. */
        PlatformDCAN2RXSetPinMux();

        /* Initialize the DCAN message RAM. */
        PlatformDcanMessageRamInit(1);

        /* Perform the DCAN pinmux. */
        PlatformDCAN2SetPinMux();
    }

    /* Register Crossbars and IRQ numbers */
    DCANAppConfigIntr();
    /* Reset the DCAN IP */
    retVal = DCANReset(gDcanAppInstance, timeOut);
    if (retVal == STW_SOK)
    {
        /* Set the desired bit rate based on input clock */
        DCANSetMode(gDcanAppInstance, DCAN_MODE_INIT);
        errStatus = DCANCalculateBitTimeParams(DCAN_APP_INPUT_CLK,
                                               DCAN_APP_BIT_RATE,
                                               &appDcanBitTimePrms);
        if (errStatus != DCAN_BIT_RATE_ERR_NONE)
        {
            return errStatus;
        }
        DCANSetBitTime(gDcanAppInstance, &appDcanBitTimePrms);
        DCANSetMode(gDcanAppInstance, DCAN_MODE_NORMAL);

        /* Configure DCAN controller */
        DCANConfig(gDcanAppInstance, &appDcanCfgPrms);
        /*
         * Enable message object interrupt to route interrupt line 1
         */
        DCANConfigIntrMux(gDcanAppInstance, DCAN_INTR_LINE_NUM_0,
                          DCAN_TX_MSG_OBJ);
        DCANConfigIntrMux(gDcanAppInstance, DCAN_INTR_LINE_NUM_0,
                          DCAN_RX_MSG_OBJ);
    }
    if (retVal == STW_SOK)
    {
        /* Wait for interface to become free */
        DCANAppWaitForIfReg(gDcanAppInstance, DCAN_APP_RX_IF_REG);
        retVal = DCANConfigMsgObj(gDcanAppInstance,
                                  DCAN_RX_MSG_OBJ,
                                  DCAN_APP_RX_IF_REG,
                                  &appDcanRxCfgPrms);
        /* Wait for config to be copied to internal message RAM */
        DCANAppWaitForIfReg(gDcanAppInstance, DCAN_APP_RX_IF_REG);
    }

    if (retVal == STW_SOK)
    {
        /* Wait for interface to become free */
        DCANAppWaitForIfReg(gDcanAppInstance, DCAN_APP_TX_IF_REG);
        retVal = DCANConfigMsgObj(gDcanAppInstance,
                                  DCAN_TX_MSG_OBJ,
                                  DCAN_APP_TX_IF_REG,
                                  &appDcanTxCfgPrms);
        /* Wait for config to be copied to internal message RAM */
        DCANAppWaitForIfReg(gDcanAppInstance, DCAN_APP_TX_IF_REG);
    }

    if (retVal == STW_SOK)
    {
        /* Wait for interface to become free */
        DCANAppWaitForIfReg(gDcanAppInstance, DCAN_APP_TX_IF_REG);
        retVal = DCANTransmitData(gDcanAppInstance,
                                  DCAN_TX_MSG_OBJ,
                                  DCAN_APP_TX_IF_REG,
                                  &appDcanTxPrms,
                                  timeOut);
        /* Wait for config to be copied to internal message RAM */
        DCANAppWaitForIfReg(gDcanAppInstance, DCAN_APP_TX_IF_REG);
    }

    if (retVal == STW_SOK)
    {
        /* Wait for transmit interrupt */
        while (gTxDoneFlag == 0) ;
    }

    if (retVal == STW_SOK)
    {
        /* Wait for receive interrupt */
        while (gRxDoneFlag == 0) ;
    }

    if (retVal == STW_SOK)
    {
        /* Clear RX structure */
        memset(&appDcanRxPrms, 0, sizeof (appDcanRxPrms));

        /* Wait for interface to become free */
        DCANAppWaitForIfReg(gDcanAppInstance, DCAN_APP_RX_IF_REG);
        retVal = DCANGetData(gDcanAppInstance,
                             DCAN_RX_MSG_OBJ,
                             DCAN_APP_RX_IF_REG,
                             &appDcanRxPrms,
                             timeOut);
    }

    if (retVal == STW_SOK)
    {
        /* Check if sent data is lost or not */
        if (appDcanRxPrms.msgLostFlag == TRUE)
        {
            msgLstErrCnt++;
        }

        /* Check if sent data has been received */
        if (appDcanRxPrms.dataLength == appDcanTxPrms.dataLength)
        {
            while (dataLength < appDcanRxPrms.dataLength)
            {
                if (appDcanRxPrms.msgData[dataLength] !=
                    appDcanTxPrms.msgData[dataLength])
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
        }
    }
    if (((msgLstErrCnt == 0) &&
         (dataMissMatchErrCnt == 0)) && (retVal == STW_SOK))
    {
        if (gMainMenuOption == DCAN_EXT_LOOPBACK_TEST)
        {
            UARTPuts("\nDCAN -- External Loopback Testmode test Passed!! \n",
                     -1);
        }
        else
        {
            UARTPuts("\nDCAN -- Internal Loopback Testmode test Passed!! \n",
                     -1);
        }
    }
    else
    {
        if (gMainMenuOption == DCAN_EXT_LOOPBACK_TEST)
        {
            UARTPuts("\nDCAN -- External Loopback Testmode test Failed!! \n",
                     -1);
        }
        else
        {
            UARTPuts("\nDCAN -- Internal Loopback Testmode test Failed!! \n",
                     -1);
        }
    }
    return retVal;
}

static void DCANAppInitParams(dcanCfgParams_t       *pDcanCfgPrms,
                              dcanMsgObjCfgParams_t *pDcanTxCfgPrms,
                              dcanMsgObjCfgParams_t *pDcanRxCfgPrms,
                              dcanTxParams_t        *pDcanTxPrms)
{
    /*Intialize DCAN Config Params*/

    if (DCAN_ECC_TEST == gMainMenuOption)
    {
        pDcanCfgPrms->parityEnable    = TRUE;
        pDcanCfgPrms->intrLine0Enable = FALSE;
#ifdef TDA3XX_FAMILY_BUILD
        pDcanCfgPrms->eccModeEnable = TRUE;
#endif
        pDcanCfgPrms->testModeEnable = FALSE;
    }
    else
    {
        pDcanCfgPrms->parityEnable    = FALSE;
        pDcanCfgPrms->intrLine0Enable = TRUE;
#ifdef TDA3XX_FAMILY_BUILD
        pDcanCfgPrms->eccModeEnable = FALSE;
#endif
        pDcanCfgPrms->testModeEnable = TRUE;
        if (gMainMenuOption == DCAN_INT_LOOPBACK_TEST)
        {
            pDcanCfgPrms->testMode = DCAN_TEST_MODE_LPBACK;
        }
        else
        {
            pDcanCfgPrms->testMode = DCAN_TEST_MODE_EXT_LPBACK;
        }
    }

    pDcanCfgPrms->autoRetransmitDisable = TRUE;
    pDcanCfgPrms->autoBusOnEnable       = FALSE;
    pDcanCfgPrms->intrLine1Enable       = FALSE;
    pDcanCfgPrms->errIntrEnable         = FALSE;
    pDcanCfgPrms->stsChangeIntrEnable   = FALSE;
    pDcanCfgPrms->autoBusOnTimerVal     = FALSE;
    pDcanCfgPrms->if1DmaEnable          = FALSE;
    pDcanCfgPrms->if2DmaEnable          = FALSE;
    pDcanCfgPrms->if3DmaEnable          = FALSE;
    pDcanCfgPrms->ramAccessEnable       = FALSE;

    /*Intialize DCAN tx Config Params*/
    pDcanTxCfgPrms->xIdFlagMask       = 0x1;
    pDcanTxCfgPrms->dirMask           = 0x1;
    pDcanTxCfgPrms->msgIdentifierMask = 0x1FFFFFFF;

    pDcanTxCfgPrms->msgValid      = TRUE;
    pDcanTxCfgPrms->xIdFlag       = TRUE;
    pDcanTxCfgPrms->direction     = DCAN_DIR_TX;
    pDcanTxCfgPrms->msgIdentifier = 0xC1;

    pDcanTxCfgPrms->uMaskUsed    = TRUE;
    pDcanTxCfgPrms->intEnable    = TRUE;
    pDcanTxCfgPrms->remoteEnable = FALSE;
    pDcanTxCfgPrms->fifoEOBFlag  = TRUE;

    /*Intialize DCAN Rx Config Params*/
    pDcanRxCfgPrms->xIdFlagMask       = 0x1;
    pDcanRxCfgPrms->msgIdentifierMask = 0x1FFFFFFF;
    pDcanRxCfgPrms->dirMask           = 0x1;

    pDcanRxCfgPrms->msgValid      = TRUE;
    pDcanRxCfgPrms->xIdFlag       = TRUE;
    pDcanRxCfgPrms->direction     = DCAN_DIR_RX;
    pDcanRxCfgPrms->msgIdentifier = 0xC1;

    pDcanRxCfgPrms->uMaskUsed    = TRUE;
    pDcanRxCfgPrms->intEnable    = TRUE;
    pDcanRxCfgPrms->remoteEnable = FALSE;
    pDcanRxCfgPrms->fifoEOBFlag  = TRUE;

    /*Intialize DCAN Tx transfer Params*/
    pDcanTxPrms->dataLength = DCAN_MAX_MSG_LENGTH;
    pDcanTxPrms->msgData[0] = 0xA5;
    pDcanTxPrms->msgData[1] = 0x5A;
    pDcanTxPrms->msgData[2] = 0xFF;
    pDcanTxPrms->msgData[3] = 0xFF;
    pDcanTxPrms->msgData[4] = 0xC3;
    pDcanTxPrms->msgData[5] = 0x3C;
    pDcanTxPrms->msgData[6] = 0xB4;
    pDcanTxPrms->msgData[7] = 0x4B;
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

static void DCANAppConfigIntr(void)
{
    xbar_irq_t intrSource;

    if (gDcanAppInstance == DCAN1_APP_INST)
    {
        intrSource = DCAN1_IRQ_INT0;
    }
    else
    {
        intrSource = DCAN2_IRQ_INT0;
    }

#if defined (BUILD_M4)
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_IPU1,
                   XBAR_INST_IPU1_IRQ_28, intrSource);

    Intc_Init();
    Intc_IntEnable(0);

    Intc_IntRegister(28, (IntrFuncPtr) DCANAppInt0Isr, (void *) 0);

    Intc_IntPrioritySet(28, 1, 0);

    Intc_SystemEnable(28);
#elif defined (BUILD_A15)
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_MPUSS,
                   XBAR_INST_MPU_IRQ_77, intrSource);

    Intc_Init();
    Intc_IntEnable(0);

    Intc_IntRegister(77, (IntrFuncPtr) DCANAppInt0Isr, (void *) 0);

    Intc_IntPrioritySet(77, 1, 0);

    Intc_SystemEnable(77);
#endif
}

static void DCANAppInt0Isr()
{
    if ((DCANIsMsgObjIntrPending(gDcanAppInstance, DCAN_TX_MSG_OBJ)) == TRUE)
    {
        DCANAppWaitForIfReg(gDcanAppInstance, DCAN_APP_TX_IF_REG);
        /* Clear the interrupts  of MSG_OBJ 1 for transmit */
        DCANIntrClearStatus(gDcanAppInstance, DCAN_TX_MSG_OBJ,
                            DCAN_APP_TX_IF_REG);
        DCANAppWaitForIfReg(gDcanAppInstance, DCAN_APP_TX_IF_REG);

        gTxDoneFlag = 1;
    }
    if ((DCANIsMsgObjIntrPending(gDcanAppInstance, DCAN_RX_MSG_OBJ)) == TRUE)
    {
        DCANAppWaitForIfReg(gDcanAppInstance, DCAN_APP_RX_IF_REG);
        /* Clear the interrupts  of MSG_OBJ 2 for Receive */
        DCANIntrClearStatus(gDcanAppInstance, DCAN_RX_MSG_OBJ,
                            DCAN_APP_RX_IF_REG);
        DCANAppWaitForIfReg(gDcanAppInstance, DCAN_APP_RX_IF_REG);

        gRxDoneFlag = 1;
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
        UARTPuts("\n\n**** DCAN APPLICATION TEST ****", -1);
        UARTPuts("\nMenu:", -1);
        UARTPuts("\n1. DCAN External Loopback test - DCAN1 Instance", -1);
        UARTPuts("\n2. DCAN Internal Loopback test - DCAN2 Instance", -1);
#ifdef TDA3XX_FAMILY_BUILD
        UARTPuts("\n3. DCAN ECC test - DCAN1 Instance", -1);
#endif
        UARTPuts("\nx. Exit", -1);
        UARTPuts("\nSelect DCAN APPLICATION TEST : ", -1);

        /* Get option */
        UARTGets(option, 1);

        if ((DCAN_EXT_LOOPBACK_TEST == *option) ||
            (DCAN_ECC_TEST == *option) ||
            (DCAN_INT_LOOPBACK_TEST == *option) || EXIT(*option))
        {
            break;
        }
        else
        {
            UARTPuts("\nEnter Valid option\n", -1);
        }
    }
}

