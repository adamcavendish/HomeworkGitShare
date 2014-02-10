#pragma once

// STL
#include <string>
#include <fstream>
#include <vector>
#include <string>

void
printUsage(const char * const name);

std::vector<std::size_t>
generateAddressList(const std::size_t addrnum);

std::vector<std::size_t>
processFile(const std::string & file);

std::vector<std::size_t>
loadData(std::ifstream & file);

void
storeData(const std::string & filename, const std::vector<std::size_t> & data);

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





