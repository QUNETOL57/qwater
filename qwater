#include <VirtualButton.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define PIN_BTN_SET 14 //(D5)
#define PIN_BTN_RESET 12 //(D6)

LiquidCrystal_I2C lcd(0x27,16,2);

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

MyBtn btnSet(PIN_BTN_SET);
MyBtn btnReset(PIN_BTN_RESET);

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Hello, world!");
}

void loop() {
  btnSet.tick();
  btnReset.tick();

  if (btnSet.click()) Serial.println("click set");
  if (btnReset.click()) Serial.println("click reset");
}
