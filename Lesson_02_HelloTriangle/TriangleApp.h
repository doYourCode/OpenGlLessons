#pragma once

#include "Application.h"
#include "Text.h"

class TriangleApp : public Application
{
public:

    TriangleApp(int width, int height, const char* title) : Application(width, height, title) {};

    void LoadContent() final;

    void Draw() final;

private:

    unsigned int vao = 0;
    unsigned int vbo = 0;

    Text text = Text("");

    void CreateBuffer();

    void DrawBuffer() const;
};