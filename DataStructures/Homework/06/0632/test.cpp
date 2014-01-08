#include <iostream>
#include <functional>

template <int n>
struct make_incrementor
{
public:
	int operator() (int x) const {
		return x + n;
	}
};

std::function<int (int)> make_inc(int n) {
	return [=](int x) { return x + n; };
}

int main()
{
	//make_incrementor<42> mi;
	//std::cout << mi(10) << std::endl;
	//std::cout << ii << std::endl;
//	std::cout << make_incrementor<42>(100) << std::endl;
	std::cout << make_inc(42)(10) << std::endl;
	return 0;
}//main

