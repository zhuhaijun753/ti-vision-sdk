/* =============================================================================
 *
 *            TEXAS INSTRUMENTS INCORPORATED PROPRIETARY INFORMATION
 *
 *  Property of Texas Instruments
 *  For Unrestricted Internal Use Only
 *  Unauthorized reproduction and/or distribution is strictly
 *  prohibited.
 *  This product is protected under copyright law and trade secret law
 *  as an unpublished work.
 *  Created 2007, (C) Copyright 2007 Texas Instruments.  All rights
 *  reserved.
 */
/**
 *  Filename       eve1/ref_tc_eve1.c
 *
 *  Description    Default code for testcase
 *                 Just returns RET_OK
 *
 * ========================================================================== */
#include "GlobalTypes.h"

#define VIRT_ADDR4   0x50300000

ReturnCode_t test_main( void )
{
  unsigned int *ptr = (unsigned int *) (VIRT_ADDR4);

  *ptr = 0xDEADBEEF;
  while (*ptr != 0xDEADBEEF);

  ReturnCode_t checkReturn = RET_OK;
  return checkReturn;
}
