#pragma once

#include "../../List/ListNode/ListNode.hpp"
#include "../Exceptions/QueueExceptions.hpp"

template <typename T>
class Queue {
  private:
    ListNode<T>* frontPtr;
    ListNode<T>* rearPtr;
    unsigned int sizeOfQueue;

    void defaultInitialize();

  public:
    Queue();
    Queue(const Queue<T>&);

    void enqueue(const T&);
    T dequeue();

    const T& front() const;
    bool isEmpty() const;
    unsigned int size() const;

    ~Queue();
};

template <typename T>
inline void Queue<T>::defaultInitialize() {
  frontPtr = nullptr;
  rearPtr = nullptr;
  sizeOfQueue = 0;
}

template <typename T>
inline Queue<T>::Queue() {
  defaultInitialize();
}

template <typename T>
inline Queue<T>::Queue(const Queue<T>& other) {

  // If other queue is empty, initialize using default method
  if (other.isEmpty()) {
    defaultInitialize();
    return;
  }

  frontPtr = new ListNode<T>(other.frontPtr->elem);
  rearPtr = frontPtr;

  ListNode<T>* traversal = other.frontPtr->next;

  while (traversal != nullptr) {
    ListNode<T>* temp = new ListNode<T>(traversal->elem);
    rearPtr->next = temp;
    rearPtr = temp;
    traversal = traversal->next;
  }

  sizeOfQueue = other.sizeOfQueue;
}

template <typename T>
void Queue<T>::enqueue(const T& elem) {
  if (sizeOfQueue == 0) {
    frontPtr = new ListNode<T>(elem);
    rearPtr = frontPtr;
  } else {
    ListNode<T>* newNode = new ListNode<T>(elem);

    rearPtr->next = newNode;
    rearPtr = rearPtr->next;
  }

  sizeOfQueue++;
}

template <typename T>
T Queue<T>::dequeue() {
  
  if (sizeOfQueue == 0) {
    throw QueueEmptyException("Queue is empty! Cannot remove/dequeue element...");
  }

  T elem = frontPtr->elem;

  if (sizeOfQueue == 1) {
    delete frontPtr;
    frontPtr = nullptr;
    rearPtr = nullptr;
  } else {
    ListNode<T>* temp = frontPtr;
    frontPtr = frontPtr->next;
    delete temp;
  }

  sizeOfQueue--;
  return elem;
}

template <typename T>
const T& Queue<T>::front() const {
  if (sizeOfQueue == 0) {
    throw QueueEmptyException("Queue is empty! Cannot get front element...");
  }

  return frontPtr->elem;
}

template <typename T>
unsigned int Queue<T>::size() const {
  return sizeOfQueue;
}

template <typename T>
bool Queue<T>::isEmpty() const {
  return sizeOfQueue == 0;
}

template <typename T>
inline Queue<T>::~Queue() {
  while (frontPtr != nullptr) {
    ListNode<T>* temp = frontPtr;
    frontPtr = frontPtr->next;
    delete temp;
  }

  rearPtr = nullptr;
}
