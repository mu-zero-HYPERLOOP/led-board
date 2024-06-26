#include "firmware/led_board.hpp"
#include "canzero/canzero.h"

Adafruit_NeoPixel led_board::strip_2 = Adafruit_NeoPixel(STRIP_2_NUM_PIXELS, 0, 0);
Adafruit_NeoPixel led_board::strip_3 = Adafruit_NeoPixel(STRIP_3_NUM_PIXELS, 0, 0);
Adafruit_NeoPixel led_board::strip_4 = Adafruit_NeoPixel(STRIP_4_NUM_PIXELS, 0, 0);
Adafruit_NeoPixel led_board::strip_5 = Adafruit_NeoPixel(STRIP_5_NUM_PIXELS, 0, 0);
Adafruit_NeoPixel led_board::strip_6 = Adafruit_NeoPixel(STRIP_6_NUM_PIXELS, 0, 0);
Adafruit_NeoPixel led_board::strip_7 = Adafruit_NeoPixel(STRIP_7_NUM_PIXELS, 0, 0);

void led_board::begin() {
}

void led_board::update() {

}

void led_board::set_sdc(bool close) {
  canzero_set_sdc_status(close ? sdc_status_CLOSED : sdc_status_OPEN);
}
