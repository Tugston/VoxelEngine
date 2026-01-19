#include "HeadingParentPanel.h"

//STND
#include <string>

//ENGN
#include "Engine.h"

namespace Editor
{
	//initializing the project name needs to be read in from a save file or something
	//just hard coding it for now because it is not important!!!
	HeadingParentPanel::HeadingParentPanel(std::string_view appName, float height):
		m_Height(height), m_ProjectName("Voxel Game"), BasePanel(appName)
	{
	}

	HeadingParentPanel::~HeadingParentPanel()
	{
	}

	void HeadingParentPanel::Draw() const
	{
		if (!imguiViewport) return;

		ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar;

		ImGui::SetNextWindowPos(imguiViewport->Pos);
		ImGui::SetNextWindowSize(ImVec2{ ImGui::GetMainViewport()->Size.x , m_Height });

		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4{ 0.f, 0.f, 0.f, 1.f });

		if (ImGui::Begin("Menu", nullptr, flags))
		{
			//top text
			ImGui::AlignTextToFramePadding();
			ImGui::TextUnformatted(std::string(m_ProjectName).c_str());
			ImGui::SameLine();
			ImGui::TextUnformatted(std::string(m_Name).c_str());

			ImGui::Separator();

			//not utilizing menu bar, because I can't get the top text above it
			//so just raw dogging BeginMenus
			//probably not the best, but idk what else to do and this works.
			//plus its the editor, its supposed to be unoptimized lol
			if (ImGui::BeginMenu("File"))
			{
				ImGui::MenuItem("Save All");
				ImGui::MenuItem("New Level");
				ImGui::EndMenu();
			}
			ImGui::SameLine();
			if (ImGui::BeginMenu("Settings"))
			{
				ImGui::MenuItem("Setting 1");
				ImGui::MenuItem("Setting 2");
				ImGui::MenuItem("Setting 3");
				ImGui::EndMenu();
			}

		}

		ImGui::End();

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
