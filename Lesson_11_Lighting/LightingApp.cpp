#include "LightingApp.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include <Texture2D.h>

#include "Mesh_PosColUvNormals.h"

bool firstMouse = true;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;

Camera camera;

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
    if (camera.Zoom < 1.0f)
        camera.Zoom = 1.0f;
    if (camera.Zoom > 45.0f)
        camera.Zoom = 45.0f;
}

void LightingApp::CreateBuffer()
{
    auto mesh = Mesh_PosColUvNormals();
    mesh.loadFromFile("../asset/mesh/suzanne.obj");

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &colorVbo);
    glGenBuffers(1, &texCoordVbo);
    glGenBuffers(1, &normalVbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, mesh.positions.size() * sizeof(float), mesh.positions.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
    glBufferData(GL_ARRAY_BUFFER, mesh.positions.size() * sizeof(float), mesh.positions.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, texCoordVbo);
    glBufferData(GL_ARRAY_BUFFER, mesh.texCoords.size() * sizeof(float), mesh.texCoords.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, normalVbo);
    glBufferData(GL_ARRAY_BUFFER, mesh.normals.size() * sizeof(float), mesh.normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(3);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), mesh.indices.data(), GL_STATIC_DRAW);

    this->eboSize = mesh.indices.size();
}

void LightingApp::SetUniformsLocations(unsigned int shader)
{
    lightDirectionUniformLocation = glGetUniformLocation(shader, "lightDirection");
    lightColorUniformLocation = glGetUniformLocation(shader, "lightColor");
    ambientColorUniformLocation = glGetUniformLocation(shader, "ambientColor");
    cameraDirectionUniformLocation = glGetUniformLocation(shader, "cameraDirection");

    modelUniformLocation = glGetUniformLocation(shader, "transform");
    viewUniformLocation = glGetUniformLocation(shader, "view");
    projectionUniformLocation = glGetUniformLocation(shader, "projection");

    showTextureUniformLocation = glGetUniformLocation(shader, "showTexture");
}

void LightingApp::SetUniformsValues(unsigned int shader)
{
    glUseProgram(shader);

    glUniform3fv(lightDirectionUniformLocation, 1, glm::value_ptr(lightDirection));
    glUniform3fv(lightColorUniformLocation, 1, glm::value_ptr(lightColor));
    glUniform3fv(ambientColorUniformLocation, 1, glm::value_ptr(ambientColor));
    glUniform3fv(cameraDirectionUniformLocation, 1, glm::value_ptr(cameraDirection));

    glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(this->transform));

    this->view = glm::lookAt(camera.Position, camera.Position + camera.Front, camera.Up);
    glUniformMatrix4fv(viewUniformLocation, 1, GL_FALSE, glm::value_ptr(this->view));

    this->projection = glm::perspective(glm::radians(camera.Zoom), (float)this->GetWidth() / (float)this->GetHeight(), 0.033f, 100.0f);
    glUniformMatrix4fv(projectionUniformLocation, 1, GL_FALSE, glm::value_ptr(this->projection));

    glUniform1i(showTextureUniformLocation, this->showTexture);
}

void LightingApp::LoadShaderProgram()
{
    Shader::SetRootPath("../asset/shader/");
    this->shader = Shader::CreateProgram("Lambertian Diffuse Light Shader","lambert.vert", "lambert.frag");

    SetUniformsLocations(this->shader);
    SetUniformsValues(this->shader);
}

void LightingApp::LoadTexture()
{
    this->texture1 = Texture2D::LoadFromFile("../asset/texture/suzanne.png");

    glUseProgram(this->shader);
    glUniform1i(glGetUniformLocation(this->shader, "texture1"), 0);
}

void LightingApp::DrawBuffer()
{
    glDisable(GL_CULL_FACE);

    glEnable(GL_DEPTH_TEST);
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->texture1);

    glUseProgram(this->shader);

    glUniformMatrix4fv(this->projectionUniformLocation, 1, GL_FALSE, glm::value_ptr(this->projection));

    SetUniformsValues(this->shader);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, (GLsizei)this->eboSize, GL_UNSIGNED_INT, nullptr);
}

void LightingApp::LoadContent()
{
    CreateBuffer();

    LoadShaderProgram();

    LoadTexture();

    camera.Position.z = -18.0f;
    camera.Front.z = 1.0f;
    camera.Up.y = 1.0f;
    camera.Zoom = 5.0f;

    glClearColor(0.3f, 0.35f, 0.4f, 1.0f);

    glfwMakeContextCurrent(this->GetWindow());
    glfwSetFramebufferSizeCallback(this->GetWindow(), framebuffer_size_callback);
    //glfwSetCursorPosCallback(this->GetWindow(), mouse_callback);
    glfwSetScrollCallback(this->GetWindow(), scroll_callback);
    // tell GLFW to capture our mouse
    glfwSetInputMode(this->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void LightingApp::Update(double deltaTime)
{
    this->transform = glm::rotate(this->transform, 0.01f, glm::vec3(0.0f, 1.0f, 0.0f));
}

void LightingApp::Draw()
{
    DrawBuffer();

    this->text.Draw("Mouse scroll to zoom in/out", 32, 64, 0.333f, glm::vec4(0.9f, 0.85f, 0.1f, 1.0f));
    this->text.Draw("Press ESC to exit", 32, 32, 0.333f, glm::vec4(0.9f, 0.85f, 0.1f, 1.0f));
}

void LightingApp::DrawGui()
{
    glDisable(GL_DEPTH_TEST);
    // Start ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Create UI
    ImGui::Begin("Light Controls");
    ImGui::SliderFloat3("Light Direction", glm::value_ptr(this->lightDirection), -1.0f, 1.0f);
    ImGui::ColorPicker3("Light Color", glm::value_ptr(this->lightColor));
    ImGui::ColorPicker3("Ambient Color", glm::value_ptr(this->ambientColor));
    ImGui::Checkbox("Show Texture", &this->showTexture);
    ImGui::End();

    // Render UI
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}