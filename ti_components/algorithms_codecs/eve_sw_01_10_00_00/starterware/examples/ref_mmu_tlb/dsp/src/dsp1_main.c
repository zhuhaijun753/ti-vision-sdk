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

#include "baseaddress.h"
//#include "EMIF4D_CRED.h"
#include "mmu.h"

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

/* OCMCRAM region1 as 64KB section        */

#define PHY_ADDR5    0x40310000
#define VIRT_ADDR5   0x50310000


#define MMU_ID EVE1__MMU0


void MMU_TLB_Configure_MM0()
{
  MMU_TlbEntry_t  mmu_entry;


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

  EVE_MMU_TlbEntrySet( MMU_ID, 3, &mmu_entry );

  /* Configure MMU Tlb Entry for 4KB of OCMCRAM */
  mmu_entry.phyAddr         = PHY_ADDR4;
  mmu_entry.virtAddr        = VIRT_ADDR4;
  mmu_entry.valid           = true;
  mmu_entry.pageSize        = MMU_Small_Size;
  mmu_entry.endianness      = MMU_Little_Endian;
  mmu_entry.elementSize     = MMU_NoTranslation_ElementSize;
  mmu_entry.tlbElementSize  = MMU_CPU_ElementSize;
  mmu_entry.preserve        = true;

  EVE_MMU_TlbEntrySet( MMU_ID, 4, &mmu_entry );

  /* Configure MMU Tlb Entry for 64KB of OCMCRAM */
  mmu_entry.phyAddr         = PHY_ADDR5;
  mmu_entry.virtAddr        = VIRT_ADDR5;
  mmu_entry.valid           = true;
  mmu_entry.pageSize        = MMU_Large_Size;
  mmu_entry.endianness      = MMU_Little_Endian;
  mmu_entry.elementSize     = MMU_NoTranslation_ElementSize;
  mmu_entry.tlbElementSize  = MMU_CPU_ElementSize;
  mmu_entry.preserve        = true;

  EVE_MMU_TlbEntrySet( MMU_ID, 5, &mmu_entry );

  /* Enable MMU */
  EVE_MMU_Enable(MMU_ID);
}


ReturnCode_t test_main( void );

#if 0
void MY_MEMCFG_ConfigureDDR ( void)
{
    volatile unsigned int *ddrptr = (volatile unsigned int *)0x80000000;
    unsigned int prev_word;
    unsigned int wrword;
    unsigned int rdword;

    /*Program EMIF CFG Registers*/
    WR_REG_32(EMIF4D, EMIF4D__DDR_PHY_CTRL_1, 0x2);//RL =6
    WR_REG_32(EMIF4D, EMIF4D__DDR_PHY_CTRL_1_SHDW, 0x2);//RL =6
    WR_REG_32(EMIF4D, EMIF4D__SDRAM_TIM_1, 0x0666a391);
    WR_REG_32(EMIF4D, EMIF4D__SDRAM_TIM_1_SHDW, 0x0666a391);
    WR_REG_32(EMIF4D, EMIF4D__SDRAM_TIM_2, 0x001631fa);
    WR_REG_32(EMIF4D, EMIF4D__SDRAM_TIM_2_SHDW, 0x001631fa);
    WR_REG_32(EMIF4D, EMIF4D__SDRAM_REF_CTRL, 0x10000618);
    WR_REG_32(EMIF4D, EMIF4D__SDRAM_REF_CTRL_SHDW, 0x10000618);
    WR_REG_32(EMIF4D, EMIF4D__SDRAM_CONFIG, 0x40800CB2);// CL = 3

    prev_word = *ddrptr;
    wrword = 0x12345678;
    *ddrptr = wrword;
    rdword = *ddrptr;
    *ddrptr = prev_word;
}
#endif

int main( void )
{
  ReturnCode_t checkReturn;

  MMU_TLB_Configure_MM0();
/* don't run that on silicon since it is done by gel file
  MY_MEMCFG_ConfigureDDR();
*/

  checkReturn = test_main();

  //test_done( checkReturn );

  while( 1 );

}
