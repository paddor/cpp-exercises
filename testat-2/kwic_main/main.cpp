#include "kwic.h"
#include <iostream>


int main(int, char*[]) {
	KWIC kwic {};
	kwic.start(std::cin, std::cout);
}
