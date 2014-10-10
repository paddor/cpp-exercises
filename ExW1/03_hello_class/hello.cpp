#include "hello.hpp"
#include <ostream>
class Hello {
	public:
	void sayhello(std::ostream &out){
		out << "Hello, world!\n";
	}
}
