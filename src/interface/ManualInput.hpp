#ifndef MANUALINPUT_HPP
#define MANUALINPUT_HPP

#include <Arduino.h>
#include <Keypad.h>

const byte MATRIX_ROWS = 4;
const byte MATRIX_COLS = 3;

class ManualInput : public Keypad {
public:
  ManualInput();

  void reset();

  void debug();

};

#endif
