#pragma once

#include <stdexcept>

class StackFullError : public std::overflow_error {
  public:
    StackFullError(const char* message = "") : std::overflow_error(message) {}
};

class StackEmptyError : public std::underflow_error {
  public:
    StackEmptyError(const char* message = "") : std::underflow_error(message) {}
};