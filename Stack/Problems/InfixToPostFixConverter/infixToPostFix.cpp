#include <iostream>
#include <string>
#include "InfixToPostfixConverter.hpp"

using namespace std;

int main() {

  string infixForm;

  cout << "\nWrite expression in infix form: ";
  getline(cin, infixForm);

  cout << "\nGiven expression in postfix form: " << convertToPostfix(infixForm) << "\n";

  return 0;
}
