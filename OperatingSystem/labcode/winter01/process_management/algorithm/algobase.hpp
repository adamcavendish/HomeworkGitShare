#pragma once
// STL
#include <memory>
// process_management
#include "../pcb/pcb_base.hpp"

class algobase
{
public: // interface
	virtual bool
	end() const = 0;

	virtual std::shared_ptr<pcb_base>
	get_process() = 0;

	virtual void
	process_finish(const std::shared_ptr<pcb_base> & p_pcb) = 0;

	virtual
	~algobase() {};
};//class algobase

