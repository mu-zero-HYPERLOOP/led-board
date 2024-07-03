#pragma once

#include "canzero/canzero.h"

static void can_defaults() {
  canzero_set_state(led_board_state_INIT);
  canzero_set_command(led_board_command_NONE);
  canzero_set_sdc_status(sdc_status_OPEN);

  canzero_set_global_state(global_state_LEVITATION_STABLE);
  canzero_set_global_command(global_command_START_PROPULSION);

  canzero_set_error_heartbeat_miss(error_flag_OK);
  canzero_set_error_level_mcu_temperature(error_level_OK);
  canzero_set_error_level_config_mcu_temperature(error_level_config{
      .m_info_thresh = 60,
      .m_info_timeout = 1,
      .m_warning_thresh = 80,
      .m_warning_timeout = 1,
      .m_error_thresh = 90,
      .m_error_timeout = 1,
      .m_ignore_info = bool_t_FALSE,
      .m_ignore_warning = bool_t_FALSE,
      .m_ignore_error = bool_t_FALSE,
  });
  canzero_set_mcu_temperature(0);
}
