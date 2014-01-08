#include <algorithm>
#include <iostream>
#include <string>
#include <limits>

// alogrithm
using std::equal;
// iostream
using std::cin;
using std::cout;
using std::endl;
// string
using std::string;
// limits
using std::numeric_limits;

inline bool is_palindrome(string word) { return equal(word.begin(), word.end(), word.rbegin()); }

int main()
{
	size_t case_num;
	string word;
	
	cin >> case_num;
	cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

	for(int i = 0; i < case_num; ++i) {
		getline(cin, word);
		cout << "Case " << i << ": " << (is_palindrome(word) ? "YES." : "NO.") << endl;
	}//for

	return 0;
}//main

