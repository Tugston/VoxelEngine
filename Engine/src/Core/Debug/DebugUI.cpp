#include "egpch.h"
#include "DebugUI.h"

#include "Core/Application.h"

#define IMGUI_HAS_DOCK

namespace Engine::Debug
{
	ImGuiID UI::id;

	bool UI::Init()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_DockingEnable;
		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_ViewportsEnable;


		bool success = true;

		success = ImGui_ImplGlfw_InitForOpenGL(Application::GetWindow()->GetGLFWWindow(), true) &&
		ImGui_ImplOpenGL3_Init("#version 410");

		return success;
	}

	void UI::Destroy()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void UI::BeginUI(const std::string& name, bool docking)
	{
		ImGui::Begin(name.c_str(), nullptr, ImGuiWindowFlags_::ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize);
	}

	void UI::UpdateContext()
	{
		GLFWwindow* backupContext = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backupContext);
	}

	void UI::EndUI()
	{
		ImGui::End();
	}

	void UI::Refresh()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void UI::Render()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}

