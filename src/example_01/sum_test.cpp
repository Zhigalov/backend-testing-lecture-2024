#include "sum.hpp"

#include <gtest/gtest.h>
#include <random>

using namespace testing_lecture::example_01;

TEST(Sum, Success) {
  EXPECT_EQ(sum(1,2), 3);
}

TEST(Sum, FailedWithAssert) {
  ASSERT_EQ(sum(2,3), 4);
  ASSERT_EQ(sum(-3,-4), 0);
}

TEST(Sum, FailedWithExpect) {
  EXPECT_EQ(sum(4,5), 6);
  EXPECT_EQ(sum(-5,-3), 0);
}

TEST(Sum, FailedCustomMessage) {
  EXPECT_EQ(sum(4,0), 5)
    << "Sum with neutral element "
    << "should be equal input number";
}

TEST(Sum, SuccessRundom) {
  std::mt19937_64 gen(/*seed=*/ 123512);
  const int64_t a = gen();
  const int64_t b = gen();

  const int64_t actual = sum(a, b);

  const int64_t expected = a + b;
  EXPECT_EQ(actual, expected);
}