#include "canzero/canzero.h"
#include "firmware/led_board.hpp"
#include "fsm/states.hpp"


led_board_state fsm::states::shutdown(led_board_command cmd, Duration time_since_last_transition) {
  led_board::strip_2.fill(0x000000, 0, led_board::STRIP_2_NUM_PIXELS);
  led_board::strip_3.fill(0x000000, 0, led_board::STRIP_3_NUM_PIXELS);
  led_board::strip_4.fill(0x000000, 0, led_board::STRIP_4_NUM_PIXELS);
  led_board::strip_5.fill(0x000000, 0, led_board::STRIP_5_NUM_PIXELS);
  led_board::strip_6.fill(0x000000, 0, led_board::STRIP_6_NUM_PIXELS);
  led_board::strip_7.fill(0x000000, 0, led_board::STRIP_7_NUM_PIXELS);

  led_board::strip_2.show();
  led_board::strip_3.show();
  led_board::strip_4.show();
  led_board::strip_5.show();
  led_board::strip_6.show();
  led_board::strip_7.show();

  return led_board_state_SHUTDOWN;
}
