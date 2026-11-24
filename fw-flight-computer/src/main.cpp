#include "arduino_freertos.h"

#include "app/BlinkTask.hpp"
#include "platform/teensy/TeensyLed.hpp"

namespace {

cmfs::platform::TeensyLed led;

} // namespace

void setup() {
  led.initialize();

  cmfs::hal::ILed* LedOutput = &led;
  BaseType_t result = xTaskCreate(cmfs::app::BlinkTask, "LED", 256, LedOutput, 2, nullptr);

  configASSERT(result == pdPASS);

  vTaskStartScheduler();

  for (;;) {
  }
}

void loop() {
}
