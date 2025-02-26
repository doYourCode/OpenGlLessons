#include "Camera3D.h"

#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Camera3D::Camera3D(GLFWwindow* window, glm::vec3 position, glm::vec3 target, float aspectRatio)
    :
    window(window),
    position(position),
    target(target),
    up(glm::vec3(0.0f, 1.0f, 0.0f)),
    aspectRatio(aspectRatio),
    fov(45.0f),
    nearPlane(0.1f),
    farPlane(100.0f),
    movementSpeed(2.5f),
    mouseSensitivity(0.1f),
    movementMode(MovementMode::FREE),
    firstMouse(true),
    lastX(0.0),
    lastY(0.0) 
{
    orientation = glm::quatLookAt(glm::normalize(target - position), up);
}

void Camera3D::processKeyboard(GLFWwindow* window, float deltaTime)
{
    switch (movementMode) {
    case MovementMode::FREE:
        moveFree(deltaTime);
        break;
    case MovementMode::FPS:
        moveFPS(deltaTime);
        break;
    case MovementMode::ORBIT:
        moveOrbit(deltaTime);
        break;
    }
}

void Camera3D::processMouse(double xpos, double ypos)
{
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xOffset = static_cast<float>(xpos - lastX) * mouseSensitivity;
    float yOffset = static_cast<float>(lastY - ypos) * mouseSensitivity;
    lastX = xpos;
    lastY = ypos;

    glm::quat pitchQuat = glm::angleAxis(glm::radians(yOffset), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::quat yawQuat = glm::angleAxis(glm::radians(xOffset), glm::vec3(0.0f, 1.0f, 0.0f));
    orientation = yawQuat * orientation * pitchQuat;
    orientation = glm::normalize(orientation);
}

void Camera3D::setMovementMode(MovementMode mode)
{
    movementMode = mode;
}

glm::mat4 Camera3D::getViewMatrix() const
{
    return glm::lookAt(position, position + glm::rotate(orientation, glm::vec3(0.0f, 0.0f, -1.0f)), up);
}

glm::mat4 Camera3D::getProjectionMatrix() const
{
    return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}

void Camera3D::moveFree(float deltaTime)
{
    float velocity = movementSpeed * deltaTime;
    glm::vec3 forward = glm::rotate(orientation, glm::vec3(0.0f, 0.0f, -1.0f));
    glm::vec3 right = glm::rotate(orientation, glm::vec3(1.0f, 0.0f, 0.0f));

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) position += forward * velocity;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) position -= forward * velocity;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) position -= right * velocity;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) position += right * velocity;
}

void Camera3D::moveFPS(float deltaTime)
{
    moveFree(deltaTime);
    position.y = 0.0f; // Lock movement to XZ plane
}

void Camera3D::moveOrbit(float deltaTime)
{
    float velocity = movementSpeed * deltaTime;
    glm::vec3 direction = position - target;
    glm::quat rotation = glm::angleAxis(glm::radians(velocity), up);
    position = target + rotation * direction;
}