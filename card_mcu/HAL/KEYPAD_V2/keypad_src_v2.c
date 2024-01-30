/*
 * keypad_src.c
 *
 *  Created on: Dec 23, 2022
 *      Author: hp
 */

/**************************************************************************************************
 * 											Includes
 *************************************************************************************************/
#include <util/delay.h>

/*******************  STD libraries ******************************************/
#include "../../Common/Bit_Math.h"
#include "../../Common/std_types.h"

/******************* peripherial libraries ******************************************/
#include "../../MCAL/DIO/DIO_Interface.h"
#include "includes/KEYPAD_cfg_v2.h"
/**************************************************************************************************
 * 										extern and global variables
 *************************************************************************************************/
extern Uint8_t KEYPAD_au8KeyValV2[KEYPAD_NO_ROW][KEYPAD_NO_COL];
extern str_enPin_t KEYPAD_strRowPins[KEYPAD_NO_ROW];
extern str_enPin_t KEYPAD_strColPins[KEYPAD_NO_COL];


/**************************************************************************************************
 * 									functions Implementation
 *************************************************************************************************/

/*
 * Author		: Bassel Yasser Mahmoud
 * Function		: KEYPAD_vidInit_V2
 * Description	: KEYPAD Initialization
 * in[1]		: void
 * Return		: void
 */
void KEYPAD_vidInit_V2()
{
	Uint8_t local_u8Col;
	Uint8_t local_u8Row;

	for (local_u8Col = 0; local_u8Col <KEYPAD_NO_COL ; local_u8Col++)
	{
		DIO_s8SETPinDir(KEYPAD_strColPins[local_u8Col].key_pin ,OUTPUT);
	}
	for (local_u8Row = 0; local_u8Row <KEYPAD_NO_ROW ; local_u8Row++)
	{
		DIO_s8SETPinDir(KEYPAD_strRowPins[local_u8Row].key_pin ,INPUT);
	}
	for (local_u8Col = 0; local_u8Col <KEYPAD_NO_COL ; local_u8Col++)
	{
		DIO_s8SETPinVal(KEYPAD_strColPins[local_u8Col].key_pin ,HIGH);
	}
	for (local_u8Row = 0; local_u8Row <KEYPAD_NO_ROW ; local_u8Row++)
	{
		DIO_s8SETPinVal(KEYPAD_strRowPins[local_u8Row].key_pin ,HIGH);
	}
}


/*
 * Author		: Bassel Yasser Mahmoud
 * Function		: KEYPAD_u8GetPressed_V2
 * Description	: KEYPAG get pin status
 * in[1]		: void
 * Return		: Uint8_t {Pin Status}
 */
Uint8_t KEYPAD_u8GetPressed_V2(void)
{
	static Uint8_t local_u8KeyPressed = NO_KEY_PRESSED;
	Uint8_t local_u8RowStatus;
	Uint8_t local_u8Col;
	Uint8_t local_u8Row;

	for(local_u8Col = 0; local_u8Col < KEYPAD_NO_COL ;local_u8Col++)
	{
		DIO_s8SETPinVal(KEYPAD_strColPins[local_u8Col].key_pin ,LOW);
		for(local_u8Row = 0;local_u8Row < KEYPAD_NO_ROW;local_u8Row++)
		{
			DIO_s8GETPinVal(KEYPAD_strRowPins[local_u8Row].key_pin, &local_u8RowStatus);
			if(!local_u8RowStatus)
			{
				_delay_ms(25);
				DIO_s8GETPinVal(KEYPAD_strRowPins[local_u8Row].key_pin, &local_u8RowStatus);
				if(!local_u8RowStatus)
				{
					local_u8KeyPressed = KEYPAD_au8KeyValV2[local_u8Row][local_u8Col];
				}
				_delay_ms(25);
			}
		}
		DIO_s8SETPinVal(KEYPAD_strColPins[local_u8Col].key_pin ,HIGH);
	}
	return local_u8KeyPressed;
}


/**************************************************************************************************
 * 											END
 *************************************************************************************************/
