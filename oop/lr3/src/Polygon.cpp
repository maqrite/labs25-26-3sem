#include "../includes/Polygon.hpp"
#include <cmath>

Polygon::Polygon(size_t num_vertices)
    : num_vertices_(num_vertices), vertices_(nullptr) {

  if (num_vertices_ > 0) {
    vertices_ = new Point[num_vertices_];
  }
}

Polygon::~Polygon() { delete[] vertices_; }

Polygon::Polygon(const Polygon &other)
    : num_vertices_(other.num_vertices_), vertices_(nullptr) {

  if (num_vertices_ > 0) {
    vertices_ = new Point[num_vertices_];
    for (size_t i = 0; i < num_vertices_; ++i) {
      vertices_[i] = other.vertices_[i];
    }
  }
}

Polygon &Polygon::operator=(const Polygon &other) {
  if (this == &other) {
    return *this;
  }

  delete[] vertices_;

  num_vertices_ = other.num_vertices_;
  vertices_ = nullptr;

  if (num_vertices_ > 0) {
    vertices_ = new Point[num_vertices_];
    for (size_t i = 0; i < num_vertices_; ++i) {
      vertices_[i] = other.vertices_[i];
    }
  }

  return *this;
}

Polygon::Polygon(Polygon &&other) noexcept
    : num_vertices_(other.num_vertices_), vertices_(other.vertices_) {
  other.num_vertices_ = 0;
  other.vertices_ = nullptr;
}

Polygon &Polygon::operator=(Polygon &&other) noexcept {
  if (this == &other) {
    return *this;
  }

  delete[] vertices_;

  num_vertices_ = other.num_vertices_;
  vertices_ = other.vertices_;

  other.num_vertices_ = 0;
  other.vertices_ = nullptr;

  return *this;
}

Point Polygon::geometricCenter() const {
  if (num_vertices_ == 0) {
    return {0.0, 0.0};
  }

  double sum_x = 0.0;
  double sum_y = 0.0;

  for (size_t i = 0; i < num_vertices_; ++i) {
    sum_x += vertices_[i].x;
    sum_y += vertices_[i].y;
  }

  return {sum_x / num_vertices_, sum_y / num_vertices_};
}

Polygon::operator double() const {
  double area = 0.0;
  if (num_vertices_ < 3) {
    return 0.0;
  }

  for (size_t i = 0; i < num_vertices_; ++i) {
    Point p1 = vertices_[i];
    Point p2 = vertices_[(i + 1) % num_vertices_];

    area += (p1.x * p2.y) - (p2.x * p1.y);
  }

  return std::abs(area) / 2.0;
}

bool Polygon::operator==(const Figure &other) const {
  const Polygon *other_poly = dynamic_cast<const Polygon *>(&other);
  if (other_poly == nullptr) {
    return false;
  }

  if (num_vertices_ != other_poly->num_vertices_) {
    return false;
  }

  for (size_t i = 0; i < num_vertices_; ++i) {
    if (vertices_[i] != other_poly->vertices_[i]) {
      return false;
    }
  }

  return true;
}

void Polygon::print(std::ostream &os) const {
  os << "N=" << num_vertices_ << " [";
  for (size_t i = 0; i < num_vertices_; ++i) {
    os << vertices_[i];
    if (i < num_vertices_ - 1) {
      os << ", ";
    }
  }
  os << "]";
}

void Polygon::read(std::istream &is) {
  for (size_t i = 0; i < num_vertices_; ++i) {
    is >> vertices_[i];
  }
}

Triangle::Triangle() : Polygon(3) {}
Figure *Triangle::clone() const { return new Triangle(*this); }

Hexagon::Hexagon() : Polygon(6) {}
Figure *Hexagon::clone() const { return new Hexagon(*this); }

Octagon::Octagon() : Polygon(8) {}
Figure *Octagon::clone() const { return new Octagon(*this); }
