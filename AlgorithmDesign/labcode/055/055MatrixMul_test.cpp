#include <cstdio>
#include <cstdlib>
#include <cstdint>

#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <thread>
#include <future>
#include <functional>
using namespace std;

//#define DEBUG

#ifdef DEBUG
#define showdbg(...) fprintf(stderr, __VA_ARGS__)
#else
#define showdbg(...)
#endif

// global vars
size_t g_id = 1;

size_t g_num;
size_t g_num_arr[20];
size_t g_temp_arr[400];
size_t g_backtrace_arr[400];

size_t g_result;

enum { g_buf_len = 1024 };
size_t	g_cur_len;
char	g_buf[g_buf_len];

int i, j, k;

std::deque<size_t> g_list;

void input();

void output(size_t id);

void calculate();

void backtrace(size_t lbound, size_t rbound);

int main(int argc, char * argv[])
{
	while(1) {
		input();
		if(feof(stdin)) {
			showdbg("EOF!");
			break;
		}//if

		calculate();

		output(g_id);

		++g_id;

		showdbg("--------------------------------------------------");
	}//while

	return 0;
}//main

void input() {
	g_result = 0;
	fscanf(stdin, "%lu", &g_num);
	for(i = 0; i < g_num + 1; ++i) {
		fscanf(stdin, "%lu", &g_num_arr[i]);
	}//for
}//input()

void output(size_t id) {
	fprintf(stdout, "Case %lu\n", id);
	fprintf(stdout, "%lu\n", g_result);

	/*
	g_cur_len = 0;
	backtrace(0, g_num - 1);
	showdbg("%s\n", g_buf);
	
	// truncate the last ')'
	g_buf[g_cur_len - 1] = '\0';
	// print after the first '('
	fprintf(stdout, "%s\n", &g_buf[1]);
	*/
}//output()

void calculate() {
	size_t min = SIZE_MAX;
	size_t cnt = 0;

	g_list.clear();

	std::vector<size_t> mullist;

	for(i = 0; i < g_num + 1; ++i) {
		g_list.push_back(g_num_arr[i]);
	}//for

	function<void(size_t, size_t &)> cal = [&](size_t id, size_t & min) {
		showdbg("id: %lu listsz: %lu\n", id, g_list.size());
		showdbg("list: ");
		for(auto ii : g_list)
			showdbg("%lu ", ii);
		showdbg("\n");


		if(g_list.size() == 2) {
			showdbg("fin: cnt=%lu\n", cnt);
			if(min > cnt) {
				min = cnt;
				showdbg("update min!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");

				showdbg("mullist: ");
				for(auto ii : mullist)
					showdbg("%lu ", ii);
				showdbg("\n");
			}//if
			showdbg("\n");

			return;
		}//if
		
		if(id + 2 == g_list.size())
			return;

		auto erased = g_list[id + 1];
		auto cnt_resv = cnt;

		mullist.push_back(g_list[id + 1]);
		cnt += g_list[id] * g_list[id + 1] * g_list[id + 2];
		showdbg("cnt += %lu*%lu*%lu = %lu\n", g_list[id], g_list[id+1], g_list[id+2], cnt);

		g_list.erase(g_list.begin() + id + 1);

		for(auto newid = 0; (newid + 2) <= g_list.size(); ++newid) {
			cal(newid, min);
		}//for
		mullist.pop_back();
		g_list.insert(g_list.begin() + id + 1, erased);
		cnt = cnt_resv;
	};

	for(auto newid = 0; newid < g_list.size() - 1; ++newid) {
		cal(newid, min);
	}//for

	g_result = min;
}//calculate()

void backtrace(size_t lbound, size_t rbound) {
	showdbg("backtrace(%lu, %lu):\n", lbound, rbound);
	size_t cut_pos = g_backtrace_arr[lbound * g_num + rbound];
	showdbg("cut: %lu\n", cut_pos);

	g_cur_len += snprintf(g_buf + g_cur_len, g_buf_len, "(");
	if(lbound == cut_pos) {
		g_cur_len += snprintf(g_buf + g_cur_len, g_buf_len, "A%lu", lbound + 1);
	} else {
		backtrace(lbound, cut_pos);
	}//if-else

	if(rbound == cut_pos + 1) {
		g_cur_len += snprintf(g_buf + g_cur_len, g_buf_len, "A%lu", rbound + 1);
	} else {
		backtrace(cut_pos + 1, rbound);
	}//if-else
	g_cur_len += snprintf(g_buf + g_cur_len, g_buf_len, ")");
}//backtrace(lbound, rbound)

