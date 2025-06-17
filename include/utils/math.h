#pragma once

#include <raylib.h>
#include <cmath>
#include "vector2int.h"

namespace math {
inline float Vector2Distance(Vector2 a, Vector2 b) {
  return std::sqrt(std::pow(a.x - b.x, 2.0f) + std::pow(a.y - b.y, 2.0f));
}
inline float Vector2IntDistance(Vector2Int a, Vector2Int b) {
  return std::sqrt(std::pow(a.x - b.x, 2.0f) + std::pow(a.y - b.y, 2.0f));
}
}  // namespace math
