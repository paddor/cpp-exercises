#include <iostream>
int main() {
	bool cond = true;
//	std::cout << cond ? "Hello" : "Peter"; // wrong
	std::cout << (cond ? "Hello" : "Peter");
}
