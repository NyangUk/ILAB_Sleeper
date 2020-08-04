#include <DHT.h>        

#define DHTPIN    8     
#define DHTTYPE   DHT22   

DHT dht(DHTPIN, DHTTYPE); 

void setup() {
  Serial.begin(9600);   
  dht.begin();          
}

void loop() {

  float temperature = dht.readTemperature();  
  float humidity = dht.readHumidity();        

  Serial.print("Temperature: ");
  Serial.print(temperature);

  Serial.print(", Humidity: ");
  Serial.println(humidity);

  delay(1000);
}
