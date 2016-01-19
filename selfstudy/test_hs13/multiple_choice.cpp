#include <iostream>

int main() {
	std::cout << "test output\n";

	std::unique_ptr<int> p {};

	if (p == nullptr)
		std::cout << "p is nullptr\n";

	if (p == nullptr && !p)
		std::cout << "(p == nullptr && !p) == true\n";

	enum class X {a, b, c};
	enum class Y:int {a=0, b, c=2};

	enum X x { X::b };
	enum Y y { Y::b };
	std::cout << "enums x: " << static_cast<int>(x) << '\n';
	std::cout << "enums y: " << static_cast<int>(y) << '\n';

	return 0;
}
