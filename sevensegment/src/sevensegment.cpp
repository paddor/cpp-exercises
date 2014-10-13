#include <ostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include "sevensegment.h"

namespace sevensegment {

	const static std::vector< std::vector<std::string> > digits {
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
	const static std::vector<std::string> minus_sign
		{ "   ", "   ", " - ", "   ", "   " }; // -

	const static std::vector< std::vector<std::string> > error {
		{ " - ", "|  ", " - ", "|  ", " - " }, // E
		{ "   ", "   ", " - ", "|  ", "   " }, // r
		{ "   ", "   ", " - ", "|  ", "   " }, // r
		{ "   ", "   ", " - ", "| |", " - " }, // o
		{ "   ", "   ", " - ", "|  ", "   " }, // r
	};

	std::string stretchLine(const std::string &line, unsigned n) {
		std::string stretched_line(n+2, line[1]);
		stretched_line.front() = line[0];
		stretched_line.back() = line[2];
		return stretched_line;
	}

	std::vector< std::vector<std::string> > split_digits(int i, std::vector< std::vector<std::string> > &vector) {
	    if(i >= 10)
	       split_digits(i / 10, vector);

	    vector.push_back(digits.at(i % 10));
	    return vector;
	}

	std::vector< std::vector<std::string> > split_digits(int i) {
		std::vector< std::vector<std::string> > vector {};
		if (i<0) {
			vector.push_back(minus_sign);
			i = -i;
		}

		return split_digits(i, vector);
	}

	std::string lineOfLargeDigits(const std::vector< std::vector<std::string> > &digits_vector, unsigned line_nr, unsigned n){
		std::string line {};
		for_each(digits_vector.begin(), digits_vector.end(), [&](std::vector<std::string> digit){
			line.append(stretchLine(digit[line_nr], n));
			line.append(n/2, ' '); // letter spacing for readability
		});
		return line;
	}


	void printDigitSequence(std::vector< std::vector<std::string> > digits_vector, std::ostream &out, unsigned n){
		unsigned line_nr {0};
		std::ostream_iterator<std::string> out_it(out, "\n");

		// iterate through lines, not digits
		// OPTIMIZE: transpose vector first
		for_each(digits_vector.front().begin(), digits_vector.front().end(), [&](std::string){
			if (line_nr == 1 || line_nr == 3) {
				auto line = lineOfLargeDigits(digits_vector, line_nr, n);
				std::generate_n(out_it, n, [&](){return line;});
			} else {
				out << lineOfLargeDigits(digits_vector, line_nr, n) << '\n';
			}
			line_nr++;
		});
	}

	void printLargeDigit(unsigned i, std::ostream &out, unsigned n) {
		auto digit = digits.at(i);
		std::vector< std::vector<std::string> > single_digit_vector { digit };
		printDigitSequence(single_digit_vector, out, n);
	}

	void printLargeNumber(int i, std::ostream &out, unsigned n) {
		auto digits_vector = split_digits(i);
		printDigitSequence(digits_vector, out, n);
	}

	void printLargeError(std::ostream &out, unsigned n) {
		printDigitSequence(error, out, n);
	}
}
