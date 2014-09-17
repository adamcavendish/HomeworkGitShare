#include "Font.hpp"
// STL
#include <iostream>
// Current Project
#include "Common/shaders.hpp"

void Font::init() {
    if(FT_Init_FreeType(&m_ftlib)) {
        std::cerr << "Init FreeType Library error!" << std::endl;
        std::exit(EXIT_FAILURE);
    }//if

    // Load the font
    if(FT_New_Face(m_ftlib, m_fontfile.c_str(), 0, &m_face)) {
        std::cerr << "Cannot open font file: " << m_fontfile << std::endl;
        std::exit(EXIT_FAILURE);
    }//if

	m_programID = loadShaders("shaders/Font_vshader.glsl", "shaders/Font_fshader.glsl");
    m_attributeCoord = glGetAttribLocation(m_programID, "coord");
	m_uniformTex = glGetUniformLocation(m_programID, "tex");
    m_uniformColor = glGetUniformLocation(m_programID, "color");
}//init()

void Font::cleanup();

void Font::displayText(
        const std::string & text,
        float x, float y,
        float scaleX, float scaleY)
{
}//displayText(text, x, y, scaleX, scaleY)

void Font::update();

void Font::keyCallback(GLFWwindow * window, int key, int scancode, int action, int mods);

void Font::mouseCallback(GLFWwindow * window, int button, int action, int mods);

