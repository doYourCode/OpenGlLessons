#pragma once

#include "Application.h"

class TriangleApp : public Application
{
public:
    TriangleApp(int width, int height, const char* title) : Application(width, height, title) {};

    void LoadContent();

    void Draw();
};