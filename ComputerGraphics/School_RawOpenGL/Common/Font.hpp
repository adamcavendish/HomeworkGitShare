#pragma once
// STL
#include <string>
// Freetype
#include <ft2build.h>
#include FT_FREETYPE_H

class Font {
public: //functions
    Font(const std::string & fontfile) :
        m_fontfile(fontfile)
    {}

    ~Font() {}
    
    void init();

    void cleanup();

    void displayText(const std::string & text,
            float x, float y,
            float scaleX, float scaleY);
    
    void update();

    void keyCallback(GLFWwindow * window, int key, int scancode, int action, int mods);

    void mouseCallback(GLFWwindow * window, int button, int action, int mods);
private: //member
    FT_Library m_ftlib;
    FT_Face m_face;
    std::string m_fontfile;
    GLuint m_programID;
    GLint m_attributeCoord;
    GLint m_uniformTex;
    GLint m_uniformColor;
    GLuint m_vertexBuffer;
};//class Font

