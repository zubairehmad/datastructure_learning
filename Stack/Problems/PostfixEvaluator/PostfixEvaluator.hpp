#pragma once

#include "../../Linked List Stack/Stack.hpp"
#include "../helper.hpp"
#include <cctype>
#include <stdexcept>

class DivisionByZeroException : public std::runtime_error {
  public:
    DivisionByZeroException(const std::string& msg = "Division by zero is undefined!") : std::runtime_error(msg) {}
};

// Evaluates given postfix expression and returns answer in points (double datatype)
inline double evaluatePostfix(const std::string& postfixExpr) {
  Stack<double> numberStack;

  for (int i = 0; i < postfixExpr.size(); i++) {

    // Ignore spaces
    if (postfixExpr[i] == ' ' || postfixExpr[i] == '\n') continue;

    // If current index is at a digit
    // extract whole number
    else if (std::isdigit(postfixExpr[i])) {
      int nextNonDigitIndex = findNextNonDigitIndex(postfixExpr, i);

      numberStack.push(std::stoi(postfixExpr.substr(i, nextNonDigitIndex - i)));

      i = nextNonDigitIndex-1;
    }

    // If current index is at operator,
    // perform associated operation
    else if (isOperator(postfixExpr[i])) {

      if (numberStack.size() < 2) {
        throw InvalidExpression("Invalid expression is given!");
      }

      double num2 = numberStack.pop();
      double num1 = numberStack.pop();

      switch (postfixExpr[i]) {
        case '+':
          numberStack.push(num1 + num2);
          break;
        case '-':
          numberStack.push(num1 - num2);
          break;
        case '*':
          numberStack.push(num1 * num2);
          break;
        case '/':
          if (num2 == 0) {
            throw DivisionByZeroException();
          }
          numberStack.push(num1 / num2);  // Ensure accurate division
      }
    }

    else {
      throw InvalidExpression("Unknown character found: '" + std::string(1, postfixExpr[i]) + "'");
    }
  }

  if (numberStack.size() != 1) {
    throw InvalidExpression("Invalid expression is given!");
  }

  return numberStack.pop();
}