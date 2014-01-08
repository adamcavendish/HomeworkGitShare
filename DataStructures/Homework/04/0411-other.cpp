#include "../../queue/queue"

#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <cctype>
#include <stdexcept>
#include <string>
#include <vector>

template <typename INT_TYPE = std::size_t>
struct binomial
{
	// member variables
	std::vector<INT_TYPE *>	_M_row_vec;
	const std::size_t		diff_tolerence = 1024;

	explicit binomial(INT_TYPE __exp = 10u)
	{ _M_row_vec.reserve(__exp + 1); }

	void init_row(INT_TYPE row_num) {
		if(_M_row_vec.size() < row_num + 1)
			_M_row_vec.resize(row_num + 1, nullptr);

		if(_M_row_vec.at(row_num) == nullptr) {
			_M_row_vec[row_num] = new INT_TYPE[row_num + 1];

			// case: C(0,0)
			if(row_num == 0) {
				_M_row_vec[0][0] = 1;
			} else {
				_M_row_vec[row_num][0] = _M_row_vec[row_num][row_num] = 1;
			}//if-else

			if(row_num > 1) {
				init_row(row_num-1);
				for(INT_TYPE __col = 1; __col < row_num; ++__col) {
					_M_row_vec[row_num][__col] =
						_M_row_vec[row_num - 1][__col - 1] +
						_M_row_vec[row_num - 1][__col];
				}//for
			}//if
		}//if
	}//init_row(row_num)

	// return C(m, n) -- C(m, n) = C(m-1, n-1) + C(m-1, n)
	INT_TYPE get(INT_TYPE m, INT_TYPE n) {
		if(m > n)
			throw std::domain_error("C(m, n): m cannot be greater than n!");
		long long ret = 1;

		if(_M_row_vec.size() + diff_tolerence > n) {
			init_row(n);
			ret = _M_row_vec[n][m];
		} else {
			for(std::size_t __i = n; __i > n-m; --__i)
				ret *= __i;
			for(std::size_t __i = m; __i > 0; -- __i)
				ret /= __i;
		}//if-else
		return ret;
	}//get(m, n)
};//struct binomial

	static binomial<> bin(2048);

std::string binomial_pic(int __exp)
{
	//static binomial<> bin(__exp);
	std::string ret;
	for(auto __row = 0; __row <= __exp; ++__row) {
		for(auto __col = 0; __col <= __row; ++__col) {
			ret += std::to_string(bin.get(__col, __row));
			ret += ' ';
		}//for
		ret += '\n';
	}//for
	
	return ret;
}//binomial_pic(__exp)

int main(int argc, char * argv[])
{
	int exp;
	if(argc != 2)
		return 1;
	exp = atoi(argv[1]);
	
	std::cout << binomial_pic(exp);

	return 0;
}//main

