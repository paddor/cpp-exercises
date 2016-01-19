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

	T const& operator[](typename std::set<T, C, A>::difference_type pos) const {
		// Apparently, the following static_cast to a signed type is not needed,
		// although recommended by tutor
//		auto sz = static_cast<typename std::set<T, C, A>
//					::difference_type>(this->size());
//		if (pos < 0) pos += sz;
//		if (pos < 0 || pos >= sz)
//			throw std::out_of_range("index out of bound");

		if (pos < 0) pos += this->size();
		if (pos < 0 || pos >= this->size())
			throw std::out_of_range("index out of bound");

		return *std::next(this->begin(), pos);
	}

	T const& front() const {
		if (this->empty()) throw std::out_of_range("container is empty");
		return *this->cbegin();
	}

	T const& back() const {
		if (this->empty()) throw std::out_of_range("container is empty");
		return *prev(this->cend());
	}

	/* NOTE: Adding at() because it was needed on a subclass of std::list
	 * during the exam of HS2015 on January 20th, 2016. Unfortunately,
	 * I fucked up and wrote:
	 *
	 *   return this->[pos];
	 */
	T const& at(typename std::set<T, C, A>::difference_type pos) const {
		return (*this)[pos];
	}

	// self-study: only here to verify some semantics of T/T& return type
	// see tests:
	//   * itHasMutableFront
	//   * itHasMutableFrontAndCanBreakSet
	T& front() {
		if (this->empty()) throw std::out_of_range("container is empty");
		return const_cast<T&>(*this->begin());
	}
};

#endif /* INDEXABLESET_H_ */
