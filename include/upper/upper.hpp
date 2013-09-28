#pragma once

// Numerical
#include "../matrix/matrix.hpp"
// STL
#include <algorithm>
#include <stdexcept>
// C-STL

template <typename T>
void upper(matrix<T> & A) {
	if(A.row() != A.col())
		throw std::runtime_error("Not a square matrix");

	if(A.row() == 0 || A.col() == 0)
		throw std::runtime_error("Empty or malform matrix");
	if(A.row() == 1 && A.col() == 1)
		return;
	
	for(std::size_t i = 0; i < A.row(); ++i) {
		T big = A(i, 0);
		for(std::size_t j = 0; j < A.col(); ++j) {
			if(big < A(i, j), 
		}//for
	}//for
}//upper(matrix)

template <typename T>
void upper(matrix<T> & A, matrix<T> & B) {

}//upper(matrix)

