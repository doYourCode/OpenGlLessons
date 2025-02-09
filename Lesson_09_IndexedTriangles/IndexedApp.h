#pragma once

#include "Application.h"

class IndexedApp : public Application
{
public:
    IndexedApp(int width, int height, const char* title) : Application(width, height, title) {};

    void LoadContent();

    void Update();

    void Draw();
};