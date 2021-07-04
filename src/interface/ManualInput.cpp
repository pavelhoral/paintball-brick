#include "ManualInput.hpp"

char MATRIX_KEYS[MATRIX_ROWS][MATRIX_COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte MATRIX_ROW_PINS[MATRIX_ROWS] = { PIN5, PIN7, PIN6, PIN3 };
byte MATRIX_COL_PINS[MATRIX_COLS] = { PIN4, 9, PIN2 };

ManualInput::ManualInput() : 
    Keypad(
      ((char*) MATRIX_KEYS), 
      MATRIX_ROW_PINS, MATRIX_COL_PINS,
      MATRIX_ROWS, MATRIX_COLS) {
}

void ManualInput::reset() {
}

void ManualInput::debug() {
  String msg = "";
  if (getKeys()) {
    for (int i=0; i<LIST_MAX; i++) {
      if (this->key[i].stateChanged ) {
        switch (this->key[i].kstate) {
          case PRESSED:
          msg = " PRESSED.";
        break;
          case HOLD:
          msg = " HOLD.";
        break;
          case RELEASED:
          msg = " RELEASED.";
        break;
          case IDLE:
          msg = " IDLE.";
        }
        Serial.print("Key ");
        Serial.print(this->key[i].kchar);
        Serial.println(msg);
      }
    }
  }
}
