#include "Application.h"
#include "TriangleApp.h"
#include <glad.c>

int main(void)
{
    TriangleApp app(800, 800, "Lesson 02: Hello Triangle");

    app.Run();

    app.Clear();
}