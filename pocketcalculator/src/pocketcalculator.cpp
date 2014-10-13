#include <iostream>
#include <string>
#include <stdexcept>
#include "calc.h"
#include "sevensegment.h"

namespace pocketcalculator {
	void display_result_for(std::istream &input, std::ostream &output, unsigned n)
	try {
		std::string term {};
		std::getline(input, term);
		auto result = calc(term);
		printLargeNumber(result, output, n);
	} catch(std::logic_error) {
		printLargeError(output, n);
	}

	void start(std::istream &input, std::ostream &output, unsigned n=3) {
		while (input) {
			output << "Please type your input term: ";
			display_result_for(input, output, n);
		}
	}
}
