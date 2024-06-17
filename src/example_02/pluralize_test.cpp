#include "pluralize.hpp"

#include <gtest/gtest.h>

using namespace testing_lecture::example_02;

TEST(Pluralize, One) {
  const std::vector<std::string> plural{"рубль", "рубля", "рублей"};
  
  EXPECT_EQ(pluralize(1, plural), "рубль");
}

TEST(Pluralize, TwoThreeFor) {
  const std::vector<std::string> plural{"рубль", "рубля", "рублей"};
  
  EXPECT_EQ(pluralize(2, plural), "рубля");
  EXPECT_EQ(pluralize(3, plural), "рубля");
  EXPECT_EQ(pluralize(4, plural), "рубля");
}

TEST(Pluralize, TopTen) {
  const std::vector<std::string> plural{"рубль", "рубля", "рублей"};
  
  EXPECT_EQ(pluralize(5, plural), "рублей");
  EXPECT_EQ(pluralize(6, plural), "рублей");
  EXPECT_EQ(pluralize(7, plural), "рублей");
  EXPECT_EQ(pluralize(8, plural), "рублей");
  EXPECT_EQ(pluralize(9, plural), "рублей");
  EXPECT_EQ(pluralize(10, plural), "рублей");
}

TEST(Pluralize, SecondTen) {
  const std::vector<std::string> plural{"рубль", "рубля", "рублей"};
  
  EXPECT_EQ(pluralize(11, plural), "рублей");
  EXPECT_EQ(pluralize(12, plural), "рублей");
  EXPECT_EQ(pluralize(13, plural), "рублей");
  EXPECT_EQ(pluralize(14, plural), "рублей");
  EXPECT_EQ(pluralize(15, plural), "рублей");
  EXPECT_EQ(pluralize(16, plural), "рублей");
  EXPECT_EQ(pluralize(17, plural), "рублей");
  EXPECT_EQ(pluralize(18, plural), "рублей");
  EXPECT_EQ(pluralize(19, plural), "рублей");
  EXPECT_EQ(pluralize(20, plural), "рублей");
}

TEST(Pluralize, EndOne) {
  const std::vector<std::string> plural{"рубль", "рубля", "рублей"};
  
  EXPECT_EQ(pluralize(21, plural), "рубль");
  EXPECT_EQ(pluralize(101, plural), "рубль");
  EXPECT_EQ(pluralize(5001, plural), "рубль");
}

TEST(Pluralize, EndTwoThreeFor) {
  const std::vector<std::string> plural{"рубль", "рубля", "рублей"};
  
  EXPECT_EQ(pluralize(22, plural), "рубля");
  EXPECT_EQ(pluralize(103, plural), "рубля");
  EXPECT_EQ(pluralize(5004, plural), "рубля");
}

TEST(Pluralize, EndTopTen) {
  const std::vector<std::string> plural{"рубль", "рубля", "рублей"};
  
  EXPECT_EQ(pluralize(25, plural), "рублей");
  EXPECT_EQ(pluralize(106, plural), "рублей");
  EXPECT_EQ(pluralize(5007, plural), "рублей");
}

TEST(Pluralize, EndSecondTen) {
  const std::vector<std::string> plural{"рубль", "рубля", "рублей"};
  
  EXPECT_EQ(pluralize(111, plural), "рублей");
  EXPECT_EQ(pluralize(5012, plural), "рублей");
}