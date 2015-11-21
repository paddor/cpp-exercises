#include "word.h"
#include "kwic.h"
#include <sstream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <iterator>
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

namespace word_tests {
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

  void it_knows_when_its_empty() {
  	Word word1 { };
  	ASSERT(word1.empty());
  	Word word2 { "foo" };
  	ASSERT(!word2.empty());
  }

  void it_initializes_in_a_vector() {
	  std::vector< Word > line {{"foo"}, {"bar"}};
	  ASSERT_EQUAL(2, line.size());
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

  void it_sorts() {
	  std::vector< Word> words { {"z"}, {"b"}, {"a"}, {"k"} };
	  std::sort(words.begin(), words.end());
	  std::vector< Word> sorted_words { {"a"}, {"b"}, {"k"}, {"z"} };
	  ASSERT_EQUAL(sorted_words, words);
  }


  void add_tests(cute::suite& suite) {
	suite.push_back(CUTE(it_initializes_empty));
	suite.push_back(CUTE(it_initializes_in_a_vector));
	suite.push_back(CUTE(it_reads_input));
	suite.push_back(CUTE(it_constructs_word_from_string));
	suite.push_back(CUTE(it_throws_when_given_empty_string));
	suite.push_back(CUTE(it_throws_when_given_invalid_characters));
	suite.push_back(CUTE(it_compares));
	suite.push_back(CUTE(it_implicitly_converts_to_string));
	suite.push_back(CUTE(it_converts_to_lowercase));
	suite.push_back(CUTE(it_outputs));
	suite.push_back(CUTE(it_inputs));
	suite.push_back(CUTE(it_sorts));
  }
}

namespace kwic_tests {
  const std::string example_input {
	"this is a test\n"
	"this is another test\n"
  };
  const std::vector< std::vector< ::Word > > example_input_lines {
	  { {"this"}, {"is"}, {"a"}, {"test"} },
	  { {"this"}, {"is"}, {"another"}, {"test"} }
  };
  std::string const example_output {
    "a test this is \n"
    "another test this is \n"
    "is a test this \n"
    "is another test this \n"
    "test this is a \n"
    "test this is another \n"
    "this is a test \n"
    "this is another test \n"
  };

  std::vector< std::vector< Word > > const example_output_lines {
    {{"a"}, {"test"}, {"this"}, {"is"}},
    {{"another"}, {"test"}, {"this"}, {"is"}},
    {{"is"}, {"a"}, {"test"}, {"this"}},
    {{"is"}, {"another"}, {"test"}, {"this"}},
    {{"test"}, {"this"}, {"is"}, {"a"}},
    {{"test"}, {"this"}, {"is"}, {"another"}},
    {{"this"}, {"is"}, {"a"}, {"test"}},
    {{"this"}, {"is"}, {"another"}, {"test"}}
  };

  void it_reads_lines() {
    KWIC k {};
    std::ostringstream output {};
    std::istringstream input { example_input };
    k.start(input, output);
    ASSERT_NOT_EQUAL_TO(0, example_input_lines.size());
  }

  void it_rotates_and_sorts() {
    KWIC k {};
    std::ostringstream output {};
    std::istringstream input { example_input };
    k.start(input, output);
    ASSERT_EQUAL(example_output_lines, k.rotated_lines());
  }
  void it_prints_correct_result() {
    KWIC k {};
    std::ostringstream output {};
    std::istringstream input { example_input };
    k.start(input, output);
    ASSERT_EQUAL(example_output, output.str());
  }
  void add_tests(cute::suite& suite) {
	suite.push_back(CUTE(it_rotates_and_sorts));
	suite.push_back(CUTE(it_reads_lines));
	suite.push_back(CUTE(it_prints_correct_result));
  }
}

void runAllTests(int argc, char const *argv[]){
	cute::suite s {};
	word_tests::add_tests(s);
	kwic_tests::add_tests(s);
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



