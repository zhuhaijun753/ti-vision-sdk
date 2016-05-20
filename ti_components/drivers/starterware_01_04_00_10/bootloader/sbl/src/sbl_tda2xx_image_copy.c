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
 *   Component:     SBL
 *
 *   Filename:      sbl_tda2xx_image_copy.c
 *
 *   Description:   This file contain imagecopy wrapper function, based on
 *                  boot-mode call the respective Bootrprc function
 */

/****************************************************************
 *  INCLUDE FILES
 ****************************************************************/
#include <stdint.h>
#include "soc_defines.h"
#include "uartConsole.h"
#include "sbl_tda2xx_image_copy.h"
#include "sbl_rprc_parse.h"

/* ============================================================================
 * GLOBAL VARIABLES DECLARATIONS
 * =============================================================================
 */

/* ============================================================================
 * LOCAL VARIABLES DECLARATIONS
 * =============================================================================
 *
 *
 ************============================================================================
 * LOCAL FUNCTIONS PROTOTYPES
 * =============================================================================
 */

/* ============================================================================
 * FUNCTIONS
 * =============================================================================
 */

/*
 * \brief       ImageCopy function is a wrapper to Multicore Image parser
 *              function. Based on boot-mode jump into specific
 *              function
 *
 * \param   none
 *
 * \return   error status.If error has occured it returns a non zero value.
 *             If no error has occured then return status will be zero. .
 *
 */
int32_t ImageCopy(void)
{
    int32_t retval = 0;

#ifdef SPI
    if (SPIBootRprc() != E_PASS)
#elif defined (MMCSD)
    if (MMCSDBootRprc() != E_PASS)
#elif defined (NOR)
    if (NORBootRprc() != E_PASS)

#elif defined (QSPI)
    if (QSPIBootRprc() != E_PASS)

#elif defined (ZEBU_DDR3)
    if (DDR3BootRprc() != E_PASS)

#elif defined (SBL_REGRESSION)
    if (MMCSDBootRprc_Regression() != E_PASS)

#else
#error Unsupported boot mode !!
#endif
    {
        retval = -1;
    }

    return retval;
}

/***************************** End Of File ***********************************/

