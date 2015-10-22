#ifndef SEVENSEGMENT_H_
#define SEVENSEGMENT_H_
#include <iosfwd>

namespace sevensegment {
	void printLargeDigit(unsigned const i, std::ostream& out, unsigned const scale_factor);
	void printLargeNumber(int const i, std::ostream& out, unsigned const scale_factor);
	void printLargeError(std::ostream& out, unsigned const scale_factor);
}

#endif /* SEVENSEGMENT_H_ */
