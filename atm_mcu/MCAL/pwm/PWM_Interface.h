/*
 * PWM_Interface.h
 *
 *  Created on: Apr 10, 2023
 *      Author: hp
 */

#ifndef MCAL_PWM_PWM_INTERFACE_H_
#define MCAL_PWM_PWM_INTERFACE_H_

/************************************************************************************************/
/*									MACROS														*/
/************************************************************************************************/
/* TIMSK REG */
#define TOIE0		0
#define OCIE0		1
#define TOIE1		2
#define OCIE1A		3
#define OCIE1B		4
#define TICIE1		5
#define TOIE2		6
#define OCIE2		7

/* TIFR REG */
#define TOV0		0
#define OCF0		1
#define TOV1		2
#define OCF1A		3
#define OCF1B		4
#define ICF1		5
#define TOV2		6
#define OCF2		7


/* TCCR1A REG */
#define WGM10		0
#define WGM11		1
#define FOC1B		2
#define FOC1A		3
#define COM1B0		4
#define COM1B1		5
#define COM1A0		6
#define COM1A1		7

/* TCCR1B REG */
#define CS10		0
#define CS11		1
#define CS12		2
#define WGM12		3
#define WGM13		4
#define ICES1		6
#define ICNC1		7

/* TCCR2 REG */
#define CS20		0
#define CS21		1
#define CS22		2
#define WGM21		3
#define COM20		4
#define COM21		5
#define WGM20		6
#define FOC2		7



#define TIMER1_COM1A			0
#define TIMER1_COM1B			1


/************************************************************************************************/
/*									USER_DEFINED TYPES											*/
/************************************************************************************************/
typedef enum
{
	TIMER2_OK,
	TIMER2_NOK,

}enu_timer2Status_t;

typedef enum
{
	TIMER1_OK,
	TIMER1_NOK,

}enu_timer1Status_t;

typedef enum
{
	TIMER2_OVF_MODE,
	TIMER2_PHASE_CORRECT_PWM_MODE,
	TIMER2_CTC_MODE,
	TIMER2_FAST_PWM_MODE,

	TIMER2_TIMER_MODE_INVALID,

}enu_timer2Mode_t;


typedef enum
{
	TIMER1_NORMAL_0xFFFF,

	TIMER1_PWM_PHASE_CORRECT_8_0x00FF,
	TIMER1_PWM_PHASE_CORRECT_9_0x01FF,
	TIMER1_PWM_PHASE_CORRECT_10_0x03FF,

	TIMER1_CTC_OCR1A,

	TIMER1_FAST_PWM_8_0x00FF,
	TIMER1_FAST_PWM_9_0x01FF,
	TIMER1_FAST_PWM_10_0x03FF,

	TIMER1_PWM_PHASE_FREQ_CORRECT_ICR1,
	TIMER1_PWM_PHASE_FREQ_CORRECT_OCR1A,

	TIMER1_PWM_PHASE_CORRECT_ICR1,
	TIMER1_PWM_PHASE_CORRECT_OCR1A,

	TIMER1_CTC_ICR1,

	TIMER1_FAST_PWM_ICR1,
	TIMER1_FAST_PWM_OCR1A,

	TIMER1_MODE_INVALID,


}enu_timer1Mode_t;




typedef enum
{
	TIMER2_NO_CLK_SRC,
	TIMER2_PRE_1,
	TIMER2_PRE_8,
	TIMER2_PRE_64,
	TIMER2_PRE_256,
	TIMER2_PRE_1024,
	TIMER2_EXT_CLK_FALLING,
	TIMER2_EXT_CLK_RISING,

	TIMER2_PRESCALR_INVALID,


}enu_timerPrescalar_t;


typedef enum
{
	TIMER1_NO_CLK_SRC,
	TIMER1_PRE_1,
	TIMER1_PRE_8,
	TIMER1_PRE_64,
	TIMER1_PRE_256,
	TIMER1_PRE_1024,
	TIMER1_EXT_CLK_FALLING,
	TIMER1_EXT_CLK_RISING,

	TIMER1_PRESCALR_INVALID,


}enu_timer1Prescalar_t;



typedef enum
{
	TIMER1_PWM_NORMAL=0,
	TIMER1_PWM_TOGGLE_ON_CMP,
	TIMER1_PWM_CLR_ON_CMP,
	TIMER1_PWM_SET_ON_CMP,
	TIMER1_PWM_INVALID,

}enu_pwm1Mode_t;


typedef enum
{
	TIMER2_PWM_NORMAL=0,
	TIMER2_RESERVED,
	TIMER2_PWM_CLR_ON_CMP,
	TIMER2_PWM_SET_ON_CMP,
	TIMER2_PWM_INVALID,

}enu_pwmMode_t;




/*************************************************************************************************************
 * 							Function Prototype
 ************************************************************************************************************/
/*
 * Author				: Bassel Yasser Mahmoud
 * Function Name		: Timer1_enuInit
 * Function Description : Initialize Timer1 to Fast PWM Mode
 * Arguments			: copy_enTmerMode  {TIMER1_OVF_MODE,TIMER1_FAST_PWM_MODE,..... }
 * Return 				: enu_timer1Status_t {TIMER1_OK or TIMER1_NOK}
 */
enu_timer1Status_t Timer1_enuInit (enu_timer1Mode_t);
/*
 * Author				: Bassel Yasser Mahmoud
 * Function Name		: Timer1_enuSetPrescallar
 * Function Description : Set Prescaller
 * Arguments			: Timer1_enuSetPrescallar  {TIMER1_PRE_1,TIMER1_PRE_64,TIMER1_PRE_256,..... }
 * Return 				: enu_timer1Status_t {TIMER1_OK or TIMER1_NOK}
 */
enu_timer1Status_t Timer1_enuSetPrescallar(enu_timer1Prescalar_t);
/*
 * Author				: Bassel Yasser Mahmoud
 * Function Name		: Timer1_enuFastPWM0Init
 * Function Description : Set PWM Mode
 * Arguments			: copy_enPWMMode  {TIMER1_PWM_NORMAL,TIMER1_PWM_CLR_ON_CMP,TIMER1_PWM_SET_ON_CMP,..... }
 * Return 				: enu_timer1Status_t {TIMER1_OK or TIMER1_NOK}
 */
enu_timer1Status_t Timer1_enuFastPWMInit(enu_pwm1Mode_t );
/*
 * Author				: Bassel Yasser Mahmoud
 * Function Name		: Timer1_enuPWM0Generate
 * Function Description : Generate PWM
 * Arguments			: copy_u8DutyCycle  {1 ~ 100}
 * Return 				: enu_timer1Status_t {TIMER1_OK or TIMER1_NOK}
 */
enu_timer1Status_t Timer1_enuPWMGenerate(Uint8_t);






/*************************************************************************************************************/

/*
 * Author				: Bassel Yasser Mahmoud
 * Function Name		: Timer2_enuInit
 * Function Description : Initialize Timer2 to Fast PWM Mode
 * Arguments			: copy_enTmerMode  {TIMER2_OVF_MODE,TIMER2_FAST_PWM_MODE,..... }
 * Return 				: enu_timer2Status_t {TIMER2_OK or TIMER2_NOK}
 */
enu_timer2Status_t Timer2_enuInit (enu_timer2Mode_t);
/*
 * Author				: Bassel Yasser Mahmoud
 * Function Name		: Timer2_enuSetPrescallar
 * Function Description : Set Prescaller
 * Arguments			: Timer2_enuSetPrescallar  {TIMER2_PRE_1,TIMER2_PRE_256,TIMER2_PRE_256,..... }
 * Return 				: enu_timer2Status_t {TIMER2_OK or TIMER2_NOK}
 */
enu_timer2Status_t Timer2_enuSetPrescallar(enu_timerPrescalar_t);
/*
 * Author				: Bassel Yasser Mahmoud
 * Function Name		: Timer2_enuFastPWM0Init
 * Function Description : Set PWM Mode
 * Arguments			: copy_enPWMMode  {TIMER2_PWM_NORMAL,TIMER2_PWM_CLR_ON_CMP,TIMER2_PWM_SET_ON_CMP,..... }
 * Return 				: enu_timer2Status_t {TIMER2_OK or TIMER2_NOK}
 */
enu_timer2Status_t Timer2_enuFastPWMInit(enu_pwmMode_t );
/*
 * Author				: Bassel Yasser Mahmoud
 * Function Name		: Timer2_enuPWM0Generate
 * Function Description : Generate PWM
 * Arguments			: copy_u8DutyCycle  {1 ~ 100}
 * Return 				: enu_timer2Status_t {TIMER2_OK or TIMER2_NOK}
 */
enu_timer2Status_t Timer2_enuPWMGenerate(Uint8_t);

#endif /* MCAL_PWM_PWM_INTERFACE_H_ */
