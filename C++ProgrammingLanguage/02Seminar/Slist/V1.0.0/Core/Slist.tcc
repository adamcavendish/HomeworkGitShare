#pragma once

#include "Slist.hpp"
#include "Slist_iterator.hpp"

template <typename DataType>
Slist<DataType>::Slist()
{
	_begin = new iterator(NULL, NULL);
}//constructor

template <typename DataType>
Slist<DataType>::Slist(const Slist<DataType> & list)
{
	_begin = new iterator(new node(list->front()), NULL);

	// @Warning !! Don't use iter < list.end()! operator< is not overloaded!!!!!
	for(const_iterator list_iter = ++list.begin(), iterator this_iter = this->begin();
			iter != list.end();
			++iter)
	{
		insert_next(this_iter, *list_iter);
	}//for
}//copy constructor

template <DataType>
Slist<DataType>::Slist(size_t arr_size, DataType arr[])
{
	if(arr_size == 0) {
		_begin = new iterator(NULL, NULL);
		return;
	}//if

	_begin = new iterator(new node(arr[0]), NULL);
	for(size_t i = 1, iterator this_iter = this->begin();
			i < arr_size;
			++i)
	{
		this->insert_next(this_iter, arr[i]);
	}//for
}//Slist(arr_size, arr[])

template <typename DataType>
DataType & Slist<DataType>::front() const
{
	return *(_begin);
}//front()

template <typename DataType>
void Slist<DataType>::push_front(const DataType & data)
{
	/*
	iterator * temp = _begin._next;
	_begin._next = new iterator(new node(data), temp);
	*/
	if(_begin == NULL) {
		_begin = new iterator(new node(data), NULL);	
		return;
	}//if
	_begin->_next = new iterator(new node(data), _begin->_next);
}//push_front(data)

template <typename DataType>
void Slist<DataType>::insert_next(iterator position, const DataType & data)
{
	position->_next = new iterator(new node(data), position->_next);
}//insert_next(position, data)

template <typename DataType>
void Slist<DataType>::pop_front()
{
	iterator temp(_begin->next);
	delete _begin;
	_begin = temp;
}//pop_front()

template <typename DataType>
void Slist<DataType>::erase_next(iterator position)
{
	iterator *temp = position->next;
	position->next = position->next->next;
}//erase(position)

template <typename DataType>
void Slist<DataType>::erase(iterator position)
{
	iterator temp(position->next);
	delete position;
	position = temp;
}//erase(position)

template <typename DataType>
void Slist<DataType>::erase(iterator first, iterator last)
{
	for(iterator iter = first, temp = first->next;
			temp != last;
			iter = temp, ++temp)
		delete iter;
		
	first->next = last;
}//erase(first, last)

template <typename DataType>
void Slist<DataType>::swap(iterator pos1, iterator pos2) {}

template <typename DataType>
void Slist<DataType>::sort(iterator first = begin(), iterator last = end()) {}

template <typename DataType>
void Slist<DataType>::merge(SList<DataType> &list){}	// simply merge, no sort

template <typename DataType>
void Slist<DataType>::splice(iterator position, SList<DataType> &list){}	// splice 

template <typename DataType>
void Slist<DataType>::reverse(){};

template <typename DataType>
iterator Slist<DataType>::find(const_iterator start, const DataType & data) const;	// if not found return NULL
	

