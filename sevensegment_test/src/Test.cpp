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

void it_prints_large_digit() {
	std::ostringstream output {};
	printLargeDigit(8,output);
	ASSERT_EQUAL(large_8, output.str());
}

void runAllTests(int argc, char const *argv[]){
	cute::suite s { };
	s.push_back(CUTE(it_prints_large_digit));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



