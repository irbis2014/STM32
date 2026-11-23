#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDR 0x3C  // Если экран не загорится, замените на 0x3D
#define BMP_ADDR  0x76  // Стандартный адрес китайских плат BMP280 (иногда 0x77)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_BMP280 bmp(&Wire);

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

  if (!bmp.begin(BMP_ADDR)) {
    display.setCursor(0, 0);
    display.println("BMP280 not found!");
    display.println("Check 0x76 / 0x77");
    display.display();
    while (true);
  }

  // Настройка фильтрации и точности измерений (рекомендуемая для метеостанции)
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                  Adafruit_BMP280::SAMPLING_X2,     // Температура
                  Adafruit_BMP280::SAMPLING_X16,    // Давление
                  Adafruit_BMP280::FILTER_X16,      // Фильтр помех
                  Adafruit_BMP280::STANDBY_MS_500); // Пауза между замерами
}

void loop() {
  float temp = bmp.readTemperature();
  float presPa = bmp.readPressure();
  float presMmHg = presPa / 133.322F; // Перевод из Паскалей в мм рт. ст.

  display.clearDisplay();
  
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("STM32 + BMP280");
  display.drawLine(0, 10, 128, 10, SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(0, 18);
  display.print(temp, 1);
  display.println(" C");

  display.setCursor(0, 42);
  display.print(presMmHg, 1);
  display.println(" mm");

  display.display();
  delay(2000);
}
