#pragma once

#include <stdexcept>

template <typename T> class List {
private:
  T *list;     // It is the array which will store all the list elements
  int current; // It is the current marker
  int size;    // Size of the list

public:
  List();

  // A copy constructor to ensure deep copy
  List(const List<T> &);

  // Returns the size of the list
  int length() const;

  // Get the index at which, the current is pointing
  size_t getCurrentIndex() const;

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
  void start();

  // Moves the current pointer to the end of the list, throws exception if list
  // don't have any elements
  void end();

  // Moves the current pointer/marker to specified index. If the index is out of
  // bounds then exception is thrown
  void moveTo(size_t);

  // Moves the current pointer/marker 1 step forward. If it can't move next
  // (i.e, at the end of list) then false is returned otherwise true. If list
  // don't have any elements, then exception is thrown
  bool next();

  // Moves the current pointer/marker 1 step backward. If it can't move backward
  // (i.e, at the start of list) then false is returned otherwise true. If list
  // don't have any elements, then exception is thrown
  bool back();

  // It moves the current marker to index at which, the given element is present
  // It returns true if element is present, otherwise false
  bool find(const T &);

  // For reading only
  const T &operator[](size_t) const;

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

template <typename T> size_t List<T>::getCurrentIndex() const {
  return current;
}

template <typename T> T List<T>::get() const {
  if (current == -1) {
    throw std::runtime_error("The list don't have any elements!");
  }
  return list[current];
}

template <typename T> void List<T>::add(const T &elem) {
  if (list == nullptr) {
    // If list is has no element, then simply create a new one.
    list = new T[1];
    list[0] = elem;
    current = 0;
  } else {
    // Store current list in temporary array
    T *temp = list;

    // Reallocate list with increased size
    list = new T[size + 1];

    int i, j;
    i = j = 0;

    while (i < size) {
      if (i == current) {
        list[j] = elem;
        ++j;
      }
      list[j] = temp[i];
      ++i;
      ++j;
    }

    // Free the memory
    delete[] temp;
  }

  // Increment the size
  size++;
}

template <typename T> void List<T>::remove() {

  if (list == nullptr)
    throw std::runtime_error("The list is empty! Cannot remove element!");

  if (size == 1) {
    delete[] list;
    list = nullptr;
    current = -1;
  } else {
    // Store current list in temp
    T *temp = list;

    // Reallocate list with decreased size
    list = new T[size - 1];

    int i, j;
    i = j = 0;

    while (i < size) {
      if (i == current) {
        ++i;
      }
      list[j] = temp[i];
      ++i;
      ++j;
    }
  }

  // Decrement size after removal
  --size;

  // If the current element was pointing at end, it should still point at end.
  if (current == size)
    --current;
}

template <typename T> void List<T>::update(const T &newValue) {
  if (current == -1)
    throw std::runtime_error("The list don't have any elements! Can't update current element!");
  list[current] = newValue;
}

template <typename T> void List<T>::start() {
  if (current == -1)
    throw std::runtime_error("The list don't have any elements! Can't move to start!");
  current = 0;
}

template <typename T> void List<T>::end() {
  if (current == -1)
    throw std::runtime_error("The list don't have any elements! Can't move to end!");
  current = size - 1;
}

template <typename T> void List<T>::moveTo(size_t index) {
  if (index < 0 || index > size - 1)
    throw std::out_of_range("The given index is out of range!");
  current = index;
}

template <typename T> bool List<T>::next() {

  if (current == -1)
    throw std::runtime_error("The list don't have any element! Can't move forward!");

  if (current == size - 1) {
    return false;
  } else {
    current += 1;
    return true;
  }
}

template <typename T> bool List<T>::back() {

  if (current == -1)
    throw std::runtime_error("The list don't have any element! Can't move backward!");

  if (current == 0) {
    return false;
  } else {
    current -= 1;
    return true;
  }
}

template <typename T> bool List<T>::find(const T &elem) {

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

template <typename T> const T &List<T>::operator[](size_t index) const {
  if (index < 0 || index > size - 1)
    throw std::out_of_range("Invalid index is given!");
  return list[index];
}

template <typename T> List<T>::~List() {
  if (list != nullptr) {
    // Free the memory allocated for list
    delete[] list;
  }
}