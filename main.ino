#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define BUZZER_PIN 2
#define DATA_PLUS_PIN A1
#define DATA_MINUS_PIN A2
#define VCC_PIN A3


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); 

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(DATA_PLUS_PIN, INPUT);
  pinMode(DATA_MINUS_PIN, INPUT);
  pinMode(VCC_PIN, INPUT);

  Serial.begin(9600);


  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  
    Serial.println(F("Не удалось найти дисплей SSD1306"));
    while (true);
  }

  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(40, 10);
  display.print("MADE BY");
  tone(BUZZER_PIN, 1000, 200);
  display.setCursor(20, 20);
  display.print("SHORT CIRCUIT");
  display.display();
  delay(2500);  
  display.clearDisplay();
}

void loop() {
  int dataPlus = analogRead(DATA_PLUS_PIN);
  int dataMinus = analogRead(DATA_MINUS_PIN);
  int vcc = analogRead(VCC_PIN);

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

 
  display.setCursor(90, 5);
  display.print("USB");
  display.setCursor(83, 20);
  display.print("TESTER");

  display.display();
  delay(500);  
}
