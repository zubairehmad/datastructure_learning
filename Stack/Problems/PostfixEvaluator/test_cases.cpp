#include <iostream>
#include <cassert>
#include "PostfixEvaluator.hpp"

using namespace std;

void assert_notice(const char* methodName, bool passed) {
  cout << "\n" << methodName << " " << (passed? "passed" : "failed") << ".";
}

void testCase1() {
  assert(evaluatePostfix("23 21 -") == 2.0);
  assert_notice(__func__, true);
}

void testCase2() {
  try {
    evaluatePostfix("10 0 /");
    assert_notice(__func__, false);
    assert(false);
  } catch (const DivisionByZeroException& e) {}
  assert_notice(__func__, true);
}

void testCase3() {
  try {
    evaluatePostfix("193 / 21");
    assert_notice(__func__, false);
    assert(false);
  } catch (const InvalidExpression& e) {}
  assert_notice(__func__, true);
}

void testCase4() {
  try {
    evaluatePostfix("21 21 4 /");
    assert_notice(__func__, false);
    assert(false);
  } catch (const InvalidExpression& e) {}
  assert_notice(__func__, true);
}

void testCase5() {
  try {
    evaluatePostfix("392& 932 -");
    assert_notice(__func__, false);
    assert(false);
  } catch (const InvalidExpression& e) {}
  assert_notice(__func__, true);
}

void testCase6() {
  try {
    evaluatePostfix("218 032");
    assert_notice(__func__, false);
    assert(false);
  } catch (const InvalidExpression& e) {}
  assert_notice(__func__, true);
}

void testCase7() {
  assert(evaluatePostfix("2 3 + 5 4 + *") == 45.0);
  assert_notice(__func__, true);
}

void testCase8() {
  assert(std::abs(evaluatePostfix("5 1 2 + 4 * + 3 /") - 5.66667) < 1e-4);
  assert_notice(__func__, true);
}

void testCase9() {
  assert(evaluatePostfix("5 7 - 2 *") == -4.0);
  assert_notice(__func__, true);
}

void testCase10() {
  assert(evaluatePostfix("50 5 10 * + 25 5 / -") == 95.0);
  assert_notice(__func__, true);
}

void testCase11() {
  try {
    evaluatePostfix("32+");
    assert_notice(__func__, false);
    assert(false);
  } catch (const InvalidExpression& e) {}
  assert_notice(__func__, true);
}

void testCase12() {
  double result = evaluatePostfix("\n  \n1 1+2+3+4+5+6+7+8+9+10+    ");
  assert(evaluatePostfix("\n  \n1 1+2+3+4+5+6+7+8+9+10+    ") == 56);
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
  testCase9();
  testCase10();
  testCase11();
  testCase12();

  cout << "\n\nAll test cases passed.\n";

  return 0;
}