#include <iostream>
#include <cassert>
#include "InfixToPostfixConverter.hpp"

using namespace std;

void assert_notice(const char* methodName, bool passed) {
  cout << "\n" << methodName << " " << (passed? "passed" : "failed") << ".";
}

void testCase1() {
  assert(convertToPostfix("1+3") == "1 3 +");
  assert_notice(__func__, true);
}

void testCase2() {
  assert(convertToPostfix("1-3*4") == "1 3 4 * -");
  assert_notice(__func__, true);
}

void testCase3() {
  assert(convertToPostfix("(1+3)/(1- 2)") == "1 3 + 1 2 - /");
  assert_notice(__func__, true);
}

void testCase4() {
  assert(convertToPostfix("((1 + 2) / 3)") == "1 2 + 3 /");
  assert_notice(__func__, true);
}

void testCase5() {
  assert(convertToPostfix("112*239+3291-932/123") == "112 239 * 3291 + 932 123 / -");
  assert_notice(__func__, true);
}

void testCase6() {
  assert(convertToPostfix("(219 - (3/(221-(21+31))))") == "219 3 221 21 31 + - / -");
  assert_notice(__func__, true);
}

void testCase7() {
  assert(convertToPostfix("(392+255)-(4420+5932)/(492310-120192)*(31938-212)") == "392 255 + 4420 5932 + 492310 120192 - / 31938 212 - * -");
  assert_notice(__func__, true);
}

void testCase8() {
  assert(convertToPostfix("241/4214-39124-2149+392/129418923-329*3021") == "241 4214 / 39124 - 2149 - 392 129418923 / + 329 3021 * -");
  assert_notice(__func__, true);
}

void testCase9() {
  assert(convertToPostfix("1-(3/(95*(3-2) + 3) / 2)") == "1 3 95 3 2 - * 3 + / 2 / -");
  assert_notice(__func__, true);
}

void testCase10() {
  assert(convertToPostfix("(((((((32-2)+1)-3)/2)*4)/18)+12)") == "32 2 - 1 + 3 - 2 / 4 * 18 / 12 +");
  assert_notice(__func__, true);
}

void testCase11() {
  try {
    convertToPostfix(")");
    assert_notice(__func__, false);
    assert(false);
  } catch (const InvalidExpression& e) {}
  assert_notice(__func__, true);
}

void testCase12() {
  try {
    convertToPostfix("192-324=329");
    assert_notice(__func__, false);
    assert(false);
  } catch (const InvalidExpression& e) {}
  assert_notice(__func__, true);
}

void testCase13() {
  try {
    convertToPostfix("291-21(32)");
    assert_notice(__func__, false);
    assert(false);
  } catch (const InvalidExpression& e) {}
  assert_notice(__func__, true);
}

void testCase14() {
  try {
    convertToPostfix("(((((((((((()-)/)*)-)+)+)-)/)*)/)-)");
    assert_notice(__func__, false);
    assert(false);
  } catch (const InvalidExpression& e) {}
  assert_notice(__func__, true);
}

void testCase15() {
  try {
    convertToPostfix("5 + (4 - 3 * (4 / 2");
    assert_notice(__func__, false);
    assert(false);
  } catch (const InvalidExpression& e)  {}
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
  testCase13();
  testCase14();
  testCase15();

  cout << "\n\nAll test cases passed....\n";

  return 0;
}