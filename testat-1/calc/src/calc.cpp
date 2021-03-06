#include "calc.h"
#include <stdexcept>
#include <sstream>
#include <istream>
#include <limits>

int sign(int const i) {
	return (int(0) < i) - (i < int(0));
}

void throw_overflow_if(bool const condition) {
	if (condition) throw std::overflow_error { "overflow" };
}

// Calculates the result of two numbers a and b and basic math operator.
int calc(int const a, int const b, char const operator_symbol) {
	using limits = std::numeric_limits<int>;

	switch (operator_symbol) {
		case '*': {
			int result { a * b };
			throw_overflow_if( (sign(a) * sign(b) != sign(result))
					|| (a != 0 && result / a != b));
			return result;
		}
		case '/':
		case '%':
			if (b == 0) throw std::domain_error { "division by zero" };
			if (operator_symbol == '/') return a / b;
			else return a % b;
		case '+':
			throw_overflow_if((a >= 0) && (limits::max() - a < b));
			throw_overflow_if((a <  0) && (b < limits::min() - a));
			return a + b;
		case '-':
			throw_overflow_if((a >= 0) && (limits::max() - a < -b));
			throw_overflow_if((a  < 0) && (-b < limits::min() - a));
			return a - b;
		default:
			std::string reason { "invalid operator: " };
			reason += operator_symbol;
			throw std::invalid_argument { reason };
	}

}

int calc(std::istream& input) {
	int a { 0 }, b { 0 };
	char operator_symbol { };
	std::string term { };
	std::getline(input, term);
	std::istringstream term_input { term };
	term_input >> a >> operator_symbol >> b;

	if (!term_input || !term_input.eof())
			throw std::runtime_error{ "malformed input term"};

	try {
		return calc(a, b, operator_symbol);

	} catch (std::logic_error const& exception) {
		// Translate exception from lower layer for upper layer.
		// What was a std::logic_error from calc(int, int, char)'s
		// point of view, is a std::runtime_error from here upwards.
		throw std::runtime_error { exception.what() };
	}
}
