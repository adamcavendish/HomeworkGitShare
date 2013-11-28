#define NDEBUG
// STL
#include <iostream>
#include <random>
// C_STL
#include <cstdlib>
// POSIX
#include <unistd.h>
// process_management
#include "all.hpp"

// Globals
static std::size_t g_id = 0;
std::random_device rd;
std::default_random_engine e(rd());
std::uniform_int_distribution<int> gen(1, 100);
std::geometric_distribution<int> gen_st(0.30);

void init() { g_id = 0; }
std::size_t newid() { return ++g_id; }
std::string newname() { return std::to_string(g_id); }

/*
void test_priority()
{
	priority_algo algo;
	algo.new_process({ newid(), newname(), 3, 0, STATE::TASK_RUNNING, 9});
	algo.new_process({ newid(), newname(), 3, 0, STATE::TASK_RUNNING, 38});
	algo.new_process({ newid(), newname(), 6, 0, STATE::TASK_RUNNING, 30});
	algo.new_process({ newid(), newname(), 3, 0, STATE::TASK_RUNNING, 29});
	algo.new_process({ newid(), newname(), 4, 0, STATE::TASK_RUNNING, 0});

	std::cout << "Priority Algorithm:" << std::endl;
	std::cout << "Time: Process" << std::endl;
	std::size_t count = 0;
	while(!algo.end()) {
		auto p = algo.get_process();
		std::cout << ++count << "\t" << p->id << std::endl;
		algo.process_finish(p);
	}//while

}//test_priority()

void test_roundrobin()
{
	roundrobin_algo algo;
	algo.new_process({ newid(), newname(), 3, 0, STATE::TASK_RUNNING, 1});
	algo.new_process({ newid(), newname(), 3, 0, STATE::TASK_RUNNING, 3});
	algo.new_process({ newid(), newname(), 6, 0, STATE::TASK_RUNNING, 2});
	algo.new_process({ newid(), newname(), 3, 0, STATE::TASK_RUNNING, 1});
	algo.new_process({ newid(), newname(), 4, 0, STATE::TASK_RUNNING, 1});

	std::cout << "Round Robin Algorithm" << std::endl;
	std::cout << "Time: Process" << std::endl;
	std::size_t count = 0;
	while(!algo.end()) {
		auto p = algo.get_process();
		std::cout << ++count << "\t" << p->id << std::endl;

		if(count == 8)
			algo.new_process({ newid(), newname(), 16, 0, STATE::TASK_RUNNING, 7});

		algo.process_finish(p);
	}//while
}//test_roundrobin()
*/

void test_fb()
{
	fb_algo algo;
	algo.new_process({ newid(), newname(), 3, 0, STATE::TASK_RUNNING});
	algo.new_process({ newid(), newname(), 3, 0, STATE::TASK_RUNNING});
	algo.new_process({ newid(), newname(), 6, 0, STATE::TASK_RUNNING});
	algo.new_process({ newid(), newname(), 3, 0, STATE::TASK_RUNNING});
	algo.new_process({ newid(), newname(), 4, 0, STATE::TASK_RUNNING});

	std::cout << "FeedBack Algorithm" << std::endl;
	std::cout << "Time Process:ServiceTimeRemain " << std::endl;
	std::size_t count = 0;
	while(!algo.end()) {
#ifndef NDEBUG
		std::cout << algo.debug_info() << std::endl;
#endif//!NDEBUG

#ifndef NDEBUG
		std::cout << "before get" << std::endl;
#endif//!NDEBUG
		auto p = algo.get_process();
		std::cout << ++count << "\t" << p->id << ": " << p->service_time_required << std::endl;

		if(count == 3) {
			algo.new_process({ newid(), newname(), 1, 0, STATE::TASK_RUNNING});
			algo.new_process({ newid(), newname(), 1, 0, STATE::TASK_RUNNING});
		}//if
		if(count == 5)
			algo.new_process({ newid(), newname(), 28, 0, STATE::TASK_RUNNING});
		if(count == 8)
			algo.new_process({ newid(), newname(), 16, 0, STATE::TASK_RUNNING});
		if(count == 11)
			algo.new_process({ newid(), newname(), 8, 0, STATE::TASK_RUNNING});
		if(count == 17)
			algo.new_process({ newid(), newname(), 9, 0, STATE::TASK_RUNNING});
		if(count == 24)
			algo.new_process({ newid(), newname(), 3, 0, STATE::TASK_RUNNING});

#ifndef NDEBUG
		std::cout << "before finish" << std::endl;
#endif//!NDEBUG
		algo.process_finish(p);

		if(gen(e) > 60 && g_id < 20000) {
			auto st = gen_st(e) + 1u;
			algo.new_process({ newid(), newname(), st, 0, STATE::TASK_RUNNING});
		}//if
#ifndef NDEBUG
		std::cout << "while end" << std::endl;
#endif//!NDEBUG
	}//while
}//test_fb()

int main(int argc, char * argv[])
{
	/*
	init();
	test_priority();

	init();
	test_roundrobin();
	*/

	init();
	test_fb();

	return 0;
}//main

