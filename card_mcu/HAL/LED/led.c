/*
 * led.c
 *
 *  Created on: Apr 4, 2023
 *      Author: hp
 */


#include "../../Common/std_types.h"
#include "../../Common/Bit_Math.h"
//#include "../../MCAL/DIO/DIO_Interface.h"
#include "led.h"


enu_ledError_t HLed_Init(enu_pin en_pinNum)
{
	enu_ledError_t errorStatus = LED_OK;

	if ( en_pinNum < PIN_INVALID )
	{
		DIO_s8SETPinDir(en_pinNum, OUTPUT);
	}
	else
	{
		errorStatus = LED_NOK;
	}



	return errorStatus;

}

enu_ledError_t HLed_on(enu_pin en_pinx)
{
	enu_ledError_t errorStatus = LED_OK;

	if ( en_pinx < PIN_INVALID )
	{
		DIO_s8SETPinVal(en_pinx, HIGH);
	}
	else
	{
		errorStatus = LED_NOK;
	}



	return errorStatus;

}



enu_ledError_t HLed_off(enu_pin en_pinx)
{
	enu_ledError_t errorStatus = LED_OK;

	if ( en_pinx < PIN_INVALID )
	{
		DIO_s8SETPinVal(en_pinx, LOW);
	}
	else
	{
		errorStatus = LED_NOK;
	}



	return errorStatus;

}


enu_ledError_t HLed_toggle(enu_pin en_pinx)
{
	enu_ledError_t errorStatus = LED_OK;

	if ( en_pinx < PIN_INVALID )
	{
		DIO_s8TOGPinVal(en_pinx);

	}
	else
	{
		errorStatus = LED_NOK;
	}

	return errorStatus;

}
