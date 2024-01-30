/*
 * DIO_Interface.h
 *
 *  Created on: Apr 3, 2023
 *      Author: hp
 */

#ifndef MCAL_DIO_DIO_INTERFACE_H_
#define MCAL_DIO_DIO_INTERFACE_H_


#include "../../Common/std_types.h"

#define E_OK	0
#define E_NOK	-1

#define PORT_INPUT		0x00
#define PORT_OUTPUT		0xff

typedef enum
{
	DIO_PINA_0 = 0,
	DIO_PINA_1 = 1,
	DIO_PINA_2 = 2,
	DIO_PINA_3 = 3,
	DIO_PINA_4 = 4,
	DIO_PINA_5 = 5,
	DIO_PINA_6 = 6,
	DIO_PINA_7 = 7,

	DIO_PINB_0 = 8,
	DIO_PINB_1 = 9,
	DIO_PINB_2 = 10,
	DIO_PINB_3 = 11,
	DIO_PINB_4 = 12,
	DIO_PINB_5 = 13,
	DIO_PINB_6 = 14,
	DIO_PINB_7 = 15,

	DIO_PINC_0 = 16,
	DIO_PINC_1 = 17,
	DIO_PINC_2 = 18,
	DIO_PINC_3 = 19,
	DIO_PINC_4 = 20,
	DIO_PINC_5 = 21,
	DIO_PINC_6 = 22,
	DIO_PINC_7 = 23,

	DIO_PIND_0 = 24,
	DIO_PIND_1 = 25,
	DIO_PIND_2 = 26,
	DIO_PIND_3 = 27,
	DIO_PIND_4 = 28,
	DIO_PIND_5 = 29,
	DIO_PIND_6 = 30,
	DIO_PIND_7 = 31,

	PIN_INVALID,

}enu_pin;


typedef enum
{
	DIO_PORTA = 0,
	DIO_PORTB = 1,
	DIO_PORTC = 2,
	DIO_PORTD = 3,
	PORT_INVALID,
}enu_port;

typedef enum
{
	INPUT = 0,
	OUTPUT,
	DIR_INVALID,

}enu_dir;

typedef enum
{
	LOW = 0,
	HIGH,
	VAL_INVALID,

}enu_val;


Sint8_t DIO_s8SETPortDir(enu_port enPortCopy,  enu_dir enPortDir);
Sint8_t DIO_s8SETPortVal(enu_port enPortCopy,  Uint8_t u8PortVal);
Sint8_t DIO_s8GETPortVal(enu_port enPortCopy,  Uint8_t* pu8Val);

Sint8_t DIO_s8SETPinDir (enu_pin enPinCopy, enu_dir enPortDir);
Sint8_t DIO_s8SETPinVal (enu_pin enPinCopy, enu_val enPortVal);
Sint8_t DIO_s8TOGPinVal (enu_pin enPinCopy);
Sint8_t DIO_s8GETPinVal (enu_pin enPinCopy, Uint8_t* pu8Val);


#endif /* 04_MCAL_DIO_DIO_INTERFACE_H_ */
