#include <VirtualButton.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Коментарии - пины на плате NodeMCU
#define BTN_SET_PIN     14  //(D5)
#define BTN_RESET_PIN   12  //(D6)
#define DHT_PIN         3   //(RX)

struct MyBtn : public VButton {
  MyBtn(uint8_t pin) {
    _pin = pin;
    pinMode(_pin, INPUT_PULLUP);
  }
  bool tick() {
    return poll(!digitalRead(_pin));
  }
  uint8_t _pin;
};

LiquidCrystal_I2C lcd(0x27,16,2); // Инициализация Дисплея
DHT   dht(DHT_PIN, DHT22); // Инициализация DHT22
MyBtn btnSet(BTN_SET_PIN); // Инициализация кнопки set
MyBtn btnReset(BTN_RESET_PIN); // Инициализация кнопки reset

uint32_t previousMillis = 0;
const uint32_t interval = 5000;

float humGlobalValue = 0;
float tempGlobalValue = 0;

int mode = 1;

void screen1(float tempValue, float humValue) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temp: ");
    lcd.setCursor(6,0);         
    lcd.print(tempValue); 
    lcd.setCursor(0,1); 
    lcd.print("Hum : ");
    lcd.setCursor(6,1);
    lcd.print(humValue);
}

void screen2(float tempValue, float humValue) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Hum : ");
    lcd.setCursor(6,0);         
    lcd.print(humValue); 
    lcd.setCursor(0,1); 
    lcd.print("Temp: ");
    lcd.setCursor(6,1);
    lcd.print(tempValue);
}

void setup() {
  Serial.begin(9600);

  lcd.init();
  dht.begin();


  lcd.backlight();
}

void loop() {
  uint32_t currentMillis = millis();

  btnSet.tick();
  btnReset.tick();

  if (btnSet.click()) {
    Serial.println("click set");
    mode = 1;
    screen1(tempGlobalValue, humGlobalValue);
  }
  if (btnReset.click()) {
    Serial.println("click reset");
    mode = 2;
    screen2(tempGlobalValue, humGlobalValue);
  }

  

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
  
    tempGlobalValue = dht.readTemperature();
    humGlobalValue = dht.readHumidity();

    switch(mode) {
      case 1: screen1(tempGlobalValue, humGlobalValue); break;
      case 2: screen2(tempGlobalValue, humGlobalValue); break;
    }
  }
}
