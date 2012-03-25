void InitPorts(void);
void InitTimer(void);
void WrtiteCharOut(void);
void LZSend0(void);
void LZSend1(void);
void data0(void);
void data1(void);
void clock(void);
void display0(void);
void display1(void);
void Blink0(void);
void Blink1(void);
void TogBlink(void);
void RedLed0(void);
void RedLed1(void);
void TogRedLed(void);
void GreenLed0(void);
void GreenLed1(void);
void TogGreenLed(void);
void RxUsbURxRs232Verarbeiten(uint8_t daten);



//Kommt noch
extern void set_eeprom_byte( uint8_t eeprom_byte ); 
extern uint8_t get_eeprom_byte( void ); 


//CharPosition ist die derzeitige position beim abarbeiten des aktuellen Buchstabens
uint8_t CharPosition;
//AktuellerChar beinhaltet den aktuellen Buchstaben
uint8_t AktuellerChar;
//CharMoveTimer wenn dieser in Timer interrupt voll ist wird eine Spalte weitergeschoben (CharMoveSub = 1)
uint8_t CharMoveTimer;
//CharMoveSub wird im Timerinterrupt gesetzt. Standart = 0 wenn 1 dann wird in der main eine Spalte weitergeschoben
volatile uint8_t CharMoveSub;
//BlinkTimer ist die Blinkfrequenz der derzeit angewählten Spalten
uint8_t BlinkTimer;
//Mit dieser Variable wird auf den aktuellen buchstaben gezeigt der gerade angezeigt wird
uint8_t TextPos;
//Mit dieser variable werden die Spalten des Buchstabens markiert um zu blinken 0=Normal 1=Blinken
uint8_t CharBlink;

//char* TextString[100];

#define PORT_A PORTA
#define DDR_A DDRA
#define PORT_B PORTB
#define DDR_B DDRB
#define PORT_D PORTD
#define DDR_D DDRD



#define PB7     7
#define PB6     6
#define PB5     5
#define PB4     4
#define PB3     3
#define PB2     2
#define PB1     1
#define PB0     0


#define PortGreenLed 4
#define PortRedLed 7


#define DATABIT		3
#define CLOCKBIT	6
#define DISPLAYBIT	0
#define BLINKBIT	4



/*#define DATABIT		7
#define CLOCKBIT	5
#define DISPLAYBIT	0
#define BLINKBIT	4*/
