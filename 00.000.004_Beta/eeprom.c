#include <avr/eeprom.h>
#include "eeprom.h"


// save data to eeprom
void set_eeprom_byte( uint8_t eeprom_byte )
{
      eeprom_write_byte( &eeprom_LED_Green, '0' );
      eeprom_write_byte( &eeprom_LED_Red, '0' );
}

// returns the dataset from eeprom
uint8_t get_eeprom_byte( void )
{
  uint8_t   eeprom_byte;
  eeprom_byte = eeprom_read_byte( &eeprom_LED_Green );
  return eeprom_byte; 
} 

 
