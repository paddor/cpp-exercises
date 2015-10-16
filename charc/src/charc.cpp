#include <iostream>
#include <iterator>
#include <algorithm>

int main() {
	using it = std::istreambuf_iterator<char>;
//	using it = std::istream_iterator<char>;
//	std::noskipws(std::cin);

	size_t count = std::count_if(it {std::cin}, it{}, [](char c) {
		return true; // count all characters
//		return std::isalnum(c); // count alphanumeric characters
	});

	std::cout << count << '\n';
}
