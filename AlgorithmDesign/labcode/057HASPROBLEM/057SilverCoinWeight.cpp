#include <iostream>
#include <cstdlib>
#include <algorithm>

std::size_t g_num;
std::size_t g_result;
std::size_t * g_temp;

bool input();
void output();
void calculate();

int main(int argc, char * argv[])
{
	g_temp = new std::size_t[100000];
	while(input()) {
		calculate();
		output();
	}//while

	delete[] g_temp;

	return 0;
}//main

bool input()
{
	std::cin >> g_num;
	if(g_num == 0) {
		return false;
	}//if
	return true;
}//input()

void output()
{
	std::cout << g_num << std::endl;
	std::cout << "Times:" << g_result << std::endl;
}//output()

void calculate()
{
	g_temp[0] = 0;
	g_temp[1] = 0;
	g_temp[2] = 1;
	for(std::size_t iter = 3; iter < g_num; ++iter) {
		std::size_t min_num = 100000000;
		for(std::size_t i = 0; i < iter; ++i) {
			for(std::size_t j = 1; j < i/2; ++j) {
				std::size_t max_num = std::max(g_temp[j], g_temp[i - 2*j] + 1);
				if(max_num < min_num)
					min_num = max_num;
			}//for
		}//for
		g_temp[iter] = min_num;
	}//for

	g_result = g_temp[g_num - 1];
}//calculate()

