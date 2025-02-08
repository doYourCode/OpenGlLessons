#pragma once

#include "Application.h"

class AttribApp : public Application
{
public:
    AttribApp(int width, int height, const char* title) : Application(width, height, title) {};

    void LoadContent();

    void Draw();
};