#include "FlightStateMachine.hpp"

void FlightStateMachine::update(const FlightData& Data) {
  switch (state_) {
    case FlightState::INIT:
      if (Data.sensors_healthy) {
        state_ = FlightState::IDLE;
      }
      break;

    case FlightState::IDLE:
      if (Data.AccelerationZMps2 > 30.0f) {
        state_ = FlightState::BOOST;
      }
      break;

    case FlightState::BOOST:
      if (Data.AccelerationZMps2 < 5.0f) {
        state_ = FlightState::BURNOUT;
      }
      break;

    case FlightState::COAST:
      if (Data.VerticalVelocityMps <= 0.0f) {
        state_ = FlightState::APOGEE;
      }
      break;

    default:
      break;
  }
}
