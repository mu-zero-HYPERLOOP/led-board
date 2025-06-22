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
#include "print.h"


static constexpr uint16_t num_pixels = led_board::STRIP_2_NUM_PIXELS;
static constexpr float speed_pixels_per_sec = 10.0f; // pixels/sec
static constexpr Duration initial_delay = 0_s;
static constexpr uint32_t pulse_color = led_board::COLOR_MUZERO;
static constexpr uint32_t background_color = 0x000000;
static constexpr int pulse_width_base = 7;    
static constexpr float speed_limit = 400.0f;
static constexpr float speed_increment = 10.0f;
static constexpr int width_increment = 5;



led_board_state fsm::states::pulsate(
    led_board_command cmd,
    Duration time_since_last_transition) {

  static float speed = speed_pixels_per_sec;
  static int pulse_count = 0;
  static Duration last_pulse = 0_s;
  static int pulse_width = pulse_width_base;
  


  if (time_since_last_transition <= initial_delay) {
    led_board::strip_2.clear();
    led_board::strip_3.clear();
    led_board::strip_2.show();
    led_board::strip_3.show();
    return led_board_state_PULSATE;
  }

  float time_ms = time_since_last_transition.as_ms() - last_pulse.as_ms();
  int current_pixel = static_cast<int>((speed * time_ms) / 1000.0f);

  // If pulse ran past the end, reset for next
  if (current_pixel - pulse_width/2 >= num_pixels) {
    pulse_count++;
    last_pulse = time_since_last_transition;
    if (speed <= speed_limit) {
      speed += speed_increment;
    }
    if (pulse_count > 20) {
      pulse_width += width_increment;
    } if (pulse_count > 40) {
      pulse_width += width_increment*4;
    }
    debugPrintf("speed: %f\n", speed);
    return led_board_state_PULSATE; // stay in state
  }
  


  

  // Clear both strips
  for (int i = 0; i < num_pixels; ++i) {
    led_board::strip_2.setPixelColor(i, background_color);
    led_board::strip_3.setPixelColor(i, background_color);
  }

  // Draw the pulse (with width)
  for (int i = -pulse_width / 2; i <= pulse_width / 2; ++i) {
    int p = current_pixel + i;
    if (p >= 0 && p < num_pixels) {
      // Distance from center, normalized to [0, 1]
      float distance = std::abs(i) / static_cast<float>(pulse_width / 2) ;
      float brightness = ease_out_cubic(1.0F - distance); // Bright in center, fades out
      //debugPrintf("p = %d distance = %f brightness = %f\n", p, distance, brightness);
      //float brightness =0.0F;

      uint32_t color = Adafruit_NeoPixel::gamma32(
        linear_interpolate(pulse_color, background_color, brightness)
      );

      led_board::strip_2.setPixelColor(p, color);
      led_board::strip_3.setPixelColor(p, color);
    }

  }


  led_board::strip_2.show();
  led_board::strip_3.show();

  if (speed > 400.0 && pulse_count > 60) {
    return led_board_state_BREATHE;
  }

  return led_board_state_PULSATE;
}
