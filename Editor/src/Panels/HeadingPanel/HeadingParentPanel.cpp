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

	void HeadingParentPanel::InputStatusBox(const char* number) const
	{
		if (m_InputModeMask & (1U << (Utility::FastATOI(number) - 1)))
			ImGui::PushStyleColor(ImGuiCol_Button, Maths::RGBtoHex(Maths::Vector3<uint8_t>{186, 183, 84}));
		else
			ImGui::PushStyleColor(ImGuiCol_Button, Maths::RGBtoHex(Maths::Vector3<uint8_t>{156, 153, 54}));

		if (ImGui::SmallButton(number))
		{
			
		}

		ImGui::PopStyleColor();
	}
}
