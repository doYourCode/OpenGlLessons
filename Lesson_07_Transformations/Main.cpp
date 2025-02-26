#include "TransformApp.h"

#include <glad.c>

int main(void)
{
    TransformApp app(800, 800, "Lesson 07: Transformations");

    app.Run();

    app.Clear();
}