CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_CXX_COMPILER g++)
SET(CMAKE_CXX_FLAGS "-std=c++11 -Wall -march=native -flto -O3")
INCLUDE_DIRECTORIES(BEFORE "${CMAKE_SOURCE_DIR}/include/")

# PROJECT
PROJECT("MemoryManagement")
MESSAGE(STATUS "Project: " ${PROJECT_NAME})

SET(__SRC__
    ./src/helper_functions.cpp
    ./src/main.cpp
)
SET(__TARGET_NAME__ "MemoryManagement")
ADD_EXECUTABLE(${__TARGET_NAME__} ${__SRC__})

