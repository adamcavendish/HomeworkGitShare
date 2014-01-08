/**
*	[Mark Allen Weiss]指出，最好的增量序列是
*	Sedgewick提出的 (1, 5, 19, 41, 109,...)，
*	该序列的项来自 9 * 4^i - 9 * 2^i + 1 和 4^i - 3 * 2^i + 1 这两个算式。
*/

#include <iostream>
#include <cmath>

int main() {
	int i, j;
	int maxn = 13;
	
	for(i = maxn; i >= 0; --i) {
		std::cout << (long)(pow(4, i+2) - 3 * pow(2, i+2) + 1) << ' ';
		std::cout << (long)(9 * (pow(4, i) - pow(2, i)) + 1) << ' ';
	}//for
	std::cout << std::endl;
	
	return 0;
}//main