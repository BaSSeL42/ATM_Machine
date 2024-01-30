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
				'1',  //ROW 0 COL 0
				'2',	//ROW 0 COL 1
				'3',  //ROW 0 COL 2
		},
		{
				'4',  //ROW 1 COL 0
				'5',	//ROW 1 COL 1
				'6',  //ROW 1 COL 2
		},
		{
				'7',   //ROW 2 COL 0
				'8',	 //ROW 2 COL 1
				'9',  //ROW 2 COL 2
		}
};




str_enPin_t KEYPAD_strColPins[KEYPAD_NO_COL] = {{DIO_PINC_5},{DIO_PINC_6},{DIO_PINC_7}};



str_enPin_t KEYPAD_strRowPins[KEYPAD_NO_ROW] ={ {DIO_PINC_2}, {DIO_PINC_3}, {DIO_PINC_4}};









