#pragma once

#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

static void error_callback(int error, const char* description);

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

class Application
{
public:
	Application(int width = 512, int height = 512, const char* title = "");

	void Run();

	void Clear();

	virtual void LoadContent() {};

	virtual void Update() {};

	virtual void Draw() {};

	virtual void UnloadContent() {};

private:
	GLFWwindow* window;
};

