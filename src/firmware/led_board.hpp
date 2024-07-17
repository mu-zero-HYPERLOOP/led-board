#pragma once

#include "util/interval.h"
#include "util/metrics.h"
#include <Adafruit_NeoPixel.h>
#include <string>
#include "LiquidCrystal_PCF8574.h"



namespace led_board {

extern Adafruit_NeoPixel strip_2;
extern Adafruit_NeoPixel strip_3;
extern Adafruit_NeoPixel strip_4;
extern Adafruit_NeoPixel strip_5;
extern Adafruit_NeoPixel strip_6;
extern Adafruit_NeoPixel strip_7;

extern LiquidCrystal_PCF8574 display;
extern Interval display_update_interval;

static constexpr uint16_t STRIP_2_NUM_PIXELS = 42;
static constexpr uint16_t STRIP_3_NUM_PIXELS = 42;
static constexpr uint16_t STRIP_4_NUM_PIXELS = 100;
static constexpr uint16_t STRIP_5_NUM_PIXELS = 100;
static constexpr uint16_t STRIP_6_NUM_PIXELS = 4;
static constexpr uint16_t STRIP_7_NUM_PIXELS = 100;
static constexpr uint8_t DISPLAY_ADDR = 0x27;
static constexpr uint8_t DISPLAY_NUM_COLUMNS = 20;

static constexpr uint16_t IDX_ANY_ERROR = 0;
static constexpr uint16_t IDX_BATTERY_UNDERVOLT = 1;
static constexpr uint16_t IDX_TEMPERATURE_SYSTEM = 2;
static constexpr uint16_t IDX_SDC_STATUS = 3;

static constexpr uint8_t DISPLAY_NUM_ROWS = 4;
static constexpr uint32_t COLOR_OK = 0x00ff00;
static constexpr uint32_t COLOR_ERROR = 0xff0000;

static constexpr uint32_t COLOR_SDC_OPEN = 0x000000;
static constexpr uint32_t COLOR_SDC_CLOSED = 0xffea00;

static constexpr uint32_t COLOR_MUZERO = 0x00ffb0;

void begin();

void update();

void set_sdc(bool close);

Temperature read_mcu_temperature();

}

