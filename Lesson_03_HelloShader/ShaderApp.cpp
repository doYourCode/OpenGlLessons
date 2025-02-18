#include "ShaderApp.h"

#include "Shader.h"
#include "Text.h"

float verticesData[] =
{    // x   // y    // z    //
    -0.5f, -0.5f,   0.0f,   // Vértice inferior esquerdo
     0.5f, -0.5f,   0.0f,   // inferior direito
     0.0f,  0.5f,   0.0f    // superior
};

unsigned int vao, vbo, shaderProgram;

Text* text;

void CreateBuffer()
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesData), verticesData, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void LoadShaderProgram()
{
    Shader::SetRootPath("../asset/shader/");
    shaderProgram = Shader::CreateProgram("basic.vert", "basic.frag");
}

void DrawBuffer(unsigned int programId)
{
    // We need to clear the draw state after the text rendering.
    glDisable(GL_CULL_FACE);
    glUseProgram(programId);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void ShaderApp::LoadContent()
{
    CreateBuffer();

    LoadShaderProgram();

    text = new Text("");

    glClearColor(0.3f, 0.35f, 0.4f, 1.0f);
}

void ShaderApp::Draw()
{
    DrawBuffer(shaderProgram);

    text->Draw(0, "Press ESC to exit", 32, 32, 0.333f, glm::vec4(0.9f, 0.85f, 0.1f, 1.0f));
}