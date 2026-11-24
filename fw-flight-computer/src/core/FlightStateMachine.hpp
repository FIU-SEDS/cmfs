#pragma once

#include "FlightData.hpp"

#include <cstdint>

enum class FlightState : std::uint8_t {
  INIT,
  IDLE,
  BOOST,
  BURNOUT,
  COAST,
  APOGEE,
  DROGUE_DESCENT,
  MAIN_DESCENT,
  LANDED,
  SIZE,
};

class FlightStateMachine {
public:
  void update(const FlightData& Data);

  FlightState getState() const {
    return state_;
  }

private:
  FlightState state_ = FlightState::INIT;
};
