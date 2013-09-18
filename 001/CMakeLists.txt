CMAKE_MINIMUM_REQUIRED(VERSION 2.8.3)
PROJECT(001)
SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../cmake/;${CMAKE_MODULE_PATH}")
INCLUDE(usr_config)
INCLUDE(cotire)

find_package(ROOT REQUIRED)
include(${ROOT_USE_FILE})
include_directories(${ROOT_INCLUDE_DIRS})

SET(__dependencies__ "")
SET(__custom_libs__ "")
SET(__target__ 031_1)
FILE(GLOB_RECURSE __src__ "${PROJECT_SOURCE_DIR}/${__target__}/" "${__target__}/*.[hc]pp")
ADD_EXECUTABLE(${__target__} ${__src__})
# ADD_DEPENDENCIES(${__target__} ${__dependencies__})
# TARGET_LINK_LIBRARIES(${__target__} ${__custom_libs__})
cotire(${__target__})

SET(__dependencies__ "")
SET(__custom_libs__ "")
SET(__target__ 031_2)
FILE(GLOB_RECURSE __src__ "${PROJECT_SOURCE_DIR}/${__target__}/" "${__target__}/*.[hc]pp")
ROOT_EXECUTABLE(${__target__} ${__src__} LIBRARIES Gui Core Cint RIO Net Hist Graf Graf3d Gpad Tree Rint
	Postscript Matrix Physics MathCore Thread m dl)
# ADD_DEPENDENCIES(${__target__} ${__dependencies__})
# TARGET_LINK_LIBRARIES(${__target__} ${__custom_libs__})
cotire(${__target__})

