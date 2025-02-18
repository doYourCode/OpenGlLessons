#include "ImGuiLessonApp.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

float rgb[] = {0.0f, 0.0f, 0.0f};

void ImGuiLessonApp::Draw()
{
	glClearColor(rgb[0], rgb[1], rgb[2], 1.0);
}

void ImGuiLessonApp::DrawGui()
{
    glDisable(GL_DEPTH_TEST);
    // Start ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Create UI
    ImGui::Begin("This is a demo window");
    ImGui::ColorPicker3("Background Color", rgb);
    ImGui::End();

    // Render UI
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
