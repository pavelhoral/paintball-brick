#include "SystemTest.hpp"

SystemTest::SystemTest(Context context) : context_(context) {
}

void SystemTest::setup() {
  registry_.clear();
  context_.display.clear();
}

void SystemTest::loop() {
  context_.input.debug();
  uint32_t chipUid = context_.rfid.readChip();
  if (chipUid == 0) {
    return;
  }
  uint8_t value = 0;
  registry_.put((byte *) &chipUid, &value);
  int cardIdx = registry_.indexOf((byte *) &chipUid);
  context_.audio.buzz(50);
  context_.display.clear();
  context_.display.setCursor(0, 0);
  context_.display.print(cardIdx);
  context_.display.setCursor(0, 1);
  context_.display.print(chipUid, 16);
}
