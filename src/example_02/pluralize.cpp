#include "pluralize.hpp"

#include <stdexcept>

namespace testing_lecture::example_02 {

std::string pluralize(int number,
                      const std::vector<std::string>& plural) {
  if (plural.size() != 3) {
    throw std::range_error(
      "Plural form should contains 3 items, but was " +
      std::to_string(plural.size()));
  }

  number = std::abs(number % 100);
  if (number < 11 || number > 20) {
    number %= 10;
    if (number == 1) {
      return plural[0];
    }
    if (number >= 2 && number <= 4) {
      return plural[1];
    }
  }
  return plural[2];
}

}  // testing_lecture::example_02