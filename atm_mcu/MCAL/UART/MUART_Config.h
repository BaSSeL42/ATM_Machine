/*
 * MUART_Config.h
 *
 *  Created on: Apr 24, 2023
 *      Author: hp
 */

#ifndef MCAL_UART_MUART_CONFIG_H_
#define MCAL_UART_MUART_CONFIG_H_

/********************************************************************************************************/
/*											Macros												*/
/********************************************************************************************************/
/*   MUART SPEED
 *	MUART_SINGLE_SPEED
 *	MUART_DOUBLE_SPEED
 *
 **/
#define MUART_SPEED_TYPE		MUART_SINGLE_SPEED


/*   MUART Transmitter Reciever Enable
 *
 *	MUART_TX_ENABLE
 *	MUART_RX_ENABLE
 *	MUART_TX_RX_ENABLE
 **/
#define MUART_TX_RX				MUART_TX_RX_ENABLE


/*
 * MUART Stop bit
 *
 * MUART_1_STOP_BIT
 * MUART_2_STOP_BIT
 */
#define MUART_STOP_BIT			MUART_1_STOP_BIT



/********************************************************************************************************/
/*											User defined data type										*/
/********************************************************************************************************/

typedef enum
{
	MUART_NO_PARITY = 0,
	MUART_PR_RESERVED,
	MUART_EVEN_PARITY,
	MUART_ODD_PARITY

}en_muartParity_t;

typedef enum
{
	MUART_FIVE_BIT_DATA = 0,
	MUART_SIX_BIT_DATA,
	MUART_SEVEN_BIT_DATA,
	MUART_EIGHT_BIT_DATA,
	DATA_RESERVED1,
	DATA_RESERVED2,
	DATA_RESERVED3,
	MUART_NINE_BIT_DATA

}en_muartDataLength_t;




typedef struct
{
	en_muartParity_t		enParityType;
	en_muartDataLength_t	enDataLength;

}st_muart_t;


#endif /* MCAL_UART_MUART_CONFIG_H_ */
