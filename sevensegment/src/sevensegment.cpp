#include <ostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include "sevensegment.h"

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

std::string stretchLine(const std::string &line, unsigned n) {
	std::string stretched_line(n+2, line[1]);
	stretched_line.front() = line[0];
	stretched_line.back() = line[2];
	return stretched_line;
}

void printLargeDigit(unsigned i, std::ostream &out) {
	printLargeDigit(i, out, 1);
}

void printLargeDigit(unsigned i, std::ostream &out, unsigned n) {
	auto digit = digits.at(i);
	std::ostream_iterator<std::string> out_it(out, "\n");
	auto second_line = stretchLine(digit[1], n);
	auto fourth_line = stretchLine(digit[3], n);

	out << stretchLine(digit[0], n) << '\n';
	std::generate_n(out_it, n, [&](){return second_line;});
	out << stretchLine(digit[2], n) << '\n';
	std::generate_n(out_it, n, [&](){return fourth_line;});
	out << stretchLine(digit[4], n) << '\n';
}
