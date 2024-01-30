/*
 * button.h
 *
 *  Created on: Apr 4, 2023
 *      Author: hp
 */
/*************************************************************************************************************
* 													FILE GUARD
************************************************************************************************************/
#ifndef HAL_BUTTON_BUTTON_H_
#define HAL_BUTTON_BUTTON_H_
/*************************************************************************************************************
* 													Includes
************************************************************************************************************/
#include "../../MCAL/DIO/DIO_Interface.h"
/*************************************************************************************************************
* 													User defined data type
************************************************************************************************************/
typedef enum
{
	BUTTON_NOK = 0,
	BUTTON_OK

}enu_buttonError_t;

/*************************************************************************************************************
* 													Function Prototype
************************************************************************************************************/
/*
* AUTHOR			: Bassel Yasser Mahmoud
* FUNCTION			: HButton_Init
* DESCRIPTION		: Initialize specified pin as input and pull up
* RETURN			: enu_buttonError_t {BUTTON_NOK, BUTTON_OK}
*/
enu_buttonError_t HButton_Init(enu_pin en_pinx);
/*
* AUTHOR			: Bassel Yasser Mahmoud
* FUNCTION			: HButton_ExtIntInit
* DESCRIPTION		: Initialize specified as pull up for external interrupt
* RETURN			: enu_buttonError_t {BUTTON_NOK, BUTTON_OK}
*/
enu_buttonError_t HButton_ExtIntInit(enu_pin en_pinx);
/*
* AUTHOR			: Bassel Yasser Mahmoud
* FUNCTION			: HButton_getPinVal
* DESCRIPTION		: Get pin status if it is high or low
* RETURN			: enu_buttonError_t {BUTTON_NOK, BUTTON_OK}
*/
enu_buttonError_t HButton_getPinVal(enu_pin en_pinx,  Uint8_t* pu8_refVal );


#endif /* HAL_BUTTON_BUTTON_H_ */
/*************************************************************************************************************
* 													END
************************************************************************************************************/
