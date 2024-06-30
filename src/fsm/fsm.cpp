#include "fsm/fsm.hpp"
#include "canzero/canzero.h"
#include "util/timestamp.h"
#include "fsm/states.hpp"

static Timestamp fsm_last_transition = Timestamp::now();

void fsm::begin() {
  //canzero_set_state(led_board_state_INIT);
  fsm_last_transition = Timestamp::now();

  // for video!!
  canzero_set_state(led_board_state_STARTUP);
  canzero_set_command(led_board_command_NONE);

}

void fsm::update() {
  led_board_state state;
  led_board_state next_state;

  do {
    const Timestamp now = Timestamp::now();
    const Duration time_since_last_transition = now - fsm_last_transition;

    led_board_command cmd = canzero_get_command();

    state = canzero_get_state();
    switch (state) {
    case led_board_state_INIT:
      break;
    case led_board_state_STARTUP:
      next_state = states::startup_ease_out(cmd, time_since_last_transition);
      break;
    case led_board_state_LIFTOFF:
      break;
    case led_board_state_BREATHE:
      next_state = states::breathe_color(cmd, time_since_last_transition);
      break;
    case led_board_state_SHUTDOWN:
      next_state = states::shutdown(cmd, time_since_last_transition);
      break;
    case led_board_state_RAINBOW:
      next_state = states::rainbow_hue(cmd, time_since_last_transition);
      break;
    }

    if (state != next_state) {
      fsm_last_transition = now;
      canzero_set_state(next_state);
      canzero_update_continue(canzero_get_time());
    }
  } while (next_state != state);
}
