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
#include "common_utils.h"
#include "INTH.h"

#include  <stdio.h>
#include  <stdlib.h>
#include  <arp32.h>
#include  <vcop/vcop.h>

void Bfswitch_error_Intr_Handler();

volatile unsigned int error_intr_ARP32_occurred = 0;

ReturnCode_t checkReturn = RET_OK;

#pragma DATA_SECTION (in1, "Adata");
unsigned int in1[100] = {0};

#pragma DATA_SECTION (in2, "Bdata");
unsigned int in2[100] = {0};

#pragma DATA_SECTION (in3, "Cdata");
unsigned int in3[100] = {0};

#pragma DATA_SECTION (in4, "Ddata");
unsigned int in4[100] = {0};

#pragma DATA_SECTION (in5, "Edata");
unsigned int in5[100] = {0};

/* Following define is defined temparorily because currently we dont have
starterware API for buffer switch */
#define EVE_MEMSWITCH_ERR_IRQENABLE_SET_REG    	0x40080118
#define EVE_MEMSWITCH_ERR_IRQENABLE_CLR_REG 	0x4008011C
#define EVE_MEMSWITCH_ERR_IRQENABLE_STATUS_REG 	0x40080114
#define EVE_MEMSWITCH_ERR_REG 					0x40080028
#define EVE_MEMSWITCH_ERR_ADDR_REG 				0x4008002C

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


void gen_error (unsigned int *ptr, unsigned int val)
{
    *ptr  = val;

    /* Wait for error to be generated and clear error  */
    while (error_intr_ARP32_occurred != 1);
    error_intr_ARP32_occurred = 0;
}

ReturnCode_t test_main( void )
{

    _tsc_start();

    /* Enable interrupt in EVE interrupt controller */
    EVE_INTH_InterruptSetup(EVE_MSW_ERR_INT,
                      (UWORD32)Bfswitch_error_Intr_Handler,
                      INTH_DEFAULT_INTERRUPT_KIND,
                      INTH_INT4);

    /* Actually set Enable bit in the interrupt controller */
    EVE_INTH_InterruptEnable(EVE_MSW_ERR_INT);

    /* Actually enable the bit in MSW_ERR IRQ enable for all MSW errors*/
    //WR_REG_32 (EVE_CONTROL, EVE_CONTROL__EVE_MSW_ERR_IRQENABLE_SET, 0xF);
	WR_MEM_32_VOLATILE (EVE_MEMSWITCH_ERR_IRQENABLE_SET_REG, 0xF );

    /* Purposefully transfer IBUFLA to VCOP and write to generate error  */
    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_VCOP);

    /* Write and generate an error */
    gen_error (&in1[0], 0xDEADBEEF);

    /* Write and generate another error */
    gen_error (&in1[99], 0xFEADFADE);

    /* Purposefully transfer IBUFLB to VCOP and write to generate error  */
    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_VCOP, IBUFLA_SYST);

    /* Write and generate an error */
    gen_error (&in2[0], 0xDEADBEEF);

    /* Write and generate another error */
    gen_error (&in2[99], 0xFEADFADE);

    /* Purposefully transfer WBUF to VCOP and write to generate error  */
    VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

    /* Write and generate an error */
    gen_error (&in3[0], 0xDEADBEEF);

    /* Write and generate another error */
    gen_error (&in3[99], 0xFEADFADE);

    /* Purposefully transfer IBUFLB to VCOP and write to generate error  */
    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_VCOP, IBUFHA_SYST, IBUFLA_SYST);

    /* Write and generate an error */
    gen_error (&in4[0], 0xDEADBEEF);

    /* Write and generate another error */
    gen_error (&in4[99], 0xFEADFADE);

    /* Purposefully transfer IBUFHB to VCOP and write to generate error  */
    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_VCOP, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

    /* Write and generate an error */
    gen_error (&in5[0], 0xDEADBEEF);

    /* Write and generate another error */
    gen_error (&in5[99], 0xFEADFADE);

    /* Set pass code.                                  */
    checkReturn = RET_OK;
  
    /* Actually disable the bit in MSW_ERR IRQ enable */
    //WR_REG_32 (EVE_CONTROL, EVE_CONTROL__EVE_MSW_ERR_IRQENABLE_CLR, 0xF);
	WR_MEM_32_VOLATILE (EVE_MEMSWITCH_ERR_IRQENABLE_CLR_REG, 0xF );

    /* Transfer all buffers back to system            */
    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

    Check_status (checkReturn);

    return checkReturn;
}

void Bfswitch_error_Intr_Handler( void )
{
  unsigned int value;
  unsigned int err_addr;
  unsigned int value_MSW_IRQStatus;

  
  //value_MSW_IRQStatus = RD_REG_32 (EVE_CONTROL, EVE_CONTROL__EVE_MSW_ERR_IRQSTATUS);
  value_MSW_IRQStatus = RD_MEM_32_VOLATILE (EVE_MEMSWITCH_ERR_IRQENABLE_STATUS_REG);

  //value     = RD_REG_32 (EVE_CONTROL, EVE_CONTROL__EVE_MSW_ERR);
  value     = RD_MEM_32_VOLATILE (EVE_MEMSWITCH_ERR_REG);
  //err_addr  = RD_REG_32 (EVE_CONTROL, EVE_CONTROL__EVE_MSW_ERRADDR);
  err_addr     = RD_MEM_32_VOLATILE (EVE_MEMSWITCH_ERR_ADDR_REG);

  if (value & 1)
  {

  printf ("Fatal ARP32 Error at address 0x%.8x \n", err_addr);
      //MASKWR_REG_32 (EVE_CONTROL, EVE_CONTROL__EVE_MSW_ERR, 1, 1);
	  MASKWR_REG_32 (EVE_MEMSWITCH_ERR_REG, 1, 1);
  }

  if (value & 2)
  {
      printf ("Fatal VCOP Error at address 0x%.8x \n", err_addr);
      //MASKWR_REG_32 (EVE_CONTROL, EVE_CONTROL__EVE_MSW_ERR, 2, 2);
	  MASKWR_REG_32 (EVE_MEMSWITCH_ERR_REG, 2, 2);
  }

  if (value & 4)
  {
      printf ("Fatal DMA error at 0x%.8x \n", err_addr);
      //MASKWR_REG_32 (EVE_CONTROL, EVE_CONTROL__EVE_MSW_ERR, 4, 4);
	  MASKWR_REG_32 (EVE_MEMSWITCH_ERR_REG, 4, 4);
  }
      
  if (value & 8)
  {
      printf ("Fatal External Host DSP/ARM error at 0x%.8x\n", err_addr);
      //MASKWR_REG_32 (EVE_CONTROL, EVE_CONTROL__EVE_MSW_ERR, 8, 8);
	  MASKWR_REG_32 (EVE_MEMSWITCH_ERR_REG, 8, 8);
  }

  if (value)  error_intr_ARP32_occurred++;

  //WR_REG_32 (EVE_CONTROL, EVE_CONTROL__EVE_MSW_ERR_IRQSTATUS, value_MSW_IRQStatus);
  WR_MEM_32_VOLATILE (EVE_MEMSWITCH_ERR_IRQENABLE_STATUS_REG, value_MSW_IRQStatus);
}

