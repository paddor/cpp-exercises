#include "calc.h"
#include "sevensegment.h"
#include "pocketcalculator.h"

#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <string>
#include <sstream>
#include <limits>
#include <algorithm>

namespace calc_tests {
	constexpr int max { std::numeric_limits<int>::max() },
				  min { std::numeric_limits<int>::min() };
	void multiplies_positive_numbers() {
		ASSERT_EQUAL(20, calc(4, 5, '*'));
	}
	void multiplies_negative_with_positive_number() {
		ASSERT_EQUAL(-30, calc(-6, 5, '*'));
	}
	void multiplies_negative_numbers() {
		ASSERT_EQUAL(20, calc(-4, -5, '*'));
	}
	void recognizes_overflows_when_multiplying() {
		calc(1, max, '*');
		calc(1, min, '*');
		calc(-1, max, '*');
		calc(-1, min+1, '*');
		calc(2, max/2, '*');
		calc(2, min/2, '*');
		calc(-2, max/2, '*');
		calc(-2, min/2+1, '*');

		ASSERT_THROWS(calc(4, max/3, '*'), std::overflow_error);
		ASSERT_THROWS(calc(4, min/3, '*'), std::overflow_error);
		ASSERT_THROWS(calc(-4, max/3, '*'), std::overflow_error);
		ASSERT_THROWS(calc(-4, min/3, '*'), std::overflow_error);
	}
	void divides() {
		ASSERT_EQUAL(5, calc(60, 12, '/'));
		ASSERT_EQUAL(-3, calc(9, -3, '/'));
	}
	void throws_when_dividing_by_zero() {
		ASSERT_THROWS(calc(1, 0, '/'), std::domain_error);
	}
	void adds() {
		ASSERT_EQUAL(5, calc(2, 3, '+'));
		ASSERT_EQUAL(-10, calc(-6, -4, '+'));
	}
	void recognizes_overflows_when_adding() {
		calc(max, 0, '+'); // must not throw
		ASSERT_THROWS(calc(max, 1, '+'), std::overflow_error);
		calc(min, 0, '+'); // must not throw
		ASSERT_THROWS(calc(min, -1, '+'), std::overflow_error);
	}
	void subtracts() {
		ASSERT_EQUAL(17, calc(20, 3, '-'));
		ASSERT_EQUAL(-5, calc(-2, 3, '-'));
	}
	void recognizes_overflows_when_subtracting() {
		calc(max, 0, '-'); // must not throw
		ASSERT_THROWS(calc(max, -1, '-'), std::overflow_error);
		calc(min, 0, '-'); // must not throw
		ASSERT_THROWS(calc(min, 1, '-'), std::overflow_error);
	}
	void knows_modulo() {
		ASSERT_EQUAL(5, calc(15, 10, '%'));
		ASSERT_EQUAL(-5, calc(-15, 10, '%'));
	}
	void throws_when_modulo_zero() {
		ASSERT_THROWS(calc(10, 0, '%'), std::domain_error);
	}
	void throws_when_given_invalid_operator() {
		ASSERT_THROWS(calc(1, 1, '^'), std::runtime_error);
	}

	void takes_term_from_istream() {
		std::istringstream term_stream { "1+1" };
		int result = calc(term_stream);
		ASSERT_EQUAL(2, result);
	}

	const std::vector<std::string> invalid_terms {
        "foobar",
        "3+2-",
        "1",
        "8--",
        "*",
        "4%%6",
        "3//7",
	};

    void throws_when_given_invalid_term() {
		for(auto const term : invalid_terms) {
			std::istringstream term_stream { term };
			ASSERT_THROWS(calc(term_stream), std::exception); // TODO: more specific?
		}
	}

	void add_tests_to_suite(cute::suite& s) {
		s.push_back(CUTE(multiplies_positive_numbers));
		s.push_back(CUTE(multiplies_negative_with_positive_number));
		s.push_back(CUTE(multiplies_negative_numbers));
		s.push_back(CUTE(recognizes_overflows_when_multiplying));
		s.push_back(CUTE(divides));
		s.push_back(CUTE(throws_when_dividing_by_zero));
		s.push_back(CUTE(adds));
		s.push_back(CUTE(recognizes_overflows_when_adding));
		s.push_back(CUTE(subtracts));
		s.push_back(CUTE(recognizes_overflows_when_subtracting));
		s.push_back(CUTE(throws_when_given_invalid_operator));
		s.push_back(CUTE(knows_modulo));
		s.push_back(CUTE(throws_when_modulo_zero));
		s.push_back(CUTE(takes_term_from_istream));
		s.push_back(CUTE(throws_when_given_invalid_term));
	}
}

namespace sevensegment_tests {
	const std::string large_8 {
		" - \n"
		"| |\n"
		" - \n"
		"| |\n"
		" - \n"
	};
	const std::string large_1 {
		"   \n"
		"  |\n"
		"   \n"
		"  |\n"
		"   \n"
	};
	const std::string large_3_scale2 {
		" -- \n"
		"   |\n"
		"   |\n"
		" -- \n"
		"   |\n"
		"   |\n"
		" -- \n"
	};

	void prints_digit() {
		std::ostringstream output {};
		sevensegment::printLargeDigit(8, output, 1);
		ASSERT_EQUAL(large_8, output.str());
		output.str("");
		sevensegment::printLargeDigit(1, output, 1);
		ASSERT_EQUAL(large_1, output.str());
	}
	void prints_scaled_digit() {
		std::ostringstream output {};
		sevensegment::printLargeDigit(3, output, 2);
		ASSERT_EQUAL(large_3_scale2, output.str());
	}
	void throws_when_digit_out_of_range() {
		std::ostringstream output {};
		ASSERT_THROWS(sevensegment::printLargeDigit(10,output, 1),
				std::out_of_range);
	}
	void throws_when_scale_out_of_range() {
		std::ostringstream output {};
		ASSERT_THROWS(sevensegment::printLargeDigit(5,output, 0),
				std::range_error);
	}

	const std::string large_number {
		" -     -  -    \n"
		"|  | |  |  |  |\n"
		" -  -  -  -    \n"
		"  |  |  ||    |\n"
		" -     -  -    \n"
	};

	const std::string large_negative_number {
	"    -  - \n"
	"     |  |\n"
	" -  -  - \n"
	"     |  |\n"
	"    -  - \n"
	};

	void prints_number() {
		std::ostringstream output {};
		sevensegment::printLargeNumber(54321, output, 1);
		ASSERT_EQUAL(large_number, output.str());
	}

	void prints_negative_number() {
		std::ostringstream output {};
		sevensegment::printLargeNumber(-33, output, 1);
		ASSERT_EQUAL(large_negative_number, output.str());
	}

	const std::string large_error {
		" -             \n"
		"|              \n"
		" -  -  -  -  - \n"
		"|  |  |  | ||  \n"
		" -        -    \n"
	};

	void prints_error() {
		std::ostringstream output {};
		sevensegment::printLargeError(output, 1);
		ASSERT_EQUAL(large_error, output.str());
	}

	void throws_when_too_many_digits_for_display() {
		std::ostringstream output {};
		ASSERT_THROWS(sevensegment::printLargeNumber(100000000, output, 1),
				std::overflow_error);
	}

	void add_tests_to_suite(cute::suite& s) {
		s.push_back(CUTE(prints_digit));
		s.push_back(CUTE(prints_scaled_digit));
		s.push_back(CUTE(throws_when_digit_out_of_range));
		s.push_back(CUTE(throws_when_scale_out_of_range));
		s.push_back(CUTE(prints_number));
		s.push_back(CUTE(prints_negative_number));
		s.push_back(CUTE(prints_error));
		s.push_back(CUTE(throws_when_too_many_digits_for_display));
	}
}

namespace pocketcalculator_tests {
	const std::string large_22 {
		" -  - \n"
		"  |  |\n"
		" -  - \n"
		"|  |  \n"
		" -  - \n"
	};

	void gets_term_and_prints_result() {
		std::ostringstream output {};
		std::istringstream input { "2+20" };
		pocketcalculator::start(input, output, 1);
		ASSERT_EQUAL(large_22, output.str());
	}

	void prints_error_on_invalid_input() {
		for(auto const term : calc_tests::invalid_terms) {

			std::ostringstream output {};
			std::istringstream input { term };
			pocketcalculator::start(input, output, 1);
			ASSERT_EQUAL(sevensegment_tests::large_error, output.str());
		}
	}

	const std::string large_2_scale4 {
		" ---- \n"
		"     |\n"
		"     |\n"
		"     |\n"
		"     |\n"
		" ---- \n"
		"|     \n"
		"|     \n"
		"|     \n"
		"|     \n"
		" ---- \n"
	};

	void scales() {
		std::ostringstream output {};
		std::istringstream input {"1+1"};
		pocketcalculator::start(input, output, 4);
		ASSERT_EQUAL(large_2_scale4, output.str());
	}

	const std::string large_2 {
		" - \n"
		"  |\n"
		" - \n"
		"|  \n"
		" - \n"
	};

	void uses_default_scale_when_scale_omitted() {
		std::ostringstream output {};
		std::istringstream input {"1+1"};
		pocketcalculator::start(input, output);
		ASSERT_EQUAL(large_2, output.str());
	}

	void add_tests_to_suite(cute::suite& s) {
		s.push_back(CUTE(gets_term_and_prints_result));
		s.push_back(CUTE(prints_error_on_invalid_input));
		s.push_back(CUTE(scales));
		s.push_back(CUTE(uses_default_scale_when_scale_omitted));
	}

	// TODO: add env scale test
}

void runAllTests(int argc, char const *argv[]){
	cute::suite s {};
	calc_tests::add_tests_to_suite(s);
	sevensegment_tests::add_tests_to_suite(s);
	pocketcalculator_tests::add_tests_to_suite(s);

	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



