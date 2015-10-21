#include "pocketcalculator.h"
#include "calc.h"
#include "sevensegment.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>

namespace pocketcalculator {
	void calc(std::istream& input, std::ostream& output, const unsigned scale_factor)
	try {
		const auto result = ::calc(input);
		sevensegment::printLargeNumber(result, output, scale_factor);
	} catch(std::exception&) {
		sevensegment::printLargeError(output, scale_factor);
	}

	unsigned automatic_scale() {
		// NOTE: can't use std::unique_ptr because the memory pointed to by the
		// pointer is not ours
		const char* scale_ptr { std::getenv("POCKETCALCULATOR_SCALE") };

		if (scale_ptr != nullptr)
			return std::stoul(std::string { scale_ptr });

		return default_scale_factor;
	}

	void start(std::istream& input, std::ostream& output, unsigned scale_factor) {
		if (scale_factor == 0)
			scale_factor = automatic_scale();

		while (!input.eof()) calc(input, output, scale_factor);
	}
}
