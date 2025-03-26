#include "egpch.h"
#include "DebugUI.h"

#include "Core/Application.h"

namespace Engine::Debug
{
	bool UI::Init()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

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

	void UI::BeginUI(const std::string& name)
	{
		ImGui::Begin(name.c_str());
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

