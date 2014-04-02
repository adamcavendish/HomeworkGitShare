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
size_t	g_id = 1;

size_t	g_result;

enum { g_buf_len = 100 };
char	g_buf[g_buf_len];

size_t	g_str1_len;
char	g_str1[100];

size_t	g_str2_len;
char	g_str2[100];

size_t	g_temp_arr[101*101];

int i, j, k;

void input();

void output(size_t id);

void calculate();

void display();

int main(int argc, char * argv[])
{
	fgets(g_buf, g_buf_len, stdin);
	while(1) {
		input();
		if(feof(stdin)) {
			showdbg("EOF!\n");
			break;
		}//if

		calculate();

		output(g_id);

		++g_id;

		showdbg("--------------------------------------------------\n");
	}//while

	return 0;
}//main

void input() {
	int cc;
	g_result = 0;
	fscanf(stdin, "%lu %lu\n", &g_str1_len, &g_str2_len);

	if(g_str1_len > 0) {
		for(i = 0; i < g_str1_len; ++i) {
			fscanf(stdin, "%c", &g_str1[i]);
			cc = fgetc(stdin);
		}//for
		if(cc != '\n') {
			fgets(g_buf, g_buf_len, stdin);
		}//if
	}//if

	if(g_str2_len > 0) {
		for(i = 0; i < g_str2_len; ++i) {
			fscanf(stdin, "%c", &g_str2[i]);
			cc = fgetc(stdin);
		}//for
		if(cc != '\n') {
			fgets(g_buf, g_buf_len, stdin);
		}//if
	}//if
}//input()

void output(size_t id) {
	showdbg("str1: %lu\n", g_str1_len);
	for(i = 0; i < g_str1_len; ++i) {
		showdbg("%c ", g_str1[i]);
	}//for
	showdbg("\n");
	showdbg("str2: %lu\n", g_str2_len);
	for(i = 0; i < g_str2_len; ++i) {
		showdbg("%c ", g_str2[i]);
	}//for
	showdbg("\n");

	fprintf(stdout, "Case %lu\n", id);
	fprintf(stdout, "%lu\n", g_result);
}//output()

void calculate() {
	// g_temp_arr(i, j) --> g_temp_arr(i * g_str2_len + j)
	if(g_str1_len == 0 || g_str2_len == 0) {
		g_result = 0;
		return;
	}//if

	for(i = 0; i <= g_str1_len; ++i) {
		g_temp_arr[i * (g_str2_len+1) + 0] = 0;
	}//for
	for(i = 0; i <= g_str2_len; ++i) {
		g_temp_arr[0 * (g_str2_len+1) + i] = 0;
	}//for

	for(i = 1; i <= g_str1_len; ++i) {
		for(j = 1; j <= g_str2_len; ++j) {
			if(g_str1[i-1] == g_str2[j-1]) {
				g_temp_arr[i * (g_str2_len+1) + j] = g_temp_arr[(i-1) * (g_str2_len+1) + (j-1)] + 1;
			} else {
				size_t max = g_temp_arr[i * (g_str2_len+1) + (j-1)];
				if(g_temp_arr[(i-1) * (g_str2_len+1) + j] > max)
					max = g_temp_arr[(i-1) * (g_str2_len+1) + j];

				g_temp_arr[i * (g_str2_len+1) + j] = max;
			}//if-else
			display();
		}//for
	}//for

	g_result = g_temp_arr[g_str1_len * (g_str2_len+1) + g_str2_len];
}//calculate()

void display() {
	size_t ii, jj;
	for(ii = 0; ii <= g_str1_len; ++ii) {
		for(jj = 0; jj <= g_str2_len; ++jj) {
			showdbg("%lu ", g_temp_arr[ii * (g_str2_len+1) + jj]);
		}//for
		showdbg("\n");
	}//for
	showdbg("####################\n");
}//display()

