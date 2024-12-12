#include "List.hpp"
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

void assert_notice(std::string name, bool passed) {
  std::cout << "\n" << name << " " << (passed ? "passed" : "failed") << ".\n";
}

void test_list_create() {
  List<int> list;
  // Expectation: After newly creating length should be zero
  assert(list.length() == 0);
  assert_notice(__func__, true);
}

void test_list_add() {
  List<int> list;
  list.add(329);
  // Expectation: After adding a new element size should be increased.
  assert(list.length() == 1);
  // Expectation: As current will be 0 after newly created list, 329 should be
  // returned by get()
  assert(list.get() == 329);
  assert_notice(__func__, true);
}

void test_list_get() {
  List<int> list;
  try {
    // Expectation: This method should throw exception (UninitializedListError)
    // when called on empty or uninitialized list. Here the list is empty
    list.get();
    assert_notice(__func__, false);
    assert(false);
  } catch (const UninitializedListError &e) {}
  list.add(329);
  // Expectation: Current is 0 for newly created list. So 329 should be returned
  assert(list.get() == 329);
  list.add(9321);
  // Expectation: Add method adds the given element to current location. Hence
  // at 9321 should reside at 0 index.
  assert(list.get() == 9321);
  assert_notice(__func__, true);
}

void test_list_remove() {
  List<int> list;
  try {
    // Expectation: Remove method throws exception (UninitializedListError) when
    // called on empty list. Here the list is empty
    list.remove();
    assert_notice(__func__, false);
    assert(false);
  } catch (const UninitializedListError &e) {}

  list.add(59);
  list.add(39);

  // Expectation: After adding two elements size should be 2
  assert(list.length() == 2);

  list.remove();

  // Expectation: After removing one element size should be 1
  assert(list.length() == 1);
  // Expectation: As element is removed from current location, so 39 should be
  // removed (it was at 0). Which lefts only 59 in list so get() should return
  // it
  assert(list.get() == 59);

  assert_notice(__func__, true);
}

void test_list_length() {
  List<int> list;
  // Expectation: Length of empty list should be zero
  assert(list.length() == 0);

  list.add(39);
  list.add(320);

  // Expectation: After adding two elements length should be 2
  assert(list.length() == 2);

  list.remove();

  // Expectation: After removing one element size should be 1
  assert(list.length() == 1);

  list.add(329);
  list.add(3295832);
  list.add(328);
  list.add(932);

  list.next();
  list.back();
  list.start();
  list.end();

  // Expectation: After adding 4 more elements, length should be 5
  // And next(), back(), start() and end() shouldn't influence length of list
  assert(list.length() == 5);
  assert_notice(__func__, true);
}

void test_list_next() {
  List<int> list;

  try {
    // Expectation: next throws exception (UninitializedListError) when called
    // on empty list. Here it is empty.
    list.next();
    assert_notice(__func__, false);
    assert(false);
  } catch (const UninitializedListError &e) {}

  // Expectation: List is empty so length should be 0
  assert(list.length() == 0);

  list.add(39);
  list.add(49);
  list.add(59);

  // Expectation: The current implementation of list adds number in a stack-like
  // structure, so 59 should reside at index 0 (current)
  assert(list.get() == 59);

  list.next();

  // Expectation: Following the way, next element should be 49
  assert(list.get() == 49);

  list.next();

  // Expectation: And last element should be 39
  assert(list.get() == 39);

  // Expectation: If current is already at last then next doesn't move forward
  // and returns false So get() should return 39 and next() should return false
  assert(list.next() == false);
  assert(list.get() == 39);

  assert_notice(__func__, true);
}

void test_list_back() {

  List<int> list;

  try {
    // Expectation: This method also throws exception (UninitializedList) when
    // called on empty list. Here it is empty.
    list.back();
    assert_notice(__func__, false);
    assert(false);
  } catch (const UninitializedListError &e) {}

  list.add(931);

  // Expectation: As current is 0 (already at start) so back() should return
  // false.
  assert(list.back() == false);
  // Expectation: There is only one element i.e, 931. get() should return 931
  assert(list.get() == 931);

  list.add(59);
  // Expectation: Again current is already at start, so back should return
  // false.
  assert(list.back() == false);

  // Expectation: List adds element in a stack like way, where each element
  // inserted is placed at current and already present element is pushed
  // further. Following this, 59 should be returned by get() when current is 0.
  assert(list.get() == 59);

  list.add(48);
  list.add(79);

  list.end();
  // Expectation: As the list is at end, and list has size of 2. So back should
  // move one current one step backward.
  assert(list.back() == true);
  // Expectation: On second last index, 59 is present so it should be returned.
  assert(list.get() == 59);

  list.back();
  list.back();

  // Expectation: As the list is already at start, so back should return false
  assert(list.back() == false);
  // Expectation: As stated above, due to stack like insertion of list elements
  // by method add, So last added element 79 should be at top (start of the
  // list).
  assert(list.get() == 79);

  assert_notice(__func__, true);
}

void test_list_start() {

  List<int> list;

  try {
    // Expectation: Start throws exception (UninitializedListError) when called
    // on empty list. Here it is empty.
    list.start();
    assert_notice(__func__, false);
    assert(false);
  } catch (const UninitializedListError &e) {}

  list.add(49);

  // Expectation: After adding a single element, length should be 1
  assert(list.length() == 1);

  list.start();

  // Expectation: Because the current is at 0 (list only has 1 element), get()
  // should return 49
  assert(list.get() == 49);

  list.add(392);
  list.add(99);
  list.add(482);

  list.next();
  list.next();

  // Expectation: Because 482 is at start, so 392 should be 3rd index, two
  // next() away (which are called) So get() should return 392
  assert(list.get() == 392);

  list.back();

  // Expectation: According to order of insertion, 99 is behind 392, so after
  // back(), get() should return it.
  assert(list.get() == 99);

  list.start();
  list.start();
  list.start();

  // Expectation: While a single start is enough, multiple starts shouldn't
  // cause any problem for going to the start of the list. 482 is at start so it
  // should be returned.
  assert(list.get() == 482);

  assert_notice(__func__, true);
}

void test_list_end() {

  List<int> list;

  try {
    // Expectation: end() also throws exception (UninitializedListError) when
    // called on empty list. Here it is empty.
    list.end();
    assert_notice(__func__, false);
    assert(false);
  } catch (const UninitializedListError &e) {}

  // Expectation: List is empty, so length should be zero
  assert(list.length() == 0);

  list.add(392);
  list.add(31);
  list.add(99);

  // Expectation: As 3 elements are added so length should be 3.
  assert(list.length() == 3);
  // Expectation: Following stack like insertion by add(), 99 should be at top
  // (start of list). The current is zero by default so 99 should be returned by
  // get()
  assert(list.get() == 99);

  list.end();

  // Expectation: Following insertion order, 392 should be at last, so get()
  // should return it
  assert(list.get() == 392);

  list.add(291);

  list.end();

  // Expectation: Again following stack-like insertion, 392 should still be at
  // end.
  assert(list.get() == 392);

  list.end();
  list.remove();

  // Expectation: Because when remove is called and current is at end, it is
  // also updated Along with size (both decrement by 1). So at current 2nd last
  // element which is 291 should reside.
  assert(list.get() == 291);

  list.remove();

  // Expectation: After removing again, 3rd last element (391) should be pointed
  // by current.
  assert(list.get() == 31);

  assert_notice(__func__, true);
}

void test_list_update() {
  List<int> list;

  try {
    // Expectation: update() throws an exception (UninitializedListError) when
    // called on empty list. And here it is empty.
    list.update(39);
    assert_notice(__func__, false);
    assert(false);
  } catch (const UninitializedListError &e) {}

  list.add(1);
  // Expectation: After adding a single element in empty list, length should be
  // 1 and current should be 0
  assert(list.get() == 1);
  assert(list.length() == 1);

  list.add(2);
  list.add(3);
  list.add(4);
  list.add(5);

  // Expectation: According to addition sequence, 5 should be at start.
  assert(list.get() == 5);

  list.update(9);

  // Expectation: 5 is updated to 9, so it should reflect it.
  assert(list.get() == 9);

  list.end();
  list.update(391);
  // Expectation: As the element is updated to 391, so it should reflect it.
  assert(list.get() == 391);

  list.remove();
  list.remove();
  list.remove();
  list.remove();
  list.remove();

  try {
    // Expectation: All elements have been removed and list is empty. Calling
    // update() should throw exception
    list.update(39);
    assert_notice(__func__, false);
    assert(false);
  } catch (const UninitializedListError &e) {}

  assert_notice(__func__, true);
}

void test_list_find() {
  List<int> list;

  // Expectation: The list is empty, nothing is present here.
  assert(list.find(93) == false);

  list.add(1);
  list.add(2);
  list.add(3);
  list.add(4);
  list.add(5);

  // Expectation: There is no 9 in the list. So false should be returned.
  assert(list.find(9) == false);
  // Expectation: The 4 is present in the list, so true should be returned. And
  // current should be moved to the index where 4 is located
  assert(list.find(4) == true);
  // Expectation: 7 is also not present, so false should be returned.
  assert(list.find(7) == false);

  // Expectation: As the current was moved to location where element was 4, so
  // get() should return 4
  assert(list.get() == 4);

  assert_notice(__func__, true);
}

void test_list_copy_constructor() {

  int arr[7] = {5, 6, 4, 1, 2, 4, 6};

  List<int> list;

  for (int i = 0; i < 7; i++) {
    list.add(arr[i]);
    // Expectation: The newly added element will always be at start, so it
    // should be returned by get()
    assert(list.get() == arr[i]);
  }

  // Expectation: As 7 elements are added, so lenght should be 7.
  assert(list.length() == 7);

  List<int> anotherList = list;

  anotherList.end();

  for (int i = 0; i < 7; i++) {
    // Expectation: As anotherList is initialized from list, so elements in
    // anotherList should be same as in list object
    assert(anotherList.get() == arr[i]);
    if (i != 6) {
      // Expectation: The current is at start, so back should move current
      // backwards and return true
      assert(anotherList.back() == true);
    } else {
      // Expectation: The current is already at start, so back() should return
      // false
      assert(anotherList.back() == false);
    }
  }

  // Expectation: As anotherList is initialized from list, length of both obj
  // should be same.
  assert(anotherList.length() == list.length());

  assert_notice(__func__, true);
}

void test_list_stream_insertion_operator() {

  List<int> list;
  std::ostringstream output;

  output << list;

  // Expectation: For empty list, [] should be output
  assert(output.str() == "[]");

  output.str("");

  list.add(93);
  list.add(39);
  list.add(9);

  output << list;

  // Expectation: For non-empty list, output should be in the specified format
  assert(output.str() == "[9, 39, 93]");
  // Expectation: Because the current is not moved, so it should be at 0
  assert(list.get() == 9);

  list.add(49);
  list.end();

  output.str("");
  output << list;

  // Expectation: Even if the current is at end, the output should always show
  // full list
  assert(output.str() == "[49, 9, 39, 93]");

  assert_notice(__func__, true);
}

int main() {

  test_list_create();
  test_list_add();
  test_list_length();
  test_list_get();
  test_list_remove();
  test_list_next();
  test_list_back();
  test_list_start();
  test_list_end();
  test_list_update();
  test_list_find();
  test_list_copy_constructor();
  test_list_stream_insertion_operator();

  std::cout << "\nAll assertions are correct\n";
  return 0;
}