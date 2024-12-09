#include "List.hpp"
#include <cassert>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

void assert_notice(std::string name, bool passed) {
  std::cout << "\n" << name << " " << (passed ? "passed" : "failed") << ".\n";
}

void test_list_create() {
  List<int> list;
  assert(list.length() == 0);
  assert_notice(__func__, true);
}

void test_list_add() {
  List<int> list;
  list.add(329);
  assert(list.length() == 1);
  assert(list.get() == 329);
  assert_notice(__func__, true);
}

void test_list_get() {
  List<int> list;
  try {
    list.get();
    assert_notice(__func__, false);
    assert(false);
  } catch (const UninitializedListError &e) {
    assert(true);
  }
  list.add(329);
  assert(list.get() == 329);
  list.add(9321);
  assert(list.get() == 9321);
  assert_notice(__func__, true);
}

void test_list_remove() {
  List<int> list;
  try {
    list.remove();
    assert_notice(__func__, false);
    assert(false);
  } catch (const UninitializedListError &e) {
    assert(true);
  }

  list.add(59);
  list.add(39);

  assert(list.length() == 2);

  list.remove();

  assert(list.length() == 1);
  assert(list.get() == 59);

  assert_notice(__func__, true);
}

void test_list_length() {
  List<int> list;
  assert(list.length() == 0);

  list.add(39);
  list.add(320);

  assert(list.length() == 2);

  list.remove();

  assert(list.length() == 1);

  list.add(329);
  list.add(3295832);
  list.add(328);
  list.add(932);

  list.next();
  list.back();
  list.start();
  list.end();

  assert(list.length() == 5);
  assert_notice(__func__, true);
}

void test_list_next() {
  List<int> list;

  try {
    list.next();
    assert_notice(__func__, false);
    assert(false);
  } catch (const UninitializedListError &e) {
    assert(true);
  }

  assert(list.length() == 0);

  list.add(39);
  list.add(49);
  list.add(59);

  assert(list.get() == 59);

  list.next();

  assert(list.get() == 49);

  list.next();

  assert(list.get() == 39);

  list.next();

  assert(list.get() == 39);

  assert_notice(__func__, true);
}

void test_list_back() {

  List<int> list;

  try {
    list.back();
    assert_notice(__func__, false);
    assert(false);
  } catch (const UninitializedListError &e) {
  }

  list.add(931);
  assert(list.back() == false);
  assert(list.get() == 931);

  list.add(59);
  assert(list.back() == false);
  assert(list.get() == 59);

  list.add(48);
  list.add(79);

  list.end();
  assert(list.back() == true);
  assert(list.get() == 59);

  list.back();
  list.back();

  assert(list.back() == false);
  assert(list.get() == 79);

  assert_notice(__func__, true);
}

void test_list_start() {

  List<int> list;

  try {
    list.start();
    assert_notice(__func__, false);
    assert(false);
  } catch (const UninitializedListError &e) {
  }

  list.add(49);

  assert(list.length() == 1);

  list.start();

  assert(list.get() == 49);

  list.add(392);
  list.add(99);
  list.add(482);

  list.next();
  list.next();

  assert(list.get() == 392);

  list.back();

  assert(list.get() == 99);

  list.start();
  list.start();
  list.start();

  assert(list.get() == 482);

  assert_notice(__func__, true);
}

void test_list_end() {

  List<int> list;

  try {
    list.end();
    assert_notice(__func__, false);
    assert(false);
  } catch (const UninitializedListError &e) {
  }

  assert(list.length() == 0);

  list.add(392);
  list.add(31);
  list.add(99);

  assert(list.length() == 3);
  assert(list.get() == 99);

  list.end();

  assert(list.get() == 392);

  list.add(291);

  list.end();

  assert(list.get() == 392);

  list.end();
  list.remove();

  assert(list.get() == 291);

  list.remove();

  assert(list.get() == 31);

  assert_notice(__func__, true);
}

void test_list_update() {
  List<int> list;

  try {
    list.update(39);
    assert_notice(__func__, false);
    assert(false);
  } catch (const UninitializedListError &e) {
  }

  list.add(1);
  assert(list.get() == 1);
  assert(list.length() == 1);

  list.add(2);
  list.add(3);
  list.add(4);
  list.add(5);

  assert(list.get() == 5);

  list.update(9);

  assert(list.get() == 9);

  list.end();
  list.update(391);
  assert(list.get() == 391);

  list.remove();
  list.remove();
  list.remove();
  list.remove();
  list.remove();

  try {
    list.update(39);
    assert_notice(__func__, false);
    assert(false);
  } catch (const UninitializedListError &e) {
  }

  assert_notice(__func__, true);
}

void test_list_find() {
  List<int> list;

  assert(list.find(93) == false);

  list.add(1);
  list.add(2);
  list.add(3);
  list.add(4);
  list.add(5);

  assert(list.find(9) == false);
  assert(list.find(4) == true);
  assert(list.find(7) == false);

  assert(list.get() == 4);
}

void test_list_copy_constructor() {

  int arr[7] = {5, 6, 4, 1, 2, 4, 6};

  List<int> list;

  for (int i = 0; i < 7; i++) {
    list.add(arr[i]);
    assert(list.get() == arr[i]);
  }

  assert(list.length() == 7);

  List<int> anotherList = list;

  anotherList.end();

  for (int i = 0; i < 7; i++) {
    assert(anotherList.get() == arr[i]);
    if (i != 6)
      assert(anotherList.back() == true);
    else
      assert(anotherList.back() == false);
  }

  assert(anotherList.length() == list.length());

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

  std::cout << "\nAll assertions are correct\n";
  return 0;
}