
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
 *   Filename:          sbl_tda2xx_image_copy.h
 *
 *   Description:       This file contain imagecopy wrapper function, based on
 *                      boot-mode call the respective Bootrprc function
 */
#ifndef SBL_TDA2xx_IMAGE_COPY_H_
#define SBL_TDA2xx_IMAGE_COPY_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include "hw_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/*
 * \brief       ImageCopy function is a wrapper to Multicore Image parser
 ********function. Based on boot-mode jump into specific
 *                  function
 *
 * \param   none
 *
 * \return   error status.If error has occured it returns a non zero value.
 *             If no error has occured then return status will be zero. .
 *
 */
int32_t ImageCopy(void);

#ifdef __cplusplus
}
#endif

#endif /*SBL_TDA2xx_IMAGE_COPY_H_*/
