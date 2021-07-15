#include "CardCounter.hpp"

CardCounter::CardCounter(Context context) : context_(context) {
}

void CardCounter::setup() {
  registry_.clear();
  context_.display.clear();
}

void CardCounter::loop() {
  uint32_t chipUid = context_.rfid.readChip();
  if (chipUid == 0) {
    return;
  }
  if (chipUid == context_.config.masterCard) {
    registry_.clear();
    context_.audio.buzz(50, 5, 25);
    context_.display.clear();
    return;
  }
  registry_.put((byte *) &chipUid, 0);
  int cardIdx = registry_.indexOf((byte *) &chipUid);
  context_.audio.buzz(50);
  context_.display.clear();
  context_.display.setCursor(0, 0);
  context_.display.print(cardIdx);
  context_.display.setCursor(0, 1);
  context_.display.print(chipUid, 16);
  if (cardIdx >= 5) {
    context_.audio.buzz(50, 6, 50);
  }
}
