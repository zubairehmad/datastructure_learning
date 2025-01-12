#include <string>
#include "../../Linked List Stack/Stack.hpp"

struct _Operator {
	char oper;
	int precedence;

	_Operator(const char& _oper, int _precedence) : oper(_oper), precedence(_precedence) {}

	// Returns default predence of the operators
	static int getDefaultPrecedence(char oper) {
		switch (oper) {
			case '+':
			case '-':
				return 1; 
				break;
			case '*':
			case '/':
				return 2;
				break;
		}
		return 0;
	}
	
	// Tell wheter given character is an operator
	// or not
	static bool isOperator(const char& ch) {
		return ch == '+' || ch == '-' || ch == '*' || ch == '/';
	}
};

inline int _findNextNonDigitIndex(std::string str, int startingPos) {

  if (startingPos > str.size()) throw std::out_of_range("Invalid starting position given!"); 

  int nextNonDigitIndex;

  for (nextNonDigitIndex = startingPos; nextNonDigitIndex < str.size(); nextNonDigitIndex++) {
		if (str[nextNonDigitIndex] < '0' || str[nextNonDigitIndex] > '9') {
			return nextNonDigitIndex;
 		}
	}

	// If there is no next non digit index, return -1
	return -1;
}

// Converts given infix form to postfix form
// Throws exception if malformed expression is passed
inline std::string convertToPostfix(const std::string& infixExpr) {
	
	int highestPrecedence = _Operator::getDefaultPrecedence('/');

	Stack<_Operator> operatorStack;

	std::string postfixExpr;

	// Helps to encounter issues related to brackets such as unmatched brackets etc. 
	int bracketCount = 0;

	// The base precedence helps to calculate the precedence of the operator based on
	// its position. For example, predence of + operator is greater in bracket but lesser
	// when not in brackets. 
	int basePrecedence = 0;

	for (int i = 0; i < infixExpr.size(); i++) {

		if (_Operator::isOperator(infixExpr[i])) {

			// If there is already an operator which has greater precedence than the
			// newly adding operator, then pop it from stack, and put in the result (postfixExpr)
      if (!operatorStack.isEmpty() && operatorStack.top().precedence >= _Operator::getDefaultPrecedence(infixExpr[i])) {	
				postfixExpr += operatorStack.pop().oper;
				postfixExpr += " ";
			}

			// Push the operator with its calculated predence 
			operatorStack.push(_Operator(infixExpr[i], basePrecedence + _Operator::getDefaultPrecedence(infixExpr[i])));
		} 

		// If current index is at digit (a potential number),
		// extract the number and start from next index after the number 
		else if (std::isdigit(infixExpr[i])) {
 			int nextNonDigitIndex = _findNextNonDigitIndex(infixExpr, i);

			postfixExpr += infixExpr.substr(i, nextNonDigitIndex == -1? std::string::npos : nextNonDigitIndex - i) + ' ';

			i = nextNonDigitIndex-1;
		}

    // A bracket is encountered, the base precedence of operators is  
		// higher than any other operator
		else if (infixExpr[i] == '(') {
      bracketCount++;	
			basePrecedence += highestPrecedence;
		}

		// A bracket is ended, hence the base precedence is decreased
		else if (infixExpr[i] == ')') {
			bracketCount--;
			basePrecedence -= highestPrecedence;
		}
	}
	
	// All the operators with lowest predence should be included
	// in the last
	while (!operatorStack.isEmpty()) {
		postfixExpr += operatorStack.pop().oper;
		postfixExpr += " ";
	}

	if (!postfixExpr.empty()) {
		postfixExpr.pop_back();	// Remove trailing ' ' character from the end
	}

	return postfixExpr;
}
