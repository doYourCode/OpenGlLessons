#include "CameraApp.h"
#include <glad.c>

int main(void)
{
    CameraApp app(800, 800, "Lesson 06: Uniforms");

    app.Run();

    app.Clear();
}