/*
 * HEEPROM_Interface.h
 *
 *  Created on: Feb 3, 2023
 *      Author: hp
 */

#ifndef HAL_EEPROM_HEEPROM_INTERFACE_H_
#define HAL_EEPROM_HEEPROM_INTERFACE_H_




void eeprom_init(void);
void eeprom_write_byte(Uint16_t address, Uint8_t data) ;
void eeprom_write_string(Uint16_t Copy_u8Address, const Uint8_t* str);
void eeprom_read_string(Uint16_t Copy_u8Address, Uint8_t* str);
Uint8_t eeprom_read_byte(Uint16_t address);


#endif /* HAL_EEPROM_HEEPROM_INTERFACE_H_ */
