#include "firmware/led_board.hpp"
#include "Adafruit_NeoPixel.h"
#include "canzero/canzero.h"
#include "core_pins.h"
#include "pinout.h"

Adafruit_NeoPixel strip_2;
Adafruit_NeoPixel strip_3;
Adafruit_NeoPixel strip_4;
Adafruit_NeoPixel strip_5;
Adafruit_NeoPixel strip_6;
Adafruit_NeoPixel strip_7;

void led_board::begin() {
  strip_2 = Adafruit_NeoPixel(STRIP_2_NUM_PIXELS, (int16_t)LedPin::led_ctrl_2, NEO_GRB + NEO_KHZ800);
  strip_3 = Adafruit_NeoPixel(STRIP_3_NUM_PIXELS, (int16_t)LedPin::led_ctrl_3, NEO_GRB + NEO_KHZ800);
  strip_4 = Adafruit_NeoPixel(STRIP_4_NUM_PIXELS, (int16_t)LedPin::led_ctrl_4, NEO_GRB + NEO_KHZ800);
  strip_5 = Adafruit_NeoPixel(STRIP_5_NUM_PIXELS, (int16_t)LedPin::led_ctrl_5, NEO_GRB + NEO_KHZ800);
  strip_6 = Adafruit_NeoPixel(STRIP_6_NUM_PIXELS, (int16_t)LedPin::led_ctrl_6, NEO_GRB + NEO_KHZ800);
  strip_7 = Adafruit_NeoPixel(STRIP_7_NUM_PIXELS, (int16_t)LedPin::led_ctrl_7, NEO_GRB + NEO_KHZ800);

  strip_2.begin();
  strip_3.begin();
  strip_4.begin();
  strip_5.begin();
  strip_6.begin();
  strip_7.begin();

  strip_2.setBrightness(255);
  strip_3.setBrightness(255);
  strip_4.setBrightness(255);
  strip_5.setBrightness(255);
  strip_6.setBrightness(255);
  strip_7.setBrightness(255);
}

void led_board::update() {

}

void led_board::set_sdc(bool close) {
  digitalWrite(SDC_CTRL_PIN, close);
  canzero_set_sdc_status(close ? sdc_status_CLOSED : sdc_status_OPEN);
}
