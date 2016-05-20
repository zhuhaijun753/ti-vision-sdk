/*==========================================================================*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#include "cram.h"
#include "baseaddress.h"
#include "EMIF4D_CRED.h"

void MEMCFG_ConfigureDDR ( void)
{
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
	    
}
