#pragma once

#include "Application.h"

class LessonApp : public Application
{

public:

    LessonApp(int width, int height, const char* title) : Application(width, height, title) {};

    void LoadContent();

    void Update(double deltaTime);

    void Draw();
};
