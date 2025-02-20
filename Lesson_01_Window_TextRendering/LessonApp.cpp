#include "LessonApp.h"

#include "Utilities.h"

void LessonApp::Update(double deltaTime)
{
	r += 0.333f * (float)deltaTime;
	r = ClampSwap(r, 0.0f, 1.0f);
}

void LessonApp::Draw()
{
	glClearColor(r, g, b, 1.0);

	text.Draw("Press ESC to exit", 32, 32, 0.333f, glm::vec4(0.9f, 0.85f, 0.1f, 1.0f));
}
