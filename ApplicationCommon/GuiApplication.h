#pragma once

#include "Application.h"

class GuiApplication : public Application
{
public:

	GuiApplication(int width = 512, int height = 512, const char* title = "");

	void Run() final;

	virtual void DrawGui() { /* Empty for later overriding */ };
};

