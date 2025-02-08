#include "LessonApp.h"
#include <glad.c>

int main(void)
{
    LessonApp app(800, 800, "Lesson 01: Window");

    app.Run();

    app.Clear();
}