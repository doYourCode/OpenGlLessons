#include "TriangleApp.h"

float verticesData[] =
{    // x   // y    // z    //
    -0.5f, -0.5f,   0.0f,   // Vértice inferior esquerdo
     0.5f, -0.5f,   0.0f,   // inferior direito
     0.0f,  0.5f,   0.0f    // superior
};

unsigned int vao, vbo;

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

void DrawBuffer()
{
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void TriangleApp::LoadContent()
{
    CreateBuffer();

    glClearColor(0.3f, 0.35f, 0.4f, 1.0f);
}

void TriangleApp::Draw()
{
    DrawBuffer();
}