#pragma once

#include "Figure.hpp"
#include "Point.hpp"
#include <cmath>
#include <cstddef>
#include <istream>
#include <memory>
#include <ostream>
#include <type_traits>
#include <utility>

template <class T>
  requires is_scalar<T>
class Polygon : public Figure<T> {
public:
  explicit Polygon(size_t num_vertices)
      : num_vertices_(num_vertices),
        vertices_(num_vertices > 0 ? std::make_unique<Point<T>[]>(num_vertices)
                                   : nullptr) {}

  virtual ~Polygon() override = default;

  Polygon(const Polygon &other)
      : num_vertices_(other.num_vertices_),
        vertices_(num_vertices_ > 0
                      ? std::make_unique<Point<T>[]>(num_vertices_)
                      : nullptr) {
    if (vertices_) {
      for (size_t i = 0; i < num_vertices_; ++i) {
        vertices_[i] = other.vertices_[i];
      }
    }
  }

  Polygon &operator=(const Polygon &other) {
    if (this == &other) {
      return *this;
    }

    num_vertices_ = other.num_vertices_;
    vertices_ = num_vertices_ > 0 ? std::make_unique<Point<T>[]>(num_vertices_)
                                  : nullptr;

    if (vertices_) {
      for (size_t i = 0; i < num_vertices_; ++i) {
        vertices_[i] = other.vertices_[i];
      }
    }
    return *this;
  }

  Polygon(Polygon &&other) noexcept
      : num_vertices_(std::exchange(other.num_vertices_, 0)),
        vertices_(std::move(other.vertices_)) {}

  Polygon &operator=(Polygon &&other) noexcept {
    if (this == &other) {
      return *this;
    }
    num_vertices_ = std::exchange(other.num_vertices_, 0);
    vertices_ = std::move(other.vertices_);
    return *this;
  }

  Point<T> geometricCenter() const override {
    if (num_vertices_ == 0 || !vertices_) {
      return {static_cast<T>(0), static_cast<T>(0)};
    }

    double sum_x = 0.0;
    double sum_y = 0.0;

    for (size_t i = 0; i < num_vertices_; ++i) {
      sum_x += static_cast<double>(vertices_[i].x);
      sum_y += static_cast<double>(vertices_[i].y);
    }

    return {static_cast<T>(sum_x / num_vertices_),
            static_cast<T>(sum_y / num_vertices_)};
  }

  operator double() const override {
    double area = 0.0;
    if (num_vertices_ < 3 || !vertices_) {
      return 0.0;
    }

    for (size_t i = 0; i < num_vertices_; ++i) {
      Point<T> p1 = vertices_[i];
      Point<T> p2 = vertices_[(i + 1) % num_vertices_];

      area += (static_cast<double>(p1.x) * p2.y) -
              (static_cast<double>(p2.x) * p1.y);
    }

    return std::abs(area) / 2.0;
  }

  bool operator==(const Figure<T> &other) const override {
    const Polygon<T> *other_poly = dynamic_cast<const Polygon<T> *>(&other);
    if (other_poly == nullptr) {
      return false;
    }

    if (num_vertices_ != other_poly->num_vertices_) {
      return false;
    }

    if (!vertices_ || !other_poly->vertices_) {
      return !vertices_ && !other_poly->vertices_;
    }

    for (size_t i = 0; i < num_vertices_; ++i) {
      if (vertices_[i] != other_poly->vertices_[i]) {
        return false;
      }
    }

    return true;
  }

  Point<T> &getVertex(size_t index) {
    if (!vertices_ || index >= num_vertices_) {
      throw std::out_of_range("Vertex index out of range for testing");
    }
    return vertices_[index];
  }

protected:
  void print(std::ostream &os) const override {
    os << "N=" << num_vertices_ << " [";
    if (vertices_) {
      for (size_t i = 0; i < num_vertices_; ++i) {
        os << vertices_[i];
        if (i < num_vertices_ - 1) {
          os << ", ";
        }
      }
    }
    os << "]";
  }

  void read(std::istream &is) override {
    if (vertices_) {
      for (size_t i = 0; i < num_vertices_; ++i) {
        is >> vertices_[i];
      }
    }
  }

  size_t num_vertices_;
  std::unique_ptr<Point<T>[]> vertices_;
};

template <class T>
  requires is_scalar<T>
class Triangle : public Polygon<T> {
public:
  Triangle() : Polygon<T>(3) {}
};

template <class T>
  requires is_scalar<T>
class Square : public Polygon<T> {
public:
  Square() : Polygon<T>(4) {}
};

template <class T>
  requires is_scalar<T>
class Rectangle : public Polygon<T> {
public:
  Rectangle() : Polygon<T>(4) {}
};
