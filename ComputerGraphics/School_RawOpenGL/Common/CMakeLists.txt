cmake_minimum_required(VERSION 3.0)
# PROJECT
project(Common)
message(STATUS "Project: " ${PROJECT_NAME})

set(TARGET_NAME ${PROJECT_NAME})
set(PROJECT_SOURCE "shaders.cpp")

add_library(${TARGET_NAME} ${PROJECT_SOURCE})

