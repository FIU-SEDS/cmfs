#include "BlinkTask.hpp"

#include "interfaces/ILed.hpp"

#include "FreeRTOS.h"
#include "task.h"

namespace cmfs::app {

void BlinkTask(void* context) {
  auto* led = static_cast<hal::ILed*>(context);

  for (;;) {
    led->write(true);
    vTaskDelay(pdMS_TO_TICKS(200));

    led->write(false);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

} // namespace cmfs::app
