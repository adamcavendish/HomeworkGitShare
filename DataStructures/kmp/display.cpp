#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstddef>
#include <cstring>
#include <string>

static void print(const char * str)
{
	const char * p_str = str;
	while(*p_str != '\0')
		printf(" %c", *p_str++);
}//print(str)

static void print_scnshot(const char * str,
		const char * pattern,
		int * fail,
		int i,
		int j)
{
	/**
	 * Do the print
	 */
	std::cout << "string  :";
	print(str);
	std::cout << std::endl;

	if(j == 0) {
		std::cout << "pattern :" << std::string(2*(i), ' ');
	} else {
		std::cout << "pattern :" << std::string(2*(i-fail[j]), ' ');
	}//if-else
	print(pattern);
	std::cout << std::endl;

	if(j == 0) {
		std::cout << "next    :" << std::string(2*(i), ' ');
	} else {
		std::cout << "next    :" << std::string(2*(i-fail[j]), ' ');
	}//if-else
	for(auto ii = 0u; ii < strlen(pattern); ++ii)
		std::cout << std::right << std::setw(2) << fail[ii];
	std::cout << std::endl;

	std::cout << "comp    :";
	std::cout << std::string(2*i, ' ') << std::right \
		<< std::setw(2) << '^';

	std::cout << "  i: " << i << "  j: " << j << std::endl;

	std::cin.get();
	/**
	 * print end
	 */
}//print_scnshot(str, pattern, fail)

static void preprocess(const char * pattern, int pat_len, int * fail)
{
	int pos = 2, k = -1;
	fail[0] = -1;
	fail[1] = 0;

	while(pos < pat_len) {
		if(k == -1 || pattern[pos] == pattern[k]) {
			++pos;
			++k;
			fail[pos] = k;
		} else {
			k = fail[k];
		}//if-else
	}//while
}//preprocess(pattern, pat_len, fail)

int kmp(const char * str, const char * pattern)
{
	int i = 0, j = 0, pos;
	int str_len = strlen(str);
	int pat_len = strlen(pattern);

	int * fail = new int[pat_len];

	preprocess(pattern, pat_len, fail);

	print_scnshot(str, pattern, fail, i, j);

	while(i < str_len && j < pat_len) {
		if(j == -1 || str[i] == pattern[j]) {
			++i;
			++j;
		} else {
			print_scnshot(str, pattern, fail, i, j);
			j = fail[j];
		}//if-else
	}//while

	if(j >= pat_len) {
		pos = i - pat_len;
	} else {
		pos = -1;
	}//if-else

	delete fail;
	return pos;
}//kmp(str, pattern)

int main(int argc, char * argv[])
{
	if(argc != 3) {
		std::cerr << "Usage: " << argv[0]
			<< " target_string pattern" << std::endl;
		exit(1);
	}//if

	std::cout << "Found at: " << kmp(argv[1], argv[2]) << std::endl;

	return 0;
}//main

