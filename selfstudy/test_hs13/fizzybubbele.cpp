#include <iostream>
#include <string>
#include <set>

int main() {
	using namespace std;
	string sekt { "FizzyBubbele" };
	cout << oct << sekt.size() << dec << '\n'; // *** 0 *** => 14 (octal 12)

	set<char> const s { sekt.cbegin(), sekt.cend() }; // B,F,b,e,i,l,y,z
	cout << s.size() << '\n'; // *** 1 *** => 8

	cout << ++*sekt.begin() << '\n'; // *** 2 *** => G (++'F')

	cout << *s.rbegin() << '\n'; // *** 3 *** => z

	auto it1 = s.begin(); ++it1;
	cout << *it1 << '\n'; // *** 4 *** => F

	cout << "----\n";


	// test
	std::copy(sekt.crbegin(),sekt.crend(),
              std::ostream_iterator<char>(std::cout, " "));
	cout << "\n";

	auto it2 = sekt.crend(); advance(it2, 3);
	cout << *it2 << '\n'; // *** 5 *** => UNDEFINED BEHAVIOR

	auto it3 = sekt.end(); --it3; it3--;
	cout << *--it3 << '\n'; // *** 6 *** => e

	auto it4 = s.end();
//	cout << *   it4   << '\n'; // *** 7 *** Output: y
	cout << *--(--it4) << '\n'; // *** 7 *** Output: y


	cout << "END ----\n";

}
