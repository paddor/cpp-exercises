#include "pocketcalculator.h"
#include <iostream>
#include <string>

int main(){
	using namespace pocketcalculator;
	auto scale = preferred_scale();

	if (scale != 0) {
		start(std::cin, std::cout, scale);
	} else {
		start(std::cin, std::cout);
	}
}
