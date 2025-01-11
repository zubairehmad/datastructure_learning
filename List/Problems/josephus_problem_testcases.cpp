#include <climits>
#include <iostream>
#include <cassert>
#include "josephus_problem.h"

using namespace std;

void assert_notice(std::string name, bool passed) {
  cout << "\n" << name << " " << (passed? "passed" : "failed") << ".";
}

void testCase1() {
  assert(getSurvivorForJosephusProblem(7, 3) == 4);
  assert_notice(__func__, true);
}

void testCase2() {
  try {
    assert(getSurvivorForJosephusProblem(1, -1));
    assert_notice(__func__, true);
    assert(false);
  } catch (const InvalidInput& e) {}
  assert_notice(__func__, true);
}

void testCase3() {
  try {
    assert(getSurvivorForJosephusProblem(-1, 10));
    assert_notice(__func__, true);
    assert(false);
  } catch (const InvalidInput& e) {}
  assert_notice(__func__, true);
}

void testCase4() {
  assert(getSurvivorForJosephusProblem(1, 1) == 1);
  assert_notice(__func__, true);
}

void testCase5() {
  assert(getSurvivorForJosephusProblem(192, 1) == 192);
  assert_notice(__func__, true);
}

void testCase6() {
  assert(getSurvivorForJosephusProblem(6, 6) == 4);
  assert_notice(__func__, true);
}

void testCase7() {
  assert(getSurvivorForJosephusProblem(10, 10) == 8);
  assert_notice(__func__, true);
}

void testCase8() {
  assert(getSurvivorForJosephusProblem(2592, 421) == 1350);
  assert_notice(__func__, true);
}

int main() {

  testCase1();
  testCase2();
  testCase3();
  testCase4();
  testCase5();
  testCase6();
  testCase7();
  testCase8();

  cout << "\n\nAll test cases passed...\n";

  return 0;
}