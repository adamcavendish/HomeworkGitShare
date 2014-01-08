#pragma once

#include "List.hpp"

namespace adamcavendish {
namespace data_structure {

template <typename T>
template <typename... Args_t>
typename List<T>::node_type *
List<T>::_M_create_node(Args_t... __arg) {
	node_type * ret = _M_allocator.allocate(1);
	try {
		_M_allocator.construct(ret, std::forward<Args_t>(__arg)...);
	} catch(...) {
		_M_allocator.deallocate(ret, 1);
		throw;
	}//try-catch
	return ret;
}//_M_create_node(__arg) -- variadic

template <typename T>
inline void
List<T>::_M_destroy_node(iterator __x) {
	_M_allocator.destroy(
			std::addressof(static_cast<node_type *>(__x._M_node)->_M_data));
	_M_allocator.deallocate(static_cast<node_type *>(__x._M_node), 1);
}//_M_destroy_node(node_type *)
	

template <typename T>
template <typename InputIterator>
void
List<T>::_M_range_init(InputIterator __first, InputIterator __last) {
	for(; __first != __last; ++__first)
		push_back(*__first);
}//_M_range_init(__first, __last)

template <typename T>
template <typename InputIterator>
void
List<T>::_M_range_fill(InputIterator __first, InputIterator __last) {
	iterator __first0 = begin();
	iterator __last0 = end();
	for(; __first != __last && __first0 != __last0;
			++__first, ++__first0)
		*__first0 = *__first;
	if(__first == __last) {
		erase(__first0, __last0);
	} else {
		insert(__first0, __first, __last);
	}//if-else
}//_M_range_fill(__first, __last)

template <typename T>
template <typename... Args_t>
void
List<T>::_M_insert(iterator __pos, Args_t && ... __arg) {
	node_type * _node = _M_create_node(std::forward<Args_t>(__arg)...);
	_node->_M_next = __pos._M_node;
	_node->_M_prev = __pos._M_node->_M_prev;
	__pos._M_node->_M_prev->_M_next = _node;
	__pos._M_node->_M_prev = _node;
}//_M_insert(__pos, __arg) -- variadic

template <typename T>
void
List<T>::_M_erase(iterator __pos) {
	_Base *__prev = __pos._M_node->_M_prev;
	_Base *__next = __pos._M_node->_M_next;

	__pos._M_node->_M_prev->_M_next = __next;
	__pos._M_node->_M_next->_M_prev = __prev;

	_M_destroy_node(__pos);
}//_M_erase(__pos)

template <typename T>
void
List<T>::_M_transfer(iterator __pos, iterator __first, iterator __last) {
	if(__pos == __last)
		return;
	__last._M_node->_M_prev->_M_next = __pos._M_node;
	__first._M_node->_M_prev->_M_next = __last._M_node;
	__pos._M_node->_M_prev->_M_next = __first._M_node;
	iterator __tmp(__pos._M_node->_M_prev);
	__pos._M_node->_M_prev = __last._M_node->_M_prev;
	__last._M_node->_M_prev = __first._M_node->_M_prev;
	__first._M_node->_M_prev = __tmp._M_node;
}//_M_transfer(__pos, __first, __last)

template <typename T>
void
List<T>::splice(iterator __pos, List<value_type> && __x) {
	if(__x.empty())
		return;
	_M_transfer(__pos, __x.begin(), __x.end());
}//splice(__position, new_list)

}//namespace data_structure
}//namespace adamcavendish

