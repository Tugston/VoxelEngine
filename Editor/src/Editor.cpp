#include "Editor.h"
#include "../VENDOR/imgui/imgui.h"
#include "../VENDOR/imgui/imgui_impl_opengl3.h"
#include "../VENDOR/imgui/imgui_impl_glfw.h"

namespace Editor
{		
	EditorApplication::EditorApplication()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_DockingEnable;
		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_ViewportsEnable;

		const bool success = ImGui_ImplGlfw_InitForOpenGL(Application::GetWindow()->GetGLFWWindow(), true) &&
			ImGui_ImplOpenGL3_Init("#version 410");

		if (success)
			LOG_MSG("Editor Application Successfully Initialized!");
		else
			LOG_FATAL("Editor Application Not Initialized!");
	}

	EditorApplication::~EditorApplication()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void EditorApplication::Start()
	{
		Application::Start();
	}

	void EditorApplication::Tick()
	{
		

		Application::Tick();
	}

	void EditorApplication::Draw()
	{
		ImGui::Render();
		ImGui::DockSpaceOverViewport();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

}

Application* Engine::CreateApplication()
{
	return new Editor::EditorApplication;
}