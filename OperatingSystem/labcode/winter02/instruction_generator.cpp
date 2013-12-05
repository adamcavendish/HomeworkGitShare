#include "instruction_generator.hpp"
// STL
#include <iostream>

namespace impl {

std::vector<std::size_t>
instruction_generator_impl::generate()  {
#ifndef NDEBUG
	this->m_sequential_count = 0;
	this->m_jmp_forward_count = 0;
	this->m_jmp_backward_count = 0;
#endif//NDEBUG

	// c_jmp_min_inst_length: the minimum of instructions that a jump jumps over
	const std::size_t c_jmp_min_inst_length = 10;
	// alias
	auto m_sz = this->m_instruction_generate_size;
	// reserve memory for beter performance
	this->m_generate_ret.reserve(m_sz);

	// last_inst: the last instruction position, starts from a random instruction
	std::size_t last_inst = [=] {
		std::uniform_int_distribution<std::size_t> r(0, m_sz);
		return r(this->m_engine);
	}();//plain
	this->m_generate_ret.push_back(last_inst);

	// geometric_distribution for forward jumper and backward jumper
	std::geometric_distribution<> jmp_dist(0.02);
	for(std::size_t i = 1; i < m_sz; ++i) {
#ifndef NDEBUG
		auto last_inst_rsv = last_inst;
#endif//!NDEBUG
		auto num = this->m_rand(this->m_engine);
		switch(num) {
		// sequential, 50% of instructions
		case 0:
		case 1:
			++last_inst;
			if(last_inst == m_sz)
				last_inst = 0;
			this->m_generate_ret.push_back(last_inst);
			break;
		// jump forward, 25% of instructions
		case 2:
			last_inst += jmp_dist(this->m_engine) + c_jmp_min_inst_length;
			if(last_inst >= m_sz) {
				std::cout << "SOFT_ASSERT: jump forward out of range,"
					" tune back to the last instruction" << std::endl;
				last_inst = m_sz - 1;
			}//if
			this->m_generate_ret.push_back(last_inst);
			break;
		// jump backward, 25% of instructions
		case 3:
			auto diff = jmp_dist(this->m_engine) + c_jmp_min_inst_length;
			if(diff > last_inst) {
				std::cout << "SOFT_ASSERT: jump backward out of range,"
					" tune back to the first instruction" << std::endl;
				diff = last_inst;
			}//if
			last_inst -= diff;
			this->m_generate_ret.push_back(last_inst);
			break;
		}//switch-case
#ifndef NDEBUG
		if(last_inst_rsv + 1 == last_inst) {
			++this->m_sequential_count;
		} else if(last_inst_rsv == m_sz-1 && last_inst == 0) {
			++this->m_sequential_count;
		} else if(last_inst_rsv > last_inst) {
			++this->m_jmp_forward_count;
		} else if(last_inst_rsv < last_inst) {
			++this->m_jmp_backward_count;
		} else {
			std::cout << "SOFT ASSERT DEBUG: unexpected instruction sequence: " << std::endl;
			std::cout << "last: " << last_inst_rsv << std::endl;
			std::cout << "curr: " << last_inst << std::endl;
		}//if-else
#endif//!NDEBUG
	}//for

	return std::move(this->m_generate_ret);
}//generate()

}//namespace impl

