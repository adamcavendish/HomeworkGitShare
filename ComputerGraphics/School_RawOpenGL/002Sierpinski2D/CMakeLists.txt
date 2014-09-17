cmake_minimum_required(VERSION 3.0)
# PROJECT
project(002Sierpinski2D)
message(status "Project: " ${PROJECT_NAME})

set(TARGET_NAME ${PROJECT_NAME})
set(PROJECT_SOURCE "main.cpp")

add_executable(${TARGET_NAME} ${PROJECT_SOURCE})
target_link_libraries(${TARGET_NAME} ${ALL_LIBS})

# Copy glsl files after build
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/shaders/")
add_custom_command(
    TARGET ${TARGET_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${CMAKE_CURRENT_SOURCE_DIR}/fshader.glsl"
    "${CMAKE_CURRENT_BINARY_DIR}/shaders/")
add_custom_command(
    TARGET ${TARGET_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${CMAKE_CURRENT_SOURCE_DIR}/vshader.glsl"
    "${CMAKE_CURRENT_BINARY_DIR}/shaders/")

