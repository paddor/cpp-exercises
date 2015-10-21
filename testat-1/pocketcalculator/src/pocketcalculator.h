#ifndef POCKETCALCULATOR_H_
#define POCKETCALCULATOR_H_
#include <iosfwd>

namespace pocketcalculator {
	const int default_scale_factor = 1;
	void start(std::istream& input, std::ostream& output,
			const unsigned scale_factor = default_scale_factor);
}


#endif /* POCKETCALCULATOR_H_ */
