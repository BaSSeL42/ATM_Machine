/*
 * keypad_int_v2.h
 *
 *  Created on: Dec 23, 2022
 *      Author: hp
 */
/**************************************************************************************************
 * 											File Guard
 *************************************************************************************************/
#ifndef HAL_KEYPAD_V2_INCLUDES_KEYPAD_INT_V2_H_
#define HAL_KEYPAD_V2_INCLUDES_KEYPAD_INT_V2_H_
/**************************************************************************************************
 * 											Includes
 *************************************************************************************************/
#include "../../../commons/std_types.h"
/**************************************************************************************************
 * 											functions prototype
 *************************************************************************************************/

/*
 * Author		: Bassel Yasser Mahmoud
 * Function		: KEYPAD_vidInit_V2
 * Description	: KEYPAD Initialization
 * in[1]		: void
 * Return		: void
 */
void KEYPAD_vidInit_V2(void);

/*
 * Author		: Bassel Yasser Mahmoud
 * Function		: KEYPAD_u8GetPressed_V2
 * Description	: KEYPAG get pin status
 * in[1]		: void
 * Return		: Uint8_t {Pin Status}
 */
Uint8_t KEYPAD_u8GetPressed_V2(void);

#endif /* HAL_KEYPAD_V2_INCLUDES_KEYPAD_INT_V2_H_ */
