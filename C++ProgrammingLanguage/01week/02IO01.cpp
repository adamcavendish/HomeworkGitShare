#include <iostream>
using std::cout;
using std::endl;

int main()
{
	int x, y, k = 0;
	while(cin >> x >> y) {
		cout << "Case " << ++k << ": " << x;
		if(y >= 0) {
			cout << " + " << y;
		} else {
			cout << " - " << -y;
		}// if-else
		cout << " = " << x+y << endl;
	}//while 
	return 0;
}//main

