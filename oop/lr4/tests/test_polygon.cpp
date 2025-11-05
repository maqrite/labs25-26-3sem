#include "Point.hpp"
#include "Polygon.hpp"
#include "gtest/gtest.h"

TEST(PointTest, IntegerComparison) {
  Point<int> p1{10, 20};
  Point<int> p2{10, 20};
  Point<int> p3{10, 21};
  ASSERT_EQ(p1, p2);
  ASSERT_NE(p1, p3);
}

TEST(PointTest, DoubleComparison) {
  Point<double> p1{0.1 + 0.2, 0.3};
  Point<double> p2{0.3, 0.3};
  ASSERT_EQ(p1, p2);
}

class PolygonTest : public ::testing::Test {
protected:
  Square<double> testSquare;
  Triangle<double> testTriangle;

  void SetUp() override {
    testSquare.getVertex(0) = {0.0, 0.0};
    testSquare.getVertex(1) = {2.0, 0.0};
    testSquare.getVertex(2) = {2.0, 2.0};
    testSquare.getVertex(3) = {0.0, 2.0};

    testTriangle.getVertex(0) = {0.0, 0.0};
    testTriangle.getVertex(1) = {3.0, 0.0};
    testTriangle.getVertex(2) = {0.0, 4.0};
  }
};

TEST_F(PolygonTest, GeometricCenter) {
  Point<double> expectedCenterSquare{1.0, 1.0};
  Point<double> expectedCenterTriangle{1.0, 4.0 / 3.0};

  ASSERT_EQ(testSquare.geometricCenter(), expectedCenterSquare);
  ASSERT_EQ(testTriangle.geometricCenter(), expectedCenterTriangle);
}

TEST_F(PolygonTest, Area) {
  ASSERT_DOUBLE_EQ(static_cast<double>(testSquare), 4.0);

  ASSERT_DOUBLE_EQ(static_cast<double>(testTriangle), 6.0);
}

TEST_F(PolygonTest, Equality) {
  Square<double> sameSquare;
  sameSquare.getVertex(0) = {0.0, 0.0};
  sameSquare.getVertex(1) = {2.0, 0.0};
  sameSquare.getVertex(2) = {2.0, 2.0};
  sameSquare.getVertex(3) = {0.0, 2.0};

  Square<double> differentSquare;

  ASSERT_EQ(testSquare, sameSquare);
  ASSERT_NE(testSquare, differentSquare);

  ASSERT_NE(static_cast<Figure<double> &>(testSquare),
            static_cast<Figure<double> &>(testTriangle));
}

TEST_F(PolygonTest, CopySemantics) {
  Square<double> copiedSquare(testSquare);
  ASSERT_EQ(testSquare, copiedSquare);

  Square<double> assignedSquare;
  assignedSquare = testSquare;
  ASSERT_EQ(testSquare, assignedSquare);

  copiedSquare.getVertex(0) = {100.0, 100.0};
  ASSERT_NE(testSquare, copiedSquare);
}

TEST_F(PolygonTest, MoveSemantics) {
  Square<double> originalSquare;
  originalSquare.getVertex(0) = {1, 1};
  originalSquare.getVertex(1) = {2, 1};
  originalSquare.getVertex(2) = {2, 2};
  originalSquare.getVertex(3) = {1, 2};

  Square<double> copyForCheck = originalSquare;

  Square<double> movedSquare(std::move(originalSquare));

  ASSERT_EQ(movedSquare, copyForCheck);

  Point<double> expectedCenter{0.0, 0.0};
  ASSERT_EQ(originalSquare.geometricCenter(), expectedCenter);

  ASSERT_DOUBLE_EQ(static_cast<double>(originalSquare), 0.0);
}
