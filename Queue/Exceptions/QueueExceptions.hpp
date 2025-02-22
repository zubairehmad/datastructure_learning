#pragma once

#include <stdexcept>

class QueueEmptyException : public std::underflow_error {
  public:
    QueueEmptyException(const std::string& msg="") : std::underflow_error(msg) {}
};

class QueueOverflowException : public std::overflow_error {
  public:
    QueueOverflowException(const std::string& msg="") : std::overflow_error(msg) {}
};