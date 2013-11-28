#pragma once
// STL
#include <limits>
#include <stdexcept>
#include <utility>
// C-STL
#include <cmath>

namespace numerical {

template <typename T, typename Doub>
Doub richardson_extrapolation(T & func, const Doub x, const Doub h, Doub & err) {
	const int ntab = 10;
	const Doub con = 1.4, con2 = (con * con);
	const Doub big = std::numeric_limits<Doub>::max();
	const Doub safe = 2.0;

	int i, j;
	Doub errt, fac, hh, ans = 0;
	Doub a[ntab][ntab];
	
	if(h <= 0.0)
		throw std::invalid_argument("Estimated initial stepsize 'h' should be positive!");

	hh = h;
	a[0][0] = (func(x+hh) - func(x-hh))/(2.0*hh);
	err = big;
	for(i = 1; i < ntab; ++i) {
		hh /= con;
		a[0][i] = (func(x+hh) - func(x-hh))/(2.0*hh);
		fac = con2;

		for(j = 1; j <= i; ++j) {
			a[j][i] = (a[j-1][i]*fac - a[j-1][i-1])/(fac - 1.0);
			fac = con2 * fac;
			errt = std::max(std::abs(a[j][i] - a[j-1][i]), std::abs(a[j][i] - a[j-1][i-1]));
			if(errt <= err) {
				err = errt;
				ans = a[j][i];
			}//if
		}//for
		if(std::abs(a[i][i] - a[i-1][i-1]) >= safe * err)
			break;
	}//for
	return ans;
}//richardson_extrapolation()

}//namespace numerical

