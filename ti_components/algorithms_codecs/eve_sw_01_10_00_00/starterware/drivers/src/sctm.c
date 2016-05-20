/*==========================================================================*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#include "GlobalTypes.h"
#include "cram.h"

#pragma CHECK_MISRA ("none")
#include "baseaddress.h"
#include "ctm_cred.h"
#pragma RESET_MISRA ("required")

#include "sctm.h"



void EVE_SCTM_Enable( CRED_index_t component)
{
  WR_REG_32(component,CTM__CTCNTL,CTM__CTCNTL__ENBL);
}

void EVE_SCTM_CounterReset( CRED_index_t component, SCTM_Counter_type_t counter_no)
{
  UWORD32 lval;

  if((counter_no == SCTM_Counter_0) || (counter_no == SCTM_Counter_1)) {
    lval = RD_REG_ARRAY_32(component,CTM__CTCR_WT,counter_no, CTM__CTCR_WT__ELSIZE);
    WR_REG_ARRAY_32(component,CTM__CTCR_WT,counter_no,(lval|CTM__CTCR_WT__RESET), CTM__CTCR_WT__ELSIZE);
  }
  else {
    lval = RD_REG_ARRAY_32(component,CTM__CTCR_WOT,(counter_no-2), CTM__CTCR_WOT__ELSIZE);
    WR_REG_ARRAY_32(component,CTM__CTCR_WOT,(counter_no-2),(lval|CTM__CTCR_WOT__RESET), CTM__CTCR_WOT__ELSIZE);
  }
}

void EVE_SCTM_ChainModeEnable( CRED_index_t component, SCTM_Counter_type_t counter_no)
{
  UWORD32 lval;

  if((counter_no == SCTM_Counter_0) || (counter_no == SCTM_Counter_1)) {
    lval = RD_REG_ARRAY_32(component,CTM__CTCR_WT,counter_no, CTM__CTCR_WT__ELSIZE);
    WR_REG_ARRAY_32(component,CTM__CTCR_WT,counter_no,(lval|CTM__CTCR_WT__CHAIN), CTM__CTCR_WT__ELSIZE);
  }
  else {
    lval = RD_REG_ARRAY_32(component,CTM__CTCR_WOT,(counter_no-2), CTM__CTCR_WOT__ELSIZE);
    WR_REG_ARRAY_32(component,CTM__CTCR_WOT,(counter_no-2),(lval|CTM__CTCR_WOT__CHAIN), CTM__CTCR_WOT__ELSIZE);
  }
}

void EVE_SCTM_InpEvtSelect( CRED_index_t component, SCTM_Counter_type_t counter_no, SCTM_Event_type_t inpsel)
{
  UWORD32 lval;

  if((counter_no == SCTM_Counter_0) || (counter_no == SCTM_Counter_1)) {
    lval = RD_REG_ARRAY_32(component,CTM__CTCR_WT,counter_no, CTM__CTCR_WT__ELSIZE);
    WR_REG_ARRAY_32(component,CTM__CTCR_WT,counter_no,(lval|((UWORD32)inpsel << CTM__CTCR_WT__INPSEL__POS)), CTM__CTCR_WT__ELSIZE);
  }
  else {
    lval = RD_REG_ARRAY_32(component,CTM__CTCR_WOT,(counter_no-2), CTM__CTCR_WOT__ELSIZE);
    WR_REG_ARRAY_32(component,CTM__CTCR_WOT,(counter_no-2),(lval|((UWORD32)inpsel << CTM__CTCR_WOT__INPSEL__POS)), CTM__CTCR_WOT__ELSIZE);
  }
}

void EVE_SCTM_SamplingSelect( CRED_index_t component, SCTM_Counter_type_t counter_no, SCTM_Sampling_type_t samping_type)
{
  UWORD32 lval;

  if((counter_no == SCTM_Counter_0) || (counter_no == SCTM_Counter_1)) {
    lval = RD_REG_ARRAY_32(component,CTM__CTCR_WT,counter_no, CTM__CTCR_WT__ELSIZE);
    WR_REG_ARRAY_32(component,CTM__CTCR_WT,counter_no,(lval|((UWORD32)samping_type << CTM__CTCR_WT__DURMODE__POS)), CTM__CTCR_WT__ELSIZE);
  }
  else {
    lval = RD_REG_ARRAY_32(component,CTM__CTCR_WOT,(counter_no-2), CTM__CTCR_WOT__ELSIZE);
    WR_REG_ARRAY_32(component,CTM__CTCR_WOT,(counter_no-2),(lval|((UWORD32)samping_type << CTM__CTCR_WT__DURMODE__POS)), CTM__CTCR_WOT__ELSIZE);
  }
}

void EVE_SCTM_CounterTimerEnable( CRED_index_t component, SCTM_Counter_type_t counter_no)
{
  UWORD32 currentEnableCounters;

  currentEnableCounters = RD_REG_32(component,CTM__CTGNBL);
  currentEnableCounters = currentEnableCounters | (UWORD32)counter_no;
  currentEnableCounters = currentEnableCounters | (UWORD32)CTM__CTCR_WT__ENBL;

  EVE_SCTM_MultipleCountersEnable(component , currentEnableCounters);

#if 0
  if((counter_no == SCTM_Counter_0) || (counter_no == SCTM_Counter_1)) {
    lval = RD_REG_ARRAY_32(component,CTM__CTCR_WT,counter_no, CTM__CTCR_WT__ELSIZE);
    WR_REG_ARRAY_32(component,CTM__CTCR_WT,counter_no,(lval|CTM__CTCR_WT__ENBL), CTM__CTCR_WT__ELSIZE);
  }
  else {
    lval = RD_REG_ARRAY_32(component,CTM__CTCR_WOT,(counter_no-2), CTM__CTCR_WOT__ELSIZE);
    WR_REG_ARRAY_32(component,CTM__CTCR_WOT,(counter_no-2),(lval|CTM__CTCR_WOT__ENBL), CTM__CTCR_WOT__ELSIZE);
  }

  lval = RD_REG_32(component,CTM__CTCNTL);
  WR_REG_32(component,CTM__CTCNTL,lval);
#endif
}

void EVE_SCTM_CounterTimerDisable( CRED_index_t component, SCTM_Counter_type_t counter_no)
{
  if((counter_no == SCTM_Counter_0) || (counter_no == SCTM_Counter_1)) {
    WR_REG_ARRAY_32(component,CTM__CTCR_WT,counter_no,0x00000000, CTM__CTCR_WT__ELSIZE);
  }
  else {
    WR_REG_ARRAY_32(component,CTM__CTCR_WOT,(counter_no-2),0x00000000, CTM__CTCR_WOT__ELSIZE);
  }
}

void EVE_SCTM_MultipleCountersEnable( CRED_index_t component, UWORD32 counter_no)
{
 UWORD32 lval;
    /* Fix for the hardware bug :  OMAPS00299074
  Any dummy write to CTCTNL register before enabling counter gives consistent counter value */
  lval = RD_REG_32(component,CTM__CTCNTL);
  WR_REG_32(component,CTM__CTCNTL,lval);

  WR_REG_32(component,CTM__CTGNBL,counter_no);
}

void EVE_SCTM_MultipleCountersDisable( CRED_index_t component, UWORD32 counter_no)
{
  WR_REG_32(component,CTM__CTGNBL,counter_no);
}

void EVE_SCTM_IdleConfigSelect( CRED_index_t component, SCTM_Counter_type_t counter_no, SCTM_Idle_type_t en_dis_idle)
{
  UWORD32 lval;

  if(en_dis_idle == SCTM_EN_COUNTER) {
    lval = RD_REG_32(component,CTM__CTCNTL);
    WR_REG_32(component,CTM__CTCNTL,(lval | ((UWORD32)CTM__CTCNTL__IDLEMODE__NO_IDLE << CTM__CTCNTL__IDLEMODE__POS)));
  }

  if((counter_no == SCTM_Counter_0) || (counter_no == SCTM_Counter_1)) {
    lval = RD_REG_ARRAY_32(component,CTM__CTCR_WT,counter_no, CTM__CTCR_WT__ELSIZE);
    WR_REG_ARRAY_32(component,CTM__CTCR_WT,counter_no,(lval|((UWORD32)en_dis_idle << CTM__CTCR_WT__IDLE__POS)), CTM__CTCR_WT__ELSIZE);
  }
  else {
    lval = RD_REG_ARRAY_32(component,CTM__CTCR_WOT,(counter_no-2), CTM__CTCR_WOT__ELSIZE);
    WR_REG_ARRAY_32(component,CTM__CTCR_WOT,(counter_no-2),(lval|((UWORD32)en_dis_idle << CTM__CTCR_WOT__IDLE__POS)), CTM__CTCR_WOT__ELSIZE);
  }
}

void EVE_SCTM_HaltConfigSelect( CRED_index_t component, SCTM_Counter_type_t counter_no, SCTM_Idle_type_t en_dis_halt)
{
  UWORD32 lval;

  if((counter_no == SCTM_Counter_0) || (counter_no == SCTM_Counter_1)) {
    lval = RD_REG_ARRAY_32(component,CTM__CTCR_WT,counter_no, CTM__CTCR_WT__ELSIZE);
    WR_REG_ARRAY_32(component,CTM__CTCR_WT,counter_no,(lval|((UWORD32)en_dis_halt << CTM__CTCR_WT__FREE__POS)), CTM__CTCR_WT__ELSIZE);
  }
  else {
    lval = RD_REG_ARRAY_32(component,CTM__CTCR_WOT,(counter_no-2), CTM__CTCR_WOT__ELSIZE);
    WR_REG_ARRAY_32(component,CTM__CTCR_WOT,(counter_no-2),(lval|((UWORD32)en_dis_halt << CTM__CTCR_WOT__FREE__POS)), CTM__CTCR_WOT__ELSIZE);
  }
}

void EVE_SCTM_TimerModeSelect( CRED_index_t component, SCTM_Counter_type_t counter_no,SCTM_Timer_Mode_t timer_mode)
{
  UWORD32 lval;

  lval = RD_REG_ARRAY_32(component,CTM__CTCR_WT,counter_no, CTM__CTCR_WT__ELSIZE);
  WR_REG_ARRAY_32(component,CTM__CTCR_WT,counter_no,(lval|((UWORD32)timer_mode << CTM__CTCR_WT__RESTART__POS)), CTM__CTCR_WT__ELSIZE);
}

void EVE_SCTM_TimerInterruptEnable( CRED_index_t component, SCTM_Counter_type_t counter_no)
{
  UWORD32 lval;

  lval = RD_REG_ARRAY_32(component,CTM__CTCR_WT,counter_no, CTM__CTCR_WT__ELSIZE);
  WR_REG_ARRAY_32(component,CTM__CTCR_WT,counter_no,(lval|(CTM__CTCR_WT__INT)), CTM__CTCR_WT__ELSIZE);
}

void EVE_SCTM_IntervalMatchValueSet( CRED_index_t component, SCTM_Counter_type_t counter_no, UWORD32 interval_match)
{
  WR_REG_ARRAY_32(component,CTM__TINTVLR,counter_no,interval_match, CTM__TINTVLR__ELSIZE);
}


UWORD32 EVE_SCTM_CounterRead( CRED_index_t component, SCTM_Counter_type_t counter_no)
{
  UWORD32 lval;

  lval = RD_REG_ARRAY_32(component,CTM__CTCNTR,counter_no, CTM__CTCNTR__ELSIZE);

  return lval;
}

UWORD32 EVE_SCTM_OverflowCheck( CRED_index_t component, SCTM_Counter_type_t counter_no)
{
  UWORD32 lval;
  UWORD32 overflow;

  if((counter_no == SCTM_Counter_0) || (counter_no == SCTM_Counter_1)) {
    lval = RD_REG_ARRAY_32(component,CTM__CTCR_WT,counter_no, CTM__CTCR_WT__ELSIZE);
  }
  else {
    lval = RD_REG_ARRAY_32(component,CTM__CTCR_WOT,(counter_no-2), CTM__CTCR_WOT__ELSIZE);
  }

  overflow = (lval & (0x00000000U | (UWORD32)CTM__CTCR_WT__OVRFLW__POS)) >> CTM__CTCR_WT__OVRFLW__POS;
  return overflow;
}

ReturnCode_t EVE_SCTM_CounterConfig ( CRED_index_t component, SCTM_Counter_type_t counter_no, SCTM_Event_type_t inpsel, SCTM_Sampling_type_t samping_type)
{
  ReturnCode_t checkReturn = RET_OK;

  EVE_SCTM_CounterReset(component,counter_no);
  EVE_SCTM_InpEvtSelect(component,counter_no,inpsel);
  EVE_SCTM_SamplingSelect(component,counter_no,samping_type);

  return checkReturn;
}

ReturnCode_t EVE_SCTM_CounterConfig_Chain_mode ( CRED_index_t component, SCTM_Counter_type_t counter_no, SCTM_Event_type_t inpsel, SCTM_Sampling_type_t samping_type)
{
  ReturnCode_t checkReturn = RET_OK;
  EVE_SCTM_CounterReset(component,counter_no);
  EVE_SCTM_CounterReset(component,(SCTM_Counter_type_t)(counter_no+1));
  if(0 == (counter_no % 2)) {
    EVE_SCTM_ChainModeEnable(component,(SCTM_Counter_type_t)(counter_no+1));
    EVE_SCTM_ChainModeEnable(component,counter_no);
    EVE_SCTM_InpEvtSelect(component,counter_no,inpsel);
    EVE_SCTM_SamplingSelect(component,counter_no,samping_type);
  }
  else {
    checkReturn = RET_FAIL;
  }
  return checkReturn;
}

ReturnCode_t EVE_SCTM_CounterConfig_idle_mode ( CRED_index_t component, SCTM_Counter_type_t counter_no, SCTM_Event_type_t inpsel, SCTM_Sampling_type_t samping_type,SCTM_Idle_type_t en_dis_idle)
{
  ReturnCode_t checkReturn = RET_OK;
  EVE_SCTM_CounterReset(component,counter_no);
  EVE_SCTM_InpEvtSelect(component,counter_no,inpsel);
  EVE_SCTM_SamplingSelect(component,counter_no,samping_type);
  EVE_SCTM_IdleConfigSelect(component,counter_no,en_dis_idle);
  return checkReturn;
}

ReturnCode_t EVE_SCTM_CounterConfig_halt_mode ( CRED_index_t component, SCTM_Counter_type_t counter_no, SCTM_Event_type_t inpsel, SCTM_Sampling_type_t samping_type,SCTM_Idle_type_t en_dis_halt)
{
  ReturnCode_t checkReturn = RET_OK;
  EVE_SCTM_CounterReset(component,counter_no);
  EVE_SCTM_InpEvtSelect(component,counter_no,inpsel);
  EVE_SCTM_SamplingSelect(component,counter_no,samping_type);
  EVE_SCTM_HaltConfigSelect(component,counter_no,en_dis_halt);
  return checkReturn;
}

ReturnCode_t EVE_SCTM_TimerConfig ( CRED_index_t component, SCTM_Counter_type_t counter_no, SCTM_Event_type_t inpsel, SCTM_Sampling_type_t samping_type, SCTM_Timer_Mode_t timer_mode, UWORD32 interval_match)
{
  ReturnCode_t checkReturn = RET_OK;
  if(counter_no >= NO_OF_TIMERS) {
    checkReturn = RET_FAIL;
  }
  else {
    EVE_SCTM_CounterReset(component,counter_no);
    EVE_SCTM_InpEvtSelect(component,counter_no,inpsel);
    EVE_SCTM_SamplingSelect(component,counter_no,samping_type);
    EVE_SCTM_TimerModeSelect(component,counter_no,timer_mode);
    EVE_SCTM_TimerInterruptEnable(component,counter_no);
    EVE_SCTM_IntervalMatchValueSet(component,counter_no,interval_match);
  }
  return checkReturn;
}
