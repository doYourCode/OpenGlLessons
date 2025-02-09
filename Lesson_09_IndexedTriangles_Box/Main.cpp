#include "IndexedApp.h"
#include <glad.c>

int main(void)
{
    IndexedApp app(800, 800, "Lesson 06: Uniforms");

    app.Run();

    app.Clear();
}