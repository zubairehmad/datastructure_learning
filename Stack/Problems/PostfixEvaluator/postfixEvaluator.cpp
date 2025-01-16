#include <exception>
#include <iostream>
#include <string>
#include "PostfixEvaluator.hpp"

using namespace std;

int main() {

  string expr;

  cout << "\nWrite expression in postfix form: ";
  getline(cin, expr);

  try {
    double answer = evaluatePostfix(expr);
    cout << "\nAnswer: " << answer << "\n";
  } catch (const exception& e) {
    cout << "\nError Occured: " << e.what() << endl;
  }

  return 0;
}