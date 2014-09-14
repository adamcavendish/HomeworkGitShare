#include "shaders.hpp"
// STL
#include <iostream>
#include <fstream>
#include <string>
// OpenGL
#include <GL/glew.h>

GLuint loadShaders(const std::string & vertexFilePath,
        const std::string & fragmentFilePath)
{
	// Create the shaders
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::ifstream vertexShaderStream(vertexFilePath);
	if(!vertexShaderStream.is_open()) {
        std::cerr << "Impossible to open " << vertexFilePath << '\n';
        return 0;
    }//if
	std::string vertexShaderCode(
            (std::istreambuf_iterator<char>(vertexShaderStream)),
            std::istreambuf_iterator<char>());

	// Read the Fragment Shader code from the file
	std::ifstream fragmentShaderStream(fragmentFilePath);
	if(!fragmentShaderStream.is_open()) {
        std::cerr << "Impossible to open " << fragmentFilePath << '\n';
        return 0;
	}//if
	std::string fragmentShaderCode(
            (std::istreambuf_iterator<char>(fragmentShaderStream)),
            std::istreambuf_iterator<char>());

	GLint status = GL_FALSE;
	int infoLogLength;

	// Compile Vertex Shader
    std::cout << "Compiling Vertex Shader: " << vertexFilePath << '\n';
	const char * vertexSourcePointer = vertexShaderCode.c_str();
	glShaderSource(vertexShaderID, 1, &vertexSourcePointer , nullptr);
	glCompileShader(vertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &status);
	glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if(infoLogLength > 0){
        std::string vertexShaderErrorMessage(infoLogLength + 1, '\0');
		glGetShaderInfoLog(vertexShaderID, infoLogLength, nullptr,
                (GLchar *)(vertexShaderErrorMessage.data()));
        std::cerr << vertexShaderErrorMessage << '\n';
	}//if

	// Compile Fragment Shader
    std::cout << "Compiling Fragment Shader: " << fragmentFilePath << '\n';
	char const * fragmentSourcePointer = fragmentShaderCode.c_str();
	glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer, nullptr);
	glCompileShader(fragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &status);
	glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if(infoLogLength > 0){
        std::string fragmentShaderErrorMessage(infoLogLength + 1, '\0');
		glGetShaderInfoLog(fragmentShaderID, infoLogLength, nullptr,
                (GLchar *)(fragmentShaderErrorMessage.data()));
        std::cerr << fragmentShaderErrorMessage << '\n';
	}//if

	// Link the program
    std::cout << "Linking program: " << vertexFilePath << " & "
        << fragmentFilePath << '\n';
	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	// Check the program
	glGetProgramiv(programID, GL_LINK_STATUS, &status);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if(infoLogLength > 0){
        std::string programErrorMessage(infoLogLength + 1, '\0');
		glGetProgramInfoLog(programID, infoLogLength, nullptr,
                (GLchar *)(programErrorMessage.data()));
        std::cerr << programErrorMessage << '\n';
	}//if

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return programID;
}//loadShaders(vertexShaderStream, fragmentFilePath)

