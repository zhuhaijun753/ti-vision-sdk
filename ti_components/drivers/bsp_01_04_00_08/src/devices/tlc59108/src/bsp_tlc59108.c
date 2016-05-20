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
 *  \file bsp_tlc59108Api.c
 *
 *  \brief TLC59108 PWM API file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <xdc/std.h>
#include <tlc59108/src/bsp_tlc59108Priv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static Int32 Bsp_tlc59108Lock(void);

static Int32 Bsp_tlc59108UnLock(void);

#if 0
static Int32 Bsp_tlc59108LockObj(Bsp_Tlc59108HandleObj *pObj);

static Int32 Bsp_tlc59108UnLockObj(Bsp_Tlc59108HandleObj *pObj);

static Bsp_Tlc59108HandleObj *Bsp_tlc59108AllocObj(void);

static Int32 Bsp_tlc59108FreeObj(Bsp_Tlc59108HandleObj *pObj);

#endif

/**
 *  \brief Sets the PWM register Corresponding to a particular PIN .
 */
static Int32 Bsp_tlc59108SetPwmRegister(UInt32 i2cInstId,
                                        UInt32 tlcDevAdd,
                                        UInt32 pinNum,
                                        UInt8  pwmRegVal);

static Int32 Bsp_tlc59108GetPwmValue(UInt32 dutyCycle, UInt8 *pwmRegVal);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/**
 *  \brief Global object storing all information related to all LCD Ctrl driver
 *  handles.
 */
static Bsp_Tlc59108Obj gBspTlc59108Obj;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  \brief System init for TLC59108 driver
 *
 *  This API
 *      - create semaphore locks needed
 *      - gets called as part of Bsp_deviceInit()
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error code.
 */
Int32 Bsp_tlc59108Init(void)
{
    Int32 retVal = FVID2_SOK;
    Int32 initValue;

    /* Memset global object */
    BspUtils_memset(&gBspTlc59108Obj, 0, sizeof (gBspTlc59108Obj));

    /* Create global LCD Ctrl lock */
    initValue = 1;
    gBspTlc59108Obj.lock = BspOsal_semCreate(initValue, (Bool)TRUE);
    if (NULL == gBspTlc59108Obj.lock)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Global semaphore create failed\n");
        retVal = FVID2_EALLOC;
    }

    return (retVal);
}

/**
 *  \brief System de-init for TLC59108 driver
 *
 *  This API
 *      - delete's allocated semaphore locks
 *      - gets called as part of Bsp_deviceDeInit()
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error code.
 */
Int32 Bsp_tlc59108DeInit(void)
{
    /* Delete semaphore's. */
    BspOsal_semDelete(&gBspTlc59108Obj.lock);

    return (FVID2_SOK);
}

#if 0
/**
 *  \brief TLC59108 create API .
 *
 *  This API does not configure the TLC59108 in any way.
 *
 *  This API
 *      - validates parameters
 *      - allocates driver handle
 *      - stores create arguments in its internal data structure.
 *
 *  Later the create arguments will be used when doing I2C communcation with
 *  TLC59108.
 *
 *  \param createPrms       [IN] Create arguments - pointer to valid
 *                          Bsp_Tlc59108CreateParams. This parameter should
 *                          be non-NULL.
 *
 *  \return                 Returns NULL in case of any error. Otherwise
 *                          returns a valid handle.
 */
void *Bsp_tlc59108Create(Ptr createPrms)
{
    Int32 retVal = FVID2_SOK;
    Bsp_Tlc59108HandleObj    *pObj = NULL;
    Bsp_Tlc59108CreateParams *pwmCreatePrms;

    /* Check parameters */
    if (NULL == createPrms)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Invalid parameters\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        pwmCreatePrms = (Bsp_Tlc59108CreateParams *) createPrms;
        if (pwmCreatePrms->deviceI2cInstId >= BSP_DEVICE_I2C_INST_ID_MAX)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Invalid I2C instance ID\n");
            retVal = FVID2_EINVALID_PARAMS;
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Allocate driver handle */
        pObj = Bsp_tlc59108AllocObj();
        if (NULL == pObj)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Alloc object failed\n");
            retVal = FVID2_EALLOC;
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Copy parameters to allocate driver handle */
        BspUtils_memcpy(
            &pObj->createPrms,
            pwmCreatePrms,
            sizeof (*pwmCreatePrms));
    }

    return (pObj);
}

/**
 *  \brief Delete function that is called when Fvid2_delete is called.
 *
 *  This API
 *      - free's driver handle object
 *
 *  \param handle           [IN] Driver handle.
 *  \param deleteArgs       [IN] Not used currently. Meant for future purpose.
 *                          Set this to NULL.
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error code. *
 */
Int32 Bsp_tlc59108Delete(Ptr handle)
{
    Int32 retVal = FVID2_SOK;
    Bsp_Tlc59108HandleObj *pObj;

    /* Check parameters */
    if (NULL == handle)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        /* Free driver handle object */
        pObj   = (Bsp_Tlc59108HandleObj *) handle;
        retVal = Bsp_tlc59108FreeObj(pObj);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Free object failed\n");
        }
    }

    return (retVal);
}

Int32 Bsp_tlc59108ConfOutput(Bsp_Tlc59108HandleObj *pObj,
                             const UInt32          *pinNum,
                             UInt32                *dutyCycle,
                             UInt32                 numPins)
{
    UInt32 cnt, pin, dutyCyl;
    Int32  retVal = FVID2_SOK;

    /* Check parameters */
    if (NULL == pObj)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        retVal = FVID2_EBADARGS;
    }

    /* lock handle */
    Bsp_tlc59108LockObj(pObj);

    if (retVal == FVID2_SOK)
    {
        if ((NULL == pinNum) || (NULL == dutyCycle) || (0 == numPins))
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
            retVal = FVID2_EBADARGS;
        }
    }

    if (retVal == FVID2_SOK)
    {
        for (cnt = 0; cnt < numPins; cnt++)
        {
            pin     = pinNum[cnt];
            dutyCyl = dutyCycle[cnt];
            Bsp_tlc59108SetPin(pObj, pin, dutyCyl);
        }
    }

    /* Unlock handle */
    Bsp_tlc59108UnLockObj(pObj);

    return retVal;
}

Int32 Bsp_tlc59108turnOnBackLightPower(void)
{
    Int32 retVal = FVID2_SOK;
    UInt8 regVal[2];
    UInt8 regAddr[2];
    UInt8 numRegs = 0;

    Bsp_deviceI2cDebugEnable(1);

    regVal[numRegs] = 0xFF;
    numRegs++;
    regVal[numRegs] = 0xDB;
    numRegs++;

    retVal = Bsp_deviceRawWrite8(
        I2C_INST_0,
        PCF8575_I2C_ADDR,
        regVal,
        2U);

    if (retVal != FVID2_SOK)
    {
        GT_0trace(BspDeviceTrace, GT_ERR,
                  "Turning on back light power failed \n");
    }

    return retVal;
}

Int32 Bsp_tlc59108SetMode(void)
{
    Int32 retVal = FVID2_SOK;
    UInt8 regVal[1];
    UInt8 regAddr[1];
    UInt8 numRegs = 0;

    regAddr[0] = BSP_TLC59108_REG_MODE1;
    regVal[0]  = 0x0;
    numRegs++;

    Bsp_deviceI2cDebugEnable(1);

    retVal = Bsp_deviceWrite8(
        I2C_INST,
        TLC_I2C_ADDR,
        regAddr,
        regVal,
        numRegs);

    if (retVal != FVID2_SOK)
    {
        GT_0trace(BspDeviceTrace, GT_ERR,
                  "Tlc set mode failed \n");
    }

    regAddr[0] = BSP_TLC59108_REG_LEDOUT0;
    regVal[0]  = 0x21;

    retVal = Bsp_deviceWrite8(
        I2C_INST,
        TLC_I2C_ADDR,
        regAddr,
        regVal,
        numRegs);

    if (retVal != FVID2_SOK)
    {
        GT_0trace(BspDeviceTrace, GT_ERR,
                  "LEDOUT0 setting succeed \n");
    }

    regAddr[0] = BSP_TLC59108_REG_PWM2;
    regVal[0]  = 0xFF;

    retVal = Bsp_deviceWrite8(
        I2C_INST,
        TLC_I2C_ADDR,
        regAddr,
        regVal,
        numRegs);

    if (retVal != FVID2_SOK)
    {
        GT_0trace(BspDeviceTrace, GT_ERR,
                  "PWM2 setting succeed \n");
    }

    regAddr[0] = BSP_TLC59108_REG_LEDOUT1;
    regVal[0]  = 0x11;

    retVal = Bsp_deviceWrite8(
        I2C_INST,
        TLC_I2C_ADDR,
        regAddr,
        regVal,
        numRegs);

    if (retVal != FVID2_SOK)
    {
        GT_0trace(BspDeviceTrace, GT_ERR,
                  "LEDOUT1 setting succeed \n");
    }

    return retVal;
}

#endif

Int32 Bsp_tlc59108WriteReg(UInt32       i2cInstId,
                           UInt32       tlcDevAdd,
                           const UInt8 *regAddr,
                           const UInt8       *regValue,
                           UInt32       numRegs)
{
    Int32 retVal = FVID2_SOK;

    /* Check params */
    if ((regAddr == NULL) || (regValue == NULL) || (numRegs == 0))
    {
        GT_0trace(BspDeviceTrace, GT_ERR,
                  " Tlc59108 - Invalid register write params !!!\n");
        retVal = FVID2_EBADARGS;
    }

    Bsp_tlc59108Lock();

    if (retVal == FVID2_SOK)
    {
        retVal = Bsp_deviceWrite8(
            i2cInstId,
            tlcDevAdd,
            regAddr,
            regValue,
            numRegs);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspDeviceTrace, GT_ERR,
                      " Tlc59108 - I2C register write failed !!!\n");
        }
    }

    Bsp_tlc59108UnLock();

    return retVal;
}

Int32 Bsp_tlc59108ReadReg(UInt32       i2cInstId,
                          UInt32       tlcDevAdd,
                          const UInt8 *regAddr,
                          UInt8       *regValue,
                          UInt32       numRegs)
{
    Int32 retVal = FVID2_SOK;

    /* Check params */
    if ((regAddr == NULL) || (regValue == NULL) || (numRegs == 0))
    {
        GT_0trace(BspDeviceTrace, GT_ERR,
                  " Tlc59108 - Invalid register Read params !!!\n");
        retVal = FVID2_EBADARGS;
    }

    Bsp_tlc59108Lock();

    if (retVal == FVID2_SOK)
    {
        retVal = Bsp_deviceRead8(
            i2cInstId,
            tlcDevAdd,
            regAddr,
            regValue,
            numRegs);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspDeviceTrace, GT_ERR,
                      " Tlc59108 - I2C register read failed !!!\n");
        }
    }

    Bsp_tlc59108UnLock();

    return retVal;
}

Int32 Bsp_tlc59108SetPin(UInt32 i2cInstId,
                         UInt32 tlcDevAdd,
                         UInt32 pinNum,
                         UInt32 dutyCycle)
{
    UInt8  bitVal = 0, bitValtmp = 0;
    Int32  retVal = FVID2_SOK;
    UInt8  regVal[2];
    UInt8  regAddr[2];
    UInt32 numRegs   = 0;
    UInt8  pwmRegVal = 0;
    UInt32 regValue = 0;
    UInt32 bitValue = 0;

    if (dutyCycle == 0)
    {
        bitVal = 0x0;
    }
    else if (dutyCycle == 100U)
    {
        bitVal = (UInt8)0x1;
    }
    else if (dutyCycle < 100U)
    {
        bitVal = (UInt8)0x2;
    }
    else
    {
        GT_0trace(BspDeviceTrace, GT_ERR,
                  "In valid dutyCycle \n");
        retVal = FVID2_EBADARGS;
    }

    bitValtmp = bitVal;
    Bsp_tlc59108Lock();

    if (retVal == FVID2_SOK)
    {
        regVal[numRegs] = 0U;
        regAddr[numRegs] = BSP_TLC59108_REG_LEDOUT0;
        numRegs++;
        regVal[numRegs] = 0U;
        regAddr[numRegs] = BSP_TLC59108_REG_LEDOUT1;
        numRegs++;

        /* apply the settings */
        retVal = Bsp_deviceRead8(
            i2cInstId,
            tlcDevAdd,
            regAddr,
            regVal,
            numRegs);

        switch (pinNum)
        {
            case BSP_TLC59108_PIN0:
                /* Read LED0 reg from I2C */
                regValue = ((UInt32)regVal[0] & ~((0x03U) <<
                             BSP_TLC59108_LEDOUT0_PIN0_SHIFT));
                bitValue = (((UInt32)bitVal <<
                             BSP_TLC59108_LEDOUT0_PIN0_SHIFT) &
                             BSP_TLC59108_LEDOUT0_PIN0_MASK);
                regValue= (regValue | bitValue);
                regVal[0]= (UInt8)regValue;
                bitVal= (UInt8)bitValue;
                /* Write this to TLC register via I2C*/
                break;

            case BSP_TLC59108_PIN1:
                regValue = ((UInt32)regVal[0] & ~((0x03U) <<
                              BSP_TLC59108_LEDOUT0_PIN1_SHIFT));
                bitValue = (((UInt32)bitVal <<
                             BSP_TLC59108_LEDOUT0_PIN1_SHIFT) &
                             BSP_TLC59108_LEDOUT0_PIN1_MASK);
                regValue= (regValue | bitValue);
                regVal[0]= (UInt8)regValue;
                bitVal= (UInt8)bitValue;
                break;

            case BSP_TLC59108_PIN2:
                regValue = ((UInt32)regVal[0] & ~((0x03U) <<
                              BSP_TLC59108_LEDOUT0_PIN2_SHIFT));
                bitValue = (((UInt32)bitVal <<
                             BSP_TLC59108_LEDOUT0_PIN2_SHIFT) &
                             BSP_TLC59108_LEDOUT0_PIN2_MASK);
                regValue= (regValue | bitValue);
                regVal[0]= (UInt8)regValue;
                bitVal= (UInt8)bitValue;
                break;

            case BSP_TLC59108_PIN3:
                regValue = ((UInt32)regVal[0] & ~((0x03U) <<
                             BSP_TLC59108_LEDOUT0_PIN3_SHIFT));
                bitValue = (((UInt32)bitVal <<
                             BSP_TLC59108_LEDOUT0_PIN3_SHIFT) &
                             BSP_TLC59108_LEDOUT0_PIN3_MASK);
                regValue= (regValue | bitValue);
                regVal[0]= (UInt8)regValue;
                bitVal= (UInt8)bitValue;
                break;

            case BSP_TLC59108_PIN4:
                regValue = ((UInt32)regVal[1] & ~((0x03U) <<
                             BSP_TLC59108_LEDOUT1_PIN4_SHIFT));
                bitValue = (((UInt32)bitVal <<
                             BSP_TLC59108_LEDOUT1_PIN4_SHIFT) &
                             BSP_TLC59108_LEDOUT1_PIN4_MASK);
                regValue= (regValue | bitValue);
                regVal[1]= (UInt8)regValue;
                bitVal= (UInt8)bitValue;
                break;

            case BSP_TLC59108_PIN5:
                regValue = ((UInt32)regVal[1] & ~((0x03U) <<
                             BSP_TLC59108_LEDOUT1_PIN5_SHIFT));
                bitValue = (((UInt32)bitVal <<
                             BSP_TLC59108_LEDOUT1_PIN5_SHIFT) &
                             BSP_TLC59108_LEDOUT1_PIN5_MASK);
                regValue= (regValue | bitValue);
                regVal[1]= (UInt8)regValue;
                bitVal= (UInt8)bitValue;
                break;

            case BSP_TLC59108_PIN6:
                regValue = ((UInt32)regVal[1] & ~((0x03U) <<
                             BSP_TLC59108_LEDOUT1_PIN6_SHIFT));
                bitValue = (((UInt32)bitVal <<
                             BSP_TLC59108_LEDOUT1_PIN6_SHIFT) &
                             BSP_TLC59108_LEDOUT1_PIN6_MASK);
                regValue= (regValue | bitValue);
                regVal[1]= (UInt8)regValue;
                bitVal= (UInt8)bitValue;
                break;

            case BSP_TLC59108_PIN7:
                regValue = ((UInt32)regVal[1] & ~((0x03U) <<
                             BSP_TLC59108_LEDOUT1_PIN7_SHIFT));
                bitValue = (((UInt32)bitVal <<
                             BSP_TLC59108_LEDOUT1_PIN7_SHIFT) &
                             BSP_TLC59108_LEDOUT1_PIN7_MASK);
                regValue= (regValue | bitValue);
                regVal[1]= (UInt8)regValue;
                bitVal= (UInt8)bitValue;
                break;

            default:
                GT_0trace(BspDeviceTrace, GT_ERR,
                          "In valid Pin Number\n");
                retVal = FVID2_EBADARGS;
                break;
        }
    }

    if (FVID2_SOK == retVal)
    {
        if (pinNum <= (UInt32) BSP_TLC59108_PIN7)
        {
            /* program regVal[0] into LEDOUT0 register*/
            retVal = Bsp_deviceWrite8(
                i2cInstId,
                tlcDevAdd,
                regAddr,
                regVal,
                numRegs);
        }
        else
        {
            GT_0trace(BspDeviceTrace, GT_ERR,
                      "In valid Pin Number\n");
            retVal = FVID2_EBADARGS;
        }
    }

    if ((bitValtmp == (UInt8)0x2) && (FVID2_SOK == retVal))
    {
        /* if bitval is 0x2 then program the corresponding PWM register as
         * well(get the reg
         * val from the percentage)*/
        retVal = Bsp_tlc59108GetPwmValue(dutyCycle, &pwmRegVal);
        if (retVal == FVID2_SOK)
        {
            retVal = Bsp_tlc59108SetPwmRegister(i2cInstId, tlcDevAdd, pinNum,
                                                pwmRegVal);
        }
    }

    Bsp_tlc59108UnLock();

    return retVal;
}

#if 0
/**
 *  \brief Allocates driver object.
 *
 *  Searches in list of driver handles and allocate's a 'NOT IN USE' handle
 *  Also create's handle level semaphore lock.
 *
 *  Returns NULL in case handle could not be allocated.
 */
static Bsp_Tlc59108HandleObj *Bsp_tlc59108AllocObj(void)
{
    UInt32 handleId;
    Bsp_Tlc59108HandleObj *pObj = NULL;
    Int32 initValue;

    /* Take global lock to avoid race condition */
    Bsp_tlc59108Lock();

    /* Find a unallocated object in pool */
    for (handleId = 0U; handleId < BSP_DEVICE_MAX_HANDLES; handleId++)
    {
        if (BSP_TLC59108_OBJ_STATE_UNUSED ==
            gBspTlc59108Obj.handlePool[handleId].state)
        {
            /* Free object found */
            pObj = &gBspTlc59108Obj.handlePool[handleId];

            /* Init state and handle ID */
            BspUtils_memset(pObj, 0, sizeof (*pObj));
            pObj->state    = BSP_TLC59108_OBJ_STATE_IDLE;
            pObj->handleId = handleId;

            /* Create driver object specific semaphore lock */
            initValue = 1;
            pObj->lock = BspOsal_semCreate(initValue, TRUE);
            if (NULL == pObj->lock)
            {
                GT_0trace(BspDeviceTrace, GT_ERR,
                          "Handle semaphore create failed\n");
                /* Error - release object */
                pObj->state = BSP_TLC59108_OBJ_STATE_UNUSED;
                pObj        = NULL;
            }
            break;
        }
    }

    /* Release global lock */
    Bsp_tlc59108UnLock();

    return (pObj);
}

/**
 *  \brief De-Allocate driver object.
 *
 *  Marks handle as 'NOT IN USE'.
 *  Also delete's handle level semaphore lock.
 */
static Int32 Bsp_tlc59108FreeObj(Bsp_Tlc59108HandleObj *pObj)
{
    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    /* Take global lock to avoid race condition */
    Bsp_tlc59108Lock();

    if (pObj->state != BSP_TLC59108_OBJ_STATE_UNUSED)
    {
        /* Mark state as unused */
        pObj->state = BSP_TLC59108_OBJ_STATE_UNUSED;

        /* Delete object locking semaphore */
        BspOsal_semDelete(&pObj->lock);
    }

    /* Release global lock */
    Bsp_tlc59108UnLock();

    return (FVID2_SOK);
}

/**
 *  \brief Handle level lock.
 */
static Int32 Bsp_tlc59108LockObj(Bsp_Tlc59108HandleObj *pObj)
{
    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    BspOsal_semWait(pObj->lock, BSP_OSAL_WAIT_FOREVER);

    return (FVID2_SOK);
}

/**
 *  \brief Handle level unlock
 */
static Int32 Bsp_tlc59108UnLockObj(Bsp_Tlc59108HandleObj *pObj)
{
    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    BspOsal_semPost(pObj->lock);

    return (FVID2_SOK);
}

#endif

/**
 *  \brief Sets the PWM register Corresponding to a particular PIN .
 */
static Int32 Bsp_tlc59108SetPwmRegister(UInt32 i2cInstId,
                                        UInt32 tlcDevAdd,
                                        UInt32 pinNum,
                                        UInt8  pwmRegVal)
{
    Int32  retVal = FVID2_SOK;
    UInt8  regAddr[1];
    UInt8  regValue[1];
    UInt32 numRegs = 0;

    switch (pinNum)
    {
        case BSP_TLC59108_PIN0:
            regAddr[numRegs] = BSP_TLC59108_REG_PWM0;
            break;
        case BSP_TLC59108_PIN1:
            regAddr[numRegs] = BSP_TLC59108_REG_PWM1;
            break;
        case BSP_TLC59108_PIN2:
            regAddr[numRegs] = BSP_TLC59108_REG_PWM2;
            break;
        case BSP_TLC59108_PIN3:
            regAddr[numRegs] = BSP_TLC59108_REG_PWM3;
            break;
        case BSP_TLC59108_PIN4:
            regAddr[numRegs] = BSP_TLC59108_REG_PWM4;
            break;
        case BSP_TLC59108_PIN5:
            regAddr[numRegs] = BSP_TLC59108_REG_PWM5;
            break;
        case BSP_TLC59108_PIN6:
            regAddr[numRegs] = BSP_TLC59108_REG_PWM6;
            break;
        case BSP_TLC59108_PIN7:
            regAddr[numRegs] = BSP_TLC59108_REG_PWM7;
            break;
        default:
            GT_0trace(BspDeviceTrace, GT_ERR,
                      "In valid Pin Number\n");
            retVal = FVID2_EBADARGS;
            break;
    }

    if (FVID2_SOK == retVal)
    {
        regValue[numRegs] = pwmRegVal;
        numRegs++;

        retVal = Bsp_deviceWrite8(
            i2cInstId,
            tlcDevAdd,
            regAddr,
            regValue,
            numRegs);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspDeviceTrace, GT_ERR,
                      " Tlc59108 - I2C register write failed !!!\n");
        }
    }

    return (retVal);
}

/**
 *  \brief Gets the Corresponding PWM register values for duty cycle.
 */
static Int32 Bsp_tlc59108GetPwmValue(UInt32 dutyCycle, UInt8 *pwmRegVal)
{
    Int32 retVal = FVID2_SOK;

    if (dutyCycle >= 100U)
    {
        retVal = FVID2_EBADARGS;
    }
    else
    {
        /* 100% ---> 0xFF(255), so approx mul factor is 2.5 */
        *pwmRegVal = (dutyCycle * 5U) / 2U;
    }

    return (retVal);
}

/**
 *  \brief Global driver level lock.
 */
static Int32 Bsp_tlc59108Lock(void)
{
    BspOsal_semWait(gBspTlc59108Obj.lock, BSP_OSAL_WAIT_FOREVER);

    return (FVID2_SOK);
}

/**
 *  \brief Global driver level unlock.
 */
static Int32 Bsp_tlc59108UnLock(void)
{
    BspOsal_semPost(gBspTlc59108Obj.lock);

    return (FVID2_SOK);
}

