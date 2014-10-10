#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "calc.cpp"

void multiplication() {
	ASSERT_EQUAL(20, calc(4, 5, "*"[0]));
}
void division() {
	ASSERT_EQUAL(5, calc(60, 12, "/"[0]));
}
void division_by_zero() {
	ASSERT_THROWS(calc(1, 0, "/"[0]), std::domain_error);
}
void addition() {
	ASSERT_EQUAL(5, calc(2, 3, "+"[0]));
}
void subtraction() {
	ASSERT_EQUAL(-1, calc(2, 3, "-"[0]));
}
void invalid_operator() {
	ASSERT_THROWS(calc(1, 1, "^"[0]), std::invalid_argument);
}

void runAllTests(int argc, char const *argv[]){
	cute::suite s { };
	s.push_back(CUTE(multiplication));
	s.push_back(CUTE(division));
	s.push_back(CUTE(division_by_zero));
	s.push_back(CUTE(addition));
	s.push_back(CUTE(subtraction));
	s.push_back(CUTE(invalid_operator));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



