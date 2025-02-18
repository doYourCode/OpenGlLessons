#include "GuiApplication.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

GuiApplication::GuiApplication(int width, int height, const char* title)
	: Application(width, height, title)
{
    // Setup ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(this->GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void GuiApplication::Run()
{
    this->LoadContent();

    int viewportWidth;
    int viewportHeight;
    /// 
    ///////////////////
    /// 

    while (!glfwWindowShouldClose(this->GetWindow()))
    {
        glfwGetFramebufferSize(this->GetWindow(), &viewportWidth, &viewportHeight);

        this->Update(GetDeltaTime());

        glViewport(0, 0, this->GetWidth(), this->GetHeight());

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        this->Draw();

        this->DrawGui();

        glfwSwapBuffers(this->GetWindow());
    }
}
