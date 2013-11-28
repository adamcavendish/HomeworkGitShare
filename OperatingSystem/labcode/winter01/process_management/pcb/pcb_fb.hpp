#pragma once

// C-STL
#include <cstdint>
// process_management
#include "pcb_base.hpp"

struct pcb_fb : public pcb_base
{
	std::size_t depth;

	pcb_fb(std::size_t id__,
			const std::string & name__,
			std::size_t service_time_required__,
			std::size_t cpu_time_used__,
			STATE process_state__) :
		depth(0)
	{
		this->id = id__;
		this->name = name__;
		this->service_time_required = service_time_required__;
		this->cpu_time_used = cpu_time_used__;
		this->process_state = process_state__;
	}//constructor
};//struct pcb_fb

