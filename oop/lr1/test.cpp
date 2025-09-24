#include "function.hpp"
#include <gtest/gtest.h>

TEST(CountVowelsTest, HandlesEmptyString) { ASSERT_EQ(countVowels(""), 0); }

TEST(CountVowelsTest, HandlesStringWithNoVowels) {
  EXPECT_EQ(countVowels("ryn gslng"), 0);
  EXPECT_EQ(countVowels("brrr ptpm"), 0);
}

TEST(CountVowelsTest, HandlesStringWithOnlyVowels) {
  EXPECT_EQ(countVowels("aeiou"), 5);
  EXPECT_EQ(countVowels("aei ou"), 5);
}

TEST(CountVowelsTest, HandlesStandardMixedString) {
  EXPECT_EQ(countVowels("hello world!"), 3);
  EXPECT_EQ(countVowels("  rayan gosling v filme drive  "), 8);
}

TEST(CountVowelsTest, HandlesNonLowercase) {
  EXPECT_EQ(countVowels("HELLO WORLD 123!@#"), 0);
}
