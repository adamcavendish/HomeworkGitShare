#include "QuadraticSolver.hpp"

// STL
#include <stdexcept>
#include <cmath>
// Boost
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

std::pair<double, double>
QuadraticSolver::solve() {
	auto iter_bgn = this->equ_.begin();
	if(this->parse(iter_bgn, this->equ_.end())) {
		return this->calculate();
	} else {
		throw std::logic_error("invalid equation at: " + std::string(iter_bgn, this->equ_.end()));
	}//if-else

	return std::make_pair(0, 0);
}//solve()

bool
QuadraticSolver::parse(std::string::iterator & first, const std::string::iterator last) {
	using namespace boost::spirit::qi;
	using boost::phoenix::ref;

	rule<std::string::iterator, double(), ascii::space_type> num_2_expr, num_1_expr, num_0_expr;
	rule<std::string::iterator> expr, rexpr, func_expr;

	num_2_expr = skip(ascii::space)[
		(
			double_[_val = _1] >> -char_('*') >> char_("xX") >> lit("^2")
		) | (
			char_("xX") >> lit("^2")[_val = 1]
		)];

	num_1_expr = skip(ascii::space)[
		(
			double_[_val = _1] >> -char_('*') >> char_("xX") >> -lit("^1")
		) | (
			char_("xX")[_val = 1] >> -lit("^1")
		)];

	num_0_expr = skip(ascii::space)[
			double_[_val = _1] >> -( char_('*') >> char_("xX") >> lit("^0") )
		];

	expr = skip(ascii::space)[
		( num_2_expr[ref(this->x_2_) += _1]
		  | num_1_expr[ref(this->x_1_) += _1]
		  | num_0_expr[ref(this->x_0_) += _1] )];

	rexpr = skip(ascii::space)[
		( num_2_expr[ref(this->x_2_) -= _1]
		  | num_1_expr[ref(this->x_1_) -= _1]
		  | num_0_expr[ref(this->x_0_) -= _1] )];

	func_expr = skip(ascii::space)[
		*expr >> char_('=') >> *rexpr
		];
	
	bool r = phrase_parse(first, last, func_expr, ascii::space);
	if(first != last)
		return false;
	return r;
}//parse(first, last)

std::pair<double, double>
QuadraticSolver::calculate() {
	const double a = this->x_2_;
	const double b = this->x_1_;
	const double c = this->x_0_;

	double x1 = 0.0;
	double x2 = 0.0;
	if(a == 0) {
		// Linear
		if(b == 0) {
			if(c != 0) {
				throw std::logic_error("Equation " + this->equ_ + " has no solution!");
			} else {
				x1 = x2 = 0.0;
			}//if-else
		} else {
			x1 = x2 = -c/b;
		}//if-else
	} else {
		// Quadratic

		double delta = b*b - 4*a*c;
		if(delta < 0)
			throw std::logic_error("Equation " + this->equ_ + " delta < 0!");

		if(b == 0) {
			x1 = x2 = -c/a;
		} else if(b > 0) {
			x1 = (-2*c)/(b + std::sqrt(delta));
			x2 = (-b - std::sqrt(delta))/(2*a);
		} else {
			x1 = (-b + std::sqrt(delta))/(2*a);
			x2 = (-2*c)/(b - std::sqrt(delta));
		}//if-else
	}//if-else

	return std::make_pair(x1, x2);
}//calculate()

