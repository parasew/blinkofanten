#include "uart.h"


void UARTInit(void){

	UCSRB |= (1<<RXCIE);				//UART RX Interrupt
	UCSRB |= (1<<TXEN);                // UART TX einschalten
	UCSRB |= (1<<RXEN);				// UART RX einschalten
	//UCSRC |= (1<<URSEL)|(3<<UCSZ0);    // Asynchron 8N1 
	UCSRC |= (3<<UCSZ0);    // Asynchron 8N1 
	
	UBRRH = UBRR_VAL >> 8;
	UBRRL = UBRR_VAL & 0xFF;

}




void UARTTX(unsigned char c){

	while (!(UCSRA & (1<<UDRE)));	//Auf Sendebereitschaft warten
	UDR=c;

}

void UARTTX_String(unsigned char *data, unsigned char len){

    uint8_t i;
	for(i=0;i!=len;i++){
        UARTTX(*data);
        data++;
    }
}

uint8_t UARTRX(void){

	while (!(UCSRA & (1<<RXC)));   // warten bis Zeichen verfuegbar
	return UDR;  
 
}