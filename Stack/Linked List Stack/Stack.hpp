#pragma once

#include "../Exceptions/StackExceptions.hpp"
#include "../../List/ListNode/ListNode.hpp"

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
  
  topElement = new ListNode<T>(other.topElement->elem);

  ListNode<T>* otherTrav = other.topElement->next;
  ListNode<T>* thisTrav = topElement;

  while (otherTrav != nullptr) {
    thisTrav->next = new ListNode<T>(otherTrav->elem);
    thisTrav = thisTrav->next;
    otherTrav = otherTrav->next;
  }
}

template <typename T>
inline Stack<T>::~Stack() {
  while (topElement != nullptr) {
    ListNode<T>* temp = topElement;
    topElement = topElement->next;
    delete temp;
  }
}

template <typename T>
inline void Stack<T>::push(const T& elem) {
  ListNode<T> *newNode = new ListNode<T>(elem);
  
  newNode->next = topElement;
  topElement = newNode;

  stackSize++;
}

template <typename T>
inline T Stack<T>::pop() {

  if (isEmpty()) throw StackEmptyError("Cannot pop element from stack! Stack is empty.");

  T topValue = topElement->elem;

  ListNode<T>* temp = topElement;
  topElement = topElement->next;
  delete temp;

  stackSize--;

  return topValue;
}

template <typename T>
inline T Stack<T>::top() const {
  if (isEmpty()) throw StackEmptyError("Cannot get top element! Stack is empty.");
  return topElement->elem;
}

template <typename T>
inline int Stack<T>::size() const {
  return stackSize;
}

template <typename T>
inline bool Stack<T>::isEmpty() const {
  return topElement == nullptr;
}
