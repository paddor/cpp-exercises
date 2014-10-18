#include "calc.h"
#include <stdexcept>
#include <sstream>
#include <istream>
#include <limits>

int sign(const int i) {
	return (int(0) < i) - (i < int(0));
}

void throw_overflow_if(const bool condition) {
	if (condition) throw std::invalid_argument { "overflow" };
}

// Calculates the result of two numbers a and b and basic math operator.
int calc(const int a, const int b, const char operator_symbol) {
	using int_limits = std::numeric_limits<int>;
	const int int_max { int_limits::max() }, int_min { int_limits::min() };

	switch (operator_symbol) {
		case '*': {
			int result { a * b };
			throw_overflow_if((sign(a) * sign(b) != sign(result)) || (a != 0 && result / a != b));
			return result;
		}
		case '/':
			if (b == 0) throw std::domain_error{"division by zero"};
			return a / b;
		case '+':
			throw_overflow_if((a >= 0) && (int_max - a < b));
			throw_overflow_if((a <  0) && (b < int_min - a));
			return a + b;
		case '-': {
			throw_overflow_if((a >= 0) && (int_max - a < -b));
			throw_overflow_if((a  < 0) && (-b < int_min - a));
			return a - b;
		}
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
	if (input.fail())
			throw std::invalid_argument{ "malformed input term"};
	return calc(a, b, operator_symbol);
}
