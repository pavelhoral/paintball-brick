#ifndef CARDCOUNTER_HPP
#define CARDCOUNTER_HPP

#include "GameModule.hpp"
#include "../context.hpp"
#include "../services/ChipRegistry.hpp"

class CardCounter : public GameModule {
public:
  CardCounter(Context context);
  void setup();
  void loop();
private:
  Context context_;
  ChipRegistry registry_;
};

#endif
