#include "LessonApp.h"

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

	text->Draw(0, "Press ESC to exit", 32, 32, 0.333f, glm::vec4(0.9f, 0.85f, 0.1f, 1.0f));
}
