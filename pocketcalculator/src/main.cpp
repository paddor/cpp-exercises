#include <iostream>
#include "sevensegment.h"

int main() {
	printLargeDigit(8, std::cout);
	printLargeDigit(3, std::cout, 3);
	printLargeDigit(5, std::cout, 4);
	printLargeDigit(7, std::cout, 4);
}
