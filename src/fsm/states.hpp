#pragma once

#include "canzero/canzero.h"
#include "util/timestamp.h"

namespace fsm::states {

led_board_state init(led_board_command cmd, Duration time_since_last_transition);

led_board_state startup_ease_out(led_board_command cmd, Duration time_since_last_transition);

led_board_state rainbow_hue(led_board_command cmd, Duration time_since_last_transition);

led_board_state liftoff(led_board_command cmd, Duration time_since_last_transition);

led_board_state breathe_brightness(led_board_command cmd, Duration time_since_last_transition);

led_board_state breathe_color(led_board_command cmd, Duration time_since_last_transition);

led_board_state shutdown(led_board_command cmd, Duration time_since_last_transition);

led_board_state pulsate(led_board_command cmd, Duration time_since_last_transition);

}
