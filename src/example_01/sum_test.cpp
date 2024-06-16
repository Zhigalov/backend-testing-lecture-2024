#include "sum.hpp"

#include <gtest/gtest.h>

using namespace testing_lecture::example_01;

TEST(Sum, Success) {
  EXPECT_EQ(sum<int>(1,2), 3);
}

TEST(Sum, FailedWithAssert) {
  ASSERT_EQ(sum<int>(2,3), 4);
  ASSERT_EQ(sum<int>(-3,-4), 0);
}

TEST(Sum, FailedWithExpect) {
  EXPECT_EQ(sum<int>(4,5), 6);
  EXPECT_EQ(sum<int>(-5,-3), 0);
}