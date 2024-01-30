
/*
 * PWM_Source.c
 *
 *  Created on: Apr 10, 2023
 *      Author: Bassel Yasser
 */
/*************************************************************************************************************
 * 								Includes
 ************************************************************************************************************/
#include "../../Common/STD_Types.h"
#include "../../Common/Bit_Math.h"
#include "PWM_Private.h"
#include "PWM_Interface.h"
#include "PWM_Config.h"

/*************************************************************************************************************
 * 								Macros
 ************************************************************************************************************/
#define PRESCALLER_CLR_MSK				(0b11111000)
#define PWM_MODE_CLR_MSK				(0b11001111)
#define TIMER2_PRESCALLER_OFFSET		0
#define TIMER2_PWM_MODE_OFFSET			4

#define PWM_MODE_CLR_COM1B_MSK					(0b11001111)
#define PWM_MODE_CLR_COM1A_MSK					(0b00111111)
#define TIMER1_PRESCALLER_OFFSET				0
#define TIMER1_PWM_MODE_COM1A_OFFSET			6
#define TIMER1_PWM_MODE_COM1B_OFFSET			4

enu_timer1Mode_t gen_PwmMode;


/*************************************************************************************************************
 * 							Function Implementation
 ************************************************************************************************************/

/*
 * Author				: Bassel Yasser Mahmoud
 * Function Name		: Timer1_enuInit
 * Function Description : Initialize Timer1 to Fast PWM Mode
 * Arguments			: copy_enTmerMode  {TIMER1_OVF_MODE,TIMER1_FAST_PWM_MODE,..... }
 * Return 				: enu_timer1Status_t {TIMER1_OK or TIMER1_NOK}
 */
enu_timer1Status_t Timer1_enuInit (enu_timer1Mode_t copy_enTmerMode)
{
	enu_timer1Status_t errorStatus = TIMER1_OK;

	if(copy_enTmerMode < TIMER1_MODE_INVALID)
	{
		switch (copy_enTmerMode)
		{
			case TIMER1_NORMAL_0xFFFF				: ClrBit(TCCR1B_REG, WGM13); ClrBit(TCCR1B_REG, WGM12); ClrBit(TCCR1A_REG, WGM11); ClrBit(TCCR1A_REG, WGM10); break;
			case TIMER1_PWM_PHASE_CORRECT_8_0x00FF	: ClrBit(TCCR1B_REG, WGM13); ClrBit(TCCR1B_REG, WGM12); ClrBit(TCCR1A_REG, WGM11); SetBit(TCCR1A_REG, WGM10); break;
			case TIMER1_PWM_PHASE_CORRECT_9_0x01FF	: ClrBit(TCCR1B_REG, WGM13); ClrBit(TCCR1B_REG, WGM12); SetBit(TCCR1A_REG, WGM11); ClrBit(TCCR1A_REG, WGM10); break;
			case TIMER1_PWM_PHASE_CORRECT_10_0x03FF	: ClrBit(TCCR1B_REG, WGM13); ClrBit(TCCR1B_REG, WGM12); SetBit(TCCR1A_REG, WGM11); SetBit(TCCR1A_REG, WGM10); break;
			case TIMER1_CTC_OCR1A					: ClrBit(TCCR1B_REG, WGM13); SetBit(TCCR1B_REG, WGM12); ClrBit(TCCR1A_REG, WGM11); ClrBit(TCCR1A_REG, WGM10); break;
			case TIMER1_FAST_PWM_8_0x00FF			: ClrBit(TCCR1B_REG, WGM13); SetBit(TCCR1B_REG, WGM12); ClrBit(TCCR1A_REG, WGM11); SetBit(TCCR1A_REG, WGM10); gen_PwmMode =TIMER1_FAST_PWM_8_0x00FF;  break;
			case TIMER1_FAST_PWM_9_0x01FF			: ClrBit(TCCR1B_REG, WGM13); SetBit(TCCR1B_REG, WGM12); SetBit(TCCR1A_REG, WGM11); ClrBit(TCCR1A_REG, WGM10); gen_PwmMode =TIMER1_FAST_PWM_9_0x01FF;  break;
			case TIMER1_FAST_PWM_10_0x03FF			: ClrBit(TCCR1B_REG, WGM13); SetBit(TCCR1B_REG, WGM12); SetBit(TCCR1A_REG, WGM11); SetBit(TCCR1A_REG, WGM10); gen_PwmMode =TIMER1_FAST_PWM_10_0x03FF; break;
			case TIMER1_PWM_PHASE_FREQ_CORRECT_ICR1	: SetBit(TCCR1B_REG, WGM13); ClrBit(TCCR1B_REG, WGM12); ClrBit(TCCR1A_REG, WGM11); ClrBit(TCCR1A_REG, WGM10); break;
			case TIMER1_PWM_PHASE_FREQ_CORRECT_OCR1A: SetBit(TCCR1B_REG, WGM13); ClrBit(TCCR1B_REG, WGM12); ClrBit(TCCR1A_REG, WGM11); SetBit(TCCR1A_REG, WGM10); break;
			case TIMER1_PWM_PHASE_CORRECT_ICR1		: SetBit(TCCR1B_REG, WGM13); ClrBit(TCCR1B_REG, WGM12); SetBit(TCCR1A_REG, WGM11); ClrBit(TCCR1A_REG, WGM10); break;
			case TIMER1_PWM_PHASE_CORRECT_OCR1A		: SetBit(TCCR1B_REG, WGM13); ClrBit(TCCR1B_REG, WGM12); SetBit(TCCR1A_REG, WGM11); SetBit(TCCR1A_REG, WGM10); break;
			case TIMER1_CTC_ICR1					: SetBit(TCCR1B_REG, WGM13); SetBit(TCCR1B_REG, WGM12); ClrBit(TCCR1A_REG, WGM11); ClrBit(TCCR1A_REG, WGM10); break;
			case TIMER1_FAST_PWM_ICR1				: SetBit(TCCR1B_REG, WGM13); SetBit(TCCR1B_REG, WGM12); SetBit(TCCR1A_REG, WGM11); ClrBit(TCCR1A_REG, WGM10); gen_PwmMode =TIMER1_FAST_PWM_ICR1;  break;
			case TIMER1_FAST_PWM_OCR1A				: SetBit(TCCR1B_REG, WGM13); SetBit(TCCR1B_REG, WGM12); SetBit(TCCR1A_REG, WGM11); SetBit(TCCR1A_REG, WGM10); break;
			default: break;
		}

		TCNT1_REG = (Uint16_t)0;
	}else
	{
		errorStatus = TIMER1_NOK;
	}

	return errorStatus;
}
/*
 * Author				: Bassel Yasser Mahmoud
 * Function Name		: Timer1_enuSetPrescallar
 * Function Description : Set Prescaller
 * Arguments			: Timer1_enuSetPrescallar  {TIMER1_PRE_1,TIMER1_PRE_64,TIMER1_PRE_256,..... }
 * Return 				: enu_timer1Status_t {TIMER1_OK or TIMER1_NOK}
 */
enu_timer1Status_t Timer1_enuSetPrescallar(enu_timer1Prescalar_t copy_enTimerPrescaller)
{
	enu_timer1Status_t errorStatus = TIMER1_OK;
	Uint8_t temp_reg;
	if(copy_enTimerPrescaller < TIMER1_PRESCALR_INVALID)
	{
		temp_reg = TCCR1B_REG;
		temp_reg &= PRESCALLER_CLR_MSK;
		temp_reg |= copy_enTimerPrescaller << TIMER1_PRESCALLER_OFFSET;
		TCCR1B_REG = temp_reg;
	}
	else
	{
		errorStatus = TIMER1_NOK;
	}
	return errorStatus;
}
/*
 * Author				: Bassel Yasser Mahmoud
 * Function Name		: Timer1_enuFastPWM0Init
 * Function Description : Set PWM Mode
 * Arguments			: copy_enPWMMode  {TIMER1_PWM_NORMAL,TIMER1_PWM_CLR_ON_CMP,TIMER1_PWM_SET_ON_CMP,..... }
 * Return 				: enu_timer1Status_t {TIMER1_OK or TIMER1_NOK}
 */
enu_timer1Status_t Timer1_enuFastPWMInit(enu_pwm1Mode_t copy_enPWMMode)
{
	enu_timer1Status_t errorStatus = TIMER1_OK;
	Uint8_t local_u8Temp;

	if(copy_enPWMMode < TIMER1_PWM_INVALID)
	{
#if TIMER1_COM1_TYPE == TIMER1_COM1A

		local_u8Temp = TCCR1A_REG;
		local_u8Temp &= PWM_MODE_CLR_COM1A_MSK;
		local_u8Temp |= (copy_enPWMMode << TIMER1_PWM_MODE_COM1A_OFFSET);
		TCCR1A_REG = local_u8Temp;

#elif TIMER1_COM1_TYPE == TIMER1_COM1B

		local_u8Temp = TCCR1A_REG;
		local_u8Temp &= PWM_MODE_CLR_COM1B_MSK;
		local_u8Temp |= (copy_enPWMMode << TIMER1_PWM_MODE_COM1B_OFFSET);
		TCCR1A_REG = local_u8Temp;

#endif
	}else
	{
		errorStatus = TIMER1_NOK;
	}
	return errorStatus;

}
/*
 * Author				: Bassel Yasser Mahmoud
 * Function Name		: Timer1_enuPWM0Generate
 * Function Description : Generate PWM
 * Arguments			: copy_u8DutyCycle  {1 ~ 100}
 * Return 				: enu_timer1Status_t {TIMER1_OK or TIMER1_NOK}
 */
enu_timer1Status_t Timer1_enuPWMGenerate(Uint8_t copy_u8DutyCycle)
{
	enu_timer1Status_t errorStatus = TIMER1_OK;

	if( copy_u8DutyCycle > 0 && copy_u8DutyCycle <= 100)
	{
#if TIMER1_COM1_TYPE == TIMER1_COM1A

		if(gen_PwmMode == TIMER1_FAST_PWM_8_0x00FF)
		{
			OCR1A_REG = ((copy_u8DutyCycle * 256)/100)-1 ;
		}
		else if(gen_PwmMode == TIMER1_FAST_PWM_9_0x01FF)
		{
			OCR1A_REG = ((copy_u8DutyCycle * 512)/100)-1 ;
		}
		else if(gen_PwmMode == TIMER1_FAST_PWM_10_0x03FF)
		{
			OCR1A_REG = ((copy_u8DutyCycle * 1024)/100)-1 ;
		}
		else if (gen_PwmMode == TIMER1_FAST_PWM_ICR1)
		{
			OCR1A_REG = copy_u8DutyCycle;
		}
		else
		{
			/*
				 * do nothing
			 */
		}


#elif TIMER1_COM1_TYPE == TIMER1_COM1B

		if(gen_PwmMode == TIMER1_FAST_PWM_8_0x00FF)
		{
			OCR1B_REG = ((copy_u8DutyCycle * 256)/100)-1 ;
		}
		else if(gen_PwmMode == TIMER1_FAST_PWM_9_0x01FF)
		{
			OCR1B_REG = ((copy_u8DutyCycle * 512)/100)-1 ;
		}
		else if(gen_PwmMode == TIMER1_FAST_PWM_10_0x03FF)
		{
			OCR1B_REG = ((copy_u8DutyCycle * 1024)/100)-1 ;
		}
		else if (gen_PwmMode == TIMER1_FAST_PWM_ICR1)
		{
			OCR1B_REG = copy_u8DutyCycle;
		}
		else
		{
			/*
				 * do nothing
			 */
		}

#endif
	}else
	{
		errorStatus = TIMER1_NOK;
	}



	return errorStatus;
}















/********************************************************************************************************/


/*
 * Author				: Bassel Yasser Mahmoud
 * Function Name		: Timer2_enuInit
 * Function Description : Initialize Timer2 to Fast PWM Mode
 * Arguments			: copy_enTmerMode  {TIMER2_OVF_MODE,TIMER2_FAST_PWM_MODE,..... }
 * Return 				: enu_timer2Status_t {TIMER2_OK or TIMER2_NOK}
 */
enu_timer2Status_t Timer2_enuInit (enu_timer2Mode_t copy_enTmerMode)
{
	enu_timer2Status_t errorStatus = TIMER2_OK;

	if(copy_enTmerMode < TIMER2_TIMER_MODE_INVALID)
	{
		switch (copy_enTmerMode)
		{
		case TIMER2_OVF_MODE 				: ClrBit(TCCR2_REG, WGM21);ClrBit(TCCR2_REG, WGM20); break;
		case TIMER2_PHASE_CORRECT_PWM_MODE 	: ClrBit(TCCR2_REG, WGM21);SetBit(TCCR2_REG, WGM20); break;
		case TIMER2_CTC_MODE 				: SetBit(TCCR2_REG, WGM21);ClrBit(TCCR2_REG, WGM20); break;
		case TIMER2_FAST_PWM_MODE 			: SetBit(TCCR2_REG, WGM21);SetBit(TCCR2_REG, WGM20); break;
		default 					: errorStatus = TIMER2_NOK; break;
		}
		TCNT2_REG = (Uint8_t)0;
	}else
	{
		errorStatus = TIMER2_NOK;
	}


	return errorStatus;
}

/*
 * Author				: Bassel Yasser Mahmoud
 * Function Name		: Timer2_enuSetPrescallar
 * Function Description : Set Prescaller
 * Arguments			: Timer2_enuSetPrescallar  {TIMER2_PRE_1,TIMER2_PRE_256,TIMER2_PRE_256,..... }
 * Return 				: enu_timer2Status_t {TIMER2_OK or TIMER2_NOK}
 */
enu_timer2Status_t Timer2_enuSetPrescallar(enu_timerPrescalar_t copy_enTimerPrescaller)
{
	enu_timer2Status_t errorStatus = TIMER2_OK;
	Uint8_t temp_reg;
	if(copy_enTimerPrescaller < TIMER2_PRESCALR_INVALID)
	{
		temp_reg = TCCR2_REG;
		temp_reg &= PRESCALLER_CLR_MSK;
		temp_reg |= copy_enTimerPrescaller << TIMER2_PRESCALLER_OFFSET;
		TCCR2_REG = temp_reg;
	}
	else
	{
		errorStatus = TIMER2_NOK;
	}


	return errorStatus;
}


/*
 * Author				: Bassel Yasser Mahmoud
 * Function Name		: Timer2_enuFastPWM0Init
 * Function Description : Set PWM Mode
 * Arguments			: copy_enPWMMode  {TIMER2_PWM_NORMAL,TIMER2_PWM_CLR_ON_CMP,TIMER2_PWM_SET_ON_CMP,..... }
 * Return 				: enu_timer2Status_t {TIMER2_OK or TIMER2_NOK}
 */
enu_timer2Status_t Timer2_enuFastPWMInit(enu_pwmMode_t copy_enPWMMode)
{
	enu_timer2Status_t errorStatus = TIMER2_OK;
	Uint8_t local_u8Temp;

	if(copy_enPWMMode < TIMER2_PWM_INVALID)
	{
		local_u8Temp = TCCR2_REG;
		local_u8Temp &= PWM_MODE_CLR_MSK;
		local_u8Temp |= (copy_enPWMMode << TIMER2_PWM_MODE_OFFSET);
		TCCR2_REG = local_u8Temp;
	}else
	{
		errorStatus = TIMER2_NOK;
	}
	return errorStatus;
}

/*
 * Author				: Bassel Yasser Mahmoud
 * Function Name		: Timer2_enuPWM0Generate
 * Function Description : Generate PWM
 * Arguments			: copy_u8DutyCycle  {1 ~ 100}
 * Return 				: enu_timer2Status_t {TIMER2_OK or TIMER2_NOK}
 */
enu_timer2Status_t Timer2_enuPWMGenerate(Uint8_t copy_u8DutyCycle)
{
	enu_timer2Status_t errorStatus = TIMER2_OK;

	if( copy_u8DutyCycle > 0 && copy_u8DutyCycle <= 100)
	{
		OCR2_REG = ((copy_u8DutyCycle * 256)/100)-1 ;
	}else
	{
		errorStatus = TIMER2_NOK;
	}

	return errorStatus;
}

