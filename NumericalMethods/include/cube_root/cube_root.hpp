#pragma once

// STL
#include <limits>

namespace numerical {

/**
 * Cube root algorithm: f(x) = x^3 - A
 * The recurrence function:
 *		p_k = (2*p_(k-1) + A/p_(k-1)^2)/3, with k = 1, 2, ...
 * Using Newton-Raphson Approximation Algorithm
 */
template <typename Doub>
Doub cube_root(const Doub x, const Doub estimation, const Doub epsilon);

inline float cube_root(const float x)
{ return cube_root<float>(x, 1, std::numeric_limits<float>::epsilon()); }

inline double cube_root(const double x)
{ return cube_root<double>(x, 1, std::numeric_limits<double>::epsilon()); }

inline long double cube_root(const long double x)
{ return cube_root<long double>(x, 1, std::numeric_limits<long double>::epsilon()); }

}//namespace numerical

#include "cube_root.tcc"

