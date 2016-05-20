/*==========================================================================*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#include "GlobalTypes.h"
#include "baseaddress.h"
#include "sctm.h"



void EVE_SCTM_Enable( CRED_index_t component)
{
	return;
}

void EVE_SCTM_CounterReset( CRED_index_t component, SCTM_Counter_type_t counter_no)
{
	return;
}

void EVE_SCTM_ChainModeEnable( CRED_index_t component, SCTM_Counter_type_t counter_no)
{
	return;
}

void EVE_SCTM_InpEvtSelect( CRED_index_t component, SCTM_Counter_type_t counter_no, SCTM_Event_type_t inpsel)
{
  	return;
}

void EVE_SCTM_SamplingSelect( CRED_index_t component, SCTM_Counter_type_t counter_no, SCTM_Sampling_type_t samping_type)
{
	return;
}

void EVE_SCTM_CounterTimerEnable( CRED_index_t component, SCTM_Counter_type_t counter_no)
{
	return;
}

void EVE_SCTM_CounterTimerDisable( CRED_index_t component, SCTM_Counter_type_t counter_no)
{
  	return;
}

void EVE_SCTM_MultipleCountersEnable( CRED_index_t component, UWORD32 counter_no)
{
  	return;
}

void EVE_SCTM_MultipleCountersDisable( CRED_index_t component, UWORD32 counter_no)
{
	return;
}

void EVE_SCTM_IdleConfigSelect( CRED_index_t component, SCTM_Counter_type_t counter_no, SCTM_Idle_type_t en_dis_idle)
{
  	return;
}

void EVE_SCTM_HaltConfigSelect( CRED_index_t component, SCTM_Counter_type_t counter_no, SCTM_Idle_type_t en_dis_halt)
{
  	return;
}

void EVE_SCTM_TimerModeSelect( CRED_index_t component, SCTM_Counter_type_t counter_no,SCTM_Timer_Mode_t timer_mode)
{
  	return;
}

void EVE_SCTM_TimerInterruptEnable( CRED_index_t component, SCTM_Counter_type_t counter_no)
{
  	return;
}

void EVE_SCTM_IntervalMatchValueSet( CRED_index_t component, SCTM_Counter_type_t counter_no, UWORD32 interval_match)
{
  	return;
}


UWORD32 EVE_SCTM_CounterRead( CRED_index_t component, SCTM_Counter_type_t counter_no)
{
  UWORD32 lval=0;

  return lval;
}

UWORD32 EVE_SCTM_OverflowCheck( CRED_index_t component, SCTM_Counter_type_t counter_no)
{
  UWORD32 overflow=0;

  return overflow;
}

ReturnCode_t EVE_SCTM_CounterConfig ( CRED_index_t component, SCTM_Counter_type_t counter_no, SCTM_Event_type_t inpsel, SCTM_Sampling_type_t samping_type)
{
  ReturnCode_t checkReturn = RET_OK;
  return checkReturn;
}

ReturnCode_t EVE_SCTM_CounterConfig_Chain_mode ( CRED_index_t component, SCTM_Counter_type_t counter_no, SCTM_Event_type_t inpsel, SCTM_Sampling_type_t samping_type)
{
  ReturnCode_t checkReturn = RET_OK;
  
  return checkReturn;
}

ReturnCode_t EVE_SCTM_CounterConfig_idle_mode ( CRED_index_t component, SCTM_Counter_type_t counter_no, SCTM_Event_type_t inpsel, SCTM_Sampling_type_t samping_type,SCTM_Idle_type_t en_dis_idle)
{
  ReturnCode_t checkReturn = RET_OK;
  return checkReturn;
}

ReturnCode_t EVE_SCTM_CounterConfig_halt_mode ( CRED_index_t component, SCTM_Counter_type_t counter_no, SCTM_Event_type_t inpsel, SCTM_Sampling_type_t samping_type,SCTM_Idle_type_t en_dis_halt)
{
  ReturnCode_t checkReturn = RET_OK;
  return checkReturn;
}

ReturnCode_t EVE_SCTM_TimerConfig ( CRED_index_t component, SCTM_Counter_type_t counter_no, SCTM_Event_type_t inpsel, SCTM_Sampling_type_t samping_type, SCTM_Timer_Mode_t timer_mode, UWORD32 interval_match)
{
  ReturnCode_t checkReturn = RET_OK;
  return checkReturn;
}
