#pragma once

#include "../Exceptions/List_Exceptions.hpp"
#include <ostream>

struct ListNode {

  ListNode(int _value = 0, ListNode *_next = nullptr, ListNode *_prev = nullptr)
      : value(_value), next(_next), prev(_prev) {}

  int value;
  ListNode *next;
  ListNode *prev;
};

class List {
private:
  ListNode *head;            // It is the start (head) of the list
  mutable ListNode *current; // It is the current pointer
  int size;                  // Size of the list

  mutable int getBackMethodIterations; // This method holds the iterations done by back method.

public:
  List();

  // A copy constructor to ensure deep copy
  List(const List &);

  // Returns the size of the list
  int length() const;

  // Returns the value at current index
  int get() const;

  // Adds the given element after the current element, and moves current pointer
  // to newly added element
  void add(const int &);

  // Removes the current element from the list
  void remove();

  // Updates the current element with provided value
  void update(const int &);

  // Moves the current pointer to the start of the list, throws exception if
  // list doesn't have any elements
  void start() const;

  // Moves the current pointer to the end of the list, throws exception if list
  // doesn't have any elements
  void end() const;

  // Moves the current pointer/marker 1 step forward. If it can't move next
  // (i.e, at the end of list) then false is returned otherwise true. If list
  // doesn't have any elements, then exception is thrown
  bool next() const;

  // Moves the current pointer/marker 1 step backward. If it can't move backward
  // (i.e, at the start of list) then false is returned otherwise true. If list
  // doesn't have any elements, then exception is thrown
  bool back() const;

  // It moves the current marker to index at which, the given element is present
  // It returns true if element is present, otherwise false
  bool find(const int &) const;

  // It returns the total iterations taken back() method (or getPreviousElement())
  int getBackMethodIterationCount() const;

  friend std::ostream &operator<<(std::ostream &, const List &);

  // Destrutor to deallocate the allocated memory
  ~List();
};

inline List::List() : head(nullptr), current(nullptr), size(0), getBackMethodIterations(0) {}

inline List::List(const List &other) : getBackMethodIterations(0) {

  if (other.size == 0) {
    head = current = nullptr;
    size = 0;
    return;
  }

  head = new ListNode(other.head->value);
  current = head;
  ListNode *otherTrav = other.head->next;

  while (otherTrav != nullptr) {
    ListNode *temp = new ListNode(otherTrav->value);
    temp->prev = current;
    current->next = temp;
    current = current->next;
    otherTrav = otherTrav->next;
  }

  // Ensure that the sizes of both lists are identical
  size = other.size;

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
    head = new ListNode();
    head->value = value;
    current = head;
  } else {
    ListNode *newElem = new ListNode(value);

    newElem->next = current->next;
    newElem->prev = current;

    // If new element is not at the end then update prev pointer of next element
    // So that it points correctly to previous new element.
    if (newElem->next != nullptr) {
      newElem->next->prev = newElem;
    }

    current->next = newElem;
    current = current->next;
  }
  size++;
}

inline void List::remove() {

  if (size == 0) {
    throw UninitializedListError(
        "There is no element in the list! Cannot remove current element...");
  }

  ListNode *temp = current;

  if (size == 1) {
    // If there is only one element, then simply set current
    // and head to nullptr
    current = nullptr;
    head = nullptr;
  } else if (current == head) {
    // If current is at head, then move the head to next element, and remove
    // previous by setting it to nullptr
    head = head->next;
    head->prev = nullptr;
    current = head;
  } else {
    // If current is in middle, then skip it in the `next` chain
    current->prev->next = current->next;

    if (current->next == nullptr) {
      // If current is at end, then move the current to previous element
      current = current->prev;
    } else {
      // Move the current to next element, and skip it in the `prev` chain also.
      current->next->prev = current->prev;
      current = current->next;
    }
  }

  delete temp;
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
                                 "backwards/to previous element...");
  }

  getBackMethodIterations = 0;

  if (current == head)
    return false;

  current = current->prev;
  getBackMethodIterations++;

  return true;
}

inline bool List::find(const int &value) const {
  ListNode *temp = head;

  for (int i = 0; i < size; i++) {
    if (temp->value == value) {
      // Move current pointer to the location at which, value is found
      current = temp;
      return true;
    }
    temp = temp->next;
  }

  return false;
}

inline int List::getBackMethodIterationCount() const {
  return getBackMethodIterations;
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
    // Ensure that current pointer of the list doesn't change
    list.current = temp;
  }

  return out;
}

inline List::~List() {
  if (head != nullptr) {
    current = head;
    while (current != nullptr) {
      ListNode *temp = current;
      current = current->next;
      delete temp;
    }
    head = nullptr;
  }
}