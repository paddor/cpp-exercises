#include <iostream>
#include <string>
#include <stdexcept>
#include "calc.h"
#include "sevensegment.h"

void display_result_for(std::istream &input, std::ostream &output)
try {
	std::string term {};
	std::getline(input, term);
	auto result = calc(term);
	printLargeNumber(result, output, 3);
} catch(std::logic_error) {
	printLargeError(output, 4);
	printLargeError(output);
}

void pocketcalculator(std::istream &input, std::ostream &output) {
	while (input) {
		output << "Please type your input term: ";
		display_result_for(input, output);
	}
}
