#include "Adafruit_NeoPixel.h"
#include "firmware/led_board.hpp"
#include "canzero/canzero.h"
#include "fsm/states.hpp"
#include <algorithm>
#include <cinttypes>
#include <cstdint>
#include "util/blends.hpp"

static constexpr uint32_t COLOR = 0x0000ff;
static constexpr uint16_t num_pixels = 20;
static constexpr float width = 0.2f;
static constexpr Duration animation_time = 2_s;
static constexpr Duration initial_delay = 0.5_s;

led_board_state fsm::states::startup_ease_out(led_board_command cmd, Duration time_since_last_transition) {
  float t = std::clamp((time_since_last_transition.as_us() - initial_delay.as_us()) /(float) animation_time.as_us(), 0.0f, 1.0f);
  t = ease_out_quint(t);
  led_board::strip_2.fill(0xff0000, 0, 100);
  for (int i = 0; i < num_pixels; ++i) {
    float x = i /(float) num_pixels; // x in [0,1)
    float my_color = 1.0f - sigmoid((x - t * (1 + 2 * width) + width) * 5 / width);

    led_board::strip_3.setPixelColor(i, my_color * COLOR);
  }
  for (int i = 0; i < led_board::STRIP_2_NUM_PIXELS; ++i) {
    led_board::strip_2.setPixelColor(i, 
        Adafruit_NeoPixel::ColorHSV((float)UINT16_MAX / led_board::STRIP_2_NUM_PIXELS * i));
    led_board::strip_2.setPixelColor(i, 0, 200, 90);



  }

  led_board::strip_2.show();
  led_board::strip_3.show();
  return led_board_state_STARTUP;
}
