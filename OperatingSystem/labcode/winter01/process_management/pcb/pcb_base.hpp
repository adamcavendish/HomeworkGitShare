#pragma once
// STL
#include <string>
#include <memory>
// C-STL

// process_management
#include "STATE.hpp"

struct pcb_base
{
	std::size_t id;
	std::string name;
	std::size_t service_time_required;
	std::size_t cpu_time_used;
	STATE process_state;
};

