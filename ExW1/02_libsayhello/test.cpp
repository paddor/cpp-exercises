#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "sayhello.hpp"
#include <sstream>
TEST_CASE("says hello") {
	auto os = std::ostringstream();
	sayhello(os);
	REQUIRE("Hello, world!\n" == os.str());
}

