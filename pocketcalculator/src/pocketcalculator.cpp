#include <iostream>
#include <string>
#include <stdexcept>
#include <stdlib.h>
#include "calc.h"
#include "sevensegment.h"

namespace pocketcalculator {
	void display_result_for(std::istream &input, std::ostream &output, unsigned n)
	try {
		std::string term {};
		std::getline(input, term);
		auto result = calc(term);
		sevensegment::printLargeNumber(result, output, n);
	} catch(std::logic_error&) {
		sevensegment::printLargeError(output, n);
	}

	const unsigned default_scale { 2 };

	unsigned preprocess_scale(unsigned n) {
		if (n>0) return n;

		char* scale_env { getenv("POCKETCALCULATOR_SCALE") };
		if (scale_env == nullptr) return default_scale;

		std::string scale_env_string { scale_env };
		int scale {};
		scale = std::stoi(scale_env);
		if (scale < 1) throw std::invalid_argument { "invalid scale" };
		return scale;
	}

	void start(std::istream &input, std::ostream &output, unsigned n) {
		n = preprocess_scale(n);
		while (input) {
			output << "Please type your input term: ";
			display_result_for(input, output, n);
		}
	}
}
