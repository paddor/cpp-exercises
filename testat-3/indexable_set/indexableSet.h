#ifndef INDEXABLESET_H_
#define INDEXABLESET_H_

#include <set>
#include <iterator>
#include <functional>
#include <cmath>
#include <stdexcept>

template<
	typename T,
	typename C = std::less<T>,
	typename A = std::allocator<T>
>
class indexableSet: public std::set<T, C, A>
{
public:
	// default constructor
	indexableSet(): std::set<T, C, A>{}{};

	// range constructors
	template< typename InputIt >
	indexableSet( InputIt const first, InputIt const last, C const& comp = C(), A const& alloc = A())
	: std::set<T, C, A>{ first, last, comp, alloc} {}

	template< typename InputIt >
	indexableSet( InputIt first, InputIt last, A const& alloc )
	: indexableSet<T, C, A>{ first, last, C(), alloc} {}

	// copy constructor
	indexableSet( indexableSet const& other, A const& alloc = A() )
	: std::set<T, C, A>{ other, alloc} {}

	// move constructor
	indexableSet( indexableSet && other, A const& alloc = A() )
	: std::set<T, C, A>{ other, alloc} {}

	// initializer list constructor
	indexableSet( std::initializer_list<T> init, C const& comp = C(), A const& alloc = A() )
	: std::set<T, C, A>{ init, comp, alloc} {}

	indexableSet( std::initializer_list<T> init, A const& alloc )
	: indexableSet<T, C, A>{ init, C(), alloc} {}

	T operator[](typename std::set<T, C, A>::difference_type pos) {
		if (pos >= 0) {
			if (pos > this->size() - 1) throw std::out_of_range("index out of bound");
			auto it = this->begin();
			advance(it, pos);
			return *it;
		} else {
			auto it = this->end();
			advance(it, pos);
			if (pos < -this->size()) throw std::out_of_range("index out of bound");
			return *it;
		}
	}
	T const operator[](typename std::set<T, C, A>::difference_type pos) const {
		if (pos >= 0) {
			auto it = this->cbegin();
			advance(it, pos);
			if (pos > this->size() - 1) throw std::out_of_range("index out of bound");
			return *it;
		} else {
			auto it = this->cend();
			advance(it, pos);
			if (pos < -this->size()) throw std::out_of_range("index out of bound");
			return *it;
		}
	}

	T front() {
		if (this->empty()) throw std::out_of_range("container is empty");
		return *this->begin();
	}
	T const front() const {
		if (this->empty()) throw std::out_of_range("container is empty");
		return *this->cbegin();
	}

	T back() {
		if (this->empty()) throw std::out_of_range("container is empty");
		return *prev(this->end());
	}
	T const back() const {
		if (this->empty()) throw std::out_of_range("container is empty");
		return *prev(this->cend());
	}
};


#endif /* INDEXABLESET_H_ */
