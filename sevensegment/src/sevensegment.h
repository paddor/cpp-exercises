#ifndef SEVENSEGMENT_H_
#define SEVENSEGMENT_H_

#include <iosfwd>

// n: scale factor
void printLargeDigit(unsigned i, std::ostream &out, unsigned n=1);

// same for numbers
void printLargeNumber(int i, std::ostream &out, unsigned n=1);


#endif /* SEVENSEGMENT_H_ */
