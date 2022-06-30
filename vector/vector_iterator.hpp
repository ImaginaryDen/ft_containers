#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include <iterator>

/* Поменять std::iterator_traits на свои классы */

namespace ft{

	template< class L >
	class RandomAccessIterator{
	public:
		typedef	typename std::iterator_traits<L*>::value_type		value_type;
		typedef	typename std::iterator_traits<L*>::pointer			pointer;
		typedef	typename std::iterator_traits<L*>::reference		reference;
		typedef	typename std::iterator_traits<L*>::difference_type	difference_type;
		typedef pointer												iterator_type;
		typedef	std::random_access_iterator_tag						iterator_category;

	private:
		pointer _ptr;
	public:
		RandomAccessIterator() : _ptr(NULL){}
		RandomAccessIterator(pointer ptr) : _ptr(ptr){}
		virtual ~RandomAccessIterator(){}
		// хз чо это remove_const
		/* RandomAccessIterator(const RandomAccessIterator<typename remove_const<value_type>::type > & src) : _ptr(&(*src)) {}
		 * RandomAccessIterator<value_type> & operator=(RandomAccessIterator<typename remove_const<value_type>::type > const & src); */

		RandomAccessIterator & operator++() {
			++_ptr;
			return *this;
		}

		RandomAccessIterator operator++(int) {
			RandomAccessIterator tmp(*this);
			++_ptr;
			return tmp;
		}

		RandomAccessIterator & operator--() {
			--_ptr;
			return *this;
		}

		RandomAccessIterator  operator--(int) {
			RandomAccessIterator tmp = *this;
			--_ptr;
			return tmp;
		}
		RandomAccessIterator operator+(const difference_type & a) const
		{ return _ptr + a; }

		RandomAccessIterator operator-(const difference_type & a) const
		{ return _ptr - a; }

		RandomAccessIterator & operator+=(const difference_type & a) {
			_ptr += a;
			return (*this);
		}

		RandomAccessIterator & operator-=(const difference_type & a) {
			_ptr -= a;
			return (*this);
		}

		pointer operator->() const
		{ return _ptr; }

		reference operator*() const
		{ return *_ptr; }

		reference operator[](difference_type n) const
		{ return *(_ptr + n); }
	};

//	Еще чот нужно дописать
}
#endif //VECTOR_ITERATOR_HPP