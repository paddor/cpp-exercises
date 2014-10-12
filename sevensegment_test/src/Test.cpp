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

void it_prints_large_8() {
	std::ostringstream output {};
	printLargeDigit(8,output);
	ASSERT_EQUAL(large_8, output.str());
}
void it_prints_large_1() {
	std::ostringstream output {};
	printLargeDigit(1,output);
	ASSERT_EQUAL(large_1, output.str());
}
void it_throws_when_number_out_of_range() {
	std::ostringstream output {};
	ASSERT_THROWS(printLargeDigit(10,output), std::out_of_range);
}

void runAllTests(int argc, char const *argv[]){
	cute::suite s { };
	s.push_back(CUTE(it_prints_large_8));
	s.push_back(CUTE(it_prints_large_1));
	s.push_back(CUTE(it_throws_when_number_out_of_range));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



