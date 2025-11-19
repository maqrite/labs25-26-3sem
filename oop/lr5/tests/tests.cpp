#include "../includes/PmrStack.h"
#include "../includes/Resource.hpp"
#include "gtest/gtest.h"
#include <string>
#include <vector>

using PmrStackInt = PmrStack<int>;
using Resource = Resource;

TEST(ResourceTest, Initialization) {
  Resource res1;
  Resource res2;

  ASSERT_TRUE(res1.is_equal(res1));
  ASSERT_FALSE(res1.is_equal(res2));
}

TEST(ResourceTest, AllocateDeallocate) {
  Resource res;

  void *p1 = res.allocate(32, 8);
  ASSERT_NE(p1, nullptr);

  res.deallocate(p1, 32, 8);

  void *p2 = res.allocate(32, 8);
  ASSERT_EQ(p1, p2);

  res.deallocate(p2, 32, 8);
}

class PmrStackIntTest : public ::testing::Test {
protected:
  Resource resource;
  PmrStackInt stack{&resource};
};

TEST_F(PmrStackIntTest, IsInitiallyEmpty) {
  ASSERT_TRUE(stack.empty());
  ASSERT_EQ(stack.size(), 0);
}

TEST_F(PmrStackIntTest, PushIncreasesSizeAndSetsTop) {
  stack.push(10);
  ASSERT_FALSE(stack.empty());
  ASSERT_EQ(stack.size(), 1);
  ASSERT_EQ(stack.top(), 10);
}

TEST_F(PmrStackIntTest, PopDecreasesSize) {
  stack.push(10);
  stack.push(20);

  stack.pop();
  ASSERT_EQ(stack.size(), 1);
  ASSERT_EQ(stack.top(), 10);
}

TEST_F(PmrStackIntTest, PopFromEmptyThrows) {
  ASSERT_THROW(stack.pop(), std::out_of_range);
}

TEST_F(PmrStackIntTest, IteratorTest) {
  stack.push(1);
  stack.push(2);
  stack.push(3);

  std::vector<int> expected = {3, 2, 1};
  std::vector<int> actual;

  for (int val : stack) {
    actual.push_back(val);
  }

  ASSERT_EQ(actual, expected);
}

struct ComplexData {
  int id;
  std::string name;

  ComplexData(int i, std::string n) : id(i), name(std::move(n)) {}
  bool operator==(const ComplexData &other) const {
    return id == other.id && name == other.name;
  }
};
using PmrStackComplex = PmrStack<ComplexData>;

class PmrStackComplexTest : public ::testing::Test {
protected:
  Resource resource;
  PmrStackComplex stack{&resource};

  ComplexData data1{1, "Alpha"};
  ComplexData data2{2, "Beta"};
};

TEST_F(PmrStackComplexTest, PushComplexType) {
  stack.push(data1.id, data1.name);
  ASSERT_EQ(stack.size(), 1);
  ASSERT_EQ(stack.top().id, 1);
  ASSERT_EQ(stack.top().name, "Alpha");
}

TEST_F(PmrStackComplexTest, CorrectDestructionOnPop) {
  stack.push(data1.id, data1.name);
  stack.push(data2.id, data2.name);

  stack.pop();
  ASSERT_EQ(stack.top().id, 1);
}
