#pragma once

#include "cmfs/hal/IDigitalOutput.hpp"

namespace cmfs::platform {

class TeensyLed final : public hal::IDigitalOutput {
public:
  void initialize();
  void write(bool high) override;
};

} // namespace cmfs::platform
