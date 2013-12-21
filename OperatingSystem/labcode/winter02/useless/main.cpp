#include "instruction_generator.hpp"
// STL
#include <vector>
#include <iostream>
#include <iomanip>
#include <map>
#include <algorithm>
#include <cstdint>

void test_instruction_generator()
{
	auto inst = instruction_generator().generate();

	for(auto i = 0lu; i < inst.size(); ++i) {
		std::cout << "inst[" << i << "]: " << inst[i] << std::endl;
	}//for

#ifndef NDEBUG
	std::cout << "sequential_count: " << instruction_generator().m_sequential_count << std::endl;
	std::cout << "forward_count: " << instruction_generator().m_jmp_forward_count << std::endl;
	std::cout << "backward_count: " << instruction_generator().m_jmp_backward_count << std::endl;

	std::map<int, int> diffmap(instruction_generator().m_jmp_forward_map);
	for(auto i : instruction_generator().m_jmp_backward_map) {
		diffmap[i.first] -= i.second;
	}//for

	for(auto i : diffmap) {
		std::cout << std::setw(7) << i.first << ": " << i.second << std::endl;
	}//for

	std::int64_t counter = 0;
	for(auto i : instruction_generator().m_jmp_forward_map) {
		counter += i.first * i.second;
	}//for

	for(auto i : instruction_generator().m_jmp_backward_map) {
		counter -= i.first * i.second;
	}//for
	std::cout << "sumup count: " << counter << std::endl;
#endif//!NDEBUG
}//test_instruction_generator

int main()
{

	return 0;
}//main

