#pragma once
// STL
#include <deque>
#include <memory>
#include <stdexcept>
#include <string>
#ifndef NDEBUG
  #include <iostream>
#endif//!NDEBUG
// process_management
#include "algobase.hpp"
#include "../pcb/pcb_fb.hpp"

class fb_algo : public algobase
{
private: //constants
	const static std::size_t C_NUMBER_QUEUES = 4;
	static_assert(fb_algo::C_NUMBER_QUEUES > 0, "fb_algo::C_NUMBER_QUEUES must be greater than 0!");

public://functions
	fb_algo() : empty_(true) {}

	~fb_algo() {}

	void
	new_process(const pcb_fb & p) {
		this->pcb_queue_[0].push_back(std::shared_ptr<pcb_base>(new pcb_fb(
					p.id, p.name, p.service_time_required, p.cpu_time_used, p.process_state)));
		this->empty_ = false;
	}//new_process(id, name, service_time_required, cpu_time_used, process_state, priority)

public: // interface implement
	bool
	end() const
	{ return this->empty_; }

	std::shared_ptr<pcb_base>
	get_process();

	void
	process_finish(const std::shared_ptr<pcb_base> & p_pcb);

#ifdef NDEBUG
private:
#else
public:
#endif//NDEBUG
	std::string
	debug_info() const {
		std::string ret;

		std::cout << "------------------------------" << std::endl;
		std::cout << "queue_id id name service_need_t cpu_t cpu_allowed_t process_state" << std::endl;
		if(this->current_process_ == nullptr) {
			std::cout << "cur is null" << std::endl;
		} else {
			auto jj = std::static_pointer_cast<pcb_fb>(this->current_process_);
			std::cout << "cur" << "\t" << jj->id << "\t" << jj->name << "\t"
				<< jj->service_time_required << "\t"
				<< jj->cpu_time_used << "\t" << get_cpu_allowed_by_depth(jj->depth) << "\t"
				<< pretty_print_state(jj->process_state) << std::endl;
		}//if-else

		std::size_t queueid = 0;
		for(auto i : this->pcb_queue_) {
			for(auto j : i) {
				auto jj = std::static_pointer_cast<pcb_fb>(j);
				std::cout << queueid << "\t" << jj->id << "\t" << jj->name << "\t"
					<< jj->service_time_required << "\t"
					<< jj->cpu_time_used << "\t" << get_cpu_allowed_by_depth(jj->depth) << "\t"
					<< pretty_print_state(jj->process_state) << std::endl;
			}//for

			++queueid;
		}//for
		std::cout << "------------------------------";
		return ret;
	}//debug_info()

	std::string
	pretty_print_state(STATE s) const {
		switch(s) {
			case STATE::TASK_INTERRUPTIBLE:
				return "INTERRUPTIBLE";
			case STATE::TASK_RUNNING:
				return "RUNNING";
			case STATE::TASK_DEAD:
				return "DEAD";
		}//switch
		return "ERROR_STATE";
	}//pretty_print_state()

private: //function
	std::size_t
	get_cpu_allowed_by_depth(std::size_t depth) const
	{ return depth + 1; }

	bool check_empty_slow() const {
		bool ret = true;
		for(auto i : this->pcb_queue_) {
			if(!i.empty()) {
				ret = false;
				break;
			}//if
		}//for

		return ret;
	}//check_empty_slow()

private: //members
	bool empty_;
	std::shared_ptr<pcb_base> current_process_;
	std::array<std::deque<std::shared_ptr<pcb_base>>, fb_algo::C_NUMBER_QUEUES> pcb_queue_;
};

