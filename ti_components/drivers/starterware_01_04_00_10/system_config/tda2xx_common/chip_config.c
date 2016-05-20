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
/**
 *  \file   chip_config.c
 *
 *  \brief  Chip Configuration  APIs.
 *
 *   This file contains the the chip configuration APIs.
 */

/****************************************************************
 *  INCLUDE FILES
 ****************************************************************/
 #include <stdint.h>
#include "chip_config.h"

/*******************************************************************************
 *                       INTERNAL API DEFINITIONS
 *******************************************************************************/
uint32_t  CHIPCONFIGGetNumEVEs(void)
{
    /* Need to use eFUSE MMR info here... */
#if !(defined (TDA2EX_BUILD))
    return (uint32_t) 4;
#else
    return (uint32_t) 0;
#endif
}

uint32_t  CHIPCONFIGGetNumDSPs(void)
{
    /* Need to use eFUSE MMR info here ... */
#if !(defined (TDA2EX_BUILD))
    return (uint32_t) 2;
#else
    return (uint32_t) 1;
#endif
}

uint32_t  CHIPCONFIGGetNumPRUSSs(void)
{
    /* Need to use eFUSE MMR info here... */
    return (uint32_t) 1;
}

uint32_t  CHIPCONFIGGetNumIPUs(void)
{
    /* Need to use eFUSE MMR info here... */
    return (uint32_t) 1;
}

uint32_t  CHIPCONFIGGetNumMPUs(void)
{
    /* Need to use eFUSE MMR info here... */
    return (uint32_t) 1;
}

