/* cube 8x8x8

*/
//pins
const byte layerpins[8] = {
  1,2,3,4,5,6,7,8};
const byte latchpin = 10;
// only needed if using soft shiftOut. 
// pins for hardware spi view datasheet
const byte datapin = 12;
const byte clockpin = 11;


// true then using shiftOut (software, slow) - false then using hardware SPI (shift with clockfrequenc, 40x faster)
// ---------------------- only Softspi function yet coming soon -----------------------------------
const boolean softspiusage = true;

//false then the layerdriver will set LOW when they have to be off - true then the layerdriver will set HIGH when they have to be off
const boolean layerdriveroffstate = false;
const int framedelay = 200;



byte frame[8][8];
byte activelayer = 0;
byte lastlayer = 0;

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
  for (int i =0;i<8;i++) {
    
    for (int j = 0;j<8;j++) {
      if (softspiusage) {
        shiftOut(datapin,clockpin,MSBFIRST,frame[i][j]);
        
      }
    }
     digitalWrite(layerpins[lastlayer],layerdriveroffstate);
    digitalWrite(latchpin,HIGH);
    digitalWrite(layerpins[i],!(layerdriveroffstate));
    lastlayer = i;
   delayMicroseconds(100);
   digitalWrite(latchpin,LOW);
   
  }
  
}
