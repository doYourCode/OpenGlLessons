#include "LightingApp.h"

#include <glad.c>

int main(void)
{
    LightingApp app(1200, 800, "Lesson 11: Lighting");

    app.Run();

    app.Clear();
}