#pragma once

#include <string>
#include <stdexcept>

// Some Exceptions
class InvalidExpression : public std::invalid_argument {
  public:
    InvalidExpression(const std::string& msg) : std::invalid_argument(msg) {}
};

// This class contains all helper methods (same methods that are required by solutions)
class Helper {
  public:
    static int findNextNonDigitIndex(std::string str, int startingPos) {
      if (startingPos > str.size()) throw std::out_of_range("Invalid starting position given!"); 

      int nextNonDigitIndex;

      for (nextNonDigitIndex = startingPos; nextNonDigitIndex < str.size(); nextNonDigitIndex++) {
        if (str[nextNonDigitIndex] < '0' || str[nextNonDigitIndex] > '9') {
          return nextNonDigitIndex;
        }
      }

      // If there is no next non digit index, return -1
      return -1;
    }
};