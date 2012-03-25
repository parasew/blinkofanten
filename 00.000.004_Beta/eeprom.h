#define EEPROM_SECTION  __attribute__ ((section (".eeprom")))

/*
** this global variables are stored in EEPROM
*/
uint8_t   eeprom_LED_Green EEPROM_SECTION  = 0;
uint8_t   eeprom_LED_Red EEPROM_SECTION  = 0;
