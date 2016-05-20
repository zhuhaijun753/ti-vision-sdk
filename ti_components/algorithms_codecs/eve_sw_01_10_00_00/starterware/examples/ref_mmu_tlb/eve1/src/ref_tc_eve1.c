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

ReturnCode_t test_main( void )
{
  unsigned int *ptr_ocmc_ram_reg0, *ptr_ocmc_ram_reg1;
  ReturnCode_t checkReturn = RET_OK;


  /* Write to the beginning og the region 0 */
  ptr_ocmc_ram_reg0 = (unsigned int *)(0x50300000);
  *ptr_ocmc_ram_reg0 = 0xDEADBEEF;
  while (*ptr_ocmc_ram_reg0 != 0xDEADBEEF);

  /* Write to the end of the region 0 */
  ptr_ocmc_ram_reg0 = (unsigned int *)(0x50300FFC);
  *ptr_ocmc_ram_reg0 = 0xFADEBABE;
  while (*ptr_ocmc_ram_reg0 != 0xFADEBABE);

  /* Write to the beginning of the region 1 */
  ptr_ocmc_ram_reg1 = (unsigned int *) (0x50310000);
  *ptr_ocmc_ram_reg1 = 0xDEADBEEF;
  while (*ptr_ocmc_ram_reg1 != 0xDEADBEEF);

  /* Write to the end of the region 1 + 16K */
  ptr_ocmc_ram_reg1 = (unsigned int *) (0x5031FFFC);
  *ptr_ocmc_ram_reg1 = 0xFADEBABE;
  while (*ptr_ocmc_ram_reg1 != 0xFADEBABE);

  return checkReturn;
}
