#pragma once

#include "../Exceptions/List_Exceptions.hpp"
#include <ostream>

struct ListNode {

  ListNode(int _value = 0, ListNode *_next = nullptr)
      : value(_value), next(_next) {}

  int value;
  ListNode *next;
};

class List {
private:
  ListNode *head;            // It is the start (head) of the list
  mutable ListNode *current; // It is the current pointer
  int size;                  // Size of the list

  ListNode *getPreviousElement() const;

public:
  List();

  // A copy constructor to ensure deep copy
  List(const List &);

  // Returns the size of the list
  int length() const;

  // Returns the value at current index
  int get() const;

  // Adds the given element to the current position in list.
  void add(const int &);

  // Removes the current element from the list
  void remove();

  // Updates the current element with provided value
  void update(const int &);

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
  bool find(const int &) const;

  friend std::ostream &operator<<(std::ostream &, const List &);

  // Destrutor to deallocate the allocated memory
  ~List();
};

inline ListNode *List::getPreviousElement() const {

  if (size == 0) {
    throw UninitializedListError(
        "There is no element in the list! Can't get previous element...");
  }

  ListNode *prevElem = head;
  while (prevElem->next != current) {
    prevElem = prevElem->next;
  }
  return prevElem;
}

inline List::List() : head(nullptr), current(nullptr), size(0) {}

inline List::List(const List &other) {
  head = new ListNode[other.size];
  size = other.size;
  current = head;

  ListNode *otherHead = other.head;

  for (int i = 0; i < size; i++) {
    current->value = otherHead->value;
    current = current->next;
    otherHead = otherHead->next;
  }

  // Current is by default at first element
  current = head;
}

inline int List::length() const { return size; }

inline int List::get() const {
  if (size == 0) {
    throw UninitializedListError("There is no element in the list! Can't get "
                                 "value of current element...");
  }
  return current->value;
}

inline void List::add(const int &value) {

  if (size == 0) {
    head = new ListNode[1];
    head->value = value;
    current = head;
  } else {
    ListNode *newElem = new ListNode(value);

    newElem->next = current->next;
    current->next = newElem;
    current = current->next;
  }
  size++;
}

inline void List::remove() {
  if (size == 0) {
    throw UninitializedListError(
        "There is no element in the list! Cannot remove current element...");
  } else if (size == 1) {
    current = nullptr;
    delete[] head;
  } else {
    ListNode *prev = getPreviousElement();
    ListNode *temp = current;

    prev->next = current->next;
    current = current->next;
    delete temp;
  }
  size--;
}

inline void List::update(const int &value) {
  if (size == 0) {
    throw UninitializedListError("There is no element in the list! Cannot "
                                 "update value of current element...");
  }
  current->value = value;
}

inline void List::start() const {
  if (size == 0) {
    throw UninitializedListError(
        "There is no element in the list! Cannot move to start...");
  }
  current = head;
}

inline void List::end() const {
  if (size == 0) {
    throw UninitializedListError(
        "There is no element in the list! Cannot move to end...");
  }
  while (current->next != nullptr) {
    current = current->next;
  }
}

inline bool List::next() const {
  if (size == 0) {
    throw UninitializedListError(
        "There is no element in the list! Cannot move to next element...");
  }

  if (current->next == nullptr)
    return false;

  current = current->next;
  return true;
}

inline bool List::back() const {
  if (size == 0) {
    throw UninitializedListError("There is no element in the list! Cannot move "
                                 "to backwards/previous element...");
  }

  if (current == head)
    return false;

  current = getPreviousElement();
  return true;
}

inline bool List::find(const int &value) const {
  ListNode *temp = head;

  for (int i = 0; i < size; i++) {
    if (temp->value == value) {
      return true;
    }
    temp = temp->next;
  }

  return false;
}

inline std::ostream &operator<<(std::ostream &out, const List &list) {

  if (list.length() == 0) {
    out << "[]";
  } else {
    ListNode *temp = list.current;
    list.start();
    out << "[" << list.get();
    while (list.next()) {
      out << ", " << list.get();
    }
    out << "]";
  }

  return out;
}

inline List::~List() {
  if (head != nullptr) {
    current = nullptr;
    delete[] head;
  }
}