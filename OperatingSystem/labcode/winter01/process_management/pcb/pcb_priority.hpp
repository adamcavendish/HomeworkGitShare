#pragma once

// C-STL
#include <cstdint>
// process_management
#include "pcb_base.hpp"

struct pcb_priority : public pcb_base
{
	std::size_t priority;

	pcb_priority(std::size_t id__,
			const std::string & name__,
			std::size_t service_time_required__,
			std::size_t cpu_time_used__,
			STATE process_state__,
			std::size_t priority__) :
		priority(priority__)
	{
		this->id = id__;
		this->name = name__;
		this->service_time_required = service_time_required__;
		this->cpu_time_used = cpu_time_used__;
		this->process_state = process_state__;
	}
};

