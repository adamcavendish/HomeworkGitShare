#include "HW01DrawLine.hpp"
// Current Project
#include "Common/shaders.hpp"
#include "../drawLine/drawLine.hpp"

void HW01DrawLine::init() {
	// Create and compile our GLSL program from the shaders
	m_programID = loadShaders(
            "shaders/HW01DrawLine_vshader.glsl",
            "shaders/HW01DrawLine_fshader.glsl");

    // Vertex Array Object
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

    // Vertex Buffer Object
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

    // enable vertex array, and initialize it
    m_loc_vPosition = glGetAttribLocation(m_programID, "vPosition");
    glEnableVertexAttribArray(m_loc_vPosition);
    glVertexAttribPointer(
        m_loc_vPosition,    // index
        2,                  // size per generic vertex
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        nullptr);           // array buffer offset
}//init()

void HW01DrawLine::display() {
    // Use our shader
    glUseProgram(m_programID);

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw points
    glDrawArrays(GL_POINTS, 0, m_points.size());

    glFlush();
}//display()

void HW01DrawLine::update() {
    if(m_updated == false) {
        m_points = lineDDA(m_lineStart, m_lineEnd, 0.001);

        glBufferData(GL_ARRAY_BUFFER, m_points.size() * sizeof(glm::vec2),
                m_points.data(), GL_STATIC_DRAW);

        m_updated = true;
    }//if
}//update()

void HW01DrawLine::cleanup() {
    // Cleanup VAO, VBO and shaders
    glDeleteProgram(m_programID);
    glDeleteVertexArrays(1, &m_vertexArrayID);
    glDeleteBuffers(1, &m_vertexBuffer);

    glDisableVertexAttribArray(m_loc_vPosition);
}//cleanup()

void HW01DrawLine::keyCallback(GLFWwindow * window, int key, int scancode, int action, int mods) {
}//keyCallback(window, key, scancode, action, mods)

void HW01DrawLine::mouseCallback(GLFWwindow * window, int button, int action, int mods) {
    if(button == GLFW_MOUSE_BUTTON_LEFT) {
        if(action == GLFW_PRESS) {
            double x, y;
            glfwGetCursorPos(window, &x, &y);
            int width, height;
            glfwGetWindowSize(window, &width, &height);

            // normalize to range [-1, 1]
            x = (x / width - 0.5) * 2;
            y = (y / height - 0.5) * -2;
            // left button pressed
            if(m_startOrEnd == false) {
                m_lineStart = glm::vec2(x, y);
                m_startOrEnd = true;
                std::cout << "line start: ("
                    << m_lineStart.x << ',' << m_lineStart.y << ")\n";
            } else {
                m_lineEnd = glm::vec2(x, y);
                m_startOrEnd = false;
                std::cout << "line end  : ("
                    << m_lineEnd.x << ',' << m_lineEnd.y << ")\n";
                // require to update the line
                m_updated = false;
            }//if-else
        }//if
    }//if
}//mouseCallback(window, button, action, mods)

