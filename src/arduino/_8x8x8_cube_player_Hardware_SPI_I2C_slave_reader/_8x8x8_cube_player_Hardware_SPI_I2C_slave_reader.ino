#include <Wire.h>
#include <avr/pgmspace.h>
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


PROGMEM prog_uchar frames[1][8][8] = {{{B00000000,B00000000,B11111100,B00000010,B00011100,B00000000,B00000000,B00000000},
{B11100000,B11100000,B10011000,B10000000,B00000100,B00000100,B00000000,B00000000},
{B00001000,B01011000,B11111000,B11001000,B00001000,B00001000,B00001000,B00000000},
{B11100000,B01100100,B01001000,B01110000,B00000000,B00000000,B00000000,B00000000},
{B00000000,B00010000,B00010000,B11010000,B01111000,B10010000,B11100000,B01000000},
{B00000000,B00100000,B00110000,B00110110,B01010100,B11001100,B11111000,B00001100},
{B00101100,B00110100,B11100000,B00100100,B01000100,B00000100,B00000000,B00000000},
{B00000100,B00001100,B00001100,B11101100,B10011100,B10110000,B01110000,B00110000}
}
};
const int framecount=0;


//----------------------------------------------------

boolean seconddata = false;

byte frame[8][8];
byte activeframe = 0;
byte lastlayer = 0;
unsigned long start = 0;
int inverti = 0;
void setup() {
  Wire.begin(44); 
  Wire.onReceive(receiveEvent); 
  SPI.begin();
  pinMode(latchpin, OUTPUT);
  for (int i = 0;i<8;i++) {
    pinMode(layerpins[i],OUTPUT);
  }
  for (int i = 0;i<8;i++) {
      for (int j = 0;j<8;j++) {
       frame[i][j] = frames[0][i][j];
    }
    }
  
}

void loop() {
  
  for (int i =0;i<8;i++) {
    
    //for (int j = 0;j<8;j++) {
      
        //SPI.transfer(frame[i][j]);
        //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // Info I know that this is bad programming, but I think that is faster than a for loop
        //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        inverti=((i*-1)+7);
      /*SPI.transfer(frame[i][0]);
      SPI.transfer(frame[i][1]);
      SPI.transfer(frame[i][2]);
      SPI.transfer(frame[i][3]);
      SPI.transfer(frame[i][4]);
      SPI.transfer(frame[i][5]);
      SPI.transfer(frame[i][6]);
      SPI.transfer(frame[i][7]);*/
      SPI.transfer(frame[inverti][0]);
      SPI.transfer(frame[inverti][1]);
      SPI.transfer(frame[inverti][2]);
      SPI.transfer(frame[inverti][3]);
      SPI.transfer(frame[inverti][4]);
      SPI.transfer(frame[inverti][5]);
      SPI.transfer(frame[inverti][6]);
      SPI.transfer(frame[inverti][7]);
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
    
}
  
}

void receiveEvent(int howMany)
{ 
  //here may be a comando to reset secondval to false if any i2c packet is lost an the cube display chaos
  
  if (howMany == 32) {
    int startval = 0;
    if ( ! seconddata) { //first data
      startval = 0;
    } else { //second data
      startval = 4;
    }
    for (int i = startval;i<(startval +4);i++) {
      for (int j = 0;j<8;j++) {
        frame[i][j] = Wire.read();
      }
    }
    
    seconddata = ! seconddata;
  }
}
