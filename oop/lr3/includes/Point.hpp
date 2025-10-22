#pragma once

#include <cmath>
#include <iostream>

struct Point {
  double x = 0.0;
  double y = 0.0;

  bool operator==(const Point &other) const {
    constexpr double EPSILON = 1e-9;
    return std::abs(x - other.x) < EPSILON && std::abs(y - other.y) < EPSILON;
  }

  bool operator!=(const Point &other) const { return !(*this == other); }
};

inline std::ostream &operator<<(std::ostream &os, const Point &p) {
  os << "(" << p.x << ", " << p.y << ")";
  return os;
}

inline std::istream &operator>>(std::istream &is, Point &p) {
  is >> p.x >> p.y;
  return is;
}
