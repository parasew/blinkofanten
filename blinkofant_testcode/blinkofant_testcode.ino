/* 
blinkytest 
for blinkofant

wizard23

1 modul braucht 1.2A

*/


#include "SPI.h"

#define CLEAR_PANEL_PIN 10
// this goes on panel to pin #10

#define DATA_PIN 11
// this goes on panel to pin #8 

#define CLOCK_PIN 13
// this goes on panel to pin #4 

#define PANELS 2
#define PANELDATA_SIZE (10*PANELS)

uint8_t panelData[PANELDATA_SIZE];

void setPixel(int x, int y, int value)
{
  int index = (y+1) + x*10; // y+1 because 1st bit controlls blinking
  int byteNr = index >> 3; // division by 8
  int bitNr = index & 0x7; // rest bei div durch 8
 
   if (value)
   {
     panelData[byteNr] |= 1 << bitNr;
   }
   else
   {
     panelData[byteNr] &= ~(1 << bitNr);
   }
}

void setAllPixel(uint8_t value)
{
  for (int i = 0; i < PANELDATA_SIZE; i++)
  {
    panelData[i] = value;
  }
}


/*  we use SPI now ;)
void shiftPixelData()
{
  screen_off();
  
  for (int i = 0; i < PANELDATA_SIZE; i++)
  {
    uint8_t value = panelData[i];

    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, panelData[i]);
  }
  
  screen_on();
}
*/


void shiftPixelData()
{
  screen_off();
  
  for (int i = 0; i < PANELDATA_SIZE; i++)
  {
    uint8_t value = panelData[i];
    
    SPDR = panelData[i];
    while(!(SPSR & (1<<SPIF)));
  }
  
  screen_on();
    

}



void setup()
{
  pinMode(CLEAR_PANEL_PIN,OUTPUT);
  pinMode(DATA_PIN,OUTPUT);
  pinMode(CLOCK_PIN,OUTPUT);
  
  digitalWrite(CLEAR_PANEL_PIN,LOW);
  digitalWrite(DATA_PIN,LOW);
  digitalWrite(CLOCK_PIN,LOW);
  
  
    SPI.begin();
    SPI.setBitOrder(LSBFIRST);
    SPI.setDataMode(SPI_MODE0);
    SPI.setClockDivider(SPI_CLOCK_DIV128); // biggest divider there is.
    

}




void screen_off()
{
    digitalWrite(CLEAR_PANEL_PIN,LOW);
}

void screen_on()
{
    digitalWrite(CLEAR_PANEL_PIN,HIGH);
}


int state = 0;
  
void loop ()
{
    state++;
    
    
  for (int x = 0; x < 8*PANELS; x++)
  {
    for (int y = 0; y < 9; y++)
    {
      setPixel(x, y, state % 2);
    }
  }
  
  shiftPixelData();  
  delay(5000);
  return;
    
  /*  
  for (int x = 0; x < 8*PANELS; x++)
  {
    for (int y = 0; y < 9; y++)
    {
      setPixel(x, y, ((x>>1)+(y>>1)+state)&1);
    }
  }
  
  shiftPixelData();  
  delay(4);
  return;
  */
  for (int x = 0; x < 8*PANELS; x++)
  {
    for (int y = 0; y < 9; y++)
    {
      //setPixel(x, y, ((x>>1) + (y>>1) + state) & 1);
      float dx = x-4;
      float dy = y-4;
      float d = sqrt(dx*dx+dy*dy); 
      int ds = 3*d+state;
      setPixel(x, y, (ds % 20) <= 10);
    }
  }
  
  shiftPixelData();
  delay(5);


  
}
