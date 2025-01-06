#pragma once

#include "../Exceptions/StackExceptions.hpp"

#define MAX_STACK_SIZE 256

class Stack {
  private:
    int current;
    int stackArray[MAX_STACK_SIZE];

  public:
    Stack();
    Stack(const Stack&);

    void push(int elem);
    int pop();
    int top() const;
    bool isEmpty() const;
    bool isFull() const;
};

inline Stack::Stack(): current(-1) {
  // Initialize every element with 0
  for (int i = 0; i < MAX_STACK_SIZE; i++) {
    stackArray[i] = 0;
  }
}

inline Stack::Stack(const Stack& other): current(other.current) {
  for (int i = 0; i < MAX_STACK_SIZE; i++) {
    stackArray[i] = other.stackArray[i];
  }
}

inline void Stack::push(int elem) {
  stackArray[++current] = elem;
}

inline int Stack::pop() {
  return stackArray[current--];
}

inline int Stack::top() const {
  return stackArray[current];
}

inline bool Stack::isEmpty() const {
  return current == -1;
}

inline bool Stack::isFull() const {
  return current == MAX_STACK_SIZE;
}