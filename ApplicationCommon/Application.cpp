#include "Application.h"

void CenterWindow(GLFWwindow* window)
{
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    if (!monitor)
        return;

    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    if (!mode)
        return;

    int monitorX, monitorY;
    glfwGetMonitorPos(monitor, &monitorX, &monitorY);

    int windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);

    glfwSetWindowPos(
        window,
        monitorX + (mode->width - windowWidth) / 2,
        monitorY + (mode->height - windowHeight) / 2);
}

Application::Application(int width, int height, const char* title)
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    this->window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!this->window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(this->window, key_callback);

    glfwMakeContextCurrent(this->window);
    gladLoadGL();
    glfwSwapInterval(1);

    glClearColor(0.0, 0.0, 0.0, 1.0);

    CenterWindow(this->window);
    glfwShowWindow(this->window);

    this->width = width;
    this->height = height;
}

void Application::Run()
{
    this->LoadContent();

    int viewportWidth, viewportHeight;
    /// 
    ///////////////////

    while (!glfwWindowShouldClose(this->window))
    {
        glfwGetFramebufferSize(window, &viewportWidth, &viewportHeight);

        this->Update(GetDeltaTime());

        glViewport(0, 0, width, height);

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        this->Draw();

        glfwSwapBuffers(this->window);
    }
}

void Application::Clear()
{
    this->UnloadContent();

    glfwDestroyWindow(this->window);

    glfwTerminate();

    exit(EXIT_SUCCESS);
}

double Application::GetDeltaTime()
{
    double now = glfwGetTime();
    double delta = now - this->lastFrameTime;
    this->lastFrameTime = now;
    return delta;
}

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}