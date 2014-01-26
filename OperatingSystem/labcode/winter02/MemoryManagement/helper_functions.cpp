#include "helper_functions.hpp"
// STL
#include <string>
#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <functional>
#include <algorithm>
#include <deque>
// C-STL
#include <cstdlib>

std::string
parseCommandLine(int argc, char * argv[]) {
    if(argc != 2) {
        std::cerr << "Usage: " << argv[0] << " [dat file]" << std::endl;
        std::cerr << "Example: " << argv[0] << " test1dat.dat" << std::endl;
        std::exit(EXIT_FAILURE);
    }//if

    return argv[1];
}//parseCommandLine(argc, argv)

std::vector<std::size_t>
processFile(const std::string & filename) {
    std::ifstream data_file;
    data_file.open(filename);

    std::vector<std::size_t> ret =
        loadData(data_file);

    data_file.close();
    return ret;
}//processFile(filename)

std::vector<std::size_t>
loadData(std::ifstream & file) {
    std::size_t line_number = 0;
    file >> line_number;

    // a vector is a `list of elements`
    std::vector<std::size_t> ret;
    ret.reserve(line_number); // reserve space for `line_number` of elements

    std::size_t address = 0;
    for(std::size_t i = 0lu; i < line_number; ++i) {
        file >> address;
        ret.push_back(address);
    }//for

    return ret;
}//loadData(file)

std::size_t
address_to_page(std::size_t address) {
    // 1K memory is 10 instructions, and every page is 1K of memory.
    return address/10;
}//address_to_page(address)

std::size_t
FIFO_algorithm(std::size_t memory_size,
               const std::vector<std::size_t> & address_list)
{
    std::size_t page_fault_times = 0; // counting page fault times

    // the index of address list, indicating which address we're calculating.
    std::size_t address_list_index = 0;

    // deque is a double-ended queue, providing inserting and removing elements
    // from both ends.
    std::deque<std::size_t> my_memory;

    // this is a function checking whether my calculation should end.
    auto check_end = [&]() -> bool {
        const static std::size_t sz = address_list.size();
        if(address_list_index == sz-1)
            return true;
        return false;
    };//lambda function

    auto find_or_fifo = [&](std::size_t current_page) -> void {
        bool found = (std::find(
            my_memory.begin(),
            my_memory.end(),
            current_page)
                != my_memory.end());
        if(!found) {
            if(my_memory.size() >= memory_size)
                my_memory.pop_front();
            my_memory.push_back(current_page);
            ++page_fault_times;
        }//if
    };//lambda function


    // when the memory is empty (no page is loaded), load page first
    while(my_memory.size() < memory_size) {
        std::size_t current_page =
            address_to_page(address_list[address_list_index]);

        find_or_fifo(current_page);

        if(check_end() == true)
            return page_fault_times;
        ++address_list_index;
    }//while

    std::size_t sz = address_list.size();
    for(std::size_t i = address_list_index;
        i < sz;
        ++i, ++address_list_index)
    {
        std::size_t current_page = address_to_page(address_list[i]);

        find_or_fifo(current_page);
    }//for

    return page_fault_times;
}//FIFO_algorithm(memory_size, address_list)


std::size_t
LRU_algorithm(std::size_t memory_size,
              const std::vector<std::size_t> & address_list)
{
    std::size_t page_fault_times = 0; // counting page fault times

    // the index of address list, indicating which address we're calculating.
    std::size_t address_list_index = 0;

    // deque is a double-ended queue, providing inserting and removing elements
    // from both ends.
    std::deque<std::size_t> my_memory;

    // this is a function checking whether my calculation should end.
    auto check_end = [&]() -> bool {
        const static std::size_t sz = address_list.size();
        if(address_list_index == sz-1)
            return true;
        return false;
    };//lambda function

    auto find_or_lru = [&](std::size_t current_page) -> void {
        auto iter =
            std::find(my_memory.begin(), my_memory.end(), current_page);
        bool found = (iter != my_memory.end());

        if(found) {
            my_memory.erase(iter);
            my_memory.push_back(current_page);
        } else {
            if(my_memory.size() >= memory_size)
                my_memory.pop_front();
            my_memory.push_back(current_page);
            ++page_fault_times;
        }//if
    };//lambda function

    // when the memory is empty (no page is loaded), load page first
    while(my_memory.size() < memory_size) {
        std::size_t current_page =
            address_to_page(address_list[address_list_index]);

        find_or_lru(current_page);

        if(check_end() == true)
            return page_fault_times;
        ++address_list_index;
    }//while

    std::size_t sz = address_list.size();
    for(std::size_t i = address_list_index;
        i < sz;
        ++i, ++address_list_index)
    {
        std::size_t current_page = address_to_page(address_list[i]);

        find_or_lru(current_page);
    }//for

    return page_fault_times;
}//LRU_algorithm(memory_size, address_list)

std::size_t
OPT_algorithm(std::size_t memory_size,
              const std::vector<std::size_t> & address_list)
{
    std::size_t page_fault_times = 0; // counting page fault times

    // the index of address list, indicating which address we're calculating.
    std::size_t address_list_index = 0;

    std::vector<std::size_t> my_memory;

    // preprocess the address_list so that it may have a O(n*m)
    // performance of OPT algorithm
    auto preprocess_address = [&]() -> std::vector<std::deque<std::size_t>> {
        std::vector<std::deque<std::size_t>> ret;

        std::size_t maxpage = 0;
        std::size_t sz = address_list.size();
        for(std::size_t i = 0; i < sz; ++i) {
            std::size_t current_page = address_to_page(address_list[i]);
            if(current_page > maxpage)
                maxpage = current_page;
            ret.resize(maxpage + 1);

            ret[current_page].push_back(i);
        }//for

        return ret;
    };//lambda function

    // this is a function checking whether my calculation should end.
    auto check_end = [&]() -> bool {
        const static std::size_t sz = address_list.size();
        if(address_list_index == sz-1)
            return true;
        return false;
    };//lambda function

    // `find_swap_page` is the function finding the page that should
    // be swapped out
    auto find_swap_page =
        [&](std::vector<std::deque<std::size_t>> & preprocessed_data)
            -> std::size_t
    {
        // `swap_page_index` is the index of the page that will be swapped out
        std::size_t swap_page_index = 0;
        // `swap_page_ref_inst` is the first future address
        // that refer to the swap_page
        std::size_t swap_page_ref_addr = 0;
        for(auto ii = 0lu, ii_end = my_memory.size();
            ii < ii_end; ++ii)
        {
			if(preprocessed_data[my_memory[ii]].empty()) {
				swap_page_ref_addr = std::numeric_limits<std::size_t>::max();
				swap_page_index = ii;
				return swap_page_index;
			} else {
				auto first_ref = preprocessed_data[my_memory[ii]].front();
				if(first_ref > swap_page_ref_addr) {
					swap_page_ref_addr = first_ref;
					swap_page_index = ii;
				}//if
			}//if-else
        }//for

        return swap_page_index;
    };//lambda function

    auto find_or_opt =
        [&](std::size_t current_page,
            std::vector<std::deque<std::size_t>> & preprocessed_data)
            -> void
    {
        bool found = (std::find(
            my_memory.begin(),
            my_memory.end(),
            current_page)
                != my_memory.end());
        if(!found) {
            if(my_memory.size() < memory_size) {
                my_memory.push_back(current_page);
            } else {
                std::size_t page = find_swap_page(preprocessed_data);
                my_memory[page] = current_page;
            }//if-else

            ++page_fault_times;
        }//if
        preprocessed_data[current_page].pop_front();
    };//lambda function

    auto preprocessed_data = preprocess_address();

    // when the memory is empty (no page is loaded), load page first
    while(my_memory.size() < memory_size) {
        std::size_t current_page =
            address_to_page(address_list[address_list_index]);

        find_or_opt(current_page, preprocessed_data);

        if(check_end() == true)
            return page_fault_times;
        ++address_list_index;
    }//while

    std::size_t sz = address_list.size();
    for(std::size_t i = address_list_index;
        i < sz;
        ++i, ++address_list_index)
    {
        std::size_t current_page = address_to_page(address_list[i]);

        find_or_opt(current_page, preprocessed_data);
    }//for

    return page_fault_times;
}//OPT_algorithm(memory_size, address_list)

