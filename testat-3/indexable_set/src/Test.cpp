#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "../indexableSet.h"


void itHasDefaultConstructor() {
	indexableSet<std::string> a;
	ASSERT_EQUAL(0, a.size());
}
void itHasRangeConstructor() {
	std::set<std::string> const a { "foo", "bar", "baz" };
	indexableSet<std::string> b(a.begin(), a.end());
	ASSERT_EQUAL(3, b.size());
}
void itHasCopyConstructor() {
	indexableSet<std::string> a;
	a.insert("foo");
	indexableSet<std::string> b(a);
	ASSERT_EQUAL(1, b.size());
}
void itHasMoveConstructor() {
	indexableSet<std::string> a;
	a.insert("foo");
	indexableSet<std::string> b(std::move(a));
	ASSERT_EQUAL(1, b.size());
}
void itHasInitializerListConstructor() {
	indexableSet<std::string> a { "foo", "bar" };
	ASSERT_EQUAL(2, a.size());
}
void itCanInsert() {
	indexableSet<std::string> a;
	a.insert("foo");
	ASSERT_EQUAL(1, a.size());
}
void itActsAsSetWhenInserting() {
	indexableSet<std::string> a;
	a.insert("bar");
	a.insert("bar");
	ASSERT_EQUAL(1, a.size());
}
void itAccessesInSortedOrder() {
	indexableSet<int> a { 1, 5, 2 };
	auto it = a.begin();
	ASSERT_EQUAL(1, *it++);
	ASSERT_EQUAL(2, *it++);
	ASSERT_EQUAL(5, *it++);
}
void itCanAccessWithPositiveIndex() {
	indexableSet<std::string> a { "bar", "baz", "foo", "quu" };
	ASSERT_EQUAL("bar", a[0]);
	ASSERT_EQUAL("baz", a[1]);
	ASSERT_EQUAL("foo", a[2]);
	ASSERT_EQUAL("quu", a[3]);
}
void itCanAccessWithNegativeIndex() {
	indexableSet<std::string> a { "bar", "baz", "foo", "quu" };
	ASSERT_EQUAL("bar", a[0]);
	ASSERT_EQUAL("quu", a[-1]);
	ASSERT_EQUAL("foo", a[-2]);
	ASSERT_EQUAL(a[0], a[-a.size()]);
}

void itHasFront() {
	indexableSet<std::string> a { "foo", "bar" };
	ASSERT_EQUAL("bar", a.front());
}

void itHasMutableFront() {
	indexableSet<std::string> a { "a", "b" };
	a.front() = "c";
}

void itHasMutableFrontAndCanBreakSet() {
	indexableSet<std::string> a { "a", "b" };
	a.front() = "c";
	ASSERT_EQUAL("c", a.front());
}

void itHasBack() {
	indexableSet<std::string> a { "foo", "bar" };
	ASSERT_EQUAL("foo", a.back());
}

void itThrowsExceptionWhenIndexOutOfBound() {
	indexableSet<std::string> a { "foo", "bar" };
	ASSERT_THROWS(a[2], std::out_of_range);
	ASSERT_THROWS(a[-3], std::out_of_range);
}

void itThrowsExceptionWhenAccessingFrontOrBackOfEmptySet() {
	indexableSet<std::string> a {};
	ASSERT_THROWS(a.front(), std::out_of_range);
	ASSERT_THROWS(a.back(), std::out_of_range);
}

void itCanUseCustomCompareFunctor() {
	struct caselessCompare {
		bool operator()(std::string const& lhs, std::string const& rhs) const {
			return std::lexicographical_compare(
					lhs.begin(), lhs.end(), rhs.begin(), rhs.end(),
					[](char l, char r){ return std::tolower(l) < std::tolower(r);
			});
		}
	};

	indexableSet<std::string, caselessCompare> const a { "foo", "FOO"};
	ASSERT_EQUAL(1, a.size());
}

void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	s.push_back(CUTE(itHasDefaultConstructor));
	s.push_back(CUTE(itHasRangeConstructor));
	s.push_back(CUTE(itHasCopyConstructor));
	s.push_back(CUTE(itHasMoveConstructor));
	s.push_back(CUTE(itHasInitializerListConstructor));
	s.push_back(CUTE(itCanInsert));
	s.push_back(CUTE(itActsAsSetWhenInserting));
	s.push_back(CUTE(itCanAccessWithPositiveIndex));
	s.push_back(CUTE(itCanAccessWithNegativeIndex));
	s.push_back(CUTE(itAccessesInSortedOrder));
	s.push_back(CUTE(itHasFront));
	s.push_back(CUTE(itHasBack));
	s.push_back(CUTE(itThrowsExceptionWhenIndexOutOfBound));
	s.push_back(CUTE(itThrowsExceptionWhenAccessingFrontOrBackOfEmptySet));
	s.push_back(CUTE(itCanUseCustomCompareFunctor));
	s.push_back(CUTE(itHasMutableFront));
	s.push_back(CUTE(itHasMutableFrontAndCanBreakSet));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}
