#ifndef WORD_H_
#define WORD_H_
#include <string>
#include <iosfwd>

class Word {
  std::string data {};
public:
  Word() = default;
  Word(std::string const &input_string);

  bool operator==(Word const &other) const;
  bool operator!=(Word const &other) const;
  bool operator>(Word const &other) const;
  bool operator<(Word const &other) const;
  bool operator>=(Word const &other) const;
  bool operator<=(Word const &other) const;

  operator std::string() const;
  std::string to_lower() const;
  bool empty() const;

  std::ostream& print(std::ostream &output_stream) const;
  std::istream& read(std::istream &input_stream);
};

std::ostream& operator<<(std::ostream &output_stream, Word const &word);
std::istream& operator>>(std::istream &input_stream, Word &word);

#endif /* WORD_H_ */
