#include "LessonApp.h"

#include "MathUtils.h"

void LessonApp::Update(double deltaTime)
{
	this->r += 0.333f * (float)deltaTime;
	this->r = Utils::Math::ClampSwap(this->r, 0.0f, 1.0f);
}

void LessonApp::Draw()
{
	glClearColor(this->r, this->g, this->b, 1.0);
}

