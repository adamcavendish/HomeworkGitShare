#pragma once

#include <algorithm>
#include <utility>
#include <string>

class QuadraticSolver
{
public: // functions
	explicit QuadraticSolver(const std::string & s) :
		equ_(s), x_2_(0.0), x_1_(0.0), x_0_(0.0)
	{
		// get rid of all space_types
		this->equ_.erase(std::remove_if(this->equ_.begin(), this->equ_.end(),
					[](char ch) {
						if(ch == ' ' || ch == '\t' || ch == '\n' || ch == '\v' || ch == '\f' || ch == '\r')
							return true;
						return false;
					}), this->equ_.end());
	}

	std::pair<double, double> solve();
private: // functions
	bool parse(std::string::iterator & first, const std::string::iterator last);

	std::pair<double, double> calculate();

private: // member
	std::string equ_;
	double x_2_;
	double x_1_;
	double x_0_;
};//class QuadraticSolver

