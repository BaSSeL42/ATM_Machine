/*
 * app.c
 *
 *  Created on: Dec 14, 2023
 *      Author: hp
 */
#include <string.h>
#include "../Common/Bit_Math.h"
#include "../HAL/HUART/HUART_Interface.h"
#include "../HAL/EEPROM/HEEPROM_Interface.h"
#include "../HAL/HTimer/HTimer.h"
#include "../HAL/LED/led.h"
#include "../HAL/HExtInt/HExtInt.h"
#include "../HAL/HSPI/HSPI_Interface.h"
#include "app.h"

#include <avr/interrupt.h>



#define MAX_BUFFER		20
#define PIN_BUFFER		10

Uint8_t myMode = PROGRAMMING_MODE;

Uint8_t gl_reset_is_set = 0;

void resetFunc(void)
{
    gl_reset_is_set = 1;
    myMode = NO_MODE;
}






void vid_appInit(void)
{
	(void) HUART_enInit(9600);
	eeprom_init();
	(void) HTimer_enInit();
	(void) HSPI_enMasterInit(SPI_PRE_16);
	(void) HExtInt_enInit(INT_0, FALL_EDGE);
	(void) HExtInt_enCBF(resetFunc);
	HLed_Init(DIO_PINB_0); // For Trigger
}

void vid_appStart(void)
{
	Uint8_t  is_ok = 0 , flag = 0, rePIN_status = 0 , once = 0 , ch;
	Uint8_t selection , PAN_size = 0, PIN_size = 0;
	Uint8_t PAN_buffer[MAX_BUFFER] , PIN_buffer[PIN_BUFFER], RE_PIN_buffer[PIN_BUFFER];
	Uint8_t read_string_from_eeprom[50] , read_pin_from_eeprom[10];


	while(1)
	{
		if (once == 0)
		{
			if (eeprom_read_byte(0x0060) == 0xAA && gl_reset_is_set == 0)
			{
				HTimer_vidDelayMs(30);
				myMode = USER_MODE;
			}
			else if (eeprom_read_byte(0x0060) != 0xAA && gl_reset_is_set == 0)
			{
				HTimer_vidDelayMs(30);
				myMode = PROGRAMMING_MODE;
			}
			else
			{
				/* do nothing */
			}
		}
		else
		{
			/* do nothing */
		}

		if ( NO_MODE == myMode)
		{
			HUART_sendSTRING( (Uint8_t* ) "Hello! please Enter Mode \r\n" );
			HUART_sendSTRING( (Uint8_t* ) "PROGRAMMING MODE press 1 \r\n" );
			HUART_sendSTRING( (Uint8_t* ) "USER MODE 		press 2 \r\n" );
			HUART_sendSTRING( (Uint8_t* ) ">> " );
			(void)HUART_enRecieveData( &selection );

			if( selection == '1' )
			{
				myMode = PROGRAMMING_MODE;
			}
			else if(selection == '2')
			{
				myMode = USER_MODE;
			}
			else
			{
				// do nothing
			}


			//HTimer_vidDelayMs(1000);

		}
		else if (PROGRAMMING_MODE == myMode )
		{
			HUART_sendSTRING( (Uint8_t* ) "\r Please Enter Your Card PAN \r\n" );
			HUART_sendSTRING( (Uint8_t* ) ">>  " );
			HUART_receiveSTRING(PAN_buffer, MAX_BUFFER);

			//HUART_sendSTRING( PAN_buffer );
			PAN_size = strlen( (Uint8_t*) PAN_buffer);

			if ( PAN_size == 16 )
			{
				eeprom_write_byte(0x0000, PAN_size) ;
				HTimer_vidDelayMs(30);
				eeprom_write_string(0x0010, PAN_buffer);

				HTimer_vidDelayMs(30);
				//data = eeprom_read_byte(0x0010);
				//HUART_enSendData( data );
				while (PIN_size != 4)
				{
					HUART_sendSTRING( (Uint8_t* ) "\r Please Enter Your PIN of 4 Numeric Digit \r\n" );
					HUART_sendSTRING( (Uint8_t* ) ">>  " );
					HUART_receiveSTRING(PIN_buffer, PIN_BUFFER);
					PIN_size = strlen(PIN_buffer);
					if(PIN_size == 4)
					{
						while(is_ok == 0)
						{
							for (Uint8_t i = 0; i < PIN_size; i++)
							{
								if(PIN_buffer[i] >= '0' && PIN_buffer[i] <= '9')
								{

								}
								else
								{
									flag = 1;
								}
							}

							if (flag == 0)
							{
								is_ok = 1;
							}
							else if(flag == 1)
							{
								flag = 0;
								HUART_sendSTRING( (Uint8_t* ) "\r Please Enter Numeric Digit \r\n" );
								HUART_sendSTRING( (Uint8_t* ) ">>  " );
								HUART_receiveSTRING(PIN_buffer, PIN_BUFFER);
								PIN_size = strlen(PIN_buffer);
							}
						}
					}
					else
					{
						HUART_sendSTRING( (Uint8_t* ) "\r Please Enter 4 Digit \r\n" );
					}
				}


				while (rePIN_status != 1)
				{
					HUART_sendSTRING( (Uint8_t* ) "\r retype your pin \r\n" );
					HUART_sendSTRING( (Uint8_t* ) ">>  " );
					HUART_receiveSTRING(RE_PIN_buffer, PIN_BUFFER);

					if ( strcmp(PIN_buffer, RE_PIN_buffer) == 0 )
					{
						eeprom_write_byte(0x0030, PIN_size) ;
						HTimer_vidDelayMs(30);
						eeprom_write_string(0x0040, PIN_buffer);
						HTimer_vidDelayMs(30);
						myMode = USER_MODE ;
						rePIN_status = 1;
					}
					else
					{
						HUART_sendSTRING( (Uint8_t* ) "\r try again \r\n" );
					}
				}


				eeprom_write_byte(0x0060, 0xAA) ;
				HTimer_vidDelayMs(30);
			}
		}
		else if(USER_MODE == myMode)
		{
			HUART_sendSTRING( (Uint8_t* ) "\r Hello Bassel \r\n" );
			//HTimer_vidDelayMs(500);

			//HTimer_vidDelayMs(500);

			HLed_on(DIO_PINB_0);
			HTimer_vidDelayMs(100);
			HLed_off(DIO_PINB_0);

//			HSPI_vidTransmitString((Uint8_t*) " Hello " );
//			HSPI_vidTransmitChar('z');
//			eeprom_read_string(0x0010, read_string_from_eeprom);
			eeprom_read_string(0x0010, 0x0000, read_string_from_eeprom);
			HUART_sendSTRING( (Uint8_t* ) read_string_from_eeprom );
			HSPI_vidTransmitString( read_string_from_eeprom );
//			HTimer_vidDelayMs(100);
			HUART_sendSTRING( (Uint8_t* ) "\r\n" );
			eeprom_read_string(0x0040, 0x0030, read_pin_from_eeprom);
			HUART_sendSTRING( (Uint8_t* ) read_pin_from_eeprom );
			HSPI_vidTransmitString( read_pin_from_eeprom );

			HUART_sendSTRING( (Uint8_t* ) "\r bye Bassel \r\n" );

			once = 1;
			myMode = WAITING_MODE ;
		}
		else
		{
			// do nothing
		}
	}

}



