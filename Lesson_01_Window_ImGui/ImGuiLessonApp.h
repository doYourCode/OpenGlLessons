#pragma once

#include "GuiApplication.h"

#include <array>

class ImGuiLessonApp : public GuiApplication
{
public:

    ImGuiLessonApp(int width, int height, const char* title) : GuiApplication(width, height, title) {};

    void Draw() final;

    void DrawGui() final;

private:

    std::array<float, 3> rgb = { 0.0f, 0.0f, 0.0f };
};