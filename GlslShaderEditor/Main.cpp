#include "EditorApp.h"

#include <glad.c>

int main(void)
{
    EditorApp app(1800, 960, "Glsl Shader Editor");

    app.Run();

    app.Clear();
}