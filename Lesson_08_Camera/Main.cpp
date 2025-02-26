#include "CameraApp.h"

#include <glad.c>

int main(void)
{
    CameraApp app(800, 800, "Lesson 08: Camera");

    app.Run();

    app.Clear();
}