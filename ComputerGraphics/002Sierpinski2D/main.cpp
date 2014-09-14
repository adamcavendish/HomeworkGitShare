// C-Standard
#include <cstdlib>
// STL
#include <iostream>
// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
// Current Project
#include "Common/shaders.hpp"

const int NumPoints = 102400;
GLuint programID;
GLuint vertexBuffer;
GLuint loc_vPosition;

void init() {
    // random seed
    std::srand(21);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // sierpoinski points
    glm::vec2 points[NumPoints];
    glm::vec2 vertices[] = {
        glm::vec2(-1.0, -1.0),
        glm::vec2( 0.0,  1.0),
        glm::vec2( 1.0, -1.0)
    };

    // choose a random point inside triangle
    points[0] = glm::vec2(0.25, 0.50);

    // calculate n-1 points
    for(int i = 1; i < NumPoints; ++i) {
        // randomly choose a vertex
        int vertexChosen = std::rand() % 3;

        // calculate the center between
        // the chosen vertex and the previous vertex
        points[i] = (points[i-1] + vertices[vertexChosen]) / glm::vec2(2.0, 2.0);
    }//for

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
}//init()

void display() {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

    // Draw points
    glDrawArrays(GL_POINTS, 0, NumPoints); // 3 indices starting at 0 -> 1 triangle

    glDisableVertexAttribArray(loc_vPosition);

    glFlush();
}//display()

void update() {
}//update()

void cleanup() {
}//cleanup()

int main(int argc, char * argv[])
{
    // Initialize the library
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!\n";
        return -1;
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
        return -1;
    }//if

    // Make the window's context current
    glfwMakeContextCurrent(window);

	// Initialize GLEW
	if(glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        glfwTerminate();
		return -1;
	}//if

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    init();

    // Loop until the user closes the window
    while(!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {

        display();

        update();

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }//while

    cleanup();
    glfwTerminate();

    return 0;
}//main

