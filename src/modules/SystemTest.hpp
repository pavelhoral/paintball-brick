#ifndef SYSTEMTEST_HPP
#define SYSTEMTEST_HPP

#include "GameModule.hpp"
#include "../context.hpp"
#include "../services/ChipRegistry.hpp"

/**
 * System test module.
 */
class SystemTest : public GameModule {
public:
  SystemTest(Context context);
  void setup();
  void loop();
private:
  Context context_;
  ChipRegistry registry_;
};

#endif
