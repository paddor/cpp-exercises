#ifndef SEVENSEGMENT_H_
#define SEVENSEGMENT_H_

#include <iosfwd>

void printLargeDigit(unsigned i, std::ostream &out);

// n: scale factor
void printLargeDigit(unsigned i, std::ostream &out, unsigned n);

// same for numbers
void printLargeNumber(int i, std::ostream &out);
void printLargeNumber(int i, std::ostream &out, unsigned n);


#endif /* SEVENSEGMENT_H_ */
