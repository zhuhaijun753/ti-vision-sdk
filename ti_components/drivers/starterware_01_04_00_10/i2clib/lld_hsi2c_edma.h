/* ======================================================================
 *   Copyright (C) 2013 Texas Instruments Incorporated
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
#ifndef LLD_HSI2C_EDMA_H_
#define LLD_HSI2C_EDMA_H_

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 *                             INCLUDE FILES
 *******************************************************************************/
#include "stdint.h"
#include "i2clib/lld_hsi2c.h"

/******************************************************************************
 *                        LOCAL MACRO DEFINITIONS
 ******************************************************************************/
#ifdef TI814X_FAMILY_BUILD
#define LLD_I2C_EDMA_CHA_I2CTXEVT0    ((uint32_t) 58U)
#define LLD_I2C_EDMA_CHA_I2CRXEVT0    ((uint32_t) 59U)
#define LLD_I2C_EDMA_CHA_I2CTXEVT1    ((uint32_t) 60U)
#define LLD_I2C_EDMA_CHA_I2CRXEVT1    ((uint32_t) 61U)

/*Cross Bar mapped*/
#define LLD_I2C_EDMA_CHA_I2CTXEVT2    ((uint32_t) 66U)
#define LLD_I2C_EDMA_CHA_I2CRXEVT2    ((uint32_t) 67U)
#define LLD_I2C_EDMA_CHA_I2CTXEVT3    ((uint32_t) 68U)
#define LLD_I2C_EDMA_CHA_I2CRXEVT3    ((uint32_t) 69U)

#endif

#ifdef TDA2XX_FAMILY_BUILD
#define LLD_I2C_EDMA_CHA_I2CTXEVT0    ((uint32_t) 26U)
#define LLD_I2C_EDMA_CHA_I2CRXEVT0    ((uint32_t) 27U)
#define LLD_I2C_EDMA_CHA_I2CTXEVT1    ((uint32_t) 28U)
#define LLD_I2C_EDMA_CHA_I2CRXEVT1    ((uint32_t) 29U)
#define LLD_I2C_EDMA_CHA_I2CTXEVT2    ((uint32_t) 24U)
#define LLD_I2C_EDMA_CHA_I2CRXEVT2    ((uint32_t) 25U)

/*Cross bar mapped need to take care depending on the cross bar mapping */
#define LLD_I2C_EDMA_CHA_I2CTXEVT3    ((uint32_t) 124U)
#define LLD_I2C_EDMA_CHA_I2CRXEVT3    ((uint32_t) 125U)
#define LLD_I2C_EDMA_CHA_I2CTXEVT4    ((uint32_t) 152U)
#define LLD_I2C_EDMA_CHA_I2CRXEVT4    ((uint32_t) 153U)
#if defined (TDA2EX_BUILD)
#define LLD_I2C_EDMA_CHA_I2CTXEVT5    ((uint32_t) 203U)
#define LLD_I2C_EDMA_CHA_I2CRXEVT5    ((uint32_t) 204U)
#endif
#endif

#ifdef TDA3XX_FAMILY_BUILD
#define LLD_I2C_EDMA_CHA_I2CTXEVT0    ((uint32_t) 26U)
#define LLD_I2C_EDMA_CHA_I2CRXEVT0    ((uint32_t) 27U)
#define LLD_I2C_EDMA_CHA_I2CTXEVT1    ((uint32_t) 28U)
#define LLD_I2C_EDMA_CHA_I2CRXEVT1    ((uint32_t) 29U)
#endif

typedef struct
{
    /*void *                     hEdma;
     * int32_t                   edma3EventQueue;*/
    uint32_t baseAddr;
    uint32_t channelType;
    uint32_t eventQueue;
    uint32_t intNum;
}LLD_hsi2cEdmaParam;

LLD_hsi2cEdmaStatus EDMA_requestChannel(hsI2cHandle          handle,
                                        uint32_t            *i2cEventNo,
                                        lldHsi2cEdmaCallback i2cCallback,
                                        void                *edmaParam);
LLD_hsi2cEdmaStatus EDMA_freeChannel(uint32_t i2cEventNo, void *edmaParam);
LLD_hsi2cEdmaStatus EDMA_disableLogicalChannel(uint32_t tcc, void *edmaParam);
LLD_hsi2cEdmaStatus EDMA_clearErrorBits(uint32_t tcc, void *edmaParam);
LLD_hsi2cEdmaStatus EDMA_setPaRAM(const void *srcPtr, const void *dstPtr,
                                  uint32_t rdWrflag,
                                  uint32_t chan, uint32_t bufLen,
                                  void *edmaParam,
                                  uint8_t fifoThreshold);
LLD_hsi2cEdmaStatus EDMA_enableTransfer(uint32_t chan, void *edmaParam);
void EDMA_callbackFn(void *arg);
#ifdef __cplusplus
}
#endif

#endif
