#include "ChipQuest.hpp"

#define CHIP_COUNT 8

#define PHASE_SETUP 1
#define PHASE_MORSE 2
#define PHASE_ITEMS 3
#define PHASE_END 4

#define MORSE_DOT 50
#define MORSE_DASH 200
#define MORSE_SPACE 500
#define MORSE_SEPARATOR 100

const uint8_t SECRET_CODE[] = { 2, 7, 3, 5 };

const String ITEMS[] = { "FISKARS", "PREPRAVKA", "JAR" };

ChipQuest::ChipQuest(Context context) : context_(context) {
}

void ChipQuest::setup() {
  changePhase(PHASE_SETUP);
}

void ChipQuest::loop() {
  if (lastPhase_ != activePhase_) {
    phaseChange_ = true;
    lastPhase_ = activePhase_;
  }
  switch (activePhase_) {
  case PHASE_SETUP:
    handlePhase1();
    break;
  case PHASE_MORSE:
    handlePhase2();
    break;
  case PHASE_ITEMS:
    handlePhase3();
    break;
  }
  phaseChange_ = false;
}

void ChipQuest::changePhase(uint8_t phase) {
  context_.display.clear();
  context_.display.backlight();
  activePhase_ = phase;
}

void ChipQuest::handlePhase1() {
  if (phaseChange_) {
    registry_.clear();
  }
  uint32_t chipUid = context_.rfid.readChip();
  if (chipUid == 0) {
    return;
  }
  if (chipUid <= lastUid_) {
    registry_.clear();
    context_.display.clear();
    context_.display.print("! ERROR  ERROR !");
    context_.display.setCursor(0, 1);
    if (chipUid == lastUid_) {
      context_.display.print("    a = b    ");
    } else {
      context_.display.print("    a > b    ");
    }
    context_.audio.buzz(50, 5);
    lastUid_ = 0;
    return;
  }
  lastUid_ = chipUid;
  uint8_t value = 0;
  registry_.put((byte *) &chipUid, &value);
  int cardIdx = registry_.indexOf((byte *) &chipUid);
  context_.audio.buzz(50);
  context_.display.clear();
  context_.display.print(cardIdx + 1);
  if (cardIdx + 1 == CHIP_COUNT) {
    context_.audio.buzz(100, 3, 100);
    changePhase(PHASE_MORSE);
  }
}

void ChipQuest::handlePhase2() {
  if (phaseChange_) {
    codeIndex_ = 0;
  }
  const String code = "-../...-/.-//..././-../--//-/.-./..//.--././-//";
  uint8_t position = 0;
  unsigned long wait = 0;
  while (true) {
    switch (code[position]) {
    case '.':
      context_.display.backlight();
      wait = millis() + 150;
      break;
    case '-':
      context_.display.backlight();
      wait = millis() + 500;
      break;
    case '/':
      wait = millis() + 1000;
      break;
    }
    if (++position > code.length()) {
      position = 0;
      context_.audio.buzz(50, 2, 50);
    }
    while (millis() < wait) {
      uint32_t chipUid = context_.rfid.readChip();
      if (chipUid == 0) {
        continue;
      }
      context_.audio.buzz(50);
      uint8_t chipNumber = registry_.indexOf((byte*) &chipUid) + 1;
      if (SECRET_CODE[codeIndex_] == chipNumber) {
        codeIndex_++;
      } else if (SECRET_CODE[0] == chipNumber) {
        codeIndex_ = 1;
      } else {
        codeIndex_ = 0;
      }
      if (codeIndex_ >= 4) {
        context_.audio.buzz(100, 3, 100);
        changePhase(PHASE_ITEMS);
        return;
      }
      context_.display.setCursor(0, 0);
      context_.display.print(chipNumber);
      context_.display.backlight();
      delay(500);
    }
    context_.display.noBacklight();
    delay(350);
  }
}

void ChipQuest::handlePhase3() {
  if (phaseChange_) {
    itemIndex_ = 0;
    context_.display.print(ITEMS[0]);
  }
  uint32_t chipUid = context_.rfid.readChip();
  if (chipUid == 0 || registry_.indexOf((byte*) &chipUid) > -1) {
    return;
  }
  if (chipUid / 1000000 == 830) {
    itemIndex_++;
    context_.audio.buzz(100);
  }
  uint8_t value = 0;
  registry_.put((byte*) &chipUid, &value);
  if (itemIndex_ >= 3) {
    context_.audio.buzz(100, 5, 100);
    changePhase(PHASE_END);
    context_.display.print("WINNER WINNER ");
    context_.display.setCursor(0, 1);
    context_.display.print("  CHICKEN DINNER");
  } else {
    context_.display.clear();
    context_.display.print(ITEMS[itemIndex_]);
  }
}
