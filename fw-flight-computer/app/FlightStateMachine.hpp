#include <cstdint>

enum class FlighState : int32_t {
  INITIALIZATION,
  IDLE,
  BOOST,
  COAST,
  APOGEE,
  DROGUE_DESCENT,
  MAIN_DESCENT,
  LANDED
};
