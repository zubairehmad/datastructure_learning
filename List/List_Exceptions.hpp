#include <new>

/*
    This exception should be thrown when someone tries to perform
    element based operations (remove, next, back, start, end) on empty list.
*/
class UninitializedListError : public std::bad_alloc {
private:
  const char *_message;

public:
  UninitializedListError(const char *message = "") : _message(message) {}

  const char *what() const noexcept override { return _message; }
};