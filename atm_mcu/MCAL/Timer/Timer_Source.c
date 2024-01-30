
/*************************************************************************************************************
 * 								Includes
 ************************************************************************************************************/
#include "avr/interrupt.h"
//#include "../../Common/std_types.h"
#include "../../Common/Bit_Math.h"
#include "TIMER_Private.h"
#include "TIMER_Interface.h"

/*************************************************************************************************************
 * 								Macros
 ************************************************************************************************************/
#define PRESCALLER_CLR_MSK		(0b11111000)
#define PRESCALLER_OFFSET		0
#define F_CPU			8000000UL

#define STOPPED			0
#define RUNNING			1

#define OVF_TICKS		256UL
#define MAX_TIM_MS		5000UL

#ifndef NULL
#define NULL	(void*)0
#endif
/*************************************************************************************************************
 * 								Global/Static Variables
 ************************************************************************************************************/
static enu_timerPrescalar_t global_prescaller;
static Uint8_t global_timerStatus;
static Uint8_t global_ovf = 1;
static Uint16_t preload = 0;
static Uint16_t gs_u16_preload_gpt0 = 0;
static cbf_t  globalCallFunc = NULL;


static Uint16_t prescaller_map[8] = {
		0,
		1,
		8,
		32,
		64,
		128,
		256,
		1024
};

/*************************************************************************************************************
 * 							Function Implementation
 ************************************************************************************************************/
enu_timerStatus_t enuTimer2_init (enu_timerMode_t enTimerMode)
{
	enu_timerStatus_t errorStatus = TIMER_OK;

	if(enTimerMode < TIMER_MODE_INVALID)
	{
		TCNT2_REG = 0;
		switch (enTimerMode)
		{
		case OVF_MODE 				: ClrBit(TCCR2_REG, WGM01);ClrBit(TCCR2_REG, WGM00); break;
		case PHASE_CORRECT_PWM_MODE : ClrBit(TCCR2_REG, WGM01);SetBit(TCCR2_REG, WGM00); break;
		case CTC_MODE 				: SetBit(TCCR2_REG, WGM01);ClrBit(TCCR2_REG, WGM00); break;
		case FAST_PWM_MODE 			: SetBit(TCCR2_REG, WGM01);SetBit(TCCR2_REG, WGM00); break;
		default 					: errorStatus = TIMER_NOK; break;
		}
	}
	else
	{
		errorStatus = TIMER_NOK;
	}
	return errorStatus;
}


/*************************************************************************************************************/
enu_timerStatus_t u8Timer2_setPrescallar(enu_timerPrescalar_t Copy_enPrescal)
{
	enu_timerStatus_t errorStatus = TIMER_OK;
	Uint8_t temp_reg;
	if(Copy_enPrescal < TIMER_PRESCALR_INVALID)
	{
		global_prescaller = Copy_enPrescal;
		if (global_timerStatus == RUNNING)
		{
			temp_reg = TCCR2_REG;		 // read
			temp_reg &= PRESCALLER_CLR_MSK;  // mod
			temp_reg |=  global_prescaller << PRESCALLER_OFFSET; // mod
			TCCR2_REG |= temp_reg;		// write
		}
		else
		{
			/* do nothing */
		}
	}
	else
	{
		errorStatus = TIMER_NOK;
	}
	return errorStatus;
}

/*************************************************************************************************************/
enu_timerStatus_t vidTimer2_OvfIrqEnable(void)
{
	enu_timerStatus_t errorStatus = TIMER_OK;

	SetBit(TIFR_REG, 6);
	SetBit(TIMSK_REG, TOIE2);
//	SetBit(SREG_REG, 7);

	return errorStatus;
}

/*************************************************************************************************************/
enu_timerStatus_t vidTimer2_OvfIrqDisable(void)
{
	enu_timerStatus_t errorStatus = TIMER_OK;

	ClrBit(TIMSK_REG, TOIE2);

	return errorStatus;
}

/*************************************************************************************************************/

//enu_timerStatus_t enu_synchTimer(void)
//{
//	enu_timerStatus_t timerState = TIMER_OK;
//
//	SetBit(TIFR_REG, TOV2);
//	if(global_timerStatus == RUNNING)
//	{
//		while(! GetBit(TIFR_REG, TOV2) );
//	}
//
//
//	return timerState;
//}


/*************************************************************************************************************/
enu_timerStatus_t vidTimer2_start(void)
{
	enu_timerStatus_t errorStatus = TIMER_OK;

	TCCR2_REG |=  global_prescaller << PRESCALLER_OFFSET;
	global_timerStatus  = RUNNING;

	return errorStatus;
}

/*************************************************************************************************************/
enu_timerStatus_t vidTimer2_stop(void)
{
	enu_timerStatus_t errorStatus = TIMER_OK;

	TCCR2_REG &=  PRESCALLER_CLR_MSK;
	global_timerStatus = STOPPED;

	return errorStatus;
}
/*************************************************************************************************************/
enu_timerStatus_t u8Timer2_setTime_ms(Uint32_t u32_time_ms)
{
	enu_timerStatus_t errorStatus = TIMER_OK;
	Uint32_t desired_ticks;
	Float32_t tick_time_ms;
	if( u32_time_ms < MAX_TIM_MS )
	{
		tick_time_ms = (Float32_t)prescaller_map[global_prescaller] / ((Uint32_t)F_CPU / 1000U)  ;
		desired_ticks = u32_time_ms / tick_time_ms;

		/* Compare ticks with OVF_ticks */
		if(desired_ticks == OVF_TICKS)
		{
			global_ovf = 1;
		}
		else if(desired_ticks < OVF_TICKS)
		{
			preload = OVF_TICKS - desired_ticks;
			TCNT2_REG = preload;
			global_ovf = 1;
		}
		else if(desired_ticks > OVF_TICKS)
		{
			global_ovf = (Uint8_t)(desired_ticks / OVF_TICKS);
			preload = (uint16_t)(OVF_TICKS - (desired_ticks % OVF_TICKS ));
			TCNT2_REG = preload;
			if (preload > 0U)
			{
				global_ovf++;
			}
		}
	}
		else
		{
			errorStatus = TIMER_NOK;
		}


		return errorStatus;
	}

/*************************************************************************************************************/

void MTIMER2_vidSynch(void)
{
	Uint8_t counter = 0;
	while(counter != global_ovf)
	{
		while(! GetBit(TIFR_REG, TOV2) );
		SetBit(TIFR_REG, TOV2);
		counter++;
	}
}


/*************************************************************************************************************/
void vidTimer2_setcbf_OVF(cbf_t cbf)
{
	if (cbf != NULL)
	{
		globalCallFunc = cbf;
	}
	return;
}



void MTIMER_vidResetTCNT(void)
{
	TCNT2_REG = 0;
}
Uint8_t MTIMER_u8GetTCNT(void)
{
	return TCNT2_REG;
}






/************************************************************************************************/
/*											TIMER 0										*/
/************************************************************************************************/
/************************************************************************************************/
/*									FUNCTIONS IMPLEMENTATION										*/
/************************************************************************************************/

static 	Uint8_t 				gs_u8_gpt0_status = STOPPED;
static 	enu_timerPrescalar_t 	gs_enu_gpt0_prescaller;
static 	Uint8_t 				gs_u8_global_ovf = 0;
static 	cbf_t  					gs_pfun_cbf = NULL;
volatile Uint32_t				g_u32_ovf_count = 0;



static Uint16_t gs_gpt0_prescaller_map[6] = {
		0,
		1,
		8,
		64,
		256,
		1024
};


void GPT0_vidOvfInit (void)
{
	TCNT0_REG = 0;
	ClrBit(TCCR0_REG, WGM01);
	ClrBit(TCCR0_REG, WGM00);
}


enu_timerStatus_t GPT0_enuSetPrescallar(enu_gpt0Prescalar_t Copy_enPrescal)
{
	enu_timerStatus_t errorStatus = TIMER_OK;
	Uint8_t temp_reg;
	if(Copy_enPrescal < GPT0_PRESCALR_INVALID)
	{
		gs_enu_gpt0_prescaller = Copy_enPrescal;
		if (gs_u8_gpt0_status == RUNNING)
		{
			temp_reg = TCCR0_REG;		 // read
			temp_reg &= PRESCALLER_CLR_MSK;  // mod
			temp_reg |=  gs_enu_gpt0_prescaller << PRESCALLER_OFFSET; // mod
			TCCR0_REG |= temp_reg;		// write
		}
		else
		{
			/* do nothing */
		}
	}
	else
	{
		errorStatus = TIMER_NOK;
	}
	return errorStatus;
}


void GPT0_vidOvfIrqEnable(void)
{
	SetBit(TIFR_REG, TOV0);
	SetBit(TIMSK_REG, TOIE0);
}


void GPT0_vidStart(void)
{
	TCCR0_REG |=  gs_enu_gpt0_prescaller << PRESCALLER_OFFSET;
	gs_u8_gpt0_status  = RUNNING;
}


void GPT0_vidStop(void)
{
	TCCR0_REG &=  PRESCALLER_CLR_MSK;
	TCNT0_REG = gs_u16_preload_gpt0;
	gs_u8_gpt0_status = STOPPED;
}


enu_timerStatus_t GPT0_enuSetTime_ms(Uint32_t u32_time_ms)
{
	enu_timerStatus_t errorStatus = TIMER_OK;
	Uint32_t desired_ticks;
	Float32_t tick_time_ms;
	if( u32_time_ms < MAX_TIM_MS )
	{
		tick_time_ms = (Float32_t)gs_gpt0_prescaller_map[gs_enu_gpt0_prescaller] / ((Uint32_t)F_CPU / 1000U)  ;
		desired_ticks = u32_time_ms / tick_time_ms;

		/* Compare ticks with OVF_ticks */
		if(desired_ticks == OVF_TICKS)
		{
			gs_u8_global_ovf = 1;
		}
		else if(desired_ticks < OVF_TICKS)
		{
			gs_u16_preload_gpt0 = OVF_TICKS - desired_ticks;
			TCNT0_REG = gs_u16_preload_gpt0;
			gs_u8_global_ovf = 1;
		}
		else if(desired_ticks > OVF_TICKS)
		{
			gs_u8_global_ovf = (Uint8_t)(desired_ticks / OVF_TICKS);
			gs_u16_preload_gpt0 = (uint16_t)(OVF_TICKS - (desired_ticks % OVF_TICKS ));
			TCNT0_REG = gs_u16_preload_gpt0;
			if (gs_u16_preload_gpt0 > 0U)
			{
				gs_u8_global_ovf++;
			}
		}
	}
		else
		{
			errorStatus = TIMER_NOK;
		}


		return errorStatus;
}


void GPT0_vidSetCbfOvf(cbf_t cbf)
{
	if (cbf != NULL)
	{
		gs_pfun_cbf = cbf;
	}
	return;
}


/*************************************************************************************************************
 * 							ISR Interrupt Handling
 ************************************************************************************************************/
ISR(TIMER2_OVF_vect)
{
	static Uint8_t counter = 0;
	counter++;
	if(counter == global_ovf)
	{
		if (globalCallFunc != NULL)
		{
			counter = 0;

			globalCallFunc();
//			TCNT2_REG = preload;
//			global_ovf = 0;
//			vidTimer1_stop();
		}
	}
}


ISR(TIMER0_OVF_vect)
{
	static Uint8_t counter = 0;
	counter++;
	if(counter == gs_u8_global_ovf)
	{
//		if (gs_pfun_cbf != NULL)
//		{
			counter = 0;
			g_u32_ovf_count++;
//		}
	}
}
