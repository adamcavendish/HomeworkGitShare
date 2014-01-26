// STL
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <memory>
// MemoryManagement
#include "config.hpp"
#include "helper_functions.hpp"

int main(int argc, char * argv[])
{
    std::string data_filename =
        parseCommandLine(argc, argv);

    std::vector<std::size_t> address_list =
        processFile(data_filename);

    std::cout << c_student_id << std::endl;
    for(std::size_t mem_sz = 4; mem_sz <= 32; ++mem_sz) {
        std::cout << mem_sz << " page frames: ";

        std::size_t page_fault =
            FIFO_algorithm(mem_sz, address_list);
        std::cout << " FIFO:" << std::fixed << std::setprecision(4)
            << 1-(double)(page_fault)/320
            << ",";

        page_fault =
            LRU_algorithm(mem_sz, address_list);
        std::cout << " LRU:" << std::fixed << std::setprecision(4)
            << 1-(double)(page_fault)/320
            << ",";

        page_fault =
            OPT_algorithm(mem_sz, address_list);
        std::cout << " OPT:" << std::fixed << std::setprecision(4)
            << 1-(double)(page_fault)/320
            << std::endl;
    }//for

    return 0;
}
