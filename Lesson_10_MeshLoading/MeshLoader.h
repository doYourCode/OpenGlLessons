#pragma once

#include "Application.h"

class MeshLoader : public Application
{
public:

    MeshLoader(int width, int height, const char* title) : Application(width, height, title) {};

    void LoadContent() final;

    void Update(double deltaTime) final;

    void Draw() final;
};