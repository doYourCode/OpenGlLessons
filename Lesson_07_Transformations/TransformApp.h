#pragma once

#include "Application.h"

class TransformApp : public Application
{
public:
    TransformApp(int width, int height, const char* title) : Application(width, height, title) {};

    void LoadContent();

    void Update(double deltaTime);

    void Draw();
};