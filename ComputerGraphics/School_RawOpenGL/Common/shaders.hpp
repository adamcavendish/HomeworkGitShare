#pragma once
// STL
#include <string>
// OpenGL
#include <GL/glew.h>

GLuint loadShaders(const std::string & vertexFilePath,
        const std::string & fragmentFilePath);

