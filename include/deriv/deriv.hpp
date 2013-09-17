#pragma once

#include <limits>

namespace numerical {

template <typename T, typename Doub>
Doub richardson_extrapolation(T & func, const Doub x, const Doub h, Doub & err);

template <typename T>
inline float deriv(T & func, const float x)
{
	float err;
	return richardson_extrapolation<T, float>(func, x, 0.1, err);
}

template <typename T>
inline double deriv(T & func, const double x)
{
	double err;
	return richardson_extrapolation<T, float>(func, x, 0.1, err);
}

template <typename T>
inline long double deriv(T & func, const long double x)
{
	long double err;
	return richardson_extrapolation<T, float>(func, x, 0.1, err);
}

}//namespace numerical

#include "deriv.tcc"

