/******************************************************************************
 *                                                                            *
 * Copyright (c) 2015 Texas Instruments Incorporated - http://www.ti.com/     *
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
 *  \ingroup BSPUTILS_API
 *  \defgroup BSPUTILS_UB960_API APIs to initialize and de-initialize UB960 EVM
 *  @{
 */

/**
 *  \file bsputils_ub960.h
 *
 *  \brief Defines APIs to initialize, de-initialize UB960 EVM, address aliases
 *          & reset sensors.
 */

#ifndef BSPUTILS_UB960_H_
#define BSPUTILS_UB960_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <common/trace.h>
#include <common/bsp_common.h>
#include <fvid2/fvid2.h>
#include <platforms/bsp_platform.h>
#include <vps/vps.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define UB960_ACCESSIBLE_FROM_I2C_INST  (BSP_DEVICE_I2C_INST_ID_1)
/**< Identify the I2C instance through which UB960 is accessible */

#define UB960_SLAVE_ADDR       (0x3D)
/**< 7 bit UB960 slave address */

/**
 * Specify the address that should be associated with TIDA00262. TIDA00262
 *  consists of 913 serializer and AR0140 sensor. Specify the address for both
 *  Address is in 7bit format.
 */
#define TIDA00262_PORT_0_SER_ADDR       (0x74U)
/**< Serializer address */
#define TIDA00262_PORT_0_SENSOR_ADDR    (0x40U)
/**< Sensor address */
#define TIDA00262_PORT_1_SER_ADDR       (0x76U)
/**< Serializer address */
#define TIDA00262_PORT_1_SENSOR_ADDR    (0x42U)
/**< Sensor address */
#define TIDA00262_PORT_2_SER_ADDR       (0x78U)
/**< Serializer address */
#define TIDA00262_PORT_2_SENSOR_ADDR    (0x44U)
/**< Sensor address */
#define TIDA00262_PORT_3_SER_ADDR       (0x7AU)
/**< Serializer address */
#define TIDA00262_PORT_3_SENSOR_ADDR    (0x46U)
/**< Sensor address */

#define BSPUTILS_UB960EVM_MAX_PORTS     (0x4U)
/**< Number of receive ports supported */

#define BSPUTILS_UB960EVM_NO_SOURCE_DETECTED     (0xFFFFFFFFU)
/**< Identifier to indicate no source detected at a given port */
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Status of UB960 initialization.
 *          When numDetected > 0, indicates UB960 EVM is initialized.
 *          When numDetected == 0, indicates UB960 EVM did not detect any
 *              sources. Please check the I2C addresses in case a source was
 *              connected but not detected.
 */
typedef struct
{
    UInt32 numDetected;
    /**< Specifies the number of sensor/modules connected to UB960 detected */
    UInt32 portNum[BSPUTILS_UB960EVM_MAX_PORTS];
    /**< Source detected at ports, range 0 & < BSPUTILS_UB960EVM_MAX_PORTS and
     *      BSPUTILS_UB960EVM_NO_SOURCE_DETECTED in cases no sources detected */
} BspUtils_Ub960Status;

/**
 *  \brief Configure I2C address of the sources
 *          When numDetected > 0, indicates UB960 EVM is initialized.
 *          When numDetected == 0, indicates UB960 EVM did not detect any
 *              sources. Please check the I2C addresses in case a source was
 *              connected but not detected.
 */
typedef struct
{
    UInt32 slaveAddr;
    /**< Specify the 7bit UB960 slave address */
    UInt32 numSource;
    /**< Specify the number of sensor/modules connected to UB960 */
    UInt32 rSlave1Addr[BSPUTILS_UB960EVM_MAX_PORTS];
    /**< Designate the 7 bit slave address for first slave.
     *      In cases where TIDA00262 is connected, this holds serializer slave
     *      address */
    UInt32 rSlave2Addr[BSPUTILS_UB960EVM_MAX_PORTS];
    /**< Designate the 7 bit slave address for second slave.
     *      In cases where TIDA00262 is connected, this holds sensor slave
     *      address */
} BspUtils_Ub960SourceI2cAddr;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Initializes the UB960 EVM. Sets up the SLAVE aliases and configures
 *          CSI2 transmit port for transmission. Please note that source
 *          connected to UB960 would require configuration to0.
 *          Supports following source to be connected.
 *          1. TIDA00262
 *
 *  \param instId     [IN]      Instance of UB960 EVM. Ignored for now.
 *  \param pSlaveAddr [IN]      I2C slave address
 *  \param pStatus    [IN/OUT]  Returns the number of sources detected.
 */
Int32 BspUtils_appInitUb960(UInt32                             instId,
                            const BspUtils_Ub960SourceI2cAddr *pSlaveAddr,
                            BspUtils_Ub960Status              *pStatus);

/**
 *  \brief De Initializes the UB960 EVM. Stops transmission on the CSI2
 *          interface.
 *
 *  \param instId [IN]  Instance of UB960 EVM. Ignored for now.
 */
Int32 BspUtils_appDeInitUb960(UInt32 instId);

/**
 *  \brief Initializes the serializer of TIDA00262 in RAW12 mode.
 *  \warning Ensure the pixel clock of AR0140 is at 72 MHz. This is requirement
 *              of the serializer.
 *
 *  \param portId [IN]  Identify the instance of TIDA that requires to be
 *                          initialized.
 */
Int32 BspUtils_appInitTida00262(UInt32 portId);

/**
 *  \brief Resets the sensor and stops transmission.
 *
 *  \param portId [IN]  Identify the instance of TIDA that requires to be
 *                          de initialized.
 */
Int32 BspUtils_appDeInitTida00262(UInt32 portId);

/**
 *  \brief Resets the sensor and stops transmission.
 *
 *  \param instId [IN]  Identify the instance of TIDA that requires to be
 *                          de initialized.
 */
inline UInt32 BspUtils_getSerAddrTida00262(UInt32 instId);

inline UInt32 BspUtils_getSerAddrTida00262(UInt32 instId)
{
    UInt32 addr;
    if (0x0U == instId)
    {
        addr = TIDA00262_PORT_0_SER_ADDR;
    }
    else if (0x1U == instId)
    {
        addr = TIDA00262_PORT_1_SER_ADDR;
    }
    else if (0x2U == instId)
    {
        addr = TIDA00262_PORT_2_SER_ADDR;
    }
    else
    {
        addr = TIDA00262_PORT_3_SER_ADDR;
    }
    return (addr);
}

#ifdef __cplusplus
}
#endif

#endif  /* #define BSPUTILS_UB960_H_ */

/* @} */
