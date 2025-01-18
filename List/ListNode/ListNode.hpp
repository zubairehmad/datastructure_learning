#pragma once

// Defines a standard structure to be used for single ListNodes i.e, 
// only next pointer. It is templatized to ensure flexibility
template <typename T> struct ListNode {

  ListNode<T> *next;
  T elem;

  ListNode(T _elem = T(), ListNode<T> *_next = nullptr)
      : elem(_elem), next(_next) {}
};

// Defines a standard structure to be used for double ListNodes i.e,
// next and prev pointer. It is templatized to ensure flexibility
template <typename T> struct DoubleListNode {

  DoubleListNode<T> *next;
  DoubleListNode<T> *prev;
  T elem;

  DoubleListNode(T _elem = T(), DoubleListNode<T> *_next = nullptr,
                 DoubleListNode<T> *_prev = nullptr)
      : elem(_elem), next(_next), prev(_prev) {}
};