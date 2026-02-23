#include "HeadingParentPanel.h"

//STND
#include <string>

//ENGN
#include "Engine.h"

namespace Editor
{
	//initializing the project name needs to be read in from a save file or something
	//just hard coding it for now because it is not important!!!
	HeadingParentPanel::HeadingParentPanel(std::string_view appName):
		m_ProjectName("Voxel Game"), BasePanel(appName)
	{
	}

	HeadingParentPanel::~HeadingParentPanel()
	{
	}

	void HeadingParentPanel::Draw(EditorMode currentMode) const
	{
		if (!imguiViewport) return;

		ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoScrollbar;

		//need 0-1 scaling
		ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4{ 126.f / 255.f, 186.f / 255.f, 84.f / 255.f, 1.f });
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				ImGui::MenuItem("Save All");
				ImGui::MenuItem("New Level");
				ImGui::MenuItem("Open Level");
				ImGui::EndMenu();
			}

			ImGui::SetCursorPosX(ImGui::GetContentRegionAvail().x - ImGui::GetFontSize());

			InputStatusBox("1");
			InputStatusBox("2");
			InputStatusBox("3");

			ImGui::EndMainMenuBar();
		}


		ImGui::PopStyleColor();
		ImGui::PopStyleVar();
	}

	void HeadingParentPanel::SetInputDisplayMask(const UINT8 index)
	{
		m_InputModeMask = 0;
		m_InputModeMask = (1U<<index);
	}

	void HeadingParentPanel::InputStatusBox(const char* number) const
	{
		const char integralNum = Utility::FastATOI(number);

		if (m_InputModeMask & (1U << (integralNum - 1)))
		{
			ImGui::PushStyleColor(ImGuiCol_Button,			ImVec4{ 206.f / 255.f, 152.f / 255.f, 104.f / 255.f, 1.f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered,	ImVec4{ 206.f / 255.f, 152.f / 255.f, 104.f / 255.f, 1.f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive,	ImVec4{ 206.f / 255.f, 152.f / 255.f, 104.f / 255.f, 1.f });
		}
		else
		{
			ImGui::PushStyleColor(ImGuiCol_Button,			ImVec4{ 156.f / 255.f, 103.f / 255.f, 54.f / 255.f, 1.f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered,   ImVec4{ 156.f / 255.f, 103.f / 255.f, 54.f / 255.f, 1.f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive,	ImVec4{ 156.f / 255.f, 103.f / 255.f, 54.f / 255.f, 1.f });
		}

		//may add clicking later, but button doesnt need to anything currently
		if (ImGui::SmallButton(number));

		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
	}
}
