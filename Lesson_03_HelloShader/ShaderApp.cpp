#include "ShaderApp.h"

#include "Shader.h"

#include <array>

const std::array<float, 9> verticesData =
{    // x   // y    // z    //
    -0.5f, -0.5f,   0.0f,   // Vértice inferior esquerdo
     0.5f, -0.5f,   0.0f,   // inferior direito
     0.0f,  0.5f,   0.0f    // superior
};

void ShaderApp::LoadContent()
{
    CreateBuffer();

    LoadShaderProgram();

    glClearColor(0.3f, 0.35f, 0.4f, 1.0f);
}

void ShaderApp::Draw()
{
    DrawBuffer();

    this->text.Draw("Press ESC to exit", 32, 32, 0.333f, glm::vec4(0.9f, 0.85f, 0.1f, 1.0f));
}

void ShaderApp::CreateBuffer()
{
    glGenVertexArrays(1, &this->vao);
    glGenBuffers(1, &this->vbo);

    glBindVertexArray(this->vao);

    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesData), verticesData.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);
}

void ShaderApp::LoadShaderProgram()
{
    Shader::SetRootPath("../asset/shader/");
    this->shader = Shader::CreateProgram("Basic Shader", "basic.vert", "basic.frag");
}

void ShaderApp::DrawBuffer() const
{
    // We need to clear the draw state after the text rendering.
    glDisable(GL_CULL_FACE);
    glUseProgram(this->shader);

    glBindVertexArray(this->vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}