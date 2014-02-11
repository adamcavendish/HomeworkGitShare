// STL
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>
// MemoryManagement
#include "config.hpp"
#include "helper_functions.hpp"

int main(int argc, char * argv[])
{
    printUsage(argv[0]);
    std::string data_filename;
    std::vector<std::size_t> address_list;

    if(argc == 1) {
        address_list = generateAddressList(c_addr_num);
        storeData("data.log", address_list);
    } else if(argc == 2) {
        address_list = processFile(argv[1]);
    } else {
        std::exit(EXIT_FAILURE);
    }//if-else

    std::size_t addrsz = address_list.size();
    for(std::size_t mem_sz = 1; mem_sz <= 35; ++mem_sz) {
        std::cout << std::setw(2) << mem_sz << " page frames: ";

        std::size_t page_fault =
            FIFO_algorithm(mem_sz, address_list);
        std::cout << " FIFO:" << std::fixed << std::setprecision(4)
            << 1-(double)(page_fault)/addrsz
            << ",";

        page_fault =
            LRU_algorithm(mem_sz, address_list);
        std::cout << " LRU:" << std::fixed << std::setprecision(4)
            << 1-(double)(page_fault)/addrsz
            << ",";

        page_fault =
            OPT_algorithm(mem_sz, address_list);
        std::cout << " OPT:" << std::fixed << std::setprecision(4)
            << 1-(double)(page_fault)/addrsz
            << std::endl;
    }//for

    return 0;
}//main

