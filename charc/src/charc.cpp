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
//	using it = std::istream_iterator<char>;

//	std::noskipws(std::cin);
	size_t count = std::count_if(it {std::cin}, it{}, process_character); // {
//		return true; // count all characters
//		return std::isalnum(c); // count alphanumeric characters
//		std::cout << "processing: '" << c << "' (in_word = " << in_word << ")" << std::endl;

//	});

	std::cout << count << '\n';
}
