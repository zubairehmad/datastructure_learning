#include <iostream>
#include <cassert>
#include "Queue.hpp"

using namespace std;

// Helper function for reporting test results.
void assert_notice(const char* methodName, bool passed) {
  cout << "\n" << methodName << " " << (passed ? "passed" : "failed") << "." << std::flush;
}

// Test enqueue: basic enqueue and verifying size, front, and rear.
void test_queue_enqueue() {
  Queue<int> q;
  assert(q.size() == 0);

  q.enqueue(39);
  q.enqueue(91);
  assert(q.size() == 2);
  assert(q.front() == 39);
  assert(q.rear() == 91);

  assert_notice(__func__, true);
}

// Test dequeue: including exception on empty queue and proper order.
void test_queue_dequeue() {
  Queue<int> q;
  assert(q.isEmpty());

  // Dequeue from an empty queue should throw an exception.
  try {
    q.dequeue();
    assert_notice(__func__, false);
    assert(false); // Should never reach here.
  } catch (const QueueEmptyException& e) {
    // Expected.
  }

  // Enqueue several elements and then dequeue them in order.
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
  assert(q.isEmpty());

  assert_notice(__func__, true);
}

// Test front: verifying that front returns the correct element and throws when empty.
void test_queue_front() {
  Queue<int> q;

  try {
    q.front();
    assert_notice(__func__, false);
    assert(false);
  } catch (const QueueEmptyException& e) {
    // Expected.
  }

  q.enqueue(100);
  assert(q.front() == 100);
  q.enqueue(200);
  assert(q.front() == 100);
  q.dequeue();
  assert(q.front() == 200);

  assert_notice(__func__, true);
}

// Test rear: verifying that rear returns the correct element and throws when empty.
void test_queue_rear() {
  Queue<int> q;

  try {
    q.rear();
    assert_notice(__func__, false);
    assert(false);
  } catch (const QueueEmptyException& e) {
    // Expected.
  }

  q.enqueue(5);
  assert(q.rear() == 5);
  q.enqueue(15);
  assert(q.rear() == 15);
  q.dequeue(); // removes 5, leaving 15.
  assert(q.rear() == 15);
  q.enqueue(25);
  assert(q.rear() == 25);

  assert_notice(__func__, true);
}

// Test isEmpty: ensuring that the queue accurately reports when it is empty.
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

// Test size: verifying that size updates correctly on enqueue and dequeue.
void test_queue_size() {
  Queue<int> q;
  assert(q.size() == 0);

  for (int i = 0; i < 100; i++) {
    q.enqueue(i);
    assert(q.size() == static_cast<unsigned>(i + 1));
  }
  for (int i = 0; i < 100; i++) {
    assert(q.size() == static_cast<unsigned>(100 - i));
    q.dequeue();
  }
  assert(q.size() == 0);

  assert_notice(__func__, true);
}

// Test copy constructor: verifies that the new queue has the same elements in order,
// and that further modifications to one do not affect the other.
void test_queue_copy_constructor() {
  Queue<int> q1;
  q1.enqueue(10);
  q1.enqueue(20);
  q1.enqueue(30);
  q1.enqueue(40);

  Queue<int> q2(q1);

  assert(q2.size() == q1.size());
  assert(q2.front() == q1.front());

  // Modify original queue; copy should remain unchanged.
  q1.enqueue(50);
  assert(q1.size() == 5);
  assert(q2.size() == 4);
  q1.dequeue();
  assert(q1.front() == 20);
  assert(q2.front() == 10);

  assert_notice(__func__, true);
}

// Test overflow: ensure that attempting to enqueue more than MAX_QUEUE_SIZE elements throws an exception.
void test_queue_overflow() {
  Queue<int> q;
  for (int i = 0; i < MAX_QUEUE_SIZE; i++) {
    q.enqueue(i);
  }
  try {
    q.enqueue(101);
    assert_notice(__func__, false);
    assert(false);
  } catch (const QueueOverflowException& e) {
    // Expected exception.
  }

  assert_notice(__func__, true);
}

// Test wrap-around behavior: dequeue some elements, then enqueue more to force wrap-around.
void test_queue_wrap_around() {
  Queue<int> q;
  // Fill the queue completely.
  for (int i = 0; i < MAX_QUEUE_SIZE; i++) {
    q.enqueue(i);
  }
  // Dequeue a few elements.
  const int dequeueCount = 10;
  for (int i = 0; i < dequeueCount; i++) {
    assert(q.dequeue() == i);
  }
  // Enqueue additional elements which will be placed at the beginning of the array.
  for (int i = MAX_QUEUE_SIZE; i < MAX_QUEUE_SIZE + dequeueCount; i++) {
    q.enqueue(i);
  }
  // After wrap-around, front should be 'dequeueCount' and rear should be MAX_QUEUE_SIZE + dequeueCount - 1.
  assert(q.front() == dequeueCount);
  assert(q.rear() == MAX_QUEUE_SIZE + dequeueCount - 1);

  // Optionally, verify the order of all elements.
  for (int i = dequeueCount; i < MAX_QUEUE_SIZE + dequeueCount; i++) {
    assert(q.dequeue() == i);
  }
  assert(q.isEmpty());

  assert_notice(__func__, true);
}

// Main function to run all tests.
int main() {
  test_queue_enqueue();
  test_queue_dequeue();
  test_queue_front();
  test_queue_rear();
  test_queue_is_empty();
  test_queue_size();
  test_queue_copy_constructor();
  test_queue_overflow();
  test_queue_wrap_around();

  cout << "\n\nAll tests completed.\n";
  return 0;
}
