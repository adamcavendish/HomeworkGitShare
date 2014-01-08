#include "regex.hpp"
#include <cassert>

int main()
{
	assert(match("tes*t", "< test") == 1);
	assert(match("te.*t", "tessssst") == 1);
	assert(match("tes*t", "tieist") == 0);
	assert(match("tes*t", "testing") == 1);
	assert(match("<a href=.*>", "<a href=http://www.pass-e.com></a>")
			== 1);
	assert(match("^$", "") == 1);
	assert(match("tes*/*t", "tessssss*t") == 1);
	assert(match("te.t", "text") == 1);
	assert(match("te.t", "te\nt") == 0);

	return 0;
}//main


