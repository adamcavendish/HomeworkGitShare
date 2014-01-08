#include "../../slist/slist"

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <cctype>
#include <iterator>
#include <algorithm>
#include <string>

class slist_string
{
private:
	__gnu_cxx::slist<char> _M_slist;

private:
	typedef __gnu_cxx::slist<char>				_Base;
	typedef std::size_t							size_type;
	typedef _Base::iterator						iterator;
	typedef _Base::const_iterator				const_iterator;
public:
	explicit slist_string(const char * str) :
		_M_slist(&str[0], &str[strlen(str)])
	{}
	
	iterator begin()
	{ return _M_slist.begin(); }
	const_iterator begin() const
	{ return _M_slist.begin(); }

	iterator end()
	{ return _M_slist.end(); }
	const_iterator end() const
	{ return _M_slist.end(); }

	iterator find_not_in_map(const slist_string & map_str) {
		bool map[256];
		memset(map, 0, sizeof(bool) * 256);

		auto map_end = map_str.end();
		for(auto i = map_str.begin(); i != map_end; ++i)
			map[static_cast<size_type>(*i)] = true;

		auto iter_end = _M_slist.end();
		for(auto i = _M_slist.begin(); i != iter_end; ++i) {
			if(map[static_cast<size_type>(*i)] == false)
				return i;
		}//for

		return iter_end;
	}//find_not_in_map(map_str)

};// class slist_string

int main(int argc, char * argv[])
{
	if(argc != 3)
		return 1;

	slist_string ss(argv[1]);
	slist_string ssmap(argv[2]);

	auto ii = ss.find_not_in_map(ssmap);

	if(ii == ss.end()) {
		std::cout << "Not found!" << std::endl;
	} else {
		int sz = std::distance(ss.begin(), ii);
		std::cout << argv[1] << std::endl;
		std::string space(sz, ' ');
		std::cout << space << '^' << std::endl;
		std::cout << sz << std::endl;
	}//if-else
		
	return 0;
}//main

