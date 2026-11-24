#pragma once

#include "interfaces/ILed.hpp"

namespace cmfs::platform {

class TeensyLed final : public hal::ILed {
public:
  void initialize();
  void write(bool high) override;
};

} // namespace cmfs::platform
