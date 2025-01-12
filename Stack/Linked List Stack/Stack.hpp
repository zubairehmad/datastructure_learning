#pragma once

#include "../Exceptions/StackExceptions.hpp"

template <typename T>
struct ListNode {
  struct ListNode<T>* prev;
  T value;

  ListNode(T _value = 0, ListNode<T>* _prev = nullptr) : value(_value), prev(_prev) {}
};

template <typename T>
class Stack {
  private:
    int stackSize;
    ListNode<T>* topElement;

  public:
    Stack();
    Stack(const Stack&);
    ~Stack();

    void push(const T& elem);
    T pop();
    T top() const;
    int size() const;
    bool isEmpty() const;
};

template <typename T>
inline Stack<T>::Stack(): stackSize(0), topElement(nullptr) {}

template <typename T>
inline Stack<T>::Stack(const Stack& other) : stackSize(other.stackSize) {

  if (other.isEmpty()) {
    // Initialize using normal constructor and exit
    *this = Stack();
    return;
  }
  
  topElement = new ListNode<T>(other.topElement->value);

  ListNode<T>* otherTrav = other.topElement->prev;
  ListNode<T>* thisTrav = topElement;

  while (otherTrav != nullptr) {
    thisTrav->prev = new ListNode<T>(otherTrav->value);
    thisTrav = thisTrav->prev;
    otherTrav = otherTrav->prev;
  }
}

template <typename T>
inline Stack<T>::~Stack() {
  while (topElement != nullptr) {
    ListNode<T>* temp = topElement;
    topElement = topElement->prev;
    delete temp;
  }
}

template <typename T>
inline void Stack<T>::push(const T& elem) {
  ListNode<T> *newNode = new ListNode<T>(elem);
  
  newNode->prev = topElement;
  topElement = newNode;

  stackSize++;
}

template <typename T>
inline T Stack<T>::pop() {

  if (isEmpty()) throw StackEmptyError("Cannot pop element from stack! Stack is empty.");

  T topValue = topElement->value;

  ListNode<T>* temp = topElement;
  topElement = topElement->prev;
  delete temp;

  stackSize--;

  return topValue;
}

template <typename T>
inline T Stack<T>::top() const {
  if (isEmpty()) throw StackEmptyError("Cannot get top element! Stack is empty.");
  return topElement->value;
}

template <typename T>
inline int Stack<T>::size() const {
  return stackSize;
}

template <typename T>
inline bool Stack<T>::isEmpty() const {
  return topElement == nullptr;
}
