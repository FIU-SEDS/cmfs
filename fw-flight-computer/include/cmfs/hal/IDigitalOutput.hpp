#pragma once

namespace cmfs::hal {

class IDigitalOutput {
public:
  virtual ~IDigitalOutput() = default;

  virtual void write(bool high) = 0;
};

} // namespace cmfs::hal
