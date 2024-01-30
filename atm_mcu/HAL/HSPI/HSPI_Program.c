/*
 * hspi.c
 *
 *  Created on: Dec 17, 2023
 *      Author: hp
 */


#include "../../MCAL/DIO/DIO_Interface.h"
//#include "../../MCAL/SPI/SPI_Interface.h"
#include "HSPI_Interface.h"


#define SS_PIN			DIO_PINB_4
#define MOSI_PIN		DIO_PINB_5
#define MISO_PIN		DIO_PINB_6
#define SCK_PIN			DIO_PINB_7


#define NULL	(void*)0

en_masterSlave_t g_en_master_slave_sel = SPI_INVALID;

enu_HSPI_status_t HSPI_enMasterInit(enu_spiPrescalar_t copy_enPrecalar)
{
	enu_HSPI_status_t HSPI_status = HSPI_OK;



	(void)DIO_s8SETPinDir (SS_PIN	, OUTPUT);
	(void)DIO_s8SETPinDir (MOSI_PIN	, OUTPUT);
	(void)DIO_s8SETPinDir (MISO_PIN	, INPUT	);
	(void)DIO_s8SETPinDir (SCK_PIN	, OUTPUT);

	(void)DIO_s8SETPinVal (SS_PIN	, HIGH);

	HSPI_status &= MSPI_enMasterInit(copy_enPrecalar);

	return HSPI_status;
}



enu_HSPI_status_t HSPI_enSlaveInit(void)
{
	enu_HSPI_status_t HSPI_status = HSPI_OK;



	(void)DIO_s8SETPinDir (SS_PIN	, INPUT	);
	(void)DIO_s8SETPinDir (MOSI_PIN	, INPUT	);
	(void)DIO_s8SETPinDir (MISO_PIN	, OUTPUT);
	(void)DIO_s8SETPinDir (SCK_PIN	, INPUT	);

	HSPI_status &= MSPI_enSlaveInit();

	return HSPI_status;
}



void HSPI_vidTransmitChar(Uint8_t copy_u8_data)
{
	if (g_en_master_slave_sel == SPI_MASTER)
	{
		(void)DIO_s8SETPinVal (SS_PIN	, LOW);
	}
	MSPI_vidTransmitChar(copy_u8_data);
}



enu_HSPI_status_t HSPI_enReceiveChar(Uint8_t* ref_u8_data)
{
	enu_HSPI_status_t HSPI_status = HSPI_OK;

	HSPI_status &= MSPI_enReceiveChar(ref_u8_data);

	return HSPI_status;
}




void HSPI_vidTransmitString(const Uint8_t* copy_ref_u8_str)
{
	if (copy_ref_u8_str != NULL)
	{
		while(*copy_ref_u8_str)
		{
			if (g_en_master_slave_sel == SPI_MASTER)
			{
				(void)DIO_s8SETPinVal (SS_PIN	, LOW);
			}
			MSPI_vidTransmitChar(*copy_ref_u8_str);
			copy_ref_u8_str++;
		}

		MSPI_vidTransmitChar('\0');
	}
}




enu_HSPI_status_t HSPI_enReceiveString(Uint8_t* ref_u8_buffer, Uint8_t length)
{
	enu_HSPI_status_t HSPI_status = HSPI_OK;
	Uint32_t buffer_index = 0 ;

	if (ref_u8_buffer != NULL && length > 0)
	{

		for (buffer_index = 0; buffer_index < length ; buffer_index++)
		{
			HSPI_status &= MSPI_enReceiveChar(&ref_u8_buffer[buffer_index]);

			if (ref_u8_buffer[buffer_index] == '\0')
			{
				buffer_index = length + 1;
			}
		}

		ref_u8_buffer[buffer_index] = '\0';

//		HSPI_status &= MSPI_enReceiveString(ref_u8_buffer, length);
	}
	else
	{
	   HSPI_status = HSPI_NOK;
	}
	return HSPI_status;
}
