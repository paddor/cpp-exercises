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

	digit_vector const digits {
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
	digit const minus_sign
		{ "   ", "   ", " - ", "   ", "   " }; // -

	std::string stretchDigitLine(std::string const& line, unsigned const scale_factor) {
		std::string stretched_line(scale_factor+2, line[1]); // stretch the center
		stretched_line.front() = line[0]; // fix first char
		stretched_line.back() = line[2]; // fix last char
		return stretched_line;
	}

	digit_vector split_digits(int const i, digit_vector& vector) {
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

	std::string lineOfLargeDigits(digit_vector const& vector,
			unsigned const line_nr, unsigned const scale_factor){

		std::string const letter_space(scale_factor/2, ' ');
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

	unsigned const display_size { 8 };
	std::vector<int> const line_numbers { 0, 1, 2, 3, 4 };

	void printDigitSequence(digit_vector const vector,
			std::ostream& out, unsigned const scale_factor){

		if (scale_factor<1)
			throw std::range_error { "invalid scale" };
		if (vector.size() > display_size)
			throw std::overflow_error { "too many digits" };

		std::ostream_iterator<std::string> out_it(out, "\n");

		// iterate through lines, not digits
		// OPTIMIZE: transpose vector first to get more cache hits
		for_each(begin(line_numbers), end(line_numbers), [&](int line_nr) {
			auto count = (line_nr == 1 || line_nr == 3) ? scale_factor : 1;
			auto line = lineOfLargeDigits(vector, line_nr, scale_factor);
			std::fill_n(out_it, count, line);
		});
	}

	// Requested for the assignment. Used nowhere but in the tests.
	void printLargeDigit(unsigned const i, std::ostream& out, unsigned const scale_factor) {
		auto const d = digits.at(i); // NOTE: will throw std::out_of_range if i not within 0..9
		digit_vector const single_digit_vector { d };
		printDigitSequence(single_digit_vector, out, scale_factor);
	}

	void printLargeNumber(int const i, std::ostream& out, unsigned const scale_factor) {
		printDigitSequence(split_digits(i), out, scale_factor);
	}

	digit_vector const error {
		{ " - ", "|  ", " - ", "|  ", " - " }, // E
		{ "   ", "   ", " - ", "|  ", "   " }, // r
		{ "   ", "   ", " - ", "|  ", "   " }, // r
		{ "   ", "   ", " - ", "| |", " - " }, // o
		{ "   ", "   ", " - ", "|  ", "   " }, // r
	};

	void printLargeError(std::ostream& out, unsigned const scale_factor) {
		printDigitSequence(error, out, scale_factor);
	}
}
