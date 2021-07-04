#ifndef CONTEXT_H
#define CONTEXT_H

#include "interface/MainDisplay.hpp"
#include "interface/ManualInput.hpp"
#include "interface/AudioOutput.hpp"
#include "interface/ChipManager.hpp"

struct CubeConfig {
  uint32_t masterCard = 3002390521;
  uint8_t moduleIndex = 0;
};

struct Context {
  ManualInput input;
  MainDisplay display;
  ChipManager rfid;
  AudioOutput audio;
  CubeConfig config;
};

#endif
