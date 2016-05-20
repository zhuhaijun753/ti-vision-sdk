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
#include "baseaddress.h"

#include "mbox.h"
#include "eden_mbids.h"
#include "INTH.h"
#include "eve_platform.h"
#include "examples_platform.h"
#include  <stdio.h>
#include  <stdlib.h>
#include  <arp32.h>

#define NUM_MSGS  100


#define MBOX_INT0  (MLB0_INT)

void Mailbox_Intr_Handler();

volatile unsigned int mailbox_intr_occurred = 0;

ReturnCode_t checkReturn = RET_OK;

UWORD32 send_val  = 0xBADEBABE;
UWORD32 rcv_val   = 0x12345678;

unsigned int profile_array[2];

void Check_status (int return_value)
{
    if (return_value == RET_OK)
    {
        printf("PASS \n");
    }
    else
    {
        printf("Fail \n");
    }
}


ReturnCode_t test_main( void )
{
  int     i;
  unsigned int t0, t1;

  _tsc_start();

  /* Enable interrupt in EVE interrupt controller */
  EVE_INTH_InterruptSetup(MBOX_INT0,
                      (UWORD32)Mailbox_Intr_Handler,
                      INTH_DEFAULT_INTERRUPT_KIND,
                      INTH_INT4);

  /* Actually set Enable bit in the interrupt controller */
  EVE_INTH_InterruptEnable(MBOX_INT0);

  /* Enable interrupt in the mailbox */
  EVE_MBOX_IrqEnable( MAILBOX,
		          EVE_MBID, /* mailBoxId */
                  MBOX_USER_0, /* userId */
                  MBOX_INT_NEW_MSG_ONLY
                ); /* enableIrq */

  t0   =  _tsc_gettime();
  for (i = 0; i < NUM_MSGS; i++)
  {

      /* Send message to gem1 */
      EVE_MBOX_Write(MAILBOX, GEM1_MBID, /* mailBoxId */ send_val); /* writeValue */

      printf ("Waiting for %d message \n", i);

      while (mailbox_intr_occurred != 1)
      {
          if (mailbox_intr_occurred == 1)   break;
      }

      if (mailbox_intr_occurred == 0)
      {
          checkReturn = RET_FAIL;
          break;
      }

      mailbox_intr_occurred = 0;
      send_val++;
      rcv_val++;
  }
  t1   =  _tsc_gettime();

  profile_array[0]  = (t1 - t0);

  Check_status (checkReturn);
  return checkReturn;
}

void Mailbox_Intr_Handler( void )
{
  UWORD32 irqStatusReg = 0;
  MBOX_UserId_t userId = MBOX_USER_0;

  mailbox_intr_occurred++;

   if ( EVE_MBOX_GetNumMsg( MAILBOX, /* component */
    	               EVE_MBID /* mailBoxId */
		       ) != 0 )
    {
          if ( EVE_MBOX_Read( MAILBOX, /* component */ EVE_MBID /* mailBoxId */) != rcv_val)
          {
             checkReturn = RET_FAIL;
          }

          irqStatusReg = EVE_MBOX_IrqGetStatus( MAILBOX, /* component */
                        EVE_MBID, /* mailBoxId */
                        userId ) ;

          EVE_MBOX_IrqClearStatus( MAILBOX, userId, irqStatusReg);

          #ifdef PRINT_STATUS
          printf ("Saw message from DSP \n");
          #endif
    }
    else
    {
      checkReturn = RET_FAIL;
    }
}
