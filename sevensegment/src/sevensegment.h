#ifndef SEVENSEGMENT_H_
#define SEVENSEGMENT_H_

#include <iosfwd>

namespace sevensegment {
	// n: scale factor
	void printLargeDigit(const unsigned i, std::ostream &out, const unsigned n=1);

	void printLargeNumber(const int i, std::ostream &out, const unsigned n=1);

	void printLargeError(std::ostream &out, const unsigned n=1);
}

#endif /* SEVENSEGMENT_H_ */
