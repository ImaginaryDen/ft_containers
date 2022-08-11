#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "../utility/utility.hpp"
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

	pointer			_first;
	size_type		_size, _capacity;
	allocator_type	_allocator;

public:

	/* Constructor */
	explicit vector( const allocator_type& alloc = allocator_type())
		: _allocator(alloc), _first(NULL), _size(0), _capacity(0) {}

	explicit vector( size_type count, const value_type& value = value_type(), const allocator_type& alloc = allocator_type())
		: _allocator(alloc), _first(NULL), _size(count), _capacity(count)
	{
		_first = _allocator.allocate(count);
		for(size_type i = 0; i < count; ++i)
			_allocator.construct(_first + i, value);
	}

	template <class InputIterator>
	vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
				typename enable_if<!is_integral<InputIterator>::value>::type* = 0 )
		 : _allocator(alloc), _size(0), _capacity(0)
	{
		push_iterator(first, last);
	}

	vector(const vector& other) : _allocator(allocator_type()), _size(0), _capacity(0)
		{ *this = other; }

	/* Destructor */
	~vector()
	{
		for(size_type i = 0; i < _size; ++i)
			_allocator.destroy(_first + i);
		if(_capacity)
			_allocator.deallocate(_first, _capacity);
	}

	/* operator = */
	vector& operator=(const vector& other)
	{
		if (this == &other)
			return *this;
		for(size_type i = 0; i < _size; ++i)
			_allocator.destroy(_first + i);
		_size = 0;
		push_iterator(other.begin, other.end());
	}

	/* operator [] */
	reference operator[](size_type index)
	{
		return _first[index];
	}

	const_reference operator[](size_type index) const
	{
		return _first[index];
	}

	/* at */
	reference at(size_type index)
	{
		if (index > _size)
			throw std::out_of_range("vector at out of range");
		return _first[index];
	}

	const_reference at(size_type index) const
	{
		if (index > _size)
			throw std::out_of_range("vector at out of range");
		return _first[index];
	}

	/* reserve() */
	void reserve(size_type n){
		if (n <= _capacity)
			return ;
		pointer new_ptr = _allocator.allocate(n);
		size_type i = 0;
		try{
			for(; i < _size ; ++i)
				_allocator.construct(new_ptr + i, _first[i]);
		}catch(...){
			for (size_type j = 0; j < i; ++j)
				_allocator.destroy(new_ptr + i);
			_allocator.deallocate(new_ptr, n);
			throw ;
		}
		this->~vector();
		_capacity = n;
		_first = new_ptr;
	}

	/* push_back() */
	void push_back(const_reference value)
	{
		if (_size >= _capacity)
			reserve(_capacity * 2);
		_allocator.construct(_first + _size++, value);
	}

	/* clear */
	void clear(){
		for (size_type i = 0; i < _size; i++)
			_allocator.destroy(_first + i);
		_size = 0;
	}

	/* assign */
	void assign (size_type n, const_reference val){
		clear();
		reserve(n);
		for (size_type i = 0; i < n; i++)
			_allocator.construct(_first + i, val);
		_size = n;
	}

	template <class InputIterator>
	void assign (InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value>::type* = 0 ){
		clear();
		push_iterator(first, last);
	}

	/* get_allocator */
	allocator_type get_allocator() const
	{ return _allocator; }

	/* front */
	reference front()
	{ return *_first; }

	const_reference front() const
	{ return *_first; }

	/* back */
	reference back()
	{return _first[size - 1]; }

	const_reference back() const
	{return _first[size - 1]; }

	/* data */
	pointer data()
	{ return _first; }

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
/*	void insert(iterator pos, const_reference val)
	{}*/

	/* pop_back */
	void pop_back()
	{
		if(!size)/* Нужна ли проверка? */
			return ;
		--_size;
		_allocator.destroy(_first + _size);
	}

	/* resize */
	void resize( size_type count, const_reference value = value_type() )
	{
		reserve(count);
		for(;_size > count; --_size)
			_allocator.destroy(_first + _size - 1);
		for(;_size < count;++_size)
			_allocator.construct(_first + _size, value);
	}

	/* swap */
	void swap (vector& other){
		std::swap(_first, other._first);
		std::swap(_size, other._size);
		std::swap(_capacity, other._capacity);
		std::swap(_allocator, other._allocator);

	}

	iterator begin(){
		return (iterator(_first));
	}
	const_iterator begin() const{
		return (const_iterator(_first));
	}
	iterator end(){
		return (iterator(_first + _size));
	}
	const_iterator end() const{
		return (const_iterator(_first + _size));
	}
/*
	reverse_iterator rbegin(){
		return (reverse_iterator(end()));
	}
	const_reverse_iterator rbegin() const{
		return (const_reverse_iterator(end()));
	}
	reverse_iterator rend(){
		return (reverse_iterator(begin()));
	}
	const_reverse_iterator rend() const{
		return (const_reverse_iterator(begin()));
	}
*/

	iterator insert(iterator pos, const_reference val)
	{
		if (pos < begin() || pos > end())
			throw std::logic_error("vector");
		if (pos == end())
		{	push_back(val);	return --end(); }
		size_type i_pos = begin() - pos;
		if (_size == _capacity)
		{
			_capacity = _capacity * 2 + (_capacity == 0);
			pointer new_ptr = _allocator.allocate(_capacity);
			size_type i = 0;
			try{
				for(; i < _size ; ++i)
					if (i_pos == i)
						_allocator.construact(new_ptr + i, val);
					else
						_allocator.construct(new_ptr + i + (i_pos < i), _first[i]);
			}catch(...){
				for (size_type j = 0; j < i; ++j)
					_allocator.destroy(new_ptr + i);
				_allocator.deallocate(new_ptr, _capacity);
				throw ;
			}
			this->~vector();
			_first = new_ptr;
			return iterator (_first + i_pos);
		}
		for (size_type i = _size; i > i_pos; i--){
			_allocator.destroy(_first + i);
			_allocator.construct(_first + i, *(_first + i - 1));
		}
		_allocator.destroy(&(*pos));
		_allocator.construct(&(*pos), val);
		_size++;
		return iterator(_first + i_pos);
	}

	void insert (iterator position, size_type n, const_reference val){
		if (n == 0)
			return ;
		else if (max_size() - _size < n)
			throw std::length_error("vector");
		difference_type start = position - begin();
		if (_size + n > _capacity){
			size_type new_cap = _capacity * 2 >= _size + n ? _capacity * 2 : _size + n;
			pointer new_arr = _allocator.allocate(new_cap);
			std::uninitialized_copy(begin(), position, iterator(new_arr));
			for (size_type i = 0; i < n; i++)
				_allocator.construct(new_arr + start + i, val);
			std::uninitialized_copy(position, end(), iterator(new_arr + start + n));
			for (size_type i = 0; i < _size; i++)
				_allocator.destroy(_first + i);
			_allocator.deallocate(_first, _capacity);
			_size += n;
			_capacity = new_cap;
			_first = new_arr;
		}
		else {
			for (size_type i = _size; i > static_cast<size_type>(start); i--) {
				_allocator.destroy(_first + i + n - 1);
				_allocator.construct(_first + i + n - 1, *(_first + i - 1));
			}
			for (size_type i = 0; i < n; i++){
				_allocator.destroy(_first + i + start);
				_allocator.construct(_first + i + start, val);
			}
			_size += n;
		}
	}

	template <class InputIterator>
	void insert (iterator position, InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value>::type* = 0){
		size_type count = static_cast<size_type>(std::distance(last, first));
		size_type start = static_cast<size_type>(std::distance(position, begin()));
		if (_size + count > _capacity) {
			size_type new_cap = std::max(_capacity * 2, _size + count);
			pointer new_arr = _allocator.allocate(new_cap);
			std::uninitialized_copy(begin(), position, iterator(new_arr));
			size_type i = 0;
			try {
				for (; i < count; ++i)
					_allocator.construct(new_arr + start + i, *(first + i));
			}
			catch (...){
				for (size_type j = 0; j < i + start; ++j)
					_allocator.destroy(new_arr + j);
				_allocator.deallocate(new_arr, new_cap);
				throw;
			}
			std::uninitialized_copy(position, end(), iterator(new_arr + start + count));
			for (size_type i = 0; i < _size; i++)
				_allocator.destroy(_first + i);
			_allocator.deallocate(_first, _capacity);
			_size += count;
			_capacity = new_cap;
			_first = new_arr;
		}
		else {
			for (size_type i = _size; i > static_cast<size_type>(start); i--) {
				_allocator.destroy(_first + i + count - 1);
				_allocator.construct(_first + i + count - 1, *first + i - 1);
			}
			for (size_type i = 0; i < static_cast<size_type>(count); i++, first++) {
				_allocator.destroy(_first + i + count);
				_allocator.construct(_first + start + i, *first);
			}
			_size += count;
		}
	}

	iterator erase (iterator position){
		size_type i = static_cast<size_type>(std::distance(begin(), position));
		for (; i < _size - 1; ++i){
			_allocator.destroy(_first + i);
			_allocator.construct(_first + i, *(_first + i + 1));
		}
		_size--;
		_allocator.destroy(_first + _size - 1);
		return position;
	}

	iterator erase (iterator first, iterator last){
		difference_type start = std::distance(begin(), first);
		difference_type need_to_copy = std::distance(last, end());
		for(size_type i = 0; first + i != last; ++i)
			_allocator.destroy(&(*(first + i)));
		if(last == end()) {
			size -= std::distance(first, last);
			return end();
		}
		for(size_type i = 0; last + i < end(); ++i)
		{
			_allocator.construct(first + i, *(last + i));
			_allocator.destroy(last + i);
		}
		return first;
	}

	/* TODO:
	 * Iterator +- готово
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