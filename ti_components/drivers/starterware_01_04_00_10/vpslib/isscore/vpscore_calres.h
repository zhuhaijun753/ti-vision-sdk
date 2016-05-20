/**
 *  \file vpscore_calres.h
 *
 *  \brief  Resource management API for CAL.
 */

/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 */
/*
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef _VPSCORE_CALRES_H_
#define _VPSCORE_CALRES_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <common/vpscore.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  struct vcoreissCaptCalAllocModIsnt
 *  \brief Allocated module instance
 */
typedef struct vcoreissCaptCalAllocModIsnt
{
    uint32_t ppiInst;
    /**< Allocated PPI instance */
    uint32_t pixExtInst;
    /**< Allocated pixel extraction instance */
    uint32_t dpcmDecodeInst;
    /**< Allocated DPCM decode instance */
    uint32_t dpcmEncodeInst;
    /**< Allocated DPCM encode instance */
    uint32_t pixPackInst;
    /**< Allocated pixel packing instance */
    uint32_t dmaInst;
    /**< Allocated write DMA instance */
    uint32_t cPortId;
    /**< Allocated C Port ID */
} vcoreissCaptCalAllocModIsnt_t;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  enum vcoreissCaptCalSubModules
 *  \brief Identifiers for different CAL sub modules.
 */
typedef enum vcoreissCaptCalSubModules
{
    VPSCORE_ISS_CAPT_CAL_SUB_MIN_ID =   0x000,
    /**< Enum begin marker */
    VPSCORE_ISS_CAPT_CAL_SUB_PPI_ID =   0x001,
    /**< Identifier for PPI & CSI2 sub blocks */
    VPSCORE_ISS_CAPT_CAL_SUB_PIX_EXT_ID =   0x002,
    /**< Identifier for pixel extract sub block */
    VPSCORE_ISS_CAPT_CAL_SUB_DPCM_DECODE_ID =   0x004,
    /**< Identifier for DPCM decode sub block */
    VPSCORE_ISS_CAPT_CAL_SUB_BYS_OUT_ID =   0x008,
    /**< Identifier for bys out sub block */
    VPSCORE_ISS_CAPT_CAL_SUB_BYS_IN_ID =   0x010,
    /**< Identifier for bys in sub block */
    VPSCORE_ISS_CAPT_CAL_SUB_VPORT_ID =   0x020,
    /**< Identifier for V port out sub block */
    VPSCORE_ISS_CAPT_CAL_SUB_DPCM_ENCODE_ID =   0x040,
    /**< Identifier for DPCM encode sub block */
    VPSCORE_ISS_CAPT_CAL_SUB_PIX_PACK_ID =   0x080,
    /**< Identifier for pixel packing sub block */
    VPSCORE_ISS_CAPT_CAL_SUB_WR_DMA_ID =   0x100,
    /**< Identifier for pixel packing sub block */
    VPSCORE_ISS_CAPT_CAL_SUB_MAX_ID,
    /**< Enum end marker */
    VPSCORE_ISS_CAPT_CAL_SUB_FORCE_INT = 0x7FFFFFFF
                                         /**< This will ensure enum is not packed,
                                                 will always be contained in int */
} vcoreissCaptCalSubModules_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Function to initialize CAL sub module resource management
 *
 *  \param numInst          number of instances to be initialized
 *  \param arg              not used as of now
 *
 *  \return                 FVID2_SOK: on successful completion, otherwise
 *                          appropriate error code.
 */
int32_t VpsCore_issCaptCalResInit(
    uint32_t numInst,
    Ptr      arg);

/**
 *  \brief Function to De-initialize CAL sub module resource management
 *
 *  \param arg              not used as of now
 *
 *  \return                 FVID2_SOK: on successful completion, otherwise
 *                          appropriate error code.
 */
int32_t VpsCore_issCaptCalResDeInit(Ptr arg);

/**
 *  \brief Allocate CAL sub modules & C Port ID
 *
 *  \param inst             Instance of CAL to allocate from
 *  \param subModules       Sub Modules that requires to be allocated
 *  \param alocInst         Module instance allocated, if every thing went well
 *  \param unAvailModules   Allocation fails due to unavailability of these
 *                              modules.
 *
 *  \return             FVID2_SOK: on successful completion, otherwise
 *                          FVID2_EALLOC.
 */
int32_t VpsCore_issCaptCalAllocRes(uint32_t inst, uint32_t subModules,
                                   vcoreissCaptCalAllocModIsnt_t *alocInst,
                                   uint32_t *unAvailModules);

/**
 *  \brief Function to De-initialize CAL sub module resource management
 *
 *  \param inst         Instance of CAL to de allocate from
 *  \param subModules   Sub Modules to be de allocate
 *  \param cportId      C Port ID to be de allocate
 *
 *  \return                 FVID2_SOK: on successful completion, otherwise
 *                          appropriate error code.
 */
int32_t VpsCore_issCaptCalFreeRes(uint32_t inst, uint32_t subModules,
                                  uint32_t cportId);

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef _VPSCORE_CALRES_H_ */
