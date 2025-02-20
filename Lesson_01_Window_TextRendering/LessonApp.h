#pragma once

#include "Application.h"
#include "Text.h"

class LessonApp : public Application
{
public:

    LessonApp(int width, int height, const char* title) : Application(width, height, title) {};

    void Update(double deltaTime) final;

    void Draw() final;

private:

    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;

    Text text = Text("");
};
