//
#include "DHT.h"
 
#define DHTPIN 12        // SDA 핀의 설정
#define DHTTYPE DHT22   // DHT22 (AM2302) 센서종류 설정
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "Nextion.h"

#include <Adafruit_NeoPixel.h>

#define touchpin 2
#define NEOPIXELPIN 6
#define NUM_LEDS 60
DHT dht(DHTPIN, DHTTYPE);

String data[12] ={""};
int dataInt[12]={0};
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, NEOPIXELPIN, NEO_GRB + NEO_KHZ800);
SoftwareSerial dataSerial(8,9);
//touchsensor
int power = LOW;

//NEOPIXEL
int r = 0;
int g = 0;
int b = 0;

void strip_color(int r, int g , int b) {
  for (int i = 0; i < 70; i++) {
    strip.setPixelColor(i, strip.Color(r, g, b));
  }
  strip.show();
}

SoftwareSerial DFPlayerSerial(10,11);
SoftwareSerial serial(0,1);

//mp3 초기설정
DFRobotDFPlayerMini myDFPlayer;
int volume = 15;
int EQnum =0;
boolean isPlaying = false;

//밝기 초기설정
int brightness = 50;
int SwitchValueFlag = 0;

//메인페이지 초기설정
int temp =14;
int hum = 35;

// 수면 분석 초기설정 
int deepSleepData = 34;
int shallowSleepData= 66;
int totalTime =4;
//int totalMinute =51;
// 메인 페이지 날씨, 온도, 습도 받기

NexButton Update = NexButton(1,4,"update");
NexNumber Temp = NexNumber(1,13,"temp");
NexNumber Hum = NexNumber(1,14,"hum");
NexNumber TotalHour = NexNumber(1,17,"th");
NexNumber TotalMinute = NexNumber(1,20,"tm");
NexNumber Deep = NexNumber(1,15,"deep");
NexNumber Shall = NexNumber(1,16,"shall");
NexNumber Hour = NexNumber(1,8,"hour");
NexNumber Minute = NexNumber(1,10,"minute");
NexNumber Weather = NexNumber(1,6,"weather");
NexNumber TempOut = NexNumber(1,7,"tempOut");

// 밝기설정 페이지
NexSlider SliderBar =NexSlider(2,1,"SliderBar");
NexDSButton Switch = NexDSButton(2,2,"Switch");
NexNumber SwitchValue = NexNumber(2,5,"SwitchValue");
NexNumber SliderValue = NexNumber(2,4,"SliderValue");

// 음악선택 페이지
NexButton b42 = NexButton(4,3,"b42");
NexButton b43 = NexButton(4,4,"b43");
NexButton b44 = NexButton(4,5,"b44");
NexButton b45 = NexButton(4,6,"b45");
NexButton b46 = NexButton(4,7,"b46");
NexButton b47 = NexButton(4,8,"b47");
NexDSButton bt40 = NexDSButton(4,9,"bt40");

//음량,음향 선택 페이지
NexButton b61 = NexButton(5,2,"b51");
NexButton b62 = NexButton(5,3,"b52");
NexButton b63 = NexButton(5,4,"b53");
NexButton b64 = NexButton(5,5,"b54");
NexNumber n60 = NexNumber(5,6,"n50"); // 음량
NexNumber n61 = NexNumber(5,8,"n51"); // EQ


NexTouch *nex_listen_list[] =
{ &SliderBar,&Switch, // 메인
  &Update,
  &b42,&b43,&b44,&b45,&b46,&b47,&bt40, // 밝기
  &b61,&b62,&b63,&b64, // 음량,음향
  NULL
  };

void Update_Callback(void *ptr){
//  temp =dht.readTemperature();
//  hum = dht.readHumidity();
//  Temp.setValue(temp);
  Hum.setValue(hum);
  TotalHour.setValue(dataInt[0]);
  TotalMinute.setValue(dataInt[1]);
  Shall.setValue(dataInt[2]);
  Deep.setValue(dataInt[3]);
  Hour.setValue(dataInt[5]);
  Minute.setValue(dataInt[6]);
  Weather.setValue(dataInt[7]);
  TempOut.setValue(dataInt[8]-272);
  }

void b61_Callback(void *ptr){
  volume++;
  n60.setValue(volume);
  myDFPlayer.volume(volume);
  Serial.print("volume :");
  Serial.println(volume);
  }
void b62_Callback(void *ptr){
  volume--;
  n60.setValue(volume);
  myDFPlayer.volume(volume);
  Serial.print("volume :");
  Serial.println(volume);
  }

void EQset(int EQnum){
  switch(EQnum){
    case 0 :
      myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
      break;
    case 1 :
      myDFPlayer.EQ(DFPLAYER_EQ_POP);
      break;
    case 2 :
      myDFPlayer.EQ(DFPLAYER_EQ_JAZZ);
      break;
    case 3 :
      myDFPlayer.EQ(DFPLAYER_EQ_CLASSIC);
      break;
    case 4 :
      myDFPlayer.EQ(DFPLAYER_EQ_BASS);
      break; 
     }
  }
void b63_Callback(void *ptr){
  EQnum++;
  n61.setValue(EQnum);
  EQset(EQnum);
  }
void b64_Callback(void *ptr){
  EQnum--;
  n61.setValue(EQnum);
  EQset(EQnum);
  } 

void song(int num){
   myDFPlayer.play(num); //Play the first song
   isPlaying = true;
   Serial.println(num);
  }
  
void Switch_Callback(void *ptr){
  uint32_t dual_state;
  SwitchValue.setValue(SwitchValueFlag);
  SwitchValue.getValue(&dual_state);
  SwitchValueFlag = dual_state;
  if (SwitchValueFlag==1&&power==HIGH){
    digitalWrite(13,HIGH);
    Serial.println("on");
    strip_color(r,g,b);
    }
  else{
    digitalWrite(13,LOW);
    Serial.println("off");
    strip_color(0,0,0);
      } 
  }
void SliderBar_Callback(void *ptr) {
  uint32_t number;
  SliderValue.setValue(brightness);
  SliderBar.getValue(&number);
  if(number<=100){
    brightness = number;
  }
  int Bright = map(brightness , 0 ,100 , 0,15);
//  strip_color(Bright , Bright
  r= Bright ;
  g= Bright ;
  b= Bright ;
  if (SwitchValueFlag==1&&power==HIGH){
    digitalWrite(13,HIGH);
    Serial.println("on");
    strip_color(r,g,b);
    }
  else{
    digitalWrite(13,LOW);
    Serial.println("off");
    strip_color(0,0,0);
      } 
  Serial.print("slider : ");
  Serial.println(number);
}
void  b42_Callback(void *ptr){
  song(1);
  }
void  b43_Callback(void *ptr){
  song(2);
  }
void  b44_Callback(void *ptr){
  song(3);
  }
void  b45_Callback(void *ptr){
  song(4);
  }
void  b46_Callback(void *ptr){
  song(5);
  }
void  b47_Callback(void *ptr){
  song(6);
  }
void bt40_Callback(void *ptr){
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

void Change(){ //touchsensor interruptpin 설정
  if(power == HIGH)
    {power = LOW;
    Serial.println(power);
    }
  else
   { power = HIGH;
    Serial.println(power);
   }
}

void setup() {
  dht.begin();
  DFPlayerSerial.begin(9600);
  strip.begin();
  strip.setPixelColor(1, strip.Color(0, 0, 0)); // 네오픽셀
//  strip.show();    
  attachInterrupt(digitalPinToInterrupt(touchpin),Change,FALLING);
  Serial.begin(9600);
//  dataSerial.begin(9600);
  delay(1000);
  nexInit();
  pinMode(13,OUTPUT);

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
  
  SliderBar.attachPop(SliderBar_Callback,&SliderBar);
  Switch.attachPop(Switch_Callback,&Switch);
  Update.attachPop(Update_Callback,&Update);
  b42.attachPop(b42_Callback,&b42);
  b43.attachPop(b43_Callback,&b43);
  b44.attachPop(b44_Callback,&b44);
  b45.attachPop(b45_Callback,&b45);
  b46.attachPop(b46_Callback,&b46);
  b47.attachPop(b47_Callback,&b47);
  bt40.attachPop(bt40_Callback,&bt40);
  b61.attachPop(b61_Callback,&b61);
  b62.attachPop(b62_Callback,&b62);
  b63.attachPop(b63_Callback,&b63);
  b64.attachPop(b64_Callback,&b64);
  dataSerial.begin(9600);
}

void loop() {
if(dataSerial.available()){
     data[0] = dataSerial.readStringUntil('\n');
     data[1] = dataSerial.readStringUntil('\n');
     data[2] = dataSerial.readStringUntil('\n');
     data[3] = dataSerial.readStringUntil('\n');
     data[4] = dataSerial.readStringUntil('\n');
     data[5] = dataSerial.readStringUntil('\n');
     data[6] = dataSerial.readStringUntil('\n');
     data[7] = dataSerial.readStringUntil('\n');
     data[8] = dataSerial.readStringUntil('\n');
     data[9] = dataSerial.readStringUntil('\n');
     data[10] = dataSerial.readStringUntil('\n');
     data[11] = dataSerial.readStringUntil('\n');
     data[12] = dataSerial.readStringUntil('\n');
     for(int i=0;i<12;i++){
      dataInt[i] = data[i].toInt();
      Serial.print(i);
      Serial.print(" : ");
      Serial.println(dataInt[i]);
      }

   }
  nexLoop(nex_listen_list);
}
