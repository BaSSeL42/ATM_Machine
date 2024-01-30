/*
 * HTimer.c
 *
 *  Created on: Apr 5, 2023
 *      Author: Bassel Yasser
 */
/*************************************************************************************************************
 * 								Includes
 ************************************************************************************************************/
//#include "../../Common/std_types.h"
#include "../../Common/Bit_Math.h"
#include "../../MCAL/Timer/TIMER_Interface.h"
#include "HTimer.h"


#ifndef NULL
#define NULL	(void*)0
#endif
/*************************************************************************************************************
 * 							Function Implementation
 ************************************************************************************************************/
enu_HTimerError_t HTimer_enInit(void)
{
	enu_HTimerError_t errorStatus = TIMER_OK;

	(void)enuTimer2_init (OVF_MODE);
	(void)u8Timer2_setPrescallar(TIMER_PRE_128);
	//(void)vidTimer2_OvfIrqEnable();
	(void)vidTimer2_OvfIrqDisable();

	return errorStatus;

}
/*************************************************************************************************************/
void HTimer_vidDelayMs( Uint32_t u32_delay )
{
	(void)u8Timer2_setTime_ms(u32_delay);
	(void)vidTimer2_start();
	MTIMER2_vidSynch();
}
/*************************************************************************************************************/

enu_HTimerError_t HTimer_enStop(void)
{
	enu_HTimerError_t errorStatus;

	errorStatus = vidTimer2_stop();

	return errorStatus;

}
/*************************************************************************************************************/
enu_HTimerError_t HTimer_enCBF(ptr_funcc pFunc)
{
	enu_HTimerError_t errorStatus = TIMER_OK;

	if(pFunc != NULL)
	{
		vidTimer2_setcbf_OVF(pFunc);

	}else{
		errorStatus = TIMER_NOK;
	}
	return errorStatus;
}


/*************************************************************************************************************
 * 							TIMER0
 ************************************************************************************************************/
/*************************************************************************************************************
 * 							Function Prototype
 ************************************************************************************************************/
enu_HTimerError_t HGPT0_enInit(void)
{
	enu_HTimerError_t enu_HTimerError = HTIMER_OK;
	GPT0_vidOvfInit ();
	enu_HTimerError &= GPT0_enuSetPrescallar(GPT0_PRE_64);
	GPT0_vidOvfIrqEnable();

	return enu_HTimerError;
}


void HGPT0_vidDelayMs( Uint32_t u32_delay )
{
	GPT0_enuSetTime_ms( u32_delay);
}


void HGPT0_vidStart(void)
{
	GPT0_vidStart();
}


void HGPT0_vidStop(void)
{
	GPT0_vidStop();
}


enu_HTimerError_t HGPT0_enCBF(ptr_funcc pFunc)
{
	enu_HTimerError_t errorStatus = TIMER_OK;

	if(pFunc != NULL)
	{
		GPT0_vidSetCbfOvf(pFunc);

	}else{
		errorStatus = TIMER_NOK;
	}
	return errorStatus;
}
/*************************************************************************************************************/
/*							End Of Implementation
*************************************************************************************************************/

