#include "core/FlightStateMachine.hpp"
#include "core/FlightData.hpp"

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

TEST(FlightStateMachineTest, TransitionsFromInitToIdle) {
  FlightStateMachine Machine;
  FlightData Data;
  Data.sensors_healthy = true;

  Machine.update(Data);

  EXPECT_EQ(Machine.getState(), FlightState::IDLE);
}

TEST(FlightDataTest, AllValuesAreInitialized) {
  FlightData Data;
  FlightData* DataPtr = &Data;

  ASSERT_NE(DataPtr, nullptr);
  EXPECT_FLOAT_EQ(DataPtr->AccelerationZMps2, 0.0f);
  EXPECT_FLOAT_EQ(DataPtr->VerticalVelocityMps, 0.0f);
  EXPECT_FALSE(DataPtr->sensors_healthy);
}
