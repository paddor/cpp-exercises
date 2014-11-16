#ifndef KWIC_H_
#define KWIC_H_
#include "word.h"
#include <iosfwd>
#include <vector>

class KWIC {

public:
  void start(std::istream &input_stream, std::ostream &output_stream);
  const std::vector< std::vector< Word > > input_lines();
  const std::vector< std::vector< Word > > rotated_lines();

private:
  std::vector< std::vector< Word > > _input_lines {};
  std::vector< std::vector< Word > > _rotated_lines {};
  void read_lines(std::istream &input_stream);
  void rotate();
  void sort();
  void print(std::ostream &output_stream);
};

#endif /* KWIC_H_ */
