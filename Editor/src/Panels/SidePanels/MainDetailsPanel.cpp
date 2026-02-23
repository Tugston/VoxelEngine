#include "MainDetailsPanel.h"

#include "../../Globals/Tables/TransformTables.h"

namespace Editor
{
	std::unique_ptr<TransformTable3D<float>> MainDetailPanel::m_TransformTable = nullptr;
	Maths::Vector3<float> MainDetailPanel::m_TestVec3{ 0.f, 0.f, 0.f };
	MainDetailPanel* MainDetailPanel::m_Instance = &MainDetailPanel::GetInstance();

	void MainDetailPanel::Init()
	{
		m_Instance->m_TransformTable = std::make_unique<TransformTable3D<float>>(&m_TestVec3, &m_TestVec3, &m_TestVec3);
	}

	void MainDetailPanel::Draw(EditorMode currentMode) const
	{
		ImGui::PushStyleColor(ImGuiCol_WindowBg, PANEL_BACKGROUND_COLOR);

		ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoDecoration;

		if (currentMode == EditorMode::PanelEdit)
			flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoInputs;

		ImGui::Begin("D E T A I L S", nullptr, flags);
		m_TransformTable->Draw();
		ImGui::End();

		ImGui::PopStyleColor();
	}
}
