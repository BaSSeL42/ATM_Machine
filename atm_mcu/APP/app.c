/*
 * app.c
 *
 *  Created on: Dec 14, 2023
 *      Author: hp
 */
#include <string.h>
#include <stdio.h>
#include "../Common/Bit_Math.h"
#include "../HAL/HTimer/HTimer.h"
#include "../HAL/LED/led.h"
#include "../HAL/HExtInt/HExtInt.h"
#include "../HAL/HSPI/HSPI_Interface.h"
#include "../HAL/HLCD/HLCD_Interface.h"
#include "../HAL/KEYPAD_V2/includes/keypad_int_v2.h"
#include "database.h"


#include "app.h"


#define RECEIVED_STR_MAX_SIZE				50
#define RECEIVED_PIN_MAX_SIZE				10
#define PAN_FOUND							1
#define PAN_UNFOUND							0
#define PIN_MAX_REPEAT_COUNT				3
#define LCD_SHIFT_FIRST_INDEX_PIN			10
#define LCD_SHIFT_FIRST_INDEX_TRANSACTION	15

#define DONE				0
#define UNDONE				1



Uint8_t gl_reset_is_set = 0;
Uint8_t g_u8_key = '\0' , g_u8_z_e_val = '\0';
static Uint8_t g_u8_database_index , g_u8_is_PAN_exist = PAN_UNFOUND;
static Uint8_t gs_u8_interrupt_counting = 0;
static Uint8_t gs_u8_is_transaction_complete = UNDONE;

extern volatile Uint8_t g_u8_stringComplete;
extern volatile st_dataBuffer_t st_dataBuffer[];
extern volatile Uint32_t g_u32_ovf_count;



void resetFunc(void)
{
    gl_reset_is_set = 1;
    //myMode = NO_MODE;
}


void APP_enterZeroButton(void);




void vid_appInit(void)
{
	(void) HTimer_enInit();
	(void) HGPT0_enInit();
	(void) HSPI_enSlaveInit();
		   HLCD_vidInit();
		   KEYPAD_vidInit_V2();
	(void) HExtInt_enInit(INT_0, FALL_EDGE);
	(void) HExtInt_enCBF(resetFunc);
	(void) HExtInt_enInit(INT_2, RISE_EDGE);
	(void) HExtInt_enCBFInt2(APP_enterZeroButton);




	//HLed_Init(DIO_PINB_0); // For Trigger
}

void vid_appStart(void)
{
	Uint8_t shift = LCD_SHIFT_FIRST_INDEX_PIN , l_u8_received_PAN[RECEIVED_STR_MAX_SIZE] , l_u8_received_PIN[RECEIVED_PIN_MAX_SIZE];
	Uint8_t l_u8_converted_pin[RECEIVED_PIN_MAX_SIZE];
	Uint32_t number_to_display = 0 ;
	Uint8_t l_u8_repeat_write_pin = 0 , l_u8_is_pin_correct = 0, l_u8_shift_transation = LCD_SHIFT_FIRST_INDEX_TRANSACTION;

	GLI();
	HGPT0_vidDelayMs(100);

	HLCD_gotoXY(0, 0);
	HLCD_WriteString((Uint8_t*) "Welcome to ATM");
	HTimer_vidDelayMs( 500);
	HLCD_ClrDisplay();
	HLCD_gotoXY(0, 0);
	HLCD_WriteString((Uint8_t*) "Insert a card");


	while(1)
	{
		if (gl_reset_is_set == 1)
		{
			gl_reset_is_set = 0;
			HTimer_vidDelayMs( 500);
			HLCD_ClrDisplay();
			if (g_u8_stringComplete == 1)
			{
				g_u8_stringComplete = 0;
				strcpy(l_u8_received_PAN, st_dataBuffer[0].receivedBuffer);
				strcpy(l_u8_received_PIN, st_dataBuffer[1].receivedBuffer);

				for (Uint8_t databaseIndex = 0; databaseIndex < DATABASE_BUFFER_SIZE; databaseIndex++)
				{
					if ( (strcmp(st_database[databaseIndex].accountNumber , l_u8_received_PAN)) == 0 )
					{
						g_u8_database_index = databaseIndex;
						g_u8_is_PAN_exist = PAN_FOUND;
						break;
					}
					else {}
				}

				if (g_u8_is_PAN_exist == PAN_FOUND)
				{
					HLCD_gotoXY(0, 0);
					HLCD_WriteString( (Uint8_t*) "APPROVED" );
					while (l_u8_repeat_write_pin < PIN_MAX_REPEAT_COUNT)
					{
						HLCD_gotoXY(1, 7);
						HLCD_WriteString( (Uint8_t*) "0000" );
						while ( g_u8_key != '#')
						{
							if(g_u8_z_e_val == '\0')
							{
								g_u8_key = KEYPAD_u8GetPressed_V2();
							}
							else if ( (g_u8_z_e_val == '0') || (g_u8_z_e_val == '#'))
							{
								g_u8_key = g_u8_z_e_val;
								g_u8_z_e_val = '\0';
							}

							if (g_u8_key != '\0')
							{
								if ( g_u8_key >= '0' && g_u8_key <= '9')
								{
									number_to_display = number_to_display * 10 + (Uint32_t)(g_u8_key - '0');
									HLCD_gotoXY(1, shift);
									HLCD_vidWriteChar('*');
//									HLCD_WriteInt(number_to_display);
									shift--;
									if(shift == LCD_SHIFT_FIRST_INDEX_PIN - 5)
									{
										//HLCD_backspace_Left();
										number_to_display = 0;
										shift = LCD_SHIFT_FIRST_INDEX_PIN;
									}
								}
							}
						}
						sprintf(l_u8_converted_pin , "%ld", number_to_display);
						if( (strcmp(l_u8_converted_pin , l_u8_received_PIN)) == 0 )
						{
							l_u8_is_pin_correct = 1;
							l_u8_repeat_write_pin = PIN_MAX_REPEAT_COUNT + 1;
						}
						else if ((strcmp(l_u8_converted_pin , l_u8_received_PIN)) != 0)
						{
							HLCD_ClrDisplay();
							HLCD_gotoXY(0, 2);
							HLCD_WriteString( (Uint8_t*) "try again" );
							l_u8_is_pin_correct = 0;
							l_u8_repeat_write_pin++;
							number_to_display = 0;
							shift = 10;
							g_u8_key = '\0';
						}
					}
					if (l_u8_is_pin_correct == 0)
					{
						HLCD_ClrDisplay();
						HLCD_gotoXY(0, 7);
						HLCD_WriteString( (Uint8_t*) "BLOCKED" );
						st_database[g_u8_database_index].en_accountState = BLOCKED;
					}
					else if (l_u8_is_pin_correct == 1)
					{
						HLCD_ClrDisplay();
						HLCD_gotoXY(0, 0);
						HLCD_WriteString( (Uint8_t*) "HELLO" );
						HLCD_gotoXY(0, 7);
						HLCD_WriteString( (Uint8_t*) st_database[g_u8_database_index].name );
						HTimer_vidDelayMs( 500);

						if (st_database[g_u8_database_index].en_accountState == RUNNING)
						{
							HLCD_ClrDisplay();
							HLCD_gotoXY(0, 2);
							HLCD_WriteString( (Uint8_t*) "Enter ur val" );
							HLCD_gotoXY(1, (LCD_SHIFT_FIRST_INDEX_TRANSACTION - 3));
							HLCD_WriteString( (Uint8_t*) "0000" );
							g_u8_key = '\0';
							number_to_display = 0;
							while ( g_u8_key != '#')
							{
								if(g_u8_z_e_val == '\0')
								{
									g_u8_key = KEYPAD_u8GetPressed_V2();
								}
								else if ( (g_u8_z_e_val == '0') || (g_u8_z_e_val == '#'))
								{
									g_u8_key = g_u8_z_e_val;
									g_u8_z_e_val = '\0';
								}
								if (g_u8_key != '\0')
								{
									if ( g_u8_key >= '0' && g_u8_key <= '9')
									{
										number_to_display = number_to_display * 10 + (Uint32_t)(g_u8_key - '0');
										HLCD_gotoXY(1, l_u8_shift_transation);
										HLCD_WriteInt(number_to_display);
										l_u8_shift_transation--;
										if(l_u8_shift_transation == ( LCD_SHIFT_FIRST_INDEX_TRANSACTION - 5) )
										{
											//HLCD_backspace_Left();
											number_to_display = 0;
											l_u8_shift_transation = LCD_SHIFT_FIRST_INDEX_TRANSACTION;
										}
									}
								}
							}

							if (number_to_display > MAX_DAILY_LIMIT)
							{
								HLCD_ClrDisplay();
								HLCD_gotoXY(0, 0);
								HLCD_WriteString( (Uint8_t*) "MAX_LIMIT_EXCEED" );
								HTimer_vidDelayMs( 500);
							}
							else if (number_to_display > st_database[g_u8_database_index].balance)
							{
								HLCD_ClrDisplay();
								HLCD_gotoXY(0, 0);
								HLCD_WriteString( (Uint8_t*) "INSUFFICIENT_FUND" );
								HTimer_vidDelayMs( 500);
							}
							else if (number_to_display <= st_database[g_u8_database_index].balance)
							{
								HLCD_ClrDisplay();
								HLCD_gotoXY(0, 0);
								HLCD_WriteString( (Uint8_t*) "APPROVED" );
								HTimer_vidDelayMs( 500);
								st_database[g_u8_database_index].balance -= number_to_display;
							}
						}
						else if(st_database[g_u8_database_index].en_accountState == BLOCKED)
						{
							HLCD_ClrDisplay();
							HLCD_gotoXY(0, 0);
							HLCD_WriteString( (Uint8_t*) "CARD stolen" );
						}
						else
						{
							/* do nothing */
						}
					}
				}
				else if (g_u8_is_PAN_exist == PAN_UNFOUND)
				{
					HLCD_ClrDisplay();
					HLCD_gotoXY(0, 0);
					HLCD_WriteString( (Uint8_t*) "FRAUD CARD" );
				}
				else
				{
					/* do nothing */
				}
			}
		}

		if (gs_u8_is_transaction_complete == DONE)
		{
			HLCD_ClrDisplay();
			HLCD_gotoXY(0, 0);
			HLCD_WriteString( (Uint8_t*) "eject card" );
			HTimer_vidDelayMs( 500);
		}
	}


}


void APP_enterZeroButton(void)
{
	if (gs_u8_interrupt_counting == 0)
	{
		g_u32_ovf_count = 0;
		HGPT0_vidStart();
		(void) HExtInt_enInit(INT_2, FALL_EDGE);
		gs_u8_interrupt_counting = 1;
	}
	else if (gs_u8_interrupt_counting == 1)
	{
		gs_u8_interrupt_counting = 0;
		HGPT0_vidStop();
		(void) HExtInt_enInit(INT_2, RISE_EDGE);
		if ((g_u32_ovf_count < 10) && (g_u32_ovf_count != 0) )
		{
			g_u8_z_e_val = '0';
		}
		else if (g_u32_ovf_count >= 10)
		{
			g_u8_z_e_val = '#';
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
}


