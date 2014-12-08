#include <SPI.h>

/* cube 8x8x8

*/
//pins
const byte layerpins[8] = {
  2,3,4,5,6,7,8,9};
const byte latchpin = 10;
/*
The Hardware SPI pins are mostly diffrent on each µC. Look in the datasheet
Connect:
Serial in on MOSI
Clock on SCK

*/

//false then the layerdriver will set LOW when they have to be off - true then the layerdriver will set HIGH when they have to be off
const boolean layerdriveroffstate = false;
const int framedelay = 2000;

//----------------------------------------------------------------------------------------------------------------------------------------------------------
// put here the code from the desinger


byte frames[3][8][8] = {{{B11111111,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B11111111,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B11111111,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B11111111,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B11111111,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B11111111,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B11111111,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B11111111,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000}
},
{{B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000}
},
{{B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000}
}
};
const int framecount=2;

//----------------------------------------------------



byte frame[8][8];
byte activeframe = 0;
byte lastlayer = 0;
unsigned long start = 0;

void setup() {
  
  if (softspiusage) {
    pinMode(datapin, OUTPUT);
    pinMode(clockpin, OUTPUT);
    
  }
  pinMode(latchpin, OUTPUT);
  for (int i = 0;i<8;i++) {
    pinMode(layerpins[i],OUTPUT);
  }
  
  
}

void loop() {
  
  for (int i =7;i>-1;i--) {
    
    //for (int j = 0;j<8;j++) {
      
        //SPI.transfer(frame[i][j]);
        //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // Info I know that this is bad programming, but I think that is faster than an for loop
        //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      SPI.transfer(frame[i][0]);
      SPI.transfer(frame[i][1]);
      SPI.transfer(frame[i][2]);
      SPI.transfer(frame[i][3]);
      SPI.transfer(frame[i][4]);
      SPI.transfer(frame[i][5]);
      SPI.transfer(frame[i][6]);
      SPI.transfer(frame[i][7]);
    //}
    digitalWrite(layerpins[lastlayer],LOW);
    // digitalWrite(layerpins[lastlayer],layerdriveroffstate);
    digitalWrite(latchpin,HIGH);
    //digitalWrite(layerpins[i],!(layerdriveroffstate));
    digitalWrite(layerpins[i],HIGH);
    lastlayer = i;
   delayMicroseconds(10);
   digitalWrite(latchpin,LOW);
   
  }
  
  if ((millis()-start) > framedelay) {
    start = millis();
    Serial.println(start);
    activeframe++;
    if (activeframe >framecount) {
      activeframe = 0;
    }
    for (int i = 0;i<8;i++) {
      for (int j = 0;j<8;j++) {
       frame[i][j] = frames[activeframe][i][j];
    }
    }
}
  
}
