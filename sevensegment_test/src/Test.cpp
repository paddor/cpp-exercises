#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "sevensegment.h"
#include <sstream>
#include <string>

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

void it_prints_digit() {
	std::ostringstream output {};
	printLargeDigit(8, output);
	ASSERT_EQUAL(large_8, output.str());
	output.str("");
	printLargeDigit(1, output);
	ASSERT_EQUAL(large_1, output.str());
}
void it_prints_scaled_digit() {
	std::ostringstream output {};
	printLargeDigit(3, output, 2);
	ASSERT_EQUAL(large_3_scale2, output.str());
}
void it_throws_when_digit_out_of_range() {
	std::ostringstream output {};
	ASSERT_THROWS(printLargeDigit(10,output), std::out_of_range);
}

void runAllTests(int argc, char const *argv[]){
	cute::suite s { };
	s.push_back(CUTE(it_prints_digit));
	s.push_back(CUTE(it_prints_scaled_digit));
	s.push_back(CUTE(it_throws_when_digit_out_of_range));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



