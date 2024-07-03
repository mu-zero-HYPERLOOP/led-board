#include "firmware/led_board.hpp"
#include "LiquidCrystal_PCF8574.h"
#include "Adafruit_NeoPixel.h"
#include "LiquidCrystal.h"
#include "canzero/canzero.h"
#include "core_pins.h"
#include "pinout.h"
#include "util/metrics.h"
#include <InternalTemperature.h>
#include <string>
#include "print.h"

Adafruit_NeoPixel led_board::strip_2 = Adafruit_NeoPixel(STRIP_2_NUM_PIXELS, (int16_t)LedPin::led_ctrl_2, NEO_BRG + NEO_KHZ800);
Adafruit_NeoPixel led_board::strip_3 = Adafruit_NeoPixel(STRIP_3_NUM_PIXELS, (int16_t)LedPin::led_ctrl_3, NEO_BRG + NEO_KHZ800);
Adafruit_NeoPixel led_board::strip_4 = Adafruit_NeoPixel(STRIP_4_NUM_PIXELS, (int16_t)LedPin::led_ctrl_4, NEO_BRG + NEO_KHZ800);
Adafruit_NeoPixel led_board::strip_5 = Adafruit_NeoPixel(STRIP_5_NUM_PIXELS, (int16_t)LedPin::led_ctrl_5, NEO_BRG + NEO_KHZ800);
Adafruit_NeoPixel led_board::strip_6 = Adafruit_NeoPixel(STRIP_6_NUM_PIXELS, (int16_t)LedPin::led_ctrl_6, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel led_board::strip_7 = Adafruit_NeoPixel(STRIP_7_NUM_PIXELS, (int16_t)LedPin::led_ctrl_7, NEO_BRG + NEO_KHZ800);

LiquidCrystal_PCF8574 led_board::display = LiquidCrystal_PCF8574(led_board::DISPLAY_ADDR);

bool bla = true;

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

  display.begin(DISPLAY_NUM_COLUMNS, DISPLAY_NUM_ROWS);
  display.setBacklight(HIGH);
  display.leftToRight();
  display.noAutoscroll();
}

const char* global_state_to_str(global_state state) {
  switch(state) {
  case global_state_INIT:
    return "Init";
  case global_state_IDLE:
    return "Idle";
  case global_state_ARMING45:
    return "Arming 45V";
  case global_state_PRECHARGE:
    return "Precharge";
  case global_state_DISARMING45:
    return "Disarming";
  case global_state_READY:
    return "Ready";
  case global_state_START_LEVITATION:
    return "Starting Levitation";
  case global_state_LEVITATION_STABLE:
    return "Levitation Stable";
  case global_state_START_GUIDANCE:
    return "Starting Guidance";
  case global_state_GUIDANCE_STABLE:
    return "Guidance Stable";
  case global_state_ACCELERATION:
    return "Accelerating";
  case global_state_CONTROLLER:
    return "Controller";
  case global_state_CRUISING:
    return "Cruising";
  case global_state_DECELERATION:
    return "Decelerating";
  case global_state_STOP_LEVITATION:
    return "Stopping Levitation";
  case global_state_STOP_GUIDANCE:
    return "Stopping Guidance";
  case global_state_SHUTDOWN:
    return "Shutdown";
  case global_state_RESTARTING:
    return "Restarting";
  case global_state_CALIBRATING:
    return "Calibrating";
  default:
    return "";
  }
}

const char* global_command_to_str(global_command cmd) {
  switch (cmd) {
  case global_command_NONE:
    return "None";
  case global_command_START_45:
    return "Start 45V";
  case global_command_STOP_45:
    return "Stop 45V";
  case global_command_START_LEVITATION:
    return "Start Levitation";
  case global_command_STOP_LEVITATION:
    return "Stop Levitation";
  case global_command_START_PROPULSION:
    return "Start Propulsion";
  case global_command_STOP_PROPULSION:
    return "Stop Propulsion";
  case global_command_START_CONTROLLER:
    return "Start Controller";
  case global_command_STOP_CONTROLLER:
    return "Stop Controller";
  case global_command_ABORT:
    return "Abort";
  case global_command_EMERGENCY:
    return "Emergency";
  case global_command_SHUTDOWN:
    return "Shutdown";
  case global_command_RESTART:
    return "Restart";
  case global_command_CALIBRATE:
    return "Calibrate";
  default:
    return "";
  }
}

void led_board::update() {
  display.setCursor(0, 0);
  display.printf("State:");
  display.setCursor(1, 1);
  display.printf("~%s", global_state_to_str(canzero_get_global_state()));
  display.setCursor(0, 2);
  display.printf("Command:");
  display.setCursor(1, 3);
  display.printf("~%s", global_command_to_str(canzero_get_global_command()));
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



