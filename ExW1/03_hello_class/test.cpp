#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "hello.cpp"
#include <sstream>
TEST_CASE("says hello") {
	auto os = std::ostringstream();
	auto h = Hello();
	h.sayhello(os);
	REQUIRE("Hello, world!\n" == os.str());
}

