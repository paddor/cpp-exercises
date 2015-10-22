#ifndef POCKETCALCULATOR_H_
#define POCKETCALCULATOR_H_
#include <iosfwd>

namespace pocketcalculator {
	unsigned const default_scale_factor { 1 };
	void start(std::istream& input, std::ostream& output,
			unsigned const scale_factor = default_scale_factor);
}


#endif /* POCKETCALCULATOR_H_ */
