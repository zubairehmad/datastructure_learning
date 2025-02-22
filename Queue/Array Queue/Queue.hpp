#pragma once

#include "../Exceptions/QueueExceptions.hpp"
#include <iostream>

#define MAX_QUEUE_SIZE 100

template <typename T>
class Queue {
  private:
    int _frontIndex;
    int _rearIndex;
    T _queueArray[MAX_QUEUE_SIZE];

    unsigned _size;

    void _initEmptyQueue();
  public:
    Queue();
    Queue(const Queue<T>&);

    template <typename Type>
    friend std::ostream& operator << (std::ostream&, const Queue<Type>&);

    void enqueue(const T&);
    T dequeue();

    const T& front() const;
    const T& rear() const;

    bool isEmpty() const;
    bool isFull() const;

    const unsigned& size() const;
};

template <typename T>
void Queue<T>::_initEmptyQueue() {
  _frontIndex = -1;
  _rearIndex = -1;
  _size = 0;
}


template <typename T>
Queue<T>::Queue() {
  _initEmptyQueue();
}

template <typename T>
Queue<T>::Queue(const Queue<T>& other) {
  // If other queue is empty, initialize with empty queue
  if (other.isEmpty()) {
    _initEmptyQueue();
    return;
  }

  int i = other._frontIndex;

  // Copy only active portion
  for (int j = 0; j < other._size; j++) {
    _queueArray[j] = other._queueArray[i];

    i = (i + 1) % MAX_QUEUE_SIZE;
  }

  _frontIndex = 0;
  _rearIndex = other._size - 1;
  _size = other._size;
}

template <typename T>
void Queue<T>::enqueue(const T& elem) {
  if (isFull()) {
    throw QueueOverflowException("Queue is already full! Cannot insert another element in queue");
  }

  _rearIndex = (_rearIndex + 1) % MAX_QUEUE_SIZE;
  _queueArray[_rearIndex] = elem;

  if (_size == 0) _frontIndex = _rearIndex;

  _size++;
}

template <typename T>
T Queue<T>::dequeue() {
  if (isEmpty()) {
    throw QueueEmptyException("Queue is empty! Cannot remove element from queue!");
  }

  T removedElem = _queueArray[_frontIndex];

  _queueArray[_frontIndex] = T();
  _frontIndex = (_frontIndex + 1) % MAX_QUEUE_SIZE;

  _size--;

  if (_size == 0) {
    // Commenting this will still work because enqueue handles the case
    // where front index might be inconsistent but to ensure a consistent
    // empty state of the queue, this is used
    _initEmptyQueue();
  }

  return removedElem;
}

template <typename T>
const T& Queue<T>::front() const {
  if (isEmpty()) {
    throw QueueEmptyException("Queue is empty! Cannot get front (first) element in the queue!");
  }
  return _queueArray[_frontIndex];
}

template <typename T>
const T& Queue<T>::rear() const {
  if (isEmpty()) {
    throw QueueEmptyException("Queue is empty! Cannot get rear (last) element in the queue!");
  }
  return _queueArray[_rearIndex];
}

template <typename T>
bool Queue<T>::isEmpty() const {
  return _size == 0;
}

template <typename T>
bool Queue<T>::isFull() const {
  return _size == MAX_QUEUE_SIZE;
}

template <typename T>
const unsigned& Queue<T>::size() const {
  return _size;
}

template <typename T>
std::ostream& operator << (std::ostream& os, const Queue<T>& queue) {
  os << "\nFull Queue:\n";
  os << "[" << queue._queueArray[0];
  for (int i = 1; i < MAX_QUEUE_SIZE; i++) {
    os << ", " << queue._queueArray[i];
  }
  os << "]\n";

  os << "\nCorrect Queue:\n";
  
  if (queue._size == 0) {
    os << "[]";
  } else {
    os << "[" << queue._queueArray[queue._frontIndex];
    int i = queue._frontIndex+1;

    for (int j = 1; j < queue._size; j++) {
      os << ", " << queue._queueArray[i];
      i = (i+1) % MAX_QUEUE_SIZE;
    }

    os << "]\n";
  }

  os << "\nDebug Info:";
  os << "\nFront index: " << queue._frontIndex << ", Rear Index = " << queue._rearIndex << ", Size = " << queue._size <<  std::endl;

  return os;
}