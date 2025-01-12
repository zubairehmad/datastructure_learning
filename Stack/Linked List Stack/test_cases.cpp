#include <iostream>
#include <cassert>
#include "Stack.hpp"

using namespace std;

void assert_notice(const char* name, bool passed) {
  cout << "\n" << name << " " << (passed? "passed" : "failed") << ".\n";
}

void test_stack_push() {
  Stack<int> myStack;

  for (int i = 0; i < 100; i++) {
    myStack.push(i);
  }

  for (int i = 99; i >= 0; i--) {
    assert(myStack.pop() == i);
  }

  assert_notice(__func__, true);
}

void test_stack_pop() {
  Stack<int> myStack;

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
  Stack<int> myStack;

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

void test_stack_size() {
  Stack<int> myStack;

  assert(myStack.size() == 0);

  myStack.push(1);
  myStack.push(2);

  assert(myStack.size() == 2);

  myStack.pop();
  myStack.pop();

  for (int i = 0; i < 256; i++) {
    myStack.push(i);
  }

  assert(myStack.size() == 256);

  for (int i = 0; i < 256; i++) {
    myStack.pop();
  }

  assert(myStack.size() == 0);

  assert_notice(__func__, true);
}

void test_stack_isEmpty() {
  Stack<int> myStack;

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

void test_stack_copy_constructor() {
  Stack<int> myStack;

  for (int i = 0; i < 256; i++) {
    myStack.push(i);
  }

  {
    Stack<int> testStack = myStack;
    assert(testStack.size() == myStack.size());
    for (int i = 255; i <= 0; i--) {
      assert(testStack.pop() == i);
    }
  }

  for (int i = 0; i < 256; i++) {
    myStack.pop();
  }

  {
    Stack<int> testStack = myStack;
    assert(testStack.size() == myStack.size());
    try {
      testStack.top();
      assert_notice(__func__, false);
      assert(false);
    } catch (const StackEmptyError& e) {}
  }

  assert_notice(__func__, true);
}

int main() {

  test_stack_push();
  test_stack_pop();
  test_stack_top();
  test_stack_size();
  test_stack_isEmpty();
  test_stack_copy_constructor();

  cout << "\nAll test cases passed...\n";

  return 0;
}
