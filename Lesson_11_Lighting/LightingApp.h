#pragma once

#include "GuiApplication.h"

class LightingApp : public GuiApplication
{
public:

    LightingApp(int width, int height, const char* title) : GuiApplication(width, height, title) {};

    void LoadContent() final;

    void Update(double deltaTime) final;

    void Draw() final;

    void DrawGui() final;

private:

    void DrawBuffer(unsigned int programId);
};