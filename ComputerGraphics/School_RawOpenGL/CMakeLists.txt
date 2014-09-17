cmake_minimum_required(VERSION 3.0)
# PROJECT
project(RootProject)
message(STATUS "Project: " ${PROJECT_NAME})
message(STATUS "PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})

find_package(OpenGL REQUIRED)
find_package(Freetype REQUIRED)

# Linking libraries
set(CUSTOM_LIBRARY
    Common)
set(X_LIBRARY
    X11
    Xxf86vm
    Xrandr
    Xi
)
set(ALL_LIBS
    ${CUSTOM_LIBRARY}
    glfw3
    GLEW
    ${X_LIBRARY}
	${OPENGL_LIBRARY}
    pthread
)

# Set using C++11
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")

# Output library path
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

# include path
include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(Common)
add_subdirectory(000FirstWindow)
add_subdirectory(001Triangle)
add_subdirectory(002Sierpinski2D)
add_subdirectory(SchoolHomework)

