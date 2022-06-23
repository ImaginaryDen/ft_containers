#ifndef STACK_HPP
#define STACK_HPP
#include <vector>

namespace ft
{
	template<typename T, typename Container = std::vector<T> >
			class stack
			{
			public:
				typedef T value_type;
				typedef typename Container::size_type size_type;
				typedef value_type& reference;
				typedef const value_type& const_reference;

			private:
				Container cont;
			public:

				explicit stack(const Container& cont = Container())
					: cont(cont){}
				stack(const stack& other) : cont(other){}

				stack<T>& operator=(const stack &other)
				{
					cont = other.cont;
					return *this;
				}
				bool empty() const
					{ return (cont.empty()); }
				size_type size() const
					{ return (cont.size()); }
				value_type& top()
					{ return (cont.back()); }
				const value_type& top() const
					{ return (cont.back()); }
				void push (const value_type& val)
					{ cont.push_back(val); }
				void pop()
					{ cont.pop_back(); }

				template <class A, class Cont>
				friend bool operator== (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs){
					return(lhs.cont == rhs.cont);}

				template <class A, class Cont>
				friend bool operator!= (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs){
					return(lhs.cont != rhs.cont);}

				template <class A, class Cont>
				friend bool operator<  (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs){
					return(lhs.cont < rhs.cont);}

				template <class A, class Cont>
				friend bool operator<= (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs){
					return(lhs.cont <= rhs.cont);}

				template <class A, class Cont>
				friend bool operator>  (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs){
					return(lhs.cont > rhs.cont);}

				template <class A, class Cont>
				friend bool operator>= (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs){
					return(lhs.cont >= rhs.cont);}
			};
}
#endif //STACK_HPP