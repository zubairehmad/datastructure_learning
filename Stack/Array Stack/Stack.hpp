#pragma once

#include "../Exceptions/StackExceptions.hpp"

#define MAX_STACK_SIZE 256

class Stack {
  private:
    int current;
    int stackArray[MAX_STACK_SIZE];

  public:
    Stack();

    void push(int elem);
    int pop();
    int top() const;
    int size() const;
    bool isEmpty() const;
    bool isFull() const;
};

inline Stack::Stack(): current(-1) {
  // Initialize every element with 0
  for (int i = 0; i < MAX_STACK_SIZE; i++) {
    stackArray[i] = 0;
  }
}

inline void Stack::push(int elem) {
  if (isFull()) throw StackFullError("Cannot push another element! Stack is full.");
  stackArray[++current] = elem;
}

inline int Stack::pop() {
  if (isEmpty()) throw StackEmptyError("Cannot remove top element! Stack is empty.");
  return stackArray[current--];
}

inline int Stack::top() const {
  if (isEmpty()) throw StackEmptyError("Cannot get top element! Stack is empty.");
  return stackArray[current];
}

inline int Stack::size() const {
  return current+1;
}

inline bool Stack::isEmpty() const {
  return current == -1;
}

inline bool Stack::isFull() const {
  return current == MAX_STACK_SIZE-1;
}