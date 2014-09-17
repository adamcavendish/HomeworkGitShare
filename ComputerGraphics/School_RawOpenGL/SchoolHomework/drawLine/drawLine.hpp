#pragma once

// OpenGL
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
// STL
#include <vector>

std::vector<glm::vec2>
lineDDA(const glm::vec2 & start, const glm::vec2 & end, float deltaPixel);

std::vector<glm::vec2>
drawLineHorizontal(const glm::vec2 & start, const glm::vec2 & end, float deltaPixel);

std::vector<glm::vec2>
drawLineVertical(const glm::vec2 & start, const glm::vec2 & end, float deltaPixel);

