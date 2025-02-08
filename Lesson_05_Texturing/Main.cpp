#include "TextureApp.h"
#include <glad.c>

int main(void)
{
    TextureApp app(800, 800, "Lesson 05: Texturing");

    app.Run();

    app.Clear();
}