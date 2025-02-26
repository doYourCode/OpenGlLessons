#pragma once

#include "GuiApplication.h"

#include "TextEditor.h"

#include <array>
#include <vector>

#include <initializer_list>
#include "AppUI.h"

class EditorApp : public GuiApplication
{
public:

    EditorApp(int width, int height, const char* title);

    void LoadContent() final;

    void Update(double deltaTime) final;

    void Draw() final;

    void DrawGui() final;

    void UnloadContent() final;

private:

    AppUI ui = AppUI(this);

    TextEditor vertTextEditor = TextEditor();
    TextEditor fragTextEditor = TextEditor();

    void TextEditorRender(TextEditor& textEditor, const std::string& editorLabel, std::string& fileToEdit);

    void DrawEditors();

    void DrawGuiTests();

    bool canCompile = false;

    void SaveToFile(TextEditor& textEditor, const std::vector<const char*>& filtersArray);

    void LoadFromFile(TextEditor& textEditor, const std::vector<const char*>& filtersArray);

    void TryToCompile(TextEditor& textEditor);
};
