#include "core/FlightStateMachine.hpp"

#include <gtest/gtest.h>

TEST(FlightStateMachineTest, StartsInInit) {
  FlightStateMachine Machine;
  EXPECT_EQ(Machine.getState(), FlightState::INIT);
}

TEST(FlightStateMachineTest, IdleSampleLeavesMachineInInit) {
  FlightStateMachine Machine;
  Machine.update(FlightData{0.0f, 0.0f});
  EXPECT_EQ(Machine.getState(), FlightState::INIT);
}
