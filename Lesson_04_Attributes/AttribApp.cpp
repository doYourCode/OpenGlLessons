#include "AttribApp.h"

#include "Shader.h"

float verticesData[] =
{    // x   // y    // z    //
    -0.5f, -0.5f,   0.0f,   // Vértice inferior esquerdo
     0.5f, -0.5f,   0.0f,   // inferior direito
     0.0f,  0.5f,   0.0f    // superior
};

float colorData[] =
{   // R    // G    // B
    1.0f,   0.0f,   0.0f,
    0.0f,   1.0f,   0.0f,
    0.0f,   0.0f,   1.0f
};

unsigned int vao, vbo, colorVbo, shaderProgram;

void CreateBuffer()
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &colorVbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesData), verticesData, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
}

void LoadShaderProgram()
{
    Shader::SetRootPath("../asset/shader/");
    shaderProgram = Shader::CreateProgram("attrib.vert", "attrib.frag");
}

void DrawBuffer(unsigned int programId)
{
    glUseProgram(programId);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void AttribApp::LoadContent()
{
    CreateBuffer();

    LoadShaderProgram();

    glClearColor(0.3f, 0.35f, 0.4f, 1.0f);
}

void AttribApp::Draw()
{
    DrawBuffer(shaderProgram);
}