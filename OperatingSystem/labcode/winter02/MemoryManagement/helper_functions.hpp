#pragma once

// STL
#include <string>
#include <fstream>
#include <vector>
#include <string>

std::string
parseCommandLine(int argc, char * argv[]);

std::vector<std::size_t>
processFile(const std::string & file);

std::vector<std::size_t>
loadData(std::ifstream & file);

std::size_t
address_to_page(std::size_t address);

/**
 * @brief FIFO algorithm
 * @return page fault times
 */
std::size_t
FIFO_algorithm(std::size_t memory_size,
               const std::vector<std::size_t> & address_list);

/**
 * @brief LRU algorithm
 * @return page fault times
 */
std::size_t
LRU_algorithm(std::size_t memory_size,
              const std::vector<std::size_t> & address_list);

/**
 * @brief OPT algorithm
 * @return page fault times
 */
std::size_t
OPT_algorithm(std::size_t memory_size,
              const std::vector<std::size_t> & address_list);





