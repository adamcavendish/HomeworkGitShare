#pragma once

// STL
// C-STL
#include <cstdint>
#include <cstdlib>

namespace Fairy
{

struct Miscellaneous {
	const static std::size_t port = 12345;
};

struct Hardware {
	const static std::size_t register_number = 16;
	const static std::size_t memory_size = 1024*1024;
};//struct Hardware

template <std::size_t ID>
inline std::size_t
R() {
	static_assert(ID >= Hardware::register_number, "Register refered out of bound!");
	return ID;
}//R()

}//namespace Fairy

