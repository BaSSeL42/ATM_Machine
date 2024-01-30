/************************************************************************************************/
/*									INCLUDES													*/
/************************************************************************************************/
#include "avr/interrupt.h"
#include "../../Common/std_types.h"
#include "../../Common/Bit_Math.h"
#include "EXTINT_Private.h"
#include "EXTINT_Interface.h"


/************************************************************************************************/
/*									USER_DEFINED TYPES											*/
/************************************************************************************************/
ptr_func callBack = NULL;
ptr_func callBackFunc = NULL;

/************************************************************************************************/
/*									FUNCTION_IMPLEMENTATION										*/
/************************************************************************************************/
Uint8_t vidExtInt_init(enu_int_type_t enIntType, enu_sns_ctrl_t enSensControl)
{

	Uint8_t err_status = E_INT_OK;
	if(enIntType < INT_TYPE_INVALID && enSensControl < SENS_CONTROL_INVALID)
	{
		if (enIntType == INT_0)
		{
//			DIO_s8SETPinVal(DIO_PIND_2, HIGH);
			switch (enSensControl)
			{
				case LOW_LEVEL 	: ClrBit(MCUCR_REG, ISC00); ClrBit(MCUCR_REG, ISC01); break;
				case ANY_LOGICAL: SetBit(MCUCR_REG, ISC00); ClrBit(MCUCR_REG, ISC01); break;
				case FALL_EDGE 	: ClrBit(MCUCR_REG, ISC00); SetBit(MCUCR_REG, ISC01); break;
				case RISE_EDGE 	: SetBit(MCUCR_REG, ISC00); SetBit(MCUCR_REG, ISC01); break;
				default : err_status = E_INT_NOK; break;
			}

			SetBit(GICR_REG, INT0);
			SetBit(GIFR_REG, INTF0);	// to clear flag for Interrupt 0
		}
		else if (enIntType == INT_1)
		{
//			DIO_s8SETPinVal(EXT_INT1, HIGH);
			switch (enSensControl)
			{
				case LOW_LEVEL 	: ClrBit(MCUCR_REG, ISC10); ClrBit(MCUCR_REG, ISC11); break;
				case ANY_LOGICAL: SetBit(MCUCR_REG, ISC10); ClrBit(MCUCR_REG, ISC11); break;
				case FALL_EDGE 	: ClrBit(MCUCR_REG, ISC10); SetBit(MCUCR_REG, ISC11); break;
				case RISE_EDGE 	: SetBit(MCUCR_REG, ISC10); SetBit(MCUCR_REG, ISC11); break;
				default : err_status = E_INT_NOK; break;
			}
			SetBit(GICR_REG, INT1);
			SetBit(GIFR_REG, INTF1);	// to clear flag for Interrupt 1
		}
		else if (enIntType == INT_2)
		{
//			DIO_s8SETPinVal(EXT_INT2, HIGH);
			switch (enSensControl)
			{
				case FALL_EDGE 	: ClrBit(MCUCSR_REG, ISC2);  break;
				case RISE_EDGE 	: SetBit(MCUCSR_REG, ISC2);  break;
				default : err_status = E_INT_NOK; break;
			}
			SetBit(GICR_REG, INT2);
			SetBit(GIFR_REG, INTF2);  // to clear flag for Interrupt 2
		}
	}
	else
	{
		err_status = E_INT_NOK;
	}

	SetBit(SREG_REG, I); // enable global interrupt
//	ClrBit(SREG_REG, I);


	return err_status;
}



void MEXTINT_vidCallBackFunc(ptr_func funcCopy)
{
	callBack = funcCopy;

}


void MEXTINT_vidCallBackFuncInt1(ptr_func funcCopy)
{
	callBackFunc = funcCopy;

}


void MEXTINT_vidWaitFlag(void)
{
	while( !( GetBit(GIFR_REG, INTF0) ) );
}


void MEXTINT_vidDisableInterrupt(void)
{
	ClrBit(GICR_REG, INT0);
//	ClrBit(SREG_REG, I);
}

void MEXTINT_vidEnableInterrupt(void)
{
	SetBit(GIFR_REG, INTF1);
	SetBit(GICR_REG, INT0);
//	SetBit(SREG_REG, I);
}





ISR(INT0_vect)
{
	callBack();
}

ISR(INT1_vect)
{
	callBackFunc();
}
