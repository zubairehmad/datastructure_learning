#include <exception>
#include <iostream>
#include <string>
#include "PostfixEvaluator.hpp"

using namespace std;

int main() {

  string expr;

  cout << "\nPlease enter postfix expression : ";
  getline(cin, expr);

  try {
    double answer = evaluatePostfix(expr);
    cout << "\nAnswer : " << answer << "\n";
  } catch (const exception& e) {
    cout << "\nException Caught: " << e.what() << endl;
  }

  return 0;
}