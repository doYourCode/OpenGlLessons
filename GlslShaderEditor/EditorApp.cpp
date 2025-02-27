#include "EditorApp.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <fstream>
#include <string>
#include <iterator>
#include <filesystem>

#include <tinyfiledialogs.h>
#include "IconsFontAwesome5.h"

#include "Shader.h"
#include <iostream>

#include <FileUtils.h>

static const ImVec4 activeCompileButtonColor = ImVec4(0.2f, 0.9f, 0.22f, 1.0f);

static const ImVec4 inactiveCompileButtonColor = ImVec4(0.9f, 0.2f, 0.22f, 1.0f);

void SetupImGuiStyle();

/*
std::string loadFileToString(const std::string& filename)
{
	try 
	{
		std::ifstream file(filename, std::ios::binary);
		if (!file)
		{
			std::cerr << "Error: Failed to open file: " << filename << std::endl;
			return "";
		}
		return { std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };
	}
	catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
		return "";
	}
}

bool saveStringToFile(const std::string& filename, const std::string& content)
{
	try
	{
		std::ofstream file(filename, std::ios::binary);
		if (!file)
		{
			std::cerr << "Error: Failed to open file: " << filename << std::endl;
			return false;
		}

		file.write(content.data(), content.size());

		if (!file)
		{  // Check if the write operation failed
			std::cerr << "Error: Failed to write to file: " << filename << std::endl;
			return false;
		}

		return true;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
		return false;
	}
}
*/

EditorApp::EditorApp(int width, int height, const char* title) : GuiApplication(width, height, title)
{

};

void EditorApp::LoadContent()
{
	auto lang = TextEditor::LanguageDefinition::GLSL();

	vertTextEditor.SetLanguageDefinition(lang);
	vertTextEditor.SetPalette(TextEditor::GetDarkPalette());
	vertTextEditor.textEditorLabel = "Vertex Shader";
	vertTextEditor.filePathFilters.push_back("*.vert*");

	fragTextEditor.SetLanguageDefinition(lang);
	fragTextEditor.SetPalette(TextEditor::GetDarkPalette());
	fragTextEditor.textEditorLabel = "Fragment Shader";
	fragTextEditor.filePathFilters.push_back("*.frag*");

	// DEVERIA CARREGAR UM FONT AWESOME AQUI

	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontDefault();
	float baseFontSize = 13.0f; // 13.0f is the size of the default font. Change to the font size you use.
	float iconFontSize = baseFontSize * 2.0f / 3.0f; // FontAwesome fonts need to have their sizes reduced by 2.0f/3.0f in order to align correctly

	// merge in icons from Font Awesome
	static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
	ImFontConfig icons_config;
	icons_config.MergeMode = true;
	icons_config.PixelSnapH = true;
	icons_config.GlyphMinAdvanceX = iconFontSize;
	io.Fonts->AddFontFromFileTTF(FONT_ICON_FILE_NAME_FAR, iconFontSize, &icons_config, icons_ranges);
	std::cout << io.Fonts->Fonts.Size;
}

void EditorApp::Update(double deltaTime)
{
}

void EditorApp::Draw()
{

}

void EditorApp::DrawGui()
{
    glDisable(GL_DEPTH_TEST);
	
    // Start ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();

	SetupImGuiStyle();

    ImGui::DockSpaceOverViewport();

	DrawGuiTests();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void DrawViewport()
{
	ImGui::Begin("Perspective", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize);
	
	ImGui::End();
}

void EditorApp::DrawEditors()
{
	ImGui::Begin("Editor Tabs");

	if (ImGui::BeginTabBar("mainTabBar"))
	{
		if (ImGui::BeginTabItem(this->vertTextEditor.textEditorLabel.c_str()))
		{
			this->TextEditorRender(this->vertTextEditor, this->vertTextEditor.textEditorLabel, this->vertTextEditor.currentFileToEdit);

			
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem(this->fragTextEditor.textEditorLabel.c_str()))
		{
			this->TextEditorRender(this->fragTextEditor, this->fragTextEditor.textEditorLabel, this->fragTextEditor.currentFileToEdit);
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Shader Controls"))
		{
			ImGui::Text("Controls"); ImGui::Text(ICON_FA_PAINT_BRUSH "  Paint");
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Shader Options"))
		{
			ImGui::Text("Options");
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Shader Info"))
		{
			ImGui::Text("Information about uniforms, etc.");
			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}

	ImGui::End();
}

void EditorApp::DrawGuiTests()
{
	DrawEditors();

	DrawViewport();
}

const void EditorApp::SaveToFile(TextEditor& textEditor, const std::vector<const char*>& filtersArray)
{
	auto filePath = Utils::File::SaveDialog("Select a file", textEditor.currentFileToEdit, filtersArray);
	if (!filePath.empty())
	{
		textEditor.currentFileToEdit = std::filesystem::path(filePath).filename().string();
		auto text = textEditor.GetText();
		Utils::File::SaveFromString(filePath, text);
	}
}

const void EditorApp::LoadFromFile(TextEditor& textEditor, const std::vector<const char*>& filtersArray)
{
	auto filePath = Utils::File::LoadDialog("Select a file", filtersArray);
	if (!filePath.empty())
	{
		textEditor.currentFileToEdit = std::filesystem::path(filePath).filename().string();
		auto file = Utils::File::LoadToString(filePath);
		textEditor.SetText(file);
	}
}

void EditorApp::TryToCompile(TextEditor& textEditor)
{
	Shader::ResetShaderErrors();

	Shader::CreateProgramFromString(textEditor.currentFileToEdit, this->vertTextEditor.GetText(), this->fragTextEditor.GetText());

	textEditor.markers.clear();

	for (auto& m : Shader::GetShaderErrors())
	{
		if (!textEditor.markers.count(m.lineNumber))
		{
			textEditor.markers.insert(
				std::make_pair<int, std::string>(
					m.lineNumber,
					std::string(m.errorCode + " : " + m.errorMessage)));
		}
	}
	textEditor.SetErrorMarkers(textEditor.markers);
}


void EditorApp::UnloadContent()
{
}

void EditorApp::TextEditorRender(TextEditor& textEditor, const std::string& editorLabel, std::string& fileToEdit)
{
	auto cpos = textEditor.GetCursorPosition();

	if (ImGui::Button("New", ImVec2(96, 48)))
	{
		textEditor.SetText("#version 460 core");
		textEditor.currentFileToEdit = "";
	}

	ImGui::SameLine();
	if (ImGui::Button("Save", ImVec2(96, 48)))
	{
		SaveToFile(textEditor, textEditor.filePathFilters);
	}

	ImGui::SameLine();
	if (ImGui::Button("Load", ImVec2(96, 48)))
	{
		LoadFromFile(textEditor, textEditor.filePathFilters);
	}

	ImGui::SameLine();
	if (this->canCompile)
		ImGui::PushStyleColor(ImGuiCol_Button, activeCompileButtonColor);
	else
		ImGui::PushStyleColor(ImGuiCol_Button, inactiveCompileButtonColor);
	if (ImGui::Button("Compile", ImVec2(96, 48)))
	{
		this->TryToCompile(textEditor);
	}
	ImGui::PopStyleColor();
	
	/*
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Save"))
			{
				auto textToSave = textEditor.GetText();
				/// save text....
			}
			if (ImGui::MenuItem("Load"))
			{
				const std::vector<const char*> filtersArray = { "*.vert*", "*.frag*", "*.glsl*" };
				auto filePath = tinyfd_openFileDialog("Select a file", "", (int)filtersArray.size(), filtersArray.data(), nullptr, 0);
				if (filePath)
				{
					fileToEdit = std::filesystem::path(filePath).filename().string();
					auto file = loadFileToString(filePath);
					textEditor.SetText(file);
				}
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			bool ro = textEditor.IsReadOnly();
			if (ImGui::MenuItem("Read-only mode", nullptr, &ro))
				textEditor.SetReadOnly(ro);
			ImGui::Separator();

			if (ImGui::MenuItem("Undo", "ALT-Backspace", nullptr, !ro && textEditor.CanUndo()))
				textEditor.Undo();
			if (ImGui::MenuItem("Redo", "Ctrl-Y", nullptr, !ro && textEditor.CanRedo()))
				textEditor.Redo();

			ImGui::Separator();

			if (ImGui::MenuItem("Copy", "Ctrl-C", nullptr, textEditor.HasSelection()))
				textEditor.Copy();
			if (ImGui::MenuItem("Cut", "Ctrl-X", nullptr, !ro && textEditor.HasSelection()))
				textEditor.Cut();
			if (ImGui::MenuItem("Delete", "Del", nullptr, !ro && textEditor.HasSelection()))
				textEditor.Delete();
			if (ImGui::MenuItem("Paste", "Ctrl-V", nullptr, !ro && ImGui::GetClipboardText() != nullptr))
				textEditor.Paste();

			ImGui::Separator();

			if (ImGui::MenuItem("Select all", nullptr, nullptr))
				textEditor.SetSelection(TextEditor::Coordinates(), TextEditor::Coordinates(textEditor.GetTotalLines(), 0));

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}
	*/

	ImGui::Text("%6d/%-6d %6d lines  | %s | %s | %s | %s", cpos.mLine + 1, cpos.mColumn + 1, textEditor.GetTotalLines(),
		textEditor.IsOverwrite() ? "Ovr" : "Ins",
		textEditor.CanUndo() ? "*" : " ",
		textEditor.GetLanguageDefinition().mName.c_str(), textEditor.currentFileToEdit.c_str());

	textEditor.Render(textEditor.textEditorLabel.c_str());
}

void SetupImGuiStyle()
{
	ImGuiStyle& style = ImGui::GetStyle();
	ImVec4* colors = style.Colors;

	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.86f, 0.93f, 0.89f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
	colors[ImGuiCol_Tab] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
	colors[ImGuiCol_TabActive] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.86f, 0.93f, 0.89f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.86f, 0.93f, 0.89f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.86f, 0.93f, 0.89f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.86f, 0.93f, 0.89f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(0.86f, 0.93f, 0.89f, 1.00f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.86f, 0.93f, 0.89f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.86f, 0.93f, 0.89f, 1.00f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);

	style.WindowRounding = 0.0f;
	style.FrameRounding = 0.0f;
	style.GrabRounding = 0.0f;
	style.ScrollbarRounding = 0.0f;
	style.TabRounding = 0.0f;
}