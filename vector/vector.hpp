#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "vector_iterator.hpp"

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

		typedef RandomAccessIterator<value_type> iterator;
		typedef RandomAccessIterator<const value_type> const_iterator;
		/*
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

	vector(const vector& other) : _alloc(allocator_type()), _size(0), _capacity(0)
		{ *this = other; }

	/* Destructor */
	~vector()
	{
		for(size_type i = 0; i < _size; ++i)
			_alloc.destroy(_start + i);
		if(_capacity)
			_alloc.deallocate(_start, _capacity);
	}

	/* operator = */
	vector& operator=(const vector& other)
	{
		if (this == &other)
			return *this;
		for(size_type i = 0; i < _size; ++i)
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
			throw std::out_of_range("vector at out of range");
		return _start[index];
	}

	const_reference at(size_type index) const
	{
		if (index > _size)
			throw std::out_of_range("vector at out of range");
		return _start[index];
	}

	/* reserve() */
	void reserve(size_type n){
		if (n <= _capacity)
			return ;
		pointer new_ptr = _alloc.allocate(n);
		size_type i = 0;
		try{
			for(; i < _size ; ++i)
				_alloc.construct(new_ptr, _start[i]);
		}catch(...){
			for (size_type j = 0; j < i; ++j)
				_alloc.destroy(new_ptr + i);
			_alloc.deallocate(new_ptr, n);
			throw ;
		}
		this->~vector();
		_capacity = n;
		_start = new_ptr;
	}

	/* push_back() */
	void push_back(const_reference value)
	{
		if (_size >= _capacity)
			reserve(_capacity * 2);
		_alloc.construct(_start + _size++, value);
	}

	/* clear */
	void clear(){
		for (size_type i = 0; i < _size; i++)
			_allocator.destroy(_first + i);
		_size = 0;
	}

	/*assign*/
	void assign (size_type n, const value_type& val){
		clear();
		reserve(n);
		for (size_type i = 0; i < n; i++)
			_allocator.construct(_first + i, val);
		_size = n;
	}

	template <class InputIterator> // Поменять 3 аргумент на свой
	void assign (InputIterator first, InputIterator last, typename std::enable_if<!std::is_integral<InputIterator>::value>::type* = 0 ){
		clear();
		push_iterator(first, last);
	}

	/* get_allocator */
	allocator_type get_allocator() const
	{ return _alloc; }

	/* front */
	reference front()
	{ return *_start; }

	const_reference front() const
	{ return *_start; }

	/* back */

	reference back()
	{return _start[size - 1]; }

	const_reference back() const
	{return _start[size - 1]; }

	/* data */
	pointer data()
	{ return _start; }

	/* empty */
	bool empty() const
	{ return _size == 0; }

	/* size */
	size_type size() const
	{ return _size; }

	/* max_size */
	size_type max_size() const{
		return _allocator.max_size();
	}

	/* capacity */
	size_type capacity() const {
		return _capacity;
	}
	/* insert */
	void insert(iterator pos, const_reference val)
	{}

	/* pop_back */
	void pop_back()
	{
		if(!size)/* Нужна ли проверка? */
			return ;
		--_size;
		_alloc.destroy(_start + _size);
	}

	/* resize */
	void resize( size_type count, const_reference value = value_type() )
	{
		reserve(count);
		for(;_size > count; --_size)
			allocator.destroy(_first + _size - 1);
		for(;_size < count;++_size)
			_allocator.construct(_first + _size, val);
	}

	/* swap */
	void swap (vector& other){
		std::swap(_first, other._first);
		std::swap(_size, other._size);
		std::swap(_capacity, other._capacity);
		std::swap(_allocator, other._allocator);

	}

	/* TODO:
	 * после добавления enable_if и is_integral в проект поменять конструктор и в assign
	 * Iterator
	 * Iterator access
	 * insert
	 * erase
	 * Non-member functions
	 * */

private:
	template <class InputIterator>
	void push_iterator(InputIterator first, InputIterator last)
	{
		try
		{
			for (;first != last; ++first)
				push_back(*first);
		}
		catch (...)
		{
			// Подчистить, пока хз что
			throw;
		}
	}
};

}

namespace std{
	template< class T, class Alloc >
	void swap(ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs ) {
		lhs.swap(rhs);
	}
}

#endif //VECTOR_HPP