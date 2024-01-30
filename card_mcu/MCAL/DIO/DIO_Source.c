//#include "../../Common/std_types.h"
#include "../../Common/Bit_Math.h"
#include "DIO_Private.h"
#include "DIO_Interface.h"




volatile Uint8_t* portReg[4] = { PORTA_REG, PORTB_REG, PORTC_REG, PORTD_REG };
volatile Uint8_t* ddrReg[4] = { DDRA_REG, DDRB_REG, DDRC_REG, DDRD_REG };
volatile Uint8_t* pinReg[4] = { PINA_REG, PINB_REG, PINC_REG, PIND_REG };


Sint8_t DIO_s8SETPortDir(enu_port enPortCopy,  enu_dir enPortDir)
{
	Sint8_t errStatus = E_OK;

	if (enPortCopy < PORT_INVALID && enPortDir < DIR_INVALID)
	{
		if (enPortDir == INPUT)
		{
			*ddrReg[enPortCopy] = 0x00;
		}
		else if(enPortDir == OUTPUT)
		{
			*ddrReg[enPortCopy] = 0xff;
		}
		else
		{
			/* do nothing */
		}
	}
	else
	{
		errStatus = E_NOK;
	}
	return errStatus;
}


Sint8_t DIO_s8SETPortVal(enu_port enPortCopy,  Uint8_t u8PortVal)
{
	Sint8_t errStatus = E_OK;
	if (enPortCopy < PORT_INVALID)
	{
		*portReg[enPortCopy] = u8PortVal;
	}
	else
	{
		errStatus = E_NOK;
	}


	return errStatus;
}



Sint8_t DIO_s8GETPortVal(enu_port enPortCopy,  Uint8_t* pu8Val)
{
	Sint8_t errStatus = E_OK;
	if (enPortCopy < PORT_INVALID )
	{
		*pu8Val = *pinReg[enPortCopy];
	}
	else
	{
		errStatus = E_NOK;
	}
	return errStatus;
}


/*
 * AUTHOR		: Bassel Yasser
 * Function		: DIO_s8SETPinDir
 * Description	: Set Pin Direction
 * Arguments	:
 * 					- enPinCopy {DIO_PINA_0...., DIO_PIND_7}
 * 					- enPortDir {INPUT , OUTPUT}
 * Return		:   Sint8_t
 */

Sint8_t DIO_s8SETPinDir (enu_pin enPinCopy, enu_dir enPortDir)
{
	Sint8_t errStatus = E_OK;
	Uint8_t portID;
	Uint8_t pinID;

	if (enPinCopy < PIN_INVALID && enPortDir< DIR_INVALID)
	{
		portID = enPinCopy/8;
		pinID  = enPinCopy%8;

		if (enPortDir == INPUT)
		{
			ClrBit(*ddrReg[portID],pinID);
		}
		else if(enPortDir == OUTPUT)
		{
			SetBit(*ddrReg[portID],pinID);
		}
		else
		{
			/* do nothing */
		}
	}
	else
	{
		errStatus = E_NOK;
	}
	return errStatus;
}

/*
 * AUTHOR		: Bassel Yasser
 * Function		: DIO_s8SETPinVal
 * Description	: Set Pin Value
 * Arguments	:
 * 					- enPinCopy {DIO_PINA_0...., DIO_PIND_7}
 * 					- enPortDir {HIGH , LOW}
 * Return		:   Sint8_t
 */
Sint8_t DIO_s8SETPinVal (enu_pin enPinCopy, enu_val enPortVal)
{
	Sint8_t errStatus = E_OK;
	Uint8_t portID;
	Uint8_t pinID;

	if (enPinCopy < PIN_INVALID && enPortVal< VAL_INVALID)
	{
		portID = enPinCopy/8;
		pinID  = enPinCopy%8;

		if (enPortVal == LOW)
		{
			ClrBit(*portReg[portID],pinID);
		}
		else if(enPortVal == HIGH)
		{
			SetBit(*portReg[portID],pinID);
		}
		else
		{
			/* do nothing */
		}
	}
	else
	{
		errStatus = E_NOK;
	}
	return errStatus;
}


Sint8_t DIO_s8TOGPinVal (enu_pin enPinCopy)
{
	Sint8_t errStatus = E_OK;
	Uint8_t portID;
	Uint8_t pinID;

	if (enPinCopy < PIN_INVALID)
	{
		portID = enPinCopy/8;
		pinID  = enPinCopy%8;

		TogBit(*portReg[portID],pinID);
	}
	else
	{
		errStatus = E_NOK;
	}
	return errStatus;

}



/*
 * AUTHOR		: Bassel Yasser
 * Function		: DIO_s8GETPinVal
 * Description	: Set Pin Value
 * Arguments	:
 * 					- enPinCopy {DIO_PINA_0...., DIO_PIND_7}
 * 					- pu8Val address of variable that u want to save value on it
 * Return		:   Sint8_t
 */
Sint8_t DIO_s8GETPinVal (enu_pin enPinCopy, Uint8_t* pu8Val)
{
	Sint8_t errStatus = E_OK;
	Uint8_t portID;
	Uint8_t pinID;
	if (enPinCopy < PIN_INVALID)
	{
		portID = enPinCopy/8;
		pinID  = enPinCopy%8;

		*pu8Val = GetBit(*pinReg[portID], pinID);

	}
	else
	{
		errStatus = E_NOK;
	}
	return errStatus;
}
