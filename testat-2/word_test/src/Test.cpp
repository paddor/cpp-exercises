#include "word.h"
#include <sstream>
#include <stdexcept>
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

void it_initializes_empty() {
	Word word { };
	ASSERT_EQUAL("", (std::string) word);
}
void it_reads_input() {
	std::istringstream input { "foobar" };
	Word word { };
	word.read(input);
	ASSERT_EQUAL("foobar", (std::string) word);
}
void it_constructs_word_from_string() {
	Word word { "foobar" };
	ASSERT_EQUAL("foobar", (std::string) word);
}

void it_throws_when_given_invalid_characters() {
	ASSERT_THROWS(Word word { "foo bar" }, std::invalid_argument);
	ASSERT_THROWS(Word word { "5bar" }, std::invalid_argument);
	ASSERT_THROWS(Word word { "b.ar" }, std::invalid_argument);
}
void it_throws_when_given_empty_string() {
	ASSERT_THROWS(Word word { "" }, std::invalid_argument);
}

void it_compares() {
	Word foo1 { "foo" };
	Word foo2 { "foo" };
	Word fOo { "fOo" };
	Word bar { "bar" };
	ASSERT(foo1 == foo2);
	ASSERT(foo1 == fOo);
	ASSERT(foo1 != bar);
	ASSERT(bar < foo1);
	ASSERT(bar <= foo1);
	ASSERT(foo1 > bar);
	ASSERT(foo1 >= bar);
}


void it_implicitly_converts_to_string() {
	Word word { "foo" };
	ASSERT_EQUAL("foo", (std::string) word);
}

void it_converts_to_lowercase() {
	Word word { "fOo" };
	ASSERT_EQUAL("foo", word.to_lower());
}

void it_outputs() {
	std::ostringstream output {};
	Word word { "foobar" };
	output << word;
	ASSERT_EQUAL("foobar", output.str());
}

void it_inputs() {
	std::istringstream input { "foobar" };
	Word word { };
	input >> word;
	ASSERT_EQUAL("foobar", (std::string) word);
}


void runAllTests(int argc, char const *argv[]){
	cute::suite s {};
	s.push_back(CUTE(it_initializes_empty));
	s.push_back(CUTE(it_reads_input));
	s.push_back(CUTE(it_constructs_word_from_string));
	s.push_back(CUTE(it_throws_when_given_empty_string));
	s.push_back(CUTE(it_throws_when_given_invalid_characters));
	s.push_back(CUTE(it_compares));
	s.push_back(CUTE(it_implicitly_converts_to_string));
	s.push_back(CUTE(it_converts_to_lowercase));
	s.push_back(CUTE(it_outputs));
	s.push_back(CUTE(it_inputs));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



