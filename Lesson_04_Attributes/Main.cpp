#include "AttribApp.h"

#include <glad.c>

int main(void)
{
    AttribApp app(800, 800, "Lesson 04: Attributes");

    app.Run();

    app.Clear();
}