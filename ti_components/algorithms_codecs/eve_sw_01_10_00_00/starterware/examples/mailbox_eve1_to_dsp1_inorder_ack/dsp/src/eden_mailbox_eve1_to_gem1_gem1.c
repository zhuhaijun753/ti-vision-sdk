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
 *  Filename       gem1/ref_tc_gem1.c
 *
 *  Description    Default code for testcase
 *                 Just returns RET_OK
 *
 * ========================================================================== */

#include <stdio.h>
#include <stdlib.h>

#include <c6x.h>
#include "GlobalTypes.h"
#include "baseaddress.h"
#include "eden_mbids.h"
#include "mbox.h"
#include "INTH_dsp.h"
#include "eve_platform.h"
#include "examples_platform.h"

#define NUM_MSGS              100


void Mailbox_Intr_Handler();

volatile unsigned int mailbox_intr_occurred = 0;

void TSC_enable();
long long TSC_read();
unsigned int profile_array[2];
ReturnCode_t checkReturn = RET_OK;

UWORD32 send_val = 0x12345678;
UWORD32 rcv_val  = 0xBADEBABE;

extern void INTH_Init();

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
  int  i;
  long long t0, t1;
  MBOX_UserId_t userId;

  INTH_Init();

  TSC_enable();

  userId = MBOX_DSP_USER_ID;
  /* Enable interrupt in EVE interrupt controller */
  EVE_HOST_INTH_InterruptSetup(INTH_INT_ID_EVE11SYNC,
                      Mailbox_Intr_Handler,
                      INTH_TYPE_IRQ,
                      INTH_DEFAULT_PRIORITY);

  /* Actually set Enable bit in the interrupt controller */
  EVE_HOST_INTH_InterruptEnable(INTH_INT_ID_EVE11SYNC);

  /* Enable interrupt in the mailbox */
  EVE_MBOX_IrqEnable( EVE1__MAILBOX,
		  GEM1_MBID, /* mailBoxId */
                  userId, /* userId */
                  MBOX_INT_NEW_MSG_ONLY ); /* enableIrq */

  t0 = TSC_read();

  for (i = 0; i < NUM_MSGS; i++)
  {
      printf ("Waiting for %d message \n", i);

      /* Wait for message from eve1 */
      while (mailbox_intr_occurred != 1)
      {
          if ( mailbox_intr_occurred )
          break;
      }

      mailbox_intr_occurred = 0;

      /* After receiving correct message, send a message to eve1 */
      EVE_MBOX_Write( EVE1__MAILBOX, EVE_MBID, /* mailBoxId */ send_val ); /* writeValue */

      rcv_val++;
      send_val++;
  }

  t1 = TSC_read();

  profile_array[0] = (t1 - t0);
  profile_array[1] = 0xBEADBABE;

  Check_status (checkReturn);
  return checkReturn;
}

void Mailbox_Intr_Handler( void )
{
  UWORD32 irqStatusReg = 0;
  MBOX_UserId_t userId;

  userId = MBOX_DSP_USER_ID;

  mailbox_intr_occurred++;

  if ( EVE_MBOX_GetNumMsg( EVE1__MAILBOX, /* component */
                   GEM1_MBID /* mailBoxId */
                   ) != 0 )
         {
             if ( EVE_MBOX_Read( EVE1__MAILBOX, /* component */ GEM1_MBID /* mailBoxId */) == rcv_val)
             {
                irqStatusReg = EVE_MBOX_IrqGetStatus( EVE1__MAILBOX, /* component */
                               GEM1_MBID, /* mailBoxId */
                               userId ) ;

                EVE_MBOX_IrqClearStatus( EVE1__MAILBOX, userId, irqStatusReg);

              }
              else
              {
                checkReturn = RET_FAIL;
              } /* Correct message ? */
          } /* num message ? */
          else
          {
             checkReturn = RET_FAIL;
          }

  printf ("Saw message from EVE \n");

}
