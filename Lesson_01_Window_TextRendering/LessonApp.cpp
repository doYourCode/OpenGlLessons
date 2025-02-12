#include "LessonApp.h"

#define GLT_IMPLEMENTATION
#include <gltext.h>

float r = 0.0f, g = 0.0f, b = 0.0f;

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

void LessonApp::TextDraw()
{
	GLTtext* text1 = gltCreateText();
	gltSetText(text1, "Hello World!");

	gltColor(1.0f, 1.0f, 1.0f, 1.0f);
	gltDrawText2D(text1, 0.0f, 0.0f, 1.0f); // x=0.0, y=0.0, scale=1.0
}
