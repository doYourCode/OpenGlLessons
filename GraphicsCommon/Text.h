#pragma once

#include <iostream>
#include <map>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

/// Holds all state information relevant to a character as loaded using FreeType
struct Character
{
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // Size of glyph
    glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};

class Text
{
public:

    explicit Text(const char* filePath = "");

    void Draw(std::string text, float x, float y, float scale, const glm::vec3& color);

	static void SetRootPath(const std::string& path) { Text::rootPath = path; }

private:

    std::map<GLchar, Character> Characters;

    unsigned int vao = 0;
    unsigned int vbo = 0;
    unsigned int shader = 0;

	static std::string rootPath;
};