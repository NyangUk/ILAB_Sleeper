#include <Adafruit_NeoPixel.h>



//define NeoPixel Pin and Number of LEDs

#define PIN 5

#define NUM_LEDS 23

//create a NeoPixel strip

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
void setup() {
  strip.begin();
  strip.show();
}

void loop() {

  // set pixel to red, delay(1000)

  strip.setPixelColor(0, 255, 0, 0); // (Pin,R,G,B)
  strip.show(); // setPixelColor 로 설정한 색 출력

  delay(1000);
  
  strip.setPixelColor(0, 0, 0, 0);
  strip.show();

  delay(1000);

}
