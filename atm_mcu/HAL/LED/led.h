/*
 * led.h
 *
 *  Created on: Apr 4, 2023
 *      Author: hp
 */

#ifndef HAL_LED_LED_H_
#define HAL_LED_LED_H_


#include "../../MCAL/DIO/DIO_Interface.h"


typedef enum
{
	LED_NOK = 0,
	LED_OK

}enu_ledError_t;



enu_ledError_t HLed_Init(enu_pin en_pinNum);

enu_ledError_t HLed_on(enu_pin en_pinx);
enu_ledError_t HLed_off(enu_pin en_pinx);
enu_ledError_t HLed_toggle(enu_pin en_pinx);

#endif /* HAL_LED_LED_H_ */
