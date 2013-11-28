CMAKE_MINIMUM_REQUIRED(VERSION 2.8.3)
SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../cmake/;${CMAKE_MODULE_PATH}")
INCLUDE(usr_config)
INCLUDE(cotire)

INCLUDE_DIRECTORIES("../include/")

SET(__dependencies__ "")
SET(__custom_libs__ "")
SET(__target__ 069_4_cuberoot)
FILE(GLOB_RECURSE __src__ "${PROJECT_SOURCE_DIR}/${__target__}/" "${__target__}/*.[hc]pp")
ADD_EXECUTABLE(${__target__} ${__src__})
# ADD_DEPENDENCIES(${__target__} ${__dependencies__})
# TARGET_LINK_LIBRARIES(${__target__} ${__custom_libs__})
cotire(${__target__})

