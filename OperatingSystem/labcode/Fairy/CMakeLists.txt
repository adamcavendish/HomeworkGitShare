CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(__TARGET_NAME__ main)
SET(__LINK_BOOST__ TRUE)

SET(CMAKE_CXX_COMPILER g++-4.8)
SET(CMAKE_CXX_FLAGS "-std=c++11 -Wall -march=native -O3")

INCLUDE_DIRECTORIES(BEFORE "include/")

FILE(GLOB ALL_CPP_FILES_SRC "*.h" "*.hpp" "*.cpp" "*.tcc" "*.cc")

# PROJECT
PROJECT(Fairy)
MESSAGE(STATUS "Project: " ${PROJECT_NAME})

SET(__SRC__
	src/Kernel/main.cpp
	src/kernel/Kernel.cpp
)
SET(__TARGET_NAME__ "kernel.out")
ADD_EXECUTABLE(${__TARGET_NAME__} ${__SRC__})
TARGET_LINK_LIBRARIES(


