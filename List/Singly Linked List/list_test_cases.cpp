#include "List.hpp"
#include <cassert>
#include <iostream>
#include <sstream>

using namespace std;

void assert_notice(std::string name, bool passed) {
  std::cout << "\n" << name << " " << (passed ? "passed" : "failed") << ".\n";
}

void test_list_constructor() {
  List list;
  assert(list.length() == 0);
  assert_notice(__func__, true);
}

void test_list_length() {
  List list;
  assert(list.length() == 0);
  list.add(32);
  assert(list.length() == 1);
  list.add(99);
  assert(list.length() == 2);
  list.remove();
  assert(list.length() == 1);
  list.remove();
  assert(list.length() == 0);
  assert_notice(__func__, true);
}

void test_list_get() {
  List list;

  try {
    list.get();
    assert_notice(__func__, false);
    assert(false);
  } catch (const UninitializedListError &e) { /* Silent this exception only */ }

  list.add(93);
  list.add(29);

  assert(list.length() == 2);
  assert(list.get() == 29);

  list.remove();

  assert(list.get() == 93);

  list.add(329);
  list.add(10);

  assert(list.get() == 10);
  assert_notice(__func__, true);
}

void test_list_add() {
  List list;

  assert(list.length() == 0);

  list.add(39);

  assert(list.length() == 1);
  assert(list.get() == 39);

  list.add(48);
  list.add(10);

  assert(list.length() == 3);
  assert(list.get() == 10);

  list.back();
  list.add(49);

  assert(list.length() == 4);
  assert(list.get() == 49);
  assert_notice(__func__, true);
}

void test_list_remove() {
  List list;

  try {
    list.remove();
    assert_notice(__func__, false);
    assert(false);
  } catch (const UninitializedListError &e) { /* Silent this exception only */ }

  assert(list.length() == 0);

  list.add(99);
  list.add(69);

  assert(list.get() == 69);

  list.remove();

  assert(list.get() == 99);
  assert(list.length() == 1);

  list.add(95);
  list.add(300);
  list.add(200);

  assert(list.get() == 200);

  list.back();
  list.back();

  assert(list.get() == 95);

  list.remove();

  assert(list.length() == 3);
  assert(list.get() == 300);

  list.start();
  list.remove();

  assert(list.length() == 2);
  assert(list.get() == 300);

  assert_notice(__func__, true);
}

void test_list_update() {
  List list;

  try {
    list.get();
    assert_notice(__func__, false);
    assert(false);
  } catch (const UninitializedListError &e) { /* Silent this exception only */ }

  list.add(94);
  list.add(1);
  list.add(24);
  list.add(0);

  assert(list.length() == 4);
  assert(list.get() == 0);

  list.update(99);

  assert(list.get() == 99);
  assert(list.length() == 4);

  assert_notice(__func__, true);
}

void test_list_start() {
  List list;

  try {
    list.start();
    assert_notice(__func__, false);
    assert(false);
  } catch (const UninitializedListError &e) { /* Silent this exception only */ }

  list.add(99);
  list.start();

  assert(list.get() == 99);
  assert(list.length() == 1);

  list.add(92);
  list.add(64);

  assert(list.get() == 64);
  assert(list.length() == 3);

  list.start();

  assert(list.length() == 3);
  assert(list.get() == 99);

  assert_notice(__func__, true);
}

void test_list_end() {
  List list;

  try {
    list.end();
    assert_notice(__func__, false);
    assert(false);
  } catch (const UninitializedListError &e) { /* Silent this exception only */ }

  list.add(932);
  list.add(19);
  list.add(192);

  assert(list.length() == 3);
  assert(list.get() == 192);

  list.end();
  assert(list.get() == 192);

  list.start();
  assert(list.get() == 932);

  list.end();
  assert(list.get() == 192);

  assert_notice(__func__, true);
}

void test_list_next() {
  List list;

  try {
    list.next();
    assert_notice(__func__, false);
    assert(false);
  } catch (const UninitializedListError &e) { /* Silent this exception */ }

  list.add(93);
  list.add(92);
  list.add(91);

  assert(list.get() == 91);
  assert(list.next() == false);

  list.start();

  assert(list.get() == 93);
  assert(list.next() == true);

  assert(list.get() == 92);
  assert(list.next() == true);

  assert(list.get() == 91);
  assert(list.next() == false);

  assert_notice(__func__, true);
}

void test_list_back() {
  List list;

  try {
    list.back();
    assert_notice(__func__, false);
    assert(false);
  } catch (const UninitializedListError &e) { /* Silent this exception only */ }

  list.add(93);

  assert(list.length() == 1);
  assert(list.get() == 93);
  assert(list.back() == false);

  list.add(92);
  list.add(91);

  assert(list.length() == 3);
  assert(list.get() == 91);

  assert(list.back() == true);
  assert(list.getBackMethodIterationCount() == 1);
  assert(list.get() == 92);

  assert(list.back() == true);
  assert(list.get() == 93);
  assert(list.getBackMethodIterationCount() == 0);
  assert(list.back() == false);

  list.end();
  list.add(90);

  assert(list.get() == 90);
  assert(list.back() == true);
  assert(list.getBackMethodIterationCount() == list.length()-2);

  assert_notice(__func__, true);
}

void test_list_find() {
  List list;

  assert(list.find(93) == false);

  list.add(93);
  list.add(92);
  list.add(91);
  list.add(39);
  list.add(29);
  list.add(19);

  assert(list.get() == 19);
  assert(list.length() == 6);

  assert(list.find(19) == true);
  assert(list.get() == 19);
  assert(list.next() == false);

  assert(list.find(92) == true);
  assert(list.get() == 92);
  assert(list.back() == true);

  assert(list.find(39) == true);
  assert(list.get() == 39);

  assert(list.find(100) == false);
  assert(list.get() == 39);

  assert_notice(__func__, true);
}

void test_list_copy_constructor() {
  List list;
  list.add(93);
  list.add(92);
  list.add(91);

  List list1 = list;
  List list2(list);

  assert(list1.length() == list2.length());

  do {
    assert(list1.get() == list2.get());
  } while (list1.next() == true && list2.next() == true);

  assert_notice(__func__, true);
}

void test_list_stream_insertion_operator() {
  List list;
  ostringstream output;

  output << list;

  assert(output.str() == "[]");
  output.str("");

  list.add(39);
  list.add(29);
  list.add(19);
  list.add(9);

  output << list;
  assert(output.str() == "[39, 29, 19, 9]");
  output.str("");

  list.end();
  assert(list.get() == 9);

  list.back();

  output << list;
  assert(output.str() == "[39, 29, 19, 9]");
  assert(list.get() == 19);

  assert_notice(__func__, true);
}

int main() {

  test_list_constructor();
  test_list_length();
  test_list_get();
  test_list_add();
  test_list_remove();
  test_list_update();
  test_list_start();
  test_list_end();
  test_list_next();
  test_list_back();
  test_list_find();
  test_list_copy_constructor();

  return 0;
}