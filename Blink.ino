#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h> // Для BMP280 замените на <Adafruit_BMP280.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C
#define BMP_ADDR  0x76 // У китайских модулей обычно 0x76, реже 0x77

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_BMP280 bme; // Для BMP280: Adafruit_BMP280 bmp;

void setup() {
  Wire.setSDA(PB7);
  Wire.setSCL(PB6);
  Wire.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  if (!bme.begin(BME_ADDR, &Wire)) {
    display.setCursor(0, 0);
    display.println("BME280 error!");
    display.display();
    while (true);
  }
}

void loop() {
  float temp = bme.readTemperature();
  float pres = bme.readPressure() / 133.322F; // Перевод из Па в мм рт. ст.
  float hum  = bme.readHumidity();            // Для BMP280 эту строку убрать

  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("Meteostation:");
  
  display.setCursor(0, 16);
  display.print("Temp: ");
  display.print(temp, 1);
  display.println(" C");

  display.setCursor(0, 32);
  display.print("Pres: ");
  display.print(pres, 1);
  display.println(" mmHg");

  display.setCursor(0, 48);
  display.print("Hum:  ");
  display.print(hum, 1);
  display.println(" %");

  display.display();
  delay(2000);
}
