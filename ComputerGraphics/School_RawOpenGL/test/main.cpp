// C-Standard
#include <cstdlib>
// STL
#include <iostream>
// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// Current Project
#include "Common/shaders.hpp"
#include "Common/Font.hpp"

GLuint vertexArrayID;
GLuint programID;
GLuint vertexBuffer;
GLuint loc_vPosition;

std::vector<glm::vec2> points;

void init() {
	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Create and compile our GLSL program from the shaders
	programID = loadShaders("vshader.glsl", "fshader.glsl");
    // Use our shader
    glUseProgram(programID);

    // Vertex Array Object
	GLuint vertexArrayID;
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

    // Vertex Buffer Object
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec2),
            points.data(), GL_STATIC_DRAW);

    // enable vertex array, and initialize it
    loc_vPosition = glGetAttribLocation(programID, "vPosition");
    glEnableVertexAttribArray(loc_vPosition);
    glVertexAttribPointer(
        loc_vPosition,      // index
        2,                  // size per generic vertex
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        nullptr);           // array buffer offset
}//init()

void display() {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw points
    glDrawArrays(GL_POINTS, 0, points.size());

    glFlush();
}//display()

void update() {
}//update()

void cleanup() {
    // Cleanup VAO, VBO and shaders
    glDeleteProgram(programID);
    glDeleteVertexArrays(1, &vertexArrayID);
    glDeleteBuffers(1, &vertexBuffer);

    glDisableVertexAttribArray(loc_vPosition);
}//cleanup()

void keyCallback(GLFWwindow * window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}//keyCallback(window, key, scancode, action, mods)

void mouseCallback(GLFWwindow * window, int button, int action, int mods) {
    if(button == GLFW_MOUSE_BUTTON_LEFT) {
        if(action == GLFW_PRESS) {
            // left button pressed
        } else if(action == GLFW_RELEASE) {
            // left button released
        }//if-else
    } else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if(action == GLFW_PRESS) {
            // right button pressed
        } else if(action == GLFW_RELEASE) {
            // right button released
        }//if-else
    } else {
        // ...
    }//if-else
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

