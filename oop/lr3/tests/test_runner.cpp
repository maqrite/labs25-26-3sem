#include <gtest/gtest.h>
#include <sstream>

#include "../includes/Array.hpp"
#include "../includes/Point.hpp"
#include "../includes/Polygon.hpp"

TEST(PointTest, Comparison) {
  Point p1{1.0, 2.0};
  Point p2{1.0000000001, 2.0};
  Point p3{1.1, 2.0};

  ASSERT_EQ(p1, p2);
  ASSERT_NE(p1, p3);
}

Triangle create_test_triangle() {
  Triangle t;
  std::stringstream ss("0 0 3 0 0 4");
  ss >> t;
  return t;
}

TEST(TriangleTest, CenterAndArea) {
  Triangle t = create_test_triangle();

  Point expected_center{1.0, 4.0 / 3.0};

  double expected_area = 6.0;

  ASSERT_EQ(t.geometricCenter(), expected_center);
  ASSERT_DOUBLE_EQ(static_cast<double>(t), expected_area);
}

TEST(PolygonTest, Comparison) {
  Triangle t1 = create_test_triangle();
  Triangle t2 = create_test_triangle();
  Hexagon h1;

  ASSERT_EQ(t1, t2);
  ASSERT_NE(t1, h1);
}

TEST(PolygonTest, Clone) {
  Figure *t1 = new Triangle();
  std::stringstream("0 0 3 0 0 4") >> *t1;

  Figure *t2_clone = t1->clone();

  ASSERT_NE(t1, t2_clone);

  ASSERT_EQ(*t1, *t2_clone);

  std::stringstream("1 1 1 1 1 1") >> *t1;
  ASSERT_NE(*t1, *t2_clone);

  delete t1;
  delete t2_clone;
}

TEST(PolygonTest, IOStream) {
  Triangle t1 = create_test_triangle();

  std::stringstream output;
  output << t1;

  ASSERT_EQ(output.str(), "N=3 [(0, 0), (3, 0), (0, 4)]");
}

TEST(ArrayTest, DefaultConstructor) {
  Array arr;
  ASSERT_EQ(arr.size(), 0);
}

TEST(ArrayTest, PushAndRemove) {
  Array arr;
  arr.push_back(new Triangle());
  arr.push_back(new Hexagon());
  arr.push_back(new Octagon());
  ASSERT_EQ(arr.size(), 3);

  arr.remove(1);
  ASSERT_EQ(arr.size(), 2);

  ASSERT_EQ(typeid(*arr[0]), typeid(Triangle));
  ASSERT_EQ(typeid(*arr[1]), typeid(Octagon));

  arr.remove(1);
  ASSERT_EQ(arr.size(), 1);
  ASSERT_EQ(typeid(*arr[0]), typeid(Triangle));
}

TEST(ArrayTest, OutOfRange) {
  Array arr;
  arr.push_back(new Triangle());
  ASSERT_THROW(arr.remove(5), std::out_of_range);
  ASSERT_THROW(arr[5], std::out_of_range);
}

TEST(ArrayTest, CopyConstructor) {
  Array a1;
  a1.push_back(new Triangle(create_test_triangle()));

  Array a2 = a1;

  ASSERT_EQ(a1.size(), 1);
  ASSERT_EQ(a2.size(), 1);

  ASSERT_NE(a1[0], a2[0]);

  ASSERT_EQ(*a1[0], *a2[0]);
  ASSERT_DOUBLE_EQ(static_cast<double>(*a2[0]), 6.0);
}

TEST(ArrayTest, CopyAssignment) {
  Array a1;
  a1.push_back(new Triangle(create_test_triangle()));

  Array a2;
  a2.push_back(new Hexagon());

  a2 = a1;

  ASSERT_EQ(a1.size(), 1);
  ASSERT_EQ(a2.size(), 1);
  ASSERT_NE(a1[0], a2[0]);
  ASSERT_EQ(*a1[0], *a2[0]);
  ASSERT_DOUBLE_EQ(static_cast<double>(*a2[0]), 6.0);

  a1 = a1;
  ASSERT_EQ(a1.size(), 1);
  ASSERT_DOUBLE_EQ(static_cast<double>(*a1[0]), 6.0);
}

TEST(ArrayTest, MoveConstructor) {
  Array a1;
  Figure *t_ptr = new Triangle(create_test_triangle());
  a1.push_back(t_ptr);

  Array a2 = std::move(a1);

  ASSERT_EQ(a1.size(), 0);

  ASSERT_EQ(a2.size(), 1);

  ASSERT_EQ(a2[0], t_ptr);
}

TEST(ArrayTest, MoveAssignment) {
  Array a1;
  Figure *t_ptr = new Triangle(create_test_triangle());
  a1.push_back(t_ptr);

  Array a2;
  a2.push_back(new Hexagon());

  a2 = std::move(a1);

  ASSERT_EQ(a1.size(), 0);
  ASSERT_EQ(a2.size(), 1);
  ASSERT_EQ(a2[0], t_ptr);
  ASSERT_EQ(typeid(*a2[0]), typeid(Triangle));
}

TEST(ArrayTest, PolymorphismAndTotalArea) {
  Array arr;
  arr.push_back(new Triangle(create_test_triangle()));

  Triangle t2;
  std::stringstream("0 0 6 0 0 0") >> t2;
  arr.push_back(new Triangle(t2));

  arr.push_back(new Hexagon());

  double total_area = 0.0;
  for (size_t i = 0; i < arr.size(); ++i) {
    total_area += static_cast<double>(*arr[i]);
  }

  ASSERT_DOUBLE_EQ(total_area, 6.0);
}
