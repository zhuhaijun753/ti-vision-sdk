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
#include <c6x.h>
#include "GlobalTypes.h"
#include "baseaddress.h"

#include "eden_mbids.h"
#include "mbox.h"
#include "INTH_dsp.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define INTH_INT_ID_EVE11SYNC 90
#define INTH_INT_ID_EVE22SYNC 91
#define INTH_INT_ID_EVE33SYNC 92
#define INTH_INT_ID_EVE44SYNC 93

#define EVE1__MAILBOX (EVE1__MLB0)
#define EVE2__MAILBOX (EVE2__MLB0)
#define EVE3__MAILBOX (EVE3__MLB0)
#define EVE4__MAILBOX (EVE4__MLB0)

void Mailbox_Intr_Handler(unsigned int evt_no);

volatile unsigned int mailbox_intr_occurred_eve1 = 0;
volatile unsigned int mailbox_intr_occurred_eve2 = 0;
volatile unsigned int mailbox_intr_occurred_eve3 = 0;
volatile unsigned int mailbox_intr_occurred_eve4 = 0;

void TSC_enable();
long long TSC_read();  
unsigned int profile_array[2];
ReturnCode_t checkReturn = RET_OK;

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
  long long t0, t1;
  int       all_msgs = 0;

  INTH_Init();

  TSC_enable();

  /* Enable interrupt in EVE interrupt controller for all EVE's*/
  EVE_HOST_INTH_InterruptSetup(INTH_INT_ID_EVE11SYNC,
                      Mailbox_Intr_Handler,
                      INTH_TYPE_IRQ,
                      INTH_DEFAULT_PRIORITY);

  EVE_HOST_INTH_InterruptSetup(INTH_INT_ID_EVE22SYNC,
                      Mailbox_Intr_Handler,
                      INTH_TYPE_IRQ,
                      INTH_DEFAULT_PRIORITY);

  EVE_HOST_INTH_InterruptSetup(INTH_INT_ID_EVE33SYNC,
                      Mailbox_Intr_Handler,
                      INTH_TYPE_IRQ,
                      INTH_DEFAULT_PRIORITY);

  EVE_HOST_INTH_InterruptSetup(INTH_INT_ID_EVE44SYNC,
                      Mailbox_Intr_Handler,
                      INTH_TYPE_IRQ,
                      INTH_DEFAULT_PRIORITY);

  printf("DSP - Interrupt Setup Done \n");
  /* Actually set Enable bit in the interrupt controller */
  EVE_HOST_INTH_InterruptEnable(INTH_INT_ID_EVE11SYNC);
  EVE_HOST_INTH_InterruptEnable(INTH_INT_ID_EVE22SYNC);
  EVE_HOST_INTH_InterruptEnable(INTH_INT_ID_EVE33SYNC);
  EVE_HOST_INTH_InterruptEnable(INTH_INT_ID_EVE44SYNC);

  printf("DSP - Interrupt Enable Done \n");  
  /* Enable interrupt in the mailbox for all EVE's */

  EVE_MBOX_IrqEnable( EVE1__MAILBOX, GEM1_MBID, MBOX_USER_1, MBOX_INT_NEW_MSG_ONLY ); /* enableIrq */
  EVE_MBOX_IrqEnable( EVE2__MAILBOX, GEM1_MBID, MBOX_USER_1, MBOX_INT_NEW_MSG_ONLY ); /* enableIrq */
  EVE_MBOX_IrqEnable( EVE3__MAILBOX, GEM1_MBID, MBOX_USER_1, MBOX_INT_NEW_MSG_ONLY ); /* enableIrq */
  EVE_MBOX_IrqEnable( EVE4__MAILBOX, GEM1_MBID, MBOX_USER_1, MBOX_INT_NEW_MSG_ONLY ); /* enableIrq */

  t0   =  TSC_read();

  

  /* Wait for message from eve1 */
  while (all_msgs != 4)
  {
      all_msgs = (
                    mailbox_intr_occurred_eve1 +
                    mailbox_intr_occurred_eve2 +
                    mailbox_intr_occurred_eve3 +
                    mailbox_intr_occurred_eve4 
                 );

  }

  t1   =  TSC_read();

  profile_array[0] = (t1 - t0);

  t0  =   TSC_read();

  if (mailbox_intr_occurred_eve1  == 0)  checkReturn = RET_FAIL;
  if (mailbox_intr_occurred_eve2  == 0)  checkReturn = RET_FAIL;
  if (mailbox_intr_occurred_eve3  == 0)  checkReturn = RET_FAIL;
  if (mailbox_intr_occurred_eve4  == 0)  checkReturn = RET_FAIL;

  t1 = TSC_read();

  profile_array[1] = (t1 - t0);

  Check_status (checkReturn);

  return checkReturn;
}

void Mailbox_Intr_Handler(unsigned int event)
{
  UWORD32 irqStatusReg = 0;
  MBOX_UserId_t userId = MBOX_USER_1;

  CRED_index_t mailbox;
  UWORD32      rcv_msg;
  UWORD32      snd_msg;
  UWORD32      eve_no;
  UWORD32      rcvd_msg;

  switch (event)
  {
      case INTH_INT_ID_EVE11SYNC:
          mailbox = EVE1__MAILBOX;
          rcv_msg = 0xbadebabe;
          snd_msg = 0x12345678;
          eve_no  = 0;
          mailbox_intr_occurred_eve1++;
          break;

      case INTH_INT_ID_EVE22SYNC:
          mailbox = EVE2__MAILBOX;
          rcv_msg = 0xbadebabf;
          snd_msg = 0x12345679;
          eve_no  = 1;
          mailbox_intr_occurred_eve2++;
          break;

      case INTH_INT_ID_EVE33SYNC:
          mailbox = EVE3__MAILBOX;
          rcv_msg = 0xbadebac0;
          snd_msg = 0x1234567A;
          eve_no  = 2;
          mailbox_intr_occurred_eve3++;
          break;

      case INTH_INT_ID_EVE44SYNC:
          mailbox = EVE4__MAILBOX;
          rcv_msg = 0xbadebac1;
          snd_msg = 0x1234567B;
          eve_no  = 3;
          mailbox_intr_occurred_eve4++;
          break;
 }

 assert ((event >=90) && (event <= 93));

  if ( EVE_MBOX_GetNumMsg( mailbox, /* component */
                   GEM1_MBID /* mailBoxId */
                   ) != 0 )
         {
             rcvd_msg = EVE_MBOX_Read(mailbox, GEM1_MBID);

             if (rcvd_msg == rcv_msg)
             {
                irqStatusReg = EVE_MBOX_IrqGetStatus( mailbox, /* component */
                               GEM1_MBID, /* mailBoxId */
                               userId ) ;

                EVE_MBOX_IrqClearStatus(mailbox, userId, irqStatusReg);

                /* After receiving correct message, send a message to eve1 */
                EVE_MBOX_Write(mailbox,
                    EVE_MBID, /* mailBoxId */
                    snd_msg ); /* writeValue */
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

  printf ("Saw message from EVE :%d, message:0x%.8x \n", eve_no, rcvd_msg);

}
