#include "calc.h"
#include <stdexcept>
#include <sstream>

int calc(int a, int b, char operator_symbol) {
	switch (operator_symbol) {
		case '*': return a*b;
		case '/':
			if (b == 0) throw std::domain_error{"division by zero"};
			return a/b;
		case '+': return a+b;
		case '-': return a-b;
		case '%': return a%b;
	}
	throw std::invalid_argument{"invalid operator"};
}

int calc(std::istream& input) {
	int a {0};
	int b {0};
	char op { };
	input >> a;
	input >> op;
	input >> b;
	return calc(a, b, op);
}
