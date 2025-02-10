#pragma once

#include "Application.h"

class UniformsApp : public Application
{
public:
    UniformsApp(int width, int height, const char* title) : Application(width, height, title) {};

    void LoadContent();

    void Update(double deltaTime);

    void Draw();
};