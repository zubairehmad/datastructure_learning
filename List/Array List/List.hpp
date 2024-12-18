#pragma once

#include <ostream>
#include "../Exceptions/List_Exceptions.hpp"

template <typename T> class List {
private:
  T *list;     // It is the array which will store all the list elements
  mutable int current; // It is the current marker
  int size;    // Size of the list

  mutable int getBackMethodIterations; // This method holds the iterations done by back() method.

public:
  List();

  // A copy constructor to ensure deep copy
  List(const List<T> &);

  // Returns the size of the list
  int length() const;

  // Returns the value at current index
  T get() const;

  // Adds the given element to the current position in list.
  void add(const T &);

  // Removes the current element from the list
  void remove();

  // Updates the current element with provided value
  void update(const T &);

  // Moves the current pointer to the start of the list, throws exception if
  // list don't have any elements
  void start() const;

  // Moves the current pointer to the end of the list, throws exception if list
  // don't have any elements
  void end() const;

  // Moves the current pointer/marker 1 step forward. If it can't move next
  // (i.e, at the end of list) then false is returned otherwise true. If list
  // don't have any elements, then exception is thrown
  bool next() const;

  // Moves the current pointer/marker 1 step backward. If it can't move backward
  // (i.e, at the start of list) then false is returned otherwise true. If list
  // don't have any elements, then exception is thrown
  bool back() const;

  // It moves the current marker to index at which, the given element is present
  // It returns true if element is present, otherwise false
  bool find(const T &) const;

  // It returns the total iterations taken back() method (or getPreviousElement())
  int getBackMethodIterationCount() const;

  template <typename VAR>
  friend std::ostream& operator << (std::ostream&, const List<VAR>&);

  // Destrutor to deallocate the allocated memory
  ~List();
};

template <typename T> List<T>::List() : list(nullptr), current(-1), size(0) {}

template <typename T> List<T>::List(const List<T> &other) {

  size = other.size;

  list = new T[size];

  for (int i = 0; i < other.size; i++) {
    list[i] = other.list[i];
  }

  // Initalize current to the start of the list
  current = 0;
}

template <typename T> int List<T>::length() const {
  // Return the length/size of the list
  return size;
}

template <typename T> T List<T>::get() const {
  if (current == -1) {
    throw UninitializedListError("The list don't have any elements!");
  }
  return list[current];
}

template <typename T> void List<T>::add(const T &elem) {
  if (current == -1) {
    // If list is has no element, then simply create a new one.
    list = new T[1];
    list[0] = elem;
    current = 0;
  } else {
    // Store current list in temporary array
    T *temp = list;

    // Reallocate list with increased size
    list = new T[size + 1];

    int oldListIndex = 0;

    // Simply copy as long as oldListIndex < current
    // If it is equal then insert the element and
    // after that keep copying oldList at oldListIndex+1 in the new list.
    while (oldListIndex < size) {
      if (oldListIndex < current) {
        list[oldListIndex] = temp[oldListIndex];
      }
      if (oldListIndex == current) {
        list[oldListIndex] = elem;
      }
      if (oldListIndex >= current) {
        list[oldListIndex+1] = temp[oldListIndex];
      }
      ++oldListIndex;
    }

    // Free the memory
    delete[] temp;
  }

  // Increment the size
  size++;
}

template <typename T> void List<T>::remove() {

  if (current == -1)
    throw UninitializedListError("The list is empty! Cannot remove element!");

  if (size == 1) {
    delete[] list;
    list = nullptr;
    current = -1;
  } else {
    // Store current list in temp
    T *temp = list;

    // Reallocate list with decreased size
    list = new T[size - 1];

    int oldListIndex = 0;
    
    // Simply copy as long as oldListIndex < current
    // When oldListIndex == current then skip copying this time.
    // Afterwards, copy oldList at oldListIndex-1 in new list
    while (oldListIndex < size) {
      if (oldListIndex < current) {
        list[oldListIndex] = temp[oldListIndex];
      }
      if (oldListIndex > current) {
        list[oldListIndex-1] = temp[oldListIndex];
      }
      ++oldListIndex;
    }

    // Free temporary memory
    delete[] temp;

    // If the current element was pointing at end, it should still point at end.
    if (current == size-1)
      --current;
  }

  // Decrement size after removal
  --size;
}

template <typename T> void List<T>::update(const T &newValue) {
  if (current == -1)
    throw UninitializedListError("The list don't have any elements! Can't update current element!");
  list[current] = newValue;
}

template <typename T> void List<T>::start() const {
  if (current == -1)
    throw UninitializedListError("The list don't have any elements! Can't move to start!");
  current = 0;
}

template <typename T> void List<T>::end() const {
  if (current == -1)
    throw UninitializedListError("The list don't have any elements! Can't move to end!");
  current = size - 1;
}

template <typename T> bool List<T>::next() const {

  if (current == -1)
    throw UninitializedListError("The list don't have any element! Can't move forward!");

  if (current == size - 1) {
    return false;
  } else {
    ++current;
    return true;
  }
}

template <typename T> bool List<T>::back() const {

  if (current == -1)
    throw UninitializedListError("The list don't have any element! Can't move backward!");

  getBackMethodIterations = 0;

  if (current == 0) {
    return false;
  } else {
    --current;
    getBackMethodIterations++;
    return true;
  }
}

template <typename T> bool List<T>::find(const T &elem) const {

  for (int i = 0; i < size; i++) {
    if (list[i] == elem) {
      // If the element is present, then simply move the current pointer/marker
      // to this index.
      current = i;
      return true;
    }
  }
  // The given element is not present in the list
  return false;
}

template <typename T> std::ostream &operator<<(std::ostream &op, const List<T>& list) {
  if (list.length() == 0)
    op << "[]";
  else {
    int oldCurrent = list.current;
    list.start(); // Ensure full list is always shown
    op << "[" << list.get();

    while (list.next()) {
      op << ", " << list.get();
    }

    op << "]";
    // Ensure current doesn't change when using << operator for list output
    list.current = oldCurrent;
  }
  return op;
}

template<typename T> int List<T>::getBackMethodIterationCount() const {
  return getBackMethodIterations;
}

template <typename T> List<T>::~List() {
  if (list != nullptr) {
    // Free the memory allocated for list
    delete[] list;
  }
}
