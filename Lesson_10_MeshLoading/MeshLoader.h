#pragma once

#include "Application.h"

class MeshLoader : public Application
{
public:
    MeshLoader(int width, int height, const char* title) : Application(width, height, title) {};

    void LoadContent();

    void Update(double deltaTime);

    void Draw();

    void UnloadContent();
        
    void TextDraw();
};