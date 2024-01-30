/*
 * HUART_Interface.h
 *
 *  Created on: Apr 25, 2023
 *      Author: hp
 */

#ifndef HAL_HUART_HUART_INTERFACE_H_
#define HAL_HUART_HUART_INTERFACE_H_

#include "../../Common/std_types.h"

typedef enum
{
	HUART_OK = 0,
	HUART_NOK

}en_huartErrStat_t;

en_huartErrStat_t HUART_enInit(Uint32_t copy_u32BaudRateH);
en_huartErrStat_t HUART_enSendData(Uint8_t Copy_u8DataH);
en_huartErrStat_t HUART_enRecieveData(Uint8_t* Ref_u8DataH);

void HUART_sendSTRING(Uint8_t * Hstr);
void HUART_receiveSTRING(Uint8_t * Hstr ,Uint8_t Hsize );
void HUART_ClearScreen(void);

#endif /* HAL_HUART_HUART_INTERFACE_H_ */
