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

	this->text.Draw("Press ESC to exit", 32, 32, 0.333f, glm::vec4(0.9f, 0.85f, 0.1f, 1.0f));
}
