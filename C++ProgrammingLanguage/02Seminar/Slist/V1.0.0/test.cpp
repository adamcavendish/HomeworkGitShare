#include "Slist"

#include <iostream>

int main()
{
	Slist<int> s;

	for(int i = 0; i < 10; ++i)
		s.push_front(i);

	for(Slist<int>::iterator i = s.begin(); i != s.end(); ++i)
		cout << *i << endl;
	return 0;
}//main

