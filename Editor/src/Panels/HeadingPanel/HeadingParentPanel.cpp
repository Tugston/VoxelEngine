#include "HeadingParentPanel.h"

//STND
#include <string>

//ENGN
#include "Engine.h"

namespace Editor
{
	//initializing the project name needs to be read in from a save file or something
	//just hard coding it for now because it is not important!!!
	HeadingParentPanel::HeadingParentPanel(std::string_view appName, std::unique_ptr<std::function<void()>> quitFunction):
		m_ProjectName("Voxel Game"), m_QuitEditor(std::move(quitFunction)), BasePanel(appName)
	{
	}

	HeadingParentPanel::~HeadingParentPanel()
	{
	}

	void HeadingParentPanel::Draw() const
	{
		if (!imguiViewport) return;

		ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoScrollbar;

		float headingHeight = 0.f;

		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4{ 0.f, 0.f, 0.f, 1.f });

		if (ImGui::BeginMainMenuBar())
		{
			headingHeight = ImGui::GetWindowSize().y;

			ImGui::TextUnformatted(std::string(m_Name).c_str());

			if (ImGui::Button("X") && m_QuitEditor)
				(*m_QuitEditor)();

			ImGui::EndMainMenuBar();
		}

		ImGui::SetNextWindowPos(ImVec2{ imguiViewport->Pos.x, imguiViewport->Pos.y + headingHeight });
		ImGui::SetNextWindowSize(ImVec2{ ImGui::GetMainViewport()->Size.x, 0.f });

		if (ImGui::Begin("##MainHeaderBar", nullptr, flags))
		{
			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					ImGui::MenuItem("Save All");
					ImGui::MenuItem("New Level");
					ImGui::MenuItem("Open Level");
					ImGui::EndMenu();
				}

				ImGui::EndMenuBar();
			}

			ImGui::End();
		}

		ImGui::PopStyleColor();
	}

	void HeadingParentPanel::InputStatusBox(const char* number)
	{
		if (m_InputModeMask & (1U << (*number)));
		//set the background color to light yellow
		else;
		//set the background color to the transparent grey

		//ImGui::Begin
	}
}
