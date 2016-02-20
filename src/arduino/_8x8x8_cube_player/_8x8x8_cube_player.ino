/* cube 8x8x8

*/
//pins
const byte layerpins[8] = {
  2,3,4,5,6,7,8,9};
const byte latchpin = 10;
// only needed if using soft shiftOut. 
// pins for hardware spi view datasheet
const byte datapin = 12;
const byte clockpin = 13;


// true then using shiftOut (software, slow) - false then using hardware SPI (shift with clockfrequenc, 40x faster)
// ---------------------- only Softspi function yet coming soon -----------------------------------
const boolean softspiusage = true;

//false then the layerdriver will set LOW when they have to be off - true then the layerdriver will set HIGH when they have to be off
const boolean layerdriveroffstate = false;
const int framedelay = 2000;

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





byte frame[8][8];
byte activeframe = 0;
byte lastlayer = 0;
unsigned long start = 0;

void setup() {
  Serial.begin(115200);
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
    
    for (int j = 0;j<8;j++) {
      //if (softspiusage) {
        shiftOut(datapin,clockpin,MSBFIRST,frame[i][j]);
        //Serial.println(i);
      //}
    }
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
