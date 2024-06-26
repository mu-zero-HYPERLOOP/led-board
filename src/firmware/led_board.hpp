#pragma once

#include "util/metrics.h"
#include <Adafruit_NeoPixel.h>



namespace led_board {

extern Adafruit_NeoPixel strip_2;
extern Adafruit_NeoPixel strip_3;
extern Adafruit_NeoPixel strip_4;
extern Adafruit_NeoPixel strip_5;
extern Adafruit_NeoPixel strip_6;
extern Adafruit_NeoPixel strip_7;

static constexpr uint16_t STRIP_2_NUM_PIXELS = 42;
static constexpr uint16_t STRIP_3_NUM_PIXELS = 42;
static constexpr uint16_t STRIP_4_NUM_PIXELS = 100;
static constexpr uint16_t STRIP_5_NUM_PIXELS = 100;
static constexpr uint16_t STRIP_6_NUM_PIXELS = 100;
static constexpr uint16_t STRIP_7_NUM_PIXELS = 100;

static constexpr uint32_t COLOR_MUZERO = 0x00ff71;

void begin();

void update();

void set_sdc(bool close);

Temperature read_mcu_temperature();

}

