#pragma once

#include "Point.hpp"
#include <iostream>

class Figure {
public:
  virtual ~Figure() = default;

  virtual Point geometricCenter() const = 0;

  virtual operator double() const = 0;

  virtual bool operator==(const Figure &other) const = 0;

  virtual Figure *clone() const = 0;

protected:
  virtual void print(std::ostream &os) const = 0;

  virtual void read(std::istream &is) = 0;

  friend std::ostream &operator<<(std::ostream &os, const Figure &fig);
  friend std::istream &operator>>(std::istream &is, Figure &fig);
};

inline std::ostream &operator<<(std::ostream &os, const Figure &fig) {
  fig.print(os);
  return os;
}

inline std::istream &operator>>(std::istream &is, Figure &fig) {
  fig.read(is);
  return is;
}
