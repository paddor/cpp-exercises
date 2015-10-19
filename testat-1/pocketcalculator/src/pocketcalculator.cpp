#include "pocketcalculator.h"
#include "calc.h"
#include "sevensegment.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <stdlib.h>

namespace pocketcalculator {
	void calc(std::istream& input, std::ostream& output, const unsigned n)
	try {
		const auto result = ::calc(input);
		sevensegment::printLargeNumber(result, output, n);
	} catch(std::exception&) {
		sevensegment::printLargeError(output, n);
	}

	void start(std::istream& input, std::ostream& output, unsigned n) {
		while (!input.eof()) calc(input, output, n);
	}

	unsigned preferred_scale() {
		const char* scale_ptr = getenv("POCKETCALCULATOR_SCALE");
		if (scale_ptr != nullptr)
			return std::stoul(std::string { scale_ptr });

		return 0;
	}
}
