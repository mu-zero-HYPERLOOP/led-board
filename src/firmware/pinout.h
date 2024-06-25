#pragma once

#include <cinttypes>

enum class LedPin : uint8_t {
  led_ctrl_2 = 2,
  led_ctrl_3 = 1,
  led_ctrl_4 = 4,
  led_ctrl_5 = 3,
  led_ctrl_6 = 6,
  led_ctrl_7 = 5,
};

static constexpr int SDC_CTRL_PIN = 16;
