#pragma once

#include "Application.h"

class ShaderApp : public Application
{
public:
    ShaderApp(int width, int height, const char* title) : Application(width, height, title) {};

    void LoadContent();

    void Draw();
};