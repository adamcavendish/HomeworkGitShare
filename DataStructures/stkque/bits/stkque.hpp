#pragma once

#include "../../stack/stack"

namespace adamcavendish {
namespace data_structure {

template <typename T>
class stkque
{
public: // member types
	typedef T				value_type;
	typedef T *				pointer;
	typedef T &				reference;
	typedef const T *		const_pointer;
	typedef const T &		const_reference;
	typedef std::size_t		size_type;
protected: // member variables
	stack<value_type> _M_in_stack;
	stack<value_type> _M_out_stack;
public: // member functions
	/**
	 * --------------------------------------------------
	 *  Constructors and destructor
	 * --------------------------------------------------
	 */
	explicit stkque()
	{}

	explicit stkque(const stkque & __other) :
		_M_in_stack(__other._M_in_stack),
		_M_out_stack(__other._M_out_stack)
	{}// copy constructor

	explicit stkque(stkque && __other) :
		_M_in_stack(std::move(__other._M_in_stack)),
		_M_out_stack(std::move(__other._M_out_stack))
	{}// move constructor

	stkque & operator=(const stkque & __other) {
		_M_in_stack = __other._M_in_stack;
		_M_out_stack = __other._M_out_stack;
		return (*this);
	}//copy assignment

	stkque & operator=(stkque && __other) {
		_M_in_stack = std::move(__other._M_in_stack);
		_M_out_stack = std::move(__other._M_out_stack);
	}//move assignment

	/**
	 * --------------------------------------------------
	 *  Capacity
	 * --------------------------------------------------
	 */
	bool empty() const
	{ return (_M_in_stack.empty() && _M_out_stack.empty()); }

	size_type size() const
	{ return _M_in_stack.size() + _M_out_stack.size(); }

	void push_in(const value_type & __x)
	{ _M_in_stack.push(__x); }

	value_type pop_out() {
		if(_M_out_stack.empty()) {
			while(!_M_in_stack.empty()) {
				_M_out_stack.push(_M_in_stack.top());
				_M_in_stack.pop();
			}//while
		}//if
		
		value_type tmp = _M_out_stack.top();
		_M_out_stack.pop();
		return tmp;
	}//pop_out

};

} //namespace data_structure
} //namespace adamcavendish

