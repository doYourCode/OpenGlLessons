#include "CameraApp.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Texture.h"
#include "Camera.h"

#include <array>
#include <Texture2D.h>

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

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

bool firstMouse = true;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;


Camera camera;


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = static_cast<float>(2.5 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.Position += cameraSpeed * camera.Front;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.Position -= cameraSpeed * camera.Front;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.Position -= glm::normalize(glm::cross(camera.Front, camera.Up)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.Position += glm::normalize(glm::cross(camera.Front, camera.Up)) * cameraSpeed;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    camera.Yaw += xoffset;
    camera.Pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (camera.Pitch > 89.0f)
        camera.Pitch = 89.0f;
    if (camera.Pitch < -89.0f)
        camera.Pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(camera.Yaw)) * cos(glm::radians(camera.Pitch));
    front.y = sin(glm::radians(camera.Pitch));
    front.z = sin(glm::radians(camera.Yaw)) * cos(glm::radians(camera.Pitch));
    camera.Front = glm::normalize(front);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.Zoom -= (float)yoffset;
    if (camera.Zoom < 15.0f)
        camera.Zoom = 15.0f;
    if (camera.Zoom > 90.0f)
        camera.Zoom = 90.0f;
}

void CameraApp::CreateBuffer()
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &colorVbo);
    glGenBuffers(1, &texCoordVbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesData), verticesData.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, texCoordVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoordData), texCoordData.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(2);
}

void CameraApp::LoadShaderProgram()
{
    Shader::SetRootPath("../asset/shader/");
    this->shader = Shader::CreateProgram("Perspective Shader", "camera.vert", "camera.frag");
}

void CameraApp::LoadTexture()
{
    this->texture1 = Texture2D::LoadFromFile("../asset/texture/uvChecker.jpg");

    glUseProgram(this->shader);
    glUniform1i(glGetUniformLocation(this->shader, "texture1"), 0);
}

void CameraApp::DrawBuffer() const
{
    glDisable(GL_CULL_FACE);

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glUseProgram(this->shader);

    glUniformMatrix4fv(glGetUniformLocation(this->shader, "transform"), 1, GL_FALSE, glm::value_ptr(transform));

    glm::mat4 view = glm::lookAt(camera.Position, camera.Position + camera.Front, camera.Up);
    glUniformMatrix4fv(glGetUniformLocation(this->shader, "view"), 1, GL_FALSE, glm::value_ptr(view));

    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)this->GetWidth() / (float)this->GetHeight(), 0.033f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(this->shader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void CameraApp::LoadContent()
{
    CreateBuffer();

    LoadShaderProgram();

    LoadTexture();

    camera.Position.z = -3.0f;
    camera.Front.z = 1.0f;
    camera.Up.y = 1.0f;
    camera.Zoom = 60.0f;

    glClearColor(0.3f, 0.35f, 0.4f, 1.0f);

    glfwMakeContextCurrent(this->GetWindow());
    glfwSetFramebufferSizeCallback(this->GetWindow(), framebuffer_size_callback);
    //glfwSetCursorPosCallback(this->window, mouse_callback);
    glfwSetScrollCallback(this->GetWindow(), scroll_callback);
    // tell GLFW to capture our mouse
    glfwSetInputMode(this->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void CameraApp::Update(double deltaTime)
{
    processInput(this->GetWindow());

    transform = glm::translate(transform, camera.Position);
    transform = glm::rotate(transform, 0.01f, glm::vec3(0.0f, 0.0f, 1.0f));
}


void CameraApp::Draw()
{
    DrawBuffer();

    text.Draw("Mouse scroll to zoom in/out", 32, 96, 0.333f, glm::vec4(0.9f, 0.85f, 0.1f, 1.0f));
    text.Draw("fov " + std::to_string(camera.Zoom), 32, 64, 0.333f, glm::vec4(0.9f, 0.85f, 0.1f, 1.0f));
    text.Draw("Press ESC to exit", 32, 32, 0.333f, glm::vec4(0.9f, 0.85f, 0.1f, 1.0f));
}