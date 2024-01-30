/*
 * SPI_Configure.h
 *
 *  Created on: Jan 27, 2023
 *      Author: hp
 */

#ifndef MCAL_SPI_SPI_CONFIGURE_H_
#define MCAL_SPI_SPI_CONFIGURE_H_

/*
 * MAster - Slave selection
 */
#define SPI_MASTER			1
#define SPI_SLAVE			2
#define SPI_TYPE			SPI_MASTER


/*
 * Order selection LSB to MSB --- or---- MSB to LSB
 */
#define SPI_ORD_LSB_MSB			1
#define SPI_ORD_MSB_LSB			2
#define SPI_ORD_SEL				SPI_ORD_LSB_MSB


/*
 * Clock polarity selection
 */
#define SPI_CPOL_LR_TF			1   // clock polarity leading edge on rising edge and trailing edge on falling edge
#define SPI_CPOL_LF_TR			2	// clock polarity leading edge on falling edge and trailing edge on rising edge
#define SPI_CPOL_SEL			SPI_CPOL_LR_TF


/*
 * Clock phase selection
 */
#define SPI_CPHA_LSA_TSE			1   // clock phase sampling on leading edge e and setup on trailing edge
#define SPI_CPHA_LSE_TSA			2	// clock phase setup on leading edge e and sampling on trailing edge
#define SPI_CPHA_SEL				SPI_CPHA_LSE_TSA

/*
 * Enable/Disable Interrupt
 */
#define SPI_INT_EN				1
#define SPI_INT_DIS				2
#define SPI_INT_SEL				SPI_INT_DIS

#endif /* MCAL_SPI_SPI_CONFIGURE_H_ */
