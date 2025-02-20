#pragma once

#include "Application.h"
#include "Text.h"

class TextureApp : public Application
{
public:
    TextureApp(int width, int height, const char* title) : Application(width, height, title) {};

    void LoadContent() final;

    void Draw() final;

private:

    unsigned int vao = 0;

    unsigned int vbo = 0;
    unsigned int colorVbo = 0;
    unsigned int texCoordVbo = 0;

    unsigned int shader = 0;

    unsigned int texture1 = 0;
    unsigned int texture2 = 0;

    Text text = Text();

    void CreateBuffer();

    void DrawBuffer() const;

    void LoadShaderProgram();

    void LoadTexture();
};