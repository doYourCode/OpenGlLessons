#include "MeshLoader.h"
#include <glad.c>

int main(void)
{
    MeshLoader app(800, 800, "Lesson 09: Mesh Loading");

    app.Run();

    app.Clear();
}