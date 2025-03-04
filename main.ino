#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define BUZZER_PIN 2
#define DATA_PLUS_PIN A1
#define DATA_MINUS_PIN A2
#define VCC_PIN A3
#define BATTERY_PIN A3  

// Настройки дисплея
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); 

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(DATA_PLUS_PIN, INPUT);
  pinMode(DATA_MINUS_PIN, INPUT);
  pinMode(VCC_PIN, INPUT);
  pinMode(BATTERY_PIN, INPUT);

  Serial.begin(9600);

  // Инициализация дисплея
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  
    Serial.println(F("Не удалось найти дисплей SSD1306"));
    while (true);
  }

  // Приветственный экран
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(40, 10);
  display.print("MADE BY");
  tone(BUZZER_PIN, 1000, 200);
  display.setCursor(20, 20);
  display.print("SHORT CIRCUIT");
  display.display();
  delay(2000);  

  display.clearDisplay();
}

void drawBatteryIndicator(float voltage) {
  int level = map(voltage * 100, 300, 420, 0, 5); 
  level = constrain(level, 0, 5);  

  int x = 110, y = 2, w = 15, h = 7;  
  display.drawRect(x, y, w, h, SSD1306_WHITE); 
  display.fillRect(x + w, y + 2, 2, h - 4, SSD1306_WHITE); 

  for (int i = 0; i < level; i++) {
    display.fillRect(x + 2 + (i * 3), y + 2, 2, h - 4, SSD1306_WHITE); 
  }
}

void loop() {
  int dataPlus = analogRead(DATA_PLUS_PIN);
  int dataMinus = analogRead(DATA_MINUS_PIN);
  int vcc = analogRead(VCC_PIN);
  
  float batteryVoltage = analogRead(BATTERY_PIN) * (5.0 / 1023.0);


  display.clearDisplay();

  // Вывод данных
  display.setCursor(0, 0);
  display.print("DATA+ ");
  if (dataPlus < 50) {  
    display.print("X");
    tone(BUZZER_PIN, 1000, 200);
  } else {
    display.print(dataPlus);
  }

  display.setCursor(0, 10);
  display.print("DATA- ");
  if (dataMinus < 50) {
    display.print("X");
    tone(BUZZER_PIN, 1000, 200);
  } else {
    display.print(dataMinus);
  }

  display.setCursor(0, 20);
  display.print("VCC ");
  if (vcc < 50) {
    display.print("X");
    tone(BUZZER_PIN, 1000, 200);
  } else {
    display.print(vcc);
  }

  
  display.setCursor(86, 3);
  display.print("USB");
   display.setCursor(80, 20);
  display.print("TESTER");

  
  drawBatteryIndicator(batteryVoltage);

  display.display();
  delay(500);
}

