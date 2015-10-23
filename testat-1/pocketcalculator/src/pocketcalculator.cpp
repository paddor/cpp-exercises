#include "pocketcalculator.h"
#include "calc.h"
#include "sevensegment.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>

namespace pocketcalculator {
	void calc(std::istream& input, std::ostream& output, unsigned const scale_factor)
	try {
		auto const result = ::calc(input);
		sevensegment::printLargeNumber(result, output, scale_factor);
	} catch(std::runtime_error const&) {
		sevensegment::printLargeError(output, scale_factor);
	}

	// This function reads and returns the scale factor from the
	// environment variable POCKETCALCULATOR_SCALE. If it's not set, it
	// returns default_scale_factor.
	//
	// NOTE: Hard to test because there's no (standard) way to set
	// environment variables from inside a program.
	unsigned automatic_scale() {
		// NOTE: can't use std::unique_ptr because the memory pointed to by the
		// pointer is not ours
		char const * const scale_ptr { std::getenv("POCKETCALCULATOR_SCALE") };

		if (scale_ptr != nullptr)
			return std::stoul(std::string { scale_ptr });

		return default_scale_factor;
	}

	// Automatic scaling is used when scale_factor == 0. Otherwise the
	// scale_factor won't be changed.
	void start(std::istream& input, std::ostream& output, unsigned scale_factor) {
		if (scale_factor == 0)
			scale_factor = automatic_scale();

		while (!input.eof())
			calc(input, output, scale_factor);
	}
}
