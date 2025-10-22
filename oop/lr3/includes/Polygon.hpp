#pragma once

#include "Figure.hpp"
#include <istream>
#include <ostream>

class Polygon : public Figure {
public:
  explicit Polygon(size_t num_vertices);
  virtual ~Polygon() override;

  Polygon(const Polygon &other);
  Polygon &operator=(const Polygon &other);
  Polygon(Polygon &&other) noexcept;
  Polygon &operator=(Polygon &&other) noexcept;

  Point geometricCenter() const override;

  operator double() const override;

  bool operator==(const Figure &other) const override;

protected:
  void print(std::ostream &os) const override;
  void read(std::istream &is) override;

  size_t num_vertices_;
  Point *vertices_;
};

class Triangle : public Polygon {
public:
  Triangle();
  Figure *clone() const override;
};

class Hexagon : public Polygon {
public:
  Hexagon();
  Figure *clone() const override;
};

class Octagon : public Polygon {
public:
  Octagon();
  Figure *clone() const override;
};
