#pragma once

#include "../Exceptions/List_Exceptions.hpp"
#include <ostream>

struct ListNode {

  ListNode(int _value = 0, ListNode *_next = nullptr)
      : value(_value), next((_next == nullptr)? this : _next) {}

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

  // Moves the current pointer/marker 1 step forward. If the current pointer is
  // at end, It moves to the start of the list
  void next() const;

  // Moves the current pointer 1 step backwards. If the current pointer is at
  // start, It moves it to the end of the list
  void back() const;

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

  // The previous element of head, in circular linked list is last element of the list.
  if (current == head) {
    this->end();
    ListNode* lastElem = current;
    current = head;
    return lastElem;
  }

  ListNode *prevElem = head;
  while (prevElem->next != current) {
    prevElem = prevElem->next;
  }
  return prevElem;
}

inline List::List() : head(nullptr), current(nullptr), size(0) {}

inline List::List(const List &other) {

  if (other.size == 0) {
    head = current = nullptr;
    size = 0;
    return;
  }

  head = new ListNode(other.head->value);
  current = head;
  ListNode *otherTrav = other.head->next;

  for (int i = 1; i < other.size; i++) {
    ListNode *temp = new ListNode(otherTrav->value);
    current->next = temp;
    current = current->next;
    otherTrav = otherTrav->next;
  }

  // In circular linked list, `next` element after the last is the `head` element
  current->next = head;

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
  
  ListNode * temp = current;

  if (size == 1) {
    current = nullptr;
    head = nullptr;
  } else if (current == head) {
    // The previous element of head node is the last node
    ListNode* prev = getPreviousElement();
    head = head->next;
    current = head;
    // Ensure the previous element (aka last node) is correctly pointing to valid head node
    prev->next = head;
  } else {
    ListNode *prev = getPreviousElement();
    prev->next = current->next;
    current = (current->next == head) ? prev : current->next;
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
  while (current->next != head) {
    current = current->next;
  }
}

inline void List::next() const {
  if (size == 0) {
    throw UninitializedListError(
        "There is no element in the list! Cannot move to next element...");
  }

  current = current->next;
}

inline void List::back() const {
  if (size == 0) {
    throw UninitializedListError("There is no element in the list! Cannot move "
                                 "backwards/to previous element...");
  }

  if (current == head)
    this->end();
  else
    current = getPreviousElement();
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

inline std::ostream &operator<<(std::ostream &out, const List &list) {

  if (list.length() == 0) {
    out << "[]";
  } else {
    ListNode *temp = list.current;
    list.current = list.head;
    out << "[" << list.get();
    while (list.current->next != list.head) {
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