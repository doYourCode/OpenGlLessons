#pragma once

#include "Application.h"

class TextureApp : public Application
{
public:
    TextureApp(int width, int height, const char* title) : Application(width, height, title) {};

    void LoadContent();

    void Draw();
};