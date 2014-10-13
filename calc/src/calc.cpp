#include "calc.h"
#include <stdexcept>
#include <sstream>
#include <istream>

// Calculates the result of two numbers a and b and basic math operator.
int calc(int a, int b, char operator_symbol) {
	switch (operator_symbol) {
		case '*': return a * b;
		case '/':
			if (b == 0) throw std::domain_error{"division by zero"};
			return a / b;
		case '+': return a + b;
		case '-': return a - b;
		case '%':
			if (b == 0) throw std::domain_error{"division by zero"};
			return a % b;
	}

	auto reason = std::string("invalid operator: ");
	reason.push_back(operator_symbol);
	throw std::invalid_argument{reason};
}

int calc(std::istream &input) {
	int a {0}, b {0};
	char operator_symbol { };
	input >> a >> operator_symbol >> b;
	if (input.fail() || !input.eof())
			throw std::invalid_argument{ "malformed input term"};
	return calc(a, b, operator_symbol);
}

int calc(std::string &term) {
	std::istringstream term_stream { term };
	return calc(term_stream);

}
