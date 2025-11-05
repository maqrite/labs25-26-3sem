#include "Array.hpp"
#include "gtest/gtest.h"
#include <string>

TEST(ArrayTest, IntArray) {
  Array<int> arr;
  ASSERT_EQ(arr.size(), 0);
  ASSERT_EQ(arr.capacity(), 0);

  arr.push_back(10);
  arr.push_back(20);
  arr.push_back(30);

  ASSERT_EQ(arr.size(), 3);
  ASSERT_EQ(arr[0], 10);
  ASSERT_EQ(arr[1], 20);
  ASSERT_EQ(arr[2], 30);
  ASSERT_GE(arr.capacity(), 3);
}

TEST(ArrayTest, StringArray) {
  Array<std::string> arr;
  arr.push_back("hello");
  std::string s = "world";
  arr.push_back(s);
  arr.push_back("!");

  ASSERT_EQ(arr.size(), 3);
  ASSERT_EQ(arr[0], "hello");
  ASSERT_EQ(arr[1], "world");
  ASSERT_EQ(arr[2], "!");
}

TEST(ArrayTest, Remove) {
  Array<int> arr;
  arr.push_back(10);
  arr.push_back(20);
  arr.push_back(30);
  arr.push_back(40);
  ASSERT_EQ(arr.size(), 4);

  arr.remove(1);
  ASSERT_EQ(arr.size(), 3);
  ASSERT_EQ(arr[0], 10);
  ASSERT_EQ(arr[1], 30);
  ASSERT_EQ(arr[2], 40);

  arr.remove(2);
  ASSERT_EQ(arr.size(), 2);
  ASSERT_EQ(arr[0], 10);
  ASSERT_EQ(arr[1], 30);

  arr.remove(0);
  ASSERT_EQ(arr.size(), 1);
  ASSERT_EQ(arr[0], 30);
}

TEST(ArrayTest, Exceptions) {
  Array<int> arr;
  arr.push_back(1);

  ASSERT_THROW(arr[10], std::out_of_range);
  ASSERT_THROW(arr.remove(10), std::out_of_range);

  ASSERT_NO_THROW(arr[0]);
  ASSERT_NO_THROW(arr.remove(0));
}

TEST(ArrayTest, CopySemantics) {
  Array<int> arr1;
  arr1.push_back(1);
  arr1.push_back(2);

  Array<int> arr2(arr1);
  ASSERT_EQ(arr1.size(), 2);
  ASSERT_EQ(arr2.size(), 2);
  ASSERT_EQ(arr1[0], arr2[0]);

  arr2[0] = 99;
  ASSERT_EQ(arr1[0], 1);
  ASSERT_EQ(arr2[0], 99);

  Array<int> arr3;
  arr3 = arr1;
  ASSERT_EQ(arr3.size(), 2);
  ASSERT_EQ(arr3[0], 1);
}

TEST(ArrayTest, MoveSemantics) {
  Array<std::string> arr1;
  arr1.push_back("one");
  arr1.push_back("two");

  size_t old_cap = arr1.capacity();

  Array<std::string> arr2(std::move(arr1));

  ASSERT_EQ(arr2.size(), 2);
  ASSERT_EQ(arr2.capacity(), old_cap);
  ASSERT_EQ(arr2[0], "one");

  ASSERT_EQ(arr1.size(), 0);
  ASSERT_EQ(arr1.capacity(), 0);

  arr1 = std::move(arr2);

  ASSERT_EQ(arr1.size(), 2);
  ASSERT_EQ(arr1.capacity(), old_cap);

  ASSERT_EQ(arr2.size(), 0);
  ASSERT_EQ(arr2.capacity(), 0);
}
