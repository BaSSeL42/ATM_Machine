/*
 * HExtInt.c
 *
 *  Created on: Apr 5, 2023
 *      Author: hp
 */


#include "../../Common/std_types.h"
#include "../../Common/Bit_Math.h"
//#include "../../MCAL/ExtInt/EXTINT_Interface.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "HExtInt.h"


ptr_func cbf = NULL;

enu_HExtIntError_t HExtInt_enInit(enu_int_type_t enExtint, enu_sns_ctrl_t snsCtrl)
{
	enu_HExtIntError_t errorStatus = HEXTINT_OK;
	DIO_s8SETPinVal(DIO_PIND_2, HIGH);
	vidExtInt_init(enExtint , snsCtrl );

	return errorStatus;

}

enu_HExtIntError_t HExtInt_enCBF(ptr_func pFunc)
{
	enu_HExtIntError_t errorStatus = HEXTINT_OK;

	if (pFunc != NULL)
	{
		MEXTINT_vidCallBackFunc(pFunc);
	}
	else
	{
		errorStatus = HEXTINT_NOK;
	}


	return errorStatus;

}

enu_HExtIntError_t HExtInt_enCBFInt1(ptr_func pFunc)
{
	enu_HExtIntError_t errorStatus = HEXTINT_OK;

	if (pFunc != NULL)
	{
		MEXTINT_vidCallBackFuncInt1(pFunc);
	}
	else
	{
		errorStatus = HEXTINT_NOK;
	}


	return errorStatus;
}
