#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <GLFW/glfw3.h>

class Camera3D
{
public:
    enum class MovementMode { FREE, FPS, ORBIT };

    Camera3D(GLFWwindow* window, glm::vec3 position, glm::vec3 target, float aspectRatio);

    void processKeyboard(GLFWwindow* window, float deltaTime);
    void processMouse(double xpos, double ypos);

    void setMovementMode(MovementMode mode);

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;

private:

    void moveFree(float deltaTime);
    void moveFPS(float deltaTime);
    void moveOrbit(float deltaTime);

    GLFWwindow* window;

    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;
    glm::quat orientation;

    float aspectRatio;
    float fov;
    float nearPlane;
    float farPlane;
    float movementSpeed;
    float mouseSensitivity;
    MovementMode movementMode;

    bool firstMouse;
    double lastX;
    double lastY;
};