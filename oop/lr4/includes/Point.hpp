#pragma once

#include <cmath>
#include <concepts>
#include <iostream>
#include <istream>
#include <limits>
#include <ostream>
#include <type_traits>

template <class T>
concept is_scalar = std::is_scalar_v<T>;

template <class T>
  requires is_scalar<T>
struct Point {

  T x{};
  T y{};

  bool operator==(const Point<T> &other) const {
    if constexpr (std::is_integral_v<T>) {
      return x == other.x && y == other.y;
    }

    else if constexpr (std::is_floating_point_v<T>) {
      return std::abs(x - other.x) < std::numeric_limits<T>::epsilon() &&
             std::abs(y - other.y) < std::numeric_limits<T>::epsilon();
    }

    else {
      return x == other.x && y == other.y;
    }
  }

  bool operator!=(const Point<T> &other) const { return !(*this == other); }
};

template <class T>
  requires is_scalar<T>
inline std::ostream &operator<<(std::ostream &os, const Point<T> &p) {
  os << "(" << p.x << ", " << p.y << ")";
  return os;
}

template <class T>
  requires is_scalar<T>
inline std::istream &operator>>(std::istream &is, Point<T> &p) {
  is >> p.x >> p.y;
  return is;
}
