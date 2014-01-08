#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cctype>

// cstdio
// using std::fprintf;
// using std::fputc;
// cstdlib
using std::srand;
// ctime
using std::time;
// cctype
using std::atol;

int main(int argc, char *argv[])
{
	srand(time(NULL));
	FILE *fd;
	static size_t rand_num;
	static long rand_min = 0L;
	static long rand_max = 1000000L;

	fd = fopen("unsorted.txt", "w");
	
	switch(argc) {
	case 2:
		rand_num = atol(argv[1]);
		break;
	case 3:
		rand_num = atol(argv[1]);
		rand_max = atol(argv[2]);
		break;
	case 4:
		rand_num = atol(argv[1]);
		rand_min = atol(argv[2]);
		rand_max = atol(argv[3]);
		break;
	default:
		printf("Usage: %s rand_num\n", argv[0]);
		printf("Usage: %s rand_num rand_max\n", argv[0]);
		printf("Usage: %s rand_num rand_min rand_max\n", argv[0]);
		break;
	}//switch

	for(int i = 1; i <= rand_num; ++i) {
		if(i % 10 == 0)
			fputc('\n', fd);
		fprintf(fd,
				"%ld ",
				(long)(rand() * (rand_max - rand_min)/RAND_MAX
					+rand_min)); 
	}//for
	
	fclose(fd);
	
	return 0;
}//main

