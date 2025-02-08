#pragma once

#include "Application.h"

class CameraApp : public Application
{
public:
    CameraApp(int width, int height, const char* title) : Application(width, height, title) {};

    void LoadContent();

    void Update();

    void Draw();
};