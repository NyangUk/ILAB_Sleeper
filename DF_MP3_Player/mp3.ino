//http://www.manelsoft.com/projects/arduino_mp3_player.aspx

#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
SoftwareSerial DFPlayerSerial(10,11);
DFRobotDFPlayerMini myDFPlayer;
int volume = 20;
boolean isPlaying = false;
void song(int num){
   myDFPlayer.play(num); //Play the first song
   isPlaying = true;
   Serial.println(num);
  }
  
void setup() {
  DFPlayerSerial.begin(9600);
  Serial.begin(9600);
  delay(1000);

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(DFPlayerSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card or USB drive!"));
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.setTimeOut(500);
  myDFPlayer.volume(volume); //Set volume value (0~30).
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  

}

void loop() {
  if (Serial.available()){
    char v = Serial.read();
   if (v =='1'){
    song(1);
    }
   if (v =='2'){
     song(2);
    }
   if (v =='3'){
     song(3);
    }
   if (v =='4'){
     song(4);
    }
   if (v =='5'){
     song(5);
    }
   if(v =='u'){
//    myDFPlayer.volumeUp();
    volume++;
    myDFPlayer.volume(volume);
    Serial.println(volume);
    }
   if(v == 'd'){
    volume--;
    myDFPlayer.volume(volume);
    Serial.println(volume);
    }
   if (v =='p'){
    if (isPlaying) {
      myDFPlayer.pause();
      isPlaying = false;
      Serial.println("Paused..");
    } 
    else {
      isPlaying = true;
      myDFPlayer.start();
      Serial.println("Playing..");
        }
    }
  }
}
