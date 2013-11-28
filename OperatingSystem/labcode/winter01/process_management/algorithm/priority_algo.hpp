#pragma once
// STL
#include <queue>
#include <memory>
#include <stdexcept>
// process_management
#include "algobase.hpp"
#include "../pcb/pcb_priority.hpp"

class priority_algo : public algobase
{
public://functions
	void
	new_process(const pcb_priority & p) {
		this->pcb_queue_.push(std::shared_ptr<pcb_base>(new pcb_priority(
					p.id, p.name, p.service_time_required, p.cpu_time_used, p.process_state, p.priority)));
	}//new_process(id, name, service_time_required, cpu_time_used, process_state, priority)

	~priority_algo() {}

public: // interface implement
	bool
	end() const
	{ return this->pcb_queue_.empty(); }

	std::shared_ptr<pcb_base>
	get_process() {
		if(this->end())
			throw std::runtime_error("no process under management");

		auto process_most_priority = this->pcb_queue_.top();
		this->pcb_queue_.pop();

		return process_most_priority;
	}//get_process()

	void
	process_finish(const std::shared_ptr<pcb_base> & p_pcb) {
		if(p_pcb == nullptr)
			throw std::runtime_error("fb_algo::passed in pcb pointer points to nullptr!");

		auto p_pcbp = std::static_pointer_cast<pcb_priority>(p_pcb);
		if(p_pcbp->priority < 3) {
			p_pcbp->priority = 0;
		} else {
			p_pcbp->priority -= 3;
		}//if-else

		--p_pcbp->service_time_required;
		if(p_pcbp->service_time_required > 0) {
			this->pcb_queue_.push(p_pcb);
		} else {
			p_pcb->process_state = STATE::TASK_DEAD;
		}//if-else
	}//process_finish(p_pcb)

private: //functions
	struct pcbcompare {
		bool
		operator()(const std::shared_ptr<pcb_base> & lhs, const std::shared_ptr<pcb_base> & rhs) {
			auto plhs = std::static_pointer_cast<pcb_priority>(lhs);
			auto prhs = std::static_pointer_cast<pcb_priority>(rhs);
			if(plhs->process_state != STATE::TASK_RUNNING)
				return true;
			if(prhs->process_state != STATE::TASK_RUNNING)
				return false;

			return plhs->priority < prhs->priority;
		}
	};

private: //members
	std::priority_queue<std::shared_ptr<pcb_base>, std::vector<std::shared_ptr<pcb_base>>, pcbcompare> pcb_queue_;
};

