/**
*	[Mark Allen Weiss]ָ������õ�����������
*	Sedgewick����� (1, 5, 19, 41, 109,...)��
*	�����е������� 9 * 4^i - 9 * 2^i + 1 �� 4^i - 3 * 2^i + 1 ��������ʽ��
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