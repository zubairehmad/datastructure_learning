#include <exception>
#include <iostream>
#include "InfixEvaluator.hpp"

using namespace std;

int main() {

  string infixExpr;

  cout << "\nWrite expression in infix form: ";
  getline(cin, infixExpr);

  try {
    double answer = evaluateInfix(infixExpr);
    cout << "\nAnswer: " << answer << endl;
  } catch (const exception& e) {
    cout << "\nError Occured: " << e.what() << endl;
  }

  return 0;
}