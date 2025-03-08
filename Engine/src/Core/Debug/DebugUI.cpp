#include "DebugUI.h"

#include "Core/Application.h"

namespace Engine
{
	bool DebugUI::Init()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		bool success = true;

		success = ImGui_ImplGlfw_InitForOpenGL(Application::GetWindow()->GetGLFWWindow(), true) &&
		ImGui_ImplOpenGL3_Init();

		return success;
	}

	void DebugUI::Destroy()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void DebugUI::BeginUI(const std::string& name)
	{
		ImGui::Begin(name.c_str());
	}

	void DebugUI::EndUI()
	{
		ImGui::End();
	}

	void DebugUI::Refresh()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void DebugUI::Render()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}

