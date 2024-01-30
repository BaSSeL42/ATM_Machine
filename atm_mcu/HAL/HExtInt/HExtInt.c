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

#ifndef NULL
#define NULL (void*)0
#endif

ptr_func cbf = NULL;

enu_HExtIntError_t HExtInt_enInit(enu_int_type_t enExtint, enu_sns_ctrl_t snsCtrl)
{
	enu_HExtIntError_t errorStatus = HEXTINT_OK;

	if (enExtint == INT_0)
	{
		DIO_s8SETPinVal(DIO_PIND_2, HIGH);
	}
	else if (enExtint == INT_1)
	{
		DIO_s8SETPinVal(DIO_PIND_3, HIGH);
	}
	else if (enExtint == INT_2)
	{
//		DIO_s8SETPinVal(DIO_PINB_2, LOW);
	}
	else
	{
		// do nothing
	}

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


enu_HExtIntError_t HExtInt_enCBFInt2(ptr_func pFunc)
{
	enu_HExtIntError_t errorStatus = HEXTINT_OK;

	if (pFunc != NULL)
	{
		MEXTINT_vidCallBackFuncInt2(pFunc);
	}
	else
	{
		errorStatus = HEXTINT_NOK;
	}
	return errorStatus;
}

