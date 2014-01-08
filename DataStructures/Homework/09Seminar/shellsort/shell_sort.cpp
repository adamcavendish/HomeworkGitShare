#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

void SHELL_SORT_ASCENDING_V2(int a[], int N)
{
	int i, j, increment;
	int temp;
	long sedgewick[] = {		// Sedgewick增量
		1073643521, 603906049, 268386305, 150958081, 67084289,
		37730305, 16764929, 9427969, 4188161, 2354689,
		1045505, 587521, 260609, 146305, 64769,
		36289, 16001, 8929, 3905, 2161,
		929, 505, 209, 109, 41,
		19, 5, 1, 0
	};		//用 0 标记终点
	long *sed = sedgewick;
	
	for(; *sed > N; ++sed);		//增量必须小于元素个数
	
	for(increment = *sed; increment > 0; increment >>= 1) {
		for(i = increment; i < N; ++i) {
			temp = a[i];
			for(j = i; (j >= increment) && (temp < a[j - increment]); j -= increment)
					a[j] = a[j - increment];
			a[j] = temp;
		}//for
	}//for
}//SHELL_SORT_ASCENDING_V2(a, N)

void SHELL_SORT_ASCENDING(int a[], int BGN, int END)
{
	int i, j, increment;
	int temp;
	int N = END - BGN + 1;
	
	for(increment = N/2; increment > 0; increment >>= 1) {
		for(i = BGN + increment; i <= END; ++i) {
			temp = a[i];
			for(j = i; (j >= BGN + increment) && (temp < a[j - BGN - increment]); j -= increment)
					a[j] = a[j - increment];
			a[j] = temp;
		}//for
	}//for
}//SHELL_SORT_ASCENDING(a, BGN, END)


int main()
{
	const int maxn = 100000;
	int nums[maxn];
	
	int k;
	fstream file("test.out", fstream::out);
	
	srand(time(NULL));
	for(k = 0; k < maxn; k++)
		nums[k] = rand()%1000000;
	
	SHELL_SORT_ASCENDING_V2(nums, maxn);
	
	for(k = 0; k < maxn; k++)
		file << nums[k] << std::endl;
	
	file.close();
	return 0;
}
