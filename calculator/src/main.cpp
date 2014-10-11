#include "calc.cpp"
#include <iostream>

int main(){
	while (std::cin) {
		std::cout << "Please type your input term: ";
		int result = calc(std::cin);
		std::cout << "= " << result << '\n';
	}
}
