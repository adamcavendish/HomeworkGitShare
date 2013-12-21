#pragma once
// STL
#include <vector>
#include <utility>
#include <random>
#include <map>

namespace impl {

/**
 * @brief instruction_generator_impl is a generator that generates instruction stream
 *
 * instruction_generator generates a vector of integers which represents
 * the next instruction to execute
 */
class instruction_generator_impl
{
public: //functions
	static instruction_generator_impl &
	instance() {
		static instruction_generator_impl gen;
		return gen;
	}//instance()

	std::size_t
	size() const
	{ return this->m_instruction_generate_size; }

	void
	size(std::size_t nsize)
	{ this->m_instruction_generate_size = nsize; }

	/// @brief the main code of generating the instruction lists
	std::vector<std::size_t>
	generate();

private://functions
	instruction_generator_impl() :
#ifndef NDEBUG
		m_sequential_count(0),
		m_jmp_forward_count(0),
		m_jmp_backward_count(0),
#endif//!NDEBUG
		m_generate_ret(),
		m_instruction_generate_size(
				instruction_generator_impl::c_instruction_generate_size),
		m_rand(0, 3),
		m_rd(),
		m_engine(m_rd())
	{}

private://literals
	/// @brief c_instruction_generate_size default instruction generation size = 1M of instructions
	const static std::size_t c_instruction_generate_size = 1024 * 1024;
#ifndef NDEBUG
public: //debug members
	std::size_t m_sequential_count;
	std::size_t m_jmp_forward_count;
	std::size_t m_jmp_backward_count;
	std::map<int, int> m_jmp_forward_map;
	std::map<int, int> m_jmp_backward_map;
#endif//!NDEBUG
private://members
	/// @brief shared data structure for the return of generate()
	std::vector<std::pair<std::size_t, std::size_t>> m_generate_ret;
	std::size_t m_page_size;
	std::size_t m_instructions_per_page;
	/// @brief m_instruction_generate_size defines the number of instructions generated
	std::size_t m_instruction_generate_size;
	std::uniform_int_distribution<std::size_t> m_rand;
	std::random_device m_rd;
	std::default_random_engine m_engine;
};//class instruction_generator_impl

}//namespace impl

inline impl::instruction_generator_impl &
instruction_generator()
{ return impl::instruction_generator_impl::instance(); }

