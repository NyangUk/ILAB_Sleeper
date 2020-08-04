#include "SoftwareSerial.h"
SoftwareSerial dataSerial1(8,9);
void setup() {
 dataSerial1.begin(9600);
 Serial.begin(9600);
 Serial.println("start");
  
}

void loop() {
//  Serial.println(dataSerial.available())
if(dataSerial1.available()){
     String data = dataSerial1.readStringUntil('\n');
     int dataInt = data.toInt();
     Serial.println(dataInt);
   }
}
