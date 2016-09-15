#include <FastLED.h>
#include <DHT.h>

#define DHTPIN 8
#define LEDPIN 9
#define NUM_LEDS 2
#define DHTTYPE DHT11
uint8_t brightness = 255;
uint8_t hue = 0;
DHT dht(DHTPIN, DHTTYPE);
CRGB lds[NUM_LEDS];

void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  dht.begin();
  FastLED.addLeds<WS2812B, LEDPIN, GRB>(lds, NUM_LEDS);
}

void loop() {

  // Wait a second between measurements.
  delay(250);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Read temperature as Celsius (the default)
  uint8_t t = dht.readTemperature();

  if (t > 32) {
    hue = 0;
  }
  if (t < 32 && t > 10) {
    hue = huecalc(t);
  }
  if (t < 10) {
    hue = 160;
  }

  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    lds[i] = CHSV(hue, 255, brightness);
  }
  FastLED.show();

  // Check if any reads failed and exit early (to try again).
  if (isnan(t) ) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print("Hue: ");
  Serial.print(hue);
  Serial.println();

}

uint8_t huecalc(uint8_t temperature) {
  return
    ((uint8_t)(-7.2727 * temperature) + (232.73));
}

