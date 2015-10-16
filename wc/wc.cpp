#include <iostream>
#include <iterator>
#include <algorithm>


bool process_character(const char c) {
	static bool in_word = false;

	if (std::isalnum(c)) {
		if (! in_word) {
			in_word = true;
			return true;
		}
	} else {
		if (in_word) in_word = false;
	}
	return false;
}

int main() {
	using it = std::istreambuf_iterator<char>;

	size_t count = std::count_if(it {std::cin}, it{}, process_character);
	std::cout << count << '\n';
}
