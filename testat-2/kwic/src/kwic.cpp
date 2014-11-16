#include "kwic.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <iostream>

void KWIC::start(std::istream &input, std::ostream &output) {
	read_lines(input);
	rotate();
	sort();
	print(output);
}

const std::vector< std::vector< Word > > KWIC::input_lines() {
	return _input_lines;
}
const std::vector< std::vector< Word > > KWIC::rotated_lines() {
	return _rotated_lines;
}

void KWIC::read_lines(std::istream &input) {
	while (!input.eof()) {
		std::string line_string {};
		std::getline(input, line_string);
		std::istringstream line_stream { line_string };

		std::vector< ::Word > line {};
		while (!line_stream.eof()) {
			Word word {};
			line_stream >> word;
			if (word.empty()) break;
			std::cout << "Adding word to line:" << word << "\n";
			line.push_back(word);
		}
		if (line.empty()) break;
        std::cout << "Adding line to lines: " << line.size() << " words\n";
		_input_lines.push_back(line);
	}
}

void KWIC::rotate() {
	for_each(_input_lines.cbegin(), _input_lines.cend(), [this](std::vector< Word > input_line) {
		for(int rotations = input_line.size(); rotations > 0; rotations--) {
			std::vector< Word > rotated_line {};
			std::rotate_copy(input_line.begin(), input_line.begin() + (rotations - 1),
					input_line.end(), std::back_inserter(rotated_line));
			std::cout << "Adding rotated line: \n";
			for_each(rotated_line.begin(), rotated_line.end(), [&](Word word) {
				std::cout << word << "\n";
			});
			_rotated_lines.push_back(rotated_line);
		}
	});
}

void KWIC::sort() {
	std::sort(_rotated_lines.begin(), _rotated_lines.end());
}

void KWIC::print(std::ostream &output) {
	for_each(_rotated_lines.cbegin(), _rotated_lines.cend(), [&](std::vector<Word> line){
		std::ostream_iterator<Word> out_it {std::cout, " "};
		copy(line.begin(), line.end(), out_it);
		output << "\n";
	});
}
