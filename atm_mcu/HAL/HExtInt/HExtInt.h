/*
 * HExtInt.h
 *
 *  Created on: Apr 5, 2023
 *      Author: hp
 */

#ifndef HAL_HEXTINT_HEXTINT_H_
#define HAL_HEXTINT_HEXTINT_H_


#include "../../MCAL/ExtInt/EXTINT_Interface.h"

typedef enum
{
	HEXTINT_NOK = 0,
	HEXTINT_OK

}enu_HExtIntError_t;



//typedef void(*ptr_func)(void);

/*
 * Author		: Bassel Yasser Mahmoud
 * function		: HExtInt_enInit
 * description 	: func to write integer number on lcd
 * in[1]	 	: enExtint : Interrupt type [INT0, INT1. INT2]
 * in[2]		: snsCtrl  : Sense Control {ANY_LOGICAL, FALL_EDGE, RISE_EDGE}
 * return		: void
 * */
enu_HExtIntError_t HExtInt_enInit(enu_int_type_t enExtint, enu_sns_ctrl_t snsCtrl);

/*
 * Author		: Bassel Yasser Mahmoud
 * function		: HExtInt_enCBF
 * description 	: Take pointer to function to be executed in ISR when it fires
 * input param 	: pointer to function
 * return		: void
 * */
enu_HExtIntError_t HExtInt_enCBF(ptr_func pFunc);

/*
 * Author		: Bassel Yasser Mahmoud
 * function		: HExtInt_enCBFInt1
 * description 	: Take pointer to function to be executed in ISR when it fires
 * input param 	: pointer to function
 * return		: void
 * */
enu_HExtIntError_t HExtInt_enCBFInt1(ptr_func pFunc);

/*
 * Author		: Bassel Yasser Mahmoud
 * function		: HExtInt_enCBFInt2
 * description 	: Take pointer to function to be executed in ISR when it fires
 * input param 	: pointer to function
 * return		: void
 * */
enu_HExtIntError_t HExtInt_enCBFInt2(ptr_func pFunc);


#endif /* HAL_HEXTINT_HEXTINT_H_ */
