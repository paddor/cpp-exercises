#ifndef POCKETCALCULATOR_H_
#define POCKETCALCULATOR_H_

#include <iosfwd>

namespace pocketcalculator {
	const unsigned default_scale { 2 }; // TODO: why not 1?
	void start(std::istream& input, std::ostream& output, const unsigned n = default_scale);
	unsigned preferred_scale();
}


#endif /* POCKETCALCULATOR_H_ */
