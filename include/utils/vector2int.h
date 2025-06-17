#pragma once

#include <cmath>
#include <functional>
#include <iostream>

struct Vector2Int {
  int x = 0;
  int y = 0;

  Vector2Int() = default;
  Vector2Int(int x, int y) : x(x), y(y) {}
  explicit Vector2Int(int value) : x(value), y(value) {}

  template <typename T>
  explicit Vector2Int(const T& vec) : x(static_cast<int>(vec.x)), y(static_cast<int>(vec.y)) {}

  Vector2Int operator+(const Vector2Int& other) const {
    return Vector2Int(x + other.x, y + other.y);
  }

  Vector2Int operator-(const Vector2Int& other) const {
    return Vector2Int(x - other.x, y - other.y);
  }

  Vector2Int operator*(int scalar) const { return Vector2Int(x * scalar, y * scalar); }

  Vector2Int operator/(int scalar) const { return Vector2Int(x / scalar, y / scalar); }

  Vector2Int operator%(int scalar) const { return Vector2Int(x % scalar, y % scalar); }

  Vector2Int operator-() const { return Vector2Int(-x, -y); }

  Vector2Int& operator+=(const Vector2Int& other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  Vector2Int& operator-=(const Vector2Int& other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  Vector2Int& operator*=(int scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
  }

  Vector2Int& operator/=(int scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
  }

  Vector2Int& operator%=(int scalar) {
    x %= scalar;
    y %= scalar;
    return *this;
  }

  bool operator==(const Vector2Int& other) const { return x == other.x && y == other.y; }

  bool operator!=(const Vector2Int& other) const { return !(*this == other); }

  bool operator<(const Vector2Int& other) const {
    return x < other.x || (x == other.x && y < other.y);
  }

  bool operator<=(const Vector2Int& other) const { return *this < other || *this == other; }

  bool operator>(const Vector2Int& other) const { return !(*this <= other); }

  bool operator>=(const Vector2Int& other) const { return !(*this < other); }

  int& operator[](int index) { return (&x)[index]; }

  const int& operator[](int index) const { return (&x)[index]; }

  int Dot(const Vector2Int& other) const { return x * other.x + y * other.y; }

  int Cross(const Vector2Int& other) const { return x * other.y - y * other.x; }

  double Length() const { return std::sqrt(x * x + y * y); }

  int LengthSquared() const { return x * x + y * y; }

  int ManhattanDistance(const Vector2Int& other = Vector2Int(0, 0)) const {
    return std::abs(x - other.x) + std::abs(y - other.y);
  }

  int ChebyshevDistance(const Vector2Int& other = Vector2Int(0, 0)) const {
    return std::max(std::abs(x - other.x), std::abs(y - other.y));
  }

  Vector2Int Sign() const {
    return Vector2Int(x > 0 ? 1 : (x < 0 ? -1 : 0), y > 0 ? 1 : (y < 0 ? -1 : 0));
  }

  Vector2Int Abs() const { return Vector2Int(std::abs(x), std::abs(y)); }

  Vector2Int Clamp(const Vector2Int& min, const Vector2Int& max) const {
    return Vector2Int(std::max(min.x, std::min(max.x, x)), std::max(min.y, std::min(max.y, y)));
  }

  Vector2Int RotateLeft() const { return Vector2Int(-y, x); }

  Vector2Int RotateRight() const { return Vector2Int(y, -x); }

  Vector2Int Rotate180() const { return Vector2Int(-x, -y); }

  bool IsZero() const { return x == 0 && y == 0; }

  Vector2Int Min(const Vector2Int& other) const {
    return Vector2Int(std::min(x, other.x), std::min(y, other.y));
  }

  Vector2Int Max(const Vector2Int& other) const {
    return Vector2Int(std::max(x, other.x), std::max(y, other.y));
  }

  std::string ToString() const { return "(" + std::to_string(x) + ", " + std::to_string(y) + ")"; }

  static const Vector2Int ZERO;
  static const Vector2Int ONE;
  static const Vector2Int UP;
  static const Vector2Int DOWN;
  static const Vector2Int LEFT;
  static const Vector2Int RIGHT;
  static const Vector2Int UP_LEFT;
  static const Vector2Int UP_RIGHT;
  static const Vector2Int DOWN_LEFT;
  static const Vector2Int DOWN_RIGHT;
};

inline const Vector2Int Vector2Int::ZERO = Vector2Int(0, 0);
inline const Vector2Int Vector2Int::ONE = Vector2Int(1, 1);
inline const Vector2Int Vector2Int::UP = Vector2Int(0, -1);
inline const Vector2Int Vector2Int::DOWN = Vector2Int(0, 1);
inline const Vector2Int Vector2Int::LEFT = Vector2Int(-1, 0);
inline const Vector2Int Vector2Int::RIGHT = Vector2Int(1, 0);
inline const Vector2Int Vector2Int::UP_LEFT = Vector2Int(-1, -1);
inline const Vector2Int Vector2Int::UP_RIGHT = Vector2Int(1, -1);
inline const Vector2Int Vector2Int::DOWN_LEFT = Vector2Int(-1, 1);
inline const Vector2Int Vector2Int::DOWN_RIGHT = Vector2Int(1, 1);

inline Vector2Int operator*(int scalar, const Vector2Int& vec) { return vec * scalar; }

inline std::ostream& operator<<(std::ostream& os, const Vector2Int& vec) {
  os << vec.ToString();
  return os;
}

// hash function (used for std::unordered_map)
namespace std {
template <>
struct hash<Vector2Int> {
  size_t operator()(const Vector2Int& vec) const {
    return hash<int>()(vec.x) ^ (hash<int>()(vec.y) << 1);
  }
};
}  // namespace std
