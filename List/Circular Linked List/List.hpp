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

  // Moves the current pointer/marker 1 step forward. If the pointer is at the end
  // of the list, then the method moves it to the start of the list
  void next() const;

  // Moves the current pointer/marker 1 step backward. If the pointer is at the start
  // of the list, then the method moves it to the end of the list
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

  // There is no previous element of head/start of list, so nullptr is returned
  if (current == head)
    return nullptr;

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

  while (otherTrav != nullptr) {
    ListNode *temp = new ListNode(otherTrav->value);
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
    delete head;
    head = nullptr;
  } else {
    ListNode *temp = current;

    if (current == head) {
      head = head->next;
      current = head;
    } else {
      ListNode *prev = getPreviousElement();
      prev->next = current->next;
      current = current->next == nullptr? head : current->next;
    }

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

inline void List::next() const {
  if (size == 0) {
    throw UninitializedListError(
        "There is no element in the list! Cannot move to next element...");
  }

  // Move to head if at the end
  current = current->next == nullptr? head : current->next;
}

inline void List::back() const {
  if (size == 0) {
    throw UninitializedListError("There is no element in the list! Cannot move "
                                 "backwards/to previous element...");
  }
  if (current == head) {
    // Move the current pointer to the end of the list
    end();
  } else {
    current = getPreviousElement();
  }
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
    list.start();
    out << "[" << list.get();
    while (list.current != nullptr) {
      out << ", " << list.get();
      list.current = list.current->next;
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