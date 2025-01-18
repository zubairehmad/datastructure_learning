#include <cassert>
#include <iostream>
#include "InfixEvaluator.hpp"

using namespace std;

void assert_notice(const char* methodName, bool passed) {
  cout << "\n" << methodName << " " << (passed? "passed" : "failed") << ".";
}

void testCase1() {
  try {
    evaluateInfix("(3 + 2");
    assert_notice(__func__, false);
    assert(false);
  } catch (const InvalidExpression& e) {}
  assert_notice(__func__, true);
}

void testCase2() {
  try {
    evaluateInfix("3 + + 2");
    assert_notice(__func__, false);
    assert(false);
  } catch (const InvalidExpression& e) {}
  assert_notice(__func__, true);
}

void testCase3() {
  assert(abs(evaluateInfix("3 + 5 * 2 - 7 / 3 + 4 * 9 - 6 / 2 + 3 * 8 - 5") - 62.6667) < 1e-4);
  assert_notice(__func__, true);
}

void testCase4() {
  try {
    evaluateInfix("3+1a");
    assert_notice(__func__, false);
    assert(false);
  } catch (const InvalidExpression& e) {}
  assert_notice(__func__, true);
}

void testCase5() {
  assert(evaluateInfix("(3 + (5 * (2 + (3 * (2 + 4))))) * 4 - 7 / (2 + 3)") == 410.6);
  assert_notice(__func__, true);
}

void testCase6() {
  assert(evaluateInfix("3 + 5 * 6 - 12 / 2 + 4 * 3 - 2 * (5 + 3) / 2 + 8") == 39);
  assert_notice(__func__, true);
}

void testCase7() {
  try {
    evaluateInfix("(5 + 3) / 0 * 2 + (8 / 0) - 6");
    assert_notice(__func__,false);
    assert(false);
  } catch (const DivisionByZeroException& e) {}
  assert_notice(__func__, true);
}

void testCase8() {
  assert(evaluateInfix("1 + 2 * 3 + 4 * 5 + 6 * 7 + 8 * 9 + 10 * 11 + 12 * 13 + 14 * 15") == 617);
  assert_notice(__func__, true);
}

void testCase9() {
  assert(evaluateInfix("((3+5*2)*(7\n+\n(6    *(2+1))\n) )-(8/ 4 +3)*(5+              \n2)") == 290);
  assert_notice(__func__, true);
}

void testCase10() {
  assert(abs(evaluateInfix("(3 + 2) / (1 + 2) * (4 + 3) / (7 - 8)") - (-11.6667)) < 1e-4);
  assert_notice(__func__, true);
}

void testCase11() {
  assert(evaluateInfix("(1 + (2 * (3 + (4 * (5 + (6 * (7 + 8))))))) + (9 * (10 + 11))") == 956);
  assert_notice(__func__, true);
}

void testCase12() {
  assert(evaluateInfix("(2 + 3) * (4 + (5 * (2 + 1))) - 2 * 3 + (7 * (8 + 3)) / 5") == 104.4);
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

  cout << "\n\nAll test cases passed successfully!\n";

  return 0;
}