#pragma once

#include "Application.h"
#include "Text.h"

class UniformsApp : public Application
{
public:

    UniformsApp(int width, int height, const char* title) : Application(width, height, title) {};

    void LoadContent() final;

    void Update(double deltaTime) final;

    void Draw() final;

private:

    unsigned int vao = 0;

    unsigned int vbo = 0;
    unsigned int colorVbo = 0;
    unsigned int texCoordVbo = 0;

    unsigned int shader = 0;
    unsigned int timerUniformLocation = 0;

    unsigned int texture1 = 0;
    unsigned int texture2 = 0;

    float timer = 0.0f;

    Text text = Text();

    void CreateBuffer();

    void DrawBuffer() const;

    void LoadShaderProgram();

    void LoadTexture();
};