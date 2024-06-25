#pragma once

#include <algorithm>
#include <cmath>


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
