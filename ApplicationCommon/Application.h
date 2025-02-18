#pragma once

#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <stdlib.h>
#include <stdio.h>
#include <chrono>

class Application
{
public:

	Application(int width = 512, int height = 512, const char* title = "");

	virtual ~Application() = default;

	virtual void Run();

	void Clear();

	virtual void LoadContent() { /* Empty for later overriding */ };

	virtual void Update(double deltaTime) { /* Empty for later overriding */ };

	virtual void Draw() { /* Empty for later overriding */ };

	virtual void UnloadContent() { /* Empty for later overriding */ };

	GLFWwindow* GetWindow() { return this->window; }

	glm::vec2 GetWindowDimensions() const { return glm::vec2(this->width, this->height); }

	unsigned int GetWidth() const { return this->width; }

	unsigned int GetHeight() const { return this->height; }

	unsigned int width;
	unsigned int height;

protected:

	double GetDeltaTime();

private:

	double lastFrameTime = 0.0;

	GLFWwindow* window;


};

