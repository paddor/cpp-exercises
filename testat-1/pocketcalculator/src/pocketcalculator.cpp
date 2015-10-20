#include "pocketcalculator.h"
#include "calc.h"
#include "sevensegment.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <stdlib.h>

namespace pocketcalculator {
	void calc(std::istream& input, std::ostream& output, const unsigned scale_factor)
	try {
		const auto result = ::calc(input);
		sevensegment::printLargeNumber(result, output, scale_factor);
	} catch(std::exception&) {
		sevensegment::printLargeError(output, scale_factor);
	}

	void start(std::istream& input, std::ostream& output, unsigned scale_factor) {
		while (!input.eof()) calc(input, output, scale_factor);
	}

	unsigned preferred_scale() {
		const std::unique_ptr<char> scale_ptr { getenv("POCKETCALCULATOR_SCALE") };
		if (scale_ptr)
			return std::stoul(std::string { *scale_ptr });
		// TODO: test with and without env var set

		return 0;
	}
}
