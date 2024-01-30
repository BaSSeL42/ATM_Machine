/*
 * MUART_Private.h
 *
 *  Created on: Apr 24, 2023
 *      Author: hp
 */

#ifndef MCAL_UART_MUART_PRIVATE_H_
#define MCAL_UART_MUART_PRIVATE_H_


#define UDR_REG				(*(volatile Uint8_t*)(0x2C))
#define UCSRA_REG			(*(volatile Uint8_t*)(0x2B))
#define UCSRB_REG			(*(volatile Uint8_t*)(0x2A))
#define UBRRL_REG			(*(volatile Uint8_t*)(0x29))
#define UBRRH_REG			(*(volatile Uint8_t*)(0x40))
#define UCSRC_REG			(*(volatile Uint8_t*)(0x40))

#define ENTER_KEY            13



/*  Bits Name   */
#ifndef U2X
#define U2X				2
#endif
#define URSEL			7

#define TXEN			3
#define RXEN			4

#define UCSZ0			1
#define UCSZ1			2
#define UCSZ2			2
#define USBS			3
#define UMSEL			6

#define UDRE			5
#define TXC				6
#define RXC				7

#define RUSBS			3
#define RUPM0			4
#define RUPM1			5

#define RXCIE   7

#endif /* MCAL_UART_MUART_PRIVATE_H_ */
