#include "firmware/led_board.hpp"
#include "canzero/canzero.h"
#include "fsm/states.hpp"

led_board_state fsm::states::startup(led_board_command cmd, Duration time_since_last_transition) {
  led_board::strip_2.fill(0xffffff, 0, led_board::STRIP_2_NUM_PIXELS);


  return led_board_state_STARTUP;
}
