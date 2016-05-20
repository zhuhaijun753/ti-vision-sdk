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

#ifndef DSP_CONFIG_H_
#define DSP_CONFIG_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define DSP_SYS_MMU_EN          (1U)
#define DSP_SYS_MMU_DIS         (0U)

#define DSP_SYS_MMU_INSTANCE0   (0U)
#define DSP_SYS_MMU_INSTANCE1   (1U)

#define DSP_SYS_MMU_ABORT_EN    (1U)
#define DSP_SYS_MMU_ABORT_DIS   (0U)

void DSPSysMmuConfig(uint32_t baseAddr, uint32_t mmuInstance, uint32_t enable,
                     uint32_t mmuAbort);

#ifdef __cplusplus
}
#endif

#endif
