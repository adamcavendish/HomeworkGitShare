#include "instruction_generator.hpp"
// STL
#include <vector>
#include <iostream>

int main()
{
	auto inst = instruction_generator().generate();

	for(auto i = 0lu; i < inst.size(); ++i) {
		std::cout << "inst[" << i << "]: " << inst[i] << std::endl;
	}//for

	std::cout << "sequential_count: " << instruction_generator().m_sequential_count << std::endl;
	std::cout << "forward_count: " << instruction_generator().m_jmp_forward_count << std::endl;
	std::cout << "backward_count: " << instruction_generator().m_jmp_backward_count << std::endl;
}//main

