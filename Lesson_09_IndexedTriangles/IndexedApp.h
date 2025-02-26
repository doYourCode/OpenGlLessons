#pragma once

#include "Application.h"
#include "Text.h"

class IndexedApp : public Application
{
public:
    IndexedApp(int width, int height, const char* title) : Application(width, height, title) {};

    void LoadContent() final;

    void Update(double deltaTime) final;

    void Draw() final;

private:

    unsigned int vao = 0;

    unsigned int vbo = 0;
    unsigned int colorVbo = 0;
    unsigned int texCoordVbo = 0;
    unsigned int ebo = 0;

    unsigned int shader = 0;
    unsigned int timerUniformLocation = 0;

    unsigned int texture1 = 0;

    float timer = 0.0f;

    Text text = Text();

    // create transformations
    glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

    void CreateBuffer();

    void DrawBuffer() const;

    void LoadShaderProgram();

    void LoadTexture();
};