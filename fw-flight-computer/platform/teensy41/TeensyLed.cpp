#include "TeensyLed.hpp"
#include <Arduino.h>

namespace cmfs::platform {

namespace {
constexpr uint8_t kLedPin = 13;
}

void TeensyLed::initialize() {
  pinMode(kLedPin, OUTPUT);
}

void TeensyLed::write(bool high) {
  digitalWrite(kLedPin, high ? HIGH : LOW);
}

} // namespace cmfs::platform
