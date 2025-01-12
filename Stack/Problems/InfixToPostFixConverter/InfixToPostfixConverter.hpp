#include <string>
#include <unordered_map>
#include <stdexcept>
#include "../../Linked List Stack/Stack.hpp"

class InvalidExpression : public std::invalid_argument {
	public:
		InvalidExpression(std::string message="") : std::invalid_argument(message) {}
};

/*
	Tells whether operator 1 has precedence over operator 2
*/
inline bool _hasPrecedence(char op1, char op2) {
	
	// Brackets are not operators rather they are used to increase
	// default precedence of the operators.
	if (op1 == '(' || op2 == '(') return false;

	static std::unordered_map<char, int> precedenceTable = {
		{'+', 1},
		{'-', 1},
		{'*', 2},
		{'/', 2}
	};

	// If the operator 1 has more precedence than operator 2, then return true.
	// If they've equal precedence then also return true to ensure left to right associativity.
	return precedenceTable[op1] >= precedenceTable[op2];
}

// Tell wheter given character is an operator or not
inline bool _isOperator(const char& ch) {
	return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

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

	Stack<char> operatorStack;

	std::string postfixExpr;

	// To ensure correct expression is given
	int openedBrackets = 0;
	int numberOfOperators = 0;
	int numberOfOperands = 0;

	for (int i = 0; i < infixExpr.size(); i++) {

		// Ignore spaces or newlines
		if (infixExpr[i] == ' ' || infixExpr[i] == '\n') continue;

		else if (_isOperator(infixExpr[i])) {

			// If there is already an operator which has equal or greater precedence than the
			// to be added operator, then pop it from stack, and put in the result (postfixExpr)
      while (!operatorStack.isEmpty() && _hasPrecedence(operatorStack.top(), infixExpr[i])) {	
				postfixExpr += operatorStack.pop();
				postfixExpr += " ";
			}

			// Push the operator with its calculated predence 
			operatorStack.push(infixExpr[i]);

			numberOfOperators++;
		} 

		// If current index is at digit (a potential number),
		// extract the number and start from next index after the number 
		else if (std::isdigit(infixExpr[i])) {
 			int nextNonDigitIndex = _findNextNonDigitIndex(infixExpr, i);

			postfixExpr += infixExpr.substr(i, nextNonDigitIndex == -1? std::string::npos : nextNonDigitIndex - i) + ' ';

			numberOfOperands++;
			i = nextNonDigitIndex-1;
		}

		else if (infixExpr[i] == '(') {
			// Push the bracket onto stack so that any higher precedence operator in stack
			// cannot get precedence over any operator in bracket
			operatorStack.push(infixExpr[i]);
			openedBrackets++;
		}

		else if (infixExpr[i] == ')') {

			// Pop all operators until no matching ( is found
			while (!operatorStack.isEmpty() && operatorStack.top() != '(') {
				postfixExpr += operatorStack.pop();
				postfixExpr += " ";
			}

			// There must be '(' remaining. If not then it means there is no matching (
			if (operatorStack.isEmpty()) {
				throw InvalidExpression("Cannot find matching '(' for ')' present at index: " + std::to_string(i));
			}

			// Also remove '(' from stack
			operatorStack.pop();
			openedBrackets--;
		}

		else {
			throw InvalidExpression("Unknown character found: '" + std::string(1, infixExpr[i]) + "'");
		}
	}

	if (openedBrackets != 0) {
		throw InvalidExpression("There unmatched brackets!");
	} else if (numberOfOperands != numberOfOperators+1) {
		throw InvalidExpression("Invalid expression given! It has irregular number of operands and operators!");
	}
	
	// All the operators with lowest predence should be included
	// in the last
	while (!operatorStack.isEmpty()) {
		postfixExpr += operatorStack.pop();
		postfixExpr += " ";
	}

	if (!postfixExpr.empty()) {
		postfixExpr.pop_back();	// Remove trailing ' ' character from the end
	}

	return postfixExpr;
}
