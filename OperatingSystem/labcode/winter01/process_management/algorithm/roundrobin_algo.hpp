#pragma once

// STL
#include <deque>
#include <memory>
#include <stdexcept>
// process_management
#include "algobase.hpp"
#include "../pcb/pcb_roundrobin.hpp"

class roundrobin_algo : public algobase
{
public:
	void
	new_process(const pcb_roundrobin & p) {
		pcb_queue_.push_back(std::shared_ptr<pcb_base>(new pcb_roundrobin(
						p.id, p.name, p.service_time_required, p.cpu_time_used, p.process_state, p.roundrobin)));
	}//new_process()

	~roundrobin_algo() {}
public: // interface implementation
	bool
	end() const
	{ return pcb_queue_.empty(); }

	std::shared_ptr<pcb_base>
	get_process() {
		if(this->end())
			throw std::runtime_error("no process under management");

		std::shared_ptr<pcb_base> ret;
		do {
			ret = pcb_queue_.front();
			pcb_queue_.pop_front();

			auto p_pcbrr = std::static_pointer_cast<pcb_roundrobin>(ret);
			if(p_pcbrr->process_state != STATE::TASK_RUNNING) {
				pcb_queue_.push_back(ret);
			} else {
				break;
			}//if-else
		} while(true);

		return ret;
	}//get_process()

	void
	process_finish(const std::shared_ptr<pcb_base> & p_pcb) {
		if(p_pcb == nullptr)
			throw std::runtime_error("fb_algo::passed in pcb pointer points to nullptr!");

		auto p_pcbrr = std::static_pointer_cast<pcb_roundrobin>(p_pcb);

		--p_pcbrr->service_time_required;
		if(p_pcbrr->service_time_required <= 0)
			return;

		++p_pcbrr->cpu_time_used;
		if(p_pcbrr->cpu_time_used >= p_pcbrr->roundrobin) {
			p_pcbrr->cpu_time_used = 0;
			pcb_queue_.push_back(p_pcb);
		} else {
			pcb_queue_.push_front(p_pcb);
		}//if-else
	}//process_finish(p_pcb)

private://member
	std::deque<std::shared_ptr<pcb_base>> pcb_queue_;
};

