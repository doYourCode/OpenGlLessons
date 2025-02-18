#include "ImGuiLessonApp.h"

#include <glad.c>

int main(void)
{
    ImGuiLessonApp app(800, 800, "Lesson 01: Window and ImGui");

    app.Run();

    app.Clear();
}