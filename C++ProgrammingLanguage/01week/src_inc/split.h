#pragma once

#include <algorithm>


template <class Output>
void split(std::string line, Output out)
{
	find_if(

