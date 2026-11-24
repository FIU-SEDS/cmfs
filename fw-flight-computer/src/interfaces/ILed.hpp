#pragma once

namespace cmfs::hal {

class ILed {
public:
  virtual ~ILed() = default;

  virtual void write(bool high) = 0;
};

} // namespace cmfs::hal
