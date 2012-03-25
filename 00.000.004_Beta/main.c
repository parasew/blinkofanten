//Lichtzeile Steuergerät
//C by WSyS.at 15.02.2011


#define F_CPU 8000000L


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "main.h"
#include "uart.h"
#include "font.c"


int main(void){
	//UART initialisieren
	UARTInit();
	
	//Alle Ports initialisieren
	InitPorts();
	
	//Timer initialisieren
	InitTimer();
	
	CharPosition = 8;
	CharMoveTimer = 0;
	CharMoveSub = 0;
	CharBlink = 0;
	TextPos=0;
	
	// Globale interrupts aktivieren
	sei();
	//String der ausgegeben werden soll. sollte später global sein
	char* TextString = "Testfirmware.  PCB and Firmware designed by WSyS.at   -   ";
	//char* TextString = "Test";
	/*if (get_eeprom_byte() == 'a'){
		 GreenLed1();
	}*/
	//set_eeprom_byte( 88 );

	
	//Main Loop
	while(1)
	{
		//Anzuzeigenden buchstaben in AktuellerChar schieben
		AktuellerChar = TextString[TextPos];
		//Wenn Satz zuende dann ist das letzte char 0. deswegen Textpos=0
		if (AktuellerChar == 0){
			TextPos=0;
			AktuellerChar = TextString[TextPos];
		}
		
		
		//Wenn der timerinterrupt oft genug ausgelöst hat wird eine Spalte weitergeschoben
		if(CharMoveSub == 1){
			CharMoveSub = 0;
			WrtiteCharOut();
		}
	}
		
	return (1);
}

void InitPorts(void) {
	//Port für Lichtzeile1
	DDRB |= 0xFF;
	PORTB = 0;
	
	//2 Status LEDs 
	DDRC |= 0xFF;
	PORTC = 0;
}

void InitTimer(void) {

  // Timer 0 konfigurieren
  TCCR1A = 0;
  TCCR1B = (1<<CS10) | (1<<CS11) | (1<<WGM12); // Prescaler 64  und CTC Modus
  //  8mHz  / prescaler / 1000x-ist-1ms 
  // ((800000/64)/1000) = 125
  OCR1A = 125-1;
 
  // Compare Interrupt erlauben
  TIMSK |= (1<<OCIE1A);

}


void WrtiteCharOut(void) {
		//wenn wir am anfang der Ausgbe sind sollte das nächste Zeichen geladen werden
		if(CharPosition == 8){
			
			//hier muss das n?chste zeichen aus den string geladen werden
		}

		//Komplette LED-Tafel ausschalten um Blinken beim schieben zu verhindern
		display0();
		
		//Das 10.Bit senden um diese zeile zum Blinken zu markieren
		if (CharBlink==0){
			LZSend0();
		}else{
			LZSend1();
		}
		
		//schleife von 0 bis 8 durchlaufen lassen und alle 9 bit der Spalte anzuzeigen
		for (uint8_t i=0; i!=9; i++)
		{
			// altes Laden der Schriftart aus dem Ram.
			//if ( font[AktuellerChar][i] & (1<<CharPosition) ) {
			
			// fontbyte aus dem Ram Laden und bit markieren
			if ( pgm_read_byte(&font[AktuellerChar][i]) & (1<<CharPosition) ) {
				LZSend1();
			}else{
				LZSend0();
			}
		}
		
		//Komplette LED-Tafel wieder einschalten da jetzt nichts mehr blinken kann
		display1();
		
		//Nächste spalte selektieren
		CharPosition--;
		//Wenn die Spalte 0 erreicht wurde wieder auf 8 für den nächsten Buchstaben setzen
		if(CharPosition == 0){
			CharPosition = 8;
			TextPos++;
			TogRedLed();
		}

}

//Eine 0 in die LED-Tafel schicken
void LZSend0(void) {
	data0(); clock();
}

//Eine 1 in die LED-Tafel schicken
void LZSend1(void) {
	data1(); clock();
}

//Datenbit auf 0 schalten
void data0(void) {
	PORTB &= ~(1<<DATABIT);
	_delay_us(2);
}

//Datenbit auf 1 schalten
void data1(void) {
	PORTB |= (1<<DATABIT);
	_delay_us(2);
}

//Tackt kurz einschalten
void clock(void) {
	PORTB |= (1<<CLOCKBIT);
	_delay_us(7);
	PORTB &= ~(1<<CLOCKBIT);
	_delay_us(7);
}

//Komplette LED-Tafel ausschalten
void display0(void) {
	PORTB &= ~(1<<DISPLAYBIT);
}

//Komplette LED-Tafel einschalten
void display1(void) {
	PORTB |= (1<<DISPLAYBIT);
}

//Alle selektierten Spalten aus
void Blink0(void) {
	PORTB &= ~(1<<BLINKBIT);
}

//Alle selektierten Spalten an
void Blink1(void) {
	PORTB |= (1<<BLINKBIT);
}

//Alle selektierten Spalten toggeln
void TogBlink(void) {
	PORTB ^= (1<<BLINKBIT);
}

//Rote LED ausschalten
void RedLed0(void) {
	PORTC &= ~(1<<PortRedLed);
}

//Rote LED einschalten
void RedLed1(void) {
	PORTC |= (1<<PortRedLed);
}

//Rote LED toggeln
void TogRedLed(void) {
	PORTC ^= (1<<PortRedLed);
}

//Grüne LED ausschalten
void GreenLed0(void) {
	PORTC &= ~(1<<PortGreenLed);
}

//Grüne LED einschalten
void GreenLed1(void) {
	PORTC |= (1<<PortGreenLed);
}

//Grüne LED toggeln
void TogGreenLed(void) {
	PORTC ^= (1<<PortGreenLed);
}


//Interrupt UART empfang
ISR(SIG_UART_RECV){
	RxUsbURxRs232Verarbeiten(UDR);
}

//Empfangene UART daten abarbeiten
void RxUsbURxRs232Verarbeiten(uint8_t daten){

}

//Interrupt Timer alle 1ms
SIGNAL (SIG_OUTPUT_COMPARE1A)
{
	CharMoveTimer++;
	if(CharMoveTimer == 50){
		CharMoveTimer = 0;
		CharMoveSub = 1;
	}
	
	BlinkTimer++;
	if(BlinkTimer == 200){
		BlinkTimer = 0;
		TogBlink();
		TogGreenLed();
	}
}
