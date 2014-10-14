#ifndef CALC_H_
#define CALC_H_

#include <iosfwd>
#include <string>
int calc(const int a, const int b, const char operator_symbol);
int calc(std::istream &input);
int calc(std::string &term);



#endif /* CALC_H_ */
