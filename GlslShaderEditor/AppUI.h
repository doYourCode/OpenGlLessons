#pragma once

class EditorApp;

class AppUI
{
public:

	AppUI(EditorApp* editorApp) : editorApp(editorApp) {};

private:

	EditorApp* editorApp;
};

