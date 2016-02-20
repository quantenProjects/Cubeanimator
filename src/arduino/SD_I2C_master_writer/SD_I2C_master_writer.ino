#include <SD.h>
#include <Wire.h>

File myFile;

int delayms = 300;

void setup() {
  Wire.begin();
  delay(5000);
  pinMode(10, OUTPUT); 
  pinMode(9, OUTPUT); //9 = cs pin
  if (!SD.begin(9)) { // 9 = cs pin
    while (true) {;}
  }
  myFile = SD.open("1.cab", FILE_WRITE); //file with the ani data. cab = cuba animator binary ;) because of the 8.3 file names not longer file extension are allowed
 if ((myFile.size() %64) != 0) {
   while (true) {;} //because than the file bad and have not the rigth length
 }
}

void loop() {
  
  Wire.beginTransmission(44);
  for (int i = 0;i<32;i++) {
    Wire.write(myFile.read());
  }
  delay(10); //delay 10 ms that the slave can compute the i2c input and dont overfill the buffer
  for (int i = 0;i<32;i++) {
    Wire.write(myFile.read());
  }
  
//  Wire.write(132); //daten ist ein array mit den daten
  int resultint = Wire.endTransmission();
  if (resultint != 0) {
    //rumheulen das es nicht geht zB mit LED
  }
  if (myFile.available() == 0) {
    myFile.seek(0);
  }
 
}

