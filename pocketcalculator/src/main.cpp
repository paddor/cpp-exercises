#include <iostream>
#include "sevensegment.h"

int main() {
	printLargeDigit(8, std::cout);
	printLargeDigit(3, std::cout, 3);
	printLargeNumber(30921, std::cout, 3);
	printLargeNumber(-9, std::cout, 3);
	printLargeNumber(-76543, std::cout, 8);
}
