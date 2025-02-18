#include "ShaderApp.h"

#include <glad.c>

int main(void)
{
    ShaderApp app(800, 800, "Lesson 03: Hello Shader");

    app.Run();

    app.Clear();
}