#include <iostream>
#include <sstream>
#include <string>

// iostream
using std::cout;
using std::cin;
using std::endl;
// sstream
using std::istringstream;
// string
using std::string;

int main()
{
	string line;
	int x, sum, count, case_cnt = 0;

	while(getline(cin, line)) {
		istringstream iss_line(line);
		sum = 0;
		count = 0;
		while(iss_line >> x) {
			sum += x;
			++count;
		}//while
		cout << "Case " << ++case_cnt << ": "
			<< count << ", " << sum << endl;
	}//while

	return 0;
}//main

