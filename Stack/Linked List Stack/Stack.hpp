#pragma once

#include "../Exceptions/StackExceptions.hpp"

struct ListNode {
  struct ListNode* prev;
  int value;

  ListNode(int _value = 0, ListNode* _prev = nullptr) : value(_value), prev(_prev) {}
};

class Stack {
  private:
    int stackSize;
    ListNode* topElement;

  public:
    Stack();
    Stack(const Stack&);
    ~Stack();

    void push(int elem);
    int pop();
    int top() const;
    int size() const;
    bool isEmpty() const;
};

inline Stack::Stack(): stackSize(0), topElement(nullptr) {}

inline Stack::Stack(const Stack& other) : stackSize(other.stackSize) {

  if (other.isEmpty()) {
    // Initialize using normal constructor and exit
    *this = Stack();
    return;
  }
  
  topElement = new ListNode(other.topElement->value);

  ListNode* otherTrav = other.topElement->prev;
  ListNode* thisTrav = topElement;

  while (otherTrav != nullptr) {
    thisTrav->prev = new ListNode(otherTrav->value);
    thisTrav = thisTrav->prev;
    otherTrav = otherTrav->prev;
  }
}

inline Stack::~Stack() {
  while (topElement != nullptr) {
    ListNode* temp = topElement;
    topElement = topElement->prev;
    delete temp;
  }
}

inline void Stack::push(int elem) {
  ListNode *newNode = new ListNode(elem);
  
  newNode->prev = topElement;
  topElement = newNode;

  stackSize++;
}

inline int Stack::pop() {

  if (isEmpty()) throw StackEmptyError("Cannot pop element from stack! Stack is empty.");

  int topValue = topElement->value;

  ListNode* temp = topElement;
  topElement = topElement->prev;
  delete temp;

  stackSize--;

  return topValue;
}

inline int Stack::top() const {
  if (isEmpty()) throw StackEmptyError("Cannot get top element! Stack is empty.");
  return topElement->value;
}

inline int Stack::size() const {
  return stackSize;
}

inline bool Stack::isEmpty() const {
  return topElement == nullptr;
}