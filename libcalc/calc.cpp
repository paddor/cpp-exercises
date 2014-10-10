#include "calc.hpp"
#include <stdexcept>
#include <sstream>

int calc(int a, int b, char op) {
	switch (op) {
	case '*': return a * b;
	case '/':
		if (b == 0) throw std::domain_error{"division by zero"};
		return a/b;
	case '+': return a+b;
	case '-': return a-b;
	}
	throw std::invalid_argument{"invalid operator"};
}
