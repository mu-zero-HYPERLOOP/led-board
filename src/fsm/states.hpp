#pragma once

#include "canzero/canzero.h"
#include "util/timestamp.h"

namespace fsm::states {

led_board_state init(led_board_command cmd, Duration time_since_last_transition);

led_board_state startup(led_board_command cmd, Duration time_since_last_transition);

}
