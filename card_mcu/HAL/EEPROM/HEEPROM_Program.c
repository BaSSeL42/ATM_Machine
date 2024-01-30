/*
 * HEEPROM_Program.c
 *
 *  Created on: Feb 3, 2023
 *      Author: hp
 */
#include <string.h>
#include "../../MCAL/IIC/MI2C_Interface.h"
#include "../../Common/std_types.h"
#include "../../Common/Bit_Math.h"
#include "HEEPROM_Interface.h"

#define EEPROM_ADDRESS		0b01010000



void eeprom_init(void)
{
	i2c_init_master();
}


void eeprom_write_byte(Uint16_t address, Uint8_t data)  // address is 10 bit
{
	Uint8_t deviceAddress;
	Uint8_t dataAddress;

	deviceAddress = EEPROM_ADDRESS | ((address >> 8) & 0x0003);
//	dataAddress = (address & 0b0011111111);

	/* Send start condition */
	i2c_start();
	/* Send slave address */
	i2c_send_slave_address_with_write_req(deviceAddress);     // i2c_write_byte(0x50 | (address >> 8) & 0x00000111 );
	 	 	 	 	 	 	 	 	 	 	 	 	 	 	  // 520 = 0b 01010 0  0  1   1 01110 11
	 	 	 	 	 	 	 	 	 	 	 	 	 	 	  //                A2 P1 P2  B7      B0
	/* Send data location */
	i2c_write_byte((Uint8_t) address); // or i2c_write_byte(dataAddress);
	/* Send data */
	i2c_write_byte(data);
	/* Send Stop Condition */
	i2c_stop();
}


Uint8_t eeprom_read_byte(Uint16_t address)
{
	Uint8_t deviceAddress;
	Uint8_t dataAddress;
	Uint8_t data;
	deviceAddress = EEPROM_ADDRESS | ((address >> 8) & 0x0003);

	/* Send start condition */
	i2c_start();
	/* Send slave address with write request*/
	i2c_send_slave_address_with_write_req(deviceAddress);
	/* Send Data location*/
	i2c_write_byte((Uint8_t) address);
	/* Send Repeated Start Condition*/
	i2c_repeated_start();
	/* Send slave address with read request*/
	i2c_send_slave_address_with_read_req(deviceAddress);
	/*Read Received Byte*/
	data = i2c_read_byte();
	/* Send Stop Condition */
	i2c_stop();

	return data;
}



void eeprom_write_string(Uint16_t Copy_u8Address, const Uint8_t* str)
{
	Uint8_t sendedAddress;
	Uint8_t dataAddress;
	Uint8_t count = 0;

	while(str[count] != '\0')
	{
		count++;

	}
	sendedAddress = EEPROM_ADDRESS | ((Copy_u8Address >> 8) & 0x0003);
	dataAddress = (Uint8_t)Copy_u8Address;
	i2c_start();

	i2c_send_slave_address_with_write_req(sendedAddress);
	i2c_write_byte((Uint8_t) dataAddress);

//    i2c_write_byte(count);

	while(*str != '\0')
	{
		i2c_write_byte(*str);
		str++;
	}

//	    for(Uint8_t i=0;i<count;i++)
//	    {
//		    i2c_write_byte(*str++);
//	    }
	   // i2c_write_byte('\0');

		i2c_stop();
}



void eeprom_read_string(Uint16_t Copy_u8Address, Uint16_t copy_address_PAN_length_size, Uint8_t* str)
{
	Uint8_t len ,count = 0;
	len = eeprom_read_byte(copy_address_PAN_length_size);

	 for(Uint8_t i=0;i<len;i++)
	 {
		 str[count++] = eeprom_read_byte(Copy_u8Address++);;
	 }

	 str[count] = '\0';
}

