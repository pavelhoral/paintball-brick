#ifndef CHIPQUEST_HPP
#define CHIPQUEST_HPP

#include "GameModule.hpp"
#include "../context.hpp"
#include "../services/ChipRegistry.hpp"

class ChipQuest : public GameModule {
public:
  ChipQuest(Context context) ;
  void setup();
  void loop();
  void changePhase(uint8_t phase);
  void handlePhase1();
  void handlePhase2();
  void handlePhase3();
private:
  Context context_;
  ChipRegistry registry_;
  uint32_t lastUid_ = 0;
  bool phaseChange_ = false;
  uint8_t activePhase_ = 0;
  uint8_t lastPhase_ = 0;
  uint8_t codeIndex_ = 0;
  uint8_t itemIndex_ = 0;
};
#endif
