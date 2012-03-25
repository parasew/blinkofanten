/* blinkytest */


#define CLEAR_PANEL_PIN 10
#define DATA_PIN 11
#define CLOCK_PIN 9


#define PANELS 1
#define PANELDATA_SIZE (10*PANELS)

uint8_t panelData[10*PANELS];

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

void shiftPixelData()
{
  screen_off();
  
  for (int i = 0; i < PANELDATA_SIZE; i++)
  {
    uint8_t value = panelData[i];
    /*
    for (int b = 0; b < 8; b++)
    {
      digitalWrite(DATA_PIN, value & 1);
      digitalWrite(CLOCK_PIN,HIGH);
      digitalWrite(CLOCK_PIN,LOW);
      
      value >>= 1;
    }
    */
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, panelData[i]);
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
  if (0)
  {
    setAllPixel(0xAA);
    shiftPixelData();
    delay(500);
    setAllPixel(0x55);
    shiftPixelData();
    delay(500);
    return;
  }
    
  
  for (int x = 0; x < 8; x++)
  {
    for (int y = 0; y < 9; y++)
    {
      setPixel(x, y, ((x>>1) + (y>>1) + state) & 1);
    }
  }
  
  shiftPixelData();
  delay(state%100);
  state++;

  
}
