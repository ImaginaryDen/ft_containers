#include <vector>
#include <iostream>
#include "stack/stack.hpp"

int main()
{
	std::vector<int> arr = {1, 2, 3, 4, 5};
	ft::stack<int> d(arr);

	while(!d.empty())
	{

		std::cout << d.top() << ' ';
		d.pop();
	}
	std::cout << std::endl;
}