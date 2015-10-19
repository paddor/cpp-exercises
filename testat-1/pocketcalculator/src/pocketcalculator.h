#ifndef POCKETCALCULATOR_H_
#define POCKETCALCULATOR_H_

#include <iosfwd>

namespace pocketcalculator {
	void start(std::istream& input, std::ostream& output, const unsigned n = 1);
	unsigned preferred_scale();
}


#endif /* POCKETCALCULATOR_H_ */
