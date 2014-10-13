#ifndef CALC_H_
#define CALC_H_

#include <iosfwd>
#include <string>
int calc(int a, int b, char operator_symbol);
int calc(std::istream &input);
int calc(std::string &term);



#endif /* CALC_H_ */
