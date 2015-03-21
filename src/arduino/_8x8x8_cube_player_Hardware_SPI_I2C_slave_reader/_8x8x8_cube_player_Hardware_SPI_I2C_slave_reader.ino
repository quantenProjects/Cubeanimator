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
