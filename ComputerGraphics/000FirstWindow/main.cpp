// STL
#include <iostream>
// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // Loop until the user closes the window
    while(!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {
        // Render here

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }//while

    glfwTerminate();

    return 0;
}//main

