#pragma once

#include "GuiApplication.h"
#include <Text.h>

class LightingApp : public GuiApplication
{
public:

    LightingApp(int width, int height, const char* title) : GuiApplication(width, height, title) {};

    void LoadContent() final;

    void Update(double deltaTime) final;

    void Draw() final;

    void DrawGui() final;

private:

    unsigned int vao = 0;

    unsigned int vbo = 0;
    unsigned int colorVbo = 0;
    unsigned int texCoordVbo = 0;
    unsigned int normalVbo = 0;
    unsigned int ebo = 0;
    size_t eboSize = 0;

    unsigned int shader = 0;
    unsigned int timerUniformLocation = 0;

    unsigned int texture1 = 0;

    float timer = 0.0f;

    Text text = Text();

    glm::vec3 lightDirection = glm::vec3(-1.0f, 1.0f, -1.0f);
    unsigned int lightDirectionUniformLocation = 0;

    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    unsigned int lightColorUniformLocation = 0;

    glm::vec3 ambientColor = glm::vec3(0.09f, 0.1f, 0.2f);
    unsigned int ambientColorUniformLocation = 0;

    glm::vec3 cameraDirection = glm::vec3(0.0);
    unsigned int cameraDirectionUniformLocation = 0;

    glm::mat4 transform = glm::mat4(1.0f);
    unsigned int modelUniformLocation = 0;

    glm::mat4 view = glm::mat4();
    unsigned int viewUniformLocation = 0;

    glm::mat4 projection = glm::mat4();
    unsigned int projectionUniformLocation = 0;

    bool showTexture = true;
    unsigned int showTextureUniformLocation = 0;

    void CreateBuffer();

    void DrawBuffer();

    void LoadShaderProgram();

    void LoadTexture();

    void SetUniformsValues(unsigned int shader);

    void SetUniformsLocations(unsigned int shader);
};