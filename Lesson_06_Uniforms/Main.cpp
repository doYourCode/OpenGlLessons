#include "UniformsApp.h"

#include <glad.c>

int main(void)
{
    UniformsApp app(800, 800, "Lesson 06: Uniforms");

    app.Run();

    app.Clear();
}