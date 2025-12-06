#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define OLED_DC 9
#define OLED_CS 10
#define OLED_RESET 8

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, OLED_DC, OLED_RESET, OLED_CS);

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup(){
  Serial.begin(115200);

  dht.begin();

  if(!display.begin(SSD1306_SWITCHCAPVCC)){
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  delay(2000);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
}

void loop(){
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if(isnan(t)||isnan(h)){
    Serial.println(F("Failed to read from DHT sensor!"));
    delay(1000);
    return;
  }

  Serial.print(F("Temp: "));
  Serial.print(t);
  Serial.print(F(" °C Humidity: "));
  Serial.print(h);
  Serial.println(F(" %"));

  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(0,0);
  display.print(F("Temperature: "));

  display.setTextSize(2);
  display.setCursor(0,10);
  display.print(t,1);
  display.print(F(" C"));

  display.setTextSize(1);
  display.setCursor(0,24);
  display.print(F("Humidity: "));
  display.print(h,0);
  display.print(F(" %"));

  display.display();

  delay(1000);
}



