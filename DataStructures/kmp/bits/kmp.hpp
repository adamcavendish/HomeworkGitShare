#pragma once

#include <cstring>

namespace adamcavendish {
namespace algorithm {

static void preprocess(const char * pattern, int pat_len, int * fail)
{
	int pos = 2, k = -1;
	fail[0] = -1;
	fail[1] = 0;

	while(pos < pat_len) {
		if(k == -1 || pattern[pos] == pattern[k]) {
			++pos;
			++k;
			fail[pos] = k;
		} else {
			k = fail[k];
		}//if-else
	}//while
}//preprocess(pattern, pat_len, fail)

int kmp(const char * str, const char * pattern)
{
	int i_str = 0; // the number pointer to str
	int i_pat = 0; // the number pointer to pattern

	int str_len = strlen(str);
	int pat_len = strlen(pattern);

	int * fail = new int[pat_len];

	preprocess(pattern, pat_len, fail);

	while(i_str + i_pat < str_len) {
		if(pattern[i_pat] == str[i_str + i_pat]) {
			if(i_pat == pat_len - 1)
				return i_str;
			++i_pat;
		} else {
			i_str = i_str + i_pat - fail[i_pat];	
			if(fail[i_pat] > -1) {
				i_pat = fail[i_pat];
			} else {
				i_pat = 0;
			}//if-else
		}//if-else
	}//while
	
	delete fail;
	return str_len;
}//kmp(str, pattern)

int kmp2(const char * str, const char * pattern)
{
	int i = 0, j = 0, pos;
	int str_len = strlen(str);
	int pat_len = strlen(pattern);

	int * fail = new int[pat_len];

	preprocess(pattern, pat_len, fail);

	while(i < str_len && j < pat_len) {
		if(j == -1 || str[i] == pattern[j]) {
			++i;
			++j;
		} else {
			j = fail[j];
		}//if-else
	}//while

	if(j >= pat_len) {
		pos = i - pat_len;
	} else {
		pos = -1;
	}//if-else

	delete fail;
	return pos;
}//kmp(str, pattern)

} //namespace algorithm
} //namespace adamcavendish

