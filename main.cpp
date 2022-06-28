#include <vector>
#include <list>
#include <iostream>
//#include "stack/stack.hpp"
//#include "vector/vector.hpp"

int main()
{
	std::vector<int> a;
	a.resize(100);
	a.resize(10);
	std::cout << a.capacity() << "\n";
	a.at(9);
}