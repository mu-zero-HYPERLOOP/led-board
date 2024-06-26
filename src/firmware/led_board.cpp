#include "firmware/led_board.hpp"
#include "Adafruit_NeoPixel.h"
#include "canzero/canzero.h"
#include "core_pins.h"
#include "pinout.h"
#include "util/metrics.h"
#include <InternalTemperature.h>

Adafruit_NeoPixel led_board::strip_2 = Adafruit_NeoPixel(STRIP_2_NUM_PIXELS, (int16_t)LedPin::led_ctrl_2, NEO_BRG + NEO_KHZ800);
Adafruit_NeoPixel led_board::strip_3 = Adafruit_NeoPixel(STRIP_3_NUM_PIXELS, (int16_t)LedPin::led_ctrl_3, NEO_BRG + NEO_KHZ800);
Adafruit_NeoPixel led_board::strip_4 = Adafruit_NeoPixel(STRIP_4_NUM_PIXELS, (int16_t)LedPin::led_ctrl_4, NEO_BRG + NEO_KHZ800);
Adafruit_NeoPixel led_board::strip_5 = Adafruit_NeoPixel(STRIP_5_NUM_PIXELS, (int16_t)LedPin::led_ctrl_5, NEO_BRG + NEO_KHZ800);
Adafruit_NeoPixel led_board::strip_6 = Adafruit_NeoPixel(STRIP_6_NUM_PIXELS, (int16_t)LedPin::led_ctrl_6, NEO_BRG + NEO_KHZ800);
Adafruit_NeoPixel led_board::strip_7 = Adafruit_NeoPixel(STRIP_7_NUM_PIXELS, (int16_t)LedPin::led_ctrl_7, NEO_BRG + NEO_KHZ800);

void led_board::begin() {
  pinMode(static_cast<uint8_t>(LedPin::led_ctrl_2), OUTPUT);
  pinMode(static_cast<uint8_t>(LedPin::led_ctrl_3), OUTPUT);
  pinMode(static_cast<uint8_t>(LedPin::led_ctrl_4), OUTPUT);
  pinMode(static_cast<uint8_t>(LedPin::led_ctrl_5), OUTPUT);
  pinMode(static_cast<uint8_t>(LedPin::led_ctrl_6), OUTPUT);
  pinMode(static_cast<uint8_t>(LedPin::led_ctrl_7), OUTPUT);
  
  pinMode(SDC_CTRL_PIN, OUTPUT);

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

  strip_2.clear();
  strip_3.clear();
  strip_4.clear();
  strip_5.clear();
  strip_6.clear();
  strip_7.clear();

  strip_2.show();
  strip_3.show();
  strip_4.show();
  strip_5.show();
  strip_6.show();
  strip_7.show();
}

void led_board::update() {

}

void led_board::set_sdc(bool close) {
  digitalWrite(SDC_CTRL_PIN, close);
  canzero_set_sdc_status(close ? sdc_status_CLOSED : sdc_status_OPEN);
}

Temperature led_board::read_mcu_temperature() {
  const float temp = InternalTemperature.readTemperatureC();
  const float temp_kelvin = temp - 273.15f;
  return Temperature(temp_kelvin);
}


