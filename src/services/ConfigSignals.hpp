#ifndef CONFIGSIGNALS_HPP
#define CONFIGSIGNALS_HPP

#include "../context.hpp"

class ConfigSignals {
public:
  /**
   * Begin configuration.
   */
  static void enter(Context &context) {
    context.audio.buzz(100);
  };

  /**
   * Confirm configuration.
   */ 
  static void confirm(Context &context) {
    context.audio.buzz(200);
  }

  /**
   * Signal configuration error.
   */
  static void error(Context &context) {
    context.audio.buzz(100, 3, 50);
  }

  /**
   * Cancel configuration.
   */
  static void cancel(Context &context) {
    context.audio.buzz(100, 2, 50);
  }

  /**
   * Persist configuration.
   */
  static void persist(Context &context) {
    for (int i = 0; i < 5; i++) {
      context.audio.buzz(20);
      delay(50);
    }
  }
};

#endif