#include <iostream>

// iostream
using std::cin;
using std::cout;
using std::endl;

int main()
{
	int x;
	int total = 0;
	size_t count = 0;

	// input
	for(count = 0; cin >> x; ++count)
		total += x;
	
	// output
	cout << count << ", " << total << endl;
	return 0;
}//main


