#pragma once

struct FlightData {
  float AccelerationZMps2 = 0.0;   // Acceleration along the flight computer's Z axis in m/s².
  float VerticalVelocityMps = 0.0; // Vertical velocity in m/s, positive upward.
  bool sensors_healthy = false;
};
