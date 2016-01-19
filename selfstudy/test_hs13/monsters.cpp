#include <string>
#include <iostream>

using std::cout;

struct monster {
	monster() { cout << "a monster is bread\n"; }
	~monster() { cout << "monster killed (name: " << name <<")\n"; }
	virtual std::string const& operator=(std::string const& name_) {
		name = name_;
		return name_;
	}
	void health() { cout << "immortal?\n"; }
	virtual void attack() { cout << "roar\n"; }
private:
	std::string name { "unnamed" };
};

struct troll: monster {
	troll(): monster{} { cout << "a troll grows\n"; }
	~troll() { cout << "troll petrified\n"; }
	void attack() { swing_club(); }
	virtual void swing_club() {
		cout << "clubbing kills me\n";
		myhealth--;
	}
	void health() { cout << "troll-health: " << myhealth << '\n'; }
protected:
	int myhealth { 10 };
};

struct forum_troll: troll {
	forum_troll(): troll{} { cout << "not quite a monster\n"; }
	~forum_troll() { cout << "troll banned\n"; }
	virtual void swing_club() {
		cout << "swinging is healthy\n";
		myhealth++;
	}
	void attack() { cout << "write stupid things\n"; }
};

int main() {
	std::cout << "a --------\n";
	forum_troll ft {};
//	ft = std::string { "ft" };
	std::cout << "--- ft initialized.\n";
	troll t {ft}; // direct-list-initialization, using implicit copy constructor, object-slicing!
//	t = std::string { "t" };
	monster &m{ft}; // reference-initialization
	m = std::string { "m/ft" };

	// a monster is bread
	// a troll grows
	// not quite a monster
	// --- no output from implicit copy constructors
	// -> constructors get called in top->down, of course
	// no need to explicitly call a constructor in the initialization list (": troll{}")

	std::cout << "b --------\n";
	ft.attack();
	t.attack();
	m.attack();
	// write stupid things
	// clubbing kills me         (<--- object is of type troll)
	// write stupid things (<--- not roar, because it's a reference to the original object, and #attack is virtual)

	std::cout << "c --------\n";
	ft.swing_club();
	t.swing_club();
	// swinging is healthy (of course, it's a forum_troll object)
	// clubbing kills me (it's actually a troll object, so it won't call forum_troll#swing_club just because it's virtual)

	std::cout << "d --------\n";
	ft.health();
	t.health();
	m.health();
	// 11 (forum_troll#swing_club has been called once)
	// 8 (troll#swing_club has been called 2)
	// immortal? (reference to same object, but reference is of type monster and #health isn't virtual)

	std::cout << "end ----\n";
	// in reverse order of declaration:
	// m => no output, because object needs to persist for ft
	// t => troll petrified
	//      monster killed (apparently destructors call up the chain)
	// ft => troll banned
	//    => troll petrified
	//    => monster killed (apparently, ~D() always calls ~B())
	//
	//    But: Because some functions are virtual, d'tors should be
	//    virtual as well to guarantee correct cleanup without leaks.
}
