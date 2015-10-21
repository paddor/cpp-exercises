#include "sevensegment.h"
#include <ostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <stdexcept>

namespace sevensegment {
	using digit = std::vector<std::string>;
	using digit_vector = std::vector<digit>;

	const digit_vector digits {
		{ " - ", "| |", "   ", "| |", " - " }, // 0
		{ "   ", "  |", "   ", "  |", "   " }, // 1
		{ " - ", "  |", " - ", "|  ", " - " }, // 2
		{ " - ", "  |", " - ", "  |", " - " }, // 3
		{ "   ", "| |", " - ", "  |", "   " }, // 4
		{ " - ", "|  ", " - ", "  |", " - " }, // 5
		{ " - ", "|  ", " - ", "| |", " - " }, // 6
		{ " - ", "  |", "   ", "  |", "   " }, // 7
		{ " - ", "| |", " - ", "| |", " - " }, // 8
		{ " - ", "| |", " - ", "  |", " - " }  // 9
	};
	const digit minus_sign
		{ "   ", "   ", " - ", "   ", "   " }; // -

	std::string stretchDigitLine(const std::string& line, const unsigned scale_factor) {
		std::string stretched_line(scale_factor+2, line[1]); // stretch the center
		stretched_line.front() = line[0]; // fix first char
		stretched_line.back() = line[2]; // fix last char
		return stretched_line;
	}

	digit_vector split_digits(const int i, digit_vector& vector) {
	    if(i >= 10)
	       split_digits(i / 10, vector);

	    vector.push_back(digits.at(i % 10));
	    return vector;
	}

	digit_vector split_digits(int i) {
		digit_vector vector {};
		if (i<0) {
			vector.push_back(minus_sign);
			i = -i;
		}

		return split_digits(i, vector);
	}

	std::string lineOfLargeDigits(const digit_vector& vector,
			const unsigned line_nr, const unsigned scale_factor){

		const std::string letter_space(scale_factor/2, ' ');
		std::string line {};
		bool first_digit = true;

		// NOTE: It would be really nice to have an infix_iterator.
		// http://stackoverflow.com/questions/3496982/printing-lists-with-commas-c/3497021#3497021
		for(digit d : vector) {
			if (!first_digit) line += letter_space;
			line += stretchDigitLine(d[line_nr], scale_factor);
			first_digit = false;
		}

		return line;
	}

	constexpr unsigned display_size { 8 };

	void printDigitSequence(const digit_vector vector,
			std::ostream& out, const unsigned scale_factor){

		if (scale_factor<1)
			throw std::range_error { "invalid scale" };
		if (vector.size() > display_size)
			throw std::overflow_error { "too many digits" };

		std::ostream_iterator<std::string> out_it(out, "\n");

		// iterate through lines, not digits
		// OPTIMIZE: transpose vector first to get more cache hits
		for(int line_nr { 0 }; line_nr < 5; ++line_nr) {
			auto count = (line_nr == 1 || line_nr == 3) ? scale_factor : 1;
			auto line = lineOfLargeDigits(vector, line_nr, scale_factor);
			std::fill_n(out_it, count, line);
		}
	}

	// Requested for the assignment. Used nowhere but in the tests.
	void printLargeDigit(const unsigned i, std::ostream& out, const unsigned scale_factor) {
		const auto d = digits.at(i);
		const digit_vector single_digit_vector { d };
		printDigitSequence(single_digit_vector, out, scale_factor);
	}

	void printLargeNumber(const int i, std::ostream& out, const unsigned scale_factor) {
		printDigitSequence(split_digits(i), out, scale_factor);
	}

	const digit_vector error {
		{ " - ", "|  ", " - ", "|  ", " - " }, // E
		{ "   ", "   ", " - ", "|  ", "   " }, // r
		{ "   ", "   ", " - ", "|  ", "   " }, // r
		{ "   ", "   ", " - ", "| |", " - " }, // o
		{ "   ", "   ", " - ", "|  ", "   " }, // r
	};

	void printLargeError(std::ostream& out, const unsigned scale_factor) {
		printDigitSequence(error, out, scale_factor);
	}
}
