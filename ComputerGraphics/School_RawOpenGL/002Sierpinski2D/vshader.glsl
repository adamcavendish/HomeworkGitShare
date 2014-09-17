#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec4 vPosition;

void main() {
    gl_Position = vPosition;
}

