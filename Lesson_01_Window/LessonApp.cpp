#include "LessonApp.h"

auto r = 0.0f, g = 0.0f, b = 0.0f;

float ClampSwap(float x, float min, float max)
{
	return x > max ? min : x < min ? max : x;
}

void LessonApp::Update(double deltaTime)
{
	r += 0.333f * (float)deltaTime;
	r = ClampSwap(r, 0.0f, 1.0f);
}

void LessonApp::Draw()
{
	glClearColor(r, g, b, 1.0);
}
