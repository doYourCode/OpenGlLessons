#include "TextureApp.h"

#include "Shader.h"
#include "Texture.h"
#include "Texture2D.h"

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

const std::array<float, 6> texCoordData =
{   // U    // V
    0.0f,   1.0f,
    1.0f,   1.0f,
    0.5f,   0.0f
};

void TextureApp::LoadContent()
{
    CreateBuffer();

    LoadShaderProgram();

    LoadTexture();

    glClearColor(0.3f, 0.35f, 0.4f, 1.0f);
}

void TextureApp::Draw()
{
    DrawBuffer();

    this->text.Draw("Press ESC to exit", 32, 32, 0.333f, glm::vec4(0.9f, 0.85f, 0.1f, 1.0f));
}

void TextureApp::CreateBuffer()
{
    glGenVertexArrays(1, &this->vao);
    glGenBuffers(1, &this->vbo);
    glGenBuffers(1, &this->colorVbo);
    glGenBuffers(1, &this->texCoordVbo);

    glBindVertexArray(this->vao);

    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesData), verticesData.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, this->colorVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, this->texCoordVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoordData), texCoordData.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(2);
}

void TextureApp::LoadShaderProgram()
{
    Shader::SetRootPath("../asset/shader/");
    this->shader = Shader::CreateProgram("Textured", "texture.vert", "texture.frag");
}

void TextureApp::LoadTexture()
{
    this->texture1 = Texture2D::LoadFromFile("../asset/texture/uvChecker.jpg");
    this->texture2 = Texture2D::LoadFromFile("../asset/texture/stop.png");

    glUseProgram(this->shader);
    glUniform1i(glGetUniformLocation(this->shader, "texture1"), 0);
    glUniform1i(glGetUniformLocation(this->shader, "texture2"), 1);
}

void TextureApp::DrawBuffer() const
{
    // We need to clear the draw state after the text rendering.
    glDisable(GL_CULL_FACE);

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, this->texture2);

    glUseProgram(this->shader);

    glBindVertexArray(this->vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}