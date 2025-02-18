#include "IndexedApp.h"
#include <glad.c>

int main(void)
{
    IndexedApp app(800, 800, "Lesson 09: Indexed Triangles");

    app.Run();

    app.Clear();
}