#pragma once

#include "Point.hpp"
#include <iostream>
#include <istream>
#include <memory>
#include <ostream>

template <class T>
  requires is_scalar<T>
class Figure;

template <class T>
  requires is_scalar<T>
inline std::ostream &operator<<(std::ostream &os, const Figure<T> &fig) {
  fig.print(os);
  return os;
}

template <class T>
  requires is_scalar<T>
inline std::istream &operator>>(std::istream &is, Figure<T> &fig) {
  fig.read(is);
  return is;
}

template <class T>
  requires is_scalar<T>
class Figure {
public:
  virtual ~Figure() = default;

  virtual Point<T> geometricCenter() const = 0;

  virtual operator double() const = 0;

  virtual bool operator==(const Figure<T> &other) const = 0;

protected:
  virtual void print(std::ostream &os) const = 0;
  virtual void read(std::istream &is) = 0;

  friend std::istream &operator>> <>(std::istream &is, Figure<T> &fig);
  friend std::ostream &operator<< <>(std::ostream &os, const Figure<T> &fig);
};
