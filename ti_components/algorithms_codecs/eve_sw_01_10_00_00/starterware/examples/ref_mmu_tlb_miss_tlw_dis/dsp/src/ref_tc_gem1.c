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
#include "mmu.h"
#include "INTH.h"
#include "ICRegAcM.h"

#include "common_utils.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef VAYU_PLATFORM
#define EVE_CONTROL__EVE_INT0_OUT_IRQSTATUS_RAW_REG (0x42080000+ 0x520)
#define TESLASS_MMU__MMU_FAULT_AD_REG (0x42081000 + 0x48)
#define TESLASS_MMU__MMU_CNTL_REG (0x42081000 + 0x44)
#endif

#ifdef VME_PLATFORM
#define EVE_CONTROL__EVE_INT0_OUT_IRQSTATUS_RAW_REG (0x59080000 + 0x520)
#define TESLASS_MMU__MMU_FAULT_AD_REG (0x59081000 + 0x48)
#define TESLASS_MMU__MMU_CNTL_REG (0x59081000 + 0x44)
#endif


/*-------------------------------------------------------------------------*//**
 * @DEFINITION BITS_32 
 *
 * @BRIEF      returns in_NbBits+1 bits to '1' starting from bit 0
 *//*------------------------------------------------------------------------ */
#ifndef BITS_32
  #define BITS_32(in_NbBits) \
    ( ( ( (UWORD32)1 << in_NbBits ) - 1 ) | ( (UWORD32)1 << in_NbBits ) )
#endif

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   TESLASS_MMU__MMU_CNTL__MMUENABLE   
 *
 * @BRIEF        MMU enable - (RW) 
 *
 *//*------------------------------------------------------------------------ */
 #ifndef BITFIELD_32
  #define BITFIELD_32(in_UpBit, in_LowBit) \
    ( BITS_32(in_UpBit) & ~((BITS_32(in_LowBit)) >> 1 ))
#endif

#define TESLASS_MMU__MMU_CNTL__MMUENABLE                      BITFIELD_32(1, 1)


/* Reset vector mapping as Section of 1 MB*/
#define PHY_ADDR1    0x80000000
#define VIRT_ADDR1   0x00000000

/* External memory mappping as a super section of 16 MB*/
#define PHY_ADDR2    0x80000000
#define VIRT_ADDR2   0x80000000

/* Region used by EDEN testbench reserved      */
#define PHY_ADDR3    0x48030000
#define VIRT_ADDR3   0x48030000

/* OCMCRAM region0 as 4KB section        */
#define PHY_ADDR4    0x40300000
#define VIRT_ADDR4   0x50300000

/* OCMCRAM region1 as 4KB section        */

#define PHY_ADDR5    0x40301000
#define VIRT_ADDR5   0x50301000

#define MMU_ID       EVE1__MMU0
#define MMU_INT_ID   MMU0_INT



void MMU_Intr_Handler();

volatile unsigned int mmu_intr_occurred = 0;

void TSC_enable();
long long TSC_read();  
unsigned int profile_array[2];
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

ReturnCode_t MMU_Configure()
{
  MMU_TlbEntry_t  mmu_entry;
  ReturnCode_t    checkReturn = RET_OK;
  UWORD32         rd_value;

  /* Configure MMU Tlb Entry for mapping reset vector of 4KB*/
  mmu_entry.phyAddr         = PHY_ADDR1;
  mmu_entry.virtAddr        = VIRT_ADDR1;
  mmu_entry.valid           = true;
  mmu_entry.pageSize        = MMU_Small_Size;
  mmu_entry.endianness      = MMU_Little_Endian;
  mmu_entry.elementSize     = MMU_NoTranslation_ElementSize;
  mmu_entry.tlbElementSize  = MMU_CPU_ElementSize;
  mmu_entry.preserve        = true;

  EVE_MMU_TlbEntrySet( MMU_ID, 1, &mmu_entry );

  /* Configure MMU Tlb Entry for DDR Data  as 16 MB Supersection*/
  mmu_entry.phyAddr         = PHY_ADDR2;
  mmu_entry.virtAddr        = VIRT_ADDR2;
  mmu_entry.valid           = true;
  mmu_entry.pageSize        = MMU_SuperSection_Size;
  mmu_entry.endianness      = MMU_Little_Endian;
  mmu_entry.elementSize     = MMU_NoTranslation_ElementSize;
  mmu_entry.tlbElementSize  = MMU_CPU_ElementSize;
  mmu_entry.preserve        = true;

  EVE_MMU_TlbEntrySet( MMU_ID, 2, &mmu_entry);

  /* Configure MMU Tlb Entry for test_done needed for reporting pass/fail for local test environment */
  /* Not needed in general and is typically unimplemented memory at SOC level. Consult your specific */
  /* SOC. 1MB region.                                                                                */

  mmu_entry.phyAddr         = PHY_ADDR3;
  mmu_entry.virtAddr        = VIRT_ADDR3;
  mmu_entry.valid           = true;
  mmu_entry.pageSize        = MMU_Section_Size;
  mmu_entry.endianness      = MMU_Little_Endian;
  mmu_entry.elementSize     = MMU_NoTranslation_ElementSize;
  mmu_entry.tlbElementSize  = MMU_CPU_ElementSize;
  mmu_entry.preserve        = true;

  EVE_MMU_TlbEntrySet( MMU_ID, 3, &mmu_entry);


  EVE_MMU_IrqEnable ( MMU_ID, MMU_INT_All );
  
    /* Enable MMU */
  EVE_MMU_Enable(MMU_ID);

  //rd_value= RD_REG_32 (MMU_ID, TESLASS_MMU__MMU_CNTL );
  rd_value= RD_MEM_32_VOLATILE(TESLASS_MMU__MMU_CNTL_REG );
	
  if (rd_value != TESLASS_MMU__MMU_CNTL__MMUENABLE) 
  {
     checkReturn = RET_FAIL;
     return (checkReturn);
  }

  return (checkReturn);
}
   



ReturnCode_t test_main( void )
{
  long long t0, t1;
  ReturnCode_t  checkReturn;
  UWORD32       rd_value;


  TSC_enable();

  /* Configure the MMU, enable MMU interrupt  */
  checkReturn = MMU_Configure();

  /* Release reset from eve */
  //release_eve1_reset();

  t0   =  TSC_read();

  //rd_value = RD_REG_32 (EVE1__EVE_CONTROL, EVE_CONTROL__EVE_INT0_OUT_IRQSTATUS_RAW);
  //RD_MEM_32_VOLATILE(EVE_CONTROL__EVE_INT0_OUT_IRQSTATUS_RAW_REG);
  
  //rd_value = RD_REG_32 (EVE1__EVE_CONTROL, EVE_CONTROL__EVE_INT0_OUT_IRQSTATUS_RAW);
  rd_value = RD_MEM_32_VOLATILE(EVE_CONTROL__EVE_INT0_OUT_IRQSTATUS_RAW_REG);
  /* Wait for event from MMU0 whcih is event 21 */
  while (rd_value != 0x200000)
  {
      //rd_value = RD_REG_32 (EVE1__EVE_CONTROL, EVE_CONTROL__EVE_INT0_OUT_IRQSTATUS_RAW);
	  rd_value = RD_MEM_32_VOLATILE(EVE_CONTROL__EVE_INT0_OUT_IRQSTATUS_RAW_REG);
  }

  MMU_Intr_Handler();

  t1   =  TSC_read();

  profile_array[0] = (t1 - t0);

  t0  =   TSC_read();

  if (mmu_intr_occurred  == 0)  checkReturn = RET_FAIL;

  t1 = TSC_read();

  profile_array[1] = (t1 - t0);

  Check_status (checkReturn);

  return checkReturn;
}


void MMU_Intr_Handler( void )
{
  MMU_TlbEntry_t  mmu1;
  UWORD32         fault_addr;
  UWORD32         status;
  

  //fault_addr = RD_REG_32(MMU_ID,TESLASS_MMU__MMU_FAULT_AD);
  fault_addr = RD_MEM_32_VOLATILE(TESLASS_MMU__MMU_FAULT_AD_REG);
  
  status     = EVE_MMU_IrqGetStatus( MMU_ID );

  printf ("EVE generated a fault at address: 0x%.8x \n", fault_addr);
  printf ("status: %d \n", status);

  if (status == (MMU_INT_TLBMiss)) 
  {
    if (fault_addr == VIRT_ADDR4) 
    {
      mmu1.phyAddr         = PHY_ADDR4;
      mmu1.virtAddr        = VIRT_ADDR4;
      mmu1.valid           = true;
      mmu1.pageSize        = MMU_Small_Size;
      mmu1.endianness      = MMU_Little_Endian;
      mmu1.elementSize     = MMU_NoTranslation_ElementSize;
      mmu1.tlbElementSize  = MMU_CPU_ElementSize;
      mmu1.preserve        = true;

      EVE_MMU_TlbEntrySet( MMU_ID, 4, &mmu1 );      
      mmu_intr_occurred ++;
    }
  }

  EVE_MMU_IrqClearStatus(MMU_ID, MMU_INT_TLBMiss);
}


