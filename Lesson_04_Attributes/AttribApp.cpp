#include "AttribApp.h"

#include "Shader.h"

#include <array>

const std::array<float, 9> verticesData =
{    // x   // y    // z    //
    -0.5f, -0.5f,   0.0f,   // Vértice inferior esquerdo
     0.5f, -0.5f,   0.0f,   // inferior direito
     0.0f,  0.5f,   0.0f    // superior
};

const std::array<float, 9> colorData =
{   // R    // G    // B
    1.0f,   0.0f,   0.0f,
    0.0f,   1.0f,   0.0f,
    0.0f,   0.0f,   1.0f
};

void AttribApp::LoadContent()
{
    CreateBuffer();

    LoadShaderProgram();

    glClearColor(0.3f, 0.35f, 0.4f, 1.0f);
}

void AttribApp::Draw()
{
    DrawBuffer();

    text.Draw("Press ESC to exit", 32, 32, 0.333f, glm::vec4(0.9f, 0.85f, 0.1f, 1.0f));
}

void AttribApp::CreateBuffer()
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &colorVbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesData), verticesData.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(1);
}

void AttribApp::LoadShaderProgram()
{
    Shader::SetRootPath("../asset/shader/");
    shader = Shader::CreateProgram("attrib.vert", "attrib.frag");
}

void AttribApp::DrawBuffer() const
{
    // We need to clear the draw state after the text rendering.
    glDisable(GL_CULL_FACE);
    glUseProgram(this->shader);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}