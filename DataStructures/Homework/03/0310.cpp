//#include <ext/slist>
#include "slist"
#include <vector>
#include <string>
#include <initializer_list>
#include <cstring>
#include <cmath>
#include <iostream>

class polynomial : public __gnu_cxx::slist<double>
{
	typedef __gnu_cxx::slist<double>			_slist;
public:
	polynomial() : _slist()
	{}

	explicit polynomial(std::initializer_list<double> li) : _slist(li)
	{}//initializer_list constructor
	
	template <typename InputIterator>
	polynomial(InputIterator __first, InputIterator __last) :
		_slist(__first, __last)
	{}//range constructor

	double calc(double __x) {
		auto __iter = this->begin();
		auto __iter_end = this->end();
		double ret = 0;

		for(size_type count = 0; __iter != __iter_end; ++__iter, ++count)
			ret += pow(__x, count) * (*__iter);

		return ret;
	}//calc(value)
};//class polynomial	

int main(int argc, char * argv[])
{
	polynomial p({3, 2, 1});

	std::cout << p.calc(10.24) << std::endl;

	return 0;
}//main

