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
 *  Filename       gem1/gem1_main.c
 *
 *  Description    main function
 *                 Calls SoC_Init and then test_main, and then test_done
 *
 * ========================================================================== */
#include "GlobalTypes.h"

ReturnCode_t test_main( void );

int main( void )
{
  ReturnCode_t checkReturn;

  checkReturn = test_main();

  //test_done( checkReturn );

  while( 1 );

}
