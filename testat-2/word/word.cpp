#include "word.h"
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <istream>
#include <ostream>
#include <cctype>
#include <iostream>

Word::Word(std::string const &input_string) {
  if(input_string.empty())
    throw std::invalid_argument("given string is empty");

  copy_if(input_string.cbegin(), input_string.cend(), std::back_inserter(data),
     [](char const character) {
  	if (!std::isalpha(character)) throw std::invalid_argument("invalid characters");
  	return true;
    }
  );
}

bool Word::operator==(Word const &other) const { return to_lower() == other.to_lower(); }
bool Word::operator!=(Word const &other) const { return to_lower() != other.to_lower(); }
bool Word::operator>(Word const &other) const { return to_lower() > other.to_lower(); }
bool Word::operator<(Word const &other) const { return other > *this; }
bool Word::operator>=(Word const &other) const { return to_lower() >= other.to_lower(); }
bool Word::operator<=(Word const &other) const { return to_lower() <= other.to_lower(); }

Word::operator std::string() const { return data; }

std::string Word::to_lower() const {
  std::string lower {};
  transform(data.cbegin(), data.cend(), std::back_inserter(lower), (int(*)(int))std::tolower);
  return lower;
}

bool Word::empty() const {
  return data.empty();
}

std::istream& Word::read(std::istream &input_stream) {
  while(!std::isalpha(input_stream.peek()) && !input_stream.eof()) {
    input_stream.ignore(1);
  }

  if(!input_stream || input_stream.eof()) return input_stream;

  while(std::isalpha(input_stream.peek())) {
    data += input_stream.get();
  }

//  if(!input_stream) input_stream.clear(std::ios_base::eofbit);
  return input_stream;
}

std::ostream& Word::print(std::ostream &output_stream) const {
  return (output_stream << data);
}


std::ostream& operator<<(std::ostream &output_stream, Word const &word) {
  return word.print(output_stream);
}
std::istream& operator>>(std::istream &input_stream, Word &word) {
  return word.read(input_stream);
}
