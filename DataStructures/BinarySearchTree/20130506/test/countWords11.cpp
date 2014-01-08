#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
// unordered_map vs. map -- faster but unordered
#include <map>
#include <unordered_map>
// c++0x for move semantics
#include <utility>
// c++0x for async mechanism
#include <future>

#include "../BinarySearchTree"


// use 'using' rather than typedef
#ifdef MAP
using WordCountMapType = std::map<std::string, std::size_t>;
#else
using WordCountMapType = adamcavendish::container::BinarySearchTree<std::string, std::size_t>;
#endif

WordCountMapType wordsInFile(const std::string & fileName) {
	// c++11 added constructor "ifstream(std::string)"
	std::ifstream __file(fileName);
	WordCountMapType __word_counts;
	if(!__file) {
		std::cerr << fileName << " Error!" << std::endl;
		return __word_counts;
	}//if
	
	for(std::string __word; __file >> __word;) {
		++__word_counts[__word];
#ifndef NDEBUG
		auto len = 50 - std::string(__word).length();
		if(std::string(__word).length() > 50)
			len = 0;
		std::cout << "Adding word: '" << __word << "' " << std::string(len, ' ')
			<< __word_counts[__word] << std::endl;
#endif
	}//for
	return __word_counts;
}//wordsInFile(fileName)

/*
 * Let's use lambda in C++11 not functor
struct pair_compare_2 {
	template <typename T>
	bool operator() (T __one, T __two) const {
		return __one->second > __two->second;
	}//operator()
};//pair_compare_2
*/

/**
 * @brief print n most common words in [bgn, end)
 */
template <typename map_iter>
void showCommonWords(map_iter bgn, map_iter end, const std::size_t n)
{
	// typedef std::vector<map_iter> vec_map_iter;
	// typedef typename vec_map_iter::iterator iter_type;
	
	std::vector<map_iter> word_iter;
	//word_iter.reserve(std::distance(bgn, end));
	for(auto __iter = bgn; __iter != end; ++__iter)
		word_iter.push_back(__iter);

	// using lambda instead of functor
	std::partial_sort(word_iter.begin(), word_iter.end(), word_iter.end(),
			[](map_iter __one, map_iter __two) {
				return __one->second > __two->second;});
	
	// using cbegin and cend for const_begin and const_end
	// -> to return a const_iterator
	auto __end = word_iter.cbegin() + n;
	for(auto __iter = word_iter.cbegin(); __iter != __end; ++__iter) {
		// using %zu to print size_t
		std::printf(" %-10s%10zu\n",
				(*__iter)->first.c_str(), (*__iter)->second);
	}//for
}//showCommonWords(bgn, end, n)

int main(int argc, const char ** argv)
{
	// in c++0x, std::vector<std::vector<int> > and
	// std::vector<std::vector<int>> are the same
	//
	// use std::future to use async mechanism
	std::vector<std::future<WordCountMapType>> futures;

	// create separate thread for each file
	for(int __i = 1; __i < argc; ++__i) {
		futures.push_back(std::async(std::launch::async, [=]{
					return wordsInFile(argv[__i]); }));
	}//for
	
	WordCountMapType word_counts;
	for(auto & __f : futures) {
		auto results = __f.get(); // move map returned by wordsInFile

#if	0
		for(const auto & __i : results)
			word_counts[__i.first] += __i.second;
#else
		for(auto __i = results.begin(); __i != results.end();) {
#ifndef NDEBUG
			auto len = 49 - std::string(__i->first).length();
			if(std::string(__i->first).length() > 49)
				len = 1;
			std::cout << "Merging word: '" << __i->first << "' "
				<< std::string(len, ' ')
				<< __i->second << std::endl;
#endif
			word_counts[__i->first] += __i->second;
			__i = results.erase(__i);
		}//for
#endif
	}//for

	std::cout << word_counts.size() << " words found." << std::endl;
	std::cout << "Most common: " << std::endl;
	const std::size_t max_words_to_show = 20;
	showCommonWords(word_counts.begin(), word_counts.end(),
		std::min(word_counts.size(), max_words_to_show));

	return 0;
}//main

