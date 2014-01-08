#pragma once

namespace adamcavendish {
namespace graph {
namespace detail {

template <
	bool if_condition,
	typename true_type,
	typename false_type>
struct meta_if
{
	typedef true_type type;
};//struct meta_if

template <
	bool if_condition,
	typename true_type,
	typename false_type>
struct meta_if<false, true_type, false_type>
{
	typedef false_type type;
};//struct meta_if

}//namespace detail
}//namespace graph
}//namespace adamcavendish

