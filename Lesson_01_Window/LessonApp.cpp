#include "LessonApp.h"

auto r = 0.0f, g = 0.0f, b = 0.0f;

float ClampSwap(float x, float min, float max)
{
	if (x > max)
		return min;
	else if (x < min)
		return max;
	else return x;
}

void LessonApp::Update()
{
	r += 0.01f;
	r = ClampSwap(r, 0.0f, 1.0f);
}

void LessonApp::Draw()
{
	glClearColor(r, g, b, 1.0);
}
