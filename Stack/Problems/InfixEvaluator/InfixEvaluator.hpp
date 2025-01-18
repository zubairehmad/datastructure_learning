#pragma once

#include "../InfixToPostFixConverter/InfixToPostfixConverter.hpp"
#include "../PostfixEvaluator/PostfixEvaluator.hpp"

// Simply converts infix to postfix, and then returns
// the answer. Throws any exception that can be thrown
// by convertToPostfix or evaluatePostfix methods.
inline double evaluateInfix(const std::string& infixExpr) {
  std::string postfixExpr = convertToPostfix(infixExpr);
  return evaluatePostfix(postfixExpr);
}