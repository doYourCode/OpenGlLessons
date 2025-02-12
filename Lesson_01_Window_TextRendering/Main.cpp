#include "LessonApp.h"
#include <glad.c>

/*
int main(void)
{
    LessonApp app(800, 800, "Lesson 01: Window");

    app.Run();

    app.Clear();
}
*/


#include <stdlib.h>
#include <stdio.h>

#include <math.h>

#include <glad/glad.h> /* https://github.com/Dav1dde/glad */
#include <GLFW/glfw3.h> /* https://github.com/glfw/glfw */

#define GLT_IMPLEMENTATION
#include "gltext.h" /* https://github.com/vallentin/glText */


int main(int argc, char* argv[])
{
	if (!glfwInit())
	{
		printf("Failed to initialize GLFW\n");
		return EXIT_FAILURE;
	}

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);

	glfwWindowHint(GLFW_ALPHA_BITS, 8);
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	glfwWindowHint(GLFW_STENCIL_BITS, 8);

	GLFWwindow* window = glfwCreateWindow(640, 480, "glText", NULL, NULL);

	if (!window)
	{
		fprintf(stderr, "Failed to create window\n");
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwShowWindow(window);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		fprintf(stderr, "Failed to load OpenGL functions and extensions\n");
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwSwapInterval(1);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	if (!gltInit())
	{
		fprintf(stderr, "Failed to initialize glText\n");
		glfwTerminate();
		return EXIT_FAILURE;
	}

	GLTtext* text1 = gltCreateText();
	gltSetText(text1, "Hello World!");

	int viewportWidth, viewportHeight;

	while (!glfwWindowShouldClose(window))
	{

		glfwGetFramebufferSize(window, &viewportWidth, &viewportHeight);

		if (glfwGetKey(window, GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(window, GLFW_TRUE);

		glViewport(0, 0, viewportWidth, viewportHeight);
		glClear(GL_COLOR_BUFFER_BIT);

		gltBeginDraw();

		gltColor(1.0f, 1.0f, 1.0f, 1.0f);
		gltDrawText2D(text1, 0.0f, 0.0f, 2.0f); // x=0.0, y=0.0, scale=1.0

		gltDrawText2DAligned(text1,
			(GLfloat)(viewportWidth / 2),
			(GLfloat)(viewportHeight / 2),
			1.0f,
			GLT_CENTER, GLT_CENTER);

		gltEndDraw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	gltDeleteText(text1);

	gltTerminate();

	glfwDestroyWindow(window);
	glfwTerminate();

	return EXIT_SUCCESS;
}
