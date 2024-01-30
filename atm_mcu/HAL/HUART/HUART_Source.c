/*
 * HUART_Source.c
 *
 *  Created on: Apr 25, 2023
 *      Author: hp
 */


//#include "../../Common/Bit_Math.h"
#include "../../MCAL/UART/MUART_Interface.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "HUART_Interface.h"

en_huartErrStat_t HUART_enInit(Uint32_t copy_u32BaudRateH)
{

	en_huartErrStat_t local_enErrorStatus = HUART_OK;

	local_enErrorStatus = MUART_enInit(copy_u32BaudRateH);

	return local_enErrorStatus;
}



en_huartErrStat_t HUART_enSendData(Uint8_t Copy_u8DataH)
{
	en_huartErrStat_t local_enErrorStatus = HUART_OK;

	local_enErrorStatus = MUART_enSendData(Copy_u8DataH);

	return local_enErrorStatus;
}



en_huartErrStat_t HUART_enRecieveData(Uint8_t* Ref_u8DataH)
{
	en_huartErrStat_t local_enErrorStatus = HUART_OK;

	local_enErrorStatus = MUART_enRecieveData(Ref_u8DataH);

	return local_enErrorStatus;
}





void HUART_sendSTRING(Uint8_t * Hstr)
{
	MUART_sendSTRING(Hstr);
}


void HUART_ClearScreen() {
    // ANSI escape sequence for clearing the screen
	MUART_sendSTRING( (const Uint8_t*) "\033[2J\033[H");  // ESC[2J
}


void HUART_receiveSTRING(Uint8_t * Hstr ,Uint8_t Hsize )
{
	MUART_receiveSTRING(Hstr ,Hsize );
}
