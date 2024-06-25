#pragma once

#include <cinttypes>

enum class LedPin : uint8_t {
  led_ctrl_2 = 2,
  led_ctrl_3 = 3,
  led_ctrl_4 = 4,
  led_ctrl_5 = 5,
  led_ctrl_6 = 6,
  led_ctrl_7 = 7,
};

static constexpr int SDC_CTRL_PIN = 16;
