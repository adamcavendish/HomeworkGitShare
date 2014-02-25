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
std::string newname() { return "P" + std::to_string(g_id); }

void test_priority()
{
	priority_algo algo;
	algo.new_process({ newid(), newname(), 3, 0, STATE::TASK_RUNNING, 9});
	algo.new_process({ newid(), newname(), 3, 0, STATE::TASK_RUNNING, 38});
	algo.new_process({ newid(), newname(), 6, 0, STATE::TASK_RUNNING, 30});
	algo.new_process({ newid(), newname(), 3, 0, STATE::TASK_RUNNING, 29});
	algo.new_process({ newid(), newname(), 4, 0, STATE::TASK_RUNNING, 0});

    std::cout << "process:service_time_required:priority" << std::endl;
    std::cout << 1 << ":" << 3 << ":" << 9 << std::endl;
    std::cout << 2 << ":" << 3 << ":" << 38 << std::endl;
    std::cout << 3 << ":" << 6 << ":" << 30 << std::endl;
    std::cout << 4 << ":" << 3 << ":" << 29 << std::endl;
    std::cout << 5 << ":" << 4 << ":" << 0 << std::endl;

	std::cout << "Time: Process" << std::endl;
	std::size_t count = 0;
	while(!algo.end()) {
		auto p = algo.get_process();
		std::cout << ++count << "\tpid " << p->id
            << ": service_time_required " << p->service_time_required << std::endl;
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

    std::cout << "process:service_time_required:roundrobin_time_slice" << std::endl;
    std::cout << 1 << ":" << 3 << ":" << 1 << std::endl;
    std::cout << 2 << ":" << 3 << ":" << 3 << std::endl;
    std::cout << 3 << ":" << 6 << ":" << 2 << std::endl;
    std::cout << 4 << ":" << 3 << ":" << 1 << std::endl;
    std::cout << 5 << ":" << 4 << ":" << 1 << std::endl;
                   
	std::cout << "Time Process:ServiceTimeRemain" << std::endl;
	std::size_t count = 0;
	while(!algo.end()) {
		auto p = algo.get_process();
		std::cout << ++count << "\tpid " << p->id
            << ": service_time_required " << p->service_time_required << std::endl;
		algo.process_finish(p);
	}//while
}//test_roundrobin()

void test_fb()
{
	fb_algo algo;
	algo.new_process({ newid(), newname(), 3, 0, STATE::TASK_RUNNING });
	algo.new_process({ newid(), newname(), 3, 0, STATE::TASK_RUNNING });
	algo.new_process({ newid(), newname(), 6, 0, STATE::TASK_RUNNING });
	algo.new_process({ newid(), newname(), 3, 0, STATE::TASK_RUNNING });
	algo.new_process({ newid(), newname(), 4, 0, STATE::TASK_RUNNING });

    std::cout << "process:service_time_required" << std::endl;
    std::cout << 1 << ":" << 3 << std::endl;
    std::cout << 2 << ":" << 3 << std::endl;
    std::cout << 3 << ":" << 6 << std::endl;
    std::cout << 4 << ":" << 3 << std::endl;
    std::cout << 5 << ":" << 4 << std::endl;

	std::cout << "Time Process:ServiceTimeRemain " << std::endl;
	std::size_t count = 0;
	while(!algo.end()) {
#ifndef NDEBUG
		std::cout << algo.debug_info() << std::endl;
#endif//!NDEBUG

		auto p = algo.get_process();
		std::cout << ++count << "\tpid " << p->id
            << ": service_time_required " << p->service_time_required << std::endl;

#if 0
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
#endif

		algo.process_finish(p);

#if 0
		if(gen(e) > 60 && g_id < 20000) {
			auto st = gen_st(e) + 1u;
			algo.new_process({ newid(), newname(), st, 0, STATE::TASK_RUNNING});
		}//if
#endif
	}//while
}//test_fb()

int main()
{
    std::cout << "Priority algorithm: " << std::endl;
	init();
	test_priority();

    std::cout << std::endl;
    std::cout << "RoundRobin algorithm: " << std::endl;
	init();
	test_roundrobin();

    std::cout << std::endl;
    std::cout << "FeedBack algorithm: " << std::endl;
	init();
	test_fb();

	return 0;
}//main

