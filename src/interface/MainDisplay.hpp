#ifndef MAINDISPLAY_HPP
#define MAINDISPLAY_HPP

#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

const uint8_t BUZZER_PIN = PIN2;

class MainDisplay : public LiquidCrystal_I2C {
public:
  MainDisplay();

  void setup();

  void reset();

};

#endif
