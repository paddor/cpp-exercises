#include "calc.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <iterator>

int main(int argc,char *argv[]){
	if (argc == 1) {
		while (std::cin) {
			std::cout << "Please type your input term: ";
			int result = calc(std::cin);
			std::cout << "= " << result << '\n';
		}
	} else {
		std::vector<std::string> arguments(argv, argv+argc);
		for_each(std::next(arguments.begin()), arguments.end(), [](std::string term) {
			std::istringstream input { term };
			auto result = calc(input);
			std::cout << term << " = " << result << '\n';
		});
	}
}
