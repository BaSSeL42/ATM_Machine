/*
 * SPI_Program.c
 *
 *  Created on: Jan 27, 2023
 *      Author: hp
 */
/*************************************************************************
 * 					INCLUDES
 ************************************************************************/
#include <avr/interrupt.h>
//#include "../../Common/std_types.h"
#include "../../Common/Bit_Math.h"
#include "SPI_private.h"
#include "SPI_Interface.h"
#include "SPI_Configure.h"




#ifndef NULL
#define NULL	(void*)0
#endif

#define BUFFER_SIZE			50
#define DATA_BUFFER_SIZE	10
/*************************************************************************
 * 					GLOBAL VARIABLES
 ************************************************************************/
volatile Uint8_t  g_dataVal;
volatile Uint8_t g_u8_receivedString[BUFFER_SIZE];
volatile Uint8_t g_u8_stringComplete = 0 ;
volatile Uint8_t g_u8_stringIndex = 0;
volatile Uint8_t g_u8_structBufferIndex = 0;
volatile Uint8_t g_u8_counter = 0;



volatile st_dataBuffer_t st_dataBuffer[DATA_BUFFER_SIZE];

/*************************************************************************
 * 					FUNCTION IMPLEMENTATION
 ************************************************************************/
//#if SPI_TYPE == SPI_MASTER
//
//enu_status_t MSPI_enuInit(enu_spiPrescalar_t copy_enPrecalar)
//
//#elif SPI_TYPE == SPI_SLAVE
//
//enu_status_t MSPI_enuInit(void)
//
//#endif
//{
//	enu_status_t errStatus = SPI_OK;
//#if SPI_TYPE == SPI_MASTER
//
//	if (copy_enPrecalar < SPI_PRE_INVALID)
//	{
//		SetBit(SPCR_REG, MSTR); // enable master mode
//		switch(copy_enPrecalar)
//		{
//			case SPI_PRE_4	: 	ClrBit(SPSR_REG, SPI2X);ClrBit(SPCR_REG, SPR1);ClrBit(SPCR_REG, SPR0); break;
//			case SPI_PRE_16	:   ClrBit(SPSR_REG, SPI2X);ClrBit(SPCR_REG, SPR1);SetBit(SPCR_REG, SPR0); break;
//			case SPI_PRE_64	: 	ClrBit(SPSR_REG, SPI2X);SetBit(SPCR_REG, SPR1);ClrBit(SPCR_REG, SPR0); break;
//			case SPI_PRE_128: 	ClrBit(SPSR_REG, SPI2X);SetBit(SPCR_REG, SPR1);SetBit(SPCR_REG, SPR0); break;
//			case SPI_PREx2_2	: 	SetBit(SPSR_REG, SPI2X);ClrBit(SPCR_REG, SPR1);ClrBit(SPCR_REG, SPR0); break;
//			case SPI_PREx2_8	: 	SetBit(SPSR_REG, SPI2X);ClrBit(SPCR_REG, SPR1);SetBit(SPCR_REG, SPR0); break;
//			case SPI_PREx2_32	: 	SetBit(SPSR_REG, SPI2X);SetBit(SPCR_REG, SPR1);ClrBit(SPCR_REG, SPR0); break;
//			case SPI_PREx2_64	: 	SetBit(SPSR_REG, SPI2X);SetBit(SPCR_REG, SPR1);SetBit(SPCR_REG, SPR0); break;
//			default: break;
//		}
//
//
//#if SPI_ORD_SEL == SPI_ORD_LSB_MSB
//
//		SetBit(SPCR_REG, DORD);
//
//#elif SPI_ORD_SEL == SPI_ORD_MSB_LSB
//
//		ClrBit(SPCR_REG, DORD);
//
//#endif
//
//
//#if SPI_CPOL_SEL == SPI_CPOL_LR_TF
//
//		ClrBit(SPCR_REG, CPOL);
//
//#elif SPI_CPOL_SEL == SPI_CPOL_LF_TR
//
//		SetBit(SPCR_REG, CPOL);
//
//#endif
//
//
//#if SPI_CPHA_SEL == SPI_CPHA_LSA_TSE
//
//		ClrBit(SPCR_REG, CPHA);
//
//#elif SPI_CPHA_SEL == SPI_CPHA_LSE_TSA
//
//		SetBit(SPCR_REG, CPHA);
//
//#endif
//
//		SetBit(SPCR_REG, SPE); // enable SPI
//
//
//	}else{
//		errStatus = SPI_NOK;
//	}
//
//#elif SPI_TYPE == SPI_SLAVE
//
//
//	ClrBit(SPCR_REG, MSTR);  // set as slave
//
//#if SPI_ORD_SEL == SPI_ORD_LSB_MSB
//
//		SetBit(SPCR_REG, DORD);
//
//#elif SPI_ORD_SEL == SPI_ORD_MSB_LSB
//
//		ClrBit(SPCR_REG, DORD);
//
//#endif
//
//
//#if SPI_CPOL_SEL == SPI_CPOL_LR_TF
//
//		ClrBit(SPCR_REG, CPOL);
//
//#elif SPI_CPOL_SEL == SPI_CPOL_LF_TR
//
//		SetBit(SPCR_REG, CPOL);
//
//#endif
//
//
//#if SPI_CPHA_SEL == SPI_CPHA_LSA_TSE
//
//		ClrBit(SPCR_REG, CPHA);
//
//#elif SPI_CPHA_SEL == SPI_CPHA_LSE_TSA
//
//		SetBit(SPCR_REG, CPHA);
//
//#endif
//
//		SetBit(SPCR_REG, SPE); // enable SPI
//
//
//#endif
//
//	return errStatus;
//}
//
//
//
//
//enu_status_t MSPI_Transciever(Uint8_t copy_u8Value , Uint8_t* ref_pu8Value)
//{
//	enu_status_t errStatus = SPI_OK;
//
//	if (ref_pu8Value != SPI_NULL)
//	{
//		SPDR_REG = copy_u8Value;
//
//#if SPI_INT_SEL == SPI_INT_DIS
//		while ( !(GetBit(SPSR_REG, SPIF)) );
//		*ref_pu8Value = SPDR_REG;
//#elif SPI_INT_SEL == SPI_INT_EN
//		SetBit(SPCR_REG, SPIE); // enable SPI interrupts
//		SetBit(SREG_REG, SPI_I); // enable global interrupt
//
//#endif
//	}else
//	{
//		errStatus = SPI_NOK;
//	}
//
//	return errStatus;
//}













enu_status_t MSPI_enMasterInit(enu_spiPrescalar_t copy_enPrecalar)
{
	enu_status_t errStatus = SPI_OK;
	if (copy_enPrecalar < SPI_PRE_INVALID)
	{
		SetBit(SPCR_REG, MSTR); // enable master mode
		switch(copy_enPrecalar)
		{
			case SPI_PRE_4	: 	ClrBit(SPSR_REG, SPI2X);ClrBit(SPCR_REG, SPR1);ClrBit(SPCR_REG, SPR0); break;
			case SPI_PRE_16	:   ClrBit(SPSR_REG, SPI2X);ClrBit(SPCR_REG, SPR1);SetBit(SPCR_REG, SPR0); break;
			case SPI_PRE_64	: 	ClrBit(SPSR_REG, SPI2X);SetBit(SPCR_REG, SPR1);ClrBit(SPCR_REG, SPR0); break;
			case SPI_PRE_128: 	ClrBit(SPSR_REG, SPI2X);SetBit(SPCR_REG, SPR1);SetBit(SPCR_REG, SPR0); break;
			case SPI_PREx2_2	: 	SetBit(SPSR_REG, SPI2X);ClrBit(SPCR_REG, SPR1);ClrBit(SPCR_REG, SPR0); break;
			case SPI_PREx2_8	: 	SetBit(SPSR_REG, SPI2X);ClrBit(SPCR_REG, SPR1);SetBit(SPCR_REG, SPR0); break;
			case SPI_PREx2_32	: 	SetBit(SPSR_REG, SPI2X);SetBit(SPCR_REG, SPR1);ClrBit(SPCR_REG, SPR0); break;
			case SPI_PREx2_64	: 	SetBit(SPSR_REG, SPI2X);SetBit(SPCR_REG, SPR1);SetBit(SPCR_REG, SPR0); break;
			default: break;
		}
#if SPI_ORD_SEL == SPI_ORD_LSB_MSB

		SetBit(SPCR_REG, DORD);

#elif SPI_ORD_SEL == SPI_ORD_MSB_LSB

		ClrBit(SPCR_REG, DORD);

#endif


#if SPI_CPOL_SEL == SPI_CPOL_LR_TF

		ClrBit(SPCR_REG, CPOL);

#elif SPI_CPOL_SEL == SPI_CPOL_LF_TR

		SetBit(SPCR_REG, CPOL);

#endif


#if SPI_CPHA_SEL == SPI_CPHA_LSA_TSE

		ClrBit(SPCR_REG, CPHA);

#elif SPI_CPHA_SEL == SPI_CPHA_LSE_TSA

		SetBit(SPCR_REG, CPHA);

#endif

		ClrBit( SPCR_REG, SPIE); // disable ISR
		SetBit(SPCR_REG, SPE); // enable SPI

	}
	else
	{
		errStatus = SPI_NOK;
	}

		return errStatus;
}





enu_status_t MSPI_enSlaveInit(void)
{
	enu_status_t errStatus = SPI_OK;

	SPDR_REG = 0xFF;

	ClrBit(SPCR_REG, MSTR);  // set as slave
	SetBit( SPCR_REG, SPIE); // Enable ISR

#if SPI_ORD_SEL == SPI_ORD_LSB_MSB

		SetBit(SPCR_REG, DORD);

#elif SPI_ORD_SEL == SPI_ORD_MSB_LSB

		ClrBit(SPCR_REG, DORD);

#endif


#if SPI_CPOL_SEL == SPI_CPOL_LR_TF

		ClrBit(SPCR_REG, CPOL);

#elif SPI_CPOL_SEL == SPI_CPOL_LF_TR

		SetBit(SPCR_REG, CPOL);

#endif


#if SPI_CPHA_SEL == SPI_CPHA_LSA_TSE

		ClrBit(SPCR_REG, CPHA);

#elif SPI_CPHA_SEL == SPI_CPHA_LSE_TSA

		SetBit(SPCR_REG, CPHA);

#endif

		SetBit(SPCR_REG, SPE); // enable SPI

		return errStatus;
}





void MSPI_vidTransmitChar(Uint8_t copy_u8_data)
{
	Uint8_t flush_buffer ;
	SPDR_REG = copy_u8_data;

	while (!(SPSR_REG & (1 << SPIF)));
	flush_buffer = SPDR_REG;
//	while ( (GetBit(SPSR_REG, SPIF)) == 0 );
}


enu_status_t MSPI_enReceiveChar(Uint8_t* ref_u8_data)
{
	enu_status_t errStatus = SPI_OK;


	if (ref_u8_data != NULL)
	{
//		SPDR_REG = 0xFF;
		while (!(SPSR_REG & (1 << SPIF)));
//		while ( (GetBit(SPSR_REG, SPIF)) == 0);
		*ref_u8_data = SPDR_REG;
	}
	else
	{
		errStatus = SPI_NOK;
	}

	return errStatus;
}



enu_status_t MSPI_enReceiveString(Uint8_t* ref_u8_buffer, Uint8_t length)
{
	enu_status_t MSPI_status = SPI_OK;
	Uint32_t buffer_index = 0 ;
	Uint8_t receivedChar;

	if (ref_u8_buffer != NULL && length > 0)
	{

		while(buffer_index < length - 1)
		{
			if ((SPSR_REG & (1 << SPIF)))
			{
				MSPI_status &= MSPI_enReceiveChar(&receivedChar);
				if (receivedChar == '\0')
				{
					break;
				}

				ref_u8_buffer[buffer_index] = receivedChar;
				buffer_index++;
			}
		}
		ref_u8_buffer[buffer_index] = '\0';
	}
	else
	{
	   MSPI_status = SPI_NOK;
	}
	return MSPI_status;
}


/*************************************************************************
 * 					INTERRUPT HANDLER
 ************************************************************************/
ISR(SPI_STC_vect)
{
    Uint8_t receivedChar = SPDR_REG;

    // Check for the end of the string (using '\0' as a delimiter)
//    if (receivedChar == '\0' || g_u8_stringIndex >= sizeof(g_u8_receivedString) - 1)
    if (receivedChar == '\0' || g_u8_stringIndex >= sizeof(st_dataBuffer[g_u8_structBufferIndex].receivedBuffer) - 1)
    {
//    	g_u8_receivedString[g_u8_stringIndex] = '\0';  // Null-terminate the string
    	st_dataBuffer[g_u8_structBufferIndex].receivedBuffer[g_u8_stringIndex] = '\0';
        g_u8_stringComplete = 1;
        g_u8_stringIndex = 0;  // Reset the index for the next string
        g_u8_structBufferIndex++;
        g_u8_counter++;
    }
    else
    {
    	st_dataBuffer[g_u8_structBufferIndex].receivedBuffer[g_u8_stringIndex] = receivedChar;
//    	g_u8_receivedString[g_u8_stringIndex] = receivedChar;
        g_u8_stringIndex++;
    }
}
