#pragma once

// C-Standard
#include <cstdlib>
// STL
#include <iostream>
#include <vector>
// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

class HW01DrawLine {
public: //functions
    HW01DrawLine() {}

    ~HW01DrawLine() {}

    void init();

    void cleanup();

    void display();
    
    void update();

    void keyCallback(GLFWwindow * window, int key, int scancode, int action, int mods);

    void mouseCallback(GLFWwindow * window, int button, int action, int mods);

private: // members
    GLuint m_vertexArrayID;
    GLuint m_programID;
    GLuint m_vertexBuffer;
    GLuint m_loc_vPosition;

    bool m_startOrEnd = false; // false for start, true for end
    bool m_updated = false; // whether the data has been updated
    glm::vec2 m_lineStart;
    glm::vec2 m_lineEnd;
    std::vector<glm::vec2> m_points;
};//class HW01DrawLine

