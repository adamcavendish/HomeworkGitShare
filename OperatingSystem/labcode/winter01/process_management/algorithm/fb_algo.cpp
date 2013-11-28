#include "fb_algo.hpp"

std::shared_ptr<pcb_base>
fb_algo::get_process() {
	if(this->end())
		throw std::runtime_error("no process under management");

	if(this->current_process_ != nullptr)
		return this->current_process_;

	auto i = pcb_queue_.begin();
	auto i_prev = pcb_queue_.begin();
	auto i_end = pcb_queue_.end();
	for(; i != i_end; ++i) {
		if(i->empty())
			continue;

		this->current_process_ = i->front();
		i->pop_front();
		i_prev = i;
		break;
	}//for
	if(i == i_end && i_prev->empty())
		this->empty_ = true;

	return this->current_process_;
}//get_process()

void
fb_algo::process_finish(const std::shared_ptr<pcb_base> & p_pcb) {
	if(p_pcb == nullptr)
		throw std::runtime_error("fb_algo::passed in pcb pointer points to nullptr!");

	if(this->current_process_ != p_pcb)
		this->current_process_ = p_pcb;

	auto p_pcbfb = std::static_pointer_cast<pcb_fb>(this->current_process_);
	auto cpu_allowed_t = this->get_cpu_allowed_by_depth(p_pcbfb->depth);
	
	--p_pcbfb->service_time_required;
	++p_pcbfb->cpu_time_used;

	if(p_pcbfb->service_time_required <= 0) {
		p_pcbfb->process_state = STATE::TASK_DEAD;
		this->current_process_.reset();
		this->empty_ = this->check_empty_slow();
		return;
	}//if

	if(p_pcbfb->cpu_time_used >= cpu_allowed_t) {
		p_pcbfb->cpu_time_used = 0;

		if(p_pcbfb->depth < fb_algo::C_NUMBER_QUEUES - 1)
			++p_pcbfb->depth;

		this->pcb_queue_[p_pcbfb->depth].push_back(this->current_process_);
		this->current_process_.reset();
	}//if

	this->empty_ = false;
}//process_finish(p_pcb)

