#include "../../queue/queue"

#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <stdexcept>
#include <cstring>
#include <string>
#include <cctype>
using namespace adamcavendish::data_structure;

std::string binomial_pic(std::size_t __exp) {
	std::string ret("1\n");
	queue<int> que_cache;

	que_cache.push(1);
	que_cache.push(1);

	for(auto __row = 2u; __row <= __exp + 1; ++__row) {
		que_cache.push(1);	// next row init
		ret += "1 ";
		for(auto __col = 1u; __col < __row; ++__col) {
			int __tmp = que_cache.back();
			que_cache.pop();
			__tmp += que_cache.back();
			que_cache.push(__tmp);

			ret += std::to_string(que_cache.back());
			ret += ' ';
		}//for
		que_cache.pop();
		que_cache.push(1);
		ret += '\n';
	}//for

	return ret;
}//binomial_pic(__exp)

int main(int argc, char * argv[])
{
	if(argc != 2)
		return 1;

	std::size_t exp = atoi(argv[1]);

	std::cout << binomial_pic(exp);

	return 0;
}//main

