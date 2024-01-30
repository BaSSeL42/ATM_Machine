/*
 * keypad_cfg.c
 *
 *  Created on: Dec 23, 2022
 *      Author: hp
 */

#include "../../Common/std_types.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "includes/KEYPAD_cfg_v2.h"



Uint8_t KEYPAD_au8KeyValV2[KEYPAD_NO_ROW][KEYPAD_NO_COL] = {
		{
				1,  //ROW 0 COL 0
				2,	//ROW 0 COL 1
				3,  //ROW 0 COL 2
				4   //ROW 0 COL 3
		},
		{
				5,  //ROW 1 COL 0
				6,	//ROW 1 COL 1
				7,  //ROW 1 COL 2
				8   //ROW 1 COL 3
		},
		{
				9,   //ROW 2 COL 0
				10,	 //ROW 2 COL 1
				11,  //ROW 2 COL 2
				12   //ROW 2 COL 3
		},
		{
				13,  //ROW 3 COL 0
				14,	 //ROW 3 COL 1
				15,  //ROW 3 COL 2
				16   //ROW 3 COL 3
		}
};




str_enPin_t KEYPAD_strColPins[KEYPAD_NO_COL] = {{DIO_PIND_0},{DIO_PIND_1},{DIO_PIND_2},{DIO_PIND_3} };



str_enPin_t KEYPAD_strRowPins[KEYPAD_NO_ROW] ={ {DIO_PIND_4}, {DIO_PIND_5}, {DIO_PIND_6}, {DIO_PIND_7} };









