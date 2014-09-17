// C-Standard
#include <cstdlib>
// STL
#include <iostream>
#include <vector>
// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
// Current Project
#include "HW01DrawLine/HW01DrawLine.hpp"

GLuint vertexArrayID;
GLuint programID;
GLuint vertexBuffer;
GLuint loc_vPosition;

bool startOrEnd = false; // false for start, true for end
bool updated = false; // whether the data has been updated
glm::vec2 lineStart(-0.153746, 0.138274);
glm::vec2 lineEnd(0.300856, -0.474033);
std::vector<glm::vec2> points;

HW01DrawLine hw01DrawLine;

void init() {
	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    hw01DrawLine.init();
}//init()

void display() {
    hw01DrawLine.display();
}//display()

void update() {
    hw01DrawLine.update();
}//update()

void cleanup() {
    hw01DrawLine.cleanup();
}//cleanup()

void keyCallback(GLFWwindow * window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    hw01DrawLine.keyCallback(window, key, scancode, action, mods);
}//keyCallback(window, key, scancode, action, mods)

void mouseCallback(GLFWwindow * window, int button, int action, int mods) {
    hw01DrawLine.mouseCallback(window, button, action, mods);
}//mouseCallback(window, button, action, mods)

void errorCallback(int error, const char * description) {
    std::cerr
        << "error code: " << error
        << " info: " << description
        << std::endl;
}//errorCallback(error, description)

int main(int argc, char * argv[])
{
    // Initialize the library
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!\n";
        std::exit(EXIT_FAILURE);
    }//if

    // OpenGL 3.3+
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    GLFWwindow * window = glfwCreateWindow(1024, 768, "Hello World", nullptr, nullptr);
    if(!window) {
        std::cerr << "Failed to open GLFW Window!\n";
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }//if

    // Error callback for processing error events
    glfwSetErrorCallback(errorCallback);
    // Make the window's context current
    glfwMakeContextCurrent(window);
    // Key callback for keyboard input
    glfwSetKeyCallback(window, keyCallback);
    // Mouse callback for mouse input
    glfwSetMouseButtonCallback(window, mouseCallback);

	// Initialize GLEW
	if(glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        glfwTerminate();
		return -1;
	}//if

    init();

    // Loop until the user closes the window
    while(!glfwWindowShouldClose(window)) {

        display();

        update();

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }//while

    cleanup();

    glfwDestroyWindow(window);
    glfwTerminate();

    std::exit(EXIT_SUCCESS);
}//main

