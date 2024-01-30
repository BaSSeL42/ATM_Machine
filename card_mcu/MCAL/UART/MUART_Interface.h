/*
 * MUART_Interface.h
 *
 *  Created on: Apr 24, 2023
 *      Author: hp
 */
/********************************************************************************************************/
/*											Header Guard												*/
/********************************************************************************************************/
#ifndef MCAL_UART_MUART_INTERFACE_H_
#define MCAL_UART_MUART_INTERFACE_H_

#include "../../Common/std_types.h"
/********************************************************************************************************/
/*											Macros												*/
/********************************************************************************************************/
/*   MUART SPEED   */
#define MUART_SINGLE_SPEED			0
#define MUART_DOUBLE_SPEED			1

/*   MUART Transmitter Reciever Enable   */
#define MUART_TX_ENABLE				0
#define MUART_RX_ENABLE				1
#define MUART_TX_RX_ENABLE			2


/*   MUART Stop bit   */
#define MUART_1_STOP_BIT			0
#define MUART_2_STOP_BIT			1


/********************************************************************************************************/
/*											User-Defined data type										*/
/********************************************************************************************************/
typedef enum
{
	MUART_OK = 0,
	MUART_NOK
}en_uartErrStat_t;

/********************************************************************************************************/
/*											Function Prototype										    */
/********************************************************************************************************/
/*
 * Author		: Bassel Yasser Mahmoud
 * Function		: MUART_enInit
 * Description	: UART Initialization
 * in[1]		: copy_u32BaudRate (BaudRate)
 * Return		: en_uartErrStat_t {MUART_OK, MUART_NOK}
 */
en_uartErrStat_t MUART_enInit(Uint32_t copy_u32BaudRate);


/*
 * Author		: Bassel Yasser Mahmoud
 * Function		: MUART_enSendData
 * Description	: UART transmit data to receiver
 * in[1]		: Copy_u8Data (Data to be sent)
 * Return		: en_uartErrStat_t {MUART_OK, MUART_NOK}
 */
en_uartErrStat_t MUART_enSendData(Uint8_t Copy_u8Data);


/*
 * Author		: Bassel Yasser Mahmoud
 * Function		: MUART_enRecieveData
 * Description	: UART Received data from transmitter
 * in[1]		: Ref_u8Data (Data to saved in it)
 * Return		: en_uartErrStat_t {MUART_OK, MUART_NOK}
 */
en_uartErrStat_t MUART_enRecieveData(Uint8_t* Ref_u8Data);

/*
 * Author		: Bassel Yasser Mahmoud
 * Function		: MUART_sendSTRING
 * Description	: Send string to receiver
 * in[1]		: str (String to be sent)
 * Return		: void
 */
void MUART_sendSTRING(const Uint8_t * str);


/*
 * Author		: Bassel Yasser Mahmoud
 * Function		: MUART_receiveSTRING
 * Description	: Receive String from transmitter
 * in[1]		: str  (pointer to array which string to be saved in it)
 * in[2]		: size (Size of array)
 * Return		: void
 */
void MUART_receiveSTRING(Uint8_t * str ,Uint8_t size );



#endif /* MCAL_UART_MUART_INTERFACE_H_ */
/********************************************************************************************************/
/*											END												*/
/********************************************************************************************************/
