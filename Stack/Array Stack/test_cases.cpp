#include <iostream>
#include <cassert>
#include "Stack.hpp"

using namespace std;

void assert_notice(const char* name, bool passed) {
  cout << "\n" << name << " " << (passed? "passed" : "failed") << ".\n";
}

void test_stack_push() {
  Stack myStack;

  for (int i = 0; i < MAX_STACK_SIZE; i++) {
    myStack.push(i);
  }

  try {
    myStack.push(95);
    assert_notice(__func__, false);
    assert(false);
  } catch (const StackFullError& e) {}

  for (int i = MAX_STACK_SIZE-1; i >= 0; i--) {
    assert(myStack.pop() == i);
  }

  assert_notice(__func__, true);
}

void test_stack_pop() {
  Stack myStack;

  try {
    myStack.pop();
    assert_notice(__func__, false);
    assert(false);
  } catch (const StackEmptyError& e) {}

  for (int i = 1; i <= 5; i++) 
    myStack.push(i*10);

  assert(myStack.top() == 50);

  for (int i = 5; i < 0; i--)
    assert(myStack.pop() == (i*10));

  assert_notice(__func__, true);
}

void test_stack_top() {
  Stack myStack;

  try {
    myStack.top();
    assert_notice(__func__, false);
    assert(false);
  } catch (const StackEmptyError& e) {}

  for (int i = 0; i < 10; i++) {
    myStack.push(i*5);
  }

  assert(myStack.top() == 45);

  for (int i = 9; i >= 0; i--) {
    assert(myStack.top() == (i*5));
    myStack.pop();
  }

  assert_notice(__func__, true);
}

void test_stack_isEmpty() {
  Stack myStack;

  assert(myStack.isEmpty() == true);

  myStack.push(1);
  myStack.push(2);
  myStack.push(3);

  assert(myStack.top() == 3);
  assert(myStack.isEmpty() == false);

  myStack.pop();
  myStack.pop();
  myStack.pop();

  assert(myStack.isEmpty() == true);

  assert_notice(__func__, true);
}

void test_stack_isFull() {
  Stack myStack;

  for (int i = 0; i < MAX_STACK_SIZE; i++) {
    myStack.push(i);
  }

  assert(myStack.isFull() == true);

  myStack.pop();

  assert(myStack.isFull() == false);

  myStack.push(0);

  assert(myStack.isFull() == true);

  assert_notice(__func__, true);
}

int main() {

  test_stack_push();
  test_stack_pop();
  test_stack_top();
  test_stack_isEmpty();
  test_stack_isFull();

  cout << "\nAll test cases passed...\n";

  return 0;
}