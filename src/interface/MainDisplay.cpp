#include "MainDisplay.hpp"

const uint8_t CUSTOM_COUNT = 5;

uint8_t CUSTOM_CHARS[CUSTOM_COUNT][7] = {
  { 0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x00, 0x04 }, // BELL
  { 0x02, 0x03, 0x02, 0x0E, 0x1E, 0x0C, 0x00 }, // NOTE
  { 0x00, 0x0E, 0x15, 0x17, 0x11, 0x0E, 0x00 }, // CLOCK
  { 0x00, 0x0A, 0x1F, 0x1F, 0x0E, 0x04, 0x00 }, // HEART 
  { 0x00, 0x0C, 0x1D, 0x0F, 0x0F, 0x06, 0x00 }  // DUCK
};

MainDisplay::MainDisplay() : LiquidCrystal_I2C(0x27, 20, 4) {
}

void MainDisplay::setup() {
  init();
  backlight();
  for (uint8_t i = 0; i < CUSTOM_COUNT; i++) {
    createChar(i, CUSTOM_CHARS[i]);
  }
}

void MainDisplay::reset() {
  clear();
}
