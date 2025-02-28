#include "MeshLoader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Mesh.h"
#include <Text.h>

bool firstMouse = true;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;

unsigned int shaderProgram;

unsigned int texture1;

// create transformations
glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

Texture* texture;

Camera camera;

StaticMesh sMesh;

Text* text;

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

void LoadShaderProgram()
{
    Shader::SetRootPath("../asset/shader/");
    shaderProgram = Shader::CreateProgram("Shader", "mesh.vert", "mesh.frag");
}

void LoadTexture()
{
    // load and create a texture 
// -------------------------

    // texture 1
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(false); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char* data = stbi_load("../asset/texture/suzanne.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);

    glUseProgram(shaderProgram);
    glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
}

void DrawBuffer(unsigned int programId)
{
    glDisable(GL_CULL_FACE);

    glEnable(GL_DEPTH_TEST);
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glUseProgram(programId);

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, glm::value_ptr(transform));

    glm::mat4 view = glm::lookAt(camera.Position, camera.Position + camera.Front, camera.Up);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));

    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)800 / (float)800, 0.033f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));


    glBindVertexArray(sMesh.renderVao);
    
    glDrawElements(GL_TRIANGLES, sMesh.indexSize, GL_UNSIGNED_INT, nullptr); printf("HERE!");
}

void MeshLoader::LoadContent()
{
    sMesh = StaticMesh::LoadFromFile("../asset/mesh/suzanne.obj");
    CheckVAOState(sMesh.renderVao, "After LoadFromFile");

    LoadShaderProgram();

    LoadTexture();

    camera.Position.z = -18.0f;
    camera.Front.z = 1.0f;
    camera.Up.y = 1.0f;
    camera.Zoom = 5.0f;

    text = new Text("");

    glClearColor(0.3f, 0.35f, 0.4f, 1.0f);

    glfwMakeContextCurrent(this->GetWindow());
    glfwSetFramebufferSizeCallback(this->GetWindow(), framebuffer_size_callback);
    //glfwSetCursorPosCallback(this->window, mouse_callback);
    glfwSetScrollCallback(this->GetWindow(), scroll_callback);
    // tell GLFW to capture our mouse
    glfwSetInputMode(this->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void MeshLoader::Update(double deltaTime)
{
    transform = glm::rotate(transform, 0.01f, glm::vec3(0.0f, 1.0f, 0.0f));
}

void MeshLoader::Draw()
{
    CheckVAOState(sMesh.renderVao, "Before DrawBuffer");
    DrawBuffer(shaderProgram);
    CheckVAOState(sMesh.renderVao, "After DrawBuffer");

    text->Draw("Mouse scroll to zoom in/out", 32, 64, 0.333f, glm::vec4(0.9f, 0.85f, 0.1f, 1.0f));
    text->Draw("Press ESC to exit", 32, 32, 0.333f, glm::vec4(0.9f, 0.85f, 0.1f, 1.0f));
}
