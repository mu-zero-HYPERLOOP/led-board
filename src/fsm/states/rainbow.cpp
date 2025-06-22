#include "Adafruit_NeoPixel.h"
#include "canzero/canzero.h"
#include "fsm/states.hpp"
#include "firmware/led_board.hpp"


led_board_state fsm::states::rainbow_hue(
    led_board_command cmd, 
    Duration time_since_last_transition) {

  led_board::strip_2.rainbow();
  led_board::strip_3.rainbow();


  led_board::strip_2.show();
  led_board::strip_3.show();


  return led_board_state_RAINBOW;
}

