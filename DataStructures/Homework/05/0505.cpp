#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <cctype>
#include <cstring>

#define N 1000
static char string_arr[N];

const char * remove_len(char * ptr, std::size_t len)
{
	const std::size_t max_remove = strlen(ptr);

	if(max_remove < len)
		return ptr;

	const std::size_t buffer_len = 1000;
	char * buffer = (char *)malloc(buffer_len);

	std::size_t buffer_sz = (len > buffer_len ? buffer_len : len);

	char * remain = ptr + len;
	std::size_t remain_sz = strlen(remain);

	char * str_end = ptr + remain_sz;

	memcpy(buffer, ptr, buffer_sz);
	memcpy(ptr, remain, remain_sz);
	memcpy(str_end, buffer, buffer_sz);

	free(buffer);

	return str_end;
}//remove_len(ptr, len)

int main(int argc, char * argv[])
{
	if(argc != 4)
		return 1;

	memset(string_arr, 0, N * sizeof(char));

	int init_len = atoi(argv[2]);
	int len = atoi(argv[3]);
	int sz;

	char * ptr = argv[1] + init_len;

	sz = remove_len(ptr, len) - argv[1];

	std::cout << argv[1] << std::endl;
	std::string ss(sz, ' ');
	std::cout << ss << '^' << std::endl;

	return 0;
}//main

