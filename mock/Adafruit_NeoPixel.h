#pragma once

#include <cinttypes>

typedef uint16_t neoPixelType; ///< 3rd arg to Adafruit_NeoPixel constructor

class Adafruit_NeoPixel {

public:
  // Constructor: number of LEDs, pin number, LED type
  Adafruit_NeoPixel(uint16_t n, int16_t pin, neoPixelType type) {}
  Adafruit_NeoPixel(void) {}

  void begin(void) {}
  void show(void) {}
  void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b) {}
  void setPixelColor(uint16_t n, uint32_t c) {}
  void fill(uint32_t c = 0, uint16_t first = 0, uint16_t count = 0) {}
  void setBrightness(uint8_t) {}
  void clear(void) {}
  static uint8_t sine8(uint8_t x) {
    return x;
  }
  static uint8_t gamma8(uint8_t x) {
    return x;
  }
  static uint32_t Color(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
  }
  static uint32_t ColorHSV(uint16_t hue, uint8_t sat = 255, uint8_t val = 255) { return 0; }
  static uint32_t gamma32(uint32_t x) { return x; }
  void rainbow(uint16_t first_hue = 0, int8_t reps = 1,
               uint8_t saturation = 255, uint8_t brightness = 255,
               bool gammify = true);

};
