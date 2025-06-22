#include "fsm/states.hpp"
#include "Adafruit_NeoPixel.h"
#include "firmware/led_board.hpp"
#include "canzero/canzero.h"
#include "fsm/states.hpp"
#include <algorithm>
#include <cinttypes>
#include <cmath>
#include <cstdint>
#include "util/blends.hpp"
#include "util/metrics.h"
#include "Arduino.h"

static constexpr uint16_t num_pixels = led_board::STRIP_2_NUM_PIXELS;
static constexpr Frequency freq = 0.5_Hz;
static constexpr Duration animation_time = 5_s;
static constexpr Duration initial_delay = 0_s;
static constexpr float min_brightness = 0.0f;
static constexpr float max_brightness = 1.0f;
static constexpr uint16_t center = num_pixels / 2;
static constexpr Duration pixel_offset = 100_ms;
static constexpr uint32_t color_1 = led_board::COLOR_MUZERO;
static constexpr uint32_t color_2 = 0xb000ff;
//static constexpr uint32_t color_2 = 0x00c0c0;
//static constexpr uint32_t color_2 = 0xff0000;


led_board_state fsm::states::breathe_brightness(
    led_board_command cmd, 
    Duration time_since_last_transition) {

  if (time_since_last_transition <= initial_delay) {
    led_board::strip_2.clear();
    led_board::strip_3.clear();
    led_board::strip_2.show();
    led_board::strip_3.show();
    return led_board_state_BREATHE;
  }
  const Duration time = time_since_last_transition - initial_delay;

  for (int i = 0; i < num_pixels; ++i) {
    float brightness = min_brightness + (max_brightness - min_brightness) * 0.5f *
      (std::cos(2 * M_PI * static_cast<float>(freq) * 
          (time.as_ms() - 
           std::abs(i - center) * pixel_offset.as_ms()) / 1000.0f) + 1);

    led_board::strip_2.setPixelColor(i, Adafruit_NeoPixel::gamma32(scale_color_32(led_board::COLOR_MUZERO, brightness)));
    led_board::strip_3.setPixelColor(i, Adafruit_NeoPixel::gamma32(scale_color_32(led_board::COLOR_MUZERO, brightness)));
  }

  led_board::strip_2.show();
  led_board::strip_3.show();
  return led_board_state_BREATHE;
}

led_board_state fsm::states::breathe_color(
    led_board_command cmd,
    Duration time_since_last_transition) {

  if (time_since_last_transition <= initial_delay) {
    led_board::strip_2.clear();
    led_board::strip_3.clear();
    led_board::strip_2.show();
    led_board::strip_3.show();
    return led_board_state_BREATHE;
  }
  const Duration time = time_since_last_transition - initial_delay;

  for (int i = 0; i < num_pixels; ++i) {
    float offset = std::abs(i - center) * pixel_offset.as_ms() < time.as_ms() ? std::abs(i - center) * pixel_offset.as_ms() : time.as_ms();
    float brightness = min_brightness + (max_brightness - min_brightness) * 0.5f *
      (std::cos(2 * M_PI * static_cast<float>(freq) * 
          (time.as_ms() - offset) / 1000.0f) + 1);

    led_board::strip_2.setPixelColor(i, Adafruit_NeoPixel::gamma32(linear_interpolate(color_1, color_2, brightness)));
    led_board::strip_3.setPixelColor(i, Adafruit_NeoPixel::gamma32(linear_interpolate(color_1, color_2, brightness)));
  }

  led_board::strip_2.show();
  led_board::strip_3.show();
  return led_board_state_BREATHE;
}
