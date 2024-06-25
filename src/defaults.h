#pragma once

#include "canzero/canzero.h"

static void can_defaults() {
  canzero_set_state(led_board_state_INIT);
  canzero_set_command(led_board_command_NONE);
  canzero_set_sdc_status(sdc_status_OPEN);
}
