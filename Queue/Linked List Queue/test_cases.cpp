#include <iostream>
#include <cassert>
#include "Queue.hpp"

using namespace std;

void assert_notice(const char* methodName, bool passed) {
  cout << "\n" << methodName << " " << (passed? "passed" : "failed") << "." << std::flush;
}

void test_queue_enequeue() {
  Queue<int> myQueue;

  assert(myQueue.size() == 0);

  myQueue.enqueue(39);
  myQueue.enqueue(91);

  assert(myQueue.size() == 2);
  assert(myQueue.front() == 39);

  assert_notice(__func__, true);
}

void test_queue_dequeue() {
  Queue<int> q;

  assert(q.isEmpty() == true);

  try {
    q.dequeue();
    assert_notice(__func__, false);
    assert(false);
  } catch (const QueueEmptyException& e) {}

  q.enqueue(10);
  q.enqueue(20);
  q.enqueue(30);
  q.enqueue(40);
  q.enqueue(50);

  assert(q.size() == 5);
  assert(q.front() == 10);

  for (int i = 10; i <= 50; i += 10) {
    assert(q.dequeue() == i);
  }

  assert_notice(__func__, true);
}

void test_queue_front() {
  Queue<int> q;

  try {
    q.front();
    assert_notice(__func__, false);
    assert(false);
  } catch (const QueueEmptyException& e) {}

  for (int i = 0; i < 1000; i++) {
    q.enqueue(i);
  }

  for (int i = 999; i <= 0; i--) {
    assert(q.front() == i);
    q.dequeue();
  }
  
  assert_notice(__func__, true);
}

void test_queue_is_empty() {
  Queue<int> q;

  assert(q.isEmpty());

  q.enqueue(93);
  q.enqueue(31);

  assert(!q.isEmpty());
  q.dequeue();
  assert(!q.isEmpty());
  q.dequeue();
  assert(q.isEmpty());

  assert_notice(__func__, true);
}

void test_queue_size() {
  Queue<int> q;

  assert(q.size() == 0);

  for (int i = 0; i < 100; i++) {
    q.enqueue(i);
    assert(q.size() == i+1);
  }

  for (int i = 0; i < 100; i++) {
    assert(q.size() == 100-i);
    q.dequeue();
  }
  assert(q.size() == 0);
  assert_notice(__func__, true);
}

void test_queue_copy_constructor() {
  Queue<int> q1;

  q1.enqueue(10);
  q1.enqueue(20);
  q1.enqueue(30);
  q1.enqueue(40);

  Queue<int> q2(q1);

  assert(q2.size() == q1.size());
  assert(q2.front() == q1.front());

  q1.enqueue(50);

  assert(q1.size() == 5);
  assert(q2.size() == 4);

  q1.dequeue();

  assert(q1.front() == 20);
  assert(q2.front() == 10);

  assert_notice(__func__, true);
}

int main() {

  test_queue_enequeue();
  test_queue_dequeue();
  test_queue_front();
  test_queue_is_empty();
  test_queue_size();
  test_queue_copy_constructor();

  cout << "\n\nAll test cases passed...\n";

  return 0;
}