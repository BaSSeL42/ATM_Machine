/*
 * SPI_private.h
 *
 *  Created on: Jan 27, 2023
 *      Author: hp
 */

#ifndef MCAL_SPI_SPI_PRIVATE_H_
#define MCAL_SPI_SPI_PRIVATE_H_

/*************************************************************************
 * 					MACROS
 ************************************************************************/
/*SPCR REG*/
#define SPR0		0
#define SPR1		1
#define CPHA		2
#define CPOL		3
#define MSTR		4
#define DORD		5
#define SPE 		6
#define SPIE		7

/*SPSR REG*/

#define SPI2X		0
#define WCOL		6
#define SPIF		7
/*SREG REG*/
#define SPI_I		7
#define SPI_NULL	(void*)(0)

/*************************************************************************
 * 					USER DEFINED DATA_TYPE
 ************************************************************************/
/*
typedef struct
{
	Uint8_t SPI2X:1;

	Uint8_t res1:1;
	Uint8_t res2:1;
	Uint8_t res3:1;
	Uint8_t res4:1;
	Uint8_t res5:1;

	Uint8_t WCOL:1;
	Uint8_t SPIF:1;

}str_spsr_reg;
*/




/*************************************************************************
 * 					SPI REGISTER
 ************************************************************************/
#define SPCR_REG			(*((volatile Uint8_t*)(0x2D)))
//#define SPSR_REG			(*((volatile str_spsr_reg*)(0x2E)))
#define SPSR_REG			(*((volatile Uint8_t*)(0x2E)))
#define SPDR_REG			(*((volatile Uint8_t*)(0x2F)))

/*************************************************************************
 * 					STATUS REGISTER
 ************************************************************************/
#define SREG_REG			(*((volatile Uint8_t*)(0x5F)))

#endif /* MCAL_SPI_SPI_PRIVATE_H_ */
