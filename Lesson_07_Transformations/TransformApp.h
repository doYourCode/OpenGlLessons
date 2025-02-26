#pragma once

#include "Application.h"
#include "Text.h"

class TransformApp : public Application
{
public:

    TransformApp(int width, int height, const char* title) : Application(width, height, title) {};

    void LoadContent() final;

    void Update(double deltaTime) final;

    void Draw() final;

private:

    unsigned int vao = 0;

    unsigned int vbo = 0;
    unsigned int colorVbo = 0;
    unsigned int texCoordVbo = 0;

    unsigned int shader = 0;
    unsigned int timerUniformLocation = 0;

    unsigned int texture1 = 0;

    float timer = 0.0f;

    Text text = Text();

    // create transformations
    glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

    glm::vec3 scale = glm::vec3();;
    glm::quat rotation = glm::quat();;
    glm::vec3 translation = glm::vec3();;
    glm::vec3 skew = glm::vec3();;
    glm::vec4 _perspective = glm::vec4();;

    void CreateBuffer();

    void DrawBuffer() const;

    void LoadShaderProgram();

    void LoadTexture();
};