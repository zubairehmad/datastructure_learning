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