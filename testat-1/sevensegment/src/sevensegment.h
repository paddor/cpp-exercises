#ifndef SEVENSEGMENT_H_
#define SEVENSEGMENT_H_
#include <iosfwd>

namespace sevensegment {
	void printLargeDigit(const unsigned i, std::ostream& out, const unsigned scale_factor);
	void printLargeNumber(const int i, std::ostream& out, const unsigned scale_factor);
	void printLargeError(std::ostream& out, const unsigned scale_factor);
}

#endif /* SEVENSEGMENT_H_ */
