#ifndef AUDIOOUTPUT_HPP
#define AUDIOOUTPUT_HPP

#include <Arduino.h>

class AudioOutput {
public:
  AudioOutput();

  /**
   * Play blocking buzzer sound.
   */
  void buzz(int length, uint8_t count = 1, int pause = 50);

  /**
   * Reset any internal and physical state.
   */
  void reset();

};

#endif
