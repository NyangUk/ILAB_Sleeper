# ILAB_Sleeper
제어
1. nodeMcu 와 arduino Uno 간의 통신
2. nodeMcu 와 서버간 통신
3. lcd 제어 (NextionEditor 사용)  
4. 온습도 센서, 터치센서(인터럽트),DF MP3 Player,스피커,NeoPixel 제어 

## nodeMcu 와 arduino Uno 간의 통신
주의사항
1. 아두이노 우노는 모든핀이 SofewareSerial이 가능하지만 아두이노 메가의 경우 SofewareSerial 핀이 정해져있음
2. nodeMcu 의 RX/TX핀과 아두이노 우노에서 SofewareSerial(mySerial) 으로 선언된 핀간의 통신은 
   nodeMcu의 Serial.print(),Serial.available()...와  아두이노 우노에서 mySeirla.print(),mySerial.available()... 등의 코드를 사용해야만 한다.
3. 서로 통신하고자하는 보드레이트를 맞춰줘야한다.
  
