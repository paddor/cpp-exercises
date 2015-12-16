#ifndef INDEXABLESET_H_
#define INDEXABLESET_H_

#include <set>
#include <iterator>
#include <memory>
#include <functional>
#include <stdexcept>

template<
	typename T,
	typename C = std::less<T>,
	typename A = std::allocator<T>
>
class indexableSet: public std::set<T, C, A>
{
public:
	// inherit all set constructors
	using std::set<T, C, A>::set;



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

	T const& front() const {
		if (this->empty()) throw std::out_of_range("container is empty");
		return *this->cbegin();
	}

	T const& back() const {
		if (this->empty()) throw std::out_of_range("container is empty");
		return *prev(this->cend());
	}

	// self-study: only here to verify some semantics of T/T& return type
	// see tests:
	//   * itHasMutableFront
	//   * itHasMutableFrontAndCanBreakSet
	T& front() {
		if (this->empty()) throw std::out_of_range("container is empty");
		return (T&)*this->begin();
	}
};


#endif /* INDEXABLESET_H_ */
