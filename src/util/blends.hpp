#pragma once

#include <algorithm>
#include <cmath>
#include <cinttypes>


inline float sigmoid(float x) {
  return 1.0f / (1.0f + std::exp(-x));
}


inline float step(float x) {
  return x <= 0.0f ? 0.0f : 1.0f;
}

inline float ease_out_cubic(float x) {
  x = std::clamp(x, 0.0f, 1.0f);
  return 1.0f - std::pow(1.0f - x, 3);
}

inline float ease_out_quart(float x) {
  x = std::clamp(x, 0.0f, 1.0f);
  return 1.0f - std::pow(1.0f - x, 4);
}

inline float ease_out_quint(float x) {
  x = std::clamp(x, 0.0f, 1.0f);
  return 1.0f - std::pow(1.0f - x, 5);
}

inline uint32_t scale_color_32(uint32_t c, float s) {
  return
    (uint32_t)(((c >> 16) & 0xff) * s) << 16 |
    (uint32_t)(((c >> 8) & 0xff) * s) << 8 |
    (uint32_t)(((c >> 0) & 0xff) * s) << 0;
}

inline uint32_t linear_interpolate(uint32_t c1, uint32_t c2, float s) {
  return scale_color_32(c1, s) + scale_color_32(c2, 1.0f - s);

}
