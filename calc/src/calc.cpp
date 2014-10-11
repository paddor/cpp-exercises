#include "calc.h"
#include <stdexcept>

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
	int a {0}, b {0};
	char operator_symbol { };
	input >> a >> operator_symbol >> b;
	return calc(a, b, operator_symbol);
}
