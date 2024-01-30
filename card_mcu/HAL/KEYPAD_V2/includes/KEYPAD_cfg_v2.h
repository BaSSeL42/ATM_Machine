/*
 * KEYPAD_cfg.h
 *
 *  Created on: Dec 23, 2022
 *      Author: hp
 */
/**************************************************************************************************
 * 											File Guard
 *************************************************************************************************/
#ifndef HAL_KEYPAD_V2_KEYPAD_CFG_H_
#define HAL_KEYPAD_V2_KEYPAD_CFG_H_
/********************************************************************************************************/
/*											User-Defined data type										*/
/********************************************************************************************************/
typedef struct
{
	enu_pin key_pin;
}str_enPin_t;


/********************************************************************************************************/
/*											MACROS										*/
/********************************************************************************************************/
//#define POLLING				1
//#define PERIODIC			2
//#define KEYPAD_MODE			POLLING

#define KEYPAD_NO_COL		4
#define KEYPAD_NO_ROW		4

#define NO_KEY_PRESSED		0



//extern Uint8_t KEYPAD_au8KeyVal[KEYPAD_NO_ROW][KEYPAD_NO_COL];
//extern str_enPin_t KEYPAD_strRowPins[KEYPAD_NO_ROW];
//extern str_enPin_t KEYPAD_strColPins[KEYPAD_NO_COL];



#endif /* HAL_KEYPAD_V2_KEYPAD_CFG_H_ */
