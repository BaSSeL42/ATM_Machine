/*
 * HSPI_Interface.h
 *
 *  Created on: Dec 17, 2023
 *      Author: hp
 */

#ifndef HAL_HSPI_HSPI_INTERFACE_H_
#define HAL_HSPI_HSPI_INTERFACE_H_


#include "../../Common/std_types.h"
#include "../../MCAL/SPI/SPI_Interface.h"

typedef enum
{
	HSPI_NOK = 0,
	HSPI_OK  = 1

}enu_HSPI_status_t;




typedef enum
{
	SPI_MASTER = 0,
	SPI_SLAVE = 1 ,
	SPI_INVALID

}en_masterSlave_t;



enu_HSPI_status_t HSPI_enMasterInit(enu_spiPrescalar_t copy_enPrecalar);
enu_HSPI_status_t HSPI_enSlaveInit(void);
void HSPI_vidTransmitChar(Uint8_t copy_u8_data);
enu_HSPI_status_t HSPI_enReceiveChar(Uint8_t* ref_u8_data);

void HSPI_vidTransmitString(const Uint8_t* copy_ref_u8_str);
enu_HSPI_status_t HSPI_enReceiveString(Uint8_t* ref_u8_buffer, Uint8_t length);




#endif /* HAL_HSPI_HSPI_INTERFACE_H_ */
