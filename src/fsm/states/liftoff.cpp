#include "canzero/canzero.h"
#include "firmware/led_board.hpp"
#include "fsm/states.hpp"
#include "util/blends.hpp"
#include "util/timestamp.h"


static constexpr int length_end_front = 6;
static constexpr int length_end_back = 5;
static constexpr uint16_t num_pixels = led_board::STRIP_2_NUM_PIXELS;
static constexpr float width = 0.2f;
static constexpr Duration animation_time = 2_s;
static constexpr Duration initial_delay = 5_s;

led_board_state fsm::states::liftoff(
    led_board_command cmd, 
    Duration time_since_last_transition) {
  if (time_since_last_transition <= initial_delay) {
    led_board::strip_2.clear();
    led_board::strip_3.clear();
    led_board::strip_2.show();
    led_board::strip_3.show();
    return led_board_state_STARTUP;
  }
  float t = std::clamp((time_since_last_transition.as_ms() - initial_delay.as_ms()) /(float) animation_time.as_ms(), 0.0f, 1.0f);
  t = ease_out_quint(t);


  for (int i = length_end_back; i < num_pixels - length_end_front; ++i) {
    float x = 0.9f + 
      (i - length_end_back) /(float) (num_pixels - length_end_back - length_end_front) * 0.1f;
        // x in [0.9, 1)
    float my_color = 1.0f - sigmoid((x - t * (1 + 2 * width) + width) * 5 / width);

    led_board::strip_2.setPixelColor(i, 
        Adafruit_NeoPixel::gamma32(my_color * led_board::COLOR_MUZERO));
    led_board::strip_3.setPixelColor(i, 
        Adafruit_NeoPixel::gamma32(my_color * led_board::COLOR_MUZERO));
  }
  for (int i = 0; i < length_end_back; ++i) {
    float x = i /(float) length_end_back * 0.9f; // x in [0, 0.9)
    float my_color = 1.0f - sigmoid((x - t * (1 + 2 * width) + width) * 5 / width);

    led_board::strip_2.setPixelColor(i, 
        Adafruit_NeoPixel::gamma32(my_color * led_board::COLOR_MUZERO));
    led_board::strip_3.setPixelColor(i, 
        Adafruit_NeoPixel::gamma32(my_color * led_board::COLOR_MUZERO));
  }
  for (int i = 0; i < length_end_front; ++i) {
    float x = i /(float) length_end_front; // x in [0,1)
    float my_color = 1.0f - sigmoid((x - t * (1 + 2 * width) + width) * 5 / width);

    led_board::strip_2.setPixelColor(num_pixels - 1 - i, 
        Adafruit_NeoPixel::gamma32(my_color * led_board::COLOR_MUZERO));
    led_board::strip_3.setPixelColor(num_pixels - 1 - i, 
        Adafruit_NeoPixel::gamma32(my_color * led_board::COLOR_MUZERO));
  }

  led_board::strip_2.show();
  led_board::strip_3.show();

}
