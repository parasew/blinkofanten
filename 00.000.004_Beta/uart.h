
#define F_CPU 8000000L
#define BAUD 19200L
         
 
// Berechnungen
// clever runden
#define UBRR_VAL  ((F_CPU+BAUD*8)/(BAUD*16)-1)  
// Reale Baudrate
#define BAUD_REAL (F_CPU/(16*(UBRR_VAL+1)))     
// Fehler in Promille 
#define BAUD_ERROR ((BAUD_REAL*1000)/BAUD-1000) 
 
#if ((BAUD_ERROR>10) || (BAUD_ERROR<-10))
  #error Systematischer Fehler der Baudrate grösser 1% und damit zu hoch! 
#endif
 


#include <avr/io.h>

void UARTInit(void);
void UARTTX(unsigned char c);
void UARTTX_String(unsigned char *data, unsigned char len);
uint8_t UARTRX(void);

