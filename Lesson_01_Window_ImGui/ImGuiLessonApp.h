#pragma once

#include "GuiApplication.h"

class ImGuiLessonApp : public GuiApplication
{
public:

    ImGuiLessonApp(int width, int height, const char* title) : GuiApplication(width, height, title) {};

    void Draw() final;

    void DrawGui() final;
};