#pragma once
// STL
#include <ostream>
#include <istream>
#include <array>
#include <algorithm>
#include <type_traits>
// C-STL
#include <cstdint>
#include <cstdlib>
// Fairy
#include <config.hpp>

namespace Fairy
{

class Register
{
public: //functions
	/**
	 * constructors/destructor and assignment operations
	 */
	explicit Register()
	{ std::fill_n(this->m_reg.begin(), Hardware::register_number, 0); }

	Register(const Register & rhs)
	{ std::copy_n(rhs.m_reg.begin(), Hardware::register_number, this->m_reg); }

	Register(Register && rhs)
	{ std::copy_n(rhs.m_reg.begin(), Hardware::register_number, this->m_reg); }

	Register & operator=(const Register & rhs) noexcept
	{ std::copy_n(rhs.m_reg.begin(), Hardware::register_number, this->m_reg); }

	Register & operator=(Register && rhs) noexcept
	{ std::copy_n(rhs.m_reg.begin(), Hardware::register_number, this->m_reg); }

	~Register()
	{ std::fill_n(this->m_reg.begin(), Hardware::register_number, 0); }

	int32_t * data() { return this->m_reg; }
	const int32_t * data() const { return this->m_reg; }

private: //functions
	friend std::ostream & operator<<(std::ostream & os, const Register & rhs);
	friend std::istream & operator>>(std::istream & os, const Register & rhs);
private: //members
	std::array<int32_t, Hardware::register_number> m_reg;
};//class Register

inline std::ostream &
operator<<(std::ostream & os, const Register & rhs) {
	for(auto i : rhs.m_reg)
		os << i;
}//operator<<(os, Register)

inline std::istream &
operator>>(std::istream & is, const Register & rhs) {
	for(auto & i : rhs.m_reg)
		is >> i;
}//operator>>(is, Register)

}//namespace Fairy

