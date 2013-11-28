#include "cube_root.hpp"

// STL
#include <stdexcept>
// C-STL
#include <cmath>

namespace numerical {

template <typename Doub>
Doub cube_root(const Doub x, const Doub estimation, const Doub epsilon) {
	if(epsilon < 0)
		throw std::invalid_argument("epsilon should be positive!");

	Doub p0 = estimation;
	Doub p1;
	Doub err;
	do {
		p1 = (2*p0 + x/(p0 * p0))/3;
		err = std::abs(p1 - p0);
		p0 = p1;
	} while(err > epsilon);

	return p0;
}//cube_root(x, err)

}//namespace numerical

