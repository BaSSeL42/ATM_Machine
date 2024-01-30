/*
 * MUART_Source.c
 *
 *  Created on: Apr 24, 2023
 *      Author: hp
 */
/********************************************************************************************************/
/*									Standard Types LIB													*/
/********************************************************************************************************/
//#include "../../Common/std_types.h"
#include "../../Common/Bit_Math.h"
#include <avr/interrupt.h>
/********************************************************************************************************/
/*									Peripheral Files 													*/
/********************************************************************************************************/
#include "MUART_Private.h"
#include "MUART_Interface.h"
#include "MUART_Config.h"
/********************************************************************************************************/
/*										Macros		     												*/
/********************************************************************************************************/
//#define F_CPU		8000000UL

#define CHAR_RECEIVE			0
#define STRING_RECEIVE			1


#define F_CPU 8000000UL  // Set your microcontroller clock frequency

#define BUFFER_SIZE 64


/********************************************************************************************************/
/*										Global Variables and extern		     							*/
/********************************************************************************************************/

extern st_muart_t uartInfo;

Uint8_t gl_u8_receive_mode = CHAR_RECEIVE;

volatile char receivedString[BUFFER_SIZE];
volatile uint8_t stringIndex = 0;
volatile uint8_t stringReceived = 0;




/********************************************************************************************************/
/*										ISR	     							*/
/********************************************************************************************************/
ISR(USART_RXC_vect) {
    char receivedChar = UDR;

    if (receivedChar == '\n' || receivedChar == '\r') {
        receivedString[stringIndex] = '\0'; // Null-terminate the string
        stringReceived = 1; // Set the flag indicating that a string is received
        stringIndex = 0; // Reset the index for the next string
    } else {
        receivedString[stringIndex] = receivedChar;
        stringIndex = (stringIndex + 1) % BUFFER_SIZE;
    }
}
/********************************************************************************************************/
/*									Function Implementation			     								*/
/********************************************************************************************************/
en_uartErrStat_t MUART_enInit(Uint32_t copy_u32BaudRate)
{
	Uint8_t local_u8BitMask;
	en_uartErrStat_t local_enErrorStatus = MUART_OK;
	Uint16_t local_u16UBRRReg ;

	if(copy_u32BaudRate >= 2400 && copy_u32BaudRate <= 250000)
	{

		/******************************** Set UART speed and setting Baudrate **************************/

#if MUART_SPEED_TYPE == MUART_SINGLE_SPEED

		ClrBit(UCSRA_REG, U2X);
		local_u16UBRRReg = ((F_CPU / (16*copy_u32BaudRate)) - 1);
		UBRRL_REG = (Uint8_t)local_u16UBRRReg;
		UBRRH_REG = (Uint8_t)((0 << URSEL) | (local_u16UBRRReg >> 8) );

#elif MUART_SPEED_TYPE == MUART_DOUBLE_SPEED

		SetBit(UCSRA_REG, U2X);
		local_u16UBRRReg = (F_CPU / (8*copy_u32BaudRate)) - 1;
		UBRRL_REG = (Uint8_t)local_u16UBRRReg;
		UBRRH_REG = (Uint8_t)((0 << URSEL) | (local_u16UBRRReg >> 8) );

#else

#error "Please put correct baudRate Speed"

#endif

		/******************************** Enabling TX and RX **************************/

#if MUART_TX_RX == MUART_TX_ENABLE

		SetBit(UCSRB_REG, TXEN);

#elif MUART_TX_RX == MUART_RX_ENABLE

		SetBit(UCSRB_REG, RXEN);

#elif MUART_TX_RX == MUART_TX_RX_ENABLE

		SetBit(UCSRB_REG, TXEN);
		SetBit(UCSRB_REG, RXEN);

		//SetBit(UCSRB_REG, RXCIE); // Enable RX Interrupt

#else
#error "MUART_TX_RX_INVALID"
#endif

		/******************************** Selecting Parity type **************************/
		UCSRC_REG &= 0b11001111;
		UCSRC_REG |= (1 << URSEL) | (uartInfo.enParityType << 4);


		/********************** Selecting Data Length ************************************/
		UCSRC_REG &= 0b11111001;
		local_u8BitMask = (0b00000011 | uartInfo.enDataLength);
		UCSRC_REG |= (1 << URSEL) | (1 << local_u8BitMask);
		local_u8BitMask = ( (0b00000100 | uartInfo.enDataLength) >> 2);
		UCSRB_REG &= 0b11111011;
		UCSRB_REG |= (local_u8BitMask << 2);

		/********************** Selecting Stop bit mode ************************************/
#if MUART_STOP_BIT == MUART_1_STOP_BIT

		ClrBit(UCSRC_REG, RUSBS);

#elif MUART_STOP_BIT == MUART_2_STOP_BIT

		SetBit(UCSRC_REG, RUSBS);
#endif

		/********************** Asynchronous mode  ************************************/
		ClrBit(UCSRC_REG, UMSEL);


	}else
	{
		local_enErrorStatus = MUART_NOK;
	}
	return local_enErrorStatus;
}



en_uartErrStat_t MUART_enSendData(Uint8_t Copy_u8Data)
{
	en_uartErrStat_t local_enErrorStatus = MUART_OK;

//	if (Copy_u8Data != 0)
//	{
		while( !(GetBit(UCSRA_REG, UDRE)) );
		UDR_REG = Copy_u8Data;
		while( !(GetBit(UCSRA_REG, TXC)) );

//	}else
//	{
//		local_enErrorStatus = MUART_NOK;
//	}
	return local_enErrorStatus;
}


en_uartErrStat_t MUART_enRecieveData(Uint8_t* Ref_u8Data)
{
	en_uartErrStat_t local_enErrorStatus = MUART_OK;

	if (Ref_u8Data != NULL)
	{
		while( !(GetBit(UCSRA_REG, RXC)) );
		*Ref_u8Data= UDR_REG;

		while( (UDR_REG != '\r') && (gl_u8_receive_mode == CHAR_RECEIVE) );

	}else
	{
		local_enErrorStatus = MUART_NOK;
	}
	return local_enErrorStatus;
}


void MUART_sendSTRING(const Uint8_t * str)
{
	//Uint8_t COUNTER = 0;
	while(*str != '\0')
	{
		(void)MUART_enSendData(*str);
		str++;
	}
}
void MUART_receiveSTRING(Uint8_t * str ,Uint8_t size )
{
	Uint8_t COUNTER = 0;
	Uint8_t Data;
	gl_u8_receive_mode = STRING_RECEIVE;
	while(COUNTER < size-1)
	{
		(void)MUART_enRecieveData(&Data);

		str[COUNTER]= Data;
		if(str[COUNTER] == ENTER_KEY)break;
//		(void)MUART_enSendData(str[COUNTER]);
		COUNTER++;
	}
	str[COUNTER] = '\0';
	gl_u8_receive_mode = CHAR_RECEIVE;
}

/********************************************************************************************************/
/*													END		     										*/
/********************************************************************************************************/
