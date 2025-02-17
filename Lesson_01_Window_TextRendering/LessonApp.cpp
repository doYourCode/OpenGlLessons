#include "LessonApp.h"

#include <iostream>
#include "Text.h"

float r = 0.0f, g = 0.0f, b = 0.0f;

Text* text;

float ClampSwap(float x, float min, float max)
{
	return x > max ? min : x < min ? max : x;
}

void LessonApp::LoadContent()
{
	text = new Text("");
}

void LessonApp::Update(double deltaTime)
{
	r += 0.333f * (float)deltaTime;
	r = ClampSwap(r, 0.0f, 1.0f);
}

void LessonApp::Draw()
{
	glClearColor(r, g, b, 1.0);

	text->Draw(0, "OpenGL is not myZovo anymore!", 32, 32, 1.0, glm::vec4(1.0f, 1.0f, 0.2f, 1.0f));
	text->Draw(0, "OpenGL is not myZovo anymore!", 32, 76, 0.75, glm::vec4(1.0f, 0.5f, 0.6f, 1.0f));
	text->Draw(0, "OpenGL is not myZovo anymore!", 32, 128, 0.5, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	text->Draw(0, "OpenGL is not myZovo anymore!", 32, 160, 0.25, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	text->Draw(0, "OpenGL is not myZovo anymore!", 32, 212, 0.125, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}
