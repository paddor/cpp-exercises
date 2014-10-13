#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include "calc.h"
#include "sevensegment.h"

int main(int argc,char *argv[]){
	printLargeDigit(8, std::cout);
	printLargeDigit(3, std::cout, 3);
	printLargeNumber(30921, std::cout, 3);
	printLargeNumber(-9, std::cout, 3);
	printLargeNumber(-76543, std::cout, 8);

	if (argc == 1) {
		while (std::cin) {
			std::cout << "Please type your input term: ";
			auto result = calc(std::cin);
			printLargeNumber(result, std::cout, 4);
		}
	} else {
		std::vector<std::string> arguments(argv, argv+argc);
		for_each(std::next(arguments.begin()), arguments.end(), [](std::string term) {
			std::istringstream input { term };
			auto result = calc(input);
			std::cout << term << " = \n";
			printLargeNumber(result, std::cout, 4);
		});
	}
}
