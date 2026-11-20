#include "arduino_freertos.h"

#include "app/BlinkTask.hpp"
#include "platform/teensy41/TeensyLed.hpp"

namespace {

cmfs::platform::TeensyLed led;

} // namespace

void setup() {
  led.initialize();

  BaseType_t result = xTaskCreate(cmfs::app::BlinkTask, "LED", 256, &led, 2, nullptr);

  configASSERT(result == pdPASS);

  vTaskStartScheduler();

  for (;;) {
  }
}

void loop() {
}
