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
 *  \file stw_utils.c
 *
 *  \brief Utility functions implementation file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "stdint.h"
#include <stddef.h>
#include <common/stw_utils.h>

void console_print_valHex(uint32_t val)
{
    UARTPutHexNum(val);
}

void console_print_string(const char *msg)
{
    UARTPuts(msg, -1);
}

void console_print_val(int32_t val)
{
    UARTPutNum(val);
}

