#include "calc.cpp"
#include <iostream>

int main(){
	while (std::cin) {
		std::cout << "Please type your term to calculate: ";
		int result = calc(std::cin);
		std::cout << "= " << result << '\n';
	}
}
