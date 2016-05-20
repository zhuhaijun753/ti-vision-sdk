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
#ifndef QSPI_CMD_INIT_H_
#define QSPI_CMD_INIT_H_

/*_______________________________ Include Files ______________________________*/

#include "qspi.h"
#include "qspi_flash.h"

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

int32_t QSPI_GetDefaultFlashDevInfo(qspi_DeviceType_e    flashType,
                                    QSPI_FlashDevInfo_t *flashDevInfo);

int32_t QSPI_SetDefaultFlashDevInfo(qspi_DeviceType_e          flashType,
                                    const QSPI_FlashDevInfo_t *flashDevInfo);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif /* QSPI_CMD_INIT_H_ */
