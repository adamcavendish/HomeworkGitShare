CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_CXX_COMPILER g++-4.8)
# SET(CMAKE_CXX_FLAGS "-std=c++11 -Wall -march=native -flto -O3")
SET(CMAKE_CXX_FLAGS "-std=c++11 -g3 -gdwarf-2 -Wall -march=native")

INCLUDE_DIRECTORIES("./include")


# PROJECT
PROJECT(PL0Compiler)
MESSAGE(STATUS "Project: " ${PROJECT_NAME})

SET(__TARGET_NAME__ pl0_lexer)
SET(__SRC__
	src/lexermain.cpp
	src/lexer/Lexer.cpp
	src/lexer/WordMap.cpp
)
ADD_EXECUTABLE(${__TARGET_NAME__} ${__SRC__})



