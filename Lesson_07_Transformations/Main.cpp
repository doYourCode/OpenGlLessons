#include "TransformApp.h"
#include <glad.c>

int main(void)
{
    TransformApp app(800, 800, "Lesson 06: Uniforms");

    app.Run();

    app.Clear();
}