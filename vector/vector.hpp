#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>

namespace ft{

template< class T, class Allocator = std::allocator<T> >
class vector{

public:
		typedef T value_type;
		typedef Allocator allocator_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;
		/*
		typedef RandomAccessIterator<value_type> iterator;
		typedef RandomAccessIterator<const value_type> const_iterator;
		typedef reverse_iterator<const_iterator> const_reverse_iterator;
		typedef reverse_iterator<iterator> reverse_iterator;
		 */

private:

	pointer			_start;
	size_type		_size, _capacity;
	allocator_type	_alloc;

public:

	/* Constructor */
	explicit vector( const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _start(NULL), _size(0), _capacity(0) {}

	explicit vector( size_type count, const value_type& value = value_type(), const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _start(NULL), _size(count), _capacity(count)
	{
		_start = _alloc.allocate(count);
		for(size_type i = 0; i < count; ++i)
			_alloc.construct(_start + i, value);
	}

	/* Изменить последний аргумент на свой */
	template <class InputIterator>
	vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
				typename std::enable_if<!std::is_integral<InputIterator>::value>::type* = 0 )
		 : _alloc(alloc), _size(0), _capacity(0)
	{
		push_iterator(first, last);
	}

	vector(const vector& other) : _alloc(allocator_type()) _size(0), _capacity(0)
		{ *this = other }

	/* Destructor */
	~vector()
	{
		for(size_type i = 0; i < size; ++i)
			_alloc.destroy(_start + i);
		if(_capacity)
			_alloc.deallocate(_start, _capacity);
	}

	/* operator = */
	vector& operator=(const vector& other)
	{
		if (this == &x)
			return *this;
		for(size_type i = 0; i < size; ++i)
			_alloc.destroy(_start + i);
		_size = 0;
		push_iterator(other.begin, other.end());
	}

	/* operator [] */
	reference operator[](size_type index)
	{
		return _start[index];
	}

	const_reference operator[](size_type index) const
	{
		return _start[index];
	}

	/* at */
	reference at(size_type index)
	{
		if (index > _size)
			throw std::out_of_range;
		return _start[index];
	}

	const_reference at(size_type index) const
	{
		if (index > _size)
			throw std::out_of_range;
		return _start[index];
	}




	/* TODO:
	 * после добавления enable_if и is_integral в проект поменять конструктор
	 * assign
	 * get_allocator
	 * front
	 * back
	 * data
	 * Iterator
	 * Iterator access
	 * empty
	 * size
	 * max_size
	 * reserve
	 * capacity
	 * clear
	 * insert
	 * emplace
	 * erase
	 * push_back
	 * pop_back
	 * resize
	 * swap
	 * Non-member functions
	 * erase*/

private:
	template <class InputIterator>
	void push_iterator(InputIterator first, InputIterator last)
	{
		try
		{
			for (;first != last; ++first)
				/*push_back(*first)*/;
		}
		catch (...)
		{
			// Подчистить, пока хз что
			throw;
		}
	}
};

}

#endif //VECTOR_HPP