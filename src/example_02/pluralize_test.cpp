#include "pluralize.hpp"

#include <gtest/gtest.h>
#include <stdexcept>

using namespace testing_lecture::example_02;

TEST(Pluralize, EndAtOne) {
  const std::vector<std::string> plural{"монета", "монеты", "монет"};
  
  EXPECT_EQ(pluralize(1, plural), "монета");
  EXPECT_EQ(pluralize(21, plural), "монета");
  EXPECT_EQ(pluralize(101, plural), "монета");
  EXPECT_EQ(pluralize(5001, plural), "монета");
}

TEST(Pluralize, EndAtTwoThreeFour) {
  const std::vector<std::string> plural{"монета", "монеты", "монет"};
  
  EXPECT_EQ(pluralize(2, plural), "монеты");
  EXPECT_EQ(pluralize(22, plural), "монеты");
  EXPECT_EQ(pluralize(103, plural), "монеты");
  EXPECT_EQ(pluralize(5004, plural), "монеты");
}

TEST(Pluralize, SecondTen) {
  const std::vector<std::string> plural{"монета", "монеты", "монет"};
  
  EXPECT_EQ(pluralize(11, plural), "монет");
  EXPECT_EQ(pluralize(12, plural), "монет");
  EXPECT_EQ(pluralize(13, plural), "монет");
  EXPECT_EQ(pluralize(14, plural), "монет");
  EXPECT_EQ(pluralize(15, plural), "монет");
  EXPECT_EQ(pluralize(16, plural), "монет");
  EXPECT_EQ(pluralize(17, plural), "монет");
  EXPECT_EQ(pluralize(18, plural), "монет");
  EXPECT_EQ(pluralize(19, plural), "монет");
  EXPECT_EQ(pluralize(20, plural), "монет");
}

TEST(Pluralize, EndAtMoreThanFour) {
  const std::vector<std::string> plural{"монета", "монеты", "монет"};
  
  EXPECT_EQ(pluralize(5, plural), "монет");
  EXPECT_EQ(pluralize(26, plural), "монет");
  EXPECT_EQ(pluralize(107, plural), "монет");
  EXPECT_EQ(pluralize(5008, plural), "монет");
}

TEST(Pluralize, CatchException) {
  const std::vector<std::string> plural{"монета", "монеты"};

  try {
    pluralize(0, plural);
    ASSERT_TRUE(false) << "pluralize should throw exception";
  } catch (const std::range_error&) {
    return;
  }
}

TEST(Pluralize, CatchException2) {
  const std::vector<std::string> plural{"монета", "монеты"};

  ASSERT_THROW(pluralize(0, plural), std::range_error);
}

TEST(Pluralize, Negative) {
  const std::vector<std::string> plural{"монета", "монеты", "монет"};
  
  EXPECT_EQ(pluralize(-1, plural), "монета");
  EXPECT_EQ(pluralize(-2, plural), "монеты");
  EXPECT_EQ(pluralize(-5, plural), "монет");
  EXPECT_EQ(pluralize(-11, plural), "монет");
  EXPECT_EQ(pluralize(-101, plural), "монета");
}

// Определение тестовой фикстуры
class PluralizeFixture : public ::testing::Test {
protected:
    void SetUp() override {
        // Код для настройки условий тестирования
    }

    void TearDown() override {
        // Код для очистки после теста
    }

    const std::vector<std::string> plural{"монета", "монеты", "монет"};
};

// Использование фикстуры в тесте
TEST_F(PluralizeFixture, FixtureExample) {
  EXPECT_EQ(pluralize(1, plural), "монета");
  EXPECT_EQ(pluralize(2, plural), "монеты");
  EXPECT_EQ(pluralize(5, plural), "монет");
}
