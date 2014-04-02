#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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

void input();

void output(size_t id);

void calculate();

void backtrace(size_t lbound, size_t rbound);

int main(int argc, char * argv[])
{
	while(1) {
		input();
		if(feof(stdin)) {
			showdbg("EOF!\n");
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
	if(g_num == 1) {
		fprintf(stdout, "Case %lu\n", id);
		fprintf(stdout, "0 A1\n");
		return;
	}//if

	g_result = g_temp_arr[0 * g_num + g_num - 1];
	fprintf(stdout, "Case %lu\n", id);
	fprintf(stdout, "%lu ", g_result);

	g_cur_len = 0;
	backtrace(0, g_num - 1);
	showdbg("%s\n", g_buf);
	
	// truncate the last ')'
	g_buf[g_cur_len - 1] = '\0';
	// print after the first '('
	fprintf(stdout, "%s\n", &g_buf[1]);
}//output()

void calculate() {
	if(g_num == 1) {
		g_result = 0;
		return;
	}//if

	for(i = 0; i < g_num; ++i) {
		g_temp_arr[i * g_num + i] = 0;
	}//for

	for(i = 1; i < g_num; ++i) {
		// alias i = spacing
		
		for(j = 0; i + j < g_num; ++j) {
			//m[j, j+spacing]
			size_t min = SIZE_MAX;
			size_t cut_pos = 0;
			showdbg(">> m[%d, %d]:\n", j, j+i);

			for(k = j; k < j+i; ++k) {
				// cut apart
				showdbg("m[%d, %d] + m[%d, %d] + %lu*%lu*%lu ", j, k, k+1, j+i,
						g_num_arr[j], g_num_arr[k+1], g_num_arr[j+i+1]);

				size_t current_mul_times = g_temp_arr[j * g_num + k] + g_temp_arr[(k+1) * g_num + j+i] +
					g_num_arr[j] * g_num_arr[k+1] * g_num_arr[j+i+1];

				showdbg("= %lu\n", current_mul_times);

				if(min > current_mul_times) {
					min = current_mul_times;
					cut_pos = k;

					showdbg("update min!\n");
				}//if
			}//for

			g_temp_arr[j * g_num + j + i] = min;
			g_backtrace_arr[j * g_num + j + i] = cut_pos;
		}//for
	}//for

	// print g_temp_arr[]
	showdbg("g_temp_arr[]:\n");
	for(i = 0; i < g_num; ++i) {
		for(j = 0; j < g_num; ++j) {
			showdbg("%lu ", g_temp_arr[i * g_num + j]);
		}//for
		showdbg("\n");
	}//for
	
	// print g_backtrace_arr[]
	showdbg("g_backtrace_arr[]:\n");
	for(i = 0; i < g_num; ++i) {
		for(j = 0; j < g_num; ++j) {
			showdbg("%lu ", g_backtrace_arr[i * g_num + j]);
		}//for
		showdbg("\n");
	}//for
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

